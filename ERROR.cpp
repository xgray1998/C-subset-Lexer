#include<iostream>
#include<fstream>
#include"ERROR.h"

using namespace std;

void ERROR::operator()(int errorcode) {
	cout << "�ʷ�����";
	cout << "<" << lineIterator << "��," << wordIterator << "�ַ�>��" << endl;
	switch (errorcode)
	{
	case L001:
		cout << "�������L001��\*ע��δ��β";
		break;
	case L002:
		cout << "����Ƿ��ַ����޷�ʶ��";
		break;
	case L003:
		cout << "���ֳ���ʶ�����С��������������";
		break;
	case L004:
		cout << "���ֳ���ʶ�����ָ��E�����������";
		break;
	case L005:
		cout << "�ַ���������Ϊ��('')";
		break;
	case L006:
		cout << "������Ч��ʮ��������ת���ַ�";
		break;
	case L007:
		cout << "������Ч��ת���ַ�";
		break;
	case R001://�����ϲ������
		cout << "δ֪�������ϱ�������Ա����л��ʹ�ñ�����";
		break;
	case R002:
		//�������δ����
		cout << "�������δ���壬���ϱ�������Ա����л��ʹ�ñ�����";
		break;
	default:
		this->operator()(R002);
		break;
	}
	exit(0);
}