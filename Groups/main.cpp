//
//  main.cpp
//  Groups
//
//  Created by Alex Nichol on 10/16/13.
//  Copyright (c) 2013 Alex Nichol. All rights reserved.
//

#include <iostream>
#include "ANGroup.h"
#include "ANModGroup.h"
#include "ANPermGroup.h"

template <class T>
void analyzeGroup(ANGroup<T> group);

template <class T>
bool mapPreservesSquares(const ANGroupMap<T> & map);

template <class T>
bool mapPreservesPowers(const ANGroupMap<T> & map);

template <class T>
bool mapPreservesProduct(const ANGroupMap<T> & map);

int main(int argc, const char * argv[]) {
    cout << "Analyzing modular addition" << endl;
    for (unsigned modulus = 2; modulus <= 5; modulus++) {
        cout << "Modulus " << modulus << endl;
        vector<ANModNumberPlus> elements = ANModNumberPlus::groupElements(modulus);
        analyzeGroup(ANGroup<ANModNumberPlus>(elements));
    }
    cout << "Analyzing permutation application" << endl;
    for (unsigned permSize = 2; permSize < 8; permSize++) {
        cout << "S" << permSize << endl;
        vector<ANPermutation> elements = ANPermutation::symmetryGroup(permSize);
        analyzeGroup(ANGroup<ANPermutation>(elements));
    }
    cout << "Analyzing modular multiplication" << endl;
    for (unsigned modulus = 2; modulus <= 11; modulus++) {
        cout << "Modulus " << modulus << endl;
        vector<ANModNumberMult> elements = ANModNumberMult::groupElements(modulus);
        analyzeGroup(ANGroup<ANModNumberMult>(elements));
    }
    return 0;
}

template <class T>
void analyzeGroup(const ANGroup<T> group) {
    vector<ANGroupMap<T>> maps = ANGroupMap<T>::allMaps(group, mapPreservesPowers<T>);
    // for each one, check various properties
    for (unsigned int i = 0; i < maps.size(); i++) {
        ANGroupMap<T> aMap = maps[i];
        bool squares = mapPreservesPowers(aMap);
        if (squares) {
            cout << "Map preserves powers" << endl;
            if (mapPreservesProduct(aMap)) {
                cout << "Map preserves product!" << endl;
            } else {
                cout << "Map does not preserve product!" << endl;
                cout << aMap << endl;
                exit(0);
            }
        }
    }
}

template <class T>
bool mapPreservesSquares(const ANGroupMap<T> & map) {
    // for each element, make sure it's square is preserved
    for (unsigned int i = 0; i < map.getCount(); i++) {
        T source = map.getSource(i);
        T destination = map.getDestination(i);
        if (map.lookup(source * source) != destination * destination) {
            return false;
        }
    }
    return true;
}

template <class T>
bool mapPreservesPowers(const ANGroupMap<T> & map) {
    // for each element, make sure it's square is preserved
    for (unsigned int i = 0; i < map.getCount(); i++) {
        T original = map.getSource(i);
        T outer = map.lookup(map.getSource(i));
        T current = original;
        T currentOuter = outer;
        do {
            if (currentOuter != map.lookup(current)) return false;
            currentOuter = outer * currentOuter;
            current = original * current;
        } while (current != original);
    }
    return true;
}

template <class T>
bool mapPreservesProduct(const ANGroupMap<T> & map) {
    for (unsigned int i = 0; i < map.getCount(); i++) {
        for (unsigned int j = 0; j < map.getCount(); j++) {
            T innerProd = map.lookup(map.getSource(i) * map.getSource(j));
            T outerProd = map.lookup(map.getSource(i)) * map.lookup(map.getSource(j));
            if (innerProd != outerProd) {
                cout << "elements are " << map.getSource(i) << ", " << map.getSource(j) << endl;
                return false;
            }
        }
    }
    return true;
}
