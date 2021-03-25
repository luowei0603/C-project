/*----------------------------
j        0  1  2  3  4  5  6  7  8
p        a  b  a  b  a  a  a  b  a
next     -1 0  0  1  2  3  1  1  2
nextval  -1 0  -1 0  -1 3  1  0  -1
------------------------------*/

#include <iostream>
#include <string.h>
using namespace std;
/*暴力解法*/
int ViolentMatch(const char *s, const char *p)
{
    int slen = strlen(s);
    int plen = strlen(p);

    int i = 0;
    int j = 0;
    while (i < slen && j < plen)
    {
        if (s[i] == p[j])
        {
            i++;
            j++;
        }
        else
        {
            i = i - j + 1;
            j = 0;
        }
    }
    if (j == plen)
    {
        return i - j;
    }
    else
    {
        return -1;
    }
}
/*KMP获取next数组*/
void GetNext(const char *p, int *next)
{
    int plen = strlen(p);
    next[0] = -1;
    int k = -1;
    int j = 0;
    while (j < plen - 1)
    {
        // p[k]表示前缀，p[j]表示后缀
        if (k == -1 || p[j] == p[k])
        {
            ++k;
            ++j;
            next[j] = k;
        }
        else
        {
            k = next[k]; // 若字符不相同，将j值回溯
        }
    }
}
/*改进后的KMP获取next数组*/
void GetNextval(const char *p, int *next)
{
    int plen = strlen(p);
    next[0] = -1;
    int k = -1;
    int j = 0;
    while (j < plen - 1)
    {
        // p[k]表示前缀，p[j]表示后缀
        if (k == -1 || p[j] == p[k])
        {
            ++j;
            ++k;
            // 若当前字符与前缀字符不同，则当前的k为nextval在j位置上的值
            if (p[j] != p[k])
            {
                next[j] = k;
            }
            else
            {
                // 如果与前缀字符相同，则将前缀字符的nextval值赋值给nextval在j位置的值
                next[j] = next[k];
            }
        }
        else
        {
            k = next[k];
        }
    }
}

int KmpSearch(const char *s, const char *p)
{
    int i = 0;
    int j = 0;
    int slen = strlen(s);
    int plen = strlen(p);
    int *next = (int *)malloc(sizeof(int) * plen);
    //GetNext(p,next);
    GetNextval(p, next);
    while (i < slen && j < plen)
    {
        if (j == -1 || s[i] == p[j])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
        }
    }
    if (j == plen)
    {
        return i - j;
    }
    else
    {
        return -1;
    }
}

int main()
{
    string s;
    string p;
    int ret;
    cout << "input s:" << endl;
    cin >> s;
    cout << "input p:" << endl;
    cin >> p;
    ret = KmpSearch(s.c_str(), p.c_str());
    cout << "p in s pos:" << ret << endl;
    return 0;
}