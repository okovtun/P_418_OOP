//String (ClassString)
#include<Windows.h>
#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-----------------------------------\n"

int StringLength(const char str[]);
char* ToUpper(char str[]);	//переводит строку в верхний регистр: Hello => HELLO
char* ToLower(char str[]);	//переводит строку в нижний регистр: Hello => HELLO

//NULL Terminated Lines
//#define LINES_BASICS_1

void main()
{
	cout << 'Ё' << "\t" << 'ё' << endl;
	cout << (int)'Ё' << "\t" << (int)'ё' << endl;
	cout << 'A' << "\t" << 'a' << endl;
	cout << (int)'A' << "\t" << (int)'a' << endl;;
	cout << 'A' - 'a' << endl;
	cout << endl;
	setlocale(LC_ALL, "");

#ifdef LINES_BASICS_1
	//char str[] = { 'H', 'e', 'l', 'l', 'o', '\0' };
//char str[] = { 'H', 'e', 'l', 'l', 'o', 0 };
	char str[] = "Hello";
	cout << str << endl;
	cout << sizeof(str) << endl;
#endif // LINES_BASICS_1

	const int SIZE = 256;
	char str[SIZE] = "Хорошо      живет     на     свете      Винни      Пух";
	cout << "Введите строку: ";
	SetConsoleCP(1251);
	//cin >> str;
	//cin.getline(str, SIZE);
	SetConsoleCP(866);
	cout << str << endl;

	cout << sizeof(str) << endl;
	cout << typeid(str).name() << endl;
	cout << StringLength(str) << endl;
	cout << strlen(str) << endl;
	//ToUpper(str);
	//cout << str << endl;
	cout << ToUpper(str) << endl;
	//cout << ToLower(str) << endl;
}

int StringLength(const char str[])
{
	/*cout << delimiter << endl;
	cout << sizeof(str) << endl;
	cout << typeid(str).name() << endl;*/
	int i = 0;
	for (; str[i]; i++);
	return i;
}
char* ToUpper(char str[])
{
	//for (int i = 0; i < 256; i++)cout << i << tab << (char)i << endl;
	for (int i = 0; str[i]; i++)
	{
		/*if (str[i] >= 'a' && str[i] <= 'z')str[i] -= ' ';
		if (str[i] >= 'а' && str[i] <= 'я')str[i] -= ' ';
		if (str[i] == 'ё')str[i] -= 16;*/
		str[i] = toupper(str[i]);
	}
	return str;
}
char* ToLower(char str[])
{
	//for (int i = 0; i < 256; i++)cout << i << tab << (char)i << endl;
	for (int i = 0; str[i]; i++)
	{
		/*if (str[i] >= 'A' && str[i] <= 'Z')str[i] += ' ';
		if (str[i] >= 'А' && str[i] <= 'Я')str[i] += ' ';
		if (str[i] == 'Ё')str[i] += 16;*/
		str[i] = tolower(str[i]);
	}
	return str;
}
