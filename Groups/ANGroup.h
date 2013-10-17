//
//  ANGroup.h
//  Groups
//
//  Created by Alex Nichol on 10/16/13.
//  Copyright (c) 2013 Alex Nichol. All rights reserved.
//

#ifndef __Groups__ANGroup__
#define __Groups__ANGroup__

#include <vector>
#include <exception>
#include <ostream>

using namespace std;

class ANGroupNoElementException : exception {
};

template <class T>
class ANGroup {
private:
    vector<T> elements;
public:
    ANGroup(const vector<T>);
    ANGroup(const ANGroup &);
    
    virtual ANGroup & operator=(const ANGroup & group);
    virtual const vector<T> & getElements() const;
};

template <class T>
class ANGroupMap {
private:
    vector<T> sources;
    vector<T> destinations;
    static vector<ANGroupMap<T>> allMapsLoop(const ANGroup<T> & group, vector<T> map, bool (*fn)(const ANGroupMap<T> &));
public:
    static vector<ANGroupMap<T>> allMaps(const ANGroup<T> &, bool (*fn)(const ANGroupMap<T> &) = 0);
    
    ANGroupMap(const vector<T> &, const vector<T> &);
    ANGroupMap(const ANGroupMap &);
    
    virtual T lookup(const T &) const;
    virtual unsigned int getCount() const;
    virtual T getSource(unsigned int index) const;
    virtual T getDestination(unsigned int index) const;
    
    virtual ANGroupMap & operator=(const ANGroupMap & map);
};

template <class T>
ostream & operator<<(ostream & stream, ANGroupMap<T> map);

/** ACTUAL IMPLEMENTATION HERE **/

// ANGroup

template <class T>
ANGroup<T>::ANGroup(const vector<T> theEls) {
    elements = theEls;
}

template <class T>
ANGroup<T>::ANGroup(const ANGroup & group) {
    elements = group.elements;
}

template <class T>
const vector<T> & ANGroup<T>::getElements() const {
    return elements;
}

template <class T>
ANGroup<T> & ANGroup<T>::operator=(const ANGroup & group) {
    elements = group.elements;
    return *this;
}

// ANGroupMap

template <class T>
ostream & operator<<(ostream & stream, ANGroupMap<T> map) {
    stream << "(" << endl;
    for (unsigned int i = 0; i < map.getCount(); i++) {
        stream << "  " << map.getSource(i) << " -> " << map.getDestination(i) << endl;
    }
    stream << ")";
    
    return stream;
}

template <class T>
ANGroupMap<T>::ANGroupMap(const vector<T> & source, const vector<T> & dest) {
    sources = source;
    destinations = dest;
}

template <class T>
ANGroupMap<T>::ANGroupMap(const ANGroupMap & automorphism) {
    sources = automorphism.sources;
    destinations = automorphism.destinations;
}

template <class T>
T ANGroupMap<T>::lookup(const T & obj) const {
    // look it up in the source vector
    for (unsigned int i = 0; i < sources.size(); i++) {
        if (sources[i] == obj) {
            return destinations[i];
        }
    }
    throw ANGroupNoElementException();
}

template <class T>
unsigned int ANGroupMap<T>::getCount() const {
    return (unsigned int)sources.size();
}

template <class T>
T ANGroupMap<T>::getSource(unsigned int index) const {
    return sources[index];
}

template <class T>
T ANGroupMap<T>::getDestination(unsigned int index) const {
    return destinations[index];
}

template <class T>
ANGroupMap<T> & ANGroupMap<T>::operator=(const ANGroupMap<T> & map) {
    sources = map.sources;
    destinations = map.destinations;
    return *this;
}

template <class T>
vector<ANGroupMap<T>> ANGroupMap<T>::allMaps(const ANGroup<T> & group, bool (*fn)(const ANGroupMap<T> &)) {
    // essentially use factorial here
    return ANGroupMap<T>::allMapsLoop(group, vector<T>(), fn);
}

// private

template <class T>
vector<ANGroupMap<T>> ANGroupMap<T>::allMapsLoop(const ANGroup<T> & group, vector<T> map, bool (*fn)(const ANGroupMap<T> &)) {
    vector<ANGroupMap<T>> auts;
    vector<T> elements = group.getElements();
    if (map.size() == elements.size()) {
        ANGroupMap theMap(elements, map);
        if (fn) {
            if (!fn(theMap)) return auts;
        }
        auts.push_back(theMap);
        return auts;
    }
    
    for (unsigned int i = 0; i < elements.size(); i++) {
        vector<T> newMap = map;
        newMap.push_back(elements[i]);
        
        vector<ANGroupMap<T>> gathered = allMapsLoop(group, newMap, fn);
        auts.insert(auts.end(), gathered.begin(), gathered.end());
    }
    return auts;
}

#endif /* defined(__Groups__ANGroup__) */
