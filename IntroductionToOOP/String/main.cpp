#include"String.h"
//#define BASE_CHECK
#define OPERATORS_CHECK
//#define CALLING_CONSTRUCTORS

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	String str(12);	//Conversion from 'int' to 'String'
//str.print();
	cout << str << endl;

	String str1 = "Hello";
	str1 = str1;
	str1.print();
	cout << str1 << endl;

	String str2 = str1;		//Copy constructor
	cout << str2 << endl;

	String str3;
	str3 = str2;			//CopyAssignment
	cout << str3 << endl;
#endif // BASE_CHECK

#ifdef OPERATORS_CHECK
	int a = 2;
	int b = 3;
	a + b;
	String str1 = "Hello";
	String str2 = "World";

	cout << delimiter << endl;
	//String str3 = str1 + str2;	//MoveConstructor
	String str3;
	str3 = str1 + str2;				//MoveAssignment
	cout << delimiter << endl;
	
	cout << str3 << endl;
#endif // OPERATORS_CHECK

#ifdef CALLING_CONSTRUCTORS
	String str1;		//Default constructor
	str1.print();

	String str2(5);		//Single-argument constructor int (explicit)
	str2.print();

	String str3 = "Hello";	//Singl-argument constructor 'const char*'
	str3.print();

	String str4();		//NOT Default constructor - это выражение НЕ вызывает никакой конструктор,
						//и НЕ создает объект, это выражение объявляет функцию, 
						//которая ничего НЕ принимает, и возвращает значене типа 'String'
	//str4.print();		//'str4' НЕ является объектом.
	//Для того чтобы явно вызвать конструктор по умолчанию, можно использовать {} следующим образом:
	String str5{};		//Явный вызов конструктора по умолчанию
	str5.print();
	//НО, с фигурными скобками нужно быть ОЧЕНЬ ОСТОРОЖНЫМ
	//Фигурные скобки как правило используются в контейнерах.

	String str6{ 7 };	//Так же как 'str2' вызывает конструктор с одним параметром типа 'int'
	str6.print();

	String str7("World");//Так же как и 'str3' вызывает конструктор с одним параметром типа 'const char*'
	String str8{ "World" };//Так же как и 'str3' вызывает конструктор с одним параметром типа 'const char*'

	String str9 = str3;	//CopyConstructor
	String str10(str9);	//CopyConstrcutor
	String str11{ str9 };//CopyConstructor
	str11.print();

	String str12 = str3 + str7;	//MoveConstructor
	str12.print();

	String str13(str3 + str7);	//MoveConstructor
	str13.print();

	String str14{ str3 + str7 };//MoveConstructor
	str14.print();
#endif // CALLING_CONSTRUCTORS

}

//Deep copy
//Shallow copy
//Debug Assertion Failed
//Memory Leak

//Move semantic:
//Move constructor
//Move assignment