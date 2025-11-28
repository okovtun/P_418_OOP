#include"String.h"
///---------------------------------------------------------------------///

///////////////////////////////////////////////////////////////////////////
///////			Class definition (Определение класса)				///////

int String::get_size()const
{
	return size;
}
const char* String::get_str()const
{
	return str;
}
char* String::get_str()
{
	return str;
}
//				Constructors:
String::String(int size) :size(size), str(new char[size] {})
{
	//this->size = size;
	//this->str = new char[size] {};
	cout << "DefConstructor:\t" << this << endl;
}
String::String(const char str[]) :String(strlen(str) + 1)
{
	for (int i = 0; str[i]; i++)this->str[i] = str[i];
	cout << "Constructor:\t" << this << endl;
}
String::String(const String& other) : String(other.str)
{
	cout << "CopyConstructor:\t" << this << endl;
}
String::String(String&& other)
{
	this->size = other.size;
	this->str = other.str;

	other.size = 0;
	other.str = nullptr;
	cout << "MoveConstructor:" << this << endl;
}
String::~String()
{
	delete[] str;
	cout << "Destructor:\t" << this << endl;
}

//              Operators
String& String::operator=(const String& other)
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
String& String::operator=(String&& other)
{
	if (this == &other)return *this;
	delete[] this->str;

	this->size = other.size;
	this->str = other.str;

	other.size = 0;
	other.str = nullptr;

	cout << "MoveAssignment:\t" << this << endl;
	return *this;
}

char String::operator[](int i)const
{
	return str[i];
}
char& String::operator[](int i)
{
	return str[i];
}

//				Methods:
void String::print()const
{
	cout << "Size:\t" << size << endl;
	cout << "Str:\t" << str << endl;
}

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

///////		Class definition end (Конец определения класса)			///////
///////////////////////////////////////////////////////////////////////////
