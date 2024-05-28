#pragma once
#include <vector>
#include <cmath>

class AffineMatrix {
private:
    std::vector<std::vector<double>> mat;
public:
    AffineMatrix() {
        std::vector<std::vector<double>> m{
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
        };
        mat = m;
    }
    AffineMatrix(std::vector<std::vector<double>> m) {
        mat = m;
    }
    //modes: (s)calar, rotations: (x), (y), (z)
    AffineMatrix(double num, char mode) {
        switch (mode) {
        case 's':
        {
            std::vector<std::vector<double>> m{
                {num, 0, 0, 0},
                {0, num, 0, 0},
                {0, 0, num, 0},
                {0, 0, 0, 1}
            };
            mat = m;
            break;
        }
        case 'x':
        {
            std::vector<std::vector<double>> m{
                {1, 0, 0, 0},
                {0, cos(num), sin(num), 0},
                {0, -sin(num), cos(num), 0},
                {0, 0, 0, 1}
            };
            mat = m;
            break;
        }
        case 'y':
        {
            std::vector<std::vector<double>> m{
                {cos(num), 0, -sin(num), 0},
                {0, 1, 0, 0},
                {sin(num), 0, cos(num), 0},
                {0, 0, 0, 1}
            };
            mat = m;
            break;
        }
        case 'z':
        {
            std::vector<std::vector<double>> m{
                {cos(num), -sin(num), 0, 0},
                {sin(num), cos(num), 0, 0},
                {0, 0, 1, 0},
                {0, 0, 0, 1}
            };
            mat = m;
            break;
        }
        }
    }
    //{x, y, z}
    AffineMatrix(double x, double y, double z) {
        std::vector<std::vector<double>> m{
            {1, 0, 0, x},
            {0, 1, 0, y},
            {0, 0, 1, z},
            {0, 0, 0, 1}
        };
        mat = m;
    }
    virtual void scale(double scalar);
    virtual AffineMatrix add(AffineMatrix m);
    virtual AffineMatrix multiply(AffineMatrix m);
    virtual AffineMatrix inverse();
    virtual double atPos(int r, int c);
    virtual void print();
};