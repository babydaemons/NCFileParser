#include <string.h>
#include <stdlib.h>
#include "NCFileParser.h"
#include "NCBlockDumper.h"

#ifdef _MSC_VER
#include <windows.h>
#endif

/// <summary>
/// NCファイルのパースを行います。
/// </summary>
/// <param name="line_num">NCファイルの入力行番号</param>
/// <param name="record">NCファイルの入力行データ</param>
/// <param name="block">Block構造体への参照</param>
/// <returns>正常終了時：true / 文法エラー時：false</returns>
bool NCFileParser::Parse(INT64 line_num, const char* record, Block& block)
{
	// 初期化
	phrase = record;
	::memset(&block, 0, sizeof(block));
	block.line_num = line_num;

	// 1行に1回のみ出現するコードのパースを行います。
	ParseResult result = ParseOnce(record, block);
	if (result == ParseResult::Ok) {
		return true;
	}
	if (result == ParseResult::Error) {
		::memset(&block, 0, sizeof(block));
		block.line_num = -line_num;
		return false;
	}

	int read_count = 0;

	// 1行に複数回出現するコードのパースを行います。
	gcode_count = 1;
	while (*phrase != '\0') {
		result = ParseMany(block);
		if (result == ParseResult::Error) {
			::memset(&block, 0, sizeof(block));
			block.line_num = -line_num;
			return false;
		}
		else if (result == ParseResult::Ok) {
			++read_count;
		}
	}

	if (read_count == 0) {
		::memset(&block, 0, sizeof(block));
		block.line_num = -line_num;
		return false;
	}

#ifdef OutputDebugString
	char message[4096];
	::OutputDebugString(NCBlockDumper::Dump(block, message, sizeof(message)));
#endif

	return true;
}

/// <summary>
/// 1行に1回のみ出現するコードのパースを行います。
/// </summary>
/// <param name="record">NCファイルの入力行データ</param>
/// <param name="block">Block構造体への参照</param>
/// <returns>ParseResult列挙値</returns>
ParseResult NCFileParser::ParseOnce(const char* record, Block& block)
{
	if (record[0] == '%') {
		block.special_code = 1;
		return ParseResult::Ok;
	}
	if (::strncmp(record, "M98", 3) == 0) {
		block.m98_flg = 1;
		const char* m98 = record + 3;
		int m98_length = static_cast<int>(::strlen(m98));
		if (m98_length == 0 || m98_length > sizeof(block.m98) - 1) {
			return ParseResult::Error;
		}
		return (::strcpy_s(block.m98, m98) == 0) ? ParseResult::Ok : ParseResult::Error;
	}
	if (::strncmp(record, "OR", 2) == 0) {
		return Fetch(0, 100, block.or_flg, block.or_, 2);
	}
	if (::strncmp(record, "f_Type", 6) == 0) {
		return Fetch(0, 1, block.ftype_flg, block.ftype, 6);
	}
	return ParseResult::None;
}

/// <summary>
/// 1行に複数回出現するコードのパースを行います。
/// </summary>
/// <param name="block">Block構造体への参照</param>
/// <returns>ParseResult列挙値</returns>
ParseResult NCFileParser::ParseMany(Block& block)
{
	switch (phrase[0]) {
	case 'G':
		switch (gcode_count++) {
		case 1: return Fetch(block.g1_flg, block.g1);
		case 2: return Fetch(block.g2_flg, block.g2);
		case 3: return Fetch(block.g3_flg, block.g3);
		case 4: return Fetch(block.g4_flg, block.g4);
		default:
			return ParseResult::Error;
		}
		break;
	case 'S':
		if (::strncmp(phrase, "S1_", 2) == 0) {
			return Fetch(block.s1_flg, block.s1, 3);
		}
		if (::strncmp(phrase, "S2_", 2) == 0) {
			return Fetch(block.s2_flg, block.s2, 3);
		}
		else {
			return ParseResult::Error;
		}
		break;
	case 'A': return Fetch(block.a_flg, block.a);
	case 'B': return Fetch(block.b_flg, block.b);
	case 'C': return Fetch(block.c_flg, block.c);
	case 'D': return Fetch(block.d_flg, block.d);
	case 'E': return Fetch(block.e_flg, block.e);
	case 'F': return Fetch(block.f_flg, block.f);
	case 'H': return Fetch(block.h_flg, block.h);
	case 'I': return Fetch(block.i_flg, block.i);
	case 'J': return Fetch(block.j_flg, block.j);
	case 'K': return Fetch(block.k_flg, block.k);
	case 'L': return Fetch(block.l_flg, block.l);
	case 'M': return Fetch(block.m_flg, block.m);
	case 'N': return Fetch(block.n_flg, block.n);
	case 'O': return Fetch(block.o_flg, block.o);
	case 'P': return Fetch(block.p_flg, block.p);
	case 'Q': return Fetch(block.q_flg, block.q);
	case 'R': return Fetch(block.r_flg, block.r);
	case 'T': return Fetch(block.t_flg, block.t);
	case 'U': return Fetch(block.u_flg, block.u);
	case 'V': return Fetch(block.v_flg, block.v);
	case 'W': return Fetch(block.w_flg, block.w);
	case 'X': return Fetch(block.x_flg, block.x);
	case 'Y': return Fetch(block.y_flg, block.y);
	case 'Z': return Fetch(block.z_flg, block.z);
	case ' ':
	case '\t':
		++phrase;
		return ParseResult::None;
	default:
		return ParseResult::Error;
	}
}
