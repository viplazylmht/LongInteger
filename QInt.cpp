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

    stringstream  out(std::ios_base::app | std::ios_base::in | std::ios_base::out);

    for (int j = 0; j < N_UINT; ++j)
    {
        for (int i = 31; i >= 0; --i)
        {
            int p = ((data.int32[j] << (31 - i)) >> 31);
			out << p;
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
	if (*this == 0) return (*this = A);

	QInt result;
	bool bit = 0; //giong nhu so nho

	for (int i = 0; i < NUMBER_OF_BIT; i++)
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
	if (*this == A)	return (*this = 0);

	QInt result = *this;
	result.add(A.toConvertBu2());

	return (*this = result);
}

bool QInt::isNegative() const
{
	return ((this->getBit(NUMBER_OF_BIT - 1)) == 1);
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
        res = 10 + c - 'a';
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
	//MIN and ZERO can't be converted
	if (*this == 0 || *this == MIN_VALUE()) return *this;

    QInt res;
	//dao chuoi qua bu 1
	res = ~(*this);

    //bu 1 cong them 1 de duoc so bu 2
	res = res + 1;

	return res;
}
QInt QInt::operator- (const QInt& A) const
{
	if ((A < 0) && (*this > MAX_VALUE() + A)) throw("Overflow");
	if ((A > 0) && (*this < MIN_VALUE() + A)) throw("Overflow");

	// Subtraction without check overflow
	QInt result = *this;
	result.sub(A);

	return result;
}

QInt QInt::operator-() const
{
	if (*this == MIN_VALUE()) throw "Overflow";
	
	return this->toConvertBu2();
}

bool QInt::operator>(QInt const& B) const
{
	if (*this == B) return false;
	
	// special case that A and B are not the same sign
	if (!isNegative() && B.isNegative()) return true;
	if (isNegative() && !B.isNegative()) return false;

	// special case with MIN included
	if (B == MIN_VALUE() && *this != MIN_VALUE()) return true;
	if (B != MIN_VALUE() && *this == MIN_VALUE()) return false;

	// in this case, both A and B are negative number, but not MIN
	if (isNegative()) return (-*this) < (-B);

	// in this case, both A and B are positive number, or 0
	for (int i = 0; i < N_UINT; i++)
	{
		if (data.int32[i] > B.data.int32[i]) return true;
		if (data.int32[i] < B.data.int32[i]) return false;
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
	//Mot trong 2 so = 0 thi tra ve ket qua la 0
	if (B == 0 || *this == 0) return 0;

	//Thuc hien phep nhan M*Q
	QInt M = *this;
	QInt Q = B;

	// check overflow
	// special case
	if ((M == MIN_VALUE() && Q == -1) || (Q == MIN_VALUE() && M == -1)) throw ("Overflow");

	// general case
	if (M > MAX_VALUE() / Q || M < MIN_VALUE() / Q) throw ("Overflow");

	QInt A = 0;
	int k = NUMBER_OF_BIT;
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
	if (result / B != *this) throw ("Unknown Overflow");
	
	return result;
}
//Restoring Division Algorithm
QInt QInt::operator/ (const QInt& P) const
{
	QInt Q = *this;
	QInt M = P;
	QInt A = 0;

	if (M == 0) throw("Division by 0");
	if (Q == 0) return 0;

	//check overflow
	if (Q == MIN_VALUE() && M == -1) throw ("Overflow");

	// Luu lai dau cua ket qua
	// ket qua la true (so am) khi va chi khi 1 trong 2 (Q, M) la so am
	bool resultSign = Q.isNegative() ^ M.isNegative();

	// Chuyen Q, M ve so duong, tat ca phep tinh tinh toan se doi voi so duong
	if (Q.isNegative()) Q = Q.toConvertBu2();
	if (M.isNegative()) M = M.toConvertBu2();

	int k = NUMBER_OF_BIT;
	while (k > 0)
	{
		A.SHL(1);
		A.setBit(0, Q.getBit(NUMBER_OF_BIT - 1));
		Q.SHL(1);
		A.sub(M); // bo qua kiem tra tran so

		//Neu A<0: Q0=0 va A+M=A
		if (A.isNegative())
		{
			Q.setBit(0, 0);
			A.add(M); // bo qua kiem tra tran so
		}
		else
		{
			//Nguoc lai: Q0=1
			Q.setBit(0, 1);
		}
		k--;
	}

	// Phuc hoi lai dau cua ket qua
	if (resultSign)
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
		
		result += save / 2 + '0';
		save = save % 2;
	}
	
	// trim first 0
	int pos = 0;
	while (result[pos] == '0') pos++;
	
	return result.substr(pos);
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
		

		res.insert(res.begin(), (temp % 10) + '0');

		numremember = (temp > 9) ? 1 : 0;
	}

	//neu la so nho cuoi cung bang 1 thi + them1 vao chuoi
	if (numremember == 1)
		res.insert(res.begin(), '1');

	return res;
}
string QInt::mul2Str(string a, string b)
{
	//chuyen chuoi qua so
	int kb = 1;

	try {
		kb = parseInt(b);
		int ka = parseInt(a);

		if (ka == 0 || kb == 0) //phep nhan neu 1 trong 2 so bang 0 thi ket qua = 0
			return "0";
	}
	catch (std::invalid_argument const& e)
	{
		return "0";
	}
	catch (std::out_of_range const& e)
	{
		// do nothing because a is out of range int
		// b only take 2 (number) to parameter
	}

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

int QInt::parseInt(string const& intStr)
{
	try
	{
		int i = std::stoi(intStr);
		return i;
	}
	catch (std::invalid_argument const& e)
	{
		throw e;
	}
	catch (std::out_of_range const& e)
	{
		throw e;
	}
}