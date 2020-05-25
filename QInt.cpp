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

bool QInt::getBit(int pos)
{
	//if (pos < 0 || pos >= NUMBER_OF_BIT) return ;

	int i = pos % 32;

	return ((this->data.int32[N_UINT - 1 - pos / 32]) >> i & 1);
}
string QInt::toString()
{
    stringstream out;
    
    out << "BIN: ";
    out << exportData(BIN) << endl;

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
            startPrint = true;
            string bt = bin2hex(c);

            if (bt.length() == 2) {
                temp << bt;
                continue;
            }

            if (bt.length() == 0) {
                temp << "00";
            }
            else {
                // bt.length() == 1
                temp << 0 << bt;
            }
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
    }
	// trim 
	string str = out.str();

	int i = 0;
	while (str[i] == '0') { i++; }

	return str.substr(i);
}
QInt QInt::DectoBin(string s)
{
	int kt = 0;//kiem tra so am
	QInt res;
	if (s[0] == '-')
	{
		s.erase(0, 1);
		kt = 1;
	}
	int i = 0;
	while (s != "0")
	{
		int bit = (s[s.length() - 1] - '0') % 2;
		res.setBit(i, bit);
		s = div2(s);
		//res += bit + '0';
		i++;
	}
	//reverse(res.begin(),res.end());

	if (kt == 1)
	{
		//chuyen qua bu 2
		res = res.convert();
	}
	
	return res;
}
bool QInt::isNegative()
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
	//string s = p.toBinStr();
	int kt = 0;
	if (p.isNegative())
	{
		p = p.convert();
		kt = 1;
	}
	//p luc nay la so duong
	string s = p.toBinStr();
	int pos = 0;
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == '1')
		{
			pos = i;
			break;
		}
	}
	string res;
	while (pos < s.length())
	{
		int k = s[pos] - '0';
		res = mul2(res, k);
		pos++;
	}
	if (kt == 1)
	{
		res = '-' + res;
	}
	return res;
}
string QInt::mul2(string s, int pos)
{
	string result = "";
	int c = pos;

	for (int i = s.length() - 1; i >= 0; i--)
	{
		int t = s[i] - '0';
		t = t * 2 + c;
		result += (t % 10 + '0');
		c = t / 10;
	}
	if (c > 0)
		result += (c + '0');

	reverse(result.begin(), result.end());

	return result;
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

bool QInt::operator==(QInt const& other)
{
    if (&other == this) return true;

    bool res = true;
    for (int i = 0; i < N_UINT; ++i)
    {
        res = (this->data.int32[i] == other.data.int32[i]) & res;
    }

    return res;
}

bool QInt::operator==(long long const& n)
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

// SAL is tha same as SHL
void QInt::SAL(int count)
{
    SHL(count);
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

QInt::QInt(string text, int op)
{
    clearBit();

    switch (op)
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
QInt QInt::operator+ (QInt& A)
{
	QInt result;
	if (isZero())
		return A;
	bool cr = 0;
	for (int i = 0; i < N_UINT * 32; i++)
	{
		int temp = cr + A.getBit(i) + getBit(i);

		switch (temp)
		{
		case 0: //0+0=0
		{
			result.setBit(i, 0);
			cr = 0;
			break;
		}
		case 1: //0+1=1 or 1+0=1
		{
			result.setBit(i, 1);
			cr = 0;
			break;
		}
		case 2://1+1=0 nho 1
		{
			result.setBit(i, 0);
			cr = 1;
			break;
		}
		case 3: //1+1+1(nho)=1 nho 1
		{
			result.setBit(i, 1);
			cr = 1;
			break;
		}
		
		}
	}
	return result;
}
QInt QInt::convert()
{
	QInt res;
	if (isZero())
		return *this;
	if (isNegative())//la so -
	{
		//tru 1
		QInt tru1;
		for (int i = 0; i < N_BYTE - 1; ++i)
		{
			tru1.data.byteAt(i) = 0b11111111;
		}

		res = res + tru1;
		res = ~res;
		//dao bit
	}
	else
	{
		//bu 1
		res = ~(*this);
		//cout << res.toBinStr();
		QInt temp("1", BIN);
		//cong them 1 de duoc so bu 2
		res = res + temp;
	}

	return res;
}
QInt QInt::operator- (QInt& A)
{
	QInt result;
	result = A.convert() + (*this);
	return result;
}
string QInt::div2(string text)
{
	string result = "";
	int t = 0;
	for (int i = 0; i < text.length(); i++)
	{
		t = t * 10 + (text[i] - '0');
		if (i > 0 || (i == 0 && t >= 2))
		{
			result += t / 2 + '0';
		}
		t = t % 2;
	}
	return result;
}
