#include "pch.h"
#include "NCFileLoader.h"

#define DATAFILE "NCFileLoaderGoogleTest.txt"
#define RECORD_OK "A 123.456"
#define RECORD_NG "ABC 123.456"
#define RECORD_OK2 "A 111.111\t\n B\t222.222\nC333.333\nD444.444\nE555.555"

const char* CreateDataFile(const char* record, char* path, int size)
{
    if (::getcwd(path, size) != nullptr) {
        ::strcat_s(path, size, "\\");
        ::strcat_s(path, size, DATAFILE);

        std::ofstream stream(path);
        stream << record << std::endl;
        stream.close();
    }
    return path;
}

/// <summary>
/// 存在しないファイルを指定すると正しくLOADFILE_OPEN_ERRORを返すこと。
/// </summary>
TEST(NCFileLoader_LoadFileTest, OpenErrorTest)
{
    NCFileLoader loader;
    EXPECT_EQ(LOADFILE_OPEN_ERROR, loader.LoadFile("NOT_FOUND.txt"));
}

/// <summary>
/// 存在するファイルを指定すると正しくLOADFILE_SUCCESSを返すこと。
/// </summary>
TEST(NCFileLoader_LoadFileTest, SuccessTest)
{
    static NCFileLoader loader;
    char path[1024] = "";
    EXPECT_EQ(LOADFILE_SUCCESS, loader.LoadFile(CreateDataFile(RECORD_OK, path, sizeof(path))));
    loader.UnloadFile();
}

/// <summary>
/// コンストラクタで正しくバッファステータスがGETLINE_NOT_READ_FILEで初期化されること。
/// </summary>
TEST(NCFileLoader_GetLineTest, NotReadFileTest)
{
    NCFileLoader loader;
    Block block;
    EXPECT_EQ(GETLINE_NOT_READ_FILE, loader.GetLine(block));
}

/// <summary>
/// NCファイルのレコード読み取りが成功すると正しくGETLINE_SUCCESSを返すこと。
/// </summary>
TEST(NCFileLoader_GetLineTest, SuccessTest)
{
    static NCFileLoader loader;
    char path[1024] = "";
    EXPECT_EQ(LOADFILE_SUCCESS, loader.LoadFile(CreateDataFile(RECORD_OK, path, sizeof(path))));
    ::std::this_thread::sleep_for(std::chrono::seconds(1));
    Block block;
    EXPECT_EQ(GETLINE_SUCCESS, loader.GetLine(block));
    loader.UnloadFile();
}

/// <summary>
/// バックグランドスレッド起動待ちのとき正しくGETLINE_INVOKING_THREADを返すこと。
/// </summary>
TEST(NCFileLoader_GetLineTest, InvokingThreadTest)
{
    static NCFileLoader loader;
    char path[1024] = "";
    EXPECT_EQ(LOADFILE_SUCCESS, loader.LoadFile(CreateDataFile(RECORD_OK, path, sizeof(path))));
    Block block;
    EXPECT_EQ(GETLINE_INVOKING_THREAD, loader.GetLine(block));
    loader.UnloadFile();
}

/// <summary>
/// NCファイルのレコードが文法エラーのとき正しくGETLINE_PARSE_ERRORを返すこと。
/// </summary>
TEST(NCFileLoader_GetLineTest, ParseErrorTest)
{
    static NCFileLoader loader;
    char path[1024] = "";
    EXPECT_EQ(LOADFILE_SUCCESS, loader.LoadFile(CreateDataFile(RECORD_NG, path, sizeof(path))));
    ::std::this_thread::sleep_for(std::chrono::seconds(1));
    Block block;
    EXPECT_EQ(GETLINE_PARSE_ERROR, loader.GetLine(block));
    loader.UnloadFile();
}

/// <summary>
/// NCファイルのレコード読み取りがリングバッファ終端に達すると正しくGETLINE_EMPTY_BUFFERを返すこと。
/// </summary>
TEST(NCFileLoader_GetLineTest, EmptyBufferTest)
{
    static NCFileLoader loader;
    char path[1024] = "";
    EXPECT_EQ(LOADFILE_SUCCESS, loader.LoadFile(CreateDataFile(RECORD_OK2, path, sizeof(path))));
    Block block;
    while (loader.GetLine(block) != GETLINE_SUCCESS) { /* busy loop */; }
    EXPECT_EQ(GETLINE_EMPTY_BUFFER, loader.GetLine(block));
    loader.UnloadFile();
}

/// <summary>
/// NCファイルのレコード読み取りがファイル終端に達すると正しくGETLINE_END_OF_FILEを返すこと。
/// </summary>
TEST(NCFileLoader_GetLineTest, EndOfFileTest)
{
    static NCFileLoader loader;
    char path[1024] = "";
    EXPECT_EQ(LOADFILE_SUCCESS, loader.LoadFile(CreateDataFile(RECORD_OK, path, sizeof(path))));
    ::std::this_thread::sleep_for(std::chrono::seconds(1));
    Block block;
    EXPECT_EQ(GETLINE_SUCCESS, loader.GetLine(block));
    EXPECT_EQ(GETLINE_END_OF_FILE, loader.GetLine(block));
    loader.UnloadFile();
}
