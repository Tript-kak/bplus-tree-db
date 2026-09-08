#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "binaryObject.h"
template <typename E>

class IndexBinaryObject : public BinaryObject<E>{
    protected:
        vector<uint8_t> bytes;

    public:
        IndexBinaryObject() = default;

        explicit IndexBinaryObject(
            const vector<uint8_t>& bytes
        ) : bytes(bytes) {}

        const vector<uint8_t> &getBytes() const override{
            return bytes;
        }
};