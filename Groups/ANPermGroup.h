//
//  ANPermGroup.h
//  Groups
//
//  Created by Alex Nichol on 10/16/13.
//  Copyright (c) 2013 Alex Nichol. All rights reserved.
//

#ifndef __Groups__ANPermGroup__
#define __Groups__ANPermGroup__

#include <exception>
#include <vector>
#include <ostream>

using namespace std;

class ANPermutationDimensionsException : exception {
};

class ANPermutation {
private:
    int * perm;
    int size;
    static vector<ANPermutation> generateSn(vector<int> remaining, vector<int> map);
    
public:
    ANPermutation(const vector<int> & desc);
    ANPermutation(const int * perm, int size);
    ANPermutation(const ANPermutation & permutation);
    ~ANPermutation();
    
    const int * getPerm() const;
    int getSize() const;
    
    virtual ANPermutation & operator=(const ANPermutation & permutation);
    virtual bool operator==(const ANPermutation & permutation) const;
    virtual bool operator!=(const ANPermutation & permutation) const;
    
    friend ANPermutation operator*(const ANPermutation & p1, const ANPermutation & p2);
    
    static vector<ANPermutation> symmetryGroup(int letters);
};

ANPermutation operator*(const ANPermutation & p1, const ANPermutation & p2);
ostream & operator<<(ostream & stream, const ANPermutation & permutation);

#endif /* defined(__Groups__ANPermGroup__) */
