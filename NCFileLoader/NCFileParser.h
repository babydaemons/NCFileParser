#pragma once
#include "Block.h"

/// <summary>
/// パース結果を表す列挙値です。
/// </summary>
enum class ParseResult { None, Ok, Error = -1 };

/// <summary>
/// NCファイルの入力行を解析するクラスです。
/// </summary>
class NCFileParser {
public:
	/// <summary>
	/// コンストラクタです。
	/// </summary>
	NCFileParser() : phrase(nullptr), gcode_count(0) { }

	/// <summary>
	/// NCファイルのパースを行います。
	/// </summary>
	/// <param name="line_num">NCファイルの入力行番号</param>
	/// <param name="record">NCファイルの入力行データ</param>
	/// <param name="block">Block構造体への参照</param>
	/// <returns>正常終了時：true / 文法エラー時：false</returns>
	bool Parse(INT64 line_num, const char* record, Block& block);

private:
	/// <summary>
	/// 1行に1回のみ出現するコードのパースを行います。
	/// </summary>
	/// <param name="record">NCファイルの入力行データ</param>
	/// <param name="block">Block構造体への参照</param>
	/// <returns>ParseResult列挙値</returns>
	ParseResult ParseOnce(const char* record, Block& block);

	/// <summary>
	/// 1行に複数回出現するコードのパースを行います。
	/// </summary>
	/// <param name="block">Block構造体への参照</param>
	/// <returns>ParseResult列挙値</returns>
	ParseResult ParseMany(Block& block);

	/// <summary>
	/// NCファイル入力行の中のコードの値を取得します。
	/// </summary>
	/// <param name="flag">Block構造体のフラグメンバーへの参照</param>
	/// <param name="value">Block構造体の値メンバーへの参照</param>
	/// <param name="offset">入力行の中の値文字列へのオフセット</param>
	/// <returns>ParseResult列挙値</returns>
	ParseResult Fetch(char& flag, double& value, int offset = 1) {
		if (flag == 0) {
			const char* start = phrase + offset;
			flag = 1;
			value = ::strtold(phrase + offset, (char**)&phrase);
			return (phrase > start) ? ParseResult::Ok : ParseResult::Error;
		}
		else {
			return ParseResult::Error;
		}
	}

	/// <summary>
	/// NCファイル入力行の中のコードの値を取得します。
	/// </summary>
	/// <param name="min">最小値</param>
	/// <param name="max">最大値</param>
	/// <param name="flag">Block構造体のフラグメンバーへの参照</param>
	/// <param name="value">Block構造体の値メンバーへの参照</param>
	/// <param name="offset">入力行の中の値文字列へのオフセット</param>
	/// <returns>ParseResult列挙値</returns>
	ParseResult Fetch(long min, long max, char& flag, char& value, int offset) {
		if (flag == 0) {
			const char* start = phrase + offset;
			flag = 1;
			long fetched = ::strtol(start, (char**)&phrase, 10);
			if ((min <= fetched && fetched <= max) && phrase > start && *phrase == '\0') {
				value = static_cast<char>(fetched);
				return ParseResult::Ok;
			}
			else {
				return ParseResult::Error;
			}
		}
		else {
			return ParseResult::Error;
		}
	}

	/// <summary>
	/// 取得結果の値が正しいかチェックします。
	/// </summary>
	/// <param name="fetched">取得結果の値</param>
	/// <param name="min">最小値</param>
	/// <param name="max">最大値</param>
	/// <returns>ParseResult列挙値</returns>
	ParseResult Check(long fetched, long min, long max, char& value) {
		if ((min <= fetched && fetched <= max) && *phrase == '\0') {
			value = static_cast<char>(fetched);
			return ParseResult::Ok;
		}
		else {
			return ParseResult::Error;
		}
	}

private:
	/// <summary>Block構造体の中の値文字列を指すポインタ</summary>
	const char* phrase;
	/// <summary>Block構造体の中の何番目のGコードかを保持するカウンタ</summary>
	int gcode_count;
};