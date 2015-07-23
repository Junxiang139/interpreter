/*
Our story starts here
try to apply plus in integer
*/
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
#include<string>
using namespace std;
template <typename T>
void type (T a) {
  cout << a.id << endl;
}
struct intnum {
	int id;
	int value;
	intnum () {
		id = 1;
		value = 0;
	}
};
struct floatnum {
	int id;
	double value;
	floatnum () {
		id = 2;
		value = 0;
	}
};
template <typename T>
floatnum cfloatnum(T a) {
	if (a.id == 2) return a;
	if (a.id == 1) {
		floatnum b;
		b.value = a.value;
		return b;
	}
}
int main() {
	intnum a;
	floatnum b;
	type(a);
	type(b);
	cin >> a.value >> b.value;
	floatnum c = plus(a, b);
	cout << c.value << endl;
	return 0;
}
