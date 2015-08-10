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
const int QVN = 1005;
const int PVN = 30005;
const int QFN = 1005;
struct num {
	int id;//1 2 3 4 5 6 int float high fraction #t#f string 
	int intnum;
	double floatnum;
	bool zf;
	int a[105] = {0};
	int fz, fm;
	bool tf;
	string name;
	string str;
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
		id = 6;
		str = b;
		str.erase(str.end() - 1);
		str.erase(str.begin());
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
		} else if (id == 5) {
			tf = c.tf;
		} else if (id == 6) {
			str = c.str;
		}
		return *this;
	}
	
	num operator+(const num &c) const;
	
	num operator-(const num &b) const;
	
	num operator*(const num &b) const;
	
	num operator/(const num &b) const;
	
	bool operator==(const num &b) const;
	
	bool operator<(const num &b) const;
};

num tru, fals;
num var[QVN];
int tot = 0;
num pvar[PVN];
int ptot = 0;

string fname[QFN];
string fmat[QFN];
string func[QFN];
int ftot = 0;

num cintnum(const num &b) {
	num a;
	a.id = 1;
	if (b.id == 1) {
		return b;
	} else if (b.id == 3) {
		a.intnum = 0;
		for (int i = 1; i <= b.a[0]; i++) {
			a.intnum = a.intnum * 10 + b.a[i];
		}
		if (b.zf == 1) {
			a.intnum = -a.intnum;
		}
	}
	return a;
}
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
	} else if (a.id == 5 && b.id == 5) {
		return a.tf == b.tf;
	} else if (a.id != 6) {
		a = cbignum(a), b = cbignum(b);
		if (a.zf != b.zf) return 0;
		if (a.a[0] != b.a[0]) return 0;
		for (int i = a.a[0]; i >= 1; i--) {
			if (a.a[i] != b.a[i]) return 0;
		}
		return 1;
	} else {
		return a.str == b.str;
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
	} else if (a.id != 6) {
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
	} else {
		return a.str < b.str;
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
	} else if (id != 6) {
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
	} else {
		a.str += b.str;
	}
	return a;
}
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
		a.zf = (zf != c.zf);
	}
	return a;
}
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
	} else if (obj.id == 5) {
		if (obj.tf == 0) {
			os << "#f";
		} else {
			os << "#t";
		}
	} else if (obj.id == 6) {
		os << obj.str;
	}
}

num getvalue(string s, int yl = 0, int yr = 0);

int lbra = 0, rbra = 0;
void calclr(string s) {
	int len = s.length();
	lbra = rbra = 0;
	int dd = 1, nd = 1;
	for (int i = 0; i < len; i++) {
		if (s[i] == '"') dd = !dd;
		if (s[i] == ';') nd = 0;
		if (dd && nd && s[i] == '(') lbra++;
		else if (dd && nd && s[i] == ')') rbra++;
	}
	return;
}

