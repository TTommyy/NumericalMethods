#include "vectalg.h"
#include <cmath>
#include <algorithm>



void swapRows(Matrix& A, int first, int second)
{
    const auto size = A.size();
    Vector temp(size);
    for (int i = 0; i < size; ++i)
    {
        temp[i] = A(first, i);
    }

    for (int i = 0; i < size; ++i)
    {
        A(first, i) = A(second, i);
    }
     for (int i = 0; i < size; ++i)
    {
        A(second, i) = temp[i];
    }
}

Vector solveEquations(const Matrix & A, const Vector & b, double eps)
{
    int n = A.size();
    Matrix a(A);
    Vector x(b);

    // Compute scale factors
    Vector scale(n);
    for (int i = 0; i < n; ++i)
    {
        double max_row = 0.0;
        for (int j = 0; j < n; ++j)
        {
            max_row = std::max(max_row, std::abs(a(i, j)));
        }
        scale[i] = max_row;
    }

    // Forward elimination
    for (int k = 0; k < n - 1; ++k)
    {
        // Scaled partial pivoting
        int max_index = k;
        double max_value = std::abs(a(k, k) / scale[k]);
        for (int i = k + 1; i < n; ++i)
        {
            double value = std::abs(a(i, k) / scale[i]);
            if (value > max_value)
            {
                max_index = i;
                max_value = value;
            }
        }
        if (max_index != k)
        {
            swapRows(a, k, max_index);
            std::swap(x[k], x[max_index]);
            std::swap(scale[k], scale[max_index]);
        }

        // Elimination
        for (int i = k + 1; i < n; ++i)
        {
            double factor = a(i, k) / a(k, k);
            for (int j = k + 1; j < n; ++j)
            {
                a(i, j) -= factor * a(k, j);
            }
            x[i] -= factor * x[k];
        }
    }

    // Backward substitution
    for (int i = n - 1; i >= 0; --i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            x[i] -= a(i, j) * x[j];
        }
        x[i] /= a(i, i);
    }

    // Iterative refinement
    Vector r(n);
    while (true) {
        // Compute residual
        for (int i = 0; i < n; ++i)
        {
            r[i] = b[i];
            for (int j = 0; j < n; ++j)
                r[i] -= A(i, j) * x[j];
        }

        // Check convergence
        double error = 0.0;
        for (int i = 0; i < n; ++i)
        {
            error = std::max(error, std::abs(r[i]));
        }
        if (error <= eps)
            break;

        // Solve for error
        a = A;
        for (int k = 0; k < n - 1; ++k)
        {
            for (int i = k + 1; i < n; ++i)
            {
                double factor = a(i, k) / a(k, k);
                for (int j = k + 1; j < n; ++j)
                {
                    a(i, j) -= factor * a(k, j);
                }
                r[i] -= factor * r[k];
            }
        }
        for (int i = n - 1; i >= 0; --i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                r[i] -= a(i, j) * r[j];

            }
            r[i] /= a(i, i);
        }

        // Update solution
        for (int i = 0; i < n; ++i)
        {
            x[i] += r[i];
        }
    }

    return x;
}