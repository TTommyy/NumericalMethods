// Tomasz Koczar

#include <cmath>

const double BOUND = 0.001;
const double FORCE_SWITCH = 0.8;
const double DIVIDER = 10.0;

double secant(
    double (*f)(double),
    const double a,
    const double b,
    const double fa,
    const int M,
    const double eps,
    const double delta)
{
    double x0 = a;
    double x1 = b;
    double x2;
    double len;
    double fx0 = fa;
    double fx1;

    for (int i = 0; i < M ; i++)
    {
        fx1 = f(x1);
        if (std::abs(fx1) <= eps)
        {
            return x1;
        }

        x2 = x1 - fx1 * (x1 - x0) / (fx1 - fx0);

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
    const double fa0,
    const int M,
    const double eps,
    const double delta)
{
    double a = a0;
    double b = b0;
    double c;
    double len;
    double fa = fa0;
    double fc;

    int Mbi = M * FORCE_SWITCH;
    int Msec = M - Mbi;

    for (int i = 0; i < Mbi; i++)
    {
        c = (a + b) / 2;

        len = (b - a) / 2;
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

        if (std::abs(fc) <= BOUND)
        {
            return secant(f, a, b, fa, M - i - 1, eps, delta);
        }
    }
    return secant(f, a, b, fa, Msec, eps, delta);
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

    if (std::abs(fa) <= eps)
    {
        return a;
    }
    if (std::abs(fb) <= eps)
    {
        return b;
    }

    if (fa * fb > 0)
    {
        return secant(f, a, b, fa, M, eps/DIVIDER, delta/DIVIDER);
    }
    return bisect(f, a, b, fa, M, eps/DIVIDER, delta/DIVIDER);
}