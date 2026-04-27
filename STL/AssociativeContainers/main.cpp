#include<iostream>
#include<string>
#include<map>
#include<set>
using std::cin;
using std::cout;
using std::endl;

#define tab			"\t"
#define delimiter	"\n-----------------------------------------------\n"

/*
---------------------------------
Все ассоциативные контейнеры хранят данные в виде Бинарного дерева поиска.
---------------------------------
*/

class MyInt
{
	int value;
public:
	MyInt(int value = 0) :value(value) {}
	~MyInt() {}
	bool operator<(const MyInt& other)const
	{
		return this->value < other.value;
	}
	friend std::ostream& operator<<(std::ostream& os, const MyInt& obj)
	{
		return os << obj.value;
	}
};

//#define STL_MAP_1
//#define STL_SET
#define STL_MAP_2

void main()
{
	setlocale(LC_ALL, "");

#ifdef STL_MAP_1
	/*
	-----------------------------------
	map - это контейнер, каждый элемент которого хранит пару <ключ, значение> - <key, value>.
	map является уникальным контейнером, т.е., не позволяет добавить два значения с одинаковым ключем,
	если есть такая необходимость, то нужно использовать multimap, который позволяет дублировать ключи.
	-----------------------------------
	*/
	std::map<int, std::string> weekdays =
	{
		std::pair<int,std::string>(1, "Monday"),
		std::pair<int,std::string>(2, "Tuesday"),
		std::pair<int,std::string>(3, "Wednesday"),
		std::pair<int,std::string>(4, "Thursday"),
		std::pair<int,std::string>(5, "Friday"),
		std::pair<int,std::string>(5, "Friday"),
		std::pair<int,std::string>(5, "Friday"),
		std::pair<int,std::string>(5, "Friday"),
		std::pair<int,std::string>(5, "Friday"),
		std::pair<int,std::string>(5, "Friday"),
		std::pair<int,std::string>(5, "Friday"),
		std::pair<int,std::string>(6, "Saturday"),
		std::pair<int,std::string>(7, "Sunday"),
	};

	for (std::multimap<int, std::string>::iterator it = weekdays.begin(); it != weekdays.end(); ++it)
	{
		cout << it->first << "\t" << it->second << endl;
	}
#endif // STL_MAP_1

#ifdef STL_SET
	/*
	---------------------------------
	set - это контейнер, у которого ключ и значение объединены.
	Он так же использует Бинарное дерево для хранения данных.
	---------------------------------
	*/
	std::set<int> i_set = { 50, 25, 75, 16, 32, 58, 85 };
	for (std::set<int>::iterator it = i_set.begin(); it != i_set.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;

	MyInt a = 5;
	cout << a << endl;

	std::set<MyInt> my_set = { 50, 25, 75, 16, 32, 58, 85 };
	for (std::set<MyInt>::iterator it = my_set.begin(); it != my_set.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;

#endif // STL_SET

#ifdef STL_MAP_2

#endif // STL_MAP_2

}
