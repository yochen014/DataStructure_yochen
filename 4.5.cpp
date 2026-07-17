#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* link;
    Node(int data, Node* link){
        this->data = data;
        this->link = nullptr;
    }
};

Node* invert(Node*& x){
    Node* p = x; //指向當前正在處理的節點（初始為頭節點 x）
    Node* q = nullptr; //指向 p 的前一個節點，它將會成為反轉後串列的新頭部，初始為空指標
    while(p){
        Node* r = q;
        q = p; //將 q 指向當前節點 p
        p = p->link;
        q->link = r; //將當前節點的 link 指向前一個節點 r，完成反轉
        //r 作為暫存指標，用來記錄 q 的前一個狀態
    }
    return q; 
}

Node* concatenate(Node* x, Node* y){ //串接以x, y為開頭的兩串列，
    if(!x)
        return y;
    if(!y)
        return x;

    Node* p = x;
    while(p->link){
        p = p->link;
    }
    p->link = y; //將y連結x的尾巴
    return x; //回傳x作為頭

    // x1(頭) -> x2 -> ... -> xm -> y1 -> ... ->yn
}

//算環狀鏈結串列長度 O(n)
int length(const Node* a){
    if(!a)
        return 0;
    
    int i=0;
    const Node* p = a;
    do{ //do-while保證會做一次以上
        ++i;
        p = p->lnk;
    }while(p != a); //當p 回到 a 就會停止

    return i;
}

void demo45(){
    //invert
    Node* x = nullptr;
    for(int v : {3, 2, 1})
        x = new Node{v, x}; //建立 1 -> 2 -> 3
    x = invert(x); // x 現在在頭 1，反轉
    for(Node* p = x; p; p = p->link){
        cout << p->data << " ";
    }
    cout << "\n";

    //Concatenate
    Node* y = new Node{4, new Node{5, nullptr}};
    Node* z = concatenate(x, y);
    for(Node* p = z; p; p=p->link){
        cout << p->data << " ";
    }
    cout << "\n";

    //Circular List length
    Node* c = new Node{0};
    c->link = new Node{0};
    c->link->link = c; //只有兩個點的環狀串列
    cout << length(c) << "\n";
}

int main(){
    demo45();
    return 0;
}