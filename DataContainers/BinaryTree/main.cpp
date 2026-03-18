#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab			"\t"
#define delimiter	"\n-----------------------------------\n"

class Tree
{
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
	}*Root;
public:

};

void main()
{

}