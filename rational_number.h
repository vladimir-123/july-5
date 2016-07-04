#pragma once
#include <iostream>

class TRationalNum {
private:
    int Numerator;
    unsigned int Denominator;
public:
    TRationalNum();
    TRationalNum(int num, unsigned int denum = 1);
    TRationalNum(const TRationalNum& otherRational);
    int GetNumerator() const;
    int GetDenominator() const;
    TRationalNum Reduce() const;
    int GetReducedNumerator() const;
    int GetWholePart() const;
    TRationalNum operator=(const TRationalNum& otherRational);
    TRationalNum operator+(const TRationalNum& otherRational) const;
    TRationalNum operator-() const;
    TRationalNum operator+() const; // унарный оператор +
    TRationalNum& operator*=(const TRationalNum& RMultiplicand);
    TRationalNum operator*(const TRationalNum& mult) const;
    TRationalNum Reciprocal() const;
    TRationalNum& operator/=(const TRationalNum& divisor);
    TRationalNum operator/(const TRationalNum& divisor) const;
    TRationalNum& operator+=(const TRationalNum& otherRational);
    TRationalNum& operator++();
    TRationalNum operator++(int);
    TRationalNum& operator--();
    TRationalNum operator--(int);
    operator double() const;
};

int CommonDiv(int a, int b);
TRationalNum operator+(const int a, const TRationalNum& summand);
TRationalNum operator*(const int a, const TRationalNum& mult);
TRationalNum operator/(const int a, const TRationalNum& divisor);
TRationalNum operator-(const TRationalNum& FirstValue, const TRationalNum& SecondValue);
bool operator==(const TRationalNum& FirstValue, const TRationalNum& SecondValue);
std::ostream& operator<<(std::ostream& os, const TRationalNum& RationalValue);
void operator-=(TRationalNum& RAugend, const TRationalNum& RAddend);
bool operator!=(const TRationalNum& FirstValue, const TRationalNum& SecondValue);
bool operator<(const TRationalNum& FirstValue, const TRationalNum& SecondValue);
bool operator>(const TRationalNum& FirstValue, const TRationalNum& SecondValue);
bool operator<=(const TRationalNum& FirstValue, const TRationalNum& SecondValue);
bool operator>=(const TRationalNum& FirstValue, const TRationalNum& SecondValue);
TRationalNum operator--(const TRationalNum& RValue);
