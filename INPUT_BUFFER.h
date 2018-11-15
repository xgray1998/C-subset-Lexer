#pragma once

#define INPUT_BUFFER_SIZE (1<<15) + 1 //���뻺������С

class INPUT_BUFFER
{
public:
	char buffer1[INPUT_BUFFER_SIZE];
	char buffer2[INPUT_BUFFER_SIZE];
	int begin = INPUT_BUFFER_SIZE - 1;//��ʼָ��
	int forward = INPUT_BUFFER_SIZE - 1;//��ǰָ��
	char* fileName = nullptr;
	char* outfileName = nullptr;
	bool isbuffer1 = false;
	bool isRetract = false;//�����˿�Խ����������������true,��һ�ο�Խʱ���ٶ�ȡ�ļ�

	INPUT_BUFFER();
	void retract(void);
	void dealEOF(void);//EOF����
	void get_char(char& ch);
};
