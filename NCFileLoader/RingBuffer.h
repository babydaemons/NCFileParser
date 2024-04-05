#pragma once
#include <mutex>

/// <summary>
/// �����O�o�b�t�@����������e���v���[�g�N���X�ł��B
/// </summary>
template<class T, int N>
class RingBuffer {
public:
	/// <summary>
	/// �R���X�g���N�^�ł��B
	/// </summary>
	RingBuffer()
	{
		clear();
	}

	/// <summary>
	/// �����O�o�b�t�@�̃o�b�t�@�i���ł��B
	/// </summary>
	static const int SIZE = N;

	/// <summary>
	/// �����O�o�b�t�@�̖����ɗv�f��ǉ����܂��B
	/// </summary>
	/// <param name="data">�ǉ�����v�f</param>
	/// <returns>�ǉ��������Ftrue / �o�b�t�@�t�����Ffalse</returns>
	bool push_back(const T& data)
	{
		std::lock_guard<std::mutex> lock(mutex);

		if (n == N) {
			return false;	// full
		}
		array[tail] = data;
		tail = (tail + 1) % SIZE;
		++n;
		return true;
	}

	/// <summary>
	/// �����O�o�b�t�@�̐擪����v�f���擾���܂��B
	/// </summary>
	/// <param name="data">�擾�����v�f</param>
	/// <returns>�擾�������Ftrue / �����O�o�b�t�@����̂Ƃ��Ffalse</returns>
	bool pop_front(T& data)
	{
		std::lock_guard<std::mutex> lock(mutex);

		if (n == 0) {
			return false;	// empty
		}
		data = array[head];
		head = (head + 1) % SIZE;
		--n;
		return true;
	}

	/// <summary>
	/// �����O�o�b�t�@�Ɋi�[����Ă���v�f����Ԃ��܂��B
	/// </summary>
	/// <returns>�����O�o�b�t�@�Ɋi�[����Ă���v�f��</returns>
	int count()
	{
		std::lock_guard<std::mutex> lock(mutex);
		return n;
	}

	/// <summary>
	/// �����O�o�b�t�@�̃o�b�t�@�i����Ԃ��܂��B
	/// </summary>
	/// <returns>�����O�o�b�t�@�̃o�b�t�@�i��</returns>
	int size() const
	{
		return SIZE;
	}

	/// <summary>
	/// �����O�o�b�t�@���N���A���܂��B
	/// </summary>
	void clear()
	{
		head = 0;
		tail = 0;
		n = 0;
		::memset(array, 0, sizeof(array));
	}

private:
	/// <summary>�r������Ɏg���~���[�e�b�N�X�ł��B</summary>
	std::mutex mutex;
	/// <summary>�����O�o�b�t�@�擪�̃C���f�b�N�X�ł��B</summary>
	int head;
	/// <summary>�����O�o�b�t�@�����̃C���f�b�N�X�ł��B</summary>
	int tail;
	/// <summary>�����O�o�b�t�@�Ɋi�[���Ă���v�f���ł��B</summary>
	int n;
	/// <summary>�v�f���i�[����z��ł��B</summary>
	T array[N];
};
