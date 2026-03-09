//ForwardList - односвязный список
#include<iostream>
#include<string>
#include<ctime>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-----------------------------------------\n"

template<typename T>class ForwardList;
template<typename T>class Iterator;
template<typename T>class ConstIterator;

template<typename T>class Element
{
	T Data;		//значение элемента
	Element<T>* pNext;	//указатель на следующий элемент
	static int count;
public:
	Element(T Data, Element<T>* pNext = nullptr) :Data(Data), pNext(pNext)
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
	friend class ForwardList<T>;
	friend class Iterator<T>;
	friend class ConstIterator<T>;
	friend ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right);
};
template<typename T>int Element<T>::count = 0;

template<typename T>class Iterator
{
	Element<T>* Temp;
public:
	Iterator(Element<T>* Temp = nullptr) :Temp(Temp)
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
		Iterator<T> old = *this;
		Temp = Temp->pNext;
		return old;
	}
	bool operator==(const Iterator<T>& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator<T>& other)const
	{
		return this->Temp != other.Temp;
	}
	T& operator*()
	{
		return Temp->Data;
	}
};

template<typename T>class ConstIterator
{
	Element<T>* Temp;
public:
	ConstIterator(Element<T>* Temp = nullptr) :Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	~ConstIterator()
	{
		cout << "ItDestructor:\t" << this << endl;
	}
	ConstIterator<T>& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	ConstIterator<T> operator++(int)
	{
		ConstIterator<T> old = *this;
		Temp = Temp->pNext;
		return old;
	}
	bool operator==(const ConstIterator<T>& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const ConstIterator<T>& other)const
	{
		return this->Temp != other.Temp;
	}
	T operator*()const
	{
		return Temp->Data;
	}
};

template<typename T>class ForwardList
{
	Element<T>* Head;	//Голова списка - является точкой входа в список
	int size;
public:
	Element<T>* get_head()const;
	int get_size()const;
	ConstIterator<T> begin()const;
	ConstIterator<T> end()const;
	Iterator<T> begin();
	Iterator<T> end();

	//					Constructors:
	ForwardList();
	explicit ForwardList(int size);
	ForwardList(const std::initializer_list<T>& il);
	ForwardList(const ForwardList<T>& other);
	ForwardList(ForwardList<T>&& other);
	~ForwardList();

	//				Operators:
	ForwardList<T>& operator=(const ForwardList<T>& other);
	ForwardList<T>& operator=(ForwardList<T>&& other);
	T& operator[](int Index);

	//				Adding elements:
	void push_front(T Data);
	void push_back(T Data);
	void insert(T Data, int Index);

	//				Removing elements:
	void pop_front();
	void pop_back();

	//				Methods:
	void reverse();
	void print()const;
};
Element<T>* get_head()const
{
	return Head;
}
int get_size()const
{
	return size;
}
ConstIterator<T> begin()const
{
	return Head;
}
ConstIterator<T> end()const
{
	return nullptr;
}
Iterator<T> begin()
{
	return Head;
}
Iterator<T> end()
{
	return nullptr;
}

//					Constructors:
template<typename T>ForwardList<T>::ForwardList()
{
	//Конструктор по умолчанию создает рустой список
	Head = nullptr;
	//Когда список пуст, его Голова указывает на 0.
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}
template<typename T>explicit ForwardList<T>::ForwardList(int size) :ForwardList()
{
	while (size--)push_front(0);
	cout << "1argLConstructor:\t" << this << endl;
}
ForwardList(const std::initializer_list<T>& il) :ForwardList()
{
	//begin() - возвращает Итератор на начало контейнера;
	//end()   - возвращает Итератор на конец контейнера;
	cout << typeid(il.begin()).name() << endl;
	for (T const* it = il.begin(); it != il.end(); it++)
	{
		push_back(*it);
	}
}
ForwardList(const ForwardList<T>& other) :ForwardList()
{
	//Deep copy
	/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
		push_back(Temp->Data);*/
	*this = other;
	cout << "LCopyConstructor:\t" << this << endl;
}
ForwardList(ForwardList<T>&& other) :ForwardList()
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
ForwardList<T>& operator=(const ForwardList<T>& other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext)
		push_front(Temp->Data);
	reverse();
	cout << "LCopyAssignment:\t" << this << endl;
	return *this;
}
ForwardList<T>& operator=(ForwardList<T>&& other)
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
T& operator[](int Index)
{
	Element<T>* Temp = Head;
	for (int i = 0; i < Index; i++)Temp = Temp->pNext;
	return Temp->Data;
}

