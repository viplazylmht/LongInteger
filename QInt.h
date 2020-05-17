#pragma once
#include <stdio.h>
#include <iostream>
#include <sstream>
using namespace std;

// KEEP IN MIND: NUMBER_OF_BIT luon la boi so cua 32, nhung bao nhiu cung duoc (64, 96, 128, ...)
#define NUMBER_OF_BIT 64

#define N_BYTE NUMBER_OF_BIT / 8
#define N_UINT NUMBER_OF_BIT / 32

#define HEX 16
#define DEC 10
#define BIN 2

class QInt
{

public:
    // dung union de int8 va int32 tro cung 1 vung nho
    union {

        // bug cuc manh o int8, vui long khong xai truc tiep, hay xem ham byteAt giai thich (doi voi trinh bien dich cua windows, g++)
        unsigned char int8[N_BYTE];
        unsigned int int32[N_UINT];

        unsigned char& byteAt(int pos) {
            // use this funtion only when machine use Big Endian by default
            // for more infomation, see this answer: https://stackoverflow.com/a/47335692
             
            int mod = pos % 4;
            return int8[pos - mod + (3 - mod)];
        }
    } data;

public:
    //decode text to object
    QInt(string text, int op);
    QInt(QInt const&);

    //------ utils ------//

    // Shift Left Logical
    void SHL(int count);

    // Shift Right Logical
    void SHR(int count);

    // Shift Arithmetic Right
    void SAR(int count);

    // Shift Arithmetic Right
    void SAL(int count);
    
    // Rotation Left
    void ROL(int count = 1);

    // Rotation Right
    void ROR(int count = 1);
    
    // set pit at pos to content of val (1 by default)
    void setBit(int const& pos, bool const& val = 1);

    // set all bit to 0
    void clearBit();

    // make printable object (not dump)
    string toString();
    
    string toBinStr();
    string toDecStr();
    string toHexStr();

    // operator
    QInt& operator=(QInt const&);
    QInt const operator<<(int);
    QInt const operator>>(int);
    QInt const operator|(QInt const&);
    QInt const operator&(QInt const&);

private:
    // convert a character from hex to bin
    // input is a char, return a byte (but take only 4 bit aka from 0b00000000 -> 0b00001111)
    // ex: 'a' -> 0b00001010
    char hex2bin(char);
};