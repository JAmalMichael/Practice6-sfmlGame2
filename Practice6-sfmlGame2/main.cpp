#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

struct A {
	int x;
	A() = default;
};

struct B {
	int y;
	B() {};
};

int main()
{
	A a{};
	B b{};
	cout << "Value of a.x = " << a.x<< endl;
	cout << "Value of b.x = " << b.y << endl;
	return 0;
}