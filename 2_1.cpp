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
    vector<int> _timeIn;
    vector<int> _minTime;
    int _timer;

    vector<int> cutpoints;

    Graph(int maxVert)
    {
        for (int i = 0; i < maxVert; ++i)
        {
            _vert.push_back(vector<int>());
            _marked.push_back(false);
            _timeIn.push_back(10000);
            _minTime.push_back(10000);
        }
    }

    void addEdge(int v1, int v2)
    {
        _vert[v1].push_back(v2);
    }

    void process()
    {
        _timer = 0;
        cutpoints.clear();
        _recursiveDepthSearch(0);
    }

    void _recursiveDepthSearch(int vert, int parentVert = -1)
    {
        _marked[vert] = true;
        _timeIn[vert] = _timer;
        _minTime[vert] = _timer;
        ++_timer;

        int childVertCount = 0;
        for (auto i = 0; i < _vert[vert].size(); ++i)
        {
            int nextVert = _vert[vert][i];
            if (nextVert == parentVert)
            {
                continue;
            }
            if (_marked[nextVert])
            {
                _minTime[vert] = min(_minTime[vert], _timeIn[nextVert]);
            }
            else
            {
                _recursiveDepthSearch(nextVert, vert);
                _minTime[vert] = min(_minTime[vert], _minTime[nextVert]);
                if ((_minTime[nextVert] >= _timeIn[vert]) && (parentVert != -1))
                {
                    _processCutpoint(vert);
                }
                ++childVertCount;
            }
        }

        if (parentVert == -1 && childVertCount > 1)
        {
            _processCutpoint(vert);
        }

    }

    void _processCutpoint(int cutpount)
    {
        cutpoints.push_back(cutpount);
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
    int vertNumber;
    if (!(sstream >> vertNumber))
    {
        cout << "wrong input format" << endl;
        return 1;
    }

    Graph graph = Graph(vertNumber);
    for (int i = 0; i < vertNumber; ++i)
    {
        if (!getline(cin, line))
        {
            cout << "wrong input format" << endl;
            return 1;
        }
        istringstream sstream2(line);
        for (int j = 0; j < vertNumber; j++)
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
                graph.addEdge(i, j);
            }
        }
    }

    graph.process();

    cout << graph.cutpoints.size() << endl;
    for (int i = 0; i < graph.cutpoints.size(); ++i)
    {
        cout << graph.cutpoints[i] << " ";
    }
    cout << endl;

    return 0;
}