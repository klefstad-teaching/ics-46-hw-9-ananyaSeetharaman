#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>
#include "dijkstras.h"

using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous)
{
    int n = G.numVertices;
    vector<int> distance(n, INF);
    previous.assign(n, -1);
    vector<bool> visited(n, false);

    struct Node
    {
        int vertex;
        int weight;
        Node(int v, int w) : vertex(v), weight(w) {}

        bool operator>(const Node &other) const 
        {
            return weight > other.weight;
        }
    }

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    distance[source] = 0;
    pq.push(Node(source, 0));

    while(!pq.empty())
    {
        Node curr = pq.top();
        pq.pop();
        int u = curr.vertex;

        if(visited[u]) {continue;}
        visited[u] = true;

        for (const Edge &edge : G[u])
        {
            int v = edge.dst;
            int weight = edge.weight;
            if (!visited[u] && distance[u] + weight < distance[v])
            {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push(Node(v, distance[v]));
            }
        }
    }
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination)
{
    vector<int> path;
    if(distances[destination] == INF)
    {
        return path;
    }

    int curr = destination;
    while (curr != -1)
    {
        path.push_back(curr);
        curr = previous[curr];
    }
    reverse(path.begin(), path,end());
    return path;
}

void print_path(const vector<int>& v, int total)
{
    if (path.empty())
    {
        cout << "No path exists." << endl;
        return;
    }

    for (size_t i = 0; i < path.size(), ++i)
    {
        cout << path[i];
        if (i < path.size() - 1)
        {
            cout << " -> ";
        }
    }
    cout << " (cost: " << total << ")" << endl;
}