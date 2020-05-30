#include "QInt.h"

QInt::QInt()
{
	clearBit();
}
void QInt::setBit(int const& pos, bool const& val)
{
	if (pos < 0 || pos >= NUMBER_OF_BIT) return;

	unsigned int* reg = &data.int32[N_UINT - 1 - pos / 32];

	int i = pos % 32;

	if (val) {
		// gan gia tri 1
		*reg = *reg | (1 << i);
	}
	else {
		// gan gia tri 0
		*reg = *reg & ~(1 << i);
	}
}
bool QInt::getBit(int pos)const
{
	int i = pos % 32;

	return ((this->data.int32[N_UINT - 1 - pos / 32]) >> i & 1);
}
string QInt::toString()
{
    stringstream out;
    
    out << "BIN: ";
    out << exportData(BIN) << endl;

    out << "DEC: ";
    out << exportData(DEC) << endl;

    out << "HEX: ";
    out << exportData(HEX) << endl;
    
    return out.str();
}

string QInt::toBinStr()
{
    // if value = 0, this func do not return anything
    // so we need return "0" if it happen 
    // this code can be accept to all base
    if (*this == 0) return "0";

    stringstream  out;

    for (int j = 0; j < N_UINT; ++j)
    {
        for (int i = 31; i >= 0; --i)
        {
            out << ((data.int32[j] << (31 - i)) >> 31);
        }
    }

    // trim 
    string str = out.str();

    int i = 0;
    while (str[i] == '0') i++;

    return str.substr(i);
}


string QInt::toHexStr()
{
    // if value = 0, this func do not return anything
    // so we need return "0" if it happen 
    // this code can be accept to all base
    if (*this == 0) return "0";

    stringstream temp;
    bool startPrint = false;

    for (int j = 0; j < N_BYTE; ++j)
    {
        char c = data.byteAt(j);
        if (startPrint || c != 0)
        {
            string bt = bin2hex(c);

            if (bt.length() == 2) {
                temp << bt;
                startPrint = true;
                continue;
            }

            if (bt.length() == 0) {
                temp << "00";
            }
            else {
                // bt.length() == 1
                if (!startPrint)
                {
                    temp << bt;
                }
                else
                {
                    temp << 0 << bt;
                }
            }

            startPrint = true;
        }
    }

    // this for toUpperCase
    string str = temp.str();
    for (char& i : str)
    {
        if (i >= 'a' && i <= 'z')
        {
            i = i + 'A' - 'a';
        }
    }

    return str;
}

