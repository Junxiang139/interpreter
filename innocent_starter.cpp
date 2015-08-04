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

string func[1005];
string fname[1005];
int ftot = 0;

struct num {
	int id;//1 2 3 4
	int intnum;
	double floatnum;
	bool zf;
	int a[105] = {0};
	int fz, fm;
	string name;
	num () {
		id = 1;
		intnum = 0;
		floatnum = 0;
		zf = 0;
		fz = fm = 0;
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
	
	num &operator=(const num &c) { //不复制变量名 
		if (this == &c) return *this;
		id = c.id;
		if (id == 1) {
			intnum = c.intnum;
			//return 0;
		} else if (id == 2) {
			floatnum = c.floatnum;
		} else if (id == 3) {
			zf = c.zf;
			for (int i = 0; i <= c.a[0]; i++) {
				a[i] = c.a[i];
			}
		} else if (id == 4) {
			fz = c.fz, fm = c.fm;
		}
		return *this;
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
	
	num operator-(const num &b) const;
	
	num operator*(const num &b) const;
	
	num operator/(const num &b) const;
	
	bool operator==(const num &b) const;
	
	bool operator<(const num &b) const;
};

num var[3005];
int tot = 0;

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
	} else if (b.id == 4) {
		a.floatnum = double(b.fz) / double(b.fm);
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
		if (v < 0) {
			a.zf = 1;
			v = -v;
		} else {
			a.zf = 0;
		}
		while (v) {
			l++;
			a.a[l] = v % 10;
			v /= 10;
		}
		a.a[0] = l;
	}
	return a;
}

num reduct(const num &b) {
	num a = b;
	if (a.id == 4) {
		int q = __gcd(a.fz, a.fm);
		if (q != 1) {
			a.fz /= q, a.fm /= q;
		}
		if (a.fm == 1) {
			a.id = 1;
			a.intnum = a.fz;
		}
	}
	return a;
}

num cfranum(const num &b) {
	if (b.id == 4) {
		return b;
	}
	num a = b;
	if (b.id == 1) {
		a.id = 4;
		a.fz = b.intnum;
		a.fm = 1;
	}
	return a;
}
bool num::operator==(const num &c) const {
	num a = *this, b = c;
	if (a.id == 1 && b.id == 1) {
		return a.intnum == b.intnum;
	} else if ((a.id == 1 || a.id == 4) && (b.id == 1 || b.id == 4)) {
		a = cfranum(a), b = cfranum(b);
		return (a.fz == b.fz && a.fm == b.fm);
	} else if (a.id == 2 || a.id == 4 || b.id == 2 || b.id == 4) {
		a = cfloat(a), b = cfloat(b);
		return abs(a.floatnum - b.floatnum) < 0.0000001;
	} else {
		a = cbignum(a), b = cbignum(b);
		if (a.zf != b.zf) return 0;
		if (a.a[0] != b.a[0]) return 0;
		for (int i = a.a[0]; i >= 1; i--) {
			if (a.a[i] != b.a[i]) return 0;
		}
		return 1;
	}
}
bool num::operator<(const num &c) const {
	num a = *this, b = c;
	if (a.id == 1 && b.id == 1) {
		return a.intnum < b.intnum;
	} else if ((a.id == 1 || a.id == 4) && (b.id == 1 || b.id == 4)) {
		a = cfranum(a), b = cfranum(b);
		return (double(a.fz) / double(a.fm)) < (double(b.fz) / double(b.fm));
	} else if (a.id == 2 || a.id == 4 || b.id == 2 || b.id == 4) {
		a = cfloat(a), b = cfloat(b);
		return a.floatnum < b.floatnum;
	} else {
		a = cbignum(a), b = cbignum(b);
		if (a == b) return 0;
		if (a.zf != b.zf) return a.zf > c.zf;
		if (a.zf == 0) {
			if (a.a[0] < b.a[0]) return 1;
			if (a.a[0] > b.a[0]) return 0;
			for (int i = a.a[0]; i >= 1; i--) {
				if (a.a[i] < b.a[i]) return 1;
				if (a.a[i] > b.a[i]) return 0;
			}
			return 0;
		} else {
			a.zf = 0, b.zf = 0;
			return !(a < b);
		}
	}
}

