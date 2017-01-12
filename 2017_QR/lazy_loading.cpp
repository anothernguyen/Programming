#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

int main()
{
    ifstream fin("lazy_loading.txt");
    ofstream fout("lazy_loading_output.txt");
    int ndays;
    fin >>ndays;
    int p[100];
    for (int i=1; i<=ndays; i++)
    {
        int np;
        fin >> np;
        for (int j=0; j<np; j++)
            fin >> p[j];
        sort(p, p+np);
        int l=0, r=np-1;
        int upperBound = 50;
        int count = 0;
        fout << "Case #" <<i<<": ";
        
        while (l<=r)
        {
            int heaviest = p[r];
            int nl = upperBound/heaviest;
            if (nl*heaviest<upperBound)
                nl++;
            nl-=1;
            l+=nl;
            if (l>r)
                break;
            else
                count++;
            r--;
        }
        fout <<count<< endl;
        
    }
    fin.close();
    fout.close();
    return 0;
}
