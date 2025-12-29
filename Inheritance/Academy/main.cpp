#include<iostream>
#include<fstream>
#include<string>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-------------------------------------------------------\n"

class Human
{
	static const int LAST_NAME_WIDTH = 12;
	static const int FIRST_NAME_WIDTH = 12;
	static const int AGE_WIDTH = 3;
	static int count;
	std::string last_name;
	std::string first_name;
	int age;
public:
	static int get_count()
	{
		return count;
	}
	const std::string& get_last_name()const
	{
		return last_name;
	}
	const std::string& get_first_name()const
	{
		return first_name;
	}
	int get_age()const
	{
		return age;
	}
	void set_last_name(const std::string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const std::string& first_name)
	{
		this->first_name = first_name;
	}
	void set_age(int age)
	{
		this->age = age;
	}
	//				Constructors:
	Human(const std::string& last_name, const std::string& first_name, int age)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		count++;
		cout << "HConstructor:\t" << this << endl;
	}
	virtual ~Human()
	{
		count--;
		cout << "HDestructor:\t" << this << endl;
	}
	virtual std::ostream& info(std::ostream& os)const
	{
		//return os << last_name << " " << first_name << " " << age;
		os.width(11);
		os << std::left;//задаем выравнивание по левому кураю
		os << std::string(typeid(*this).name() + 6) + ":";
		os.width(LAST_NAME_WIDTH);	//задаем ширину вывода, т.е., сколько знакопозиций будет занимать следующее выводимое значение
		os << last_name;
		os.width(FIRST_NAME_WIDTH);
		os << first_name;
		os.width(AGE_WIDTH);
		os << age;
		return os;
	}
	virtual std::ofstream& write(std::ofstream& ofs)const
	{
		ofs << typeid(*this).name() + 6 << ":";
		ofs << last_name << " " << first_name << " " << age;
		return ofs;
	}
	virtual std::ifstream& read(std::ifstream& ifs)
	{
		ifs >> last_name >> first_name >> age;
		return ifs;
	}
};
int Human::count = 0;

std::ostream& operator<<(std::ostream& os, const Human& obj)
{
	//os - Output stream
	return obj.info(os);
	//obj.info();
	//return os << obj.get_last_name() << " " << obj.get_first_name() << " " << obj.get_age();
}
//std::ofstream& operator<<(std::ofstream& ofs, const Human& obj)
//{
//	obj.write(ofs);
//	return ofs;
//}
std::ifstream& operator>>(std::ifstream& ifs, Human& obj)
{
	obj.read(ifs);
	return ifs;
}

class AcademyMember :public Human
{
	static const int SPECIALITY_WIDTH = 16;
	std::string speciality;
public:
	const std::string& get_speciality()const
	{
		return speciality;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	//				Constructors:
	AcademyMember
	(
		const std::string& last_name, const std::string& first_name, int age,
		const std::string& speciality
	) :Human(last_name, first_name, age)
	{
		set_speciality(speciality);
		cout << "AMConstructor:\t" << this << endl;
	}
	~AcademyMember()
	{
		cout << "AMDestructor:\t" << this << endl;
	}

	//				Methods:
	std::ostream& info(std::ostream& os)const override
	{
		//return Human::info(os) << " " << speciality;
		Human::info(os);
		os.width(SPECIALITY_WIDTH);
		os << speciality;
		return os;
		//Human::info(os);
		//return os << speciality << endl;
	}
	std::ofstream& write(std::ofstream& ofs)const override
	{
		Human::write(ofs);
		ofs << " " << speciality;
		return ofs;
	}
	std::ifstream& read(std::ifstream& ifs)override
	{
		Human::read(ifs);
		char buffer[SPECIALITY_WIDTH + 1] = {};
		//https://legacy.cplusplus.com/reference/istream/istream/read/
		ifs.read(buffer, SPECIALITY_WIDTH);
		//cout << buffer << endl;
		for (int i = SPECIALITY_WIDTH - 1; buffer[i] == ' '; i--)buffer[i] = 0;
		while (buffer[0] == ' ')
			for (int i = 0; buffer[i]; i++)buffer[i] = buffer[i + 1];
		this->speciality = buffer;
		return ifs;
	}
};

class Student :public AcademyMember
{
	static const int GROUP_WIDTH = 8;
	static const int RATING_WIDTH = 8;
	static const int ATTENDANCE_WIDTH = 8;
	std::string group;
	double rating;
	double attendance;
public:
	const std::string& get_group()const
	{
		return group;
	}
	double get_rating()const
	{
		return rating;
	}
	double get_attendance()const
	{
		return attendance;
	}
	void set_group(const std::string& group)
	{
		this->group = group;
	}
	void set_rating(double rating)
	{
		this->rating = rating;
	}
	void set_attendance(double attendance)
	{
		this->attendance = attendance;
	}

