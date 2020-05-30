#pragma once
#include <stdio.h>
#include <iostream>
#include <sstream>
#include<string>
using namespace std;

// KEEP IN MIND: NUMBER_OF_BIT luon la boi so cua 32, nhung bao nhiu cung duoc (64, 96, 128, ...)
#define NUMBER_OF_BIT 128

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
    QInt(string text, int base);
    QInt(QInt const&);
    QInt(long long const& n);

    // Shift Left Logical
    void SHL(int count);

    // Shift Right Logical
    void SHR(int count);

    // Shift Arithmetic Right
    void SAR(int count);
    
    // Rotation Left
    void ROL(int count = 1);

    // Rotation Right
    void ROR(int count = 1);
    
    // make printable object (not dump)
    string toString();
    
	//Chuyen doi cac he co so
    string toBinStr();
    string toDecStr();
    string toHexStr();

    string exportData(int base);

    // operator
    QInt& operator=(QInt const&);

	QInt operator+ (const QInt&) const;
	QInt operator- (const QInt&) const;
	QInt operator* ( const QInt&) const;
	QInt operator/ (const QInt&) const;

	bool operator==(QInt const&) const;
	bool operator==(long long const&) const;
	bool operator!= (QInt const& B) const;
	bool operator> (QInt const& B) const;
	bool operator< (QInt const& B) const;

	QInt const operator<<(int);
	QInt const operator>>(int);
	QInt const operator|(QInt const&);
	QInt const operator&(QInt const&);
	QInt operator^ (const QInt&) const;
	QInt operator~ () const;

    static QInt MIN_VALUE();
    static QInt MAX_VALUE();

private:
    //------ utils ------//

    // convert a character from hex to bin
    // input is a char, return a byte (but take only 4 bit aka from 0b00000000 -> 0b00001111)
    // ex: 'a' -> 0b00001010
    char hex2bin(char);
    string bin2hex(unsigned char const&);

    // kiem tra so am
    bool isNegative() const;

    //kiem tra bang 0
    bool isZero() const;

    //chuyen doi so qua bu 2
    QInt toConvertBu2() const;

    //Ham chia 2 ho tro cho chuyen doi tu str10 ve str2
    string div2(string);

    //cong 2 chuoi so nguyen duong
    string add2Str(string, string);

    //Ham nhan 2 chuoi so duong tra ve ket qua la chuoi
    string mul2Str(string, string);

    //Ham mu voi cac so truyen vao nguyen duong tra ve ket qua la chuoi
    string Power(unsigned int, unsigned int);

    // set all bit to 0
    void clearBit();

    // set pit at pos to content of val (1 by default)
    void setBit(int const& pos, bool const& val = 1);

    //get bit at pos
    bool getBit(int pos)const;

    //str10 qua str2
    QInt DectoBin(string);


public:
    // add, sub, mul, div QInt without overflow check
    QInt add(QInt const&);
    QInt sub(QInt const&);

};