string QInt::exportData(int base)
{
    switch (base)
    {
    case BIN:
        return toBinStr();
        
    case HEX:
        return toHexStr();
        
    // return in Decimal by default
    default:
        return toDecStr();
    }  
}
QInt QInt::DectoBin(string s)
{
	int checkNegative = 0; //kiem tra so am
	QInt res;
	if (s[0] == '-')
	{
		s.erase(0, 1);//xoa dau -
		checkNegative = 1; //la so am
	}
	int i = 0;

	while (s != "")
	{
		//chuyen str10 qua str2
		int bit = (s[s.length() - 1] - '0') % 2;
		res.setBit(i, bit);
		s = div2(s);
		i++;
	}
	if (checkNegative == 1)//la so am
	{
		//chuyen qua bu 2
		res = res.toConvertBu2();
	}
	return res;
}
QInt QInt::add(QInt const& A)
{
	//neu bang 0 + A thi tra ve A
	if (isZero())
	{
		*this = A;
		return *this;
	}

	if (A.isZero()) return *this;

	QInt result;
	bool bit = 0; //giong nhu so nho

	for (int i = 0; i < N_UINT * 32; i++)
	{
		int temp = bit + A.getBit(i) + getBit(i);

		switch (temp)
		{
		case 0: //0+0=0
		{
			result.setBit(i, 0);
			bit = 0;
			break;
		}
		case 1: //0+1=1 or 1+0=1
		{
			result.setBit(i, 1);
			bit = 0;
			break;
		}
		case 2://1+1=0 nho 1
		{
			result.setBit(i, 0);
			bit = 1;
			break;
		}
		case 3: //1+1+1(nho)=1 nho 1
		{
			result.setBit(i, 1);
			bit = 1;
			break;
		}

		}
	}

	*this = result;

	return *this;
}
QInt QInt::sub(QInt const& A)
{
	// FOR CASE 2 PARAMETER ARE EQUAL (for skip error occurred when call MIN - MIN)
	if (*this == A) {
		*this = 0;
		return *this;
	}

	// Alway pass greater parameter to first parameter of addition (to skip bug that cannot convert MIN_VALUE)
	//QInt result = (A > * this) ? A.toConvertBu2() + (*this) : A + (*this).toConvertBu2();
	QInt result;
	if (*this > A) 
	{
		result = *this;
		result.add(A.toConvertBu2());
	}
	else {
		result = A.toConvertBu2();
		result.add(*this);
	}
	
	*this = result;
	return *this;
}
bool QInt::isNegative() const
{
	return ((this->getBit(N_UINT * 32 - 1)) == 1);
}
bool QInt::QInt::isZero() const
{
	for (int i = 0; i < N_UINT; i++)
	{
		if (this->data.int32[i] != 0)
		{
			return false;
		}
	}

	return true;
}
//str2->>str10
string QInt::toDecStr()
{
    // if value = 0, this func do not return anything
    // so we need return "0" if it happen 
    // this code can be accept to all base
    if (*this == 0) return "0";

	QInt p = *this;

	int checkNegative = 0;
	if (p.isNegative())
	{
		//Neu la so am thi chuyen qua bu 2
		p = p.toConvertBu2();
		checkNegative = 1;
	}
	//p luc nay la so duong
	string s = p.toBinStr();//s[0] luon bang 1 o vi tri so 0
	int pos = 0;

	string res = "0";
	int count = s.length() - 1;
	while (pos < s.length())
	{
		int bit = s[pos] - '0';
		if (bit != 0)
		{ 
			string temp = Power(2, count);
			res = add2Str(res, temp);
		}
		count--;
		pos++;
	}
	if (checkNegative == 1)
	{
		res = '-' + res;
	}
	return res;
}

QInt& QInt::operator=(QInt const& other)
{
    if (this != &other) {
        for (int i = 0; i < N_UINT; i++) {
            this->data.int32[i] = other.data.int32[i];
        }
    }

    return *this;
}

bool QInt::operator==(QInt const& other) const
{
    if (&other == this) return true;

    bool res = true;
    for (int i = 0; i < N_UINT; ++i)
    {
        res = (this->data.int32[i] == other.data.int32[i]) & res;
    }

    return res;
}

bool QInt::operator==(long long const& n) const
{
    QInt t = n;
    return (*this == t);
}

QInt::QInt(long long const& n)
{
    // long long take only 8 low byte (right side)

    unsigned int low = ((n << 32) >> 32);
    unsigned int high = (n >> 32); // n >> 32 here is SAR because n is signed

    data.int32[N_UINT - 1] = low;
    data.int32[N_UINT - 2] = high;

    int mask = 0;

    // check sign of n
    if ((high >> 31) == 1) // SHR because high is unsigned
    {
        // negative number
        mask = -1;
    }

    for (int i = 0; i < N_UINT - 2; ++i)
    {
        data.int32[i] = mask;
    }
}

QInt const QInt::operator<<(int count)
{
    QInt t(*this);
    t.SHL(count);

    return t;
}

QInt const QInt::operator>>(int count)
{
    // shift right is SAR
    QInt t(*this);
    t.SAR(count);

    return t;
}

QInt const QInt::operator|(QInt const& other)
{
    QInt t = (*this);
    for (int i = 0; i < N_UINT; ++i)
    {
        t.data.int32[i] = (this->data.int32[i] | other.data.int32[i]);
    }

    return t;
}

