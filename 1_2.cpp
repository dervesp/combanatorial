#include <iostream>
#include "combinatorial/combination.h"

using namespace std;

void PrintCombination(Combination const & combination)
{
    for (auto index : combination.getCombination())
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

    Combination combination = Combination(n, k);
    do
    {
        if (useOutput)
        {
            PrintCombination(combination);
        }
    }
    while (combination.next());
    return 0;
}