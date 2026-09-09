#pragma once

#include <bits/stdc++.h>
using namespace std;

#include "binaryObject.h"
#include "binaryPointer.h"
#include "IndexBinaryObject.h"
#include "BinaryObjectFactory.h"

class PointerIndexBinaryObject : public IndexBinaryObject<Pointer>{
    public:
        static constexpr size_t BYTES = Pointer :: BYTES;

        PointerIndexBinaryObject() = default;

        PointerIndexBinaryObject(
            const vector<uint8_t>& bytes
        ): IndexBinaryObject<Pointer>(bytes){}

        Pointer asObject() const override{
            return Pointer :: fromBytes(bytes);
        }

        size_t size() const override{
            return BYTES;
        }



        class Factory: public BinaryObjectFactory<Pointer>{
            public:
                unique_ptr<BinaryObject<Pointer>>
                create(const Pointer& pointer) const override{
                    return make_unique<PointerIndexBinaryObject>(pointer.toBytes());
                }

                unique_ptr<BinaryObject<Pointer>>
                create(
                    const vector<uint8_t>& bytes,
                    size_t beginning
                )  override{
                    vector<uint8_t> value(
                        bytes.begin() + beginning, 
                        bytes.begin() + beginning + BYTES
                    );

                    return make_unique<PointerIndexBinaryObject>(value);
                }

                
                
        };
};

int main() {

    Pointer p = Pointer::empty();

    PointerIndexBinaryObject::Factory factory;

    auto obj = factory.create(p);

    cout << "Size: " << obj->size() << endl;

    return 0;
}