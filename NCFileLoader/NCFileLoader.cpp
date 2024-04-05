#include <windows.h>
#include <string.h>
#include "NCFileLoader.h"

#define INTERVAL std::chrono::microseconds(100)

/// <summary>
/// NC�t�@�C���̃��[�h���w�����܂��B�t�@�C�����I�[�v�����A���[�h�E�p�[�X�E�o�b�t�@�����O���s���X���b�h���N�����܂��B
/// </summary>
/// <param name="path">NC�t�@�C���̃p�X</param>
/// <returns>����I���F0 / �t�@�C���I�[�v���G���[�F-1</returns>
int NCFileLoader::LoadFile(const char* path)
{
	input_stream.open(path);
	if (input_stream.fail()) {
		return LOADFILE_OPEN_ERROR;
	}

	buffer_status = GETLINE_INVOKING_THREAD;
	std::thread thread(EntryBackgroundThread, this);
	loader_thread = std::move(thread);
	loader_thread.detach();

	return LOADFILE_SUCCESS;
}

/// <summary>
/// NC�t�@�C����1�s���̃f�[�^��Ԃ��܂��B
/// </summary>
/// <param name="block">Block�\���̕ϐ��ւ̎Q��</param>
/// <returns>�o�b�t�@����F1 / �t�@�C���̍Ō�ɓ��B�F2 / �t�@�C�����ǂݍ��܂�Ă��Ȃ��F3 / �Y���s�����@�G���[�F4 / �X���b�h�N�����F5 / ����I���F0</returns>
int NCFileLoader::GetLine(Block& block)
{
	if (buffer_status == GETLINE_NOT_READ_FILE) {
		return GETLINE_NOT_READ_FILE;
	}
	else if (buffer_status == GETLINE_INVOKING_THREAD) {
		return GETLINE_INVOKING_THREAD;
	}
	else if (ring_buffer.count() > 0 && ring_buffer.pop_front(block)) {
		if (block.line_num < 0) {
			block.line_num = -block.line_num;
			return GETLINE_PARSE_ERROR;
		}
		return GETLINE_SUCCESS;
	}
	else if (buffer_status == GETLINE_END_OF_FILE) {
		if (ring_buffer.count() == 0) {
			return GETLINE_END_OF_FILE;
		}
		else if (ring_buffer.pop_front(block)) {
			if (block.line_num < 0) {
				block.line_num = -block.line_num;
				return GETLINE_PARSE_ERROR;
			}
			return GETLINE_SUCCESS;
		}
		else {
			return GETLINE_END_OF_FILE;
		}
	}
	else {
		return GETLINE_EMPTY_BUFFER;
	}
}

/// <summary>
/// �t�@�C�����N���[�Y���A�����O�o�b�t�@�ƃo�b�t�@�X�e�[�^�X���ď��������܂��B
/// </summary>
void NCFileLoader::UnloadFile()
{
	input_stream.close();
	ring_buffer.clear();
	buffer_status = GETLINE_NOT_READ_FILE;
	line_num = 0;
}

/// <summary>
/// �o�b�N�O���E���h�X���b�h�̃G���g���[�|�C���g�ł��B
/// </summary>
/// <param name="self">NC�t�@�C�������[�h�E�p�[�X�E�o�b�t�@�����O����N���X�̃C���X�^���X�|�C���^</param>
void NCFileLoader::EntryBackgroundThread(NCFileLoader* self)
{
	self->ParseFile();
}

/// <summary>
/// NC�t�@�C�������[�h�E�p�[�X�E�o�b�t�@�����O����o�b�N�O���E���h�X���b�h�̎������ł��B
/// </summary>
void NCFileLoader::ParseFile()
{
	char record[4096];
	for (line_num = 1; input_stream.is_open() && input_stream.getline(record, sizeof(record) - 1); ++line_num) {
		Block block;
		if (!parser.Parse(line_num, record, block)) {
			// �p�[�X�G���[���̍ď�������NCFileParser#Parse()���\�b�h�Ŏ��{�ς�
			// memset(&block, 0, sizeof(block));
			// block.line_num = -line_num;
		}

		bool stored = false;
		do {
			const int NEAR_FULL = ring_buffer.size() * 3 / 4;
			if (ring_buffer.count() < NEAR_FULL) {
				stored = ring_buffer.push_back(block);
			}
			else {
				stored = false;
			}
			std::this_thread::sleep_for(INTERVAL);
		} while (!stored);
		buffer_status = GETLINE_SUCCESS;
	}

	buffer_status = GETLINE_END_OF_FILE;
}
