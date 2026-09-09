#pragma once

#include <bits/stdc++.h>
#include <binaryObject.h>
using namespace std;

template<typename E>

class BinaryObjectFactory{
    public: 

    virtual unique_ptr<BinaryObject<E>>
    create(const E& value) const = 0;

    virtual unique_ptr<BinaryObject<E>>
    create(const vector<uint8_t>&bytes, size_t beginning) = 0;

    virtual unique_ptr<BinaryObject<E>>
    create(const vector<uint8_t>& bytes){
        return create(bytes,0);
    }

    virtual size_t size() const = 0;

    virtual unique_ptr<BinaryObject<E>>
    createEmpty() const = 0;

    virtual ~BinaryObjectFactory() = default;
};