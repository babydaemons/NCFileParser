#pragma once
#include <thread>
#include <iostream>
#include <fstream>
#include "NCFileLoaderIF.h"
#include "NCFileParser.h"
#include "RingBuffer.h"

/// <summary>
/// NCファイルをロード・パース・バッファリングするクラスです。
/// </summary>
class NCFileLoader {
public:
	/// <summary>
	/// コンストラクタです。
	/// </summary>
	NCFileLoader() : line_num(0), buffer_status(GETLINE_NOT_READ_FILE) { }

	/// <summary>
	/// NCファイルのロードを指示します。ファイルをオープンし、ロード・パース・バッファリングを行うスレッドを起動します。
	/// </summary>
	/// <param name="path">NCファイルのパス</param>
	/// <returns>正常終了：0 / ファイルオープンエラー：-1</returns>
	int LoadFile(const char* path);

	/// <summary>
	/// NCファイルの1行分のデータを返します。
	/// </summary>
	/// <param name="block">Block構造体変数への参照</param>
	/// <returns>バッファが空：1 / ファイルの最後に到達：2 / ファイルが読み込まれていない：3 / 該当行が文法エラー：4 / 正常終了：0</returns>
	int GetLine(Block& block);

	/// <summary>
	/// ファイルをクローズし、リングバッファとバッファステータスを再初期化します。
	/// </summary>
	void UnloadFile();

private:
	/// <summary>
	/// バックグラウンドスレッドのエントリーポイントです。
	/// </summary>
	/// <param name="self">NCファイルをロード・パース・バッファリングするクラスのインスタンスポインタ</param>
	static void EntryBackgroundThread(NCFileLoader* self);

	/// <summary>
	/// NCファイルをロード・パース・バッファリングするバックグラウンドスレッドの実処理です。
	/// </summary>
	void ParseFile();

private:
	/// <summary>ロード・パース・バッファリングを行うバックグラウンドスレッドのインスタンスです。</summary>
	std::thread loader_thread;
	/// <summary>NCファイルの入力ストリームです。</summary>
	std::ifstream input_stream;
	/// <summary>NCファイルの行番号です。</summary>
	INT64 line_num;
	/// <summary>リングバッファのステータスです。</summary>
	GETLINE_RESULT buffer_status;
	/// <summary>NCファイルの入力行を解析するクラスのインスタンスです。</summary>
	NCFileParser parser;
	/// <summary>リングバッファのインスタンスです。</summary>
	RingBuffer<Block, RING_BUFFER_COUNT> ring_buffer;
};