#include <iostream>
using namespace std;

struct PNode{
    int coef;
    int exp;
    PNode* link = nullptr;
};

//較花時間方法O(n)，線性串列回收
//為了將整串 $t$ 完美地銜接在 $avail$ 的前面，
//我們必須找到 $t$ 串列的「尾巴」，才能將這條線連到 $avail$ 的「頭部」。

void erase(PNode*& t, PNode*& avail){ //t為要回收的串列的頭部指標(入口)，avail為可用串列
    if(!t)
        return;
    PNode* p = t; //p為t
    while(p->link){ //讓他走訪到尾端
        p = p->link;
    }
    p->link = avail; //
    avail = t; //回收池新入口
    t = nullptr; //將t的頭部指向nullptr，避免野指標
}

// 較快方法：環狀串列O(1)
void cerase(PNode*& t, PNode*& avail){
    if(!t)
        return;
    PNode* first = t->link; 
    t->link = avail;
    avail = first;
}

"""
+------------------------------------------+
     V                                          |
    [ t ] ---> [ first ] ---> [ ... ] ---> [ tail ]
                 ^
                 |
      first -----+  (記住這個位置)
"""

"""
            [ first ] ---> [ ... ] ---> [ tail ]
                 ^                          |
                 |                          |
      first -----+                          V
                                          [ t ]
                                            |
                                            | (嫁接！)
                                            V
 avail ---> [ 舊的 A_1 ] ---> [ 舊的 A_2 ] ---> nullptr
"""

"""
avail ------------------------------------+
                                            |
                                            V
               [ first ] ---> [ ... ] ---> [ tail ]
                                            |
                                            V
                                          [ t ]
                                            |
                                            V
            [ 舊的 A_1 ] ---> [ 舊的 A_2 ] ---> nullptr
"""