/// <summary>
/// NC�t�@�C��1�s���f�[�^��\������\���̂��`����w�b�_�t�@�C��
/// </summary>
#pragma once

/// <summary>
/// �����O�o�b�t�@�̒i�����`����萔�l
/// </summary>
#define RING_BUFFER_COUNT	1000

typedef __int64 INT64;

/// <summary>
/// NC�t�@�C��1�s���f�[�^��\������\����
/// </summary>
struct Block
{
	INT64 line_num;
	char special_code;	// %�Ŏn�܂�R�����g�s�F1�A���̑��F0
	char ftype_flg;		// f_Type�R�[�h�̎�1
	char ftype;			// f_Type�R�[�h�̐��l0 or 1
	char or_flg;		// OR�R�[�h�̎�1
	char or_;			// OR�R�[�h�̐��l0~100
	char a_flg;			// a�R�[�h�̎�1
	double a;			// a�R�[�h�̒l
	char b_flg;			// b�R�[�h�̎�1
	double b;			// b�R�[�h�̒l
	char c_flg;			// c�R�[�h�̎�1
	double c;			// c�R�[�h�̒l
	char d_flg;			// d�R�[�h�̎�1
	double d;			// d�R�[�h�̒l
	char e_flg;			// e�R�[�h�̎�1
	double e;			// e�R�[�h�̒l
	char f_flg;			// f�R�[�h�̎�1
	double f;			// f�R�[�h�̒l
	char h_flg;			// h�R�[�h�̎�1
	double h;			// h�R�[�h�̒l
	char i_flg;			// i�R�[�h�̎�1
	double i;			// i�R�[�h�̒l
	char j_flg;			// j�R�[�h�̎�1
	double j;			// j�R�[�h�̒l
	char k_flg;			// k�R�[�h�̎�1
	double k;			// k�R�[�h�̒l
	char l_flg;			// l�R�[�h�̎�1
	double l;			// l�R�[�h�̒l
	char n_flg;			// n�R�[�h�̎�1
	double n;			// n�R�[�h�̒l
	char o_flg;			// o�R�[�h�̎�1
	double o;			// o�R�[�h�̒l
	char p_flg;			// p�R�[�h�̎�1
	double p;			// p�R�[�h�̒l
	char q_flg;			// q�R�[�h�̎�1
	double q;			// q�R�[�h�̒l
	char r_flg;			// r�R�[�h�̎�1
	double r;			// r�R�[�h�̒l
	char t_flg;			// t�R�[�h�̎�1
	double t;			// t�R�[�h�̒l
	char u_flg;			// u�R�[�h�̎�1
	double u;			// u�R�[�h�̒l
	char v_flg;			// v�R�[�h�̎�1
	double v;			// v�R�[�h�̒l
	char w_flg;			// w�R�[�h�̎�1
	double w;			// w�R�[�h�̒l
	char x_flg;			// x�R�[�h�̎�1
	double x;			// x�R�[�h�̒l
	char y_flg;			// y�R�[�h�̎�1
	double y;			// y�R�[�h�̒l
	char z_flg;			// z�R�[�h�̎�1
	double z;			// z�R�[�h�̒l
	// �uG�v��1�s�ɕ�����L�q����鎖������̂ŁA4�܂Ŋi�[�ł���悤�ɂ���(G90G01�Ȃ�)
	// �s�̐擪���猻�ꂽ���Ɋi�[����
	char g1_flg;		// 1�Ԗڂ�g�R�[�h�̎�1
	double g1;			// 1�Ԗڂ�g�R�[�h�̒l
	char g2_flg;		// 2�Ԗڂ�g�R�[�h�̎�1
	double g2;			// 2�Ԗڂ�g�R�[�h�̒l
	char g3_flg;		// 3�Ԗڂ�g�R�[�h�̎�1
	double g3;			// 3�Ԗڂ�g�R�[�h�̒l
	char g4_flg;		// 4�Ԗڂ�g�R�[�h�̎�1
	double g4;			// 4�Ԗڂ�g�R�[�h�̒l
	//�uM98�v�����͓���ŁA���̌�ɑ�������������o��
	char m98_flg;		// �uM98�v�̎�1
	char m98[32];		// �uM98�v�ɑ���������
	//�uM98�v�ȊO��M�R�[�h�͒l���i�[����
	char m_flg;			// m�R�[�h�̎�1
	double m;			// m�R�[�h�̒l
	//�uS1_�v�A�uS2_�v
	char s1_flg;		// �uS1_�v�R�[�h�̎�1
	double s1;			// �uS1_�v�R�[�h�̒l
	char s2_flg;		// �uS2_�v�R�[�h�̎�1
	double s2;			// �uS2_�v�R�[�h�̒l
};
