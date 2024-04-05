#pragma once
#include "Block.h"

/// <summary>
/// LoadFile関数の戻り値を表す列挙値です。
/// </summary>
enum LOADFILE_RESULT {
	LOADFILE_SUCCESS = 0,		// 正常終了
	LOADFILE_OPEN_ERROR	= -1,	// ファイルオープンエラー
};

/// <summary>
/// NCファイルのロードを指示します。ファイルをオープンし、ロード・パース・バッファリングを行うスレッドを起動します。
/// </summary>
/// <param name="path">NCファイルのパス</param>
/// <returns>正常終了：0 / ファイルオープンエラー：-1</returns>
extern int LoadFile(const char* path);

/// <summary>
/// GetLine関数の戻り値を表す列挙値です。
/// </summary>
enum GETLINE_RESULT {
	GETLINE_SUCCESS = 0,			// 正常終了：0
	GETLINE_EMPTY_BUFFER = 1,		// バッファが空：1
	GETLINE_END_OF_FILE = 2,		// ファイルの最後に到達：2
	GETLINE_NOT_READ_FILE = 3,		// ファイルが読み込まれていない：3
	GETLINE_PARSE_ERROR = 4,		// 該当行が文法エラー：4
	GETLINE_INVOKING_THREAD = 5,	// スレッド起動中：5
};

/// <summary>
/// NCファイルの1行分のデータを返します。
/// </summary>
/// <param name="block">Block構造体変数へのポインタ</param>
/// <returns>バッファが空：1 / ファイルの最後に到達：2 / ファイルが読み込まれていない：3 / 該当行が文法エラー：4 / 正常終了：0</returns>
extern int GetLine(Block* block);

/// <summary>
/// ファイルをクローズし、リングバッファとバッファステータスを再初期化します。
/// </summary>
extern void UnloadFile();

/// <summary>
/// Block構造体のデバッグ出力用文字列を構築します。
/// </summary>
/// <param name="block">Block構造体への参照</param>
/// <param name="message">デバッグ出力用文字列を返すバッファ</param>
/// <param name="size">バッファサイズ</param>
/// <returns>デバッグ出力用文字列を返すバッファ</returns>
extern const char* BlockDump(const Block* block, char* message, int size);
