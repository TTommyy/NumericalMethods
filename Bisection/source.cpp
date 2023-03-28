// Tomasz Koczar

#include <cmath>

double secant(
    double (*f)(double),
    const double a,
    const double b,
    const int M,
    const double eps,
    const double delta)
{
    double x0 = a;
    double x1 = b;
    double x2;
    double len;
    double fx0 = f(x0);
    double fx1;
    for (int i = 0; i < M; i++)
    {
        fx1 = f(x1);
        if (std::abs(fx1) <= eps)
        {
            return x1;
        }

        x2 = x1 - fx1 * ((x1 - x0) / (fx1 - fx0));
        len = std::abs(x2 - x1);
        if (len <= delta)
        {
            return x2;
        }

        x0 = x1;
        x1 = x2;
        fx0 = fx1;
    }
    return x2;
}

double bisect(
    double (*f)(double),
    const double a0,
    const double b0,
    const int M,
    const double eps,
    const double delta)
{
    double a = a0;
    double b = b0;
    double len;
    double c;
    double fa;
    double fc;
    for (int i = 0; i < M; i++)
    {
        len = (b - a) / 2;
        c = (a + b) / 2;
        if (len <= delta)
        {
            return c;
        }

        fc = f(c);
        if (std::abs(fc) <= eps)
        {
            return c;
        }

        if (fc * fa > 0)
        {
            a = c;
            fa = fc;
        }
        else
        {
            b = c;
        }
    }
    return c;
}

double findZero(
    double (*f)(double),
    double a,
    double b,
    int M,
    double eps,
    double delta)
{
    const double fa = f(a);
    const double fb = f(b);
    M = M - 2;
    if (fa * fb > 0)
    {
        return secant(f, a, b, M, eps, delta);
    }
    return bisect(f, a, b, M, eps, delta);
}