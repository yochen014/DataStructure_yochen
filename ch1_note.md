# Ch1 Introduction
## 演算法 (Algorithm) 
在計算機科學中，演算法必須是一個能在有限步驟內完成特定任務的指令集合。它與「程式 (Program)」最大的不同在於有限性 (Finiteness)；例如作業系統是一個程式，但它通常處於等待任務的狀態而不會終止，所以嚴格來說它不是演算法。 
一個嚴謹的演算法必須滿足以下五個條件：  

**Input (輸入)**：需要零個或多個由外部提供的量。

**Output (輸出)**：至少產生一個量。

**Definiteness (明確性)**：每個指令都必須清晰且毫無歧義。

**Finiteness (有限性)**：必須在執行有限步驟之後終止。<br>
反例：找出 $x, y, z$ 使得 $x^n+y^n = z^n$ 有解。

**Effectiveness (有效性)**：每個步驟都必須是基本且可行的（原則上可以用紙筆推演完成。<br>
反例：將 $6/0$ 存入 $x$ 。

# Ch1.5 STL, OOP Design Patterns
STL 是 C++ 內建的強大函式庫，它提供了一套通用的模板類別和函式，讓開發者不用從零開始「造輪子」。你可以把它想像成一個裝滿高級工具的工具箱。

OOP 是一種程式設計的思維典範。傳統的程序導向（Procedural）寫法是把程式看作一連串執行的步驟；而 OOP 則是把程式看作是一群互相互動的「物件 (Objects)」。

如果說 OOP 是給了你磚塊和水泥，那Design patterns就是建築藍圖的參考書。它是前人在軟體開發過程中，面對反覆出現的特定架構問題所總結出來的「最佳解決方案」。
## OOP(物件導向程式設計)
### Pointer(指標) 複習
「指標」 $p$，本質上也是一個變數，只是它儲存的值不是普通的數字，而是一個「位址」。<br>
$$p = A_x$$
 $p$ 「指向」 $x$ 時，就是這個意思。透過解參考（Dereference）運算，我們建立了一個映射，讓你可以直接對該位址上的數值進行操作：
 $$*p \equiv x$$
在 C++ 中，操作指標只需要記住兩個符號：
* & (取址運算子)： 取得變數在記憶體中的位址（對應 $A_x$）。讀作 "address of"。
* *(解參考運算子)： 循著位址，前往該記憶體位置讀取或修改裡面的內容（對應 $*p$）。讀作 "value pointed to by"。

`int* variableName` 代表這個變數是指標，儲存記憶體位址。
<details><summary>星號靠左還是靠右(寫法差異)</summary>

```cpp
int* p;   // 寫法 1 (推薦)：強調型態。變數 p 的型態是 int*
int * p;  // 寫法 2：星號放中間
int *p;   // 寫法 3 (C 語言傳統)：強調解參考。對 p 進行解參考 (*p) 會得到一個 int
```
</details>
<br>
<details><summary>Example: 指標</summary>

```cpp
#include <iostream>
using namespace std;

int main(){
    int x = 10;

    // 宣告一個「指向 int 的指標 p」，給他 x 的位址 (&x) 
    int* p = &x;
    cout << "--- 初始狀態 ---" << "\n";
    cout << "變數 x 的值: " << x << "\n";
    cout << "變數 x 的位址 (&x): " << &x << "\n";
    
    // p 本身儲存的值就是 x 的位址
    cout << "指標 p 儲存的位址: " << p << "\n";
    
    // 透過 *p 可以循著位址找到 x 的值 (10)
    cout << "透過指標讀取 (*p): " << *p << "\n\n";


    cout << "--- 透過指標修改值 ---" << "\n";
    *p = 99; // 循著 p 儲存的位址，將該記憶體空間的值改為 99

    // 因為 *p 實際操作的是 x 的記憶體空間，所以 x 的值會被改變 (變成99)
    cout << "修改 *p 後，變數 x 的值變成: " << x << "\n";

    return 0;
}
```
</details>

---
### Class(類別)
`class` 是一種使用者自訂的資料型態，它將狀態（變數，稱為成員變數）與行為（函式，稱為成員函式）封裝在一起。

