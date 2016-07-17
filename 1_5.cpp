#include <c++/cstddef>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;
struct Item
{
    unsigned weigth;
    unsigned cost;
    bool active;
};

struct Backpack
{
    unsigned _weightLimit;
    vector<Item> _items;
    string _maxComposition;
    unsigned _maxWeight;
    unsigned _maxCost;

    Backpack(unsigned weightLimit)
    {
        _weightLimit = weightLimit;
        _items = vector<Item>();
    }

    void addItem(unsigned weight, unsigned cost)
    {
        Item item = {weight, cost, false};
        _items.push_back(item);
    }

    void process()
    {
        _maxWeight = 0;
        recursiveAdd(0);
    }

    void recursiveAdd(size_t index)
    {
        if (index < _items.size())
        {
            _items[index].active = false;
            recursiveAdd(index + 1);

            _items[index].active = true;
            recursiveAdd(index + 1);
        }
        else
        {
            unsigned weight = 0;
            unsigned cost = 0;
            bool overweight = false;
            ostringstream buffer;
            for (Item item: _items)
            {
                if (item.active)
                {
                    weight += item.weigth;
                    if (weight > _weightLimit)
                    {
                        overweight = true;
                        break;
                    }
                    cost += item.cost;
                    buffer << "1";
                }
                else
                {
                    buffer << "0";
                }
            }
            if (!overweight)
            {
                if (_maxCost < cost)
                {
                    _maxCost = cost;
                    _maxWeight = weight;
                    _maxComposition = buffer.str();
                }
            }
        }
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
    int itemNumber, weightLimit;
    if (!(sstream >> itemNumber >> weightLimit))
    {
        cout << "wrong input format" << endl;
        return 1;
    }

    Backpack backpack = Backpack(weightLimit);
    for (int i = 0; i < itemNumber; ++i)
    {
        if (!getline(cin, line))
        {
            cout << "wrong input format" << endl;
            return 1;
        }
        istringstream sstream2(line);
        unsigned weight, cost;
        while (sstream2 >> weight >> cost)
        {
            backpack.addItem(weight, cost);
        }
    }

    backpack.process();

    cout << backpack._maxCost << endl;
    cout << backpack._maxWeight << endl;
    cout << backpack._maxComposition << endl;

    return 0;
}