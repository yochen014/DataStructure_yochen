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
### Constructor(建構子)
當你根據 class 的藍圖建立一個具體的「物件」（Object）時，編譯器會自動呼叫一個特殊的成員函式，這就是 **Constructor**。它的唯一目的是初始化物件的狀態。<br>
建構子有三個嚴格的語法規則：
* 名稱必須與 class 完全相同。

* 絕對沒有回傳值（連 void 都不用寫）。

* 在物件建立時*自動觸發*，無法手動像一般函式那樣呼叫。
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
解構子有三個非常嚴格的限制：
* 名稱是波浪號 ~ 加上類別名稱。

* 絕對沒有回傳值。

* 絕對沒有參數。這意味著一個類別只能有一個解構子，不能像建構子那樣進行多載（Overload）。
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
</details>