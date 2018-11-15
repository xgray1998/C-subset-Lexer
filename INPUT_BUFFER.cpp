#include"INPUT_BUFFER.h"
#include"ERROR.h"
#include<iostream>
#include<fstream>

using namespace std;

fstream file;
extern bool isEOF;
extern ERROR lexerError;


INPUT_BUFFER::INPUT_BUFFER() {
	buffer1[INPUT_BUFFER_SIZE - 1] = EOF;
	buffer2[INPUT_BUFFER_SIZE - 1] = EOF;
}

void INPUT_BUFFER::retract(void) {
	//向前指针回退一个
	if (forward != 0) {
		forward--;
	}
	else {
		//回退跨越缓冲区
		forward = INPUT_BUFFER_SIZE - 2;//末尾是EOF 故再左移一位
		isbuffer1 = !isbuffer1;
		isRetract = true;
	}
}

void INPUT_BUFFER::dealEOF(void) {
	if (forward == INPUT_BUFFER_SIZE - 1) {//在末尾，即需要跨越缓冲区
		char* buffer;
		forward = 0;
		if (!file.is_open())file.open(fileName, ios::in);
		isbuffer1 = !isbuffer1;
		if (!isRetract) {
			if (isbuffer1)buffer = buffer1;
			else buffer = buffer2;
			file.read(buffer, INPUT_BUFFER_SIZE - 1);
			if (file.gcount() != INPUT_BUFFER_SIZE - 1) {
				buffer[file.gcount()] = EOF;
			}
		}
		isRetract = false;
	}
}

void INPUT_BUFFER::get_char(char& ch) {
	//确定哪个缓冲区
	char*buffer;
	if (isbuffer1)buffer = buffer1;
	else buffer = buffer2;

	//读到EOF，要么跨越缓冲区，要么真的是结尾
	if (buffer[forward] == EOF) {
		dealEOF();
		if (isbuffer1)buffer = buffer1;
		else buffer = buffer2;

		//真是结尾
		if (forward != 0) {
			ch = '\n';//若读到文件末尾，传回一个换行符以结束分析器现在的分析，然后关闭程序
			isEOF = true;
			return;
		}
	}
	ch = buffer[forward];

	//ERROR的统计处理
	if (ch == '\n') {
		lexerError.lineIterator++;
		lexerError.sumword += lexerError.wordIterator - 1;
		lexerError.wordIterator = 1;
	}
	else lexerError.wordIterator++;
	forward++;

	return;
}