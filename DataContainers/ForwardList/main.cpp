//ForwardList - односвязный список
#include<iostream>
#include<ctime>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-----------------------------------------\n"

class Element
{
	int Data;		//значение элемента
	Element* pNext;	//указатель на следующий элемент
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

	}
	~Element()
	{
		count--;
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

	}
	friend class ForwardList;
};
int Element::count = 0;

class ForwardList
{
	Element* Head;	//Голова списка - является точкой входа в список
	int size;
public:
	int get_size()const
	{
		return size;
	}
	//					Constructors:
	ForwardList()
	{
		//Конструктор по умолчанию создает рустой список
		Head = nullptr;
		//Когда список пуст, его Голова указывает на 0.
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	explicit ForwardList(int size) :ForwardList()
	{
		while (size--)push_front(0);
		cout << "1argLConstructor:\t" << this << endl;
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);*/
		*this = other;
		cout << "LCopyConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//				Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_front(Temp->Data);
		reverse();
		cout << "LCopyAssignment:\t" << this << endl;
		return *this;
	}
	int& operator[](int Index)
	{
		Element* Temp = Head;
		for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}

	//				Adding elements:
	void push_front(int Data)
	{
		////1) Создаем добавляемый элемент:
		//Element* New = new Element(Data);

		////2) Пристыковаем Новый элемент к началу списка:
		//New->pNext = Head;

		////3) Смещаем Голову на Новый элемент:
		//Head = New;

		Head = new Element(Data, Head);

		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);

		//1) Создаем новый элемент:
		//Element* New = new Element(Data);

		//2) Доходим до конца списка:
		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;

		//3) Добавляем элемент в конец списка:
		Temp->pNext = new Element(Data);

		size++;
	}

	void insert(int Data, int Index)
	{
		if (Index == 0) return push_front(Data);

		//1) Создаем новый элемент:
		//Element* New = new Element(Data);

		//2) Доходим до нужного элемента:
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			if (Temp->pNext == nullptr)break;
			Temp = Temp->pNext;
		}

		//3) Добавляем элемент в список:
		//New->pNext = Temp->pNext;
		//Temp->pNext = New;

		Temp->pNext = new Element(Data, Temp->pNext);

		size++;
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

		size--;
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

		size--;
	}

	//				Methods:
	void reverse()
	{
		ForwardList reverse;
		while (Head)
		{
			reverse.push_front(Head->Data);
			pop_front();
		}
		this->Head = reverse.Head;
		reverse.Head = nullptr;
	}
	void print()const
	{
		/*Element* Temp = Head;	//Temp - это Итератор.
		//Итератор - это указатель, при помощи которого можно перемещаться по элементам структуры данных.
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;		//Переход на следующий элемент.
		}*/
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка:" << size << endl;
		cout << "Общее количество элементов: " << Element::count << endl;
		//cout << "Общее количество элементов: " << Head->count << endl;
	}
};

//#define BASE_CHECK
//#define SIZE_CHECK
//#define HOME_WORK_1
//#define COPY_SEMANTIC_CHECK
#define PERFORMANCE_CHECK

void main()
{
	setlocale(LC_ALL, "");
	cout << "Hello ForwardList" << endl;

#ifdef BASE_CHECK
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
#endif // BASE_CHECK

#ifdef SIZE_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);

	list1.print();
	list2.print();
#endif // SIZE_CHECK

#ifdef HOME_WORK_1
	ForwardList list(5);	//Implicit conversion from 'int' to 'ForwardList'
							//Неявное преобразование из 'int' в 'ForwardList'
	list.print();
	for (int i = 0; i < list.get_size(); i++)
	{
		list[i] = rand() % 100;
	}
	for (int i = 0; i < list.get_size(); i++)
	{
		cout << list[i] << tab;
	}
	cout << endl;
#endif // HOME_WORK_1

#ifdef COPY_SEMANTIC_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1 = list1;
	list1.print();

	ForwardList list2 = list1;	//CopyConstructor
	list2.print();
	//ForwardList list2;
//l-value = r-value;
	list2 = list1;		//CopyAssignment
	list2.print();
#endif // COPY_SEMANTIC_CHECK

#ifdef PERFORMANCE_CHECK
	int n;
	cout << "Введите разамер списка: "; cin >> n;
	ForwardList list1;
	clock_t start = clock();	//Функция 'clock()' возвращает количество тактов, и мы сохраняем его в переменную 'start'.
	for (int i = 0; i < n; i++)
	{
		list1.push_front(rand() % 100);
		//list1.push_back(rand() % 100);
	}
	clock_t end = clock();		//Сохраняем количество тактов, потраченных на заполнение списка
	//Теперь разность замеров 'start' и 'end' (end - start) - это время, потраченное на заполнение списка в тактах.
	//Для того чтобы определить время в секундах, нужно промежуток времени в тактах разделить на количество тактов зв 1 секунду.
	//list1.print();
	cout << delimiter << endl;
	cout << "list1 заполнен за " << double(end - start) / CLOCKS_PER_SEC << " секунд" << endl;
	cout << delimiter << endl;
	system("PAUSE");
	start = clock();
	ForwardList list2 = list1;
	end = clock();
	cout << delimiter << endl;
	cout << "list2 скопирован за " << double(end - start) / CLOCKS_PER_SEC << " секунд" << endl;
	cout << delimiter << endl;
	//list2.print();
#endif // PERFORMANCE_CHECK


}