QInt const QInt::operator&(QInt const& other)
{
    QInt t = (*this);
    for (int i = 0; i < N_UINT; ++i)
    {
        t.data.int32[i] = (this->data.int32[i] & other.data.int32[i]);
    }

    return t;
}

QInt QInt::MIN_VALUE()
{
    QInt t = 0;
    t.setBit(NUMBER_OF_BIT - 1);

    return t;
}

QInt QInt::MAX_VALUE()
{
    QInt t = -1;
    t.setBit(NUMBER_OF_BIT - 1, false);
    
    return t;
}

char QInt::hex2bin(char c)
{
    char res = 0;
    if (c >= '0' && c <= '9') 
    {
        res = c - '0';
        return res;
    } 
    
    if (c >= 'A' && c <= 'F')
    {
        res = 10 + c - 'A';
        return res;
    }

    if (c >= 'a' && c <= 'f')
    {
        res = 10 + c - 'A';
        return res;
    }

    // return 0 if c is not valid hex code 
    return res;
}

string QInt::bin2hex(unsigned char const& c)
{
    stringstream out;
    // mo
    char l = c >> 4;
    if (l != 0) {
        if (l < 10) {
            out << (char)(l + '0');
        }
        else {
            out << (char)(l + 'A' - 10);
        }
    }
    // lo
    char r = c & 0b00001111;
    if (r != 0) {
        if (r < 10) {
            out << (char)(r + '0');
        }
        else {
            out << (char)(r + 'A' - 10);
        }
    }
    else {
        if (out.str().length() == 1) out << 0;
    }

    return out.str();
}

void QInt::SHL(int count)
{
    // debug
    //cout << "SHL CALLED - " << toString();

    for (int i = 0; i < count; ++i)
    {
        for (int j = 0; j < N_UINT; ++j)
        {
            data.int32[j] = data.int32[j] << 1;

            // set bit0 to content of bit31 on prev int32 (if exist)
            if (j < N_UINT - 1)
            {
                unsigned int t = data.int32[j + 1];
                data.int32[j] = data.int32[j] | ((t >> 31) & 1);
            }
        }
    }
}

void QInt::SHR(int count)
{
    for (int i = 0; i < count; ++i)
    {
        for (int j = N_UINT - 1; j >= 0; --j)
        {
            data.int32[j] = data.int32[j] >> 1;

            // set bit31 to content of bit0 on next int32 (if exist)
            if (j > 0)
            {
                unsigned int t = data.int32[j - 1];
                data.int32[j] = data.int32[j] | ((t & 1) << 31);
            }
        }
    }
}

void QInt::SAR(int count)
{
    bool msb = (data.int32[0] >> 31) & 1;
    for (int i = 0; i < count; ++i) {
        SHR(1);
        if (msb) setBit(NUMBER_OF_BIT - 1);
    }
}

void QInt::ROR(int count)
{
    QInt l = (*this);
    QInt r = (*this);

    l.SHR(count);
    r.SHL(NUMBER_OF_BIT - count);

    *this = (l | r);
}

void QInt::ROL(int count)
{
    QInt l = (*this);
    QInt r = (*this);

    l.SHR(NUMBER_OF_BIT - count);
    r.SHL(count);

    *this = (l | r);
}

void QInt::clearBit()
{
    for (int j = 0; j < N_UINT; ++j)
    {
        data.int32[j] = 0;
    }
}

QInt::QInt(string text, int base)
{
    clearBit();

    switch (base)
    {
    case BIN:

        for (int i = 0; i < text.length(); ++i)
        {
            SHL(1);
            unsigned char state = text.at(i) - '0';

            // update LSB
            data.int32[N_UINT - 1] = data.int32[N_UINT - 1] | state;
        }

        break;
    case HEX:
        for (int i = 0; i < text.length(); ++i)
        {
            SHL(4);
            unsigned char state = hex2bin(text.at(i));

            // update LSB
            // two option are the same

            //data.int32[N_UINT - 1] = data.int32[N_UINT - 1] | state;
            data.byteAt(N_BYTE - 1) = data.byteAt(N_BYTE - 1) | state;
        }

        break;

	case DEC:
	{
		*this = DectoBin(text);
	}
    default:
        break;
    }
}