`count_` 是一個私有(private)變數，外部程式碼無法改他或執行類似`counter.count_ = -5;` 的操作。

```cpp
#include <iostream>
class Counter {
public:
    Counter() : count_(0) {} //constructor(建構子)
    void increment() {++count_;}
    void reset() {count_ = 0;}
    int value() const {return count_;}
}
```
### Member(資料成員、成員函式)
C++類別成員主要分為資料成員（變數）與成員函式（方法）。資料成員用來儲存物件的狀態，而成員函式定義了物件的行為。兩者皆可依需求宣告為public（公開）或private（私有），藉此實現物件導向的**封裝(Encapsulation)**特性。

### 成員變數(Member Variable)
* **獨立性**：修改物件 A 的成員變數，絕對不會影響到物件 B。
* **全域性**：class內的所有成員函式皆可看見、**修改**這些成員變數。
### 成員函式(Member Function)
「成員函式」就是物件的行為與運算能力（動詞）。在C++內又稱為方法(Method)
### 靜態變數(Static Variable)
屬於整個類別，所有物件共享這一份資料。用`static`開頭。
```cpp
class Matrix {
private:
    // 【一般成員變數 (實體變數)】
    // 每個矩陣物件都有自己獨立的 rows 和 cols
    int rows;
    int cols;

public:
    // 【靜態變數 (Static Variable)】
    // 屬於整個 Matrix 類別，所有物件共享這一份資料
    // 用來記錄「總共創造了多少個矩陣」
    static int totalCount; 

    // 建構子
    Matrix(int r, int c) : rows(r), cols(c) {
        // 每當一個新物件誕生，就讓全域計數器 +1
        totalCount++; 
    }

    // 解構子
    ~Matrix() {
        totalCount--; // 物件消滅時計數器 -1
    }

    // 【成員函式】：計算總元素個數
    int getElementCount() const {
        // area 是一個【區域變數】
        // 它只在這個函式執行的瞬間存在，算完就消失了
        int area = rows * cols; 
        return area;
    }
    
    // 【成員函式】：印出目前狀態
    void printInfo() const {
        cout << "這個矩陣是 " << rows << "x" << cols << "\n";
    }
};

// 【重要語法】靜態變數必須在類別的「外部」進行真正的記憶體分配與初始化
int Matrix::totalCount = 0;
```

### Constructor(建構子)
當你根據 class 的藍圖建立一個具體的「物件」（Object）時，編譯器會自動呼叫一個特殊的成員函式，這就是 **Constructor**。它的唯一目的是初始化物件的狀態。<br>
> [!IMPORTANT]
> 建構子有三個嚴格的語法規則：
> * 名稱必須與 class 完全相同。
> 
> * 絕對沒有回傳值（連 void 都不用寫）。
>
> * 在物件建立時*自動觸發*，無法手動像一般函式那樣呼叫。
---
在嚴謹的程式設計中，未定義的行為（Undefined Behavior） 是最致命的錯誤之一。

如果沒有建構子，當你在記憶體中宣告一個變數時，它會繼承該記憶體區塊殘留的「垃圾值」。建構子確保了每一個物件從誕生的那一刻起，都處於一個合法且可預期的初始狀態，這就像是在進行數學證明前，必須先嚴格定義好所有初始變數的值與範圍一樣。

<details>
<summary>Example:複數class</summary>

```cpp
#include <iostream>
class Complex {
private:
    // 這些是物件的內部狀態，外部無法直接修改 (例如不能直接寫 z.real = 5)
    double real;
    double imag;
public:
    // 1. 預設建構子 (Default Constructor)
    // 當建立物件卻沒有給定參數時，會自動呼叫此建構子
    Complex() {
        real = 0.0;
        ীমag = 0.0;
        std::cout << "呼叫預設建構子：初始化為 0 + 0i\n";
    }
    // 2. 參數化建構子 (Parameterized Constructor)
    // 允許在建立物件時，直接傳入實部與虛部的值
    Complex(double r, double i) {
        real = r;
        imag = i;
        std::cout << "呼叫參數化建構子：初始化為 " << real << " + " << imag << "i\n";
    }
    // 公開的成員函式，提供外部查看內部狀態的介面
    void print() {
        std::cout << "複數值: " << real << " + " << imag << "i\n";
    }
};
int main() {
    // 建立第一個物件：不帶參數，觸發預設建構子
    Complex z1;  
    // 建立第二個物件：帶入兩個 double 參數，觸發參數化建構子
    Complex z2(3.0, 4.0); 
    std::cout << "\n--- 狀態輸出 ---\n";
    z1.print();
    z2.print();
    return 0;
}
```
註解：Complex z1會因為預設建構子獲得初始值 $0+0i$，而z2會直接傳入參數得到值。
</details>

