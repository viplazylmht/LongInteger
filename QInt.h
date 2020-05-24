#pragma once
#include <stdio.h>
#include <iostream>
#include <sstream>
#include<string>
using namespace std;

// KEEP IN MIND: NUMBER_OF_BIT luon la boi so cua 32, nhung bao nhiu cung duoc (64, 96, 128, ...)
#define NUMBER_OF_BIT 96

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
	QInt();
    QInt(string text, int op);
    QInt(QInt const&);


	// set pit at pos to content of val (1 by default)
	void setBit(int const& pos, bool const& val = 1);

	//get bit at pos
	bool getBit(int pos);

	// make printable object (not dump)
	string toString();

	string toBinStr();
	string toDecStr();
	//string toHexStr();

	string DectoBin(string);
    // Shift Left Logical
    void SHL(int count);
    
    void clearBit();

    // operator
    QInt& operator=(QInt const&);
	QInt operator+ (QInt&);
	QInt operator- (QInt&);
	QInt operator^ (const QInt&) const;
	QInt operator~ () const;


	// kiem tra so am
	bool isNegative();

	//kiem tra bang 0
	bool isZero() const;

	//chuyen doi so qua bu 2
	QInt convert();

	//Ham chia 2
	string div2(string);

	//Ham nhan 2
	string mul2(string s, int pos);

};