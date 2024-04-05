#include "NCFileLoader.h"
#include "NCBlockDumper.h"

namespace {
	NCFileLoader loader;
}

/// /// <summary>
/// NCファイルのロードを指示します。ファイルをオープンし、ロード・パース・バッファリングを行うスレッドを起動します。
/// </summary>
/// <param name="path">NCファイルのパス</param>
/// <returns>正常終了：0 / ファイルオープンエラー：-1</returns>
int LoadFile(const char* path)
{
	return loader.LoadFile(path);
}

/// <summary>
/// NCファイルの1行分のデータを返します。
/// </summary>
/// <param name="block">Block構造体変数へのポインタ</param>
/// <returns>バッファが空：1 / ファイルの最後に到達：2 / ファイルが読み込まれていない：3 / 該当行が文法エラー：4 / 正常終了：0</returns>
int GetLine(Block* block)
{
	return loader.GetLine(*block);
}

/// <summary>
/// ファイルをクローズし、リングバッファとバッファステータスを再初期化します。
/// </summary>
void UnloadFile()
{
	loader.UnloadFile();
}

/// <summary>
/// Block構造体のデバッグ出力用文字列を構築します。
/// </summary>
/// <param name="block">Block構造体への参照</param>
/// <param name="message">デバッグ出力用文字列を返すバッファ</param>
/// <param name="size">バッファサイズ</param>
/// <returns>デバッグ出力用文字列を返すバッファ</returns>
const char* BlockDump(const Block* block, char* message, int size)
{
	return NCBlockDumper::Dump(*block, message, size);
}
