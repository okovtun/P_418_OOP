#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n----------------------------------\n"

class String
{
	int size;	//размер строки в Байтах
	char* str;	//указатель на строку в динамической памяти
public:
	int get_size()const
	{
		return size;
	}
	const char* get_str()const
	{
		return str;
	}
	char* get_str()
	{
		return str;
	}

	//				Constructors:
	explicit String(int size = 80)
	{
		this->size = size;
		this->str = new char[size] {};
		cout << "DefConstructor:\t" << this << endl;
	}
	String(const char str[])
	{
		this->size = strlen(str) + 1;
		this->str = new char[size] {};
		for (int i = 0; str[i]; i++)this->str[i] = str[i];
		cout << "Constructor:\t" << this << endl;
	}
	String(const String& other)
	{
		this->size = other.size;
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = other.str[i];
		cout << "CopyConstructor:" << this << endl;
	}
	String(String&& other)
	{
		//String&& - r-value reference

		//Shallow copy - поверхностное копирование:
		this->size = other.size;
		this->str = other.str;

		//Обязательно нужно обнулить копируемый объект:
		other.size = 0;
		other.str = nullptr;
		//это предотвращает удаление динамической памяти деструктором.

		cout << "MoveConstructor:" << this << endl;
	}
	~String()
	{
		delete[] str;
		cout << "Destructor:\t" << this << endl;
	}

	//				Operators
	String& operator=(const String& other)
	{
		if (this == &other)return *this;
		delete[] this->str;
		//Deep copy:
		this->size = other.size;
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = other.str[i];
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}

	char operator[](int i)const
	{
		return str[i];
	}
	char& operator[](int i)
	{
		return str[i];
	}


	//				Methods:
	void print()const
	{
		cout << "Size:\t" << size << endl;
		cout << "Str:\t" << str << endl;
	}
};

String operator+(const String& left, const String& right)
{
	//Сложение строк - Конкатенация строк:
	String result(left.get_size() + right.get_size() - 1);
	const double PI = 3.14;
	//PI = 2.7;
	for (int i = 0; i < left.get_size(); i++)
		result[i] = left[i];
		//result.get_str()[i] = left.get_str()[i];
	for (int i = 0; i < right.get_size(); i++)
		result[i + left.get_size() - 1] = right[i];
		//result.get_str()[i + left.get_size() - 1] = right.get_str()[i];
	return result;
	//0x00e12640
	//r-value reference
}

std::ostream& operator<<(std::ostream& os, const String& obj)
{
	return os << obj.get_str();
}

//#define BASE_CHECK
#define OPERATORS_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	String str(12);	//Conversion from 'int' to 'String'
//str.print();
	cout << str << endl;

	String str1 = "Hello";
	str1 = str1;
	str1.print();
	cout << str1 << endl;

	String str2 = str1;		//Copy constructor
	cout << str2 << endl;

	String str3;
	str3 = str2;			//CopyAssignment
	cout << str3 << endl;
#endif // BASE_CHECK

#ifdef OPERATORS_CHECK
	int a = 2;
	int b = 3;
	a + b;
	String str1 = "Hello";
	String str2 = "World";

	cout << delimiter << endl;
	String str3 = str1 + str2;
	cout << delimiter << endl;
	
	cout << str3 << endl;
#endif // OPERATORS_CHECK

}

//Deep copy
//Shallow copy
//Debug Assertion Failed
//Memory Leak

//Move semantic:
//Move constructor
//Move assignment