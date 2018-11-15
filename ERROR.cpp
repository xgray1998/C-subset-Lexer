#include<iostream>
#include<fstream>
#include"ERROR.h"

using namespace std;

void ERROR::operator()(int errorcode) {
	cout << "词法错误：";
	cout << "<" << lineIterator << "行," << wordIterator << "字符>处" << endl;
	switch (errorcode)
	{
	case L001:
		cout << "错误代码L001：\*注释未结尾";
		break;
	case L002:
		cout << "读入非法字符，无法识别";
		break;
	case L003:
		cout << "数字常量识别出错，小数点后必须有数字";
		break;
	case L004:
		cout << "数字常量识别出错，指数E后必须有数字";
		break;
	case L005:
		cout << "字符常量不能为空('')";
		break;
	case L006:
		cout << "不是有效的十六进制数转义字符";
		break;
	case L007:
		cout << "不是有效的转义字符";
		break;
	case R001://理论上不会出错
		cout << "未知错误，请上报开发人员，感谢您使用本程序";
		break;
	case R002:
		//错误代码未定义
		cout << "错误代码未定义，请上报开发人员，感谢您使用本程序";
		break;
	default:
		this->operator()(R002);
		break;
	}
	exit(0);
}