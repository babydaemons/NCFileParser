#pragma once
#include <thread>
#include <iostream>
#include <fstream>
#include "NCFileLoaderIF.h"
#include "NCFileParser.h"
#include "RingBuffer.h"

/// <summary>
/// NC�t�@�C�������[�h�E�p�[�X�E�o�b�t�@�����O����N���X�ł��B
/// </summary>
class NCFileLoader {
public:
	/// <summary>
	/// �R���X�g���N�^�ł��B
	/// </summary>
	NCFileLoader() : line_num(0), buffer_status(GETLINE_NOT_READ_FILE) { }

	/// <summary>
	/// NC�t�@�C���̃��[�h���w�����܂��B�t�@�C�����I�[�v�����A���[�h�E�p�[�X�E�o�b�t�@�����O���s���X���b�h���N�����܂��B
	/// </summary>
	/// <param name="path">NC�t�@�C���̃p�X</param>
	/// <returns>����I���F0 / �t�@�C���I�[�v���G���[�F-1</returns>
	int LoadFile(const char* path);

	/// <summary>
	/// NC�t�@�C����1�s���̃f�[�^��Ԃ��܂��B
	/// </summary>
	/// <param name="block">Block�\���̕ϐ��ւ̎Q��</param>
	/// <returns>�o�b�t�@����F1 / �t�@�C���̍Ō�ɓ��B�F2 / �t�@�C�����ǂݍ��܂�Ă��Ȃ��F3 / �Y���s�����@�G���[�F4 / ����I���F0</returns>
	int GetLine(Block& block);

	/// <summary>
	/// �t�@�C�����N���[�Y���A�����O�o�b�t�@�ƃo�b�t�@�X�e�[�^�X���ď��������܂��B
	/// </summary>
	void UnloadFile();

private:
	/// <summary>
	/// �o�b�N�O���E���h�X���b�h�̃G���g���[�|�C���g�ł��B
	/// </summary>
	/// <param name="self">NC�t�@�C�������[�h�E�p�[�X�E�o�b�t�@�����O����N���X�̃C���X�^���X�|�C���^</param>
	static void EntryBackgroundThread(NCFileLoader* self);

	/// <summary>
	/// NC�t�@�C�������[�h�E�p�[�X�E�o�b�t�@�����O����o�b�N�O���E���h�X���b�h�̎������ł��B
	/// </summary>
	void ParseFile();

private:
	/// <summary>���[�h�E�p�[�X�E�o�b�t�@�����O���s���o�b�N�O���E���h�X���b�h�̃C���X�^���X�ł��B</summary>
	std::thread loader_thread;
	/// <summary>NC�t�@�C���̓��̓X�g���[���ł��B</summary>
	std::ifstream input_stream;
	/// <summary>NC�t�@�C���̍s�ԍ��ł��B</summary>
	INT64 line_num;
	/// <summary>�����O�o�b�t�@�̃X�e�[�^�X�ł��B</summary>
	GETLINE_RESULT buffer_status;
	/// <summary>NC�t�@�C���̓��͍s����͂���N���X�̃C���X�^���X�ł��B</summary>
	NCFileParser parser;
	/// <summary>�����O�o�b�t�@�̃C���X�^���X�ł��B</summary>
	RingBuffer<Block, RING_BUFFER_COUNT> ring_buffer;
};