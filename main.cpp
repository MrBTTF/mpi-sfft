#include <iostream>
#include <vector>
#include <complex>
#include <fstream>

#include "AudioProcessing.h"

using namespace std;

void readInput(string filename, vector<complex<float>> &result)
{
    ifstream f(filename);

    if (!f)
    {
        cout << filename << " is not open!" << endl;
        return;
    }

    while (!f.eof())
    {
        complex<float> sample;
        f >> sample;
        result.push_back(sample);
    }

    f.close();
}

void writeOutput(string filename, const vector<complex<float>> &output)
{
    ofstream f(filename);

    if (!f)
    {
        cout << filename << " is not open!" << endl;
        return;
    }


    for (auto it=output.begin(); it != output.end(); it++)
    {
        f << fixed << it->real() << ((it->imag()>=0) ? "+" : "")  << it->imag() << "j\n";
    }

    f.close();
}


int main()
{
    vector<complex<float>> input;
    readInput("input.txt", input);

    vector<complex<float>> output = FFT(input);

    writeOutput("output.txt", output);

    return 0;
}