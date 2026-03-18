#pragma once
#include<iostream>
#include<string>
using std::cin;
using std::cout;
using std::endl;

#define tab			"\t"
#define delimiter	"\n----------------------------------------------\n"

//Class - обычный класс;
//Class<T> - шаблонный класс;
//Class<int> obj1;		//шаблонные пол€ будут типа 'int';
//Class<double> obj2;	//шаблонные пол€ будут типа 'double';

////////////////////////////////////////////////////////////////////////////////////////////////////
////////					Class declaration	(ќбъ€вление класса)							////////

template<typename T>class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List;
	}*Head, *Tail;//Ёкземпл€ры класса можно объ€вл€ть непосредственно после описани€ класса
	//ќдним выражением можно объ€вить несколько переменных одного типа, один раз указав тип данных,
	//и перечислив имена объ€вл€емых переменных через зап€тую.
	size_t size;//size_t - это typedef на 'unsigned int'.
	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr) :Temp(Temp) {}
		~ConstBaseIterator() {}
		bool operator==(const ConstBaseIterator& other)const;
		bool operator!=(const ConstBaseIterator& other)const;
		T operator*()const;
	};
public:
	class ConstIterator :public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp) {}
		~ConstIterator() {}

		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);
	};
	class ConstReverseIterator :public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp) {}
		~ConstReverseIterator() {}

		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator operator--(int);
	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) :ConstIterator(Temp) {}
		~Iterator() {}
		T& operator*();
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp) :ConstReverseIterator(Temp) {}
		~ReverseIterator() {}
		T& operator*();
	};
	ConstIterator cbegin()const;
	ConstIterator cend()const;
	ConstReverseIterator crbegin()const;
	ConstReverseIterator crend()const;
	Iterator begin();
	Iterator end();
	ReverseIterator rbegin();
	ReverseIterator rend();

	List();
	List(const std::initializer_list<T>& il);
	~List();

	//				Adding elements:
	void push_front(T Data);
	void push_back(T Data);
	void insert(T Data, int Index);

	//				Removing elements:
	void pop_front();
	void pop_back();
	void erase(int index);

	//				Methods:
	void print()const;
	void reverse_print()const;
};

////////				Class declaration end	( онец объ€влени€ класса)					////////
////////////////////////////////////////////////////////////////////////////////////////////////////
