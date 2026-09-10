#pragma once 

#include <bits/stdc++.h>
using namespace std;

class AbstractTreeNodeBase{
    protected:
        vector<uint8_t> data;
        bool leaf;

    public:
        AbstractTreeNodeBase(
            const vector<uint8_t>& data, bool leaf
        ): data(data) , leaf(leaf) {}

        virtual ~AbstractTreeNodeBase() = default;

        vector<uint8_t>& getData(){
            return data;
        }

        const vector<uint8_t> &getData() const{
            return data;
        }

        bool isLeaf(){
            return leaf;
        }
};