//				Adding elements:
void push_front(T Data)
{
	Head = new Element<T>(Data, Head);
	size++;
}
void push_back(T Data)
{
	if (Head == nullptr)return push_front(Data);

	//1) Создаем новый элемент:
	//Element* New = new Element(Data);

	//2) Доходим до конца списка:
	Element<T>* Temp = Head;
	while (Temp->pNext)Temp = Temp->pNext;

	//3) Добавляем элемент в конец списка:
	Temp->pNext = new Element<T>(Data);

	size++;
}

void insert(T Data, int Index)
{
	if (Index == 0) return push_front(Data);

	Element<T>* Temp = Head;
	for (int i = 0; i < Index - 1; i++)
	{
		if (Temp->pNext == nullptr)break;
		Temp = Temp->pNext;
	}
	Temp->pNext = new Element<T>(Data, Temp->pNext);
	size++;
}

//				Removing elements:
void pop_front()
{
	//1) Запоминаем адрес удаляемого элемента:
	Element<T>* Erased = Head;

	//2) Смещаем Голову на следующий элемент:
	Head = Head->pNext;

	//3) Удаляем удаляемый элемент из памяти:
	delete Erased;

	size--;
}
void pop_back()
{
	//1) Доходим до предпоследнего элемента списка:
	Element<T>* Temp = Head;
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
	ForwardList<T> reverse;
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
	for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количество элементов списка:" << size << endl;
	cout << "Общее количество элементов: " << Element<T>::count << endl;
	//cout << "Общее количество элементов: " << Head->count << endl;
}
template<typename T>ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right)
{
	ForwardList<T> result = left;	//CopyConstructor
	//for (Element* Temp = right.get_head(); Temp; Temp = Temp->pNext)result.push_back(Temp->Data);
	for (ConstIterator<T> it = right.begin(); it != right.end(); ++it)
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

	ForwardList<int> list1 = { 3, 5, 8, 13, 21 };
	ForwardList<int> list2 = { 34, 55, 89 };
	ForwardList<int> list3 = list1 + list2;
	for (int i : list1) cout << i << tab; cout << endl;
	for (int i : list2) cout << i << tab; cout << endl;
	for (int i : list3) cout << i << tab; cout << endl;
	cout << delimiter << endl;

	//TODO: need check on different types

	ForwardList<double> d_list_1 = { 2.7, 3.14, 1.8, 5.2 };
	ForwardList<double> d_list_2 = { 8.33, 9.11, 7.55 };
	ForwardList<double> d_list_3 = d_list_1 + d_list_2;
	for (double i : d_list_1)cout << i << tab; cout << endl;
	for (double i : d_list_2)cout << i << tab; cout << endl;
	for (double i : d_list_3)cout << i << tab; cout << endl;
	cout << delimiter << endl;

	ForwardList<std::string> s_list_1 = { "Хорошо", "живет", "на", "свете", "Винни", "Пух" };
	ForwardList<std::string> s_list_2 = { "И", "Пятачек", "тоже" };
	ForwardList<std::string> s_list_3 = s_list_1 + s_list_2;
	for (std::string i : s_list_1)cout << i << tab; cout << endl;
	for (std::string i : s_list_2)cout << i << tab; cout << endl;
	for (std::string i : s_list_3)cout << i << tab; cout << endl;

	/*uint8_t ui8t = 49;
	cout << ui8t << endl;*/
	
}