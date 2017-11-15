
#pragma once

#include <vector>
#include <complex>


std::vector<std::complex<float>> FFT(std::vector<std::complex<float>> samples);

std::vector<unsigned short> inverseFFT(std::vector<std::complex<float>> samples);

