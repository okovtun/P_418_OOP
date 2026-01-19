#include<Windows.h>
#include<iostream>
using namespace std;

//Enumeration - enum
enum Color
{
	Black = 0x00000000,
	Red = 0x000000FF,	//0x - Hexadecimal
	//bRed= 0000 0000   0000 0000   0000 0000   1111 1111
	Green = 0x0000FF00,
	Blue = 0x00FF0000,
	Yellow = 0x0000FFFF,
	Purple = 0x00800080,
	White = 0x00FFFFFF
};
enum Enum
{
	Sunday,
	Monday,
	Tuesday = 12,
	Wednesday,
	Thursday
};

#define SHAPE_TAKE_PARAMETERS	int start_x, int start_y, int line_width, Color color
#define SHAPE_GIVE_PARAMETERS	start_x, start_y, line_width, color
class Shape
{
	static const int MIN_START_X = 100;
	static const int MIN_START_Y = 100;
	static const int MAX_START_X = 1000;
	static const int MAX_START_Y = 700;
	static const int MIN_LINE_WIDTH = 1;
	static const int MAX_LINE_WIDTH = 32;
	static const int MIN_SIZE = 20;
	static const int MAX_SIZE = 500;
protected:
	Color color;	//Цвет фигуры
	int start_x;
	int start_y;
	int line_width;
public:
	int get_start_x()const
	{
		return start_x;
	}
	int get_start_y()const
	{
		return start_y;
	}
	int get_line_width()const
	{
		return line_width;
	}
	void set_start_x(int start_x)
	{
		//if (start_x < MIN_START_X)start_x = MIN_START_X;
		//if (start_x > MAX_START_X)start_x = MAX_START_X;
		//this->start_x = start_x;
		this->start_x =
			start_x < MIN_START_X ? MIN_START_X :
			start_x > MAX_START_X ? MAX_START_X :
			start_x;
	}
	void set_start_y(int start_y)
	{
		//if (start_y < MIN_START_Y)start_y = MIN_START_Y;
		//if (start_y > MAX_START_Y)start_y = MAX_START_Y;
		//this->start_y = start_y;
		this->start_y =
			start_y < MIN_START_Y ? MIN_START_Y :
			start_y > MAX_START_Y ? MAX_START_Y :
			start_y;
	}
	void set_line_width(int line_width)
	{
		//if (line_width < MIN_LINE_WIDTH)line_width = MIN_LINE_WIDTH;
		//if (line_width > MAX_LINE_WIDTH)line_width = MAX_LINE_WIDTH;
		//this->line_width = line_width;
		this->line_width =
			line_width < MIN_LINE_WIDTH ? MIN_LINE_WIDTH :
			line_width > MAX_LINE_WIDTH ? MAX_LINE_WIDTH :
			line_width;
	}
	double filter_size(double size)
	{
		//if (size < 20)size = 20;
		//if (size > 800)size = 500;
		//return size;
		return
			size < MIN_SIZE ? MIN_SIZE :
			size > MAX_SIZE ? MAX_SIZE :
			size;
	}
	Shape(SHAPE_TAKE_PARAMETERS) :color(color)
	{
		set_start_x(start_x);
		set_start_y(start_y);
		set_line_width(line_width);
	}
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
	Square(double side, SHAPE_TAKE_PARAMETERS):Shape(SHAPE_GIVE_PARAMETERS)
	{
		set_side(side);
	}
	~Square() {}
	void set_side(double side)
	{
		this->side = filter_size(side);
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
		HPEN hPen = CreatePen(PS_SOLID, line_width, color);	//Карандаш - рисует контур фигуры
		HBRUSH hBrush = CreateSolidBrush(color);	//Кисть рисует заливку фигуры

		//4) Вышесозданные инструменты нужно выбрать (взять в руки):
		SelectObject(hdc, hPen);
		SelectObject(hdc, hBrush);

		//5) Рисуем фигуру:
		Rectangle(hdc, start_x, start_y, start_x + side, start_y + side);
		/*
		Функция Rectangle() рисует прямоугольник.
		hdc - это контекст устройства, на котором нужно нарисовать прямоуголник;
		300,300 - координаты вернего-левого угла;
		500,500 - координаты правого-нижнего угла;
		Все координаты всегда задаются в пикселах!!!
		Начало координат всегда находится в левом-верхнем углу экрана;
		Rectangle() является частью библиотеки WinGDI - Windows Graphics Device Interface
		https://learn.microsoft.com/en-us/windows/win32/gdi/windows-gdi
		*/

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
	Square square(50000, -300, -300, 1, Color::White);
	/*cout << "Сторона квадрата: " << square.get_side() << endl;
	cout << "Площадь фигуры: " << square.get_area() << endl;
	cout << "Периметр фигуры: " << square.get_perimeter() << endl;
	square.draw();*/
	square.info();
}