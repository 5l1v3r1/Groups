//
//  ANPermGroup.cpp
//  Groups
//
//  Created by Alex Nichol on 10/16/13.
//  Copyright (c) 2013 Alex Nichol. All rights reserved.
//

#include "ANPermGroup.h"

ANPermutation::ANPermutation(const vector<int> & desc) {
    perm = new int[desc.size()];
    for (int i = 0; i < (int)desc.size(); i++) {
        perm[i] = desc[i];
    }
    size = (int)desc.size();
}

ANPermutation::ANPermutation(const int * _perm, int _size) {
    size = _size;
    perm = new int[size];
    memcpy(perm, _perm, sizeof(int) * size);
}

ANPermutation::ANPermutation(const ANPermutation & permutation)
 : ANPermutation(permutation.perm, permutation.size) {
}

ANPermutation::~ANPermutation() {
    delete perm;
}

const int * ANPermutation::getPerm() const {
    return perm;
}

int ANPermutation::getSize() const {
    return size;
}

ANPermutation & ANPermutation::operator=(const ANPermutation & permutation) {
    size = permutation.size;
    delete perm;
    
    perm = new int[size];
    memcpy(perm, permutation.perm, sizeof(int) * size);
    return *this;
}

bool ANPermutation::operator==(const ANPermutation & permutation) const {
    if (permutation.size != size) return false;
    return (memcmp(perm, permutation.perm, sizeof(int) * size) == 0);
}

bool ANPermutation::operator!=(const ANPermutation & permutation) const {
    if (permutation.size != size) return true;
    return (memcmp(perm, permutation.perm, sizeof(int) * size) != 0);
}

ANPermutation operator*(const ANPermutation & p1, const ANPermutation & p2) {
    if (p1.size != p2.size) {
        throw ANPermutationDimensionsException();
    }
    
    int * buffer = new int[p1.size];
    for (int i = 0; i < p1.size; i++) {
        buffer[i] = p1.perm[p2.perm[i]];
    }
    
    // create permutation container
    ANPermutation perm(buffer, p1.size);
    delete buffer;
    return perm;
}

ostream & operator<<(ostream & stream, const ANPermutation & permutation) {
    stream << "<";
    const int * ptr = permutation.getPerm();
    for (int i = 0; i < permutation.getSize(); i++) {
        if (i > 0) stream << " ";
        stream << ptr[i];
    }
    return stream << ">";
}

// generation

vector<ANPermutation> ANPermutation::symmetryGroup(int letters) {
    vector<int> remaining;
    for (int i = 0; i < letters; i++) {
        remaining.push_back(i);
    }
    return generateSn(remaining, vector<int>());
}

vector<ANPermutation> ANPermutation::generateSn(vector<int> remaining, vector<int> map) {
    vector<ANPermutation> permutations;
    if (remaining.size() == 0) {
        permutations.push_back(ANPermutation(map));
        return permutations;
    }
    for (unsigned int i = 0; i < remaining.size(); i++) {
        vector<int> newRem = remaining;
        vector<int> newMap = map;
        newRem.erase(newRem.begin() + i);
        newMap.push_back(remaining[i]);
        vector<ANPermutation> subPerms = generateSn(newRem, newMap);
        permutations.insert(permutations.begin(), subPerms.begin(), subPerms.end());
    }
    return permutations;
}
