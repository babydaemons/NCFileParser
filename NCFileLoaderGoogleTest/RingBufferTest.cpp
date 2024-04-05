#include "pch.h"
#include "RingBuffer.h"

/// <summary>
/// �R���X�g���N�^�Ő������v�f�����[������������邱�ƁB
/// </summary>
TEST(RingBuffer_Test, Count0Test)
{
    RingBuffer<int, 4> buffer;
    EXPECT_EQ(0, buffer.count());
    EXPECT_EQ(4, buffer.size());
}

/// <summary>
/// �v�f��1�i�[�E�擾�ł��邱�ƁB
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
/// �v�f�i�[�z��̋��E���z���āA�v�f��1�i�[�E�擾�ł��邱�ƁB
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
/// �i�[�������Ԃ̒ʂ�ɗv�f���擾�ł��邱�ƁB�o�b�t�@�̃t���ƃG���v�e�B�����������o�ł��邱�ƁB
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
