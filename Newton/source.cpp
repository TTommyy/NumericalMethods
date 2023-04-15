// Tomasz Koczar

#include <cstdio>
#include <cmath>
#include <climits>
#include <algorithm>
#include <iostream>

using std::cout;

template <int N>
double norm(double* x)
{
    double sum;
    for (int i = 0; i< N; i++)
    {
        sum += std::abs(x[i]);
    }
    return sum;
}

template<int N>
double maxNorm(double* x)
{
    double max = std::abs(x[0]);
    for (int i = 1; i< N; i++)
    {
        double abs =  std::abs(x[i]);
        if (abs > max)
        {
            max = abs;
        }
    }
    return max;
}

typedef void (*FuncPointer)(const double* x, double* y, double* Df);

void printVector(const double* x, unsigned N){
  for(unsigned i=0; i<N; ++i)
    printf("%17.17f ",x[i]);
  printf("\n");
}

typedef void (*FuncPointer)(const double* x, double* y, double* Df);

int findCurve(FuncPointer f, double* x, unsigned k, double h)
{
    const static int NO_ERROR = 0;
    const static int VECTOR_SIZE = 3;
    const double TOLERANCE = 10e-14;

    bool done = false;

    double x0 = x[0], x1 = x[1];
    double y[2], Df[6], h1, h2, det;
    double px[2], len[2];
    for (unsigned i = 1; i <= k; i++)
    {
        done = false;
        x[0] = x0, x[1] = x1;
        x[2] += h;
        do
        {
            px[0] = x[0];
            px[1] = x[1];

            f(x, y, Df);

            det = (Df[0] * Df[4]) - (Df[1] * Df[3]);
            // F'(X) * H == -F(X)
            // Metoda Crammera
            h1 = ( (Df[4] * -y[0]) - (Df[1] * -y[1])) / det;
            h2 = ( (-Df[3] * -y[0]) + (Df[0] * -y[1])) / det;

            // X++ == H + X
            x[0] += h1;
            x[1] += h2;

            if (std::max(std::abs(y[0]), std::abs(y[1])) < TOLERANCE)
            {
                done = true;
                break;
            }
            len[0] = x[0] - px[0];
            len[1] = x[1] - px[1];
        }while (norm<2>(len) < 10);
        if (!done)
        {
            return i;
        }
        printVector(x, VECTOR_SIZE);
    }
    return NO_ERROR;
}

int findSurface(FuncPointer f, double* x, unsigned k1, unsigned k2, double h1, double h2)
{
    const static int NO_ERROR = 0;
    const static int VECTOR_SIZE = 3;
    const double TOLERANCE = 10e-14;

    bool done = false;

    double x0 = x[0], x2 = x[2];
    double y[2], Df[6], h;
    double px;
    for (unsigned i = 1; i <= k1; i++)
    {
        x[1] += h1;
        x[2] = x2;
        for( unsigned j = 1; j <= k2; j++)
        {
            done = false;
            x[0] = x0;
            x[2] += h2;
            do
            {
                f(x, y, Df);

                // x++ = x - f/f'
                h = y[0]/Df[0];
                x[0] -= h;

                if (std::abs(y[0]) < TOLERANCE)
                {
                    done = true;
                    break;
                }
            }while (std::abs(px - x[0]) < 10);
            if (!done)
            {
                return i * k1 + j;
            }
            printVector(x, VECTOR_SIZE);
        }
        cout << "\n";
    }
    return NO_ERROR;
}

int findFixedPoints(FuncPointer f, double* x, unsigned k1, unsigned k2, double h1, double h2)
{
    const static int NO_ERROR = 0;
    const static int VECTOR_SIZE = 4;
    const double TOLERANCE = 10e-14;

    bool done = false;

    double x0 = x[0], x1 = x[1], x2 = x[2], x3 = x[3];

    double y[2], Df[8], hh1, hh2, det;
    double px[2], len[2];
    for (unsigned i = 1; i <= k1; i++)
    {
        x[2] += h1;
        x[3] = x3;
        for( unsigned j = 1; j <= k2; j++)
        {
            done = false;
            x[0] = x0;
            x[1] = x1;
            x[3] += h2;
            do
            {
                px[0] = x[0];
                px[1] = x[1];

                f(x, y, Df);

                y[0] -= x[0];
                y[1] -= x[1];

                if (maxNorm<2>(y) <= TOLERANCE)
                {
                    done = true;
                    break;
                }

                Df[0] -= 1;
                Df[5] -= 1;

                det = (Df[0] * Df[5]) - (Df[1] * Df[4]);
                // F'(X) * H == F(X) - X
                // Metoda Crammera
                hh1 = ( (Df[5] *  -y[0] ) - ( Df[1] * -y[1] )) / det;
                hh2 = ( (-Df[4] * -y[0] ) + ( Df[0] * -y[1] )) / det;

                // X++ == H + X
                x[0] += hh1;
                x[1] += hh2;


                len[0] = x[0] - px[0];
                len[1] = x[1] - px[1];
        }while (norm<2>(len) < 1);
        if (!done)
        {
            return i * k1 + j;
        }
        printVector(x, VECTOR_SIZE);
        }
        cout << "\n";
    }
    return NO_ERROR;
}