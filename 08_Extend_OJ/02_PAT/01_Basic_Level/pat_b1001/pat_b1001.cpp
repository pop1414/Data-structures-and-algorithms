// input: 0 < n <= 1000
// 输入n，如果是偶数砍掉一半，如果是奇数，把3n + 1 砍掉一半。计算需要多少步，使得n == 1
// output: 从 n 计算到 1 需要的步数。

#include <cstdio>
#include <iostream>
#include <fstream>

using namespace std;

void redirect_input(const char *file_path)
{
    FILE *fin = freopen(file_path, "r", stdin);

    if (fin == NULL)
    {
        fprintf(stderr, "错误：test_case 文件不存在或路径错误！\n");
        exit(1); // 打开失败直接退出程序
    }
}

int main(int argc, char *argv[])
{

    if (argc > 1)
    {
        redirect_input(argv[1]);
    }

    int n;
    scanf("%d", &n);

    int step = 0;

    while (n != 1)
    {
        if (n % 2 == 0)
        {
            n = n / 2;
            step++;
        }
        else
        {
            n = (3 * n + 1) / 2;
            step++;
        }
    }

    printf("%d", step);

    return 0;
}