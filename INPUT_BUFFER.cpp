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
	//��ǰָ�����һ��
	if (forward != 0) {
		forward--;
	}
	else {
		//���˿�Խ������
		forward = INPUT_BUFFER_SIZE - 2;//ĩβ��EOF ��������һλ
		isbuffer1 = !isbuffer1;
		isRetract = true;
	}
}

void INPUT_BUFFER::dealEOF(void) {
	if (forward == INPUT_BUFFER_SIZE - 1) {//��ĩβ������Ҫ��Խ������
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
	//ȷ���ĸ�������
	char*buffer;
	if (isbuffer1)buffer = buffer1;
	else buffer = buffer2;

	//����EOF��Ҫô��Խ��������Ҫô����ǽ�β
	if (buffer[forward] == EOF) {
		dealEOF();
		if (isbuffer1)buffer = buffer1;
		else buffer = buffer2;

		//���ǽ�β
		if (forward != 0) {
			ch = '\n';//�������ļ�ĩβ������һ�����з��Խ������������ڵķ�����Ȼ��رճ���
			isEOF = true;
			return;
		}
	}
	ch = buffer[forward];

	//ERROR��ͳ�ƴ���
	if (ch == '\n') {
		lexerError.lineIterator++;
		lexerError.sumword += lexerError.wordIterator - 1;
		lexerError.wordIterator = 1;
	}
	else lexerError.wordIterator++;
	forward++;

	return;
}