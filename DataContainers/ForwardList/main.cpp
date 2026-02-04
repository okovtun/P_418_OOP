//ForwardList - односвязный список
#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-----------------------------------------\n"

class Element
{
	int Data;		//значение элемента
	Element* pNext;	//указатель на следующий элемент
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};
class ForwardList
{
	Element* Head;	//Голова списка - является точкой входа в список
public:
	ForwardList()
	{
		//Конструктор по умолчанию создает рустой список
		Head = nullptr;
		//Когда список пуст, его Голова указывает на 0.
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}

	//				Adding elements:
	void push_front(int Data)
	{
		//1) Создаем добавляемый элемент:
		Element* New = new Element(Data);

		//2) Пристыковаем Новый элемент к началу списка:
		New->pNext = Head;

		//3) Смещаем Голову на Новый элемент:
		Head = New;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);

		//1) Создаем новый элемент:
		Element* New = new Element(Data);

		//2) Доходим до конца списка:
		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;

		//3) Добавляем элемент в конец списка:
		Temp->pNext = New;
	}

	void insert(int Data, int Index)
	{
		if (Index == 0) return push_front(Data);

		//1) Создаем новый элемент:
		Element* New = new Element(Data);

		//2) Доходим до нужного элемента:
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			if (Temp->pNext == nullptr)break;
			Temp = Temp->pNext;
		}

		//3) Добавляем элемент в список:
		New->pNext = Temp->pNext;
		Temp->pNext = New;
	}

	//				Removing elements:
	void pop_front()
	{
		//1) Запоминаем адрес удаляемого элемента:
		Element* Erased = Head;

		//2) Смещаем Голову на следующий элемент:
		Head = Head->pNext;

		//3) Удаляем удаляемый элемент из памяти:
		delete Erased;
	}
	void pop_back()
	{
		//1) Доходим до предпоследнего элемента списка:
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;

		//2) Удаляем удаляемый элемент:
		delete Temp->pNext;

		//3) Зануляем указатель на последний элемент в предпоследнем элементе:
		Temp->pNext = nullptr;
	}

	//				Methods:
	void print()const
	{
		Element* Temp = Head;	//Temp - это Итератор.
		//Итератор - это указатель, при помощи которого можно перемещаться по элементам структуры данных.
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;		//Переход на следующий элемент.
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");
	cout << "Hello ForwardList" << endl;

	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	//list.push_back(123);
	//list.pop_front();
	//list.pop_back();
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
}