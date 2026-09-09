#pragma once 
#include <bits/stdc++.h>

using namespace std;

template <typename E>

class BinaryObject{
    public:
        virtual ~BinaryObject() = default;

        virtual E asObject() const = 0;

        virtual size_t size() const = 0;

        const virtual vector<uint8_t> getBytes() const = 0;

        virtual E getFirst() const{
            throw runtime_error("Operation not supported");
        }

        virtual E getNext() const{
            throw runtime_error("Operation not supported");
        }

        virtual bool supportIncrements() const{
            return false;
        }
        
};