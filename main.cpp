#include <iostream>
#include <vector>
#include <complex>
#include <fstream>
#include <omp.h>
#include <chrono>

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
//
//    vector<complex<float>> output = FFT(input);
//
//    writeOutput("output.txt", output);

    vector<complex<float>> output;

    for (int i = 0; i < 4; i++)
    {
        omp_set_num_threads(pow(2,i));
        chrono::time_point<chrono::system_clock> start = chrono::system_clock::now(), end;

        output = FFT(input);

        end = chrono::system_clock::now();
        int elapsed = chrono::duration_cast<chrono::milliseconds>(end-start).count();
        cout << pow(2,i) << " threads:" << elapsed << endl;
    }

    writeOutput("output.txt", output);



    return 0;
}