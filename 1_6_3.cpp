#include <c++/cstddef>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct Typography
{
    unsigned _tomeNum;
    vector<unsigned> _stories;

    Typography(unsigned tomeNum)
    {
        _tomeNum = tomeNum;
        _stories = vector<unsigned>();
    }

    void addStory(unsigned storySize)
    {
        _stories.push_back(storySize);
    }

    void process()
    {
        vector<unsigned> _permutation = vector<unsigned>(_stories.size() + _tomeNum - 1, 0);
        for (int i = 0; i < _stories.size(); ++i)
        {
            _permutation[i] = i + 1;
        }

        vector<vector<unsigned>> minTomes;
        unsigned minMaxTomeSize = 2050;
        do
        {
            auto tomes = _getTomesWithStories(_permutation);
            unsigned maxTomeSize = _calcMaxTomeSize(tomes);
            if (maxTomeSize < minMaxTomeSize)
            {
                minMaxTomeSize = maxTomeSize;
                minTomes = tomes;
            }
        }
        while(_next(_permutation));

        cout << minMaxTomeSize << endl;
        for (auto tome: minTomes)
        {
            for (auto index: tome)
            {
                cout << index << " [" << _stories[index] << "] ";
            }
            cout << endl;
        }
    }

    bool _next(vector<unsigned> & _permutation)
    {
        unsigned n = _permutation.size();
        unsigned m = n - 2;
        while ((m != -1) && (_permutation[m] >= _permutation[m + 1]))
        {
            m--;
        }
        if (m == -1)
        {
            return false;
        }
        int k = n - 1;
        while (_permutation[m] >= _permutation[k])
        {
            k--;
        }

        swap(_permutation[m],_permutation[k]);

        int l = m + 1;
        int r = n - 1;
        while (l < r)
        {
            swap(_permutation[l++], _permutation[r--]);
        }
        return true;
    }

    vector<vector<unsigned>> _getTomesWithStories(vector<unsigned> & _permutation)
    {
        vector<vector<unsigned>> tomes = vector<vector<unsigned>>();
        vector<unsigned> currentTome = vector<unsigned>();
        for (auto index: _permutation)
        {
            if (index == 0)
            {
                tomes.push_back(currentTome);
                currentTome = vector<unsigned>();
            }
            else
            {
                currentTome.push_back(index - 1);
            }
        }
        tomes.push_back(currentTome);
        return tomes;
    }

    unsigned _calcMaxTomeSize(vector<vector<unsigned>> & tomes)
    {
        unsigned maxSize = 0;
        for (auto tome: tomes)
        {
            unsigned size = 0;
            for (auto index: tome)
            {
                size += _stories[index];
            }
            maxSize = (size > maxSize) ? size : maxSize;
        }
        return maxSize;
    }
};

int main(int argc, char * argv[])
{
    string line;
    if (!getline(cin, line))
    {
        cout << "wrong input format" << endl;
        return 1;
    }
    istringstream sstream(line);
    int tomeNumber;
    if (!(sstream >> tomeNumber))
    {
        cout << "wrong input format" << endl;
        return 1;
    }
    Typography typography = Typography(tomeNumber);
    if (!getline(cin, line))
    {
        cout << "wrong input format" << endl;
        return 1;
    }
    istringstream sstream2(line);
    int storySize;
    while (sstream2 >> storySize)
    {
        typography.addStory(storySize);
    }

    typography.process();
    return 0;
}