#include <iostream>
#include <vector>

using namespace std;

struct Term { //預設public
    int row;
    int col;
    int value;
};


//把a轉置，給到b
void fastTranspose(const vector<Term>& a, vector<Term>& b){
    if(a.empty()) return;

    //儲存矩陣的metadata (a的總列, 總行, 非零元素總數)
    int numRows = a[0].row;
    int numCols = a[0].col;
    int numTerms = a[0].value;

    b.resize(numTerms + 1);
    b[0].row = numCols;
    b[0].col = numRows;
    b[0].value = numTerms;

    if(numTerms > 0){
        vector<int> row_terms(numCols, 0); //a矩陣第i行非零元素個數
        vector<int> starting_pos(numCols, 0); //b矩陣第i行應該從哪個idx開始釋放

        //計算a每一行有多少非零元素，時間複雜度O(t)
        for(int i=1; i<= numTerms; ++i){ 
            row_terms[a[i].col]++;
        }

        //計算每一行轉置後從哪個idx開始擺放，O(n)
        starting_pos[0] = 1; //初始條件
        for(int i=1; i < numCols; ++i){
            starting_pos[i] = starting_pos[i-1] + row_terms[i-1];
        }

        for(int i=1; i<=numTerms; ++i){
            int c = a[i].col; //取得原本的行，未來的列
            int j = starting_pos[c]; //取得目標idx

            b[j].row = a[i].col;
            b[j].col = a[i].row;
            b[j].value = a[i].value;
            starting_pos[a[i].col]++;
        }
    }
}
