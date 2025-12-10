#include<iostream>
#include<string>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-------------------------------------------------------\n"

class Human
{
	std::string last_name;
	std::string first_name;
	int age;
public:
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
		cout << "HConstructor:\t" << this << endl;
	}
	Human(const Human& other)
	{
		this->last_name = other.last_name;
		this->first_name = other.first_name;
		this->age = other.age;
		cout << "HCopyConstructor: " << this << endl;
	}
	~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}
	virtual void info()const
	{
		cout << last_name << " " << first_name << " " << age << endl;
	}
};
std::ostream& operator<<(std::ostream& os, const Human& obj)
{
	return os << obj.get_last_name() << " " << obj.get_first_name() << " " << obj.get_age();
}

class AcademyMember :public Human
{
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
	void info()const override
	{
		Human::info();
		cout << speciality << endl;
	}
};
std::ostream& operator<<(std::ostream& os, const AcademyMember& obj)
{
	return os << (Human&)obj << " " << obj.get_speciality();
}

class Student :public AcademyMember
{
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
	void info()const override
	{
		AcademyMember::info();
		cout << group << " " << rating << " " << attendance << endl;
	}
};
std::ostream& operator<<(std::ostream& os, const Student& obj)
{
	return os << (AcademyMember&)obj << obj.get_group() << " " << obj.get_rating() << " " << obj.get_attendance();
}

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
	void info()const override
	{
		AcademyMember::info();
		cout << experience << endl;
	}
};
std::ostream& operator<<(std::ostream& os, const Teacher& obj)
{
	return os << (AcademyMember&)obj << obj.get_experience();
}
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
	):Student(last_name, first_name,age,speciality,group,rating,attendance)
	{
		set_subject(subject);
		cout << "GConstructor:\t" << this << endl;
	}
	~Graduate()
	{
		cout << "GDestructor:\t" << this << endl;
	}
	void info()const override
	{
		Student::info();
		cout << subject << endl;
	}
};
std::ostream& operator<<(std::ostream& os, const Graduate& obj)
{
	return os << (Student&)obj << obj.get_subject();
}

//#define INHERITANCE

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

	//Polymorphism (многоформенность: poly-много, morphis-форма)
	/*
		Runtime polymorhism:
			1. Base class pointers;
			2. Virtual functions (methods);
	*/

	Human* group[] =
	{
		new Student("Кондратенко", "Георний", 18, "РПО", "P_418", 97, 98),
		new Teacher("Stanne", "Michael", 55, "Vocals", 40),
		new Student("Щербаков", "Илья", 15, "РПО", "P_418", 100, 99.9),
		new Teacher("Henriksson", "Matrin", 50, "Bass", 40),
		new Student("Тетевосян", "Элеонора", 17, "РПО", "P_418", 98, 48),
		new Graduate("Пензин", "Богдан", 15, "РПО", "P_418", 98, 99, "Мнение и этическая позиция подростков на развитие искуственного интеллекта (AGI - Artificial General Intelligence)")
	};

	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		//group[i]->info();
		cout << delimiter << endl;
		//cout << *dynamic_cast<AcademyMember*>(group[i]) << endl;
		cout << typeid(*group[i]).name() << ":\t";
		if (typeid(*group[i]) == typeid(Student))cout << *dynamic_cast<Student*>(group[i]) << endl;
		if (typeid(*group[i]) == typeid(Teacher))cout << *dynamic_cast<Teacher*>(group[i]) << endl;
		if (typeid(*group[i]) == typeid(Graduate))cout << *dynamic_cast<Graduate*>(group[i]) << endl;
	}
	5;	//Числовая константа типа 'int'.
	cout << sizeof(5) << endl;
	cout << typeid(5).name() << endl;
	cout << typeid(3.14).name() << endl;
}