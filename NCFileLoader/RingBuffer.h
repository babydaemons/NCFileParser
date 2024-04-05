#pragma once
#include <mutex>

/// <summary>
/// リングバッファを実装するテンプレートクラスです。
/// </summary>
template<class T, int N>
class RingBuffer {
public:
	/// <summary>
	/// コンストラクタです。
	/// </summary>
	RingBuffer()
	{
		clear();
	}

	/// <summary>
	/// リングバッファのバッファ段数です。
	/// </summary>
	static const int SIZE = N;

	/// <summary>
	/// リングバッファの末尾に要素を追加します。
	/// </summary>
	/// <param name="data">追加する要素</param>
	/// <returns>追加成功時：true / バッファフル時：false</returns>
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
	/// リングバッファの先頭から要素を取得します。
	/// </summary>
	/// <param name="data">取得した要素</param>
	/// <returns>取得成功時：true / リングバッファが空のとき：false</returns>
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
	/// リングバッファに格納されている要素数を返します。
	/// </summary>
	/// <returns>リングバッファに格納されている要素数</returns>
	int count()
	{
		std::lock_guard<std::mutex> lock(mutex);
		return n;
	}

	/// <summary>
	/// リングバッファのバッファ段数を返します。
	/// </summary>
	/// <returns>リングバッファのバッファ段数</returns>
	int size() const
	{
		return SIZE;
	}

	/// <summary>
	/// リングバッファをクリアします。
	/// </summary>
	void clear()
	{
		head = 0;
		tail = 0;
		n = 0;
		::memset(array, 0, sizeof(array));
	}

private:
	/// <summary>排他制御に使うミューテックスです。</summary>
	std::mutex mutex;
	/// <summary>リングバッファ先頭のインデックスです。</summary>
	int head;
	/// <summary>リングバッファ末尾のインデックスです。</summary>
	int tail;
	/// <summary>リングバッファに格納している要素数です。</summary>
	int n;
	/// <summary>要素を格納する配列です。</summary>
	T array[N];
};
