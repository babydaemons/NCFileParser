#include "pch.h"
#include "NCFileParser.h"
#include "NCBlockDumper.h"

/// <summary>
/// Block�\���̂̍s�ԍ��ȊO���S�ă[���ł��邱�Ƃ��`�F�b�N����w���p�[�֐��ł��B
/// </summary>
/// <param name="line_num">�s�ԍ�</param>
/// <param name="block">Block�\���̂ւ̎Q��</param>
/// <returns>Block�\���̂̍s�ԍ��ȊO���S�ă[���ł���Ƃ�true</returns>
bool IsAllZero(INT64 line_num, const Block& block) {
	Block zero = { -line_num };
	return ::memcmp(&block, &zero, sizeof(block)) == 0;
}

/// <summary>
/// ��s���͂��������G���[�ɂȂ邱�ƁB
/// </summary>
TEST(NCFileParser_Once_NullTest, NGEmptyTest)
{
	NCFileParser parser;
	Block block;
	EXPECT_FALSE(parser.Parse(11111, "", block));
	EXPECT_TRUE(IsAllZero(11111, block));
}

/// <summary>
/// �󔒕����݂̂̓��͂��������G���[�ɂȂ邱�ƁB
/// </summary>
TEST(NCFileParser_Once_NullTest, NGSpaceTest)
{
	NCFileParser parser;
	Block block;
	EXPECT_FALSE(parser.Parse(11111, " \t", block));
	EXPECT_TRUE(IsAllZero(11111, block));
}

/// <summary>
/// �s���̃R�����g����������͂ł��邱�ƁBBlock�\���̂̃_���v���ʂ����������ƁB
/// </summary>
TEST(NCFileParser_Once_CommentTest, OKTest)
{
	NCFileParser parser;
	Block block;
	EXPECT_TRUE(parser.Parse(11111, "% comment", block));
	EXPECT_EQ(1, block.special_code);
	EXPECT_EQ(11111, block.line_num);

	char message[1024];
	EXPECT_STREQ("11111,comment\n", NCBlockDumper::Dump(block, message, sizeof(message)));
}

/// <summary>
/// �s�r���̃R�����g���������G���[�ɂȂ邱�ƁB
/// </summary>
TEST(NCFileParser_Once_CommentTest, NGTest)
{
	NCFileParser parser;
	Block block;
	EXPECT_FALSE(parser.Parse(11111, "A 123.456% comment", block));
	EXPECT_TRUE(IsAllZero(11111, block));
}

/// <summary>
/// �l�Ȃ�(�u�����N)��M98�R�[�h���������G���[�ɂȂ邱�ƁB
/// </summary>
TEST(NCFileParser_Once_M98Test, NGBlankTest)
{
	NCFileParser parser;
	Block block;
	EXPECT_FALSE(parser.Parse(11111, "M98", block));
	EXPECT_TRUE(IsAllZero(11111, block));
}

/// <summary>
/// 31�����ȓ��̍s����M98�R�[�h����������͂ł��邱�ƁBBlock�\���̂̃_���v���ʂ����������ƁB
/// </summary>
TEST(NCFileParser_Once_M98Test, OKTest)
{
	NCFileParser parser;
	Block block;
	EXPECT_TRUE(parser.Parse(11111, "M98aaaaabbbbbcccccdddddeeeeefffffg", block));
	EXPECT_EQ(1, block.m98_flg);
	EXPECT_STREQ("aaaaabbbbbcccccdddddeeeeefffffg", block.m98);
	EXPECT_EQ(11111, block.line_num);

	char message[1024];
	EXPECT_STREQ("11111,M98,aaaaabbbbbcccccdddddeeeeefffffg\n", NCBlockDumper::Dump(block, message, sizeof(message)));
}

/// <summary>
/// 32�����ȏ�̍s����M98�R�[�h���������G���[�ɂȂ邱�ƁB
/// </summary>
TEST(NCFileParser_Once_M98Test, NGTest)
{
	NCFileParser parser;
	Block block;
	EXPECT_FALSE(parser.Parse(11111, "M98aaaaabbbbbcccccdddddeeeeefffffgg", block));
	EXPECT_TRUE(IsAllZero(11111, block));
}

