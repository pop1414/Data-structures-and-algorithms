#include <bits/stdc++.h>

using namespace std;

// <iostream>
void redirect_input()
{
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

// <stdio>
// void redirect_input()
// {
//     FILE *fin = freopen("./test_case", "r", stdin);

//     if (fin == NULL)
//     {
//         fprintf(stderr, "错误：test_case 文件不存在或路径错误！\n");
//         exit(1); // 打开失败直接退出程序
//     }
// }

// int main()
// {

//     redirect_input();

//     int n;
//     scanf("%d", &n);

//     int step = 0;

//     while (n != 1)
//     {
//         if (n % 2 == 0)
//         {
//             n = n / 2;
//             step++;
//         }
//         else
//         {
//             n = (3 * n + 1) / 2;
//             step++;
//         }
//     }

//     printf("%d", step);

//     return 0;
// }