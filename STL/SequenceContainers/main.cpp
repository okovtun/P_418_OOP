#include<iostream>
#include<array>
#include<vector>
#include<deque>
#include<list>
#include<iterator>
#include<forward_list>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-----------------------------------\n"

template<typename T>void vector_properties(const std::vector<T>& vec)
{
	cout << "Size:    " << vec.size() << endl;		//фактический размер
	cout << "Capacity:" << vec.capacity() << endl;	//вместительность
	cout << "MaxSize: " << vec.max_size() << endl;	//максимально-возможный размер
}
bool less_then_10(const int value)
{
	return value < 10;
}

//#define STL_ARRAY
//#define STL_VECTOR
//#define STL_DEQUE
//#define STL_LIST
#define STL_FORWARD_LIST

void main()
{
	setlocale(LC_ALL, "");

#ifdef STL_ARRAY
	//array - это контейнер, который хранит данные в виде статического массива.
	std::array<int, 5> arr = { 3, 5, 8, 13, 21 };
	for (int i = 0; i < arr.size(); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;
#endif // STL_ARRAY

#ifdef STL_VECTOR
	//vector - это контейнер, который хранит данные в виде динамического массива.
	std::vector<int> i_vec = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34 };
	vector_properties(i_vec);
	i_vec.push_back(55);
	i_vec.push_back(89);
	vector_properties(i_vec);
	i_vec.reserve(25);	//резервирует дополнительную память
	i_vec.shrink_to_fit();	//приравнивает вместительность вектора до его фактического размера
	//i_vec.resize(5);
	//i_vec.resize(15);
	vector_properties(i_vec);
	for (int i = 0; i < i_vec.size(); i++)
	{
		//cout << i_vec[i] << tab;
		cout << i_vec.at(i) << tab;
	}
	cout << endl;
	cout << "Front:\t" << i_vec.front() << endl;
	cout << "Back:\t" << i_vec.back() << endl;
	i_vec.data();	// возвращает RAW-массив, пренадлежащий Вектору.
	//std::vector<double> d_vec;
	//vector_properties(d_vec);
	//	IA-32

	double index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	if (index <= i_vec.size())
		i_vec.insert(i_vec.begin() + index, value);

	for (std::vector<int>::iterator it = i_vec.begin(); it != i_vec.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // STL_VECTOR

#ifdef STL_DEQUE
	//deque - это контейнер, который хрант данные в виде набора динамических массивов.
	//deque может объединять массивы в массив, или в список, в зависимости от реализации.
	//deque - Duble-Ended-Queue
	//На уровне пользователя deque отличается от vector тем, что может добавлять значения
	//непосредственно в начало контейнера.
	std::deque<int> i_deque = { 3, 5, 8, 13, 21 };
	for (int i = 0; i < i_deque.size(); i++)
	{
		cout << i_deque[i] << tab;
	}
	cout << endl;
	i_deque.push_front(1);
	i_deque.push_front(1);
	i_deque.push_front(0);
	i_deque.push_back(34);
	i_deque.push_back(55);
	i_deque.push_back(89);
	for (std::deque<int>::iterator it = i_deque.begin(); it != i_deque.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // STL_DEQUE

#ifdef STL_LIST
	std::list<int> i_list = { 3, 5, 8, 13, 21 };
	/*for (int i = 0; i < i_list.size(); i++)
	{
		cout << i_list[i] << tab;
	}
	cout << endl;*/
	for (std::list<int>::iterator it = i_list.begin(); it != i_list.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
	i_list.push_front(1);
	i_list.push_front(1);
	i_list.push_front(0);

	i_list.push_back(34);
	i_list.push_back(55);
	i_list.push_back(89);

	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	std::list<int>::iterator position = i_list.begin();
	//for (int i = 0; i < index; i++)position++;
	std::advance(position, index);
	i_list.insert(position, value);

	for (int i : i_list)
	{
		cout << i << tab;
	}
	cout << endl;

	for (std::list<int>::reverse_iterator it = i_list.rbegin(); it != i_list.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // STL_LIST

#ifdef STL_FORWARD_LIST
	std::forward_list<int> i_flist = { 3, 5, 8, 13, 21 };
	for (std::forward_list<int>::iterator it = i_flist.begin(); it != i_flist.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
	cout << "Размер списка: " << std::distance(i_flist.begin(), i_flist.end()) << endl;;
	//https://stackoverflow.com/questions/31822494/why-does-stdforward-list-have-no-size-member-function
	//https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2008/n2543.htm

	/*int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	std::forward_list<int>::iterator position = i_flist.begin();
	//for (int i = 0; i < index-1; i++)position++;
	if (index > 0 && index < std::distance(i_flist.begin(), i_flist.end()))
	{
		std::advance(position, index - 1);
		i_flist.insert_after(position, value);
	}*/
	//i_flist.remove(13);
	//i_flist.remove_if(less_then_10);
	[]
	{
		cout << "Hello Lambda" << endl;
	};
	i_flist.remove_if([](const int value)->bool { return value % 2 == 0; });
	for (int i : i_flist)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // STL_FORWARD_LIST


}

/*
-----------------------------------
	[]		()		mutable			throw			->type
	{
		group-of-statements;
	}
[]		- показывают начало lambda-выражения;
()		- список принимаемых параметров;
mutable	- ???
throw	- показывает, бросает ли lambda исключение;
->type	- тип возвращаемого значния;
{}		- тело функции;
-----------------------------------
*/