/// <summary>
/// �s����OR�R�[�h(�ŏ��l)����������͂ł��邱�ƁBBlock�\���̂̃_���v���ʂ����������ƁB
/// </summary>
TEST(NCFileParser_Once_ORTest, OK_MinTest)
{
	NCFileParser parser;
	Block block;
	EXPECT_TRUE(parser.Parse(11111, "OR0", block));
	EXPECT_EQ(1, block.or_flg);
	EXPECT_EQ(0, block.or_);
	EXPECT_EQ(11111, block.line_num);

	char message[1024];
	EXPECT_STREQ("11111,OR,0\n", NCBlockDumper::Dump(block, message, sizeof(message)));
}

/// <summary>
/// �s����OR�R�[�h(�ő�l)����������͂ł��邱�ƁBBlock�\���̂̃_���v���ʂ����������ƁB
/// </summary>
TEST(NCFileParser_Once_ORTest, OK_MaxTest)
{
	NCFileParser parser;
	Block block;
	EXPECT_TRUE(parser.Parse(11111, "OR100", block));
	EXPECT_EQ(1, block.or_flg);
	EXPECT_EQ(100, block.or_);
	EXPECT_EQ(11111, block.line_num);

	char message[1024];
	EXPECT_STREQ("11111,OR,100\n", NCBlockDumper::Dump(block, message, sizeof(message)));
}

/// <summary>
/// �s����OR�R�[�h(�ŏ��l����)���������G���[�ɂȂ邱�ƁB
/// </summary>
TEST(NCFileParser_Once_ORTest, NG_MinTest)
{
	NCFileParser parser;
	Block block;
	EXPECT_FALSE(parser.Parse(11111, "OR-1", block));
	EXPECT_TRUE(IsAllZero(11111, block));
}

/// <summary>
/// �s����OR�R�[�h(�ő�l����)���������G���[�ɂȂ邱�ƁB
/// </summary>
TEST(NCFileParser_Once_ORTest, NG_MaxTest)
{
	NCFileParser parser;
	Block block;
	EXPECT_FALSE(parser.Parse(11111, "OR101", block));
	EXPECT_TRUE(IsAllZero(11111, block));
}

/// <summary>
/// ��x�ڂ�OR�R�[�h���������G���[�ɂȂ邱�ƁB
/// </summary>
TEST(NCFileParser_Once_ORTest, NG_TwiceTest)
{
	NCFileParser parser;
	Block block;
	EXPECT_FALSE(parser.Parse(11111, "OR100OR0", block));
	EXPECT_TRUE(IsAllZero(11111, block));
}

/// <summary>
/// �l�Ȃ�(�u�����N)��OR�R�[�h���������G���[�ɂȂ邱�ƁB
/// </summary>
TEST(NCFileParser_Once_ORTest, NG_BlankTest)
{
	NCFileParser parser;
	Block block;
	EXPECT_FALSE(parser.Parse(11111, "OR", block));
	EXPECT_TRUE(IsAllZero(11111, block));
}

/// <summary>
/// �l�Ȃ�(�󔒕���)��OR�R�[�h���������G���[�ɂȂ邱�ƁB
/// </summary>
TEST(NCFileParser_Once_ORTest, NG_SpaceTest)
{
	NCFileParser parser;
	Block block;
	EXPECT_FALSE(parser.Parse(11111, "OR \t", block));
	EXPECT_TRUE(IsAllZero(11111, block));
}

/// <summary>
/// �s����f_Type�R�[�h(�ŏ��l)����������͂ł��邱�ƁBBlock�\���̂̃_���v���ʂ����������ƁB
/// </summary>
TEST(NCFileParser_Once_fTypeTest, OK_MinTest)
{
	NCFileParser parser;
	Block block;
	EXPECT_TRUE(parser.Parse(11111, "f_Type0", block));
	EXPECT_EQ(1, block.ftype_flg);
	EXPECT_EQ(0, block.ftype);
	EXPECT_EQ(11111, block.line_num);

	char message[1024];
	EXPECT_STREQ("11111,f_Type,0\n", NCBlockDumper::Dump(block, message, sizeof(message)));
}

