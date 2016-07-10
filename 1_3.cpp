#include <iostream>
#include "combinatorial/variation.h"

using namespace std;

void PrintVariation(Variation const & variation)
{
    for (auto index : variation.getVariation())
    {
        cout << to_string(index) << " ";
    }
    cout << endl;
}

int main(int argc, char * argv[]) {
    if (argc < 3)
    {
        cout << "Usage: <n> <k> [<output>]" << endl;
        return 1;
    }
    int n = stoi(argv[1]);
    int k = stoi(argv[2]);
    bool useOutput = (argc > 3);

    Variation variation = Variation(n, k);
    do
    {
        if (useOutput)
        {
            PrintVariation(variation);
        }
    }
    while (variation.next());
    return 0;
}