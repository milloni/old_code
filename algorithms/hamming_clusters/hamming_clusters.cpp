#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

void flipBit(string *str, int index)
{
    if ((*str)[index] == '1') {
        (*str)[index] = '0';
    } else {
        (*str)[index] = '1';
    }
}

void unionFind(const vector<string>& nodes)
{
    
}

int getClusterCount(const vector<string>& nodes, int bitCount)
{
    unordered_map<string, int> verticesByCode;
    for (int i = 0; i < static_cast<int>(nodes.size()); i++) {
        verticesByCode[nodes[i]] = vertex;
    }

    vector<int> clusterSizes(nodes.size(), 0);
    for (int i = 0; i < static_cast<int>(nodes.size()); i++) {
        
    }
    
    for (int i = 0; i < static_cast<int>(nodes.size()); i++) {
        string compString(nodes[i]);
        for (int j = 0; j < bitCount; j++) {
            if (j != 0) {
                flipBit(&compString, j - 1);
            }
            flipBit(&compString, j);

            int cluster = verticesByCode[nodes[i]];
            int addCluster = verticesByCode[compString];
            for (int k = 0; k < static_cast<int>(nodes.size()); k++) {
                if (verticesByCode[nodes[k]] == addCluster) {
                    verticesByCode[nodes[k]] = cluster;
                }
            }
        }
    }

    return 666;
}

int main()
{
    int nodeCount;
    cin >> nodeCount;
    int bitCount;
    cin >> bitCount;
    vector<string> nodes;
    for (int i = 0; i < nodeCount; i++) {
        string node(bitCount, '\0');
        for (int j = 0; j < bitCount; j++) {
            cin >> node[j];
        }
        nodes.push_back(node);
    }

    cout << getClusterCount(nodes, bitCount) << endl;
    return 0;
}
