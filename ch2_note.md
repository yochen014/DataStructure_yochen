# Ch2 Arrays(陣列)
# 2.1 Introduction(介紹)
一個常見的誤解是將陣列直接定義為「一連串連續的記憶體位置」。但這種說法其實是混淆了「資料結構的本質」與它的「底層實作方式」。
## Definition of Arrays
陣列實際上是一個 (索引, 數值) 配對的集合。在數學上，這是一個對應或映射（mapping）關係，對於每一個定義好的索引，都有一個關聯的數值。

## Axioms of Arrays(公理)
有三個函數：
* `CREATE()` 負責建立新的、空array。
* `RETRIEVE(A, i)` 回傳在index `i`時的value，或是回傳error
* `STORE(A, i, x)` 存入一組新的index-value 配對，並回傳array。

**核心第二公理（J. McCarthy 提出）：**
\[RETRIEVE(STORE(A, i, x), j)\]
如果在陣列 $A$ 的位置 $i$ 存入數值 $x$ 後，我們去讀取位置 $j$ 的值。這在邏輯上完全等價於以下判斷：  檢查 $i$ 與 $j$ 是否相等：若相等則回傳 $x$。  
否則，在剩餘的陣列 $A$ 中搜尋第 $j$ 個值（即等同於執行 $RETRIEVE(A, j)$）。

---

# 2.2 Ordered List(有序串列)
一個有序串列可表為
\[(a_1, a_2, \cdots , a_n)\]

**優點**：利用可隨機存取記憶體的特性，可在 $O(1)$ 的常數時間內讀取或修改任意元素。
**缺點**：執行插入（Insert）與刪除（Delete）操作時，需要大規模向右或向左移動剩餘元素，計算成本極高。

## Polynomial的例子
為了解決實際運算（如多項式加法、乘法等）的需求，我們必須為多項式設計合適的資料結構

### Dense Representation(稠密表示法)
將每個係數和最高n次都保存成
\[A=(n, a_n, a_{n-1}, \cdots, a_1, a_0)\]
指數隱含在陣列位置中，這使得處理稀疏多項式時會**浪費極大的空間**。例如 $x^{1000} + 1$ 需要佔用 $1002$ 個位置，其中 $999$ 個位置都在儲存無意義的 $0$。

### Sparse Representation(稀疏表示法)
我們強制其指數保持嚴格遞減，並僅記錄非零項。對於包含 $m$ 個非零項的多項式，結構為：
\[(m, e_{m-1}, b_{m-1}, e_{m-2}, b_{m-2}, \ldots, e_0, b_0)\]
此陣列長 $2m+1$ ，包含項數以及指數-係數配對。

PADD(多項式加法):
```cpp
// Scheme-2 sparse polynomial: A[0] = #terms; then (exp, coef) pairs in
// DECREASING exponent order. (Index 0 holds the count, mirroring SPARKS A(1)=m
// with 1-based pairs.) PADD merges A and B by exponent, like the SPARKS code.
vector<int> padd(const vector<int>& A, const vector<int>& B) {
    int m = A[0], n = B[0]; //儲存最高次方
    vector<int> C{0};                         // C[0] filled in at the end
    int p = 1, q = 1;  
                                
    while (p <= 2 * m - 1 && q <= 2 * n - 1) {
        if (A[p] == B[q]) {                         // equal exponents -> add coefs
            int sum = A[p + 1] + B[q + 1];
            if (sum != 0) { C.push_back(A[p]); C.push_back(sum); }
            p += 2; q += 2;
        } else if (A[p] < B[q]) {                  // B's exponent is larger
            C.push_back(B[q]); C.push_back(B[q + 1]); q += 2;
        } else {                                   // A's exponent is larger
            C.push_back(A[p]); C.push_back(A[p + 1]); p += 2;
        }
    }
    while (p <= 2 * m - 1) { 
        C.push_back(A[p]); C.push_back(A[p + 1]); p += 2; 
    }
    while (q <= 2 * n - 1) { 
        C.push_back(B[q]); C.push_back(B[q + 1]); q += 2; 
    }

    C[0] = (int)(C.size() - 1) / 2;                // number of terms
    return C;
}
```

> [!NOTE]
> 在最差情況下，例如 $A(x) = \sum_{i=0}^{n} x^{2i}$ 和 $B(x) = \sum_{i=0}^{n} x^{2i+1}$ ，
> 兩個多項式(分別有 $n$ 與 $m$ 個非零項) 的加法，總計算時間為 $O(n+m)$

---
### Sparse Matrix(稀疏矩陣)

* 改用一維陣列來儲存一系列的 3-Tuple： $(i, j, \text{value})$ 。
* **「先比較列（row）、再比較行（column）」** 的順序排列。
* 陣列的第一個位置（例如 A(0)）會特別用來記錄矩陣的維度與非零元素的總數：$(\text{rows}, \text{columns}, t)$。