#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n------------------------------------------\n"

class Fraction;
Fraction operator*(Fraction left, Fraction right);
Fraction operator/(const Fraction& left, const Fraction& right);

class Fraction
{
	int integer;		//целая часть
	int numerator;		//числитель
	int denominator;	//значенатель
public:
	int get_integer()const
	{
		return integer;
	}
	int get_numerator()const
	{
		return numerator;
	}
	int get_denominator()const
	{
		return denominator;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator(int denominator)
	{
		if (denominator == 0)denominator = 1;
		this->denominator = denominator;
	}

	//				Constructors:
	Fraction()
	{
		integer = 0;
		numerator = 0;
		denominator = 1;
		cout << "DefaultConstrcutor:\t" << this << endl;
	}
	explicit Fraction(int integer)
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		cout << "SingleArgumentConstrcutor:" << this << endl;
	}
	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		set_numerator(numerator);
		set_denominator(denominator);
		cout << "Constructor:\t\t" << this << endl;
	}
	Fraction(int integer, int numerator, int denominator)
	{
		set_integer(integer);
		set_numerator(numerator);
		set_denominator(denominator);
		cout << "Constructor:\t\t" << this << endl;
	}
	Fraction(const Fraction& other)
	{
		//Конструктор копирования всегда принимает константную ссылку на объект
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		//Здесь можно не применять set-методы, а записывать значения напрямую в переменные,
		//потому что все значения прошли фильтрацию данных при создании объекта 'other'.
		cout << "CopyConstructor:\t" << this << endl;
	}
	~Fraction()
	{
		cout << "Destructor:\t\t" << this << endl;
	}

	//			Operators:
	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyAssignment:\t\t" << this << endl;
		return *this;
	}
	Fraction& operator*=(const Fraction& other)
	{
		return *this = *this*other;
	}
	Fraction operator/=(const Fraction& other)
	{
		return *this = *this / other;
	}

	//			Increment/Decrement:
	Fraction& operator++()	//Prefix increment
	{
		this->integer++;
		return *this;
	}
	Fraction& operator++(int)
	{
		//Постфиксные ++/-- всегда принимают один параметр типа 'int',
		//это позволяет на уровне перегрузки функций отличать их 
		//от префиксных ++/--;
		Fraction old = *this;	//old - это локальный объект
		this->integer++;
		return old;
	}

	//			Methods:
	Fraction& to_improper()
	{
		numerator += integer * denominator;
		integer = 0;
		return *this;
	}
	Fraction& to_proper()
	{
		integer += numerator / denominator;
		numerator %= denominator;
		return *this;
	}
	Fraction inverted()const
	{
		Fraction inverted = *this;
		inverted.to_improper();
		std::swap(inverted.numerator, inverted.denominator);
		return inverted;
	}
	Fraction& reduce()
	{
		//https://www.webmath.ru/poleznoe/formules_12_7.php
		int more, less, rest = 0;
		if (numerator > denominator)more = numerator, less = denominator;
		else less = numerator, more = denominator;
		do
		{
			rest = more % less;
			more = less;
			less = rest;
		} while (rest);
		int GCD = more;	//GCD - Greatest Common Divisor (Наибольший общий делитель)
		numerator /= GCD;
		denominator /= GCD;
		return *this;
	}
	void print()const
	{
		if (integer)cout << integer;
		if (numerator)
		{
			if (integer) cout << "(";
			cout << numerator << "/" << denominator;
			if (integer) cout << ")";
		}
		else if (integer == 0)cout << 0;
		cout << endl;
	}
};
Fraction operator*(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();

	return Fraction
	(
		left.get_numerator()*right.get_numerator(),
		left.get_denominator()*right.get_denominator()
	).to_proper().reduce();

	/*Fraction result
	(
		left.get_numerator()*right.get_numerator(),
		left.get_denominator()*right.get_denominator()
	);
	result.to_proper();
	return result;*/

	/*Fraction result;
	result.set_numerator(left.get_numerator()*right.get_numerator());
	result.set_denominator(left.get_denominator()*right.get_denominator());
	return result;*/
}
Fraction operator/(const Fraction& left, const Fraction& right)
{
	return left * right.inverted();	//Повторное использование кода
}

//				Comparison operators:
bool operator==(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return left.get_numerator()*right.get_denominator() == right.get_numerator()*left.get_denominator();
}
bool operator!=(const Fraction& left, const Fraction& right)
{
	return !(left == right);
}
bool operator>(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return 
		left.get_numerator()*right.get_denominator() > 
		right.get_numerator()*left.get_denominator();
}
bool operator<(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return 
		left.get_numerator()*right.get_denominator() < 
		right.get_numerator()*left.get_denominator();
}
bool operator>=(const Fraction& left, const Fraction& right)
{
	return !(left < right);
	//return left > right || left == right;
}
bool operator<=(const Fraction& left, const Fraction& right)
{
	return !(left > right);
}

