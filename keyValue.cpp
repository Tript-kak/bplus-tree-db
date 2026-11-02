#include <bits/stdc++.h>
using namespace std;
#pragma once

template <typename K, typename V>

struct KeyValue{
    K key;
    V value;

    KeyValue(const K& key, const V& value) : key(key), value(value){}

    bool operator<(const KeyValue& other) const{
        return key < other.key;
    }
};