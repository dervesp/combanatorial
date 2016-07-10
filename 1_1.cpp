#include <iostream>
#include "combinatorial/permutation.h"

using namespace std;

void PrintPermutation(Permutation const & permutation)
{
    for (auto index : permutation.getPermutation())
    {
        cout << to_string(index) << " ";
    }
    cout << endl;
}

int main(int argc, char * argv[]) {
    if (argc < 2)
    {
        cout << "Usage: <n> [<output>]" << endl;
        return 1;
    }
    int n = stoi(argv[1]);
    bool useOutput = (argc > 2);

    Permutation permutation = Permutation(n);
    do
    {
        if (useOutput)
        {
            PrintPermutation(permutation);
        }
    }
    while (permutation.next());
    return 0;
}