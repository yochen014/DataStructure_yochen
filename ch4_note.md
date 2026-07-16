# Ch4 Linked List
## 4.1 
`DELETE()`:

```cpp
#include <iostream>
// Remove node x from the list headed by `head` (x must be in the list). O(n).
void deleteNode(Node*& head, Node* x) {
    if (x == head) {                         // x is the head
        head = x->link;
    } else {
        Node* y = head;
        while (y->link != x) y = y->link;    // predecessor scan
        y->link = x->link;
    }
    delete x;                                // return node to the pool (RET)
}
void demo41() {
    Node* head = nullptr;
    for (int v : {3, 2, 1}) head = new Node{v, head};   // 1 -> 2 -> 3
    deleteNode(head, head->link);                        // delete the 2
    for (Node* p = head; p; p = p->link) std::cout << p->data << ' ';
    std::cout << '\n';                                   // 1 3
}
demo41();
```