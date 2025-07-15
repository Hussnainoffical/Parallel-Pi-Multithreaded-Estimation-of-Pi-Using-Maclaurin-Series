#include <iostream>
#include <cmath>

using namespace std;

int main() 
{
    int n = 100000; // value of n
    double pi = 0.0;

    cout << "n: " << n << "\n";
    
    for (int i = 0; i < n; ++i) 
    {
        double term;
        if (i % 2 == 0)
        {
            term = 1.0 / (2 * i + 1);
        }
        else
        {
            term = -1.0 / (2 * i + 1);
        }
        pi += term;
    }

    pi *= 4;
    cout << "Value of pi: " << pi << "\n";

    return 0;
}
