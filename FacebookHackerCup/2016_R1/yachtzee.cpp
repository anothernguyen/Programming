#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <queue>
#include <vector>
#include <functional>
#include <iomanip>

using namespace std;

int main()
{
    ifstream fin("yachtzee.txt");
    ofstream fout("output.txt");
    
    int T, N, A, B;
    double R = 0;
    
    fin >> T;
    
    for (int k=1; k<=T; k++)
    {
        fin >> N >> A >> B;
        long long* C = new long long[N+1];
        long long sum = 0;
        for (int i=0; i<N; i++)
        {
            fin >> C[i];
            sum += C[i];
        }
        
        int n = A;
        double avg = 0;
        double* preCal = new double[N];
        double preSum = 0;
        for (int i=0; i<N; i++)
        {
            //int lowerBound = 0;
            //int upperBound = C[i];
            //int range = C[i];
            //preCal[i] = (upperBound - lowerBound) / 2.0 * range;
            preCal[i] = C[i]*C[i]/2.0;
            preSum += preCal[i];
        }
        
        // ... [start] ... [N]
        // nTurns x ([1] ... [N])
        // [1] ... [end] ...
        
        //nTurns
        int nTurns = B/sum - A/sum - 1;
        if (A%sum==0)       // (A%sum==0) -> nTurns = B/sum - A/sum
            nTurns +=1;
        if (nTurns > 0)
            avg += nTurns * preSum;
        else
            nTurns = 0;
        
        //start
        int posStart = 0;
        long long r = A % sum;
        if (r!=0)
        {
            int l = 0;
            for (; l<N; l++)
            {
                r -= C[l];
                if (r<0)
                {
                    r+= C[l];
                    posStart = l;
                    break;
                }
            }
            int upperBound = (B>C[l])?C[l]: B;
            avg += (r+upperBound)/2.0*(upperBound-r);
            if (nTurns != 0)
            {
                for (l+=1; l<N; l++)
                    avg += preCal[l];
            }
        }
        
        //end
        r = B % sum;
        if (r!=0)
        {
            int l = 0;
            for (; l<N; l++)
            {
                r -= C[l];
                if (r<0)
                {
                    r+= C[l];
                    break;
                }
                if ((nTurns!=0) || ((nTurns==0) && (l>posStart)))
                    avg += preCal[l];
                    
            }
            if (nTurns!=0)
            {
                int lowerBound = 0;
                if (l>0)
                    lowerBound = C[l];
                avg += (r)/2.0*(r);
            }
        }
        
        R = avg / (B-A);
        fout <<setprecision(6)<<fixed<< "Case #" << k<< ": " << R << endl;
    }
    
    
    fin.close();
    fout.close();
    return 0;
}
