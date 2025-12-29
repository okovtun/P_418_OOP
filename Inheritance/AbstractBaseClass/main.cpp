#include<iostream>
using namespace std;

class Vehicle	//Транспортное средство
{
	int speed;	//Скорость
public:
	virtual void move() = 0;
};
//Наземное транспортное средство
class GroundVehicle:public Vehicle{};

class Car :public GroundVehicle
{
public:
	void move()override
	{
		cout << "Машина едет на 4-х колесах" << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	cout << "AbstractBaseClass" << endl;
	//Vehicle v;	//E0322: Object of abstract class type 'Vehicle' is not allowed (Объекты абстрактного класса 'Vehicle' НЕ допускаются).
				//C2259: Cannot instantiate abstract class.
				//Instance - экземпляр. Instantiate - создать экземпляр.
	//GroundVehicle gv;
	Car bmw;
	bmw.move();
}

/*
--------------------
//Pure-virtual function (Чисто-виртуальный метод):
virtual type name(parameters)modifiers = 0;
//Прототип функции (Объявление функции - Function declaration)
--------------------
//Реализация функции (Определение функции - Function definition)
virtual type name(parameters)modifiers override
{
	.......;
	group-of-statements;
	.......;
}
--------------------
*/