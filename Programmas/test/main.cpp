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
    d q = 1.75e5;
    q *= 4;
    d T = 17;
    d R = 0.0125;
    ll nR = 1000;
    d R0 = 0.02;
    d intervalR = R0 / d(nR);
    for(ll i = 0; i <= nR; i ++) {
        if(intervalR*i < R)out << intervalR*i << ' ' << q / 6 * (3*pow(R, 2) - pow(intervalR*i, 2)) + T << '\n';
        else out << intervalR*i << ' ' << q * pow(R, 3) / (3 * intervalR*i) + T << '\n';
    }
    out.close();
}

void createPlotFile(string data_file) //Creates output file for GnuPlot.
{
    ofstream out;
    out.open("plot.plt");
    out << "set encoding utf8" << '\n' << "set xlabel " << '"' << "{/Symbol f}" << '"' << '\n' << "set yrange[10:70]"<< '\n' << "set xrange[0:0.02]"<< '\n'<< "set ylabel " << '"' << "A" << '"' << '\n' << "set title " << '"' << "" << '"' << '\n' << "unset key" << '\n' << "plot '" << data_file << "' w l lw 2 title " << '"' << "E({/Symbol q})" << '"' << ", 0 lw 1 title " << '"' << '"' << '\n' << "pause mouse";
    //set yrange[10:70]
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
