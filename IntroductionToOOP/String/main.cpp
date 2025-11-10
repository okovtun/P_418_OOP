//String (ClassString)
#define _CRT_SECURE_NO_WARNINGS
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
char* Shrink(char str[]);
bool isPalindrome(const char str[]);

bool is_bin_number(const char str[]);
int bin_to_dec(const char str[]);

bool is_hex_number(const char str[]);
int hex_to_dec(const char str[]);



//NULL Terminated Lines
//#define LINES_BASICS_1
//#define LINES_BASICS_2

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

#ifdef LINES_BASICS_2
	const int SIZE = 256;
	//char str[SIZE] = "Хорошо      живет     на     свете      Винни      Пух";
	char str[SIZE] = "Аргентина манит негра";
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
	//cout << ToUpper(str) << endl;
	//cout << ToLower(str) << endl;
	cout << Shrink(str) << endl;
	cout << "Строка " << (isPalindrome(str) ? "" : "не ") << "является палиндромом" << endl;
#endif // LINES_BASICS_2

	const int SIZE = 48;
	//char str[SIZE] = "10   1100 1000";
	char str[SIZE] = "0xC8";

	cout << "Строка " << (is_bin_number(str) ? "" : "не ") << "является двоичным числом" << endl;
	cout << str << "(bin) = " << bin_to_dec(str) << "(dec)" << endl;

	cout << "Строка " << (is_hex_number(str) ? "" : "не ") << "является шестнадцатеричным числом" << endl;
	cout << str << "(hex) = " << hex_to_dec(str) << "(dec)" << endl;


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
char* Shrink(char str[])
{
	for (int i = 0; str[i]; i++)
	{
		while (str[i] == ' ' && str[i + 1] == ' ')
		{
			for (int j = i + 1; str[j]; j++)str[j] = str[j + 1];
		}
	}
	return str;
}
char* RemoveSymbol(char str[], char symbol = ' ')
{
	for (int i = 0; str[i]; i++)
	{
		while (str[i] == symbol)
		{
			for (int j = i; str[j]; j++)str[j] = str[j + 1];
		}
	}
	return str;
}
bool isPalindrome(const char str[])
{
	int size = StringLength(str);
	char* buffer = new char[size + 1]{};
	strcpy(buffer, str);
	//strcpy(dst,src); //Эта функция копирует содержимое строки 'src' (Source - Источник) в строку 'dst' (Destination - Получатель)
	ToLower(buffer);
	RemoveSymbol(buffer);
	size = StringLength(buffer);
	for (int i = 0; i < size / 2; i++)
	{
		if (buffer[i] != buffer[size - 1 - i])
		{
			delete[] buffer;
			return false;
		}
	}
	delete[] buffer;
	return true;
}
bool is_bin_number(const char str[])
{
	for (int i = 0; str[i]; i++)
	{
		if (str[i] != '0' && str[i] != '1' && str[i] != ' ')return false;
	}
	return true;
}
int bin_to_dec(const char str[])
{
	int decimal = 0;
	int weight = 1;		//Весовой коэффициент разряда
	int length = StringLength(str);
	for (int i = length - 1; i >= 0; i--)
	{
		if (str[i] == ' ')continue;
		decimal += (str[i] - '0')*weight;
		weight *= 2;
	}
	return decimal;
}
bool is_hex_number(const char str[])
{
	bool prefix = false;
	if (str[0] == '0' && str[1] == 'x')prefix = true;
	for (int i = prefix ? 2 : 0; str[i]; i++)
	{
		if (
			!(str[i] >= '0' && str[i] <= '9') &&
			!(str[i] >= 'A' && str[i] <= 'F') &&
			!(str[i] >= 'a' && str[i] <= 'f')
			)return false;
	}
	return true;
}
int hex_to_dec(const char str[])
{
	int decimal = 0;
	int weight = 1;
	int length = StringLength(str);
	bool prefix = false;
	if (str[0] == '0' && str[1] == 'x')prefix = true;
	for (int i = length - 1; i >= (prefix ? 2 : 0); i--)
	{
		int digit;
		if (str[i] >= '0' && str[i] <= '9')digit = str[i] - 48;
		if (str[i] >= 'A' && str[i] <= 'F')digit = str[i] - 55;
		if (str[i] >= 'a' && str[i] <= 'f')digit = str[i] - 87;
		decimal += digit * weight;
		weight *= 16;
	}
	return decimal;
}