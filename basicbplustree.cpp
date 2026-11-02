#include <bits/stdc++.h>
using namespace std;


template <typename K, typename V>
class BplusTree {
  
    static constexpr size_t Order = 4;

    struct Node {
        bool isLeaf;
        vector<K> keys;
        vector<Node*> children;  
        vector<V> values;       
        Node* next;              
        explicit Node(bool leaf = false) : isLeaf(leaf), next(nullptr) {}
    };

    Node* root;

    static void destroy(Node* n) {
        if (!n) return;
        if (!n->isLeaf)
            for (Node* c : n->children) destroy(c);
        delete n;
    }


    Node* descend(const K& key, vector<Node*>* path) const {
        Node* cur = root;
        while (!cur->isLeaf) {
            if (path) path->push_back(cur);
            size_t i = upper_bound(cur->keys.begin(), cur->keys.end(), key) - cur->keys.begin();
            cur = cur->children[i];
        }
        return cur;
    }

 
    pair<K, Node*> splitLeaf(Node* leaf) {
        Node* right = new Node(true);
        size_t mid = leaf->keys.size() / 2;

        right->keys.assign(leaf->keys.begin() + mid, leaf->keys.end());
        right->values.assign(leaf->values.begin() + mid, leaf->values.end());
        leaf->keys.erase(leaf->keys.begin() + mid, leaf->keys.end());
        leaf->values.erase(leaf->values.begin() + mid, leaf->values.end());

        right->next = leaf->next;
        leaf->next = right;

        return {right->keys[0], right};  
    }

    pair<K, Node*> splitInternal(Node* node) {
        Node* right = new Node(false);
        size_t mid = node->keys.size() / 2;
        K up = node->keys[mid];

        right->keys.assign(node->keys.begin() + mid + 1, node->keys.end());
        right->children.assign(node->children.begin() + mid + 1, node->children.end());
        node->keys.erase(node->keys.begin() + mid, node->keys.end());   
        node->children.erase(node->children.begin() + mid + 1, node->children.end());

        return {up, right}; 
    }

public:
    BplusTree() : root(new Node(true)) {}
    ~BplusTree() { destroy(root); }
    BplusTree(const BplusTree&) = delete;             
    BplusTree& operator=(const BplusTree&) = delete;

   
    V* search(const K& key) {
        Node* leaf = descend(key, nullptr);
        auto it = lower_bound(leaf->keys.begin(), leaf->keys.end(), key);
        if (it != leaf->keys.end() && !(key < *it))
            return &leaf->values[it - leaf->keys.begin()];
        return nullptr;
    }

  
    bool get(const K& key, V& out) {
        V* p = search(key);
        if (!p) return false;
        out = *p;
        return true;
    }

    void insert(const K& key, const V& value) {
        vector<Node*> path;                       
        Node* leaf = descend(key, &path);

        size_t pos = lower_bound(leaf->keys.begin(), leaf->keys.end(), key) - leaf->keys.begin();
        if (pos < leaf->keys.size() && !(key < leaf->keys[pos])) {  
            leaf->values[pos] = value;
            return;
        }
        leaf->keys.insert(leaf->keys.begin() + pos, key);
        leaf->values.insert(leaf->values.begin() + pos, value);
        if (leaf->keys.size() < Order) return;

        
        Node* left = leaf;
        pair<K, Node*> sp = splitLeaf(leaf);

        while (true) {
            if (path.empty()) {                  
                Node* newRoot = new Node(false);
                newRoot->keys.push_back(sp.first);
                newRoot->children.push_back(left);
                newRoot->children.push_back(sp.second);
                root = newRoot;
                return;
            }
            Node* parent = path.back();           
            path.pop_back();

            size_t p = upper_bound(parent->keys.begin(), parent->keys.end(), sp.first) - parent->keys.begin();
            parent->keys.insert(parent->keys.begin() + p, sp.first);
            parent->children.insert(parent->children.begin() + p + 1, sp.second);

            if (parent->keys.size() < Order) return;  

            left = parent;
            sp = splitInternal(parent);                
        }
    }

    
    bool validate() const {
        int leafDepth = -1;
        if (!check(root, nullptr, nullptr, 0, leafDepth)) return false;
        Node* c = root;
        while (!c->isLeaf) c = c->children[0];
        const K* prev = nullptr;                  
        for (; c; c = c->next)
            for (const K& k : c->keys) {
                if (prev && !(*prev < k)) return false;
                prev = &k;
            }
        return true;
    }

