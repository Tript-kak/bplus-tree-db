#pragma once 

#include "binaryObject.h"
#include "binaryPointer.h"

#include <bits/stdc++.h>

using namespace std;

class PointerBinaryObject : public BinaryObject<Pointer>{
   private:
    vector<uint8_t> bytes;
    public: 
        PointerBinaryObject() = default;

        explicit PointerBinaryObject(const vector<uint8_t>& bytes) : bytes(bytes) {}

        Pointer asObject() const override{
            return Pointer :: fromBytes(bytes);
        }

        size_t size() const override{
            return Pointer :: BYTES;
        }

        const vector<uint8_t> &getBytes() const override{
            return bytes;
        }
};

