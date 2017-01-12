#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

int main()
{
    ifstream fin("coding_contest_creation.txt");
    ofstream fout("output.txt");
    
    int T, N, R;
    fin >> T;
    for (int k=1; k<=T; k++)
    {
        fin >> N;
        
        //GREEDY
        R=0;
        int D, prevD;
        int currPos = 0;
        fin >> prevD;
        for (int i=1; i<N; i++)
        {
            fin >> D;
            int xtra = 0;
            if (currPos!=3)
            {
                if (D>prevD)
                    xtra = min((D-prevD-1)/10, 3 - currPos);
                else
                    xtra = 3 - currPos;
            }
            R+=xtra;
            currPos+=xtra+1;
            currPos%=4;
            
            prevD = D;
        }
        R += 3-currPos;
        fout << "Case #"<<k<<": "<<R<<endl;
    }
    
    
    fin.close();
    fout.close();
    return 0;
}
