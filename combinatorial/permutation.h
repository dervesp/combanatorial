#ifndef COMBANATORIAL_PERMUTATION_H
#define COMBANATORIAL_PERMUTATION_H

#include <c++/cstddef>
#include <vector>

struct Permutation
{
    unsigned _n;
    unsigned _m;
    std::vector<unsigned> _permutation;
    std::vector<unsigned> _reverse;
    std::vector<unsigned> _direction;

    Permutation(unsigned n)
    {
        _n = n;
        _permutation = std::vector<unsigned>(_n, 0);
        _reverse = std::vector<unsigned>(_n, 0);
        for (auto i = 0; i < _n; ++i)
        {
            _permutation[i] = i + 1;
            _reverse[i] = i + 1;
        }
        _permutation.push_back(_n + 1);
        _permutation.insert(_permutation.begin(), _n + 1);

        _direction = std::vector<unsigned>(_n, -1);
        _direction[0] = 0;
    }

    bool next()
    {
        _iterate();
        if (_m == 1)
        {
            return false;
        }
        return true;
    }

    const std::vector<unsigned> getPermutation() const
    {
        return std::vector<unsigned>(_permutation.begin() + 1, _permutation.end() - 1);
    }

    void _iterate()
    {
        _m = _n;
        while (_permutation[_reverse[_m - 1] + _direction[_m - 1]] > _m)
        {
            _direction[_m - 1] *= -1;
            --_m;
        }

        std::swap(_permutation[_reverse[_m - 1]], _permutation[_reverse[_m - 1] + _direction[_m - 1]]);
        std::swap(_reverse[_permutation[_reverse[_m - 1]] - 1], _reverse[_m - 1]);
    }
};

#endif //COMBANATORIAL_PERMUTATION_H
