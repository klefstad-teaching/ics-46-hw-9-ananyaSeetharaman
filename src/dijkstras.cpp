#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>

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

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination);
void print_path(const vector<int>& v, int total);