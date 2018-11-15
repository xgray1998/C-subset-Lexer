#pragma once

#define INPUT_BUFFER_SIZE (1<<15) + 1 //输入缓冲区大小

class INPUT_BUFFER
{
public:
	char buffer1[INPUT_BUFFER_SIZE];
	char buffer2[INPUT_BUFFER_SIZE];
	int begin = INPUT_BUFFER_SIZE - 1;//开始指针
	int forward = INPUT_BUFFER_SIZE - 1;//向前指针
	char* fileName = nullptr;
	char* outfileName = nullptr;
	bool isbuffer1 = false;
	bool isRetract = false;//若回退跨越两个缓冲区，则置true,下一次跨越时不再读取文件

	INPUT_BUFFER();
	void retract(void);
	void dealEOF(void);//EOF处理
	void get_char(char& ch);
};
