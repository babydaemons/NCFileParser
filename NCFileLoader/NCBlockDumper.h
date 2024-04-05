#pragma once
#include <sstream>
#include "Block.h"

/// <summary>
/// NC�t�@�C���̓��͍s����͂���N���X�ł��B
/// </summary>
class NCBlockDumper {
public:
	/// <summary>
	/// Block�\���̂̃f�o�b�O�o�͗p��������\�z���܂��B
	/// </summary>
	/// <param name="block">Block�\���̂ւ̎Q��</param>
	/// <param name="message">�f�o�b�O�o�͗p�������Ԃ��o�b�t�@</param>
	/// <param name="size">�o�b�t�@�T�C�Y</param>
	/// <returns>�f�o�b�O�o�͗p�������Ԃ��o�b�t�@</returns>
	static const char* Dump(const Block& block, char* message, int size);

private:
	/// <summary>
	/// Block�\���̂̒��̒l�̃f�o�b�O�o�͗p��������o�͕�����X�g���[���֏����o���܂��B
	/// </summary>
	/// <param name="label">Block�\���̂̒��̒l�����ʂ��郉�x��������</param>
	/// <param name="flag">Block�\���̂̃t���O�����o�[</param>
	/// <param name="value">Block�\���̂̒l�����o�[</param>
	/// <param name="ss">�o�͕�����X�g���[��</param>
	static void Dump(const char* label, char flag, double value, std::ostringstream& ss) {
		if (flag == 1) {
			ss << ',' << label << ',' << value;
		}
	}
};