QInt::QInt(QInt const& other)
{
    *this = other;
}
QInt QInt::operator~ () const
{
	QInt result;
	for (int i = 0; i < N_UINT; i++)
	{
		result.data.int32[i] = ~this->data.int32[i];
	}
	return result;
}
QInt QInt::operator^ (const QInt& A) const
{
	QInt result;
	for (int i = 0; i < N_UINT; i++)
	{
		result.data.int32[i] = this->data.int32[i] ^ A.data.int32[i];
	}
	return result;
}
QInt QInt::operator+ (const QInt& A) const
{
	// Addition without check overflow
	QInt result = *this;
	result.add(A);

	//Check overflow
	//vi du: A+B th� A,B cung dau ma cho ket qua trai dau
	if (!A.isNegative() && !isNegative()&& result.isNegative())
	{
		throw("Overflow");
	}
	if (A.isNegative() && isNegative() && !result.isNegative())
	{
		throw("Overflow");
	}
	return result;
}
bool QInt::operator!= (QInt const& B) const
{
	return !(*this == B);
}
QInt QInt::toConvertBu2() const
{
	if (isZero()) return *this;
	//MIN can't be converted
	if (*this == MIN_VALUE()) return *this;

    QInt res;
	//dao chuoi qua bu 1
	res = ~(*this);

	QInt temp = 1;

    //bu 1 cong them 1 de duoc so bu 2
	res = res + temp;

	return res;
}
QInt QInt::operator- (const QInt& A) const
{
	// Subtraction without check overflow
	QInt result = *this;
	result.sub(A);

	//Check overflow
	//vi du: A-B thi A va (-B)(so bu 2 cua B) cung dau ma cho ket qua trai dau
	if (!A.toConvertBu2().isNegative() && !isNegative() && result.isNegative())
	{
		throw("Overflow");
	}
	if (A.toConvertBu2().isNegative() && isNegative() && !result.isNegative())
	{
		throw("Overflow");
	}
	return result;
}

bool QInt::operator>(QInt const& B) const
{
	if (!isNegative() && B.isNegative()) return true;
	if (isNegative() && !B.isNegative()) return false;
	for (int i = 0; i < N_UINT; i++)
	{
		if (data.int32[i] > B.data.int32[i])
			return true;
		if (data.int32[i] < B.data.int32[i])
			return false;
	}
	
	return false;
}
bool QInt::operator<(QInt const& B) const 
{
	return !(*this > B || *this == B);
}

