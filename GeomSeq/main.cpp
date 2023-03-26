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

inline void extract(const float product, const float sum, std::ostream& o)
{
    if (product == 0.0)
    {
        invalid(o);
        return;
    }
    //o << "Input: " << product << " " << sum << "\n";
    const float x2 = cbrtf(product);
    //o << "x2 : " << x2 << "\n";
    const float K = (sum / x2) - 1.0;
    //o << "K : "  << K << "\n";
    if (fabs(K) < 2.0)
    {
        invalid(o);
        return;
    }


    const float sqrtK = sqrtf(fabs(K-2)) * sqrtf(fabs(K+2));

    float q = (K/ 2.0)  - (sqrtK / 2.0);
    if (fabs(q) < 1.0f)
    {
        q = (K + sqrtK) / 2.0;
    }
    float x1 = x2 / q;
    float x3 = x2 * q;

    print(x1, x2, x3, o);

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