### Destructor(解構子)
解構子是一個特殊的成員函式，它會在物件的生命週期結束（例如離開所在的程式區塊，或是被手動刪除）時自動被呼叫。它的唯一目的是釋放物件在存活期間佔用的外部資源。<br>
> [!IMPORTANT]
>解構子有三個非常嚴格的限制：
> * 名稱是波浪號 ~ 加上類別名稱。
> 
> * 絕對沒有回傳值。
> 
> * 絕對沒有參數。這意味著一個類別只能有一個解構子，不能像建構子那樣進行多載（Overload）。

---

如果你建立的物件只包含簡單的數值（例如複數的 double real, imag），解構子其實**不是必須**的，編譯器預設的清理機制就足夠了。

但假設你正在設計一個用來進行數值分析的 $n$ 維向量類別。這個向量的大小 $n$ 是在執行時期決定的，因此你必須向系統動態借用一塊記憶體（使用 new）。

當這個物件消滅時，它內部指向那塊記憶體的**指標雖然不見了，但那塊記憶體本身並不會自動歸還給系統**。如果不處理，就會造成「記憶體洩漏（Memory Leak）」，程式跑久了就會把系統記憶體吃光並崩潰。

由Constructor獲取資源、在Destructor釋放資源的設計模式稱為
<font color="yellow">**RAII(Resource Acquisition Is Initialization)**</font>。

<details><summary>Example: n 維向量class</summary>

```cpp
#include <iostream>
using namespace std;

class MathVector{
private:
    int* data; //指向動態陣列的指標
    int size;
public:
    MathVector(int n) { //建構子，物件誕生時動態配置記憶體
        size = n;
        data = new int[size] //向系統要一塊連續的記憶體
        cout << "建構子：配置大小為" << size << "的陣列空間\n";
    }
    //解構子，消滅物件前釋放記憶體
    ~MathVector() {
        delete[] data; //把借來的記憶體還給系統 (一個陣列)
    }
    // 一個簡單的操作函式(不重要)
    void setZero() {
        for(int i = 0; i < size; i++) {
            data[i] = 0;
        }
        std::cout << "已將向量初始化為零向量\n";
    }
 
};

void doMath() {
    cout << "進入domath\n";

    MathVector v(5); //建立一個5維向量；自動呼叫建構子
    v.setzero();
    cout << "準備離開domath\n";
    //此時代表 v 的生命走到盡頭，解構子 ~Mathvector() 會被呼叫
}

int main() {
    cout << "程式開始\n";
    doMath();
    cout << "程式結束\n";
    return 0;
}
```
輸出：
```txt
程式開始
--- 進入 doMath 函式區塊 ---
建構子：配置了大小為 5 的陣列空間
已將向量初始化為零向量
--- 準備離開 doMath 函式區塊 ---
解構子：釋放了陣列空間
程式結束
```
</details>

---
### Copy Constructor(複製建構子)
複製建構子是一種特殊的建構子，它的任務是「利用一個已經存在的同型態物件，來初始化一個全新的物件」。<br>
如果你沒有自己寫複製建構子，C++ 編譯器會自動幫你生成一個預設的。這個預設的複製建構子會進行所謂的 **「淺拷貝（Shallow Copy）」** ——也就是把原來物件的所有成員變數，原封不動地複製（賦值）給新物件。