//Booth's Multiplication Algorithm
QInt QInt::operator* (const QInt& B) const
{
	//Thuc hien phep nhan M*Q
	QInt M = *this;
	QInt Q = B;

	//Mot trong 2 so = 0 thi tra ve ket qua la 0
	if (B.isZero() || isZero()) return 0;

	//Check overflow
	// special case
	if ((M == MIN_VALUE() && Q == -1) || (Q == MIN_VALUE() && M == -1)) throw ("Overflow");

	// general case
	//if (M > MAX_VALUE() / Q || M < MIN_VALUE() / Q) throw ("Overflow");

	QInt A = 0;
	int k = N_UINT * 32;
	int Q1 = 0;

	while (k > 0)
	{
		// ignore overflow of addition/subtraction here (by add, sub builtin function)
		
		//Q0Q1 = 10 thi A = A - M
		if (Q.getBit(0) == 1 && Q1 == 0)
		{
			A.sub(M);
		}
		//Q0Q1 = 01 thi A = A + M
		else if (Q.getBit(0) == 0 && Q1 == 1)
		{
			A.add(M);
		}
		
		//dich phai [A,Q,Q1]
		Q1 = Q.getBit(0);
		Q.SHR(1);
		Q.setBit(NUMBER_OF_BIT - 1, A.getBit(0));
		A.SAR(1);
		k--;
	}
	string s = A.toBinStr() + Q.toBinStr();
	
	QInt result(s, BIN);

	//check overflow again
//	if (result / B != *this) throw ("Unknown Overflow");
	
	return result;
}
//Restoring Division Algorithm
QInt QInt::operator/ (const QInt& P) const
{
	QInt Q = *this;
	QInt M = P;
	QInt A = 0;//Q>0 thi gan A=0

	if (M.isZero()) throw("Division by 0");
	if (Q.isZero()) return 0;

	//check overflow
	if (Q == MIN_VALUE() && M == -1) throw ("Overflow");

	if (Q.isNegative())
	{
		//Q<0 thi gan A=1
		for (int i = 0; i < N_UINT * 32; i++)
		{
			A.setBit(i, 1);
		}
	}
	//Neu so am thi chuyen ve duong
	if (Q.isNegative()) Q = Q.toConvertBu2();
	if (M.isNegative()) M = M.toConvertBu2();

	int k = N_UINT * 32;
	while (k > 0)
	{
		A.SHL(1);
		A.setBit(0, Q.getBit(NUMBER_OF_BIT - 1));
		Q.SHL(1);
		A = A - M;
		//Neu A<0: Q0=0 va A+M=A
		if (A.isNegative())
		{
			Q.setBit(0, 0);
			A = A + M;
		}
		else
		{
			//Nguoc lai: Q0=1
			Q.setBit(0, 1);
		}
		k--;
	}
	
	//neu 2 so khac thi chuyen ve so am 
	/*if ((*this * P).isNegative())
	{
		Q = Q.toConvertBu2();
	}
	*/
	if ((*this).isNegative() ^ P.isNegative())
	{
		Q = Q.toConvertBu2();
	}

	return Q;
}
string QInt::div2(string text)
{
	string result = "";
	int save = 0;
	for (int i = 0; i < text.length(); i++)
	{
		save = (text[i] - '0') + save * 10;
		if (save == 0 && i == 0 || i > 0)
		{
			result += save / 2 + '0';
		}
		save = save / 2;
	}
	return result;
}

string QInt::add2Str(string a, string b)
{
	string res = "";
	int numremember = 0;//luu so nho sau moi lan cong
	//them 0 vao moi chuoi de cho 2 chuoi co do dai bang nhau
	if (a.length() > b.length())
	{
		while (a.length() != b.length())
		{
			b = '0' + b;
		}
	}
	else
	{
		while (a.length() != b.length())
		{
			a = '0' + a;
		}
	}

	for (int i = a.length() - 1; i >= 0; --i)
	{
		int temp = (a[i] - '0') + (b[i] - '0') + numremember;
		
		res += (temp % 10) + '0';

		numremember = (temp > 9) ? 1 : 0;
	}

	//neu la so nho cuoi cung bang 1 thi + them1 vao chuoi
	if (numremember == 1)
		res = res + '1';
	//do chuoi bi nguoc nen chuoi doi nguoc lai
	reverse(res.begin(), res.end());

	return res;
}
string QInt::mul2Str(string a, string b)
{
	//chuyen chuoi qua so
	int ka = atoi(a.c_str());
	int kb = atoi(b.c_str());

	if (ka == 0 || kb == 0)//phep nhan neu 1 trong 2 so bang 0 thi ket qua = 0
		return "0";

	string res = a;
	
	for (int i = 0; i < kb - 1; ++i)
	{
		res = add2Str(res, a);
	}
	return res;
}
string QInt::Power(unsigned int a, unsigned int n)
{
	if (n == 0)//qui uoc a^0 = 1
		return "1";

	//chuyen so thanh chuoi
	string res = to_string(a);
	string A = to_string(a);

	for (int i = 0; i < n - 1; ++i)
	{
		res = mul2Str(res, A);
	}
	return res;
}

