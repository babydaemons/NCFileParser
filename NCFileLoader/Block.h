/// <summary>
/// NCファイル1行分データを表現する構造体を定義するヘッダファイル
/// </summary>
#pragma once

/// <summary>
/// リングバッファの段数を定義する定数値
/// </summary>
#define RING_BUFFER_COUNT	1000

typedef __int64 INT64;

/// <summary>
/// NCファイル1行分データを表現する構造体
/// </summary>
struct Block
{
	INT64 line_num;
	char special_code;	// %で始まるコメント行：1、その他：0
	char ftype_flg;		// f_Typeコードの時1
	char ftype;			// f_Typeコードの数値0 or 1
	char or_flg;		// ORコードの時1
	char or_;			// ORコードの数値0~100
	char a_flg;			// aコードの時1
	double a;			// aコードの値
	char b_flg;			// bコードの時1
	double b;			// bコードの値
	char c_flg;			// cコードの時1
	double c;			// cコードの値
	char d_flg;			// dコードの時1
	double d;			// dコードの値
	char e_flg;			// eコードの時1
	double e;			// eコードの値
	char f_flg;			// fコードの時1
	double f;			// fコードの値
	char h_flg;			// hコードの時1
	double h;			// hコードの値
	char i_flg;			// iコードの時1
	double i;			// iコードの値
	char j_flg;			// jコードの時1
	double j;			// jコードの値
	char k_flg;			// kコードの時1
	double k;			// kコードの値
	char l_flg;			// lコードの時1
	double l;			// lコードの値
	char n_flg;			// nコードの時1
	double n;			// nコードの値
	char o_flg;			// oコードの時1
	double o;			// oコードの値
	char p_flg;			// pコードの時1
	double p;			// pコードの値
	char q_flg;			// qコードの時1
	double q;			// qコードの値
	char r_flg;			// rコードの時1
	double r;			// rコードの値
	char t_flg;			// tコードの時1
	double t;			// tコードの値
	char u_flg;			// uコードの時1
	double u;			// uコードの値
	char v_flg;			// vコードの時1
	double v;			// vコードの値
	char w_flg;			// wコードの時1
	double w;			// wコードの値
	char x_flg;			// xコードの時1
	double x;			// xコードの値
	char y_flg;			// yコードの時1
	double y;			// yコードの値
	char z_flg;			// zコードの時1
	double z;			// zコードの値
	// 「G」は1行に複数回記述される事があるので、4つまで格納できるようにする(G90G01など)
	// 行の先頭から現れた順に格納する
	char g1_flg;		// 1番目のgコードの時1
	double g1;			// 1番目のgコードの値
	char g2_flg;		// 2番目のgコードの時1
	double g2;			// 2番目のgコードの値
	char g3_flg;		// 3番目のgコードの時1
	double g3;			// 3番目のgコードの値
	char g4_flg;		// 4番目のgコードの時1
	double g4;			// 4番目のgコードの値
	//「M98」だけは特殊で、その後に続く文字列を取り出す
	char m98_flg;		// 「M98」の時1
	char m98[32];		// 「M98」に続く文字列
	//「M98」以外のMコードは値を格納する
	char m_flg;			// mコードの時1
	double m;			// mコードの値
	//「S1_」、「S2_」
	char s1_flg;		// 「S1_」コードの時1
	double s1;			// 「S1_」コードの値
	char s2_flg;		// 「S2_」コードの時1
	double s2;			// 「S2_」コードの値
};
