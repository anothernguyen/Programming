#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

int main()
{
    int R = 50;
    int n;
    ifstream fin("progress_pie.txt");
    ofstream fout("progress_pie_output.txt");
    fin >> n;
    for (int i=1; i<=n; i++)
    {
        double p, x, y, pp;
        fin >> p >> x >> y;
        x -= 50; y-=50;
        double d = sqrt(x*x+y*y);
        if (d > R)
        {
            fout << "Case #" << i << ": white"<<endl;
            continue;
        }
        else
        {
            if (y==0)
            {
                if (x>0)
                    pp = 0;
                else
                    pp = 180;
            }
            else
            {
                pp = atan2(y, x)/M_PI*180;
                pp = fmod((450-pp), 360);
                pp = pp/3.6;
                if (pp>p)
                    fout << "Case #" << i << ": white"<<endl;
                else
                    fout << "Case #" << i << ": black"<<endl;
            }
        }
    }
    fin.close();
    fout.close();
    
    
    return 0;
}
