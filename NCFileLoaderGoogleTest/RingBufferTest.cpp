#include "pch.h"
#include "RingBuffer.h"

/// <summary>
/// コンストラクタで正しく要素数がゼロ初期化されること。
/// </summary>
TEST(RingBuffer_Test, Count0Test)
{
    RingBuffer<int, 4> buffer;
    EXPECT_EQ(0, buffer.count());
    EXPECT_EQ(4, buffer.size());
}

/// <summary>
/// 要素を1個格納・取得できること。
/// </summary>
TEST(RingBuffer_Test, Count1Test)
{
    RingBuffer<int, 4> buffer;
    EXPECT_EQ(true, buffer.push_back(1111));
    EXPECT_EQ(1, buffer.count());
    int fetched_value = -1;
    EXPECT_EQ(true, buffer.pop_front(fetched_value));
    EXPECT_EQ(1111, fetched_value);
    EXPECT_EQ(0, buffer.count());
}

/// <summary>
/// 要素格納配列の境界を越えて、要素を1個格納・取得できること。
/// </summary>
TEST(RingBuffer_Test, Count1To9Test)
{
    RingBuffer<int, 4> buffer;
    for (int i = 1; i < 9; ++i) {
        EXPECT_EQ(true, buffer.push_back(i * 1111));
        EXPECT_EQ(1, buffer.count());
        int fetched_value = -1;
        EXPECT_EQ(true, buffer.pop_front(fetched_value));
        EXPECT_EQ(i * 1111, fetched_value);
        EXPECT_EQ(0, buffer.count());
    }
}

/// <summary>
/// 格納した順番の通りに要素が取得できること。バッファのフルとエンプティが正しく検出できること。
/// </summary>
TEST(RingBuffer_Test, FullEmptyTest)
{
    RingBuffer<int, 4> buffer;
    EXPECT_EQ(true, buffer.push_back(1111));
    EXPECT_EQ(1, buffer.count());
    EXPECT_EQ(true, buffer.push_back(2222));
    EXPECT_EQ(2, buffer.count());
    EXPECT_EQ(true, buffer.push_back(3333));
    EXPECT_EQ(3, buffer.count());
    EXPECT_EQ(true, buffer.push_back(4444));
    EXPECT_EQ(4, buffer.count());
    EXPECT_EQ(false, buffer.push_back(5555));
    EXPECT_EQ(4, buffer.count());
    int fetched_value = -1;
    EXPECT_EQ(true, buffer.pop_front(fetched_value));
    EXPECT_EQ(1111, fetched_value);
    EXPECT_EQ(3, buffer.count());
    EXPECT_EQ(true, buffer.pop_front(fetched_value));
    EXPECT_EQ(2222, fetched_value);
    EXPECT_EQ(2, buffer.count());
    EXPECT_EQ(true, buffer.pop_front(fetched_value));
    EXPECT_EQ(3333, fetched_value);
    EXPECT_EQ(1, buffer.count());
    EXPECT_EQ(true, buffer.pop_front(fetched_value));
    EXPECT_EQ(4444, fetched_value);
    EXPECT_EQ(0, buffer.count());
    EXPECT_EQ(false, buffer.pop_front(fetched_value));
    EXPECT_EQ(0, buffer.count());
}
