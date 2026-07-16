#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* link;
    Node(int data){
        this->data = data;
        this->link = nullptr;
    }
};

void invert(Node*& x){
    Node* p = x; //指向當前正在處理的節點（初始為頭節點 x）
    Node* q = nullptr; //指向 p 的前一個節點，它將會成為反轉後串列的新頭部，初始為空指標
    while(p){
        Node* r = q;
        q = p; //將 q 指向當前節點 p
        p = p->link;
        q->link = r; //將當前節點的 link 指向前一個節點 r，完成反轉
        //r 作為暫存指標，用來記錄 q 的前一個狀態

    }
}