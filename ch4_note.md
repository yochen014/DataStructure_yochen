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

## 4.4
係數加法 (Coefficient additions)： 介於 $0$ 到 $\min(m, n)$ 次。
只有當兩個指標指到的指數完全相同時（ $ EXP(p) = EXP(q) $ ），才會觸發係數加法。

我們會用 Linked list 實作多項式，因為：
* **處理稀疏性 (Sparsity) 的絕對優勢**(鏈結表示法只在乎「非零項」)
* **動態回收機制 (Dynamic Reclamation)**：得益於我們之前實作的儲存池（Storage Pool）或動態記憶體配置機制，我們可以立刻精準地釋放 $T$ 的所有節點，避免記憶體溢出（Memory Leak），這在進行大型數值計算時是確保系統穩定性的關鍵。

假設兩多項式分別有 $m$ , $n$ 項。
時間複雜度： $O(m+n)$ ，為理論上最佳。

### 4.4.3 Head Nodes & Sentinels(哨兵節點)
在處理多項式加法時，如果遇到「空多項式（Empty Polynomial）」，往往需要寫許多特別的 `if-else` 防呆機制來處理邊界情況。引入 Head Node：
我們**規定每一個多項式（無論是否為空）都必須帶有一個「頭部節點（Head Node）」**。
空集定義：一個空多項式在幾何上被定義為「頭部節點的指標指向自己」。
**哨兵設計 (Sentinel)：** 我們將這個頭部節點的指數（EXP）設定為 $-1$。
因為在我們的系統中，指數是嚴格遞減的且為非負整數，$-1$ 在數學上代表著絕對的下界。
消滅殘留迴圈：在實作環狀多項式加法（CPADD）時，這個 EXP = -1 的哨兵可以讓演算法在單一個 switch-case 狀態機中自然終止，我們再也不需要像線性串列那樣，在主迴圈結束後還要寫兩個額外的 for 迴圈去收拾 $A$ 或 $B$ 剩下的殘局。