#include <iostream>
#include "AudioProcessing.h"


using namespace std;


int reverse2(int a, int n)
{
    int ra = 0;
    for (int i = 0; i < log2(n); i++)
    {
        ra = ((ra << 1) + (a & 1));
        a >>= 1;
    }
    return ra;
}

vector<complex<float>> FFT(vector<complex<float>> samples)
{
    int n = (int) samples.size();
    vector <complex<float>> rsamples(n); //result

    //reverse
    #pragma omp parallel for
    for (int i = 0; i < samples.size(); i++)
    {
        rsamples.at(reverse2(i, n)) = samples.at(i);
    }

    for (int i = 1; i <= log2(n); i++)
    {
        int m = (int) pow(2, i);
        complex<float> wm = exp((const complex<float>) (-1i * 2 * M_PI / m));
        #pragma omp parallel for
        for (int j = 0; j < n; j += m)
        {
            complex<float> w = 1.f + 0i;
            #pragma omp parallel for
            for (int l = 0; l < m / 2; l++)
            {
                complex<float> t = w * rsamples.at(j + l + m / 2);
                complex<float> u = rsamples.at(j + l);
                rsamples.at(j + l) = u + t;
                rsamples.at(j + l + m / 2) = u - t;
                w *= wm;

            }
        }

    }

    //rsamples.resize(rsamples.size()/2);
    return rsamples;
}

vector<unsigned short> inverseFFT(vector<complex<float>> samples)
{
    int n = (int) samples.size();

    vector <complex<float>> rsamples(n);

    //reverse
    for (int i = 0; i < samples.size(); i++)
    {
        rsamples.at(reverse2(i, n)) = samples[i];
    }

    for (int i = 1; i <= log2(n); i++)
    {
        int m = (int) pow(2, i);
        complex<float> wm = exp((const complex<float>) (1i * 2 * M_PI / m));
        for (int j = 0; j < n; j += m)
        {
            complex<float> w = 1.f + 0i;
            for (int l = 0; l < m / 2; l++)
            {
                complex<float> t = w * rsamples[j + l + m / 2];
                complex<float> u = rsamples[j + l];
                rsamples[j + l] = u + t;
                rsamples[j + l + m / 2] = u - t;
                w *= wm;
            }
        }
    }
    vector<unsigned short> rshortsamples;
    for (size_t i = 0; i < rsamples.size(); i++)
    {
        rshortsamples.push_back(round(abs(rsamples[i]/(float)rsamples.size())));
    }
    return rshortsamples;
}