	//				Constructors:
	Student
	(
		const std::string& last_name, const std::string& first_name, int age,
		const std::string& speciality,
		const std::string& group, double rating, double attendance
	) :AcademyMember(last_name, first_name, age, speciality)
	{
		set_group(group);
		set_rating(rating);
		set_attendance(attendance);
		cout << "SConstructor:\t" << this << endl;
	}
	~Student()
	{
		cout << "SDestructor:\t" << this << endl;
	}

	//					Methods:
	std::ostream& info(std::ostream& os)const override
	{
		//return AcademyMember::info(os) << " " << group << " " << rating << " " << attendance;
		AcademyMember::info(os);
		os.width(GROUP_WIDTH);
		os << group;
		os.width(RATING_WIDTH);
		os << rating;
		os.width(ATTENDANCE_WIDTH);
		os << attendance;
		return os;
		//AcademyMember::info(os);
		/*
		:: - Оператор разрешения видимости (Scope operator), показывает, в какой области видиморсти объявлен идентификатор (функция, константа, переменная и т.д.)
		*/
		//return os << group << " " << rating << " " << attendance << endl;
	}
	std::ofstream& write(std::ofstream& ofs)const override
	{
		AcademyMember::write(ofs);
		ofs << " " << group << " " << rating << " " << attendance;
		return ofs;
	}
	std::ifstream& read(std::ifstream& ifs)override
	{
		AcademyMember::read(ifs);
		ifs >> group >> rating >> attendance;
		return ifs;
	}
};

class Teacher :public AcademyMember
{
	int experience;
public:
	int get_experience()const
	{
		return experience;
	}
	void set_experience(int experience)
	{
		this->experience = experience;
	}
	//			Constructors:
	Teacher
	(
		const std::string& last_name, const std::string& first_name, int age,
		const std::string& speciality,
		int experience
	) :AcademyMember(last_name, first_name, age, speciality)
	{
		set_experience(experience);
		cout << "TConstrcutor:\t" << this << endl;
	}
	~Teacher()
	{
		cout << "TDestructor:\t" << this << endl;
	}