> [!TIP]
> 當你進行以下三種操作時，編譯器會自動呼叫複製建構子：
> 
> * 明確宣告複製： `Complex z2 = z1`; 或 `Complex z2(z1)`;
> 
> * 函式的傳值呼叫（Pass by Value）： 將物件當作參數傳入函式時。
> 
> * 函式的回傳值（Return by Value）： 函式執行完畢，將物件回傳出來時。

如果你的類別只包含像 int 或 double 這樣的純數值，預設的淺拷貝完全沒問題。

但是，如果你的類別內部包含**指標**（動態配置的記憶體），災難就會發生。


<font color='yellow'>**語法規則**</font><br>
> [!CAUTION]
> **複製建構子的參數必須是該類別的常數參考（const ClassName&）**

否則...如果參數是傳值（ClassName other），那麼在呼叫複製建構子、把來源物件傳進去時，系統為了「複製參數」，又會再呼叫一次複製建構子，然後為了傳遞那個參數，又再呼叫一次……這會造成無限遞迴（Infinite Recursion）。因此，必須使用參考來直接存取來源物件，避免產生額外的複製行為。

```cpp
class MathVector {
private:
    int* data;
    int size;

public:
    // 1. 一般建構子
    MathVector(int n) {
        size = n;
        data = new int[size];
        for(int i = 0; i < size; i++) data[i] = 0;
        cout << "一般建構子：配置了大小為 " << size << " 的記憶體\n";
    }
    // 2. 複製建構子 (深拷貝實作)
    MathVector(const MathVector& other) {
        size = other.size;
        // 核心步驟：向系統要一塊『全新的』記憶體
        data = new int[size]; 
        
        // 將來源物件的值，一個一個複製到新記憶體中
        for(int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
        cout << "複製建構子：執行深拷貝，並配置新記憶體\n";
    }
```

<details><summary>Example: 複製一份Array</summary>

```cpp
int main() {
    cout << "--- 建立 V1 ---\n";
    MathVector V1(5);
    V1.setFirstElement(99);

    cout << "\n--- 建立 V2 (觸發複製建構子) ---\n";
    MathVector V2 = V1; 

    cout << "\n--- 獨立性測試 ---\n";
    V2.setFirstElement(888); // 修改 V2 的內容

    cout << "V1 ";
    V1.printFirstElement(); // 若為淺拷貝，V1 也會變成 888。因為是深拷貝，「V1 依然是 99」。
    
    cout << "V2 ";
    V2.printFirstElement(); // 888

    cout << "\n--- 程式結束，準備呼叫解構子 ---\n";
    return 0;
}
```
</details>

---
### Encapsulation(封裝)
```cpp
class Counter {
public:
    Counter() : count_(0) {}      // constructor
    void   increment()       { ++count_; }
    void   reset()           { count_ = 0; }
    int    value() const     { return count_; }

private:
    int count_;                   // invariant: count_ >= 0
};
```
使用者不能直接修改`count_`，但可以透過public method修改，例如`c.increment()`。

---

### Inheritance(繼承)
<font color='yellow'>**語法規則**</font><br>
定義新類別時，使用冒號 : 來指明它繼承自哪一個基礎類別

```cpp
class Circle : public Shape { 
    // ...
};
```
上述例子，Circle為**子類別**，Shape為**父類別**。

### 覆寫(Override)
使用`override`告訴系統這是繼承父類別。不寫`override`程式仍然可動但**危險**
```cpp
class Circle : public Shape {
    public:
        Circle(double r) r_(r) {}
        double area() const override {return 3.14159 * r_ * r_;} //const代表此函數不改變物件成員變數
    private:
        double r_;
};
```

---

### Virtual(虛擬)
用來實現「多型 (Polymorphism)」的關鍵字。它的核心機制是開啟執行期分派 (Runtime Dispatch)。
> [!NOTE]
> 在沒有 virtual 的情況下，編譯器會在編譯階段就決定好要呼叫哪個函數。
> 
> 但如果在基礎類別的函數前加上 virtual，你就是在告訴編譯器：「請在程式執行時，根據物件實際的型別來決定要呼叫哪一個函數版本，而不是根據指標的型別來決定。」

