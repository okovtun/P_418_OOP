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
	friend class Iterator;
	friend class ConstIterator;
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};
int Element::count = 0;

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) :Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "ItDestructor:\t" << this << endl;
	}
	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator operator++(int)
	{
		Iterator old = *this;
		Temp = Temp->pNext;
		return old;
	}
	bool operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}
	int& operator*()
	{
		return Temp->Data;
	}
};
class ConstIterator
{
	Element* Temp;
public:
	ConstIterator(Element* Temp = nullptr) :Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	~ConstIterator()
	{
		cout << "ItDestructor:\t" << this << endl;
	}
	ConstIterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	ConstIterator operator++(int)
	{
		ConstIterator old = *this;
		Temp = Temp->pNext;
		return old;
	}
	bool operator==(const ConstIterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const ConstIterator& other)const
	{
		return this->Temp != other.Temp;
	}
	int operator*()const
	{
		return Temp->Data;
	}
};

class ForwardList
{
	Element* Head;	//Голова списка - является точкой входа в список
	int size;
public:
	Element* get_head()const
	{
		return Head;
	}
	int get_size()const
	{
		return size;
	}
	ConstIterator begin()const
	{
		return Head;
	}
	ConstIterator end()const
	{
		return nullptr;
	}
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
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
	ForwardList(const std::initializer_list<int>& il) :ForwardList()
	{
		//begin() - возвращает Итератор на начало контейнера;
		//end()   - возвращает Итератор на конец контейнера;
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		//Deep copy
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);*/
		*this = other;
		cout << "LCopyConstructor:\t" << this << endl;
	}
	ForwardList(ForwardList&& other):ForwardList()
	{
		//Shallow copy:
		/*this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;*/
		*this = std::move(other);	//Метод 'std::move()' вызывает MoveAssignment.
		cout << "LMoveConstructor:\t" << this << endl;
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
	ForwardList& operator=(ForwardList&& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "LMoveAssignment:\t" << this << endl;
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

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList result = left;	//CopyConstructor
	//for (Element* Temp = right.get_head(); Temp; Temp = Temp->pNext)result.push_back(Temp->Data);
	for (ConstIterator it = right.begin(); it != right.end(); ++it)
	{
		//*it *= 100;
		result.push_back(*it);
	}
	return result;
}

//#define BASE_CHECK
//#define SIZE_CHECK
//#define HOME_WORK_1
//#define COPY_SEMANTIC_CHECK
//#define PERFORMANCE_CHECK
//#define MOVE_SEMANTIC_CHECK
//#define RANGE_BASED_FOR_ARRAY
//#define RANGE_BASED_FOR_LIST

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

#ifdef MOVE_SEMANTIC_CHECK
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

	cout << delimiter << endl;
	ForwardList list3 = list1 + list2;
	cout << delimiter << endl;
	list3.print();
#endif // MOVE_SEMANTIC_CHECK

#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3, 5, 8, 13, 21 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

	//Range-based for (for для контейнеров)
	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_ARRAY

#ifdef RANGE_BASED_FOR_LIST
	ForwardList list = { 3, 5, 8, 13, 21 };
	//list.print();
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;

	for (Iterator it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_LIST

	ForwardList list1 = { 3, 5, 8, 13, 21 };
	ForwardList list2 = { 34, 55, 89 };
	ForwardList list3 = list1 + list2;
	for (int i : list1) cout << i << tab; cout << endl;
	for (int i : list2) cout << i << tab; cout << endl;
	for (int i : list3) cout << i << tab; cout << endl;
}