std::ostream& operator<<(std::ostream& os, const Fraction& obj)
{
	if (obj.get_integer())os << obj.get_integer();
	if (obj.get_numerator())
	{
		if (obj.get_integer())os << "(";
		os << obj.get_numerator() << "/" << obj.get_denominator();
		if (obj.get_integer())os << ")";
	}
	else if (obj.get_integer() == 0)os << 0;
	return os;
}
std::istream& operator>>(std::istream& is, Fraction& obj)
{
	/*
	------------------------------
	5
	1/2
	7(8/10)
	7+8/10
	7 8/10
	------------------------------
	*/
	const int SIZE = 32;
	char buffer[SIZE] = {};
	is >> buffer;
	//is.getline(buffer, SIZE);	//позволяет ввести строку с пробелами
	cout << buffer << endl;
	int numbers[3] = {};
	const char delimiters[] = "+()/";
	int n = 0;
	for (char* pch = strtok(buffer, delimiters); pch; pch = strtok(NULL, delimiters))
	{	
		numbers[n++] = std::atoi(pch);	//atoi() - ANSI/ASCII to Int;
		//cout << pch << "\t";
	}
	for (int i = 0; i < n; i++)
	{
		cout << numbers[i] << "\t";
	}
	cout << endl;
	switch (n)
	{
	case 1:obj = Fraction(numbers[0]); break;
	case 2:obj = Fraction(numbers[0],numbers[1]); break;
	case 3:obj = Fraction(numbers[0],numbers[1],numbers[2]); break;
	}

	/*int integer;
	int numerator;
	int denominator;
	is >> integer >> numerator >> denominator;
	obj = Fraction(integer, numerator, denominator);*/

	return is;
}

//#define CONSTRUCTORS_CHECK
//#define ARITHMETICAL_OPERATORS_CHECK
//#define COMPOUND_ASSIGNMENTS_CHECK
//#define INCREMENTO_DECREMENTO
//#define STREAMS_CHECK_1
//#define STREAMS_CHECK_2
//#define TYPE_CONVERSIONS_BASICS
//#define CONVERSIONS_FROM_OTHER_TO_CLASS
#define HOME_WORK

void main()
{
	setlocale(LC_ALL, "");

#ifdef CONSTRUCTORS_CHECK
	Fraction A;		//Default constructor
	A.print();

	Fraction B = 5;//Single-argument constructor
	B.print();

	Fraction C(1, 2);
	C.print();

	Fraction D(2, 3, 4);
	D.print();

	Fraction E = D;		//CopyConstructor
	E.print();

	Fraction F;
	F = E;		//CopyAssignment - Оператор присваивания (Assignment - Присваивание)
	F.print();
#endif // CONSTRUCTORS_CHECK

#ifdef ARITHMETICAL_OPERATORS_CHECK
	Fraction A(2, 3, 4);
	A.print();

	Fraction B(3, 4, 5);
	B.print();

	A.to_improper();
	A.print();
	A.to_proper();
	A.print();
	cout << delimiter << endl;
	Fraction C = A / B;
	cout << delimiter << endl;
	C.print();
#endif // ARITHMETICAL_OPERATORS_CHECK

#ifdef COMPOUND_ASSIGNMENTS_CHECK
	Fraction A(2, 3, 4);
	Fraction B(3, 4, 5);
	A *= B;
	A.print();

	A /= B;
	A.print();
#endif // COMPOUND_ASSIGNMENTS_CHECK

#ifdef INCREMENTO_DECREMENTO
	for (double i = .5; i < 10; i++)
	{
		cout << i << tab;
	}
	cout << endl;

	for (Fraction i(1, 2); i.get_integer() < 10; i++)
	{
		i.print();
	}

	Fraction A(1, 2);
	Fraction B = A++;
	B.print();
#endif // INCREMENTO_DECREMENTO

#ifdef STREAMS_CHECK_1
	//cout << (2 == 2) << endl;
//cout << (Fraction(1, 3) <= Fraction(5, 11)) << endl;

	Fraction A(2, 3, 4);
	cout << "Введите простую дробь: ";

	cin >> A;

	cout << A << endl;

	/*typedef char DataType;
	DataType a = 2;
	DataType b = 3;
	DataType* pa = &a;
	DataType* pb = &b;
	cout << pa << endl;
	cout << pb << endl;
	cout << pa - pb << endl;*/
#endif // STREAMS_CHECK_1

#ifdef STREAMS_CHECK_2
	Fraction A, B, C;
	cout << "Введите три простых дроби: ";
	cin >> A >> B >> C;
	cout << A << tab << B << tab << C << endl;
#endif // STREAMS_CHECK_2

#ifdef TYPE_CONVERSIONS_BASICS
	//(type)value;	//C-like notation		(C-подобная форма записи)
	//type(value);	//Functional notation	(Функциональная форма записи)

	int a = 2;		//No conversions
	double b = a;	//Conversion from less to more
	int c = b;		//Conversion from more to less without data loss
	int d = 3.14;	//Conversion from more to less with data loss
	//		l-value = r-value;
	int e = 2 + 3.14;
#endif // TYPE_CONVERSIONS_BASICS

	//1)From other to Class - из других типов в наш тип;
	//		Single-argument constructor;
	//		Copy assignment
	//2)From class to other - из нашего типа в другие типы;

#ifdef CONVERSIONS_FROM_OTHER_TO_CLASS
	Fraction A = (Fraction)5;		//Conversion from 'int' to 'Fraction'
	cout << A << endl;

	Fraction B;
	B = Fraction(8);	//Conversion from 'int' to 'Fraction'
	cout << B << endl;
#endif // CONVERSIONS_FROM_OTHER_TO_CLASS

#ifdef HOME_WORK
	Fraction A = 2.75;
	cout << A << endl;
#endif // HOME_WORK

}