int getnex(string s, int pos) {
	int l = 1, r = 0, len = s.length();
	pos++;
	if (s[pos] == '"') {
		pos++;
		while (s[pos] != '"') {
			pos++;
		}
		pos++;
		return pos;
	}
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
bool isop(char c) {
	 return c == '+' || c == '-' || c == '*' || c == '/'
	 || c == '=' || c == '>' || c == '<'; // || c == '&' || c == '|' || c == '!';
}
bool isaon(string s) {
	return  (s[1] == 'a' && s[2] == 'n' && s[3] == 'd' && s[4] == ' ') ||
			(s[1] == 'o' && s[2] == 'r' && s[3] == ' ') ||
			(s[1] == 'n' && s[2] == 'o' && s[3] == 't' && s[4] == ' ');
}
bool numon(string s) {
	int len = s.length();
	if (s[0] == '"') return 1;
	int st = 0, dot = 0;
	if (s[0] == '-') st = 1;
	for (int i = st; i < len; i++) {
		if (s[i] == '.' || s[i] == '/') {
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
	if (s[0] == '"') {
		v.id = 6;
		v.str = s;
		//cout << v << endl;
		v.str.erase(v.str.end() - 1);
		v.str.erase(v.str.begin());
		return v;
	}
	int dot = 0;
	int st = 0;
	if (s[0] == '-') st = 1;
	for (int i = 0; i < len; i++) {
		if (s[i] == '.') {
			dot = 1;
			break;
		}
		if (s[i] == '/') {
			dot = 2;
			break;
		}
	}
	if (dot == 1) {
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
	} else if (dot == 2) {
		v.id = 4, v.fz = 0, v.fm = 0;
		int dot1 = 0;
		for (int i = st; i < len; i++) {
			if (s[i] == '/') {
				dot1 = 1;
				continue;
			}
			if (dot1) v.fm = v.fm * 10 + (s[i] - '0');
			else v.fz = v.fz * 10 + (s[i] - '0');
		}
		if (st == 1) v.fz = -v.fz;
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
num calcv(num a, num b, char c) {
	if (c == '+') return a + b;
	else if (c == '-') return a - b;
	else if (c == '*') return a * b;
	else if (c == '/') return a / b;
	if (c == '=') {
		num d;
		d.id = 5;
		if (a == b) {
			d.tf = 1;
		} else {
			d.tf = 0;
		}
		return d;
	} else if (c == '<') {
		num d;
		d.id = 5;
		if (a < b) {
			d.tf = 1;
		} else {
			d.tf = 0;
		}
		return d;
	} else if (c == '>')  {
		num d;
		d.id = 5;
		if (a < b) {
			d.tf = 0;
		} else if (a == b) {
			d.tf = 0;
		} else {
			d.tf = 1;
		}
		return d;
	} else if (c == 'a') {
		return a.tf == 1 && b.tf == 1;
	} else if (c == 'o') {
		return a.tf == 1 || b.tf == 1;
	}
	return a;
}

int findname(string s) {//for var 
	for (int i = 1; i <= tot; i++) {
		if (var[i].name == s) {
			return i;
		}
	}
	return 0;
}
int findpname(string s, int pl, int pr) {//for part var
	for (int i = pl + 1; i <= pr; i++) {
		if (pvar[i].name == s) {
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

string pref[1005];
int pretot = 10;
int ispref(string s) {
	for (int i = 1; i <= pretot; i++) {
		if (s == pref[i]) {
			return i;
		}
	}
	return 0;
}
num calcpref(string s, string s1, int yl = 0, int yr = 0) {
	num a;
	if (s1 == "display") {
		string s2;
		num b, c;
		int k1 = 0, k2 = getnex(s, k1);
		k1 = k2, k2 = getnex(s, k1);
		s2.assign(s, k1 + 1, k2 - k1 - 1);
	//	cout << "cp s2 " << s2 << endl << "yl yr " << yl << yr << endl;
		b = getvalue(s2, yl, yr);
		cout << b;
	} else if (s1 == "newline") {
		cout << endl;
	} else if (s1 == "quotient") {
		string s2;
		num b, c;
		int k1 = 0, k2 = getnex(s, k1);
		k1 = k2, k2 = getnex(s, k1);
		s2.assign(s, k1 + 1, k2 - k1 - 1);
		b = getvalue(s2, yl, yr);
		b = cintnum(b);
		k1 = k2, k2 = getnex(s, k1);
		s2.assign(s, k1 + 1, k2 - k1 - 1);
		c = getvalue(s2, yl, yr);
		c = cintnum(c);
		a = b;
		a.intnum = b.intnum / c.intnum;
	} else if (s1 == "modulo") {
		string s2;
		num b, c;
		int k1 = 0, k2 = getnex(s, k1);
		k1 = k2, k2 = getnex(s, k1);
		s2.assign(s, k1 + 1, k2 - k1 - 1);
		b = getvalue(s2, yl, yr);
		b = cintnum(b);
		k1 = k2, k2 = getnex(s, k1);
		s2.assign(s, k1 + 1, k2 - k1 - 1);
		c = getvalue(s2, yl, yr);
		c = cintnum(c);
		a = b;
		a.intnum = b.intnum % c.intnum;
	}
	return a;
}
num getvalue(string s, int yl, int yr) {
	//cout << endl << "s " << s << endl;
	if (numon(s)) {
		return numv(s);
	} else if (yr > yl && findpname(s, yl, yr)) {
		return pvar[findpname(s, yl, yr)];
	} else if (findname(s)) {
		return var[findname(s)];
	} else if (isop(s[1]) || isaon(s)) {
		int k1, k2, k3;
		k1 = getnex(s, 0), k2 = getnex(s, k1), k3 = getnex(s, k2);
		string s1 (s, k1 + 1, k2 - k1 - 1), s2;
		if (s[1] == 'n') {
			num ans = getvalue(s1);
			ans.tf = !ans.tf;
			return ans;
		}
		s2.assign(s, k2 + 1, k3 - k2 - 1);
		//cout << "s1 " << s1 << endl << "s2 " << s2 << endl << endl;
		num v1 = getvalue(s1, yl, yr), v2 = getvalue(s2, yl, yr), v3;
		v3 = v1;
		v1 = calcv(v3, v2, s[1]);
		if (s[1] == '=' || s[1] == '<' || s[1] == '>') {
			return v1;
		}
		while (s[k3] == ' ') {
			k2 = k3;
			k3 = getnex(s, k2);
			s2.assign(s, k2 + 1, k3 - k2 - 1);
			v2 = getvalue(s2, yl, yr);
			v1 = calcv(v1, v2, s[1]);
		}
		return v1;
	} else {
		int k1 = 1, k2 = getnex(s, k1), k3;
		int fr = 0;
		string s1 (s, k1, k2 - k1), s2;
		if (s1 == "if") {
		//	cout << "here" << endl;
			k1 = k2, k2 = getnex(s, k1);
			s1.assign(s, k1 + 1, k2 - k1 - 1);
			num d = getvalue(s1, yl, yr);
			k1 = k2, k2 = getnex(s, k1);
			if (d == fals) {
				k1 = k2, k2 = getnex(s, k1);
		//		cout << "go" << endl;
		//		system("pause");
			}
			s1.assign(s, k1 + 1, k2 - k1 - 1);
		//	cout << "s1-2 " << s1 << endl;
			return getvalue(s1, yl, yr);
		} else if (s1 == "cond") {
			k3 = k2;
			int use = 0;
			while (1) {
				k2 = k3, k1 = k3, k3 = getnex(s, k1);
				k1 = k2 + 1, k2 = getnex(s, k1);
				s1.assign(s, k1 + 1, k2 - k1 - 1);
				//cout << "s1 " << s1 << endl;
				if (s1 != "else") {
					num d = getvalue(s1, yl, yr);
					if (d == tru) {
						use = 1;
					}
				} else use = 1;
				if (use) {
					k1 = k2, k2 = getnex(s, k1);
					s2.assign(s, k1 + 1, k2 - k1 - 1);
					//cout << "s2 " << s2 << endl;
					num d = getvalue(s2, yl, yr);
					return d;
				}
			}
		} else if (ispref(s1)) {
			return calcpref(s, s1, yl, yr);
		}
		//cout << "s1 " << s1 << endl;
		fr = findfunc(s1);
		/*
		cout << "here" << endl;
		k3 = getnex(s, k2);
		s2.assign(s, k2 + 1, k3 - k2 - 1);
		cout << "s1 " << s1 << endl << "s2 " << s2 << endl;
		*/
		
		//define var
		int pl = ptot, pr = ptot;//range of ptot
		string y = fmat[fr];//(square x)
		string y1;
		//cout << "y " << y << endl;
		int x1 = 0, x2 = getnex(y, x1);
		//cout << y[x1] << y[x2] << '?' << endl;
		while (y[x2] == ' ') {
			x1 = x2, x2 = getnex(y, x1);
			y1.assign(y, x1 + 1, x2 - x1 - 1);
			ptot++, pr = ptot;
			pvar[pr].name = y1;
		//	cout << "var " << y1 << endl;
		}
		//getvalue(every element);
		if (pr > pl) {
			for (int i = pl + 1; i <= pr; i++) {
				k1 = k2, k2 = getnex(s, k1);
				s1.assign(s, k1 + 1, k2 - k1 - 1);
				pvar[i] = getvalue(s1, yl, yr);
		//		cout << "pvar " << pvar[i] << endl;
			}
		}
		string z = func[fr];//(* x x)
		//cout << "func " << z << endl;
		k1 = -1, k2 = getnex(z, k1);
		num a;
		while (1) {
			s2.assign(z, k1 + 1, k2 - k1 - 1);
			//cout << "s2 " << s2 << endl;
			if (pr > pl) a = getvalue(s2, pl, pr);
			else a = getvalue(s2);
			if (z[k2] != ' ') break;
			k1 = k2, k2 = getnex(z, k1);
		//	cout << "1cget\n";
	//		cout << "zk1" << z[k1] << "zk1+1" << z[k1+1] << endl;
		}
		return a;
		//cout << sf << endl;
	}
	return 0;
}

int main() {
	pref[1] = "display";
	pref[2] = "newline";
	pref[3] = "quotient";
	pref[4] = "modulo";
	string s, s1;
	s.clear();
	char forgets[1005];
	num a = 1, b = 1.0;

	//pre
	tru.id = fals.id = 5;
	tru.tf = 1, fals.tf = 0;	
	//preend
	int predefine = 3;
	int cpre = 0;
	while (1) {
		if (cpre < predefine) {
		
		cpre++;
		if (cpre == 1) {
			s = "(define #t 0)";
		} else if (cpre == 2) {
			s = "(define #f 0)";
		} else {
			var[1].id = 5;
			var[1].tf = 1;
			var[2].id = 5;
			var[2].tf = 0;
		}
		
		} else {
		
		gets(forgets);
		s += forgets;
		if (s == "Requiescat in pace") break;
		calclr(s);
		if (lbra != rbra) continue;
		bool dd = 1;
		string::iterator ti, it;
		it = s.begin();
		while (it != s.end() && !(dd == 1 && (*it) == ';')) {
			if ((*it) == '"') dd = !dd;
			it++;
		}
		if ((*it) == ';') {
			while (it != s.end()) {
				s.erase(it);
			}
			//cout << s << endl;
		}
		it = s.begin();
		while (*it == ' ' && !s.empty()) {
			s.erase(it);
		}
		ti = s.end() - 1;
		while (*ti == ' ' && !s.empty()) {
			s.erase(ti);
			ti--;
		}
		dd = 1;
		if (!s.empty()) {
			for (ti = s.begin(), it = ti + 1; it != s.end(); ti = it, it++) {
				if (*it == '"') dd = !dd;
				if (dd && (*ti) == ' ' && (*it) == ' ') {
					s.erase(it);
					//cout << *ti << *it << "h\n";
					it--;
				} else if (dd && (*ti) == '(' && (*it) == ' ') {
					s.erase(it);
					it--;
				} else if (dd && (*ti) == ' ' && (*it) == ')') {
					s.erase(ti);
					it--, it--;
				}
			}
		}
		
		}
		//cout << s << endl;
		//define
		ptot = 0;
		if (s.length() >= 8) {
			string s2 (s, 1, 6), s3;
			if (s2 == "define") {
				int k1 = 7, k2 = getnex(s, k1), k3 = getnex(s, k2);
				if (s[k1 + 1] == '(') {
					k1 = 9, k2 = getnex(s, k1);
					ftot++;
					fname[ftot].assign(s, k1, k2 - k1);
					k1 = 7, k2 = getnex(s, k1), k3 = getnex(s, k2);
					fmat[ftot].assign(s, k1 + 1, k2 - k1 - 1);
					func[ftot].assign(s, k2 + 1, k3 - k2 - 1);
					while (s[k3] == ' ') {
						k2 = k3, k3 = getnex(s, k3);
						s3.assign(s, k2 + 1, k3 - k2 - 1), s3 = ' ' + s3;
						func[ftot] += s3;
					}
					//cout << fname[ftot] << endl << fmat[ftot] << endl << func[ftot] << endl;
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
				a = getvalue(s);
				s.clear();
			}
		} else if (!s.empty()) {
			a = getvalue(s);
			s.clear();
		}
	}
	return 0;
}

