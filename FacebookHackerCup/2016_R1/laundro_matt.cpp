#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <queue>
#include <vector>
#include <functional>

using namespace std;

class Pair
{
public:
    long long W, t_W;
    Pair()
    {
        W = 0; t_W = 0;
    }
    Pair(long long a, long long  b)
    {
        W = a; t_W = b;
    }
};

bool compare(Pair p1, Pair p2)
{
    return p1.t_W > p2.t_W;
}

int main()
{
    ifstream fin("laundro_matt.txt");
    ofstream fout("output.txt");
    
    int T, L, N, M = 0, D;
    long long  R;
    fin >> T;
    for (int k=1; k<=T; k++)
    {
        priority_queue<Pair, vector<Pair>, std::function<bool(Pair, Pair)>> WM(compare);
        fin >> L >> N >> M >> D;
        Pair* Dryers = new Pair[M];
        int i_dryer = 0;
        for (int i=0; i<M; i++)
        {
            Dryers[i].W = D;
            Dryers[i].t_W = 0;
        }
        for (int i = 0; i<N; i++)
        {
            Pair p;
            fin >> p.W;
            p.t_W = p.W;
            WM.push(p);
        }
        
        for (int i=0; i<L; i++)
        {
            Pair p = WM.top();
            WM.pop();
            Dryers[i_dryer].t_W = max(Dryers[i_dryer].t_W, p.t_W) + Dryers[i_dryer].W;
            p.t_W+=p.W;
            WM.push(p);
            i_dryer++;
            i_dryer%=M;
        }
        R = Dryers[(L-1)%M].t_W;
        
        fout << "Case #" << k <<": " << R << endl;
    }
    
    
    fin.close();
    fout.close();
    return 0;
}
