#include<iostream>
using namespace std;

class Point
{
	double x;
	double y;
public:
	double get_x()const
	{
		//x = 0;
		return x;
	}
	double get_y()const
	{
		return y;
	}
	void set_x(double x)
	{
		this->x = x;
		//this - это указатель на объект, для которого вызывается метод.
	}
	void set_y(double y)
	{
		this->y = y;
	}

	//			Methods:
	double distance(Point other)
	{
		double x_distance = this->x - other.x;
		double y_distance = this->y - other.y;
		double distance = sqrt(x_distance*x_distance + y_distance*y_distance);	//Square Root
		return distance;
	}
};

double distance(Point A, Point B)
{
	double x_distance = A.get_x() - B.get_x();
	double y_distance = A.get_y() - B.get_y();
	double distance = sqrt(x_distance*x_distance + y_distance * y_distance);
	return distance;
}

//#define STRUCT_POINT
//#define DISTANCE_CHECK
#define FOR_COUNTER_LIFETIME

void main()
{
	setlocale(LC_ALL, "");

#ifdef STRUCT_POINT
	cout << "Hello OOP" << endl;
	int a;		//Объявление переменной 'a' типа 'int'.
	Point A;	//Объявление переменной 'A' типа 'Point'.
				//Объявление объекта 'A' структуры 'Point'.
				//Создание экземпляра 'A' структуры 'Point'.
	A.x = 2;
	A.y = 3;
	cout << A.x << "\t" << A.y << endl;

	Point* pA = &A;	//Объявляем указатель на объект 'A'
	cout << pA->x << "\t" << pA->y << endl;
#endif // STRUCT_POINT

#ifdef DISTANCE_CHECK
	Point A;
	A.set_x(2);
	A.set_y(3);
	cout << A.get_x() << "\t" << A.get_y() << endl;

	Point B;
	B.set_x(7);
	B.set_y(8);
	cout << B.get_x() << "\t" << B.get_y() << endl;

	cout << "Расстояние от точки 'A' до точки 'B':" << A.distance(B) << endl;
	cout << "Расстояние от точки 'B' до точки 'A':" << B.distance(A) << endl;
	cout << "Расстояние между точками 'A' и 'B':  " << distance(A, B) << endl;
	cout << "Расстояние между точками 'B' и 'A':  " << distance(B, A) << endl;
#endif // DISTANCE_CHECK

#ifdef FOR_COUNTER_LIFETIME
	for (int i = 0; i < 10; i++)
	{
		cout << i << "\t";
	}
	//Если бы переменная 'i' была объектом, то по звершении всех итераций для нее был бы вызван Destructor,
	//поскольку время жизни переменной 'i' завершается по завершении всех итераций цикла 'for'.
	cout << endl;
#endif // FOR_COUNTER_LIFETIME

}

/*
-----------------------------------------
.  - Оператор прямого доступа (Point operator)
-> - Оператор косвенного доступа (Arrow operator)
-----------------------------------------
*/

/*
-----------------------------------------
1. Модификаторы доступа:
	private:	закрытые поля, доступны только внутри класса;
	public:		открытые поля, доступны из любого места программы;
	protected:	защищенные поля, этот модификатор доступа работает
				только при наследовании.
				protected-поля доступны только внутри класса и его дочерних классов;
2. Get/Set-методы:
	get-методы (get - взять, получить)		- открывают доступ к переменным членам класса на чтение,
				т.е., позволяют получить значения закрытых переменных.
	set-методы (set - задать, установить)	- открывают доступ к закрытым переменным класса на запись,
				т.е., позволяют задавать значения закрытым переменным. Кроме того, set-методы
				обеспечивают фильтрацию данных, т.е., предотвращают попадание некорректных значений
				в переменные члены класса.
-----------------------------------------
*/

/*
-----------------------------------------
		Special members:
1. Constructor - это метод, который создает объект,
				 а именно, 
				 выделяет память под объект, 
				 и инициализирует его поля;
	Конструкторы бывают:
		- с параметрами;
		- без параметров;
		- по умолчанию - это конструктор, который может быть вызван без параметров;
		- конструктор копирования;
		- конструктор переноса;
2. ~Destructor - это метод, который уничтожает объект 
				 по завершении его времени жизни;
3. Assignment operator;
-----------------------------------------
*/