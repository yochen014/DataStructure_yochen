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
* 當迴圈執行到第 $i$ 次時，`A[i]` 提取出的就是第 $i$ 個非零元素的 3-Tuple。這個 Tuple 內部的三個位置嚴格定義如下： 
* `A[i][0]`：該元素在原矩陣中的列索引（Row）。  
* `A[i][1]`：該元素在原矩陣中的行索引（Column）。 
* `A[i][2]`：該元素的實際非零數值（Value）。

## Matrix Transpose(矩陣轉置)
在使用二維陣列時，這只是簡單的雙重迴圈，時間複雜度為 $O(nm)$。但換成 3-Tuple 表示法後，如果我們直接依序讀取元素並互換行列，會因為不知道目標位置在哪，導致大量的資料搬移。

### Algorithm Transpose(基本轉置演算法)
為了避免搬移，我們可以改成**「依序掃描行（column）」**：找出所有第 $1$ 行的元素放到新陣列的第 $1$ 列，再找第 $2$ 行，以此類推。
時間複雜度為 $O(nt)$ ，其中 $n$ 為總行數，$t$ 為非零元素數。
```cpp
using Sparse = vector<array<int,3>>;

Sparse transposeSlow(const Sparse& A) {
    int m = A[0][0], n = A[0][1], t = A[0][2]; //A[0]先記錄矩陣維度與非零元素總數
    Sparse B(1);
    B[0] = {n, m, t};                              // dimensions swap
    if (t <= 0) return B;
    for (int col = 1; col <= n; ++col)             // transpose by columns
        for (int p = 1; p <= t; ++p)               // scan all nonzero terms
            if (A[p][1] == col)                    // element in this column?
                B.push_back({A[p][1], A[p][0], A[p][2]});   // (j, i, value)
    return B;
}
```

> [!CAUTION]
> 致命缺陷：當矩陣不夠稀疏（即 $t \approx nm$）時，這個演算法的時間複雜度會退化成 $O(n^2 m)$，這比傳統陣列的 $O(nm)$ 還要慢非常多！

### Algorithm Fast_Transpose(快速轉置演算法)
以 **空間換取時間**，建立兩個輔助陣列：
*  $S(k)$：記錄原矩陣中第 $k$ 行的非零元素個數（等同於轉置後第 $k$ 列的元素個數）
*  $T(k)$：記錄轉置後第 $k$ 列在目標陣列中的「起始儲存位置」。(轉置後的矩陣 $B$ 中，第 $k$ 列的第一個元素，必須放在 $B$ 陣列的哪一個索引位置)

這是一個遞迴式子，起始條件為 $T(1)=1$
\[T(i) = T(i-1) + S(i-1)\]
有了 $T$ 陣列，我們只需要遍歷一次原陣列，就能以 $O(1)$ 的時間知道每個元素轉置後的確切位置並直接存入。
> [!NOTE]
> 嚴謹分析：計算 $S$ 耗時 $O(t)$，計算 $T$ 耗時 $O(n)$，搬移資料耗時 $O(t)$，整體時間複雜度大幅降至 $O(n+t)$。即便在最糟情況下（$t \approx nm$），它也等同於 $O(nm)$，完美達到了「既省空間又不犧牲效能」的境界。

```cpp
using Sparse = std::vector<std::array<int,3>>;

Sparse fastTranspose(const Sparse& A) {
    int m = A[0][0], n = A[0][1], t = A[0][2];
    Sparse B(t + 1);
    B[0] = {n, m, t}; //轉置後的資訊
    if (t <= 0) { B.resize(1); return B; }

    vector<int> S(n + 1, 0), T(n + 1, 0);
    for (int i = 1; i <= t; ++i) 
        S[A[i][1]]++;     // 算各行共有多少非零元素
    T[1] = 1;

    for (int i = 2; i <= n; ++i) 
        T[i] = T[i-1] + S[i-1];   // starting positions

    for (int i = 1; i <= t; ++i) {                 // move each element once
        int j = A[i][1];                           // A的行 是 B的列
        B[T[j]] = {A[i][1], A[i][0], A[i][2]}; // B的列放 A的()
        T[j]++;
    }
    return B;
}
```

