#include<iostream>
using namespace std;

//#define EXAMPLE_1
//#define EXAMPLE_2

#ifdef EXAMPLE_1
void Hello()
{
	cout << "Hello" << endl;;
}
#endif // EXAMPLE_1

#ifdef EXAMPLE_2
const char* Hello()
{
	return "Hello";
}
#endif // EXAMPLE_2

int sum(int a, int b)
{
	return a + b;
}

void main()
{
	setlocale(LC_ALL, "");
	cout << "Function pointers" << endl;

#ifdef EXAMPLE_1
	void(*pHello)() = Hello;
	cout << Hello << endl;
	cout << pHello << endl;
	(*pHello)();
#endif // EXAMPLE_1

#ifdef EXAMPLE_2
	cout << Hello() << endl;
	const char* (*pHello)() = Hello;
	cout << Hello << endl;
	cout << pHello << endl;
	cout << (*pHello)() << endl;
#endif // EXAMPLE_2

	int(*p_sum)(int a, int b) = sum;
	cout << (*p_sum)(2, 3) << endl;
}

/*
----------------------------------------
type name(parameters);		//Исходная функция, на которую нужно объявить указатель
type (*p_name)(parameters);	//Указатель на функцию
(*name)(parameters);		//Вызов исходной функции 'name()' через указатель 'p_name()';
----------------------------------------
*/