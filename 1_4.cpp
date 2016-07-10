#include <c++/cstddef>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void PrintRandomPermutation(const vector<unsigned> & randomPermutation)
{
    for (auto index : randomPermutation)
    {
        cout << to_string(index) << " ";
    }
    cout << endl;
}

vector<unsigned> getRandomPermutation(unsigned n)
{
    vector<unsigned> permutation = vector<unsigned>(n, 0);
    for (auto i = 0; i < permutation.size(); ++i)
    {
        permutation[i] = i;
    }
    std::random_shuffle(permutation.begin(), permutation.end());
}

int main(int argc, char * argv[]) {
    if (argc < 2)
    {
        cout << "Usage: <n> [<output>]" << endl;
        return 1;
    }
    int n = stoi(argv[1]);
    bool useOutput = (argc > 2);

    vector<unsigned> randomPermutation = getRandomPermutation(n);
    if (useOutput)
    {
        PrintRandomPermutation(randomPermutation);
    }
    return 0;
}