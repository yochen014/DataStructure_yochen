#include <iostream>
#include <stdexcept>
using namespace std;

class Node{
public:
    int data;
    Node* next;
    Node(int data, Node* next = nullptr) {
        this->data = data;
        this->next = next;
    }
};


void push(Node*& head, int y){
    head->next = new Node(y, head);
    // 1 <- 2 <- 3 <- y (head從左邊開始)
}

// 1 <- 2 <- 3(head) ...
// 1 <- 2(3.next) <- 3 ...
int pop(Node*& head){
    if(!head)
        throw runtime_error("Stack is empty");
    
    Node* x = head;
    int y = x->data;
    head = x->next;
    delete x;
    return y;
}
// 1 <- 2 <- 3(head) ...
// 1 <- 2(3.next) <- 3 ...

int main(){
    demo42();
    return 0;
}