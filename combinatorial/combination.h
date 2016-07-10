#ifndef COMBANATORIAL_COMBINATION_H
#define COMBANATORIAL_COMBINATION_H

#include <c++/cstddef>
#include <vector>

struct Combination
{
    unsigned _n;
    unsigned _k;
    std::vector<unsigned> _combination;

    Combination(unsigned n, unsigned k)
    {
        _n = n;
        _k = k;
        _combination = std::vector<unsigned>(_k, 0);
        _populate(0, 1);
    }

    bool next()
    {
        if (_combination[0] > (_n - _k))
        {
            return false;
        }
        _increment(_k - 1);
        return true;
    }

    const std::vector<unsigned> getCombination() const
    {
        return _combination;
    }

    void _populate(size_t startIndex, unsigned value)
    {
        for (auto i = startIndex; i < _k; ++i)
        {
            _combination[i] = value;
            ++value;
        }
    }

    void _increment(size_t index)
    {
        ++_combination[index];
        if (_combination[index] > _n - _k + index + 1)
        {
            _increment(index - 1);
            if (_combination[index - 1] <= (_n - _k + index))
            {
                _populate(index - 1, _combination[index - 1]);
            }
        }
    }
};

#endif //COMBANATORIAL_COMBINATION_H
