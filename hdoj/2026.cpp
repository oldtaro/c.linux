#include <iostream>
#include <string>
using namespace std;

int main(void){
    string str,cur;
    while(getline(cin,str)){
        cur=str.at(0)-32;
        str.replace(0,1,cur,0,1);
        cout<<str<<endl;
    }
    return 0;
}