#include <c++/cstddef>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct Graph
{
    vector<vector<int>> _vert;
    vector<bool> _marked;
    vector<int> result;

    Graph(int maxVert)
    {
        for (int i = 0; i < maxVert; ++i)
        {
            _vert.push_back(vector<int>());
            _marked.push_back(false);
            result.push_back(-1);
        }
    }

    void addEdge(int v1, int v2)
    {
        _vert[v1].push_back(v2);
    }

    void process()
    {
        for (int i = 0; i < _vert.size(); ++i)
        {
            _marked = vector<bool>(_vert.size(), false);
            _recursiveKuhn(i);
        }
    }

    bool _recursiveKuhn(int vert)
    {
        if (!_marked[vert])
        {
            _marked[vert] = true;
            for (int i = 0; i < _vert[vert].size(); ++i)
            {
                int nextVert = _vert[vert][i];
                if ((result[nextVert] == -1) || _recursiveKuhn(result[nextVert]))
                {
                    result[nextVert] = vert;
                    return true;
                }
            }
        }
        return false;
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
    int leftVertNum, rightVertNum;
    if (!(sstream >> leftVertNum >> rightVertNum))
    {
        cout << "wrong input format" << endl;
        return 1;
    }
    if (leftVertNum != rightVertNum)
    {
        cout << "no" << endl;
        return 0;
    }

    Graph graph = Graph(leftVertNum);
    for (int i = 0; i < leftVertNum; ++i)
    {
        if (!getline(cin, line))
        {
            cout << "wrong input format" << endl;
            return 1;
        }
        istringstream sstream2(line);
        for (int j = 0; j < leftVertNum; j++)
        {
            int edgeWeight;
            if (!(sstream2 >> edgeWeight))
            {
                cout << "wrong input format" << endl;
                return 1;
            }
            else
            {
                if (edgeWeight > 0)
                {
                    graph.addEdge(i, j);
                }
            }
        }
    }

    graph.process();

    bool noPair = false;
    for (int i = 0; i < graph.result.size(); ++i)
    {
        if (graph.result[i] == -1)
        {
            noPair = true;
            break;
        }
    }
    if (noPair)
    {
        cout << "no" << endl;
    }
    else
    {
        cout << "yes" << endl;
    }
    for (int i = 0; i < graph.result.size(); ++i)
    {
        cout << i << " " << graph.result[i] << endl;
    }

    return 0;
}