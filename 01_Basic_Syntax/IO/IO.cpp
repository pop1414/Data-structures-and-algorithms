#include <bits/stdc++.h>

using namespace std;

void redirect_input(){
    ifstream fin("./test_case");
    cin.rdbuf(fin.rdbuf());
}

     
int main()
{

    redirect_input();

    int a, b;

    cin >> a >> b;
    cout << a + b << endl;

    return 0;
}