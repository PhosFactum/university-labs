#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <limits>
#include <queue>

#define MAX_W 100

const int inf = std::numeric_limits<int>::max();

std::vector<std::vector<int>> genGraph(int n, int v)
{
    std::vector<std::vector<int>> matrixGraph(n, std::vector<int>(n, inf));
    std::vector<bool> used(n, false);
    std::queue<int> next;
    next.push(0);
    int unused_n = n - 1;
    int unused_v = v;

    while (unused_n > 0)
    {
        int amountOfV = rand() % (v / n) + 1;
        int cur_src = next.front();
        next.pop();

        for (int i = 0; i < amountOfV && unused_n > 0; i++) 
        {
            int w = rand() % MAX_W + 1;
            matrixGraph[cur_src][unused_n] = w;
            matrixGraph[unused_n][cur_src] = w;
            next.push(unused_n);
            unused_n--;
            unused_v--;
        }
    }

    while (unused_v > 0) 
    {
        int src = rand() % n;
        int dest = rand() % n;

        if (src == dest || matrixGraph[src][dest] != inf) 
        {
            continue;
        }

        int w = rand() % MAX_W + 1;
        matrixGraph[src][dest] = w;
        matrixGraph[dest][src] = w;
        unused_v--;
    }

    return matrixGraph;
}

std::vector<int> leader;

int getLeader(int x)
{
    if (x == leader[x]) 
    {
        return x;
    }

    return leader[x] = getLeader(leader[x]);
}

bool unite(int x, int y)
{
    x = getLeader(x);
    y = getLeader(y);

    if (x == y) 
    {
        return false;
    }
        
    if (rand() % 2 == 0) 
    {
        std::swap(x, y);
    }

    leader[x] = y;
    return true;
}

std::vector<int> bellman_ford(const std::vector<std::vector<int>>& graph, int source) {
    int n = graph.size();
    std::vector<int> dist(n, inf);
    dist[source] = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                if (graph[u][v] != inf && dist[u] != inf && dist[v] > dist[u] + graph[u][v]) {
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }
    }

    return dist;
}

std::vector<std::vector<int>> floyd_warshall(const std::vector<std::vector<int>>& graph) {
    int n = graph.size();
    std::vector<std::vector<int>> dist(n, std::vector<int>(n, inf));

    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (graph[u][v] != inf) {
                dist[u][v] = graph[u][v];
            }
        }
    }

    for (int k = 0; k < n; k++) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                if (dist[u][k] != inf && dist[k][v] != inf && dist[u][v] > dist[u][k] + dist[k][v]) {
                    dist[u][v] = dist[u][k] + dist[k][v];
                }
            }
        }
    }

    return dist;
}


int main() 
{
    // {10,12},{20,25},{30,37},{40,50},{50,62},{60,75},{70,87},{80,100},{90,112},{100,125}
    srand(static_cast<unsigned int>(time(NULL)));
    char c = ' ';

    while (c != 'q')
    {   
        int r = 0;
        std::cout << "Iterations:" << std::endl;
        std::cin >> r;
        int n = 0;
        std::cout << "Vertex count:" << std::endl;
        std::cin >> n;
        int m = 0;
        std::cout << "Edges count:" << std::endl;
        std::cin >> m;

        double time_f1_sum = 0, time_f2_sum = 0;

        for (int k = 0; k < r; k++)
        {
            std::vector<std::vector<int>> matGraph = genGraph(n, m);
            clock_t start = clock();
            bellman_ford(matGraph, 0);
            clock_t end = clock();
            double seconds = (double)(end - start) / CLOCKS_PER_SEC;
            time_f1_sum += seconds;

            matGraph = genGraph(n, m);
            start = clock();
            floyd_warshall(matGraph);
            end = clock();
            seconds = (double)(end - start) / CLOCKS_PER_SEC;
            time_f2_sum += seconds;
        }
        
        double time_1 = time_f1_sum / (double)r;
        std::cout << "The time (bellman_ford): " << time_1 << " seconds" << std::endl;
        double time_2 = time_f2_sum / (double)r;
        std::cout << "The time (floyd-warshall): " << time_2 << " seconds" << std::endl;

        std::cout << "Enter any char to continue; enter 'q' to exit." << std::endl;
        std::cin >> c;
    }

    return 0;
}