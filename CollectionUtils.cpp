#pragma once 

#include <bits/stdc++.h>

using namespace std;

template <typename T>

int indexToInsert(const vector<T>& keys , const T& item){
    auto it = lower_bound(keys.begin(), keys.end(),item);

    if(it != keys.end() && *it == item){
        throw runtime_error("Item already exists");
    }

    return static_cast<int>(it-keys.size()); 
}

template <typename T>

bool contains(const vector<T>& keys, const T&item ){
    return find(keys.begin(),keys.end(),item) != keys.end(); 
}
template <typename T>
int indexOf(const vector<T>& keys, const T& item){
    auto it = find(keys.begin(),keys.end(),item);

    if(it == keys.end()) return -1;

    return static_cast<int>(it - keys.begin());
}