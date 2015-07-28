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

/*
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
*/

struct num {
	int id;//1 2 3
	int intnum;
	double floatnum;
	bool zf;
	int a[105];
	num () {
		id = intnum = 0;
		floatnum = 0;
		//a.clear();
	}
	num (int b) {
		id = 1;
		intnum = b;
	}
	num (double b) {
		id = 2;
		floatnum = b;
	}
	num (string b) {
		int l = b.length();
		//printf("l = %d\n", l);
		zf = 0;
		if (b[0] == '-') zf = 1;
		if (l < 9) {
			id = 1;
			intnum = 0;
			if (zf == 0) {
				for (int i = l - 1; i >= 0; i--) {
					intnum = intnum * 10 + b[i] - '0';
				}
			} else {
				for (int i = l - 1; i >= 1; i--) {
					intnum = intnum * 10 + b[i] - '0';
				}
			}
		} else {
			//printf("here\n");
			id = 3;
			a[0] = l;
			///*
			if (zf == 0) {
				for (int i = l - 1, j = 1; j <= l; j++, i--) {
					a[j] = b[i] - '0';
				}
				/*
				printf("id = %d\n", id);
				for (int i = 0; i <= a[0]; i++) {
					printf("%d", a[i]);
				}
				printf("\n");
				*/
			} else {
				for (int i = l - 1, j = 1; j < l; j++, i--) {
					a[j] = b[i] - '0';
				}
				/*
				printf("id = %d\n", id);
				for (int i = 0; i <= a[0]; i++) {
					printf("%d", a[i]);
				}
				printf("\n");
				*/
			}
			//*/
		}
	}
	
	num operator+(const num &c) const;
	/* {
		if (id == 1 && c.id == 1) {
			num a;
			a.id = 1;
			a.intnum = intnum + c.intnum;
			return a;
		} else if (id == 2 || c.id == 2) {
			num a, b;
			a = cfloat(*this), b = cfloat(c);
		} else {
			
		}
	}*/
	
	num operator-(const num &b) const {
		num a;
		if (id == 1 && b.id == 1) {
			a.id = 1;
			a.intnum = intnum - b.intnum;
			return a;
		}
	}
	
	num operator*(const num &b) const {
		num a;
		if (id == 1 && b.id == 1) {
			a.id = 1;
			a.intnum = intnum * b.intnum;
			return a;
		}
	}
	
	num operator/(const num &b) const {
		num a;
		if (id == 1 && b.id == 1) {
			a.id = 1;
			a.intnum = intnum / b.intnum;
			return a;
		}
	}
};

num cfloat(const num &b) {
	num a;
	a.id = 2;
	a.floatnum = 0.0;
	if (b.id == 1) {
		a.floatnum = b.intnum;
	} else if (b.id == 2) {
		return b;
	} else if (b.id == 3) {
		for (int i = b.a[0]; i >= 1; i--) {
			a.floatnum = a.floatnum * 10 + b.a[i];
			//printf("v %f\n", a.floatnum);
		}
		if (b.zf == 1) a.floatnum = -a.floatnum;
		//printf("v %f\n", a.floatnum);
	}
	return a;
}

num cbignum(const num &b) {
	num a;
	a.id = 3;
	if (b.id == 3) {
		return b;
	} else if (b.id == 1) {
		int v = b.intnum, l = 0;
		while (v) {
			l++;
			a.a[l] = v % 10;
			v /= 10;
		}
		a.a[0] = l;
	}
	return a;
}

num num::operator+(const num &c) const {
	num a, b;
	if (id == 1 && c.id == 1) {
		a.id = 1;
		a.intnum = intnum + c.intnum;
	} else if (id == 2 || c.id == 2) {
		a = cfloat(*this), b = cfloat(c);
		a.floatnum += b.floatnum;
	} else {
		a = cbignum(*this), b = cbignum(c);
	}
	return a;
}