/// <summary>
/// �s����f_Type�R�[�h(�ő�l)����������͂ł��邱�ƁBBlock�\���̂̃_���v���ʂ����������ƁB
/// </summary>
TEST(NCFileParser_Once_fTypeTest, OK_MaxTest)
{
	NCFileParser parser;
	Block block;
	EXPECT_TRUE(parser.Parse(11111, "f_Type1", block));
	EXPECT_EQ(1, block.ftype_flg);
	EXPECT_EQ(1, block.ftype);
	EXPECT_EQ(11111, block.line_num);

	char message[1024];
	EXPECT_STREQ("11111,f_Type,1\n", NCBlockDumper::Dump(block, message, sizeof(message)));
}

/// <summary>
/// �s����f_Type�R�[�h(�ŏ��l����)���������G���[�ɂȂ邱�ƁB
/// </summary>
TEST(NCFileParser_Once_fTypeTest, NG_MinTest)
{
	NCFileParser parser;
	Block block;
	EXPECT_FALSE(parser.Parse(11111, "f_Type-1", block));
	EXPECT_TRUE(IsAllZero(11111, block));
}

/// <summary>
/// �s����f_Type�R�[�h(�ő�l����)���������G���[�ɂȂ邱�ƁB
/// </summary>
TEST(NCFileParser_Once_fTypeTest, NG_MaxTest)
{
	NCFileParser parser;
	Block block;
	EXPECT_FALSE(parser.Parse(11111, "f_Type2", block));
	EXPECT_TRUE(IsAllZero(11111, block));
}

/// <summary>
/// ��x�ڂ�f_Type�R�[�h���������G���[�ɂȂ邱�ƁB
/// </summary>
TEST(NCFileParser_Once_fTypeTest, NG_TwiceTest)
{
	NCFileParser parser;
	Block block;
	EXPECT_FALSE(parser.Parse(11111, "f_Type0f_Type1", block));
	EXPECT_TRUE(IsAllZero(11111, block));
}

/// <summary>
/// �l�Ȃ�(�u�����N)��f_Type�R�[�h���������G���[�ɂȂ邱�ƁB
/// </summary>
TEST(NCFileParser_Once_fTypeTest, NG_BlankTest)
{
	NCFileParser parser;
	Block block;
	EXPECT_FALSE(parser.Parse(11111, "f_Type", block));
	EXPECT_TRUE(IsAllZero(11111, block));
}

/// <summary>
/// �l�Ȃ�(�󔒕���)��f_Type�R�[�h���������G���[�ɂȂ邱�ƁB
/// </summary>
TEST(NCFileParser_Once_fTypeTest, NG_SpaceTest)
{
	NCFileParser parser;
	Block block;
	EXPECT_FALSE(parser.Parse(11111, "f_Type \t", block));
	EXPECT_TRUE(IsAllZero(11111, block));
}

/// <summary>
/// 1�݂̂�G�R�[�h����������͂ł��邱�ƁBBlock�\���̂̃_���v���ʂ����������ƁB
/// </summary>
TEST(NCFileParser_Once_GTest, OK_Count1Test)
{
	NCFileParser parser;
	Block block;
	EXPECT_TRUE(parser.Parse(11111, "G12.345", block));
	EXPECT_EQ(1, block.g1_flg);
	EXPECT_DOUBLE_EQ(12.345, block.g1);
	EXPECT_EQ(11111, block.line_num);

	char message[1024];
	EXPECT_STREQ("11111,G1,12.345\n", NCBlockDumper::Dump(block, message, sizeof(message)));
}

/// <summary>
/// 2�݂̂�G�R�[�h����������͂ł��邱�ƁBBlock�\���̂̃_���v���ʂ����������ƁB
/// </summary>
TEST(NCFileParser_Once_GTest, OK_Count2Test)
{
	NCFileParser parser;
	Block block;
	EXPECT_TRUE(parser.Parse(11111, "G12.345G23.456", block));
	EXPECT_EQ(1, block.g1_flg);
	EXPECT_DOUBLE_EQ(12.345, block.g1);
	EXPECT_EQ(1, block.g2_flg);
	EXPECT_DOUBLE_EQ(23.456, block.g2);
	EXPECT_EQ(11111, block.line_num);

	char message[1024];
	EXPECT_STREQ("11111,G1,12.345,G2,23.456\n", NCBlockDumper::Dump(block, message, sizeof(message)));
}

