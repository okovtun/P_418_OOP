#include<iostream>
using namespace std;

	//Рекурсивная
	//Итерационная
	//Стек вызовов (Call stack)
	//Stack overflow exception

class Fibonacci
{
	static void Calculate(int n, int a, int b)
	{
		if (a > n)return;
		cout << a << "\t";
		Calculate(n, b, a + b);
	}
public:
	static void Calculate(int n)
	{
		Calculate(n, 0, 1);
		cout << endl;
	}
};

void Elevator(int floor);
int Factorial(int n);
double Power(double a, int n);//a - основание степени, n - показатель степени
void Fibonacci(int n, int a = 0, int b = 1);

void main()
{
	setlocale(LC_ALL, "");
	//cout << "Hello World!";
	int n;
	int a;
	//cout << "Введите номер этажа: "; cin >> n;
	//Elevator(n);
	//cout << "Введите число: "; cin >> n;
	//cout << Factorial(n) << endl;
	/*cout << "Введите основание степени: "; cin >> a;
	cout << "Введите показатель степени: "; cin >> n;
	cout << Power(a, n) << endl;*/
	cout << "Введите предел ряда Фибоначчи: "; cin >> n;
	Fibonacci::Calculate(n);
	//Fibonacci(n, 22, 33);
	cout << endl;
	
	main();
	//Написать рекурсивную функцию ??? Factorial(???), которая принимает число,
	//и возвращает факториал этого числа.
}

void Elevator(int floor)
{
	if (floor == 0)
	{
		cout << "Вы в подвале" << endl;
		return;
	}
	cout << "Вы на " << floor << " этаже" << endl;
	Elevator(floor-1);
	cout << "Вы на " << floor << " этаже" << endl;
}
int Factorial(int n)
{
	return n == 0 ? 1 : n * Factorial(n - 1);
	/*if (n == 0)return 1;
	else return n*Factorial(n - 1);*/
}
double Power(double a, int n)
{
	return n == 0 ? 1 : n > 0 ? a * Power(a, n - 1) : 1 / Power(a, -n);
	/*if (n == 0)return 1;
	else if(n>0)return a * Power(a, n - 1);
	else return 1 / Power(a, -n);*/
	//else return 1 / a * Power(a, n + 1);
}
void Fibonacci(int n, int a, int b)
{
	if (a > n)return;
	cout << a << "\t";
	Fibonacci(n, b, a + b);
}