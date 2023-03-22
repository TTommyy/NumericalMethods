// Tomasz Koczar

#include <iostream>
#include <cmath>

using std::cout;
using std::cin;
using std::abs;

inline void invalid(std::ostream& o)
{
    o << 0.0f << " " << 0.0f << " " << 0.0f << "\n";
}

inline void print(float x1, float x2, float x3, std::ostream& o)
{
    if( x1 <  x3)
    {
        float temp = x1;
        x1 = x3;
        x3 = temp;
    }
    o << x1 << " " << x2 << " " << x3 << "\n";
}

inline float K2_4(float K)
{
    return (K-2)*(K+2);
}

inline void extract(const float product, const float sum, std::ostream& o)
{
    //o << "Input: " << product << " " << sum << "\n";
    float q;
    const float x2 = cbrt(product);
    //o << "x2 : " << x2 << "\n";
    const float K = (sum - x2) / x2;
    //o << "K : "  << K << "\n";
    if (fabs(K) < 2.0f)
    {
        invalid(o);
        return;
    }


    const float sqrtK = sqrt(K2_4(K));

    q = (K - sqrtK)/2;
    if (fabs(q) < 1.0f)
    {
        q = (K + sqrtK)/2;
    }
    float x1 = x2 / q;
    float x3 = x2 * q;
    if (abs(x1 + x2 + x3 - sum) <= 0.0001f)
    {
        print(x1, x2, x3, o);
        return;
    }
    invalid(o);
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    cout.precision(10);
    cout << std::scientific;

    int NUBMER_OF_SEQ;
    cin >> NUBMER_OF_SEQ;

    float product, sum;

    for (int i = 0; i < NUBMER_OF_SEQ; i++)
    {
        cin >> product >> sum;
        extract(product, sum, cout);
    }
}