```cpp
class Shape {
    public:
        virtual double area() const = 0; //建立計算面積「虛擬函數」

        virtual ~Shape() = default; //虛擬建構子
}
```
```cpp
virtual ~Shape() {}; //舊版cpp 的虛擬建構子
```
> [!TIP]
> 註解：`virtual` 允許子類別覆寫(override)這個函數；`const`承諾此函數`area()`不修改物件內部變數。；`=0`為「純虛擬函數」之註記，代表父類別不實作。
> 若只有`constant`、沒有`=0`，則就要在父類別(以Shape為例)實作

### 多型(Polymorphism)與模板(Templates)
* Compile-time / **Static** Polymorphism（編譯期多型/靜態多型）<br>
    在編譯期多型中，編譯器會根據上下文來決定函數或運算子的行為方式。這種類型的多型是透過函數多載（function overloading）或運算子多載（operator overloading）來實現的。<br>
    使用Templates:
    ```cpp
    template <typename T>
    T maximum(T a, T b) {
        return (a > b) ? a : b; //三元運算子
    }
    int    x = maximum(3, 7);             // T = int
    double y = maximum(2.5, 1.7);         // T = double
    string s = maximum<string>("apple", "pear"); //顯式指定 (Explicit Specification)
    ```
    註解：`maximum<string>`用來明顯指定其型別，避免進行`>`判斷時邏輯錯誤。(但不會編譯錯誤)

* Run-time Polymorphism（執行期多型）<br>
    與編譯期多型不同，執行期多型中的函數呼叫是在執行期間才被解析，而非在編譯期間由編譯器決定綁定哪一個函數呼叫。<br>
    執行期多型是透過使用虛擬函數（virtual functions）來進行函數覆寫（function overriding）實現的。<br>
    伴隨著虛擬函數表 (vtable) 的指標查詢成本。
    例如：
    ```cpp
    class Shape {
        public:
            virtual double area() const = 0; //建立計算面積「虛擬函數」
            virtual ~Shape() = default; //虛擬建構子
    }
    
    class Circle : public Shape {
    public:
        Circle(double r) r_(r) {}
        double area() const override {return 3.14159 * r_ * r_;} //const代表此函數不改變物件成員變數
    private:
        double r_;
    };
    int main(){
        Circle c(3.0);
        Square q(4.0);
        cout << c.area(); //多型
        cout << q.area(); //多型
    }
    ```

* Class Templates(類別模板)
    `template <typename T>`中的`T`未來被替換成某種型別(可為int, double, string, object...)。
    ```cpp
    class Stack {
    public:
        void push(const T& x) { data_[++top_] = x; } // T& x為call by reference
        T pop()               { return data_[top_--]; }
        bool empty() const    { return top_ == -1; }
    private:
        T data_[1000]; //此陣列可裝1000個類別為T的
        int top_ = -1;
    };
    ```

    ```cpp
    int main() {
        Stack<int>    si;  // 編譯器生成一個內部全部是 int 的 Stack
        Stack<string> ss;  // 編譯器生成一個內部全部是 string 的 Stack
        Stack<Shape*> sp;  // 編譯器生成一個內部全部是指標 Shape* 的 Stack
        return 0;
    }
    ```
    編譯器會根據你提供的型別，自動展開並生成三份各自獨立的類別程式碼。

* Operator Overloading(運算子多載)
    像是我們在定義一個新的代數結構與運算方式(例如二維空間)。
    例如：
    ```cpp
    class Vec2 {
    public:
        Vec2(double x, double y) : x_(x), y_(y) {} //

        Vec2 operator+(const Vec2& o) const { return {x_+o.x_, y_+o.y_}; }
        Vec2 operator*(double s)      const { return {x_*s, y_*s}; }

        friend std::ostream& operator<<(std::ostream& os, const Vec2& v) {
            return os << '(' << v.x_ << ',' << v.y_ << ')';
        }
    private:
        double x_, y_;
    };
    ```
    `Vec2 operator+` 重新定義了加法(就如同向量空間中的加法也要被重新定義一樣)

