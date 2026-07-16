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

// Stack實作
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

//Queue實作(用linked list)
class Queue{
public:
    Node* front = nullptr;
    Node* rear = nullptr;
};

//從前頭插入
void enqueue(Queue& q, int y){
    Node* x = new Node{y, nullptr};
    if(!q.front){ //若Queue為空
        q.front = x;
        q.rear = x;
    }
    else {
        q.front->next = x; //將queue的頭指向x node.
        q.front = x; //把queue的頭改成x node.
    }
}

//從前端拋出
int dequeue(Queue& q){
    if(!q.front)
        throw runtime_error("Queue is empty");
    
    Node* x = q.front;
    int y = x->data;
    q.front = x->next;

    if(!q.front) //做完這格才能刪光整個queue
        q.rear = nullptr;
    delete x;
    return y;
}

void demo42(){
    Node* s = nullptr;
    push(s, 1);
    push(s, 2);
    cout << "Stack pop: " << pop(s) << " " << pop(s) << endl; // 2 1

    Queue q;
    enqueue(q, 1);
    enqueue(q, 2);
    cout << "Queue dequeue: " << dequeue(q) << " " << dequeue(q) << endl; // 1 2
}


int main(){
    demo42();
    return 0;
}