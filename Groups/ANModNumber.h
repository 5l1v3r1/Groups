//
//  ANModGroup.h
//  Groups
//
//  Created by Alex Nichol on 10/16/13.
//  Copyright (c) 2013 Alex Nichol. All rights reserved.
//

#ifndef __Groups__ANModGroup__
#define __Groups__ANModGroup__

#include <vector>
#include <exception>
#include <ostream>

using namespace std;

class ANModMismatchException : exception {
};

class ANModNumber {
protected:
    unsigned int number;
    unsigned int modulus;
public:
    ANModNumber(unsigned int number, unsigned int modulus);
    ANModNumber(const ANModNumber & number);
    
    virtual ANModNumber product(const ANModNumber & aNumber) const;
    ANModNumber sum(const ANModNumber & aNumber) const;
    
    virtual bool operator==(const ANModNumber & number) const;
    virtual bool operator!=(const ANModNumber & number) const;
    
    int getNumber() const;
    int getModulus() const;
};

ostream & operator<<(ostream & stream, const ANModNumber & number);

class ANModNumberPlus : public ANModNumber {
public:
    ANModNumberPlus(unsigned int number, unsigned int modulus) : ANModNumber(number, modulus) {}
    ANModNumberPlus(const ANModNumber & number) : ANModNumber(number) {}
    static vector<ANModNumberPlus> groupElements(unsigned int modulus);
};

ANModNumberPlus operator*(const ANModNumberPlus & num1, const ANModNumberPlus & num2);
ANModNumberPlus operator+(const ANModNumberPlus & num1, const ANModNumberPlus & num2);

class ANModNumberMult : public ANModNumber {
public:
    ANModNumberMult(unsigned int number, unsigned int modulus) : ANModNumber(number, modulus) {};
    ANModNumberMult(const ANModNumber & number) : ANModNumber(number) {};
    static vector<ANModNumberMult> groupElements(unsigned int modulus);
};

ANModNumberMult operator*(const ANModNumberMult & num1, const ANModNumberMult & num2);
ANModNumberMult operator+(const ANModNumberMult & num1, const ANModNumberMult & num2);

#endif /* defined(__Groups__ANModGroup__) */
