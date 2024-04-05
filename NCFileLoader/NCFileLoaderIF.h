#pragma once
#include "Block.h"

/// <summary>
/// LoadFile�֐��̖߂�l��\���񋓒l�ł��B
/// </summary>
enum LOADFILE_RESULT {
	LOADFILE_SUCCESS = 0,		// ����I��
	LOADFILE_OPEN_ERROR	= -1,	// �t�@�C���I�[�v���G���[
};

/// <summary>
/// NC�t�@�C���̃��[�h���w�����܂��B�t�@�C�����I�[�v�����A���[�h�E�p�[�X�E�o�b�t�@�����O���s���X���b�h���N�����܂��B
/// </summary>
/// <param name="path">NC�t�@�C���̃p�X</param>
/// <returns>����I���F0 / �t�@�C���I�[�v���G���[�F-1</returns>
extern int LoadFile(const char* path);

/// <summary>
/// GetLine�֐��̖߂�l��\���񋓒l�ł��B
/// </summary>
enum GETLINE_RESULT {
	GETLINE_SUCCESS = 0,			// ����I���F0
	GETLINE_EMPTY_BUFFER = 1,		// �o�b�t�@����F1
	GETLINE_END_OF_FILE = 2,		// �t�@�C���̍Ō�ɓ��B�F2
	GETLINE_NOT_READ_FILE = 3,		// �t�@�C�����ǂݍ��܂�Ă��Ȃ��F3
	GETLINE_PARSE_ERROR = 4,		// �Y���s�����@�G���[�F4
	GETLINE_INVOKING_THREAD = 5,	// �X���b�h�N�����F5
};

/// <summary>
/// NC�t�@�C����1�s���̃f�[�^��Ԃ��܂��B
/// </summary>
/// <param name="block">Block�\���̕ϐ��ւ̃|�C���^</param>
/// <returns>�o�b�t�@����F1 / �t�@�C���̍Ō�ɓ��B�F2 / �t�@�C�����ǂݍ��܂�Ă��Ȃ��F3 / �Y���s�����@�G���[�F4 / ����I���F0</returns>
extern int GetLine(Block* block);

/// <summary>
/// �t�@�C�����N���[�Y���A�����O�o�b�t�@�ƃo�b�t�@�X�e�[�^�X���ď��������܂��B
/// </summary>
extern void UnloadFile();

/// <summary>
/// Block�\���̂̃f�o�b�O�o�͗p��������\�z���܂��B
/// </summary>
/// <param name="block">Block�\���̂ւ̎Q��</param>
/// <param name="message">�f�o�b�O�o�͗p�������Ԃ��o�b�t�@</param>
/// <param name="size">�o�b�t�@�T�C�Y</param>
/// <returns>�f�o�b�O�o�͗p�������Ԃ��o�b�t�@</returns>
extern const char* BlockDump(const Block* block, char* message, int size);
