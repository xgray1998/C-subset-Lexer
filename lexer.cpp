#include"lexer.h"
#include"INPUT_BUFFER.h"
#include<cmath>
#include"ERROR.h"

extern INPUT_BUFFER buffer;
extern bool isEOF;
extern ERROR lexerError;

TOKEN* lexer_scan(void) {
	int state = 0;
	TOKEN* token = nullptr;

	string idname = "";
	long long int num = 0;//识别NUM时整数部分
	int charnum = 0;//识别CH时使用
	int powerE = 0;//识别NUM时E后面的数字部分
	double fnum = 0.0;//识别NUM时小数部分
	int afterDot = 0;//当前识别的字符是小数点后多少位
	int powerEsign = 0;//powerE的符号

	while (1) {
		if (isEOF) {
			if (state == 0)return new TOKEN(TAG_NULL);
			else lexerError(L001);////*未结尾
		}

		char ch;
		buffer.get_char(ch);
		switch (state)
		{
		//state=1-14识别空白符、分界符、运算符、注释
		case 0:
			if (ch == ' ' || ch == '\n' || ch == '\t')state = 0;
			else if (ch == '[' || ch == ']' || ch == '(' || ch == ')' ||
				ch == '.' || ch == '~' || ch == '?' || ch == ':' ||
				ch == ',' || ch == ';' || ch == '}' || ch == '{') {
				token = new TOKEN(ch);
				return token;
			}
			else if (ch >= 'a'&&ch <= 'z' || ch >= 'A'&&ch <= 'Z' || ch == '_') {
				idname = "";
				idname += ch;
				state = 38;
			}
			else if (ch >= '0'&&ch <= '9') {
				num = 0;
				num += ch - '0';
				state = 18;
			}
			else switch (ch)
			{
			case '-':
				state = 1;
				break;
			case '+':
				state = 2;
				break;
			case '&':
				state = 3;
				break;
			case '|':
				state = 4;
				break;
			case '>':
				state = 5;
				break;
			case '<':
				state = 7;
				break;
			case '*':
				state = 9;
				break;
			case '^':
				state = 10;
				break;
			case '!':
				state = 11;
				break;
			case '%':
				state = 12;
				break;
			case '=':
				state = 13;
				break;
			case '/':
				state = 14;
				break;
			case'\'':
				state = 24;
				charnum = 0;
				break;
			case'"':
				state = 32;
				idname = "";
				idname += ch;
				break;
			default:
				lexerError(L002);
				break;
			}
			break;
		case 1:
			switch (ch)
			{
			case '>':
				token = new TOKEN(TAG_POINTER);
				break;
			case '-':
				token = new TOKEN(TAG_SELFSUB);
				break;
			case'=':
				token = new TOKEN(TAG_SUB_ASSIGN);
				break;
			default:
				token = new TOKEN('-');
				buffer.retract();
				break;
			}
			return token;
			break;
		case 2:
			switch (ch)
			{
			case '+':
				token = new TOKEN(TAG_SELFADD);
				break;
			case '=':
				token = new TOKEN(TAG_ADD_ASSIGN);
				break;
			default:
				token = new TOKEN('+');
				buffer.retract();
				break;
			}
			return token;
			break;
		case 3:
			switch (ch)
			{
			case '&':
				token = new TOKEN(TAG_AND);
				break;
			case '=':
				token = new TOKEN(TAG_BITAND_ASSIGN);
				break;
			default:
				token = new TOKEN('&');
				buffer.retract();
				break;
			}
			return token;
			break;
		case 4:
			switch (ch)
			{
			case '|':
				token = new TOKEN(TAG_OR);
				break;
			case '=':
				token = new TOKEN(TAG_BITOR_ASSIGN);
				break;
			default:
				token = new TOKEN('|');
				buffer.retract();
				break;
			}
			return token;
			break;
		case 5:
			switch (ch)
			{
			case'>':
				state = 6;
				break;
			case'=':
				token = new TOKEN(TAG_GE);
				return token;
				break;
			default:
				token = new TOKEN('>');
				buffer.retract();
				return token;
				break;
			}
			break;
		case 6:
			switch (ch)
			{
			case'=':
				token = new TOKEN(TAG_RIGHTSHIFT_ASSIGN);
				break;
			default:
				token = new TOKEN(TAG_RIGHTSHIFT);
				buffer.retract();
				break;
			}
			return token;
			break;
		case 7:
			switch (ch)
			{
			case '<':
				state = 8;
				break;
			case'=':
				token = new TOKEN(TAG_LEFTSHIFT);
				return token;
				break;
			default:
				token = new TOKEN('<');
				buffer.retract();
				return token;
				break;
			}
			break;
		case 8:
			switch (ch)
			{
			case'=':
				token = new TOKEN(TAG_LEFTSHIFT_ASSIGN);
				break;
			default:
				token = new TOKEN(TAG_LEFTSHIFT);
				buffer.retract();
				break;
			}
			return token;
			break;
		case 9:
			switch (ch)
			{
			case'=':
				token = new TOKEN(TAG_MUL_ASSIGN);
				break;
			default:
				token = new TOKEN('*');
				buffer.retract();
				break;
			}
			return token;
			break;
		case 10:
			switch (ch)
			{
			case'=':
				token = new TOKEN(TAG_BITNOR_ASSIGN);
				break;
			default:
				token = new TOKEN('^');
				buffer.retract();
				break;
			}
			return token;
			break;
		case 11:
			switch (ch)
			{
			case'=':
				token = new TOKEN(TAG_NEQ);
				break;
			default:
				token = new TOKEN('!');
				buffer.retract();
				break;
			}
			return token;
			break;
		case 12:
			switch (ch)
			{
			case'=':
				token = new TOKEN(TAG_MOD_ASSIGN);
				break;
			default:
				token = new TOKEN('%');
				buffer.retract();
				break;
			}
			return token;
			break;
		case 13:
			switch (ch)
			{
			case'=':
				token = new TOKEN(TAG_EQ);
				break;
			default:
				token = new TOKEN('=');
				buffer.retract();
				break;
			}
			return token;
			break;
		case 14:
			switch (ch)
			{
			case'=':
				token = new TOKEN(TAG_DIV_ASSIGN);
				return token;
				break;
			case'/':
				state = 15;
				break;
			case'*':
				state = 16;
				break;
			default:
				token = new TOKEN('/');
				buffer.retract();
				return token;
				break;
			}
			break;


		//state=15-17识别注释
		case 15:
			if (ch == '\n')state = 0;
			break;
		case 16:
			if (ch == '*')state = 17;
			break;
		case 17:
			if (ch == '/')state = 0;
			else if (ch == '*')state = 17;
			else state = 16;
			break;


		//state=18-23识别数字常量
		case 18:
			if (ch >= '0'&&ch <= '9') {
				num *= 10;
				num += ch - '0';
			}
			else if (ch == 'E') {
				state = 21;
				powerE = 0;
			}
			else if (ch == '.') {
				state = 19;
				afterDot = 1;
				fnum = 0;
			}
			else {
				token = new TOKEN(TAG_INTEGER);
				token->num(num);
				buffer.retract();
				return token;
			}
			break;
		case 19:
			if (ch >= '0'&&ch <= '9') {
				fnum += (ch - '0')*pow(10, -afterDot);
				afterDot++;
				state = 20;
			}
			else lexerError(L003);
			break;
		case 20:
			if (ch >= '0'&&ch <= '9') {
				fnum += (ch - '0')*pow(10, -afterDot);
				afterDot++;
			}
			else if (ch == 'E') {
				state = 21;
				powerE = 0;
				powerEsign = 1;
			}
			else {
				token = new TOKEN(TAG_REAL);
				token->num((double)num+fnum);
				buffer.retract();
				return token;
			}
			break;
		case 21:
			if (ch == '+' || ch == '-') {
				state = 22;
				if (ch == '+')powerEsign = 1;
				else powerEsign = -1;
			}
			else if (ch >= '0'&&ch <= '9') {
				powerE = ch - '0';
				state = 23;
				powerEsign = 1;
			}
			else lexerError(L004);
			break;
		case 22:
			if (ch >= '0'&&ch <= '9') {
				state = 23;
				powerE = ch - '0';
			}
			else lexerError(L004);
			break;
		case 23:
			if (ch >= '0'&&ch <= '9') {
				powerE *= 10;
				powerE += ch - '0';
			}
			else {
				if (fnum == 0.0 && powerE == 0) {
					token = new TOKEN(TAG_INTEGER);
					token->num(num);
				}
				else {
					fnum += num;
					
					token = new TOKEN(TAG_REAL);
					token->num(fnum*pow(10, powerEsign*powerE));
				}
				buffer.retract();
				return token;
			}
			break;


		//state=24-30识别字符常量
		case 24:
			if (ch == '\\') {
				state = 26;
			}
			else if (ch == '\'') {
				lexerError(L005);
			}
			else {
				charnum = ch;
				state = 25;
			}
			break;
		case 25:
			if (ch == '\\') {
				state = 26;
			}
			else if (ch == '\'') {
				token = new TOKEN(TAG_CH);
				token->num(charnum);
				return token;
			}
			else {
				charnum <<= 16;
				charnum += ch;
				state = 25;
			}
			break;
		case 26:
			if (ch == 'a' || ch == 'b' || ch == 'f' || ch == 'n' || ch == 'r' || ch == 't' || ch == 'v' || ch == '\\' || ch == '"' || ch == '\'') {
				char temp = ch;
				switch (ch)
				{
				case 'a':
					temp = '\a';
					break;
				case 'b':
					temp = '\b';
					break;
				case 'f':
					temp = '\f';
					break;
				case 'n':
					temp = '\n';
					break;
				case 'r':
					temp = '\r';
					break;
				case 't':
					temp = '\t';
					break;
				case 'v':
					temp = '\v';
					break;
				case '\\':
					temp = '\\';
					break;
				case '\'':
					temp = '\'';
					break;
				case '"':
					temp = '"';
					break;
				default:
					break;
				}
				charnum <<= 16;
				charnum += temp;
				state = 25;
			}
			else if (ch >= '0' && ch <= '7') {
				num = ch - '0';
				state = 27;
			}
			else if (ch == 'x') {
				state = 29;
			}
			else lexerError(L007);
			break;
		case 27:
			if (ch >= '0' && ch <= '7') {
				num *= 8;
				num += ch - '0';
				state = 28;
			}
			else if (ch == '\'') {
				charnum <<= 16;
				charnum += num;
				token = new TOKEN(TAG_CH);
				token->num(charnum);
				return token;
			}
			else {
				state = 25;
				charnum <<= 16;
				charnum += num;
				charnum <<= 16;
				charnum += ch;
			}
			break;
		case 28:
			if (ch == '\'') {
				charnum <<= 16;
				charnum += num;
				token = new TOKEN(TAG_CH);
				token->num(charnum);
				return token;
			}
			else {
				if (ch >= '0'&&ch <= '7') {
					num *= 8;
					num += ch - '0';
					state = 25;
					charnum <<= 16;
					charnum += num;
				}
				else {
					charnum <<= 16;
					charnum += num;
					charnum <<= 16;
					charnum += ch;
				}
				state = 25;
			}
			break;
		case 29:
			if (ch >= '0'&&ch <= '9' || ch >= 'a'&&ch <= 'f' || ch >= 'A'&&ch <= 'F') {
				if (ch >= '0'&&ch <= '9') {
					num = ch - '0';
				}
				else if (ch >= 'a'&&ch <= 'f') {
					num = 10 + ch - 'a';
				}
				else {
					num = 10 + ch - 'A';
				}
				state = 30;
			}
			else lexerError(L006);
		case 30:
			if (ch == '\'') {
				charnum <<= 16;
				charnum += num;
				token = new TOKEN(TAG_CH);
				token->num(charnum);
				return token;
			}
			else {
				if (ch >= '0'&&ch <= '9' || ch >= 'a'&&ch <= 'f' || ch >= 'A'&&ch <= 'F') {
					num *= 16;
					if (ch >= '0'&&ch <= '9') {
						num += ch - '0';
					}
					else if (ch >= 'a'&&ch <= 'f') {
						num += 10 + ch - 'a';
					}
					else {
						num += 10 + ch - 'A';
					}
					charnum <<= 16;
					charnum += num;
				}
				else {
					charnum <<= 16;
					charnum += num;
					charnum <<= 16;
					charnum += ch;
				}
				state = 25;
			}
			break;


		//state=32-37识别字符串常量
		case 32:
			if (ch == '\\') {
				state = 33;
				num = 0;
			}
			else if (ch == '"') {
				idname += ch;
				token = new TOKEN(TAG_STR);
				token->word(idname);
				return token;
			}
			else {
				idname += ch;
				state = 32;
			}
			break;
		case 33:
			if (ch == 'a' || ch == 'b' || ch == 'f' || ch == 'n' || ch == 'r' || ch == 't' || ch == 'v' || ch == '\\' || ch == '"' || ch == '\'') {
				char temp = ch;
				switch (ch)
				{
				case 'a':
					temp = '\a';
					break;
				case 'b':
					temp = '\b';
					break;
				case 'f':
					temp = '\f';
					break;
				case 'n':
					temp = '\n';
					break;
				case 'r':
					temp = '\r';
					break;
				case 't':
					temp = '\t';
					break;
				case 'v':
					temp = '\v';
					break;
				case '\\':
					temp = '\\';
					break;
				case '\'':
					temp = '\'';
					break;
				case '"':
					temp = '"';
					break;
				default:
					break;
				}
				idname += temp;
				state = 32;
			}
			else if (ch >= '0' && ch <= '7') {
				num = ch - '0';
				state = 34;
			}
			else if (ch == 'x') {
				state = 36;
			}
			else lexerError(L007);
			break;
		case 34:
			if (ch >= '0' && ch <= '7') {
				num *= 8;
				num += ch - '0';
				state = 35;
			}
			else if (ch == '"') {
				idname += (char)num;
				idname += ch;
				token = new TOKEN(TAG_STR);
				token->word(idname);
				return token;
			}
			else {
				state = 32;
				idname += (char)num;
				idname += ch;
			}
			break;
		case 35:
			if (ch == '"') {
				idname += (char)num;
				idname += ch;
				token = new TOKEN(TAG_STR);
				token->word(idname);
				return token;
			}
			else {
				if (ch >= '0'&&ch <= '7') {
					num *= 8;
					num += ch - '0';
					idname += (char)num;
				}
				else {
					idname += (char)num;
					idname += ch;
				}
				state = 32;
			}
			break;
		case 36:
			if (ch >= '0'&&ch <= '9' || ch >= 'a'&&ch <= 'f' || ch >= 'A'&&ch <= 'F') {
				if (ch >= '0'&&ch <= '9') {
					num = ch - '0';
				}
				else if (ch >= 'a'&&ch <= 'f') {
					num = 10 + ch - 'a';
				}
				else {
					num = 10 + ch - 'A';
				}
				state = 37;
			}
			else lexerError(L006);
			break;
		case 37:
			if (ch == '"') {
				idname += (char)num;
				idname += ch;
				token = new TOKEN(TAG_STR);
				token->word(idname);
				return token;
			}
			else {
				if (ch >= '0'&&ch <= '9' || ch >= 'a'&&ch <= 'f' || ch >= 'A'&&ch <= 'F') {
					num *= 16;
					if (ch >= '0'&&ch <= '9') {
						num += ch - '0';
					}
					else if (ch >= 'a'&&ch <= 'f') {
						num += 10 + ch - 'a';
					}
					else {
						num += 10 + ch - 'A';
					}
					idname += (char)num;
				}
				else {
					idname += (char)num;
					idname += ch;
				}
				state = 32;
			}
			break;


		//state=38识别关键字和标识符
		case 38:
			if (ch >= 'a'&&ch <= 'z' || ch >= 'A'&&ch <= 'Z' || ch == '_' || ch >= '0'&&ch <= '9') {
				idname += ch;
			}
			else {
				buffer.retract();
				token = new TOKEN(TAG_ID);
				token->word(idname);
				//区分关键字和标识符
				lexer_scan_reverse(token);
				return token;
			}
			break;
		default:
			lexerError(R001);
			break;
		}
	}
}


