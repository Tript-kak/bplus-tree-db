#include <bits/stdc++.h>
using namespace std;

template <typename K, typename V>
class BplusTree {
    private: 
        static const int Order = 4;
         struct Node{
            bool isLeaf;

            vector<K> keys;

            vector<Node*> children;
            vector<V> values;

            Node* next;

            Node(bool leaf = false){
                isLeaf = leaf;
                next = nullptr;
            }
         };

         Node* root;

         public:
            BplusTree(){
                root = new Node(true);
            }

            V* search(const K& key){
                Node* current = root;

                while(!current->isLeaf){
                    int i = 0;

                    while(i < current->keys.size() && key >= current->keys[i]){
                        i++;
                    }

                    current = current-> children[i];
                }

                for(int i=0; i < current->keys.size(); i++){
                    if(current->keys[i] == key){
                        return &current->values[i];
                    }
                }

                return nullptr;
            }

            void insert(const K& key, const V& value){
                Node* leaf = findLeaf(key);

                int pos = lower_bound(leaf->keys.begin(),leaf->keys.end(),key) - leaf->keys.begin();

                if(pos < leaf->keys.size() && leaf->keys[pos] == key){
                    leaf->values[pos] = value;
                    return;
                }

                leaf->keys.insert(leaf->keys.begin()+pos,key);

                leaf->values.insert(leaf->values.begin()+pos,value);

                if(leaf->keys.size() < Order){
                    return ;
                }

                splitLeaf(leaf);
            }

            private:
                Node* findLeaf(const K& key){
                    Node* current = root;
                    while(!current->isLeaf){
                    int i = 0;

                    while(i < current->keys.size() && key >= current->keys[i]){
                        i++;
                    }
                    current = current->children[i];
                }
                return current;
            }

            void splitLeaf(Node* leaf){
                Node* newLeaf = new Node(true);

                int mid = leaf->keys.size()/2;

                newLeaf->keys.assign(leaf->keys.begin()+mid,leaf->keys.end());

                newLeaf->values.assign(leaf->values.begin()+mid,leaf->values.end()); 

                leaf->keys.erase(leaf->keys.begin()+mid , leaf->keys.end());

                leaf->values.erase(leaf->values.begin()+mid, leaf->values.end());
            
                newLeaf->next = leaf->next;
                leaf->next = newLeaf;

                K promotedKey = newLeaf -> keys[0];

                if(leaf == root){
                    Node* newRoot = new Node(false);

                    newRoot->keys.push_back(promotedKey);

                    newRoot->children.push_back(leaf);
                    newRoot->children.push_back(newLeaf);

                    root = newRoot;

                    return;
                }

                Node* parent = findParent(root,leaf);

                insertIntoInterval(parent,promotedKey,newLeaf);
            }

            void insertIntoInterval(Node* parent, const K& key, Node* rightChild){
                int pos = lower_bound(parent->keys.begin(), parent->keys.end(),key) - parent->keys.begin();

                parent->keys.insert(parent->keys.begin()+pos,key);

                parent->children.insert(parent->children.begin()+pos+1,rightChild);

                if(parent->keys.size() < Order){
                    return;
                }

                splitInternal(parent);
            }

            void splitInternal(Node* node){
                Node* newInternal = new Node(false);

                int mid = node->keys.size()/2;

                K promotedKey = node->keys[mid];

                newInternal->keys.assign(node->keys.begin() + mid + 1, node->keys.end());

                newInternal->children.assign(node->children.begin() + mid + 1, node->children.end());

                node->keys.erase(node->keys.begin() + mid, node->keys.end());

                node->children.erase(node->children.begin()+mid+1,node->children.end());

                if(node == root){
                    Node* newRoot = new Node(false);

                    newRoot->keys.push_back(promotedKey);
                    newRoot->children.push_back(node);
                    newRoot->children.push_back(newInternal);

                    root = newRoot;
                    return;
                }

                Node* parent = findParent(root,node);

                insertIntoInterval(parent,promotedKey,newInternal);
            }

            Node* findParent(Node* current, Node* child){
                if(current->isLeaf){
                    return nullptr;
                }

                for(Node* c : current->children){
                    if(c == child) return current;

                    Node* result = findParent(c,child);

                    if(result != nullptr){
                        return result;                  
                      }
                }
                return nullptr;
            }

            public:
                void printTree(){
                    printNode(root,0);
                }

            private: 
                void printNode(Node* node, int level){
                    cout << "Level" << level << ": ";
                    cout << "[";

                    for(int i=0; i < node->keys.size(); i++){
                        cout << node->keys[i];

                        if(i+1 < node->keys.size()){
                            cout << "| ";
                        }
                    }

                    cout << "]" << endl;

                    if(!node->isLeaf){
                        for(Node* child : node->children){
                            printNode(child,level+1);
                        }
                    }
                }

                public:
                    void printLeaves(){
                        Node* current = root;

                        while(!current->isLeaf){
                            current = current->children[0];
                        }

                        while(current != nullptr){
                            cout << "[";

                            for(int i=0; i < current->keys.size(); i++){
                                cout << current->keys[i];
                            

                            if(i+1 < current->keys.size()){
                                cout << ", ";
                            }
                        }
                        cout << "]";

                        if(current->next != nullptr){
                            cout << "->";
                        }

                        current = current->next;
                    }
                    cout << endl;
                }
            };

int main(){
     BplusTree<int, string> tree;

    tree.insert(10, "Alok");
    tree.insert(20, "Bhannu");
    tree.insert(5, "Dharmil");
    tree.insert(30, "Aditya");
    tree.insert(15, "Ayush");
    tree.insert(25, "Piyush");
    tree.insert(35, "Souviks");
    tree.insert(40, "Raman");

    tree.printTree();

    cout << "\nLeaves:\n";
    tree.printLeaves();

    cout << "\nSearch:\n";

    string* result = tree.search(25);

    if (result != nullptr) {
        cout << "Found: " << *result << endl;
    }
    else {
        cout << "Not found\n";
    }

    return 0;
}