num num::operator+(const num &c) const {
	num a, b;
	if (id == 1 && c.id == 1) {
		a.id = 1;
		a.intnum = intnum + c.intnum;
		if (abs(a.intnum) > 1000000000) {
			a = cbignum(a);
		}
	} else if ((id == 1 || id == 4) && (c.id == 1 || c.id == 4)) {
		a = (*this), b = c;
		a = cfranum(a), b = cfranum(b);
		if (a.fm == b.fm) {
			a.fz += b.fz;
			if (abs(a.fz) > 1000000000) {
				a = cfloat(a);
			} else if (a.fz == 0) {
				a.id = 1;
				a.intnum = 0;
			} else {
				a = reduct(a);
			}
		} else {
			long long vz, vm;
			vz = (long long)a.fz * b.fm + (long long)b.fz * a.fm;
			vm = (long long)a.fm * b.fm;
			if (abs(vz) > 1000000000ll || abs(vm) > 1000000000ll) {
				a = cfloat(a), b = cfloat(b);
				a = a + b;
			} else {
				a.fz = (int)vz, a.fm = (int)vm;
				a = reduct(a);
			}
		}
	} else if (id == 2 || id == 4 || c.id == 2 || c.id == 4) {
		a = cfloat(*this), b = cfloat(c);
		a.floatnum += b.floatnum;
	} else {
		a = cbignum(*this), b = cbignum(c);
		if (a.zf == b.zf) {
			a.a[0] = max(a.a[0], b.a[0]);
			int k = 0;
			for (int i = 1; i <= a.a[0]; i++) {
				a.a[i] += b.a[i] + k;
				if (a.a[i] >= 10) {
					a.a[i] -= 10;
					k = 1;
				} else k = 0;
			}
			if (k) {
				a.a[++a.a[0]] = 1;
			}
		} else {
			b.zf = !(b.zf);//a - b
			if (a == b) {
				num d;
				a = d;
			} else {
				int mark = 0;
				if (a.zf == 1) {
					mark = 1;
					a.zf = 0, b.zf = 0;
				}
				if (b < a) {
					int i, k = 0;
					for (int i = 1; i <= b.a[0]; i++) {
						a.a[i] = a.a[i] - b.a[i] - k;
						if (a.a[i] < 0) {
							a.a[i] += 10;
							k = 1;
						} else {
							k = 0;
						}
					}
					for (int i = b.a[0] + 1; k; i++) {
						a.a[i] -= k;
						if (a.a[i] < 0) {
							a.a[i] += 10;
							k = 1;
						} else {
							k = 0;
						}
					}
					while (a.a[a.a[0]] == 0) {
						a.a[0]--;
					}
				} else {
					num d;
					b.zf = !(b.zf);
					d = b + a;
					//d.zf = !(d.zf);
					a = d;
				}
				if (mark) {
					a.zf = !(a. zf);
				}
			}
		}
	}
	return a;
}
//100000000000000000000
num num::operator-(const num &c) const {
	num a, b;
	if (id == 1 && c.id == 1) {
		a.id = 1;
		a.intnum = intnum - c.intnum;
		if (abs(a.intnum) > 1000000000) {
			a = cbignum(a);
		}
	} else if ((id == 1 || id == 4) && (c.id == 1 || c.id == 4)) {
		a = cfranum(*this), b = cfranum(c);
		b.fz = -b.fz;
		a = a + b;
	} else if (id == 2 || id == 4 || c.id == 2 || c.id == 4) {
		a = cfloat(*this), b = cfloat(c);
		a.floatnum -= b.floatnum;
	} else {
		a = cbignum(*this), b = cbignum(c);
		b.zf = !(b.zf);
		a = a + b;
	}
	return a;
}

