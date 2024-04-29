#include "Mystack.h"
#include <string>
using namespace std;

class tea{
private:
    double pay;
    string name;
public:
    tea(double _pay, string _name): pay(_pay), name(_name){}
    void get_pay()const{
        cout << "价格为：" << pay << ' ';
    }
    void get_name()const{
        cout << "茶叶名为：" << name << endl;
    }
};

int main() {
    Mystack<int> st;
    for(int i = 0; i < 4; i++){
        st.push(i);
    }
    Mystack<int> s;
    for(int i = 0; i < 10; i++){
        s.push(i);
    }
    cout << st.size() << endl;
    cout << s.size() << endl;
    if(st >= s) cout << "st >= s";
    else cout << "st < s";
    st.swap(s);
    cout << endl;
    cout << "swap:" << endl;
    cout << st.size() << endl;
    cout << s.size() << endl;
    Mystack<string> st_;
    st_.push("sss");
    st_.push("aaa");
    cout << st_.size();
    Mystack<tea> _st;
    _st.emplace(1, "ss");
    _st.emplace(10, "aaa");
    _st.emplace(100, "aaaa");
    cout << "iterator: string" << endl;
    for(Mystack<string>::Iterator it = st_.begin(); it != st_.end(); ++it){
        cout << *it << ' ';
    }
    cout << endl;
    cout << "iterator: tea" << endl;
    for(const auto& tea_: _st){
        tea_.get_pay();
        tea_.get_name();
    }
}