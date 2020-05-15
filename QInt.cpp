#include "QInt.h"

string QInt::toString()
{
    stringstream out;
    out << "BIN: ";

    for (int j = 0; j < N_UINT; ++j)
    {
        for (int i = 31; i >= 0; --i)
        {
            out << ((data.int32[j] << (31 - i)) >> 31);
        }
    }
    out << endl;

    return out.str();
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
    cout << "SHL CALLED - " << toString();

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

    default:
        break;
    }
}

QInt::QInt(QInt const& other)
{
    *this = other;
}