/// <summary>
/// 3�݂̂�G�R�[�h����������͂ł��邱�ƁBBlock�\���̂̃_���v���ʂ����������ƁB
/// </summary>
TEST(NCFileParser_Once_GTest, OK_Count3Test)
{
	NCFileParser parser;
	Block block;
	EXPECT_TRUE(parser.Parse(11111, "G12.345G23.456G34.567", block));
	EXPECT_EQ(1, block.g1_flg);
	EXPECT_DOUBLE_EQ(12.345, block.g1);
	EXPECT_EQ(1, block.g2_flg);
	EXPECT_DOUBLE_EQ(23.456, block.g2);
	EXPECT_EQ(1, block.g3_flg);
	EXPECT_DOUBLE_EQ(34.567, block.g3);
	EXPECT_EQ(11111, block.line_num);

	char message[1024];
	EXPECT_STREQ("11111,G1,12.345,G2,23.456,G3,34.567\n", NCBlockDumper::Dump(block, message, sizeof(message)));
}

/// <summary>
/// 4�݂̂�G�R�[�h����������͂ł��邱�ƁBBlock�\���̂̃_���v���ʂ����������ƁB
/// </summary>
TEST(NCFileParser_Once_GTest, OK_Count4Test)
{
	NCFileParser parser;
	Block block;
	EXPECT_TRUE(parser.Parse(11111, "G12.345G23.456G34.567G45.678", block));
	EXPECT_EQ(1, block.g1_flg);
	EXPECT_DOUBLE_EQ(12.345, block.g1);
	EXPECT_EQ(1, block.g2_flg);
	EXPECT_DOUBLE_EQ(23.456, block.g2);
	EXPECT_EQ(1, block.g3_flg);
	EXPECT_DOUBLE_EQ(34.567, block.g3);
	EXPECT_EQ(1, block.g4_flg);
	EXPECT_DOUBLE_EQ(45.678, block.g4);
	EXPECT_EQ(11111, block.line_num);

	char message[1024];
	EXPECT_STREQ("11111,G1,12.345,G2,23.456,G3,34.567,G4,45.678\n", NCBlockDumper::Dump(block, message, sizeof(message)));
}

/// <summary>
/// 5�ڂ�G�R�[�h���������G���[�ɂȂ邱�ƁB
/// </summary>
TEST(NCFileParser_Once_GTest, NG_Count5Test)
{
	NCFileParser parser;
	Block block;
	EXPECT_FALSE(parser.Parse(11111, "G12.345G23.456G34.567G45.678G56.789", block));
	EXPECT_TRUE(IsAllZero(11111, block));
}

class NCFileParser_Many_Test : public ::testing::TestWithParam<const char*> {};

/// <summary>
/// 1�ڂ�A�R�[�h�`Z�R�[�h����������͂ł��邱�ƁBBlock�\���̂̃_���v���ʂ����������ƁB
/// </summary>
TEST_P(NCFileParser_Many_Test, OK_Count1Test)
{
	char record[1024] = "";
	::strcat_s(record, GetParam());
	::strcat_s(record, "123.456");
	NCFileParser parser;
	Block block;
	EXPECT_TRUE(parser.Parse(11111, record, block));

	char expect_message[1024] = "11111,";
	::strcat_s(expect_message, GetParam());
	::strcat_s(expect_message, ",123.456\n");

	char message[1024];
	EXPECT_STREQ(expect_message, NCBlockDumper::Dump(block, message, sizeof(message)));
}

/// <summary>
/// �p�f�B���O�t����1�ڂ�A�R�[�h�`Z�R�[�h����������͂ł��邱�ƁBBlock�\���̂̃_���v���ʂ����������ƁB
/// </summary>
TEST_P(NCFileParser_Many_Test, OK_Count1PaddingTest)
{
	char record[1024] = "";
	::strcat_s(record, GetParam());
	::strcat_s(record, " \t123.456");
	NCFileParser parser;
	Block block;
	EXPECT_TRUE(parser.Parse(11111, record, block));

	char expect_message[1024] = "11111,";
	::strcat_s(expect_message, GetParam());
	::strcat_s(expect_message, ",123.456\n");

	char message[1024];
	EXPECT_STREQ(expect_message, NCBlockDumper::Dump(block, message, sizeof(message)));
}

