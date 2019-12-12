#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int maxn=3*50010;
// parent array
int par[maxn];
/*  k lines' input
    n animals      */
int n,k,ans;
// represent the ith d,x,y
int d[maxn],x[maxn],y[maxn];
// initialize UFS
void init(int x)
{
    for(int i=0;i<x;i++)
        par[i]=i;
}
// find in which set
int find(int x)
{
    return x == par[x] ? x : par[x]=find(par[x]);
}
// union two elements
void Union(int x,int y)
{
    x=find(x);
    y=find(y);
    if(x==y)
        return;
    else
        par[x]=y;
}
// find if two elements in the same set
bool same(int x,int y)
{
    if(find(x)==find(y))
        return true;
    else
        return false;
}
int main()
{
    cin>>n>>k;
    for(int i=0;i<k;i++)
    {
        scanf("%d%d%d",&d[i],&x[i],&y[i]);
        //x[i]--;y[i]--;
    }
    init(3*n);
    for(int i=0;i<k;i++)
    {
        if(x[i]>n || y[i]>n || x[i]<1 || y[i]<1)
        {
            ans++;
            continue;
        }
        if(d[i]==1)
        {
            if(same(x[i],y[i]+n) || same(x[i],y[i]+2*n))
            {
                ans++;
                continue;
            }
            else
            {
                Union(x[i],y[i]);
                Union(x[i]+n,y[i]+n);
                Union(x[i]+2*n,y[i]+2*n);
                continue;
            }
        }
        else
        {
            if(same(x[i],y[i]) || same(x[i],y[i]+2*n))
            {
                ans++;
                continue;
            }
            else
            {
                Union(x[i],y[i]+n);
                Union(x[i]+n,y[i]+2*n);
                Union(x[i]+2*n,y[i]);
                continue;
            }
        }
    }
    cout<<ans<<endl;
}