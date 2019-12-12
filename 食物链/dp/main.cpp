#include <bits/stdc++.h>
using namespace std;
int main()
{
    FILE *fp = fopen("ans.txt", "w");
    for(int T = 0;T<100;T++)
    {
        system("random > data.in");
        double sst = clock();
        system("bf < data.in > data.ans");
        double st = clock();
        system("sol < data.in > data.out");
        double et = clock();
        if(system("fc data.out data.ans"))
        {
            puts("Wrong Answer\n");
            fprintf(fp,"Wrong Answer\n");
            return 0;
        }
        else
        {
            printf("Accepted, case: #%d,time sol: %.0fms, time bf: %.0fms\n",T,et-st,st-sst);
            fprintf(fp,"Accepted, case: #%d,time sol: %.0fms, time bf: %.0fms\n",T,et-st,st-sst);
        }
    }
    return 0;
}
