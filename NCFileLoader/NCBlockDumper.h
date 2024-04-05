#pragma once
#include <sstream>
#include "Block.h"

/// <summary>
/// NCファイルの入力行を解析するクラスです。
/// </summary>
class NCBlockDumper {
public:
	/// <summary>
	/// Block構造体のデバッグ出力用文字列を構築します。
	/// </summary>
	/// <param name="block">Block構造体への参照</param>
	/// <param name="message">デバッグ出力用文字列を返すバッファ</param>
	/// <param name="size">バッファサイズ</param>
	/// <returns>デバッグ出力用文字列を返すバッファ</returns>
	static const char* Dump(const Block& block, char* message, int size);

private:
	/// <summary>
	/// Block構造体の中の値のデバッグ出力用文字列を出力文字列ストリームへ書き出します。
	/// </summary>
	/// <param name="label">Block構造体の中の値を識別するラベル文字列</param>
	/// <param name="flag">Block構造体のフラグメンバー</param>
	/// <param name="value">Block構造体の値メンバー</param>
	/// <param name="ss">出力文字列ストリーム</param>
	static void Dump(const char* label, char flag, double value, std::ostringstream& ss) {
		if (flag == 1) {
			ss << ',' << label << ',' << value;
		}
	}
};