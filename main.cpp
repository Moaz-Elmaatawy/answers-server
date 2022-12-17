#include <iostream>
using namespace std;
int main() {
    freopen("questions.txt" ,"w" ,stdout);
    for(int i=1;i<=120;++i){
        cout<<i<<"-"<<(char)(rand()%4 + 'A')<<endl;
    }
    return 0;
}
