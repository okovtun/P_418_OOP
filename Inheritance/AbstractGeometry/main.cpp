#include<Windows.h>
#include<iostream>
using namespace std;

//Enumeration - enum
enum Color
{
	Red = 0x000000FF,	//0x - Hexadecimal
	//bRed= 0000 0000   0000 0000   0000 0000   1111 1111
	Green = 0x0000FF00,
	Blue = 0x00FF0000,
	Yellow = 0x0000FFFF,
	Purple = 0x00800080
};
enum Enum
{
	Sunday,
	Monday,
	Tuesday = 12,
	Wednesday,
	Thursday
};

class Shape
{
	Color color;	//Цвет фигуры
public:
	Shape(Color color) :color(color) {}
	virtual ~Shape() {}
	virtual double get_area() const = 0;	//Pure virtual function
	virtual double get_perimeter() const = 0;
	virtual void draw() const = 0;
	virtual void info() const
	{
		cout << "Площадь фигуры: " << get_area() << endl;
		cout << "Периметр фигуры: " << get_perimeter() << endl;
		draw();
	}
};

class Square :public Shape
{
	double side;
public:
	Square(double side, Color color) :Shape(color)
	{
		this->side = side;
	}
	~Square() {}
	void set_side(double side)
	{
		this->side = side;
	}
	double get_side()const
	{
		return side;
	}
	double get_area() const override
	{
		return side * side;
	}
	double get_perimeter() const override
	{
		return side * 4;
	}
	void draw() const override
	{
		/*for (int i = 0; i < side; i++)
		{
			for (int i = 0; i < side; i++)
			{
				cout << "* ";
			}
			cout << endl;
		}*/

		HWND hwnd = GetConsoleWindow();	//1) Получаем окно консоли, чтобы к нему можно было обращаться
		HDC  hdc = GetDC(hwnd);	//2) Получаем контекст окна консоли. Конетекст - это то, на чем мы будем рисовать.

		//3) Создаем чем мы будем рисовать:
		HPEN hPen = CreatePen(PS_SOLID, 5, Color::Red);	//Карандаш - рисует контур фигуры
		HBRUSH hBrush = CreateSolidBrush(Color::Red);	//Кисть рисует заливку фигуры

		//4) Вышесозданные инструменты нужно выбрать (взять в руки):
		SelectObject(hdc, hPen);
		SelectObject(hdc, hBrush);

		//5) Рисуем фигуру:
		Rectangle(hdc, 300, 300, 500, 500);

		//6) Удаляем инструменты, для того чтобы освободить ресурсы, занимаемые этими инструментами:
		DeleteObject(hBrush);
		DeleteObject(hPen);
		ReleaseDC(hwnd, hdc);
	}
	void info()const override
	{
		cout << typeid(*this).name() + 6 << endl;
		cout << "Длина стороны: " << get_side() << endl;
		Shape::info();
	}
};

void main()
{
	setlocale(LC_ALL, "");
	/*cout << Enum::Monday << endl;
	cout << Enum::Tuesday << endl;
	cout << Enum::Wednesday << endl;
	cout << Enum::Thursday << endl;*/
	//Shape shape = Color::Red;
	Square square(5, Color::Red);
	/*cout << "Сторона квадрата: " << square.get_side() << endl;
	cout << "Площадь фигуры: " << square.get_area() << endl;
	cout << "Периметр фигуры: " << square.get_perimeter() << endl;
	square.draw();*/
	square.info();
}