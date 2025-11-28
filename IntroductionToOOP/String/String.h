#pragma once
#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n----------------------------------\n"

///////////////////////////////////////////////////////////////////////////
///////			Class declaration (ќбъ€вление класса)				///////

class String
{
	int size;	//размер строки в Ѕайтах
	char* str;	//указатель на строку в динамической пам€ти
public:
	int get_size()const;
	const char* get_str()const;
	char* get_str();

	//				Constructors:
	explicit String(int size = 80);
	String(const char str[]);
	String(const String& other);
	String(String&& other);
	~String();

	//				Operators
	String& operator=(const String& other);
	String& operator=(String&& other);

	char operator[](int i)const;
	char& operator[](int i);


	//				Methods:
	void print()const;
};

///////		Class declaration end ( онец объ€влени€ класса)			///////
///////////////////////////////////////////////////////////////////////////
