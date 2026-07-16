#include <iostream>
using namespace std;

class PNode{
public:
    int coef;
    int exp;
    PNode* link = nullptr;
};

void attach(int coef, int exp, PNode*& d){ // d為尾端指標
    d->link = new PNode{coef, exp, nullptr}; // 指向一個 新末節點
    d = d->link; //動態的移動到最尾端
}

PNode* padd(const PNode* p, const PNode* q){
    PNode head{0, 0, nullptr}; //一個空的記憶體
    PNode* d = &head;

    while(p && q){
        if(p->exp == q->exp){
            int sum = p->coef + q->coef;
            if(sum != 0)
                attach(sum, p->exp, d);
        } else if (p->exp < q->exp){
            attach(q->coef, q->exp, d);
            q = q->link; //q移動到下個冪次
        } else {
            attach(p->coef, p->exp, d);
            p = p->link; //p移動到下個冪次
        }
    }
    //處理剩下沒走完的(若p現在指向nullptr，則q還有剩下的節點，反之亦然)
    for(; p; p = p->link){
        attach(p->coef, p->exp, d);
    }
    for(; q; q = q->link){
        attach(q->coef, q->exp, d);
    }

    return head.link; // 回傳第一個節點
    //因為head的type是 PNode，所以用一個點
    //若為PNode* 的type，則使用 ->link。
}

//static 代表別的專案看不見這個函數
static PNode* term(int c, int e, PNode* next){
    PNode* p = new PNode{c, e, next};
    return p;
}

//測試
void demo44(){
    PNode* A = term(3, 14, term(2, 8, term(1, 0, nullptr)));
    PNode* B = term(8, 14, term(-3, 10, term(10, 6, nullptr)));

    for(PNode* r = padd(A, B); r; r = r->link){}
}