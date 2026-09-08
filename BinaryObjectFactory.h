#pragma once

#include <bits/stdc++.h>
#include <binaryObject.h>
using namespace std;

template<typename E>

class BinaryObjectFactory{
    public: 

    virtual shared_ptr<BinaryObject<E>>
    create(const E& value) = 0;

    virtual shared_ptr<BinaryObject<E>>
    create(const vector<uint8_t>&bytes, size_t beginning) = 0;

    virtual shared_ptr<BinaryObject<E>>
    create(const vector<uint8_t>& bytes){
        return create(bytes,0);
    }

    virtual int size() const = 0;

    virtual shared_ptr<BinaryObject<E>>
    createEmpty() = 0;

    virtual ~BinaryObjectFactory() = default;
};