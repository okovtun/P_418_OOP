#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<list>
#include<ctime>
using std::cin;
using std::cout;
using std::endl;

#define tab			"\t"
#define delimiter	"\n--------------------------------------------\n"

const std::map<int, std::string> OFFENCES =
{
	std::pair<int, std::string>(1, "Парковка в неположенном месте"),
	std::pair<int, std::string>(2, "Непристегнутый ремень безопасности"),
	std::pair<int, std::string>(3, "Превышение скорости"),
	std::pair<int, std::string>(4, "Пересечение сплошной"),
	std::pair<int, std::string>(5, "Вождение в нетрезвом состоянии"),
	std::pair<int, std::string>(6, "Оскорбление офицера"),
	std::pair<int, std::string>(7, "Проезд на красный")
};

class Offence
{
	std::string location;
	tm time;	//Структура 'tm' описывает дату и время.
	int offence;
public:
	const std::string& get_location()const
	{
		return location;
	}
	std::string get_time()const
	{
		return std::asctime(&this->time);
	}
	time_t get_timestamp()const
	{
		tm time = this->time;
		tm* p_time = &time;
		return mktime(p_time);
	}
	int get_offence()const
	{
		return offence;
	}

	//			Constructors:
	Offence(const std::string& location, const char* time, int offence)
	{
		char time_buffer[32] = {};
		strcpy(time_buffer, time);
		this->location = location;
		this->time = {};
		this->get_time_from_string(time_buffer);
		this->offence = offence;
	}
	Offence(const std::string& location, time_t timestamp, int offence)
	{
		this->location = location;
		this->time = *localtime(&timestamp);
		this->offence = offence;
	}

	//			Methods:
	tm get_time_from_string(char* str)
	{
		const char delimiters[] = "./ -:"; //2026.04.29 12:10
		char* dateparts[5] = {};
		int i = 0;
		for (char* pch = strtok(str, delimiters); pch; pch = strtok(NULL, delimiters))
			dateparts[i++] = pch;
		this->time.tm_year = std::atoi(dateparts[0]) - 1900;
		this->time.tm_mon = std::atoi(dateparts[1]) - 1;
		this->time.tm_mday = std::atoi(dateparts[2]);	//'ASCII string' to 'int'
		this->time.tm_hour = std::atoi(dateparts[3]);
		this->time.tm_min = std::atoi(dateparts[4]);
		time_t timestamp = mktime(&this->time);
		this->time = *localtime(&timestamp);
		return this->time;
	}
};
std::ostream& operator<<(std::ostream& os, const Offence& obj)
{
	std::string offence_time = obj.get_time();
	offence_time[offence_time.size() - 1] = 0;
	return	os << offence_time << tab
		<< obj.get_location() << tab
		<< OFFENCES.at(obj.get_offence());
}
std::ofstream& operator<<(std::ofstream& ofs, const Offence& obj)
{
	ofs << obj.get_timestamp() << " " << obj.get_offence() << " " << obj.get_location();
	return ofs;
}

void Print(const std::map<std::string, std::list<Offence>>& base);
void Save(const std::map<std::string, std::list<Offence>>& base, const std::string& filename);

//#define OFFENCE_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef OFFENCE_CHECK
	Offence offence("Улица Ленина", "2026.04.29 11:52", 1);
	cout << offence << endl;

	Offence offence2("Переулок Космический", time(NULL), 2);
	cout << offence2 << endl;
#endif // OFFENCE_CHECK

	std::map<std::string, std::list<Offence>> base =
	{
		std::pair<std::string, std::list<Offence>>("a123bb", {Offence("ул. Ленина", "2023.04.29 12:31", 1), Offence("пер. Космический", "2016.11.16 17:30",2) }),
		std::pair<std::string, std::list<Offence>>("a777bb", {Offence("ул. Октябрьская", "2023.06.29 18:31", 3), Offence("ул. Октябрьская", "2023.06.29 18:31",5), Offence("ул. Октябрьская", "2023.06.29 18:45",6) }),
		std::pair<std::string, std::list<Offence>>("a304bb", {Offence("ул. Парижкой Коммуны", "2015.06.16 18:31", 3), Offence("ул. Парижской Коммуны", "2015.06.29 18:31",4)}),
	};

	Print(base);
	Save(base, "base.txt");

}

void Print(const std::map<std::string, std::list<Offence>>& base)
{
	for (
		std::map<std::string, std::list<Offence>>::const_iterator it = base.begin();
		it != base.end();
		++it
		)
	{
		cout << it->first << ":\n";
		for (
			std::list<Offence>::const_iterator of_it = it->second.begin();
			of_it != it->second.end();
			++of_it
			)
		{
			cout << tab << *of_it << endl;
		}
		cout << delimiter << endl;
	}
}
void Save(const std::map<std::string, std::list<Offence>>& base, const std::string& filename)
{
	std::ofstream fout(filename);
	for (
		std::map<std::string, std::list<Offence>>::const_iterator it = base.begin();
		it != base.end();
		++it
		)
	{
		fout << it->first << ":";
		for (
			std::list<Offence>::const_iterator of_it = it->second.begin();
			of_it != it->second.end();
			++of_it
			)
		{
			fout << *of_it << ",";
		}
		fout.seekp(-1,std::ios::cur);	//Смещаем курсор на один символ влево от текущей позиции курсора (std::ios::cur).
		fout << ";" << endl;;
	}
	fout.close();
	std::string cmd = "notepad ";
	cmd += filename;
	system(cmd.c_str());
}