num num::operator*(const num &c) const {
	num a, b;
	if (id == 1 && c.id == 1) {
		a.id = 1;
		long long v;
		v = (long long)intnum * c.intnum;
		if (abs(v) > 1000000000ll) {
			num a1, b1;
			a1 = cbignum(*this), b1 = cbignum(c);
			a = a1 * b1;
			return a;
		} else {
			a.intnum = intnum * c.intnum;
		}
	} else if ((id == 1 || id == 4) && (c.id == 1 || c.id == 4)) {
		a = cfranum(*this), b = cfranum(c);
		long long vz, vm;
		vz = (long long)a.fz * b.fz;
		vm = (long long)a.fm * b.fm;
		if (abs(vz) > 1000000000ll || abs(vm) > 1000000000ll) {
			a = cfloat(a), b = cfloat(b);
			a = a * b;
		} else {
			a.fz = (int)vz, a.fm = (int)vm;
			if (a.fz == 0) {
				a.id = 1;
				a.intnum = 0;
			} else {
				a = reduct(a);
			}
		}
	} else if (id == 2 || id == 4 || c.id == 2 || c.id == 4) {
		a = cfloat(*this), b = cfloat(c);
		a.floatnum *= b.floatnum;
	} else {
		a = cbignum(*this), b = cbignum(c);
		int l = a.a[0] + b.a[0] - 1;
		num d;
		d.id = 3;
		for (int i = 1; i <= a.a[0]; i++) {
			for (int j = 1; j <= b.a[0]; j++) {
				d.a[i + j - 1] += a.a[i] * b.a[j];
			}
		}
		int k = 0;
		for (int i = 1; i <= l; i++) {
			d.a[i] += k;
			if (d.a[i] >= 10) {
				k = d.a[i] / 10;
				d.a[i] %= 10;
			} else k = 0;
		}
		while (k) {
			d.a[++l] += k % 10;
			k /= 10;
		}
		d.a[0] = l;
		a = d;
	}
	return a;
}
//1238109823420938 1238109823420938
num num::operator/(const num &c) const {
	num a, b;
	if (id == 1 && c.id == 1) {
		a.id = 4;
		a.fz = intnum;
		a.fm = c.intnum;
		a = reduct(a);
	} else if ((id == 1 || id == 4) && (c.id == 1 || c.id == 4)) {
		a = cfranum(*this), b = cfranum(c);
		int k = b.fm;
		b.fm = b.fz, b.fz = k;
		a = a * b;
	} else if (id == 2 || id == 4 || c.id == 2 || c.id == 4) {
		a = cfloat(*this), b = cfloat(c);
		a.floatnum /= b.floatnum;
	} else {
		a = cfloat(*this), b = cfloat(c);
		a = a / b;
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
	} else if (obj.id == 4) {
		os << obj.fz << '/' << obj.fm;
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
/*
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
*/
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
int findname(string s) {
	for (int i = 1; i <= tot; i++) {
		if (var[i].name == s) {
			return i;
		}
	}
	return 0;
}
int findfunc(string s) {
	for (int i = 1; i <= ftot; i++) {
		if (fname[i] == s) {
			return i;
		}
	}
	return 0;
}
bool isop(char c) {
	 return c == '+' || c == '-' || c == '*' || c == '/';
}
num calcv(num a, num b, char c) {
	if (c == '+') return a + b;
	else if (c == '-') return a - b;
	else if (c == '*') return a * b;
	else if (c == '/') return a / b;
	return a;
}
num getvalue(string s) {
	if (numon(s)) {
		return numv(s);
	} else if (findname(s)) {
		return var[findname(s)];
	} else if (isop(s[1])) {
		int k1 = 2, k2 = getnex(s, k1), k3 = getnex(s, k2);
		string s1 (s, k1 + 1, k2 - k1 - 1), s2 (s, k2 + 1, k3 - k2 - 1);
		num v1 = getvalue(s1), v2 = getvalue(s2);
		v1 = calcv(v1, v2, s[1]);
		while (s[k3] == ' ') {
			k2 = k3;
			k3 = getnex(s, k2);
			s2.assign(s, k2 + 1, k3 - k2 - 1);
			v2 = getvalue(s2);
			v1 = calcv(v1, v2, s[1]);
		}
		return v1;
	} else {
		int k1 = 1, k2 = getnex(s, k1), k3 = getnex(s, k2);
		string s1 (s, k1, k2 - k1), s2 (s, k2 + 1, k3 - k2 - 1), sf;
		//cout << s1 << endl << s2 << endl;
		sf = func[findfunc(s1)];
		cout << sf << endl;
	}
	return 0;
}
int main() {
	string s, s1;
	s.clear();
	char forgets[1005];
	num a, b;
	a = b;
	//printf("%d\n", __gcd(12, 27));
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
		if (s == "Requiescat in pace") break;
		calclr(s);
		if (lbra != rbra) continue;
		//define
		if (s.length() >= 8) {
			string s2 (s, 1, 6);
			if (s2 == "define") {
				int k1 = 7, k2 = getnex(s, k1), k3 = getnex(s, k2);
				if (s[k1 + 1] == '(') {
					k1 = 9, k2 = getnex(s, k1);
					ftot++;
					fname[ftot].assign(s, k1, k2 - k1);
					k1 = 7, k2 = getnex(s, k1), k3 = getnex(s, k2);
					func[ftot].assign(s, k2 + 1, k3 - k2 - 1);
					cout << fname[ftot] << endl << func[ftot] << endl;
					s.clear();
					continue;
				}
				tot++;
				s2.assign(s, k1 + 1, k2 - k1 - 1);
				var[tot].name = s2;
				s2.assign(s, k2 + 1, k3 - k2 - 1);
				//cout << getvalue(s2) << endl;
				var[tot] = getvalue(s2);
				//cout << getvalue(s2) << endl;
				s.clear();
			} else {
				cout << getvalue(s) << endl;
				s.clear();
			}
		} else {
			cout << getvalue(s) << endl;
			s.clear();
		}
		/*
		if (tot == 2) {
			cout << var[1] << ' ' << var[2] << endl;
		}
		*/
	}
	return 0;
}
/*
(+ (+ 1 2) 3)
(define (square x) (* x x))
(square 21)
441
(sqaure (square 4))
256
*/
