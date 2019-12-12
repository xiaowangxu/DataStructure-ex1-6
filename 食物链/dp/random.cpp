#include <bits/stdc++.h>
using namespace std;
int main()
{
    mt19937 rnd(time(0));
    int n = rnd()%50000+1, k = rnd()%100001;
    cout<<n<<' '<<k<<endl;
    for(int i=0;i<k;i++)
    {
        cout<<(rnd()%2+1)<<' '<<(rnd()%(n-1))+1<<' '<<(rnd()%(n-1))+1<<endl;
    }
}