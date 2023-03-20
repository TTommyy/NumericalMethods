// Tomasz Koczar

#include <iostream>
#include <cmath>

using std::cout;
using std::cin;

inline void extract(const float product, const float sum, std::ostream& o)
{
    float x;
    float q;
    o << x << " " << x * q << " " << x * q * q << "\n";
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