#include <iostream>
#include <stack>
using namespace std;

long long cal(const long long& a, const long long& b, const string& op){
    if(op == "+") return a + b;
    if(op == "-") return a - b;
    if(op == "*") return a * b;
    if(op == "/") return a / b;

    return 0;
}

int main(){
    int T;
    stack<long long> store;
    cin >> T;
    long long a = 0, b = 0, result = 0;
    string op;
    
    int isFirst=1;
    for(int i=0; i<T; ++i){
        cin >> op;
        if((op == "+") || (op == "-") || (op == "*") || (op == "/")){
        
            b = store.top();
            store.pop();
            a = store.top();
            store.pop();
            // cout << a << " "<<  b << endl;
            // result = cal(a, b, op);
            store.push(cal(a, b, op));
            // cout << "\n" << result << "\n";
        } else {
            store.push(stoll(op));
        }
        
    }
    cout << store.top() << "\n";

    return 0;
}