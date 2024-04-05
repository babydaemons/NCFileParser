#include <windows.h>
#include <string.h>
#include "NCFileLoader.h"

#define INTERVAL std::chrono::microseconds(100)

/// <summary>
/// NCファイルのロードを指示します。ファイルをオープンし、ロード・パース・バッファリングを行うスレッドを起動します。
/// </summary>
/// <param name="path">NCファイルのパス</param>
/// <returns>正常終了：0 / ファイルオープンエラー：-1</returns>
int NCFileLoader::LoadFile(const char* path)
{
	input_stream.open(path);
	if (input_stream.fail()) {
		return LOADFILE_OPEN_ERROR;
	}

	buffer_status = GETLINE_INVOKING_THREAD;
	std::thread thread(EntryBackgroundThread, this);
	loader_thread = std::move(thread);
	loader_thread.detach();

	return LOADFILE_SUCCESS;
}

/// <summary>
/// NCファイルの1行分のデータを返します。
/// </summary>
/// <param name="block">Block構造体変数への参照</param>
/// <returns>バッファが空：1 / ファイルの最後に到達：2 / ファイルが読み込まれていない：3 / 該当行が文法エラー：4 / スレッド起動中：5 / 正常終了：0</returns>
int NCFileLoader::GetLine(Block& block)
{
	if (buffer_status == GETLINE_NOT_READ_FILE) {
		return GETLINE_NOT_READ_FILE;
	}
	else if (buffer_status == GETLINE_INVOKING_THREAD) {
		return GETLINE_INVOKING_THREAD;
	}
	else if (ring_buffer.count() > 0 && ring_buffer.pop_front(block)) {
		if (block.line_num < 0) {
			block.line_num = -block.line_num;
			return GETLINE_PARSE_ERROR;
		}
		return GETLINE_SUCCESS;
	}
	else if (buffer_status == GETLINE_END_OF_FILE) {
		if (ring_buffer.count() == 0) {
			return GETLINE_END_OF_FILE;
		}
		else if (ring_buffer.pop_front(block)) {
			if (block.line_num < 0) {
				block.line_num = -block.line_num;
				return GETLINE_PARSE_ERROR;
			}
			return GETLINE_SUCCESS;
		}
		else {
			return GETLINE_END_OF_FILE;
		}
	}
	else {
		return GETLINE_EMPTY_BUFFER;
	}
}

/// <summary>
/// ファイルをクローズし、リングバッファとバッファステータスを再初期化します。
/// </summary>
void NCFileLoader::UnloadFile()
{
	input_stream.close();
	ring_buffer.clear();
	buffer_status = GETLINE_NOT_READ_FILE;
	line_num = 0;
}

/// <summary>
/// バックグラウンドスレッドのエントリーポイントです。
/// </summary>
/// <param name="self">NCファイルをロード・パース・バッファリングするクラスのインスタンスポインタ</param>
void NCFileLoader::EntryBackgroundThread(NCFileLoader* self)
{
	self->ParseFile();
}

/// <summary>
/// NCファイルをロード・パース・バッファリングするバックグラウンドスレッドの実処理です。
/// </summary>
void NCFileLoader::ParseFile()
{
	char record[4096];
	for (line_num = 1; input_stream.is_open() && input_stream.getline(record, sizeof(record) - 1); ++line_num) {
		Block block;
		if (!parser.Parse(line_num, record, block)) {
			// パースエラー時の再初期化はNCFileParser#Parse()メソッドで実施済み
			// memset(&block, 0, sizeof(block));
			// block.line_num = -line_num;
		}

		bool stored = false;
		do {
			const int NEAR_FULL = ring_buffer.size() * 3 / 4;
			if (ring_buffer.count() < NEAR_FULL) {
				stored = ring_buffer.push_back(block);
			}
			else {
				stored = false;
			}
			std::this_thread::sleep_for(INTERVAL);
		} while (!stored);
		buffer_status = GETLINE_SUCCESS;
	}

	buffer_status = GETLINE_END_OF_FILE;
}
