#include "QInt.h"

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

string QInt::toString()
{
    stringstream out;
    
    out << "BIN: ";

    out << toBinStr() << endl;

    out << "HEX: ";
    out << toHexStr() << endl;

    return out.str();
}

string QInt::toBinStr()
{
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

string QInt::toDecStr()
{
    return string();
}

string QInt::toHexStr()
{
    stringstream temp;
    for (int j = 0; j < N_UINT; ++j)
    {
        if (data.int32[j] != 0)
        {
            temp << hex << data.int32[j];
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

QInt& QInt::operator=(QInt const& other)
{
    if (this != &other) {
        for (int i = 0; i < N_UINT; i++) {
            this->data.int32[i] = other.data.int32[i];
        }
    }

    return *this;
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

    default:
        break;
    }
}

QInt::QInt(QInt const& other)
{
    *this = other;
}
