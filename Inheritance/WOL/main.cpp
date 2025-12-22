//WOL - Wake On LAN
#include<iostream>
#include<fstream>
using std::cin;
using std::cout;
using std::endl;

//#define WOL
#define DHCPD

void main()
{
	setlocale(LC_ALL, "");

#ifdef WOL
	std::ifstream fin("201 RAW.txt");
	std::ofstream fout("201 WOL.txt");	//WOL - Wake On LAN
	if (fin.is_open())
	{
		const int IP_BUFFER_SIZE = 16;
		const int MAC_BUFFER_SIZE = 18;
		int i_Number = 0;
		//https://ru.wikipedia.org/wiki/%D0%92%D0%B5%D0%BD%D0%B3%D0%B5%D1%80%D1%81%D0%BA%D0%B0%D1%8F_%D0%BD%D0%BE%D1%82%D0%B0%D1%86%D0%B8%D1%8F
		//NULL-Terminated Line (sz_ - String Zero)
		char sz_IP_buffer[IP_BUFFER_SIZE] = {};
		char sz_MAC_buffer[MAC_BUFFER_SIZE] = {};
		while (!fin.eof())
		{
			fin >> sz_IP_buffer >> sz_MAC_buffer;
			cout << sz_MAC_buffer << "\t" << sz_IP_buffer << endl;
			fout << sz_MAC_buffer << "\t" << sz_IP_buffer << endl;
		}
	}
	else
	{
		std::cerr << "Error: file not found" << endl;
		//cerr - Console Errors
	}
	fout.close();
	fin.close();
	system("notepad 201 WOL.txt");
#endif // WOL



}