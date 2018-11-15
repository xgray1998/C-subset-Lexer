#include"INPUT_BUFFER.h"
#include"lexer.h"
#include"ERROR.h"
#include<fstream>
#include<string>

INPUT_BUFFER buffer;
ERROR lexerError;
bool isEOF = false;

void printTOKEN(TOKEN* t);//测试代码

int main(int argc, char** argv)
{
	//命令行参数判断处理模式
	if (argc == 1) {
		buffer.fileName = argv[1];
		const char* temp = "test.txt";
		char ttemp[9];
		for (int i = 0; i < 8; i++)ttemp[i] = temp[i];
		ttemp[8] = 0;
		buffer.fileName = ttemp;
	}
	else if (argc == 2) {
		buffer.fileName = argv[1];
	}
	else if (argc == 3) {
		buffer.fileName = argv[1];
		buffer.outfileName = argv[2];
	}


	//测试代码：输出token到文件里
	TOKEN* token;
	for (; !isEOF;) {
		token = lexer_scan();
		if (token->tag != TAG_NULL) {
			lexerError.lexmeIterator++;
			printTOKEN(token);
		}
		delete token;
	}
	cout << "共有" << lexerError.lineIterator << "行" << endl;
	cout << "共有" << lexerError.sumword << "个字符" << endl;
	cout << "共有" << lexerError.lexmeIterator << "个词素" << endl;
	return 0;
}

//测试代码(输出到文件中）
void printTOKEN(TOKEN* t) {
	if (buffer.outfileName == nullptr) {
		char temp[12] = "outcome.txt";
		buffer.outfileName = temp;
	}
	static ofstream outTest(buffer.outfileName, ios::out);
	switch (t->tag)
	{
	case TAG_POINTER:
		outTest << "< -> >" << endl;
		break;
	case TAG_SELFADD:
		outTest << "< ++ >" << endl;
		break;
	case TAG_SELFSUB:
		outTest << "< -- >" << endl;
		break;
	case TAG_SIZEOF:
		outTest << "< sizeof >" << endl;
		break;
	case TAG_LEFTSHIFT:
		outTest << "< << >" << endl;
		break;
	case TAG_RIGHTSHIFT:
		outTest << "< >> >" << endl;
		break;
	case TAG_GE:
		outTest << "< >= >" << endl;
		break;
	case TAG_LE:
		outTest << "< <= >" << endl;
		break;
	case TAG_EQ:
		outTest << "< == >" << endl;
		break;
	case TAG_NEQ:
		outTest << "< != >" << endl;
		break;
	case TAG_AND:
		outTest << "< && >" << endl;
		break;
	case TAG_OR:
		outTest << "< || >" << endl;
		break;
	case TAG_DIV_ASSIGN:
		outTest << "< /= >" << endl;
		break;
	case TAG_MUL_ASSIGN:
		outTest << "< *= >" << endl;
		break;
	case TAG_MOD_ASSIGN:
		outTest << "< %= >" << endl;
		break;
	case TAG_ADD_ASSIGN:
		outTest << "< += >" << endl;
		break;
	case TAG_SUB_ASSIGN:
		outTest << "< -= >" << endl;
		break;
	case TAG_LEFTSHIFT_ASSIGN:
		outTest << "< <<= >" << endl;
		break;
	case TAG_RIGHTSHIFT_ASSIGN:
		outTest << "< >>= >" << endl;
		break;
	case TAG_BITAND_ASSIGN:
		outTest << "< &= >" << endl;
		break;
	case TAG_BITNOR_ASSIGN:
		outTest << "< ^= >" << endl;
		break;
	case TAG_BITOR_ASSIGN:
		outTest << "< |= >" << endl;
		break;
	case TAG_AUTO:
		outTest << "< auto >" << endl;
		break;
	case TAG_BREAK:
		outTest << "< break >" << endl;
		break;
	case TAG_CASE:
		outTest << "< case >" << endl;
		break;
	case TAG_CHAR:
		outTest << "< char >" << endl;
		break;
	case TAG_CONST:
		outTest << "< const >" << endl;
		break;
	case TAG_CONTINUE:
		outTest << "< continue >" << endl;
		break;
	case TAG_DEFAULT:
		outTest << "< default >" << endl;
		break;
	case TAG_DO:
		outTest << "< do >" << endl;
		break;
	case TAG_DOUBLE:
		outTest << "< double >" << endl;
		break;
	case TAG_ELSE:
		outTest << "< else >" << endl;
		break;
	case TAG_ENUM:
		outTest << "< enum >" << endl;
		break;
	case TAG_EXTERN:
		outTest << "< extern >" << endl;
		break;
	case TAG_FLOAT:
		outTest << "< float >" << endl;
		break;
	case TAG_FOR:
		outTest << "< for >" << endl;
		break;
	case TAG_GOTO:
		outTest << "< goto >" << endl;
		break;
	case TAG_IF:
		outTest << "< if >" << endl;
		break;
	case TAG_INT:
		outTest << "< int >" << endl;
		break;
	case TAG_LONG:
		outTest << "< long >" << endl;
		break;
	case TAG_REGISTER:
		outTest << "< register >" << endl;
		break;
	case TAG_RETURN:
		outTest << "< return >" << endl;
		break;
	case TAG_SHORT:
		outTest << "< short >" << endl;
		break;
	case TAG_SIGNED:
		outTest << "< signed >" << endl;
		break;
	case TAG_STATIC:
		outTest << "< static >" << endl;
		break;
	case TAG_STRUCT:
		outTest << "< struct >" << endl;
		break;
	case TAG_SWITCH:
		outTest << "< switch >" << endl;
		break;
	case TAG_TYPEDEF:
		outTest << "< typedef >" << endl;
		break;
	case TAG_UNION:
		outTest << "< union >" << endl;
		break;
	case TAG_UNSIGNED:
		outTest << "< unsigned >" << endl;
		break;
	case TAG_VOID:
		outTest << "< void >" << endl;
		break;
	case TAG_VOLATILE:
		outTest << "< volatile >" << endl;
		break;
	case TAG_WHILE:
		outTest << "< while >" << endl;
		break;
	case TAG_ID:
		outTest << "< id," << t->lexeme << " >" << endl;
		break;
	case TAG_INTEGER:
		outTest << "< num," << t->value_int << " >" << endl;
		break;
	case TAG_REAL:
		outTest << "< num," << t->value_float << " >" << endl;
		break;
	case TAG_STR:
		outTest << "< str," << t->lexeme << " >" << endl;
		break;
	case TAG_CH:
		outTest << "< ch," << (char)t->value_char << " >" << endl;
		break;
	default:
		outTest << "< " << (char)t->tag << " >" << endl;
		break;
	}
}