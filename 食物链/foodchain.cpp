#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int maxn = 3 * 50010;
/* 

题意如下：
已知有三类动物A、B、C，可以形成A吃B，B吃C，C吃A
1 X Y 表示 X 和 Y是同类
2 X Y 表示 X 吃 Y
有 K 句话描述动物之间的关系，那么是假话的情况为以下三种：
①当前的话与之前的话冲突
②X || Y 比 N 大
③X 吃 X

题解如下：
要求的是动物之间的同类关系和互相吃的关系，可以维护表示动物之间关系的并查集解决问题
由于有三种动物，我们并不知道描述的是哪一种动物
因此对于某一动物i，我们可以用 i-A,i-B,i-C 代表三种不同类型的动物i
由于动物一共有n个，我们需要一个空间为 n*3 的并查集容纳下所有可能的情况
即利用0~n-1表示A，n~2n-1表示B，2n~3n-1表示C
可以简单认为par[i]表示同类关系，par[i+n]表示猎物关系，par[i+2*n]表示天敌关系
接着开始判断说的话：
即若X和Y是同类，在这句话前若有出现X和Y是猎物或天敌关系，则为假
若X吃Y，则在这句话前有X和Y是同类或Y吃X，则为假
对于 1 X Y 的情况，当且仅当 X-A 与 Y-B 或 X-A 与 Y-C 在同一个集合中时产生冲突
因为 A 吃 B ， C 吃 A ，他们并不能是同类
若不产生冲突，那么合并 X-A与Y-A 和 X-B与Y-B 和 X-C与Y-C
对于 2 X Y 的情况，当且仅当 X-A 与 Y-A 或 X-A 与 Y-C 在同一个集合中时产生冲突
因为都是A类时他们是同类，不会发生 X吃Y 的 情况
而X是A类，Y是C类时，由于C吃A，不会发生X吃Y的情况
若不产生冲突，那么合并 X-A与Y-B 和 X-B 和 Y-C 和 X-C 和 Y-A

*/
// parent array
int par[maxn];
/*  k lines' input
    n animals      */
int n, k, ans;
// represent the ith d,x,y
int d[maxn], x[maxn], y[maxn];
// initialize UFS
void init(int x)
{
    for (int i = 0; i < x; i++)
        par[i] = i;
}
// find in which set
int find(int x)
{
    return x == par[x] ? x : par[x] = find(par[x]);
}
// union two elements
void Union(int x, int y)
{
    x = find(x);
    y = find(y);
    if (x == y)
        return;
    else
        par[x] = y;
}
// find if two elements in the same set
bool same(int x, int y)
{
    if (find(x) == find(y))
        return true;
    else
        return false;
}
int main()
{
    // Input
    cin >> n >> k;
    for (int i = 0; i < k; i++)
        scanf("%d%d%d", &d[i], &x[i], &y[i]);
    // Initialize
    init(3 * n);
    // handle Input
    for (int i = 0; i < k; i++)
    {
        // if （ X || Y ） > （ N || <0 ） , ans++
        if (x[i] > n || y[i] > n || x[i] < 1 || y[i] < 1)
        {
            ans++;
            continue;
        }
        // if d == 1
        if (d[i] == 1)
        {
            // if x-A and (y-B || y-C) in the same set
            if (same(x[i], y[i] + n) || same(x[i], y[i] + 2 * n))
            {
                ans++;
                continue;
            }
            // if not in the same set union them
            else
            {
                Union(x[i], y[i]);
                Union(x[i] + n, y[i] + n);
                Union(x[i] + 2 * n, y[i] + 2 * n);
                continue;
            }
        }
        else
        {
            // if x-A and (y-A || y-C) in the same set
            if (same(x[i], y[i]) || same(x[i], y[i] + 2 * n))
            {
                ans++;
                continue;
            }
            // if not in the same set union them
            else
            {
                Union(x[i], y[i] + n);
                Union(x[i] + n, y[i] + 2 * n);
                Union(x[i] + 2 * n, y[i]);
                continue;
            }
        }
    }
    cout << ans << endl;
}