### Friend function(朋友函數)
今天一個 function 若宣告為 friend 是告訴來引用此類別的人說，我們提供一個公開的方法(規格)，且能夠讓你去存取 private member。但要做什麼，需要你自己來實作。
必須**call by reference**。
如上面例子：
```cpp
friend ostream& operator<<(ostream& os, const Vec2& v) {
    return os << '(' << v.x_ << ',' << v.y_ << ')';
}
Vec2 a(1, 2), b(3, 4);
cout << a + b * 2.0;  // (7,10)
```
> [!NOTE]
> 這段語法是用來定義如何將 `Vec2` 列印到終端機（例如 `cout << a;`）
> 使用`friend`的原因：
> 如果我們把 `operator<<` 寫成 `Vec2` 的一般成員函數，那麼使用的語法會被迫反過來，變成 `a << cout;`，這完全違背了資料流的直覺。<br>
> `operator<<`必須定義為一個獨立於類別之外的全域函數（因為左邊的運算元是 `ostream` 而不是 `Vec2`）

> [!TIP]
> **突破封裝的特權：**
> 因為它是一個外部函數，理當無法存取 `Vec2` 內部私有的 `x_` 與 `y_`。透過在類別內部宣告 `friend`，`Vec2` 等同於給予這個特定的外部函數「破例存取私有成員」的特權。
> 
> 結論：`friend`可**允許外部函數去存取**`private`變數，要謹慎用。
>
### 記憶體管理法則(Zero / Three / Five)
The Rule of Zero / Three / Five

* **The rule of Zero(零法則)**
  如果你的類別沒有「直接」管理任何原始資源（例如沒有手動操作指標或 new/delete），那麼你完全不需要撰寫任何特殊的生命週期函數（write nothing），編譯器生成的預設行為就已經是正確的。
  > [!TIP]
  > 我們應該極力「偏好使用零法則 (Prefer the Rule of Zero)」。其精神在於將原始資源包裝在標準型別內，把繁瑣的記帳工作完全交接給它們。
* **The rule of Three(三法則)**
  只要你的類別需要手動管理一項資源（Manage a resource?），你就必須同時定義這三個函數：**解構子 (destructor)**、**複製建構子 (copy ctor)** 以及**複製賦值運算子 (copy assignment)**。
  > [!TIP]
  > 一旦你寫了自訂的解構子來釋放動態記憶體，編譯器預設的「淺拷貝」就會在物件複製時引發記憶體位址重疊，最終導致雙重釋放 (Double Free) 的崩潰。三法則強制你補齊深拷貝 (Deep Copy) 的邏輯，確保每個物件狀態的絕對獨立。

* **The rule of Five(五法則)**
  在現代 C++ 實務中，如果你因為管理資源而觸發了三法則，你應該進一步補上另外兩個函數：**移動建構子 (move ctor)** 與**移動賦值運算子 (move assignment)**。
  這兩個機制允許我們利用「資源所有權轉移」來取代昂貴的深拷貝，這能將特定操作的時間複雜度從 $O(n)$ 直接微縮至 $O(1)$，是現代 C++ 達成極致效能的關鍵。

```cpp
#include <vector>
#include <string>
using namespace std;

class Good {
    // 遵守「零法則」的最佳示範
    vector<int> data_;  // vector 會自己管理內部動態陣列的生命週期
    string      name_;  // string 也會自己管理字串記憶體
    
    // 複製/移動/銷毀：全部由編譯器自動生成
};
```

### 記憶體管理--Smart Pointers(智慧型指標)
使用原始指標與 `new/delete` 來管理動態記憶體，這非常容易因為忘記釋放或執行期錯誤而導致記憶體外洩。智慧型指標則是將 RAII（資源獲取即初始化）的公理完美封裝的類別。
```cpp
#include <memory>
using namespace std;

// 1. unique_ptr
unique_ptr<Shape> s1 = make_unique<Circle>(3.0); 

// 2. shared_ptr
shared_ptr<Shape> s2 = make_shared<Square>(4.0);
auto s3 = s2; 

// 3. weak_ptr
weak_ptr<Shape> w = s2;
```
其中，
>* `unique_ptr`獨佔存取權：一塊記憶體同時只能被一個指標存取；
> 離開其作用域 (scope exit) 時，底層的記憶體會被自動刪除 (auto-deleted)。

