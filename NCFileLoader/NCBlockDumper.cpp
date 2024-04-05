#include <string.h>
#include <stdlib.h>
#include "NCBlockDumper.h"

/// <summary>
/// Block構造体のデバッグ出力用文字列を構築します。
/// </summary>
/// <param name="block">Block構造体への参照</param>
/// <param name="message">デバッグ出力用文字列を返すバッファ</param>
/// <param name="size">バッファサイズ</param>
/// <returns>デバッグ出力用文字列を返すバッファ</returns>
const char* NCBlockDumper::Dump(const Block& block, char* message, int size)
{
	std::ostringstream ss;
	ss << block.line_num;
	if (block.special_code == 1) {
		ss << ",comment";
	}
	else if (block.ftype_flg == 1) {
		ss << ",f_Type," << (int)block.ftype;
	}
	else if (block.or_flg == 1) {
		ss << ",OR," << (int)block.or_;
	}
	else if (block.m98_flg == 1) {
		ss << ",M98," << block.m98;
	}
	else {
		Dump("A", block.a_flg, block.a, ss);
		Dump("B", block.b_flg, block.b, ss);
		Dump("C", block.c_flg, block.c, ss);
		Dump("D", block.d_flg, block.d, ss);
		Dump("E", block.e_flg, block.e, ss);
		Dump("F", block.f_flg, block.f, ss);
		Dump("G1", block.g1_flg, block.g1, ss);
		Dump("G2", block.g2_flg, block.g2, ss);
		Dump("G3", block.g3_flg, block.g3, ss);
		Dump("G4", block.g4_flg, block.g4, ss);
		Dump("H", block.h_flg, block.h, ss);
		Dump("I", block.i_flg, block.i, ss);
		Dump("J", block.j_flg, block.j, ss);
		Dump("K", block.k_flg, block.k, ss);
		Dump("L", block.l_flg, block.l, ss);
		Dump("M", block.m_flg, block.m, ss);
		Dump("N", block.n_flg, block.n, ss);
		Dump("O", block.o_flg, block.o, ss);
		Dump("P", block.p_flg, block.p, ss);
		Dump("Q", block.q_flg, block.q, ss);
		Dump("R", block.r_flg, block.r, ss);
		Dump("S1_", block.s1_flg, block.s1, ss);
		Dump("S2_", block.s2_flg, block.s2, ss);
		Dump("T", block.t_flg, block.t, ss);
		Dump("U", block.u_flg, block.u, ss);
		Dump("V", block.v_flg, block.v, ss);
		Dump("W", block.w_flg, block.w, ss);
		Dump("X", block.x_flg, block.x, ss);
		Dump("Y", block.y_flg, block.y, ss);
		Dump("Z", block.z_flg, block.z, ss);
	}
	ss << std::endl;
	::strcpy_s(message, size, ss.str().c_str());
	return message;
}
