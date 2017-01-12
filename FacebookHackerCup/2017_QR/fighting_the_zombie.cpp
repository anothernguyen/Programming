#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

double calProb(int nSides, int nRolling, double extra, double minDamage)
{
    double sum[21][401];
    int w = nSides*nRolling;
    int h = nRolling;
    for (int iw=0; iw<w; iw++)
    {
        sum[1][iw] = 0;
    }
    for (int i = 1; i<=nSides; i++)
    {
        sum[1][i] = 1;
    }
    for (int ih = 2; ih<=h; ih++)
    {
        for (int iw=0; iw<ih; iw++)
        {
            sum[ih][iw]=0;
        }
        for (int iw=ih; iw<=w; iw++)
        {
            sum[ih][iw] = 0;
            for (int i=iw-1; (i>=iw-nSides) && (i>=0); i--)
            {
                sum[ih][iw]+=sum[ih-1][i];
            }        }
    }
    
    
    double nCases = 0;
    for (int i=nRolling; i<=w; i++)
    {
        nCases += sum[h][i];
    }
    double nTrueCases = 0;
    double targetScore = minDamage-extra;
    for (int i=targetScore; i<=w; i++)
    {
        nTrueCases += sum[h][i];
    }
    
    double prob = nTrueCases/nCases;
    
    return prob;
}

int main()
{
    ifstream fin("fighting_the_zombie.txt");
    ofstream fout("fighting_the_zombie_output.txt");
    int T, H, S;
    int nSides, nRolling, nExtra;
    unsigned long posd, poss;
    double prob = 0;
    string st;
    
    fin >>T;

    for (int i=1; i<=T; i++)
    {
        prob=0;
        fin >> H >> S;
        fout << "Case #" <<i<<": ";
        for (int j=0; j<S; j++)
        {
            fin >> st;
            if (prob==1)
                continue;
            posd = st.find('d', 0);
            nRolling = atoi(st.substr(0, posd).c_str());
            poss = st.find('+', posd+2);
            if (poss == st.npos)
                poss = st.find('-', posd+2);
            if (poss== st.npos)
            {
                nExtra = 0;
                nSides = atoi(st.substr(posd+1, st.length()-posd-1).c_str());
            }
            else
            {
                nExtra = atoi(st.substr(poss+1, st.length()-poss-1).c_str());
                if (st[poss] == '-')
                    nExtra = -nExtra;
                nSides = atoi(st.substr(posd+1, poss-posd-1).c_str());
            }
            double p = 0;
            if (H-nExtra <= nRolling)
                p=1;
            else if (H-nExtra > nRolling*nSides)
            {
                p=0;
            }
            else
                p = calProb(nSides, nRolling, nExtra, H);
            if (p>prob)
                prob = p;
        }
        fout << prob << endl;
    }
    fin.close();
    fout.close();
    return 0;
}