>* `shared_ptr`多對一參考計數：多個獨立的擁有者 (many independent owners) **共享**同一塊記憶體 (shared)。
> 當你將 s2 賦值給 s3 (`auto s3 = s2;`) 時，內部的計數器會嚴格遞增 (ref-count++)。只有當最後一個指向該記憶體的 shared_ptr 被銷毀 (drops it) 且計數器歸零時，記憶體才會被真正刪除。

>* `weak_ptr`觀察者：不擁有任何資源。可以觀察`shared_ptr`管理的物件，但**不增加參考計數**。
> 圖論中的有向圖或雙向鏈結串列時極為關鍵。如果兩個節點透過 `shared_ptr` 互相指向對方，就會形成「循環依賴」，導致參考計數永遠無法歸零，造成記憶體外洩。
>

## STL(標準模板庫Standard Templates Library)
STL四大元件：
* **Container(容器)**：負責儲存資料的結構
* **Iterator(迭代器)**：指向容器內部的指標，它是連接容器與演算法的橋樑
* **Algorithm(演算法)**：透過迭代器來對資料進行運作
* **Function Objects(函數物件)**：用來自訂演算法的特定行為

> [!CAUTION]
> 任何演算法只要搭配相容的迭代器，就能在任何容器上完美運作。這就像是定義了一組廣義的線性算子，只要空間的基底滿足特定條件，該算子就能直接套用。

### Sequence Container(序列容器)
* `vector<T>`：動態陣列(dynamic array)。 $O(1)$ 的隨機存取；與分攤提後的 $O(1)$ 尾端插入 (amortized push_back)。
* `array<T, N>`：固定大小的陣列 (fixed-size array)。配置於**堆疊區 (stack-allocated)**，因此具備**零額外開銷 (no overhead)** 的特性。
* `deque<T>`：分段陣列(segemented array)，其優勢在於支援兩端皆為 $O(1)$ 的推入操作。
* `list<T>`與`forward_list<T>`：分別為雙向與單向鏈結串列 (doubly-linked list / singly-linked list)。只要給特定的迭代器，能在 $O(1)$ 的時間內完成插入與刪除
> [!TIP]
> **預設**選擇為`vector`，快取區域性 (Cache locality) 勝過理論上的複雜度。

### Associative Container(關聯性容器)
依資料結構分為兩大類：
* Ordered(有序：基於樹結構)：`set<T>`與`map<K, V>`內部維持**嚴格遞增**底層實作是紅黑樹 (red-black tree)，這確保了搜尋、插入與刪除在最壞情況下都具備 $O(\log n)$ 
* Unordered(無序：基於雜湊表)：`unordered_set<T>`與`unordered_map<K, V>`內部無序。它們犧牲了順序性，換取了平均 $O(1)$ 的搜尋與插入時間 (average $O(1)$)。
> [!NOTE]
> 字首帶有 multi- 的版本，如 multiset，則允許集合內存在重複的元素。

```cpp
#include <map>
#include <unordered_map>
#include <string>
using namespace std;

int main() {
    map<string, int>           phone;      // 內部是有序的紅黑樹結構
    unordered_map<string, int> phone_fast; // 內部是無序的雜湊表結構
    
    phone["Alice"] = 1234;                 // O(log n) 的插入操作
    return 0;
}
```

### Container Adapters(容器轉接器)
設計模式中，**轉接器模式 (Adapter Pattern)**的核心思想是將一個現有的介面轉換成另一個符合特定邏輯的介面。
這些轉接器本身並不負責底層的記憶體管理，而是包裝了現有的序列容器（如 deque 或 vector）。
```cpp
#include <stack>
#include <queue>
using namespace std;

int main() {
    // 1. Stack
    stack<int> s; 
    s.push(1); s.push(2); 
    int t = s.top(); // t = 2

    // 2. Queue
    queue<int> q; 
    q.push(1); q.push(2); 
    int f = q.front(); // f = 1

    // 3. Priority Queue
    priority_queue<int> pq; 
    pq.push(3); pq.push(7); 
    int m = pq.top(); // m = 7

    return 0;
}
```