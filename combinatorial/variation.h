#ifndef COMBANATORIAL_VARIATION_H
#define COMBANATORIAL_VARIATION_H

#include <c++/cstddef>
#include <vector>
#include "combination.h"
#include "permutation.h"

struct Variation
{
    unsigned _n;
    unsigned _k;
    Combination _combination = Combination(1, 1);
    Permutation _permutation = Permutation(1);
    std::vector<unsigned> _variation;

    Variation(unsigned n, unsigned k)
    {
        _n = n;
        _k = k;
        _variation = std::vector<unsigned>(_k, 0);
        _combination = Combination(_n, _k);
        _permutation = Permutation(_k);
        _prepareVariation();
    }

    bool next()
    {
        bool hasPermutations, hasCombinations;

        hasPermutations = _permutation.next();
        if (hasPermutations)
        {
            _prepareVariation();
        }
        else
        {
            hasCombinations = _combination.next();
            if (hasCombinations)
            {
                _permutation = Permutation(_k);
                _prepareVariation();
            }
        }
        return (hasPermutations || hasCombinations);
    }

    const std::vector<unsigned> getVariation() const
    {
        return _variation;
    }

    bool _prepareVariation()
    {
        auto permutation = _permutation.getPermutation();
        auto combination = _combination.getCombination();
        for (auto i = 0; i < _k; ++i)
        {
            _variation[i] = combination[permutation[i] - 1];
        }
    }
};

#endif //COMBANATORIAL_VARIATION_H
