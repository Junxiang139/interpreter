/*
Our story starts here
try to apply plus in integer
*/
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<typeinfo>
#include<iostream>
#include<vector>
#include<string>
using namespace std;

struct floatnum {
	double value;
	floatnum () {
		//id = 2;
		value = 0;
	}
};

struct bignum {
	//int id;
	int a[258];
	bigbum () {
		//id = 3;
		a[0] = 0;
	}
	operator floatnum () const {
		floatnum b;
		for (int i = 1; i <= a[0]; i++) {
			b.value = b.value * 10 + a[0];
		}
		return b;
	}
};

struct intnum {
	int value;
	intnum () {
		//id = 1;
		value = 0;
	}
	
	operator bignum () const {
		bignum b;
		int len = 0;
		int v = value;
		while (v) {
			len++;
			b.a[len] = v % 10;
			v /= 10;
		}
		b.a[0] = len;
	}
	
	operator floatnum () const {
		floatnum b;
		b.value = value;
		return b;
	}
};

/*
template <typename T>
void type (T a) {
	cout << a.id << endl;
}
*/

/*
template <typename T>
floatnum cfloatnum(T a) {
	if (typeid(a) == typeid(floatnum)) return a;
	if (typeid(a) == typeid(intnum)) {
		floatnum b;
		b.value = a.value;
		return b;
	}
}
*/

vector<intnum> intlist;    //rank % 3 = 0
vector<floatnum> floatlist;//rank % 3 = 1
vector<bignum> biglist;    //rank % 3 = 2

int lbra = 0, rbra = 0;
void calclr(string s) {
	int len = s.length();
	lbra = rbra = 0;
	for (int i = 0; i < len; i++) {
		if (s[i] == '(') lbra++;
		else if (s[i] == ')') rbra++;
	}
	return;
}
bool numon(string s) {
	int len = s.length();
	for (int i = 0; i < len; i++) {
		if (s[i] < '0' || s[i] > '9') return 0;
	}
	return 1;
}
int numv(string s) {
	int len = s.length();
	if (len < 10) {
		int v = 0;
		for (int i = 0; i < len; i++) {
			v = v * 10 + (s[i] - '0');
		}
		return v;
	}
	return 0;
}
int eplus(int a, int b) {
	return a + b;
}
int eminus(int a, int b) {
	return a - b;
}
int emulti(int a, int b) {
	return a * b;
}
int divine(int a, int b) {
	return a / b;
}
int getnex(string s, int pos) {
	int l = 1, r = 0, len = s.length();
	pos++;
	if (s[pos] != '(') {
		while (s[pos] != ' ' && s[pos] != ')' && pos < len) pos++;
		return pos;
	}
	while (pos < len) {
		pos++;
		if (s[pos] == '(') l++;
		else if (s[pos] == ')') {
			r++;
			if (l == r) return pos + 1;
		}
	}
	return 0;
}
int getvalue(string s) {
	if (numon(s)) return numv(s);
	else {
		int k1 = 2, k2 = getnex(s, 2), k3 = 0;
		k3 = getnex(s, k2);
		//cout << k2 << ' ' << k3 << endl;
		//cout << s << endl << s[k1] << s[k2] << s[k3] << endl;
		///*
		string s1 (s, k1 + 1, k2 - k1 - 1), s2 (s, k2 + 1, k3 - k2 - 1);
		//cout << s1 << endl << s2 << endl;
		int v1 = getvalue(s1), v2 = getvalue(s2);
		switch(s[1]) {
			case '+':
				return eplus(v1, v2);
				break;
			case '-':
				return eminus(v1, v2);
				break;
			case '*':
				return emulti(v1, v2);
				break;
			case '/':
				return divine(v1, v2);
				break;
		}
		//*/
	}
	return 0;
}
int main() {
	intnum a;
	string s, s1;
	s.clear();
	char forgets[1005];
	while (1) {
		gets(forgets);
		s += forgets;
		calclr(s);
		if (lbra != rbra) continue;
		//define
		if (s.length() >= 8) {
			string s2 (s, 1, 6);
			if (s2 == "define") {
				continue;		
			}
		}
		cout << getvalue(s) << endl;
		s.clear();
	}
	system("pause");
	return 0;
}
/*
(+ (+ 1 2) 3)
*/
