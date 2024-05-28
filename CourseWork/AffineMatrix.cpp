#include <algorithm>
#include <vector>
#include <stdio.h>
#include <iostream>
#include "AffineMatrix.h"

void AffineMatrix::scale(double scalar) {
    /*auto scale = [&](const double x)
        {
            return scalar * x;
        };
    for (std::vector<double> row : mat) {
        std::transform(row.begin(), row.end(), row, scale);
    }*/
}

AffineMatrix AffineMatrix::add(AffineMatrix m) {
    std::vector<std::vector<double>> newMat{
        {atPos(0, 0) + m.atPos(0, 0), atPos(0, 1) + m.atPos(0, 1), atPos(0, 2) + m.atPos(0, 2), atPos(0, 3) + m.atPos(0, 3)},
        {atPos(1, 0) + m.atPos(1, 0), atPos(1, 1) + m.atPos(1, 1), atPos(1, 2) + m.atPos(1, 2), atPos(1, 3) + m.atPos(1, 3)},
        {atPos(2, 0) + m.atPos(2, 0), atPos(2, 1) + m.atPos(2, 1), atPos(2, 2) + m.atPos(2, 2), atPos(2, 3) + m.atPos(2, 3)},
        {atPos(3, 0) + m.atPos(3, 0), atPos(3, 1) + m.atPos(3, 1), atPos(3, 2) + m.atPos(3, 2), atPos(3, 3) + m.atPos(3, 3)}
    };
    return AffineMatrix(newMat);
}

AffineMatrix AffineMatrix::multiply(AffineMatrix m) {
    std::vector<std::vector<double>> newMat;
    for (int i = 0; i < 4; i++) {
        std::vector<double> temp;
        for (int j = 0; j < 4; j++) {
            double n = 0;
            for (int k = 0; k < 4; k++) {
                n += atPos(i, k) * m.atPos(k, j);
            }
            temp.push_back(n);
        }
        newMat.push_back(temp);
    }
    return AffineMatrix(newMat);
}

AffineMatrix AffineMatrix::inverse() {
    std::vector<std::vector<double>> newMat;
    auto invf = [](int i, int j, const double* m) {
        int o = 2 + (j - i);
        i += 4 + o;
        j += 4 - o;
        #define e(a,b) m[((j+b)%4)*4 + ((i+a)%4)]
        float inv =
            e(1, -1) * e(0, 0) * e(-1, 1) +
            e(1, 1) * e(0, 1) * e(1, 0) +
            e(-1, -1) * e(1, 0) * e(0, 1) -
            e(-1, -1) * e(0, 0) * e(1, 1) -
            e(-1, 1) * e(0, -1) * e(1, 0) -
            e(1, -1) * e(-1, 0) * e(0, 1);
        return (o % 2) ? inv : -inv;
        #undef e
        };
    auto inverse = [invf](const double* m, double* out) {
        float inv[16];
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                inv[j * 4 + i] = invf(i, j, m);
            }
        }
        double D = 0;
        for (int k = 0; k < 4; k++) {
            D += m[k] * inv[k * 4];
        }
        if (D == 0) {
            return false;
        }
        D = 1.0 / D;
        for (int i = 0; i < 16; i++) {
            out[i] = inv[i] * D;
        }
        return true;
        };
    double m[16], inv[16];
    for (int i = 0, n = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat.at(i).size(); j++, n++) {
            m[n] = mat.at(i).at(j);
        }
    }
    if (inverse(&m[0], &inv[0]) == false) {
        throw std::runtime_error("Affine matrix has determinant of 0, cannot invert");
    }
    for (int i = 0, n = 0; i < mat.size(); i++) {
        std::vector<double> temp;
        for (int j = 0; j < mat.at(i).size(); j++, n++) {
            temp.push_back(inv[n]);
        }
        newMat.push_back(temp);
    }
    return AffineMatrix(newMat);
}

double AffineMatrix::atPos(int r, int c) {
    return mat.at(r).at(c);
}

void AffineMatrix::print() {
    for (std::vector<double> row : mat) {
        for (double col : row) {
            std::cout << col << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}