	//			Methods:
	std::ostream& info(std::ostream& os)const override
	{
		return AcademyMember::info(os) << experience;
		//AcademyMember::info(os);
		//return os << experience << endl;
	}
	std::ofstream& write(std::ofstream& ofs)const override
	{
		AcademyMember::write(ofs);
		ofs << " " << experience;
		return ofs;
	}
	std::ifstream& read(std::ifstream& ifs)override
	{
		AcademyMember::read(ifs);
		ifs >> experience;
		return ifs;
	}
};
class Graduate :public Student
{
	std::string subject;
public:
	const std::string& get_subject()const
	{
		return subject;
	}
	void set_subject(const std::string& subject)
	{
		this->subject = subject;
	}
	//			Constructors:
	Graduate
	(
		const std::string& last_name, const std::string& first_name, int age,
		const std::string& speciality,
		const std::string& group, double rating, double attendance,
		const std::string& subject
	) :Student(last_name, first_name, age, speciality, group, rating, attendance)
	{
		set_subject(subject);
		cout << "GConstructor:\t" << this << endl;
	}
	~Graduate()
	{
		cout << "GDestructor:\t" << this << endl;
	}
	std::ostream& info(std::ostream& os)const override
	{
		return Student::info(os) << subject;
		//Student::info(os);
		//return os << subject << endl;
	}
	std::ofstream& write(std::ofstream& ofs)const override
	{
		Student::write(ofs);
		ofs << " " << subject;
		return ofs;
	}
	std::ifstream& read(std::ifstream& ifs)
	{
		Student::read(ifs);
		std::getline(ifs, subject);
		return ifs;
	}
};

void Print(Human* group[], const int n)
{
	// __vfptr (Virtual Functions Pointers) - Таблица указателей на виртуальные функции.
	//Specialization - уточнение
	//Downcast - приведение базового типа к дочернему.
	for (int i = 0; i < n; i++)
	{
		//group[i]->info();
		//cout << delimiter << endl;
		cout << *group[i] << endl;
	}
}
void Save(Human* group[], const int n, const std::string& filename)
{
	std::ofstream fout(filename);
	for (int i = 0; i < n; i++)
	{
		fout << *group[i] << endl;
	}
	fout.close();
	std::string cmd = "notepad ";
	cmd += filename;
	system(cmd.c_str());
}
Human* Factory(const char type[])
{
	Human* human = nullptr;
	//Функция strstr(str1, str2) находит последовательность 'str2' в строке 'str1' 
	//https://legacy.cplusplus.com/reference/cstring/strstr/
	if (strstr(type, "Student"))	human = new Student("", "", 0, "", "", 0, 0);
	if (strstr(type, "Graduate"))	human = new Graduate("", "", 0, "", "", 0, 0, "");
	if (strstr(type, "Teacher"))	human = new Teacher("", "", 0, "", 0);
	return human;
}
Human** Load(const std::string& filename, int& n)
{
	Human** group = nullptr;
	std::ifstream fin(filename);
	if (fin.is_open())
	{
		//1) Вычисляем количество объектов в файле:
		n = 0;	//Обнуляем размер массива
		std::string buffer;
		while (!fin.eof())
		{
			std::getline(fin, buffer);
			if (buffer.size() == 0)continue;
			n++;
		}
		cout << n << endl;
		//2) Выделяем память под массив, в который будут сохраняться объекты из файла:
		group = new Human*[n] {};

		//3) Возвращаемся в начало файла для того чтобы загрузить из него объекты:
		cout << fin.tellg() << endl;
		fin.clear();
		fin.seekg(0);
		cout << fin.tellg() << endl;

		//4) Загружаем объекты из файла:
		for (int i = 0; !fin.eof(); i++)
		{
			std::getline(fin, buffer, ':');
			if (buffer.size() == 0)continue;
			group[i] = Factory(buffer.c_str());
			if (group[i])fin >> *group[i];
			else i--;
		}
	}
	else
	{
		std::cerr << "Error: file not found" << endl;
	}
	fin.close();
	return group;
}

//#define INHERITANCE
//#define POLYMORPHISM

void main()
{
	setlocale(LC_ALL, "");

#ifdef INHERITANCE
	//Human human("Einstein", "Albert", 146);
//human.info();

	AcademyMember albert("Einstein", "Albert", 146, "Astronomy");
	albert.info();

	Student student("Щербаков", "Илья", 15, "Разработка программного обеспечения", "P_418", 100, 99.9);
	student.info();

	Teacher teacher("Einstein", "Albert", 146, "Astronomy", 120);
	teacher.info();
#endif // INHERITANCE

#ifdef POLYMORPHISM
	//Polymorphism (многоформенность: poly-много, morphis-форма)
/*
	Runtime polymorhism:
		1. Base class pointers;
		2. Virtual functions (methods);
*/

//Generalization - Обобщение
//Upcast - преобразование дочернего объекта к базовому типу.
	Human* group[] =
	{
		new Student("Кондратенко", "Георний", 18, "РПО", "P_418", 97, 98),
		new Teacher("Stanne", "Michael", 55, "Vocals", 40),
		new Student("Щербаков", "Илья", 15, "РПО", "P_418", 100, 99.9),
		new Teacher("Henriksson", "Matrin", 50, "Bass guitar", 40),
		new Student("Тетевосян", "Элеонора", 17, "РПО", "P_418", 98, 48),
		new Graduate("Пензин", "Богдан", 15, "РПО", "P_418", 98, 99, "Мнение и этическая позиция подростков на развитие искуственного интеллекта (AGI - Artificial General Intelligence)")
	};
	Print(group, sizeof(group) / sizeof(group[0]));
	Save(group, sizeof(group) / sizeof(group[0]), "P_418.txt");

	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		delete group[i];
	}
	cout << "Количество участников группы: " << Human::get_count() << endl;
#endif // POLYMORPHISM

	int n = 0;
	Human** group = Load("P_418.txt", n);
	Print(group, n);
}