/// <summary>
/// �s���ȃp�f�B���O��1�ڂ�A�R�[�h�`Z�R�[�h���������G���[�ɂȂ邱�ƁB
/// </summary>
TEST_P(NCFileParser_Many_Test, NG_Count1PaddingTest)
{
	char record[1024] = "";
	::strcat_s(record, GetParam());
	::strcat_s(record, "_123.456");
	NCFileParser parser;
	Block block;
	EXPECT_FALSE(parser.Parse(11111, record, block));
	EXPECT_TRUE(IsAllZero(11111, block));
}

/// <summary>
/// �d������2�ڂ�A�R�[�h�`Z�R�[�h���������G���[�ɂȂ邱�ƁB
/// </summary>
TEST_P(NCFileParser_Many_Test, NG_Count2Test)
{
	char record[1024] = "";
	::strcat_s(record, GetParam());
	::strcat_s(record, "123.456");
	::strcat_s(record, GetParam());
	::strcat_s(record, "234.567");
	NCFileParser parser;
	Block block;
	EXPECT_FALSE(parser.Parse(11111, record, block));
	EXPECT_TRUE(IsAllZero(11111, block));
}

/// <summary>
/// �l�Ȃ�(�u�����N)��A�R�[�h�`Z�R�[�h���������G���[�ɂȂ邱�ƁB
/// </summary>
TEST_P(NCFileParser_Many_Test, NG_Count0BlankTest)
{
	NCFileParser parser;
	Block block;
	EXPECT_FALSE(parser.Parse(11111, GetParam(), block));
	EXPECT_TRUE(IsAllZero(11111, block));
}

/// <summary>
/// �l�Ȃ�(�󔒕���)��A�R�[�h�`Z�R�[�h���������G���[�ɂȂ邱�ƁB
/// </summary>
TEST_P(NCFileParser_Many_Test, NG_Count0SpaceTest)
{
	char record[1024] = "";
	::strcat_s(record, GetParam());
	::strcat_s(record, " \t");
	NCFileParser parser;
	Block block;
	EXPECT_FALSE(parser.Parse(11111, record, block));
	EXPECT_TRUE(IsAllZero(11111, block));
}

INSTANTIATE_TEST_CASE_P(AccelMotions, NCFileParser_Many_Test,
	::testing::Values(
		"A", "B", "C", "D", "E", "F", "H", "I", "J", "K", "L", "M", "N",
		"O", "P", "Q", "R", "S1_", "S2_", "T", "U", "V", "W", "X", "Y", "Z"
	)
);

/// <summary>
/// �d�����Ȃ�1�ڂ�A�R�[�h�`Z�R�[�h���S�ďo�����Ă���������͂ł��邱�ƁBBlock�\���̂̃_���v���ʂ����������ƁB
/// </summary>
TEST(NCFileParser_Many_TestAll, OK_Count1TestAll)
{
	static const char* keywords[] = {
		"A", "B", "C", "D", "E", "F", "H", "I", "J", "K", "L", "M", "N",
		"O", "P", "Q", "R", "S1_", "S2_", "T", "U", "V", "W", "X", "Y", "Z"
	};
	char record[1012] = "";
	char expected[1024] = "11111";
	char padding[1024] = "";
	for (int i = 0; i < _countof(keywords); ++i) {
		std::ostringstream ss;
		ss << 111.00 + (i + 1) * 0.01;
		::strcat_s(padding, " ");
		::strcat_s(record, keywords[i]);
		::strcat_s(record, padding);
		::strcat_s(record, ss.str().c_str());
		::strcat_s(expected, ",");
		::strcat_s(expected, keywords[i]);
		::strcat_s(expected, ",");
		::strcat_s(expected, ss.str().c_str());
	}
	::strcat_s(expected, "\n");

	NCFileParser parser;
	Block block;
	EXPECT_TRUE(parser.Parse(11111, record, block));

	char message[1024];
	EXPECT_STREQ(expected, NCBlockDumper::Dump(block, message, sizeof(message)));
}
