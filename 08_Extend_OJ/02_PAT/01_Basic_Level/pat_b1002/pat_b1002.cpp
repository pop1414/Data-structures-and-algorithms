// n 小于 10^100，远超long long的范围，所以用字符串数组来接收

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    // 核心优化：关闭cin与stdio的同步，解除cin/cout与C流的绑定
    ios::sync_with_stdio(false);
    // 取消cin的缓冲区同步（进一步提速）
    cin.tie(nullptr);
    // 用'\n'代替endl，避免强制刷新缓冲区

    if (argc > 1)
    {
        freopen(argv[1], "r", stdin);
    }

    string pinyin[] = {"ling", "yi", "er", "san", "si", "wu", "liu", "qi", "ba", "jiu"};

    // 定义长度101的字符数组，足够存100位数字 + \0
    string n;

    cin >> n;

    int num = 0;
    for (char c : n)
    {
        num += c - '0';
    }

    string str_num = to_string(num);

    for (size_t i = 0; i < str_num.size(); i++)
    {
        if (i > 0)
        { // 非第一个字符，先输出空格
            cout << " ";
        }
        // 字符转数字，取对应拼音
        int digit = str_num[i] - '0';
        cout << pinyin[digit];
    }

    return 0;
}