//保留字识别
void lexer_scan_reverse(TOKEN* t) {
	switch (t->lexeme[0])
	{
	case'a':
		if (t->lexeme == "auto")t->tag = TAG_AUTO;
		break;
	case'b':
		if (t->lexeme == "break")t->tag = TAG_BREAK;
		break;
	case'c':
		switch (t->lexeme[1])
		{
		case'a':
			if (t->lexeme == "case")t->tag = TAG_CASE;
			break;
		case'h':
			if (t->lexeme == "char")t->tag = TAG_CHAR;
			break;
		case'o':
			if (t->lexeme == "const")t->tag = TAG_CONST;
			else if (t->lexeme == "continue")t->tag = TAG_CONTINUE;
			break;
		default:
			break;
		}
		break;
	case'd':
		switch (t->lexeme[1])
		{
		case'o':
			if (t->lexeme == "do")t->tag = TAG_DO;
			else if (t->lexeme == "double")t->tag = TAG_DOUBLE;
			break;
		case'e':
			if (t->lexeme == "default")t->tag = TAG_DEFAULT;
			break;
		default:
			break;
		}
		break;
	case'e':
		switch (t->lexeme[1])
		{
		case 'l':
			if (t->lexeme == "else")t->tag = TAG_ELSE;
			break;
		case'n':
			if (t->lexeme == "enum")t->tag = TAG_ENUM;
			break;
		case'x':
			if (t->lexeme == "extern")t->tag = TAG_EXTERN;
			break;
		default:
			break;
		}
		break;
	case'f':
		switch (t->lexeme[1])
		{
		case 'l':
			if (t->lexeme == "float")t->tag = TAG_FLOAT;
			break;
		case'o':
			if (t->lexeme == "for")t->tag = TAG_FOR;
			break;
		default:
			break;
		}
		break;
	case'g':
		if (t->lexeme == "goto")t->tag = TAG_GOTO;
		break;
	case'i':
		switch (t->lexeme[1])
		{
		case 'f':
			if (t->lexeme == "if")t->tag = TAG_IF;
			break;
		case'n':
			if (t->lexeme == "int")t->tag = TAG_INT;
			break;
		default:
			break;
		}
		break;
	case'l':
		if (t->lexeme == "long")t->tag = TAG_LONG;
		break;
	case'r':
		if (t->lexeme == "register")t->tag = TAG_REGISTER;
		else if (t->lexeme == "return")t->tag = TAG_RETURN;
		break;
	case's':
		switch (t->lexeme[1])
		{
		case 'h':
			if (t->lexeme == "short")t->tag = TAG_SHORT;
			break;
		case'i':
			if (t->lexeme == "signed")t->tag = TAG_SIGNED;
			else if (t->lexeme == "sizeof")t->tag = TAG_SIZEOF;
			break;
		case't':
			if (t->lexeme == "static")t->tag = TAG_STATIC;
			else if (t->lexeme == "struct")t->tag = TAG_STRUCT;
			break;
		case'w':
			if (t->lexeme == "switch")t->tag = TAG_SWITCH;
			break;
		default:
			break;
		}
		break;
	case't':
		if (t->lexeme == "typedef")t->tag = TAG_TYPEDEF;
		break;
	case'u':
		if (t->lexeme == "union")t->tag = TAG_UNION;
		else if (t->lexeme == "unsigned")t->tag = TAG_UNSIGNED;
		break;
	case'v':
		if (t->lexeme == "void")t->tag = TAG_VOID;
		else if (t->lexeme == "volatile")t->tag = TAG_VOLATILE;
		break;
	case'w':
		if (t->lexeme == "while")t->tag = TAG_WHILE;
		break;
	default:
		break;
	}
}