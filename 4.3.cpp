#include <iostream>
#include <stdexcept>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int data){
        this->data = data;
        this->next = nullptr;
    }
};

class Pool{ //儲存池
public:
    Node* av = nullptr;
};

Node* getnode(Pool& p){ //像是pop
    if(!p.av)
        throw runtime_error("No available nodes in the pool.");
    Node* x = p.av;
    p.av = x->next;
    x->next = nullptr;
    return x;
}

void ret(Pool& p, Node* x){ //像是push
    x->next = p.av;
    p.av = x;
}