    void printTree() const { printNode(root, 0); }
    void printLeaves() const {
        Node* c = root;
        while (!c->isLeaf) c = c->children[0];
        for (; c; c = c->next) {
            cout << "[";
            for (size_t i = 0; i < c->keys.size(); i++) cout << c->keys[i] << (i + 1 < c->keys.size() ? ", " : "");
            cout << "]" << (c->next ? "->" : "");
        }
        cout << endl;
    }

private:
    bool check(Node* n, const K* lo, const K* hi, int depth, int& leafDepth) const {
        for (size_t i = 0; i < n->keys.size(); i++) {
            if (i && !(n->keys[i - 1] < n->keys[i])) return false;  
            if (lo && n->keys[i] < *lo) return false;               
            if (hi && !(n->keys[i] < *hi)) return false;
        }
        if (n->isLeaf) {
            if (leafDepth == -1) leafDepth = depth;
            return leafDepth == depth && n->keys.size() == n->values.size();  
        }
        if (n->children.size() != n->keys.size() + 1) return false;
        for (size_t i = 0; i < n->children.size(); i++) {
            const K* l = i ? &n->keys[i - 1] : lo;
            const K* h = i < n->keys.size() ? &n->keys[i] : hi;
            if (!check(n->children[i], l, h, depth + 1, leafDepth)) return false;
        }
        return true;
    }

    void printNode(Node* n, int level) const {
        cout << "Level" << level << ": [";
        for (size_t i = 0; i < n->keys.size(); i++) cout << n->keys[i] << (i + 1 < n->keys.size() ? "| " : "");
        cout << "]" << endl;
        if (!n->isLeaf)
            for (Node* c : n->children) printNode(c, level + 1);
    }
};

int main() {
   
    BplusTree<int, string> tree;
   vector<pair<int, string>> data = {
    {10, "Alok"}, {20, "Bhannu"}, {5, "Dharmil"},
    {30, "Aditya"}, {15, "Ayush"}, {25, "Piyush"},
    {35, "Souviks"}, {40, "Raman"}
};

for (const auto& p : data) {
    tree.insert(p.first, p.second);
}
    tree.printTree();
    cout << "\nLeaves:\n";
    tree.printLeaves();
    string name;
    cout << "\nSearch 25: " << (tree.get(25, name) ? name : "Not found") << "\n";

   
    BplusTree<int, int> t;
    map<int, int> ref;
    mt19937 g(12345);
    bool ok = true;
    for (int i = 0; i < 50000 && ok; i++) {
        int k = g() % 8000, v = g();
        t.insert(k, v);
        ref[k] = v;
        if (i % 5000 == 0) ok = t.validate();
    }
    ok = ok && t.validate();
    for (const auto& p : ref) {
    int got;
    if (!t.get(p.first, got) || got != p.second) {
        ok = false;
    }
}
    int dummy;
    for (int k = 8000; k < 8100; k++)
        if (t.get(k, dummy)) ok = false;
    cout << "\nrandom test vs std::map: " << (ok ? "PASS" : "FAIL") << "\n";

 
    BplusTree<string, int> st;
    for (int i = 0; i < 1000; i++) st.insert("key" + to_string(i), i);
    int sv;
    cout << "string keys: " << (st.validate() && st.get("key777", sv) && sv == 777 ? "PASS" : "FAIL") << "\n";

  
    BplusTree<int, int> big;
    auto s = chrono::steady_clock::now();
    for (int i = 0; i < 100000; i++) big.insert(i, i);
    auto ms = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - s).count();
    cout << "100k sequential inserts: " << ms << " ms, valid=" << big.validate() << "\n";
}