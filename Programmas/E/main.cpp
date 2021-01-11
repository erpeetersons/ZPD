#include <bits/stdc++.h>
typedef long long ll;
typedef long double d;
using namespace std;
#define wi(x) cout << #x << ' ' << x << '\n'

d E(d phi, d H, d theta) //Calculates energy of system.
{
    return -H * cos(phi - theta) - 0.5 * pow(cos(theta), 2); //Function from Stoner-Wohlfarth model.
}

void createOutput(d phi, d H) //Calculates every point of function E and determines minimums of the function.
{
    ofstream out;
    out.open("output.txt");
    d theta = 0;
    ll n = 100000; //Number of sections that theta will be divided into.
    d interval = 1 / d(n) * M_PI * 2; //Interval that will be added to theta in every step.
    for(ll i = 0; i < n; i ++) //Calculates energy at every theta in one cycle.
    {
        out << theta << ' ' << E(phi, H, theta) << '\n';
        if(E(phi, H, theta) < E(phi, H, theta + interval) && E(phi, H, theta) < E(phi, H, theta - interval)) //Outputs point if it is minimum of the function.
        {
            cout << "Minimum: " << theta << '\n';
        }
        theta += interval; //Increases theta by interval.
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
    d H;
    d angle;
    cout << "Insert angle: ";
    cin >> angle;
    cout << "Insert H: ";
    cin >> H;
    d phi = angle * M_PI / 180;
    string data_file = "output.txt";
    string gnuplot_file = "plot.plt";
    createOutput(phi, H); //Calculates points for output function.
    createPlotFile(data_file);
    string sys = "start gnuplot " + gnuplot_file;
    system(sys.c_str());
    return 0;
}
