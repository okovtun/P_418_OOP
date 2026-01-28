#define _USE_MATH_DEFINES
#include<Windows.h>
#include<iostream>
using namespace std;

//#define SQUARE_FULL
//#define EQUILATERAL_FULL

namespace Geometry
{
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

#define SHAPE_TAKE_PARAMETERS	int start_x, int start_y, int line_width, Color color, Color fill_color = Color::Black
#define SHAPE_GIVE_PARAMETERS	start_x, start_y, line_width, color, fill_color
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
		Color color;		//Цвет фигуры
		Color fill_color;	//Цвет заливки
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
		Shape(SHAPE_TAKE_PARAMETERS) :color(color), fill_color(fill_color)
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

#ifdef SQUARE_FULL
	class Square :public Shape
	{
		double side;
	public:
		Square(double side, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
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
			HBRUSH hBrush = CreateSolidBrush(fill_color);	//Кисть рисует заливку фигуры

			//4) Вышесозданные инструменты нужно выбрать (взять в руки):
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			//5) Рисуем фигуру:
			::Rectangle(hdc, start_x, start_y, start_x + side, start_y + side);
			::MoveToEx(hdc, start_x, start_y, NULL);
			::LineTo(hdc, start_x + side, start_y + side);
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
#endif // SQUARE_FULL


	class Rectangle :public Shape
	{
		double width;
		double height;
	public:
		double get_width()const
		{
			return width;
		}
		double get_height()const
		{
			return height;
		}
		void set_width(double width)
		{
			this->width = filter_size(width);
		}
		void set_height(double height)
		{
			this->height = filter_size(height);
		}
		Rectangle(double width, double height, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_width(width);
			set_height(height);
		}
		~Rectangle() {}

		double get_area()const override
		{
			return width * height;
		}
		double get_perimeter()const override
		{
			return (width + height) * 2;
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(fill_color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			//	:: - Global Scope;
			::Rectangle(hdc, start_x, start_y, start_x + width, start_y + height);
			::MoveToEx(hdc, start_x, start_y, NULL);
			::LineTo(hdc, start_x + width, start_y + height);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
	};
	class Square :public Rectangle
	{
	public:
		Square(double side, SHAPE_TAKE_PARAMETERS) :Rectangle(side, side, SHAPE_GIVE_PARAMETERS) {}
		~Square() {}
	};

	class Circle :public Shape
	{
		double radius;
	public:
		double get_radius()const
		{
			return radius;
		}
		void set_radius(double radius)
		{
			this->radius = filter_size(radius);
		}
		//			Constructors:
		Circle(double radius, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_radius(radius);
		}
		~Circle() {}
		double get_area()const override
		{
			return M_PI * radius*radius;
		}
		double get_perimeter()const override
		{
			return 2 * M_PI*radius;
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(fill_color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			Ellipse(hdc, start_x, start_y, start_x + 2 * radius, start_y + 2 * radius);

			MoveToEx(hdc, start_x + radius, start_y + radius, NULL);
			LineTo(hdc, (start_x + radius * 2), (start_y + radius));

			MoveToEx(hdc, start_x + radius, start_y + radius, NULL);
			int degree = 30;
			double angle = -degree * M_PI / 180;
			LineTo(hdc, (start_x + radius) + radius * cos(angle), (start_y + radius) + radius * sin(angle));

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
	};
	class Triangle :public Shape
	{
	public:
		Triangle(SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS) {}
		~Triangle() {}
		virtual double get_height()const = 0;
		void info()const override
		{
			cout << "Высота треугольника: " << get_height() << endl;
			Shape::info();
		}
	};
#ifdef EQUILATERAL_FULL
	class EquilateralTriangle :public Triangle
	{
		double side;
	public:
		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			this->side = filter_size(side);
		}
		EquilateralTriangle(double side, SHAPE_TAKE_PARAMETERS) :Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_side(side);
		}
		~EquilateralTriangle() {}
		double get_height()const override
		{
			return sqrt(pow(side, 2) - pow(side / 2, 2));
		}
		double get_area()const override
		{
			return side / 2 * get_height();
		}
		double get_perimeter()const override
		{
			return 3 * side;
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(fill_color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			//https://learn.microsoft.com/en-us/windows/win32/gdi/about-polygons
			POINT vertices[] =
			{
				{start_x + side / 2,start_y},
				{start_x + side,start_y + get_height()},
				{start_x,start_y + get_height()},
			};
			Polygon(hdc, vertices, 3);

			MoveToEx(hdc, start_x + side / 2, start_y, NULL);
			LineTo(hdc, start_x + side / 2, start_y + get_height());

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
	};
#endif // EQUILATERAL_FULL

	class IsoscelesTriangle :public Triangle
	{
		double base;
		double side;
	public:
		double get_base()const
		{
			return base;
		}
		double get_side()const
		{
			return side;
		}
		void set_base(double base)
		{
			this->base = filter_size(base);
		}
		void set_side(double side)
		{
			this->side = filter_size(side);
		}
		IsoscelesTriangle(double base, double side, SHAPE_TAKE_PARAMETERS) :Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_base(base);
			set_side(side);
		}
		~IsoscelesTriangle() {}
		double get_height()const override
		{
			return sqrt(pow(side, 2) - pow(base / 2, 2));
		}
		double get_area()const override
		{
			return base / 2 * get_height();
		}
		double get_perimeter()const override
		{
			return base + 2 * side;
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(fill_color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			//https://learn.microsoft.com/en-us/windows/win32/gdi/about-polygons
			POINT vertices[] =
			{
				{start_x + base / 2, start_y},
				{start_x + base, start_y + get_height()},
				{start_x, start_y + get_height()},
			};
			Polygon(hdc, vertices, 3);

			MoveToEx(hdc, start_x + base / 2, start_y, NULL);
			LineTo(hdc, start_x + base / 2, start_y + get_height());

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
	};
	class EquilateralTriangle :public IsoscelesTriangle
	{
	public:
		EquilateralTriangle(double side, SHAPE_TAKE_PARAMETERS) :IsoscelesTriangle(side, side, SHAPE_GIVE_PARAMETERS) {}
		~EquilateralTriangle() {}
	};

	class RightTriangle :public Triangle
	{
		double cathet_1;
		double cathet_2;
	public:
		double get_cathet_1()const
		{
			return cathet_1;
		}
		double get_cathet_2()const
		{
			return cathet_2;
		}
		double get_hypotenuse()const
		{
			return sqrt(cathet_1*cathet_1 + cathet_2 * cathet_2);
		}
		void set_cathet_1(double cathet_1)
		{
			this->cathet_1 = filter_size(cathet_1);
		}
		void set_cathet_2(double cathet_2)
		{
			this->cathet_2 = filter_size(cathet_2);
		}
		RightTriangle(double cathet_1, double cathet_2, SHAPE_TAKE_PARAMETERS) :Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_cathet_1(cathet_1);
			set_cathet_2(cathet_2);
		}
		~RightTriangle() {}
		double get_height()const override
		{
			return cathet_1 * cathet_2 / get_hypotenuse();
		}
		double get_area()const override
		{
			return cathet_1 * cathet_2 / 2;
		}
		double get_perimeter()const override
		{
			return cathet_1 + cathet_2 + get_hypotenuse();
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(fill_color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT vertices[] =
			{
				{start_x, start_y},
				{start_x, start_y + cathet_2},
				{start_x + cathet_1, start_y + cathet_2},
			};
			Polygon(hdc, vertices, 3);

			MoveToEx(hdc, start_x, start_y + cathet_2, NULL);
			/*double cat2_oposite_angle = asin(cathet_2 / get_hypotenuse())/M_PI* 180 ;
			double height_right_angle = 180 - 90 - cat2_oposite_angle;
			double height = get_height();
			double target_x = get_height()*sin(90-height_right_angle*M_PI / 180);
			double target_y = get_height()*cos(90-height_right_angle*M_PI / 180);
			LineTo(hdc, start_x+target_x, start_y+target_y);*/

			RightTriangle tri_1(cathet_1*cathet_1 / get_hypotenuse(), get_height(), 0, 0, 0, Color::Black);
			RightTriangle tri_2(get_height(), cathet_2*cathet_2 / get_hypotenuse(), 0, 0, 0, Color::Black);
			//RightTriangle tri_22(tri_2.get_height(), tri_2.cathet_2*tri_2.cathet_2 / tri_2.get_hypotenuse(), 0, 0, 0, Color::Black);
			//LineTo(hdc, start_x + tri_2.get_height(), start_y + tri_22.cathet_2);
			LineTo(hdc, start_x + tri_2.get_height(), start_y + cathet_2 - tri_1.get_height());

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
	};
}

void main()
{
	setlocale(LC_ALL, "");
	/*cout << Enum::Monday << endl;
	cout << Enum::Tuesday << endl;
	cout << Enum::Wednesday << endl;
	cout << Enum::Thursday << endl;*/
	//Shape shape = Color::Red;
	Geometry::Square square(250, -300, -300, 1, Geometry::Color::White);
	/*cout << "Сторона квадрата: " << square.get_side() << endl;
	cout << "Площадь фигуры: " << square.get_area() << endl;
	cout << "Периметр фигуры: " << square.get_perimeter() << endl;
	square.draw();*/
	square.info();

	Geometry::Rectangle rect(200, 100, 400, 100, 5, Geometry::Color::Red);
	rect.info();

	Geometry::Circle circle(150, 700, 100, 5, Geometry::Color::Yellow);
	circle.info();

	Geometry::EquilateralTriangle e_triangle(180, 450, 250, 18, Geometry::Color::Green, Geometry::Color::Green);
	e_triangle.info();

	Geometry::IsoscelesTriangle iso_triangle(100, 180, 700, 400, 8, Geometry::Color::Purple);
	iso_triangle.draw();

	Geometry::RightTriangle r_triangle(300, 150, 850, 420, 5, Geometry::Color::White);
	r_triangle.info();
	//instance - экземпляр;
	//instantiate - создать экземпляр;
	while (true)
	{
		square.draw();
		rect.draw();
		circle.draw();
		iso_triangle.draw();
		r_triangle.draw();
	}
}