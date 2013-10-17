//
//  ANModGroup.cpp
//  Groups
//
//  Created by Alex Nichol on 10/16/13.
//  Copyright (c) 2013 Alex Nichol. All rights reserved.
//

#include "ANModGroup.h"

static int getGCD(int a, int b);

ANModNumber::ANModNumber(unsigned int _number, unsigned int _modulus) {
    number = _number;
    modulus = _modulus;
}

ANModNumber::ANModNumber(const ANModNumber & val) {
    number = val.number;
    modulus = val.modulus;
}

ANModNumber ANModNumber::product(const ANModNumber & aNumber) const {
    if (aNumber.modulus != modulus) {
        throw ANModMismatchException();
    }
    return ANModNumber((number * aNumber.number) % modulus, modulus);
}

ANModNumber ANModNumber::sum(const ANModNumber & aNumber) const {
    if (aNumber.modulus != modulus) {
        throw ANModMismatchException();
    }
    return ANModNumber((number + aNumber.number) % modulus, modulus);
}

bool ANModNumber::operator==(const ANModNumber & num) const {
    return num.number == number && num.modulus == modulus;
}

bool ANModNumber::operator!=(const ANModNumber & num) const {
    return num.number != number || num.modulus != modulus;
}

int ANModNumber::getNumber() const {
    return number;
}

int ANModNumber::getModulus() const {
    return modulus;
}

ostream & operator<<(ostream & stream, const ANModNumber & number) {
    int aNum = number.getNumber();
    int aMod = number.getModulus();
    return stream << aNum << "%" << aMod;
}

// ANModNumberPlus

vector<ANModNumberPlus> ANModNumberPlus::groupElements(unsigned int modulus) {
    vector<ANModNumberPlus> numbers;
    for (unsigned int i = 0; i < modulus; i++) {
        ANModNumberPlus number = ANModNumberPlus(i, modulus);
        numbers.push_back(number);
    }
    return numbers;
}

ANModNumberPlus operator*(const ANModNumberPlus & num1, const ANModNumberPlus & num2) {
    return num1 + num2;
}

ANModNumberPlus operator+(const ANModNumberPlus & num1, const ANModNumberPlus & num2) {
    return (ANModNumberPlus)num1.sum(num2);
}

// ANModNumberMult

vector<ANModNumberMult> ANModNumberMult::groupElements(unsigned int modulus) {
    vector<ANModNumberMult> numbers;
    for (unsigned int i = 1; i < modulus; i++) {
        if (getGCD(modulus, i) == 1) {
            ANModNumberMult number = ANModNumberMult(i, modulus);
            numbers.push_back(number);
        }
    }
    return numbers;
}

ANModNumberMult operator*(const ANModNumberMult & num1, const ANModNumberMult & num2) {
    return (ANModNumberMult)num1.product(num2);
}

ANModNumberMult operator+(const ANModNumberMult & num1, const ANModNumberMult & num2) {
    return (ANModNumberMult)num1.sum(num2);
}

static int getGCD(int a, int b){
    if (a > b){
        if (a % b == 0){
            return b;
        } else{
            a = a % b;
            return getGCD(a, b);
        }
    } else {
        if (b % a == 0){
            return a;
        } else{
            b = b % a;
            return getGCD(a, b);
        }
    }
}
