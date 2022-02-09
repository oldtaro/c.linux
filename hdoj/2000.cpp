#include <iostream>
using namespace std;
#define swap(a,b) {char temp=a;a=b;b=temp;}
//输入三个字符由ASCII码大小输出三个字符
int main(void){
    char a[4];
    while(cin>>a){
        if(a[0]>a[1]){
            swap(a[0],a[1]);
        }
        if(a[1]>a[2]){
            swap(a[1],a[2]);
        }
        if(a[0]>a[1]){
            swap(a[0],a[1]);
        }
        cout <<a[0]<<' '<<a[1]<<' '<<a[2]<<endl;
    }
    return 0;
}