#pragma once
#include<string.h>
#include<iostream>

using namespace std;

//运算符TAG定义
#define TAG_POINTER 256 //->
#define TAG_SELFADD 257 //++
#define TAG_SELFSUB 258 //--
#define TAG_SIZEOF 259 //sizeof
#define	TAG_LEFTSHIFT 260 //<<
#define TAG_RIGHTSHIFT 261 //>>
#define TAG_GE 262 //>=
#define TAG_LE 263 //<=
#define TAG_EQ 264 //==
#define TAG_NEQ 265 //!=
#define TAG_AND 266 //&&
#define TAG_OR 267 //||
#define TAG_DIV_ASSIGN 268 // /=
#define TAG_MUL_ASSIGN 269 //*=
#define TAG_MOD_ASSIGN 270 //%=
#define TAG_ADD_ASSIGN 271 //+=
#define TAG_SUB_ASSIGN 272 //-=
#define TAG_LEFTSHIFT_ASSIGN 273 //<<=
#define TAG_RIGHTSHIFT_ASSIGN 274 //>>=
#define TAG_BITAND_ASSIGN 275 //&=
#define TAG_BITNOR_ASSIGN 276 //^=
#define TAG_BITOR_ASSIGN 277 //|=

//常量TAG定义
#define TAG_INTEGER 278
#define TAG_REAL 279
#define TAG_CH 281
#define TAG_STR 282

//标识符TAG定义
#define TAG_ID 283

//保留字TAG定义
#define TAG_IF 284
#define TAG_ELSE 285
#define TAG_WHILE 286
#define TAG_DO 287
#define TAG_CLASS 288
#define TAG_BREAK 289
#define TAG_AUTO 290
#define TAG_CASE 291
#define TAG_CHAR 292
#define TAG_CONST 293
#define TAG_CONTINUE 294
#define TAG_DEFAULT 295
#define TAG_DOUBLE 296
#define TAG_ENUM 297
#define TAG_EXTERN 298
#define TAG_FLOAT 299
#define TAG_FOR 300
#define TAG_GOTO 301
#define TAG_INT 302
#define TAG_LONG 303
#define TAG_REGISTER 304
#define TAG_RETURN 305
#define TAG_SHORT 306
#define TAG_SIGNED 307
#define TAG_STATIC 308
#define TAG_STRUCT 309
#define TAG_SWITCH 310
#define TAG_TYPEDEF 311
#define TAG_UNION 312
#define TAG_UNSIGNED 313
#define TAG_VOID 314
#define TAG_VOLATILE 315

//失效的TOKEN应该舍去
#define TAG_NULL -1


class TOKEN
{
public:
	int tag;
	long long int value_int;//识别出INTEGER后存储在该变量中
	double value_float;//识别出REAL后存储在该变量中
	int value_char;//识别出CH后存储在该变量中
	string lexeme;//识别出标识符(ID)或STR后赋值lexeme

	TOKEN(int tag) { this->tag = tag; }
	void num(long long int value) { this->value_int = value; }
	void num(double value) { this->value_float = value; }
	void num(int value) { this->value_char = value; }
	void word(string lexeme) { this->lexeme = lexeme; }
};