ostream& operator<<(ostream &os, const num &obj) {
	if (obj.id == 1) {
		os << obj.intnum;
	} else if (obj.id == 2) {
		os << obj.floatnum;
	} else if (obj.id == 3) {
		int p = obj.a[0], zf = obj.zf;
		if (zf == 1) os << '-';
		for (int i = p; i >= 1; i--) {
			os << obj.a[i];
		}
		if (p == 0) os << 0;
	}
}

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
/*
vector<intnum> intlist;    //rank % 3 = 0
vector<floatnum> floatlist;//rank % 3 = 1
vector<bignum> biglist;    //rank % 3 = 2
*/

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
	int st = 0, dot = 0;
	if (s[0] == '-') st = 1;
	for (int i = st; i < len; i++) {
		if (s[i] == '.') {
			if (dot == 0) dot = 1;
			else return 0;
		} else {
			if (s[i] < '0' || s[i] > '9') return 0;
		}
	}
	return 1;
}

num numv(string s) {
	int len = s.length();
	num v;
	int dot = 0;
	int st = 0;
	if (s[0] == '-') st = 1;
	for (int i = 0; i < len; i++) {
		if (s[i] == '.') {
			dot = 1;
			break;
		}
	}
	if (dot) {
		v.id = 2, v.floatnum = 0;
		double q = 1;
		int dot1 = 0;
		for (int i = st; i < len; i++) {
			if (dot1) q *= 10.0;
			if (s[i] == '.') dot1 = 1;
			if (s[i] != '.') v.floatnum = v.floatnum * 10 + (s[i] - '0');
		}
		v.floatnum /= q;
		if (st == 1) v.floatnum = -v.floatnum;
	} else if (len < 9) {
		v.id = 1, v.intnum = 0;
		for (int i = st; i < len; i++) {
			v.intnum = v.intnum * 10 + (s[i] - '0');
		}
		if (st == 1) v.intnum = -v.intnum;
	} else {
		v.id = 3;
		//v.a.clear();
		if (st == 1) {v.zf = 1, v.a[0] = len - 1;}
		else {v.zf = 0, v.a[0] = len;}
		for (int i = st, j = v.a[0]; i < len; i++, j--) {
			v.a[j] = s[i] - '0';
		}
	}
	return v;
}

/*
template <class T>
T eplus(T a, T b) {
	if (typeid(a) == typeid(floatnum) || typeid(b) == typeid(floatnum)) {
		floatnum c;
		c.value = a.value + b.value;
		return c;
	} else {
		intnum c;
		c.value = a.value + b.value;
		return c;
	}
}
*/
num eplus(num a, num b) {
	//printf("id %d %d\n", a.id, b.id);
	return a + b;
}
num eminus(num a, num b) {
	return a - b;
}
num emulti(num a, num b) {
	return a * b;
}
num divine(num a, num b) {
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
num getvalue(string s) {
	if (numon(s)) return numv(s);
	else {
		int k1 = 2, k2 = getnex(s, 2), k3 = 0;
		k3 = getnex(s, k2);
		//cout << k2 << ' ' << k3 << endl;
		//cout << s << endl << s[k1] << s[k2] << s[k3] << endl;
		///*
		string s1 (s, k1 + 1, k2 - k1 - 1), s2 (s, k2 + 1, k3 - k2 - 1);
		//cout << s1 << endl << s2 << endl;
		num v1 = getvalue(s1), v2 = getvalue(s2);
		switch(s[1]) {
			case '+': {
				return eplus(v1, v2);
				break;
			}
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
	string s, s1;
	s.clear();
	char forgets[1005];
	/*
	num fairy;
	fairy = 3.1416;
	cout << fairy << endl;
	fairy = 120;
	cout << fairy << fairy.id << endl;
	fairy = 120.000;
	cout << fairy << fairy.id << endl;
	string b = "1293801124532134422";
	fairy = b;
	cout << fairy << fairy.id << endl;
	*/
	//return 0;
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
