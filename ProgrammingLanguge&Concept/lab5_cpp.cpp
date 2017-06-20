


#include "stdafx.h"
#include <iostream>

using namespace std;
class A
{
public:
	virtual void p()
	{
		cout << "A.p" << endl;
	}
	void q()
	{
		cout << "A.q" << endl;
	}
	virtual void r()
	{
		p(); q();
	}
};
class B : public A
{
public:
	void p()
	{
		cout << "B.p" << endl;
	}
};
class C : public B
{
public:
	void q()
	{
		cout << "C.q" << endl;
	}
	void r()
	{
		p(); q();
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	A* a;
	C* c = new C();
	a = c;
	a->r();
	a = new B();
	a->r();
	a = new C();
	a->r();

	char input;
	cin >> input;
	return 0;
}


