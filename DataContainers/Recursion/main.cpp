#include<iostream>
using namespace std;

	//Рекурсивная
	//Итерационная
	//Стек вызовов (Call stack)
	//Stack overflow exception

void Elevator(int floor);
int Factorial(int n);
double Power(double a, int n);//a - основание степени, n - показатель степени

void main()
{
	setlocale(LC_ALL, "");
	cout << "Hello World!";
	int n;
	int a;
	//cout << "Введите номер этажа: "; cin >> n;
	//Elevator(n);
	//cout << "Введите число: "; cin >> n;
	//cout << Factorial(n) << endl;
	cout << "Введите основание степени: "; cin >> a;
	cout << "Введите показатель степени: "; cin >> n;
	cout << Power(a, n) << endl;
	
	//main();
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
	if (n == 0)return 1;
	else return a * Power(a, n - 1);
}