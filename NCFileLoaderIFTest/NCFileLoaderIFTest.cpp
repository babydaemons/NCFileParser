#include <stdlib.h>
#include <thread>
#include <iostream>
#include "NCFileLoaderIF.h"

void DoTest(const char* path, int min_interval, int max_interval)
{
	int load_result = LoadFile(path);
	if (load_result != 0) {
		::perror(path);
		return;
	}

	int get_result = GETLINE_NOT_READ_FILE;
	while (get_result != GETLINE_END_OF_FILE) {
		Block block;
#ifdef _DEBUG
		char message[1024];
#endif
		get_result = GetLine(&block);
		switch (get_result) {
		case GETLINE_INVOKING_THREAD:
			std::cout << "GETLINE_INVOKING_THREAD" << std::endl;
			break;
		case GETLINE_NOT_READ_FILE:
			std::cout << "GETLINE_NOT_READ_FILE" << std::endl;
			break;
		case GETLINE_EMPTY_BUFFER:
			std::cout << "GETLINE_EMPTY_BUFFER" << std::endl;
			break;
		case GETLINE_SUCCESS:
#ifdef _DEBUG
			BlockDump(&block, message, sizeof(message));
			std::cout << message;
#endif
			break;
		case GETLINE_PARSE_ERROR:
			std::cout << block.line_num << ",ERROR" << std::endl;
			break;
		case GETLINE_END_OF_FILE:
			UnloadFile();
			break;
		}
		int interval = min_interval + (max_interval - min_interval) * rand() / RAND_MAX;
		std::this_thread::sleep_for(std::chrono::microseconds(interval));
	}
}

int main()
{
	DoTest("NCFileLoaderIFTestXXX.txt", 80, 160);
	DoTest("NCFileLoaderIFTest.txt", 80, 160);
	DoTest("NCFileLoaderIFTest2.txt", 800, 1600);
	return 0;
}