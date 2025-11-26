#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

class MyString {
	char* data;

public:
	// Constructor
	MyString(const char* str = "") {
		data = new char[strlen(str) + 1];
		strcpy(data, str);
	}

	// User-defined move assignment operator
	MyString& operator=(MyString&& other) {
		std::cout << "Move assignment called\n";

		if (this != &other) {
			// Free old memory
			delete[] data;
			// Steal the pointer
			data = other.data;
			// Set source to null
			other.data = nullptr;
		}

		return *this;
	}

	// Destructor
	~MyString() {
		delete[] data;
	}

	void print() const {
		if (data)
			std::cout << data << "\n";
		else
			std::cout << "[empty]\n";
	}
};
int main() {
	MyString a("Hello");
	MyString b("World");

	b = std::move(a);

	b.print();
	a.print();
}

