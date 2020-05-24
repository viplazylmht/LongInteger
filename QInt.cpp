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
		*reg = *reg & !(1 << i);
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

	out << "\nBIN: ";
	out << toBinStr() << endl;

	out << "\nDEC: ";
	out << toDecStr();

	//out << "\n\nHEX: ";
	//out << toHexStr() << endl;

	return out.str();
}
string QInt::toBinStr()
{
    stringstream out;

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
	while (str[i] == '0') { i++; }

	return str.substr(i);
}
string QInt::DectoBin(string s)
{
	int kt = 0;//kiem tra so am
	string res = "";
	if (s[0] == '-')
	{
		s.erase(0, 1);
		kt = 1;
	}
	int i = N_UINT * 32 - 1;
	while (s != "")
	{
		int bit = (s[s.length() - 1] - '0') % 2;
		setBit(i, bit);
		s = div2(s);
		res += bit + '0';
	}
	reverse(res.begin(),res.end());

	if (kt == 1)
	{
		//chuyen qua bu 2
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
	QInt p = *this;
	string s = p.toBinStr();
	int kt = 0;
	if (isNegative())
	{
		//chuyen qua bu 2 da
		kt = 1;
	}
	//la so duong
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

void QInt::SHL(int count)
{
    // debug
    //cout << "SHL CALLED - " << toString();

    for (int i = 0; i < count; ++i)
    {
        for (int j = 0; j < N_UINT; ++j)
        {
            data.int32[j] = data.int32[j] << 1;

            // set bit0 to content of bit31 on next int32 (if exist)
            if (j < N_UINT - 1)
            {
                unsigned int t = data.int32[j + 1];
                data.int32[j] = data.int32[j] | ((t >> 31) & 1);
            }
        }
    }
}

void QInt::clearBit()
{
    for (int j = 0; j < NUMBER_OF_BIT / 32; ++j)
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
	case DEC:
	{
		string s = DectoBin(text);
		*this = QInt(s, BIN);
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
		return *this;
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
	//bu 1
	res = ~(*this);
	cout << res.toBinStr();
	QInt temp("1", BIN);
	//cong them 1 de duoc so bu 2
	res = res + temp;
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
