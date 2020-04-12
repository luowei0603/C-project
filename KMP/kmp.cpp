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
            k = next[k];
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
            if (p[j] != p[k])
            {
                next[j] = k;
            }
            else
            {
                // 因为不能出现p[j] = p[ next[j ]]，所以当出现时需要继续递归，k = next[k] = next[next[k]]
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