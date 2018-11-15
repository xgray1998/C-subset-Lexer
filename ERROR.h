#pragma once

#define L001 1
#define L002 2
#define L003 3
#define L004 4
#define L005 5
#define L006 6
#define L007 7
#define R001 1001
#define R002 1002


class ERROR
{
public:
	int lineIterator = 1;
	int wordIterator = 1;
	int sumword = 0;
	int lexmeIterator = 0;//单词个数(标点和空格不计数)
	void operator()(int errorcode);
};