#pragma once
#include "Block.h"

/// <summary>
/// �p�[�X���ʂ�\���񋓒l�ł��B
/// </summary>
enum class ParseResult { None, Ok, Error = -1 };

/// <summary>
/// NC�t�@�C���̓��͍s����͂���N���X�ł��B
/// </summary>
class NCFileParser {
public:
	/// <summary>
	/// �R���X�g���N�^�ł��B
	/// </summary>
	NCFileParser() : phrase(nullptr), gcode_count(0) { }

	/// <summary>
	/// NC�t�@�C���̃p�[�X���s���܂��B
	/// </summary>
	/// <param name="line_num">NC�t�@�C���̓��͍s�ԍ�</param>
	/// <param name="record">NC�t�@�C���̓��͍s�f�[�^</param>
	/// <param name="block">Block�\���̂ւ̎Q��</param>
	/// <returns>����I�����Ftrue / ���@�G���[���Ffalse</returns>
	bool Parse(INT64 line_num, const char* record, Block& block);

private:
	/// <summary>
	/// 1�s��1��̂ݏo������R�[�h�̃p�[�X���s���܂��B
	/// </summary>
	/// <param name="record">NC�t�@�C���̓��͍s�f�[�^</param>
	/// <param name="block">Block�\���̂ւ̎Q��</param>
	/// <returns>ParseResult�񋓒l</returns>
	ParseResult ParseOnce(const char* record, Block& block);

	/// <summary>
	/// 1�s�ɕ�����o������R�[�h�̃p�[�X���s���܂��B
	/// </summary>
	/// <param name="block">Block�\���̂ւ̎Q��</param>
	/// <returns>ParseResult�񋓒l</returns>
	ParseResult ParseMany(Block& block);

	/// <summary>
	/// NC�t�@�C�����͍s�̒��̃R�[�h�̒l���擾���܂��B
	/// </summary>
	/// <param name="flag">Block�\���̂̃t���O�����o�[�ւ̎Q��</param>
	/// <param name="value">Block�\���̂̒l�����o�[�ւ̎Q��</param>
	/// <param name="offset">���͍s�̒��̒l������ւ̃I�t�Z�b�g</param>
	/// <returns>ParseResult�񋓒l</returns>
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
	/// NC�t�@�C�����͍s�̒��̃R�[�h�̒l���擾���܂��B
	/// </summary>
	/// <param name="min">�ŏ��l</param>
	/// <param name="max">�ő�l</param>
	/// <param name="flag">Block�\���̂̃t���O�����o�[�ւ̎Q��</param>
	/// <param name="value">Block�\���̂̒l�����o�[�ւ̎Q��</param>
	/// <param name="offset">���͍s�̒��̒l������ւ̃I�t�Z�b�g</param>
	/// <returns>ParseResult�񋓒l</returns>
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
	/// �擾���ʂ̒l�����������`�F�b�N���܂��B
	/// </summary>
	/// <param name="fetched">�擾���ʂ̒l</param>
	/// <param name="min">�ŏ��l</param>
	/// <param name="max">�ő�l</param>
	/// <returns>ParseResult�񋓒l</returns>
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
	/// <summary>Block�\���̂̒��̒l��������w���|�C���^</summary>
	const char* phrase;
	/// <summary>Block�\���̂̒��̉��Ԗڂ�G�R�[�h����ێ�����J�E���^</summary>
	int gcode_count;
};