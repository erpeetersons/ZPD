#include <bits/stdc++.h>
typedef long long ll;
typedef long double d;
using namespace std;
#define wi(x) cout << #x << ' ' << x << '\n'

d E(d phi, d H, d theta) //Calculates energy of system.
{
    return -H * cos(phi - theta) - 0.5 * pow(cos(theta), 2); //Function from Stoner-Wohlfarth model.
}

void createOutput() //Calculates area inside of graph of all minimums of function E in respect to H.
{
    ofstream out;
    out.open("output.txt");
    d phi = 0;
    ll nPhi = 100; //Number of sections that Phi will be divided into.
    d intervalPhi = 0.5 * M_PI / d(nPhi); //Interval that will be added to Phi in every step.
    while(phi <= 0.5 * M_PI)
    {
        d H = -1;
        ll nH = 1000; //Number of sections that H will be divided into.
        d intervalH = 2 / d(nH); //Interval that will be added to H in every step.
        d points[nH][2]; //Array that stores all points of graph. [x][0] is the smaller one, [x][1] is the larger one.
        for(ll i = 0; i < nH; i ++) //Goes trough all H values and finds minimums of function E.
        {
            points[i][0] = 5;
            points[i][1] = 5;
            d theta = 0;
            ll nT = 1000; //Number of sections that theta will be divided into.
            d intervalT = 1 / d(nT) * M_PI * 2; //Interval that will be added to theta in every step.
            for(ll j = 0; j < nT; j ++) //Calculates energy at every theta in one cycle.
            {
                if(E(phi, H, theta) < E(phi, H, theta + intervalT) && E(phi, H, theta) < E(phi, H, theta - intervalT)) //Checks if point is minimum of the function.
                {
                    if(points[i][0] == 5)
                    {
                        points[i][0] = cos(phi - theta); //First minimum.
                    }
                    else
                    {
                        points[i][1] = cos(phi - theta); //Second minimum.
                        break;
                    }
                }
                theta += intervalT; //Increases theta by intervalT.
            }
            if(points[i][1] == 5) //Sets second equal to first, if there's only one minimum.
            {
                points[i][1] = points[i][0];
            }
            if(points[i][1] < points[i][0]) //Arranges in ascending order.
            {
                swap(points[i][0], points[i][1]);
            }
            H += intervalH; //Increases H by intervalH.
        }
        d A = 0;
        for(ll i = 0; i < nH; i ++) //Integrates the function.
        {
            A += (points[i][1] - points[i][0]) * intervalH;
        }
        out << phi * 180 / M_PI << ' ' << A << '\n';
        phi += intervalPhi; //Increases phi by intervalPhi.
    }
    out.close();
}

void createPlotFile(string data_file) //Creates output file for GnuPlot.
{
    ofstream out;
    out.open("plot.plt");
    out << "set term png font " << '"' << "Times,12" << '"' << '\n' << "set encoding utf8" << '\n' << "set output " << '"' << "output.png" << '"' << '\n' << "set xlabel " << '"' << "{/Symbol q}" << '"' << '\n' << "set ylabel " << '"' << "E" << '"' << '\n' << "set title " << '"' << "{/Symbol q f}" << '"' << '\n' << "# unset key" << '\n' << "plot '" << data_file << "' w l lw 2 title " << '"' << "E({/Symbol q})" << '"' << ", 0 lw 1 title " << '"' << '"' << '\n';
    out.close();
}

int main()
{
    string data_file = "output.txt";
    string gnuplot_file = "plot.plt";
    createOutput(); //Calculates points for output function.
    createPlotFile(data_file);
    string sys = "start gnuplot " + gnuplot_file;
    system(sys.c_str());
    return 0;
}
