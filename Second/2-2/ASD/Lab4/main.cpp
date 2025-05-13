#include <iostream>
#include <vector>
#include <time.h>
#include <queue>
#include <algorithm>
#include <cstdlib>

#define MAX_W 100
#define C 100000

using namespace std;

struct edge
{
    int src, dest, w;
};

bool cmp(edge &a, edge &b)
{
    return a.w < b.w;
}

vector<vector<int>> genGraph(int n, int v)
{
    vector <edge> graph;
    vector <vector<int>> matrixGraph(n, vector<int>(n, -1));
    vector <bool> used(n, false);
    queue<int> next;
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

        if (src == dest || matrixGraph[src][dest] != -1) 
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

vector<edge> matGraphConv(vector<vector<int>> matGraph, int n)
{
    vector<edge> graph;

    for (int i = 0; i < n; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            edge cur;
            if (matGraph[i][j] != -1)
            {
                cur.src = i;
                cur.dest = j;
                cur.w = matGraph[i][j];
                graph.push_back(cur);
            }
        }
    }

    return graph;
}

vector <int> leader;

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
        swap(x, y);
    }

    leader[x] = y;
    return true;
}

void kruskal(vector<edge> graph, int n, int m)
{
    sort(graph.begin(), graph.end(), cmp);
    leader.resize(n);

    for (int i = 0; i < n; i++) 
    {
        leader[i] = i;
    }

    for (int i = 0; i < m; i++)
    {
        int x = graph[i].dest, y = graph[i].src;
    }
    
    return;
}

void prim(vector<vector<int>> graph, int n) 
{
	int no_edge;
    std::vector<bool> selected(n);
	selected[0] = true;
	int x, y;

	while (no_edge < n - 1) 
    	{
		int min = INT_MAX;
		x = 0;
		y = 0;
		for (int i = 0; i < n; i++) 
        		{
			if (selected[i]) 
            		{
				for (int j = 0; j < n; j++) 
                			{
					if (!selected[j] && graph[i][j]) 
                    			{
						if (min > graph[i][j] && graph[i][j] != 0) 
                        				{
							min = graph[i][j];
							x = i;
							y = j;
						}
					}
				}
			}
		}

		selected[y] = true;
		no_edge++;
	}
}

int main() 
{
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
            vector<vector<int>> matGraph = genGraph(n, m);
            std::cout << "Graph gen 1" << std::endl;
            clock_t start = clock();
            prim(matGraph, n);
            clock_t end = clock();
            double seconds = (double)(end - start) / CLOCKS_PER_SEC;
            time_f1_sum += seconds;

            matGraph = genGraph(n, m);
            vector<edge> graph = matGraphConv(matGraph, n);
            std::cout << "Graph gen 2" << std::endl;
            start = clock();
            kruskal(graph, n, m);
            end = clock();
            seconds = (double)(end - start) / CLOCKS_PER_SEC;
            time_f2_sum += seconds;
        }
        
        double time_1 = time_f1_sum / (double)r;
        std::cout << "The time (prim): " << time_1 << " seconds" << std::endl;
        double time_2 = time_f2_sum / (double)r;
        std::cout << "The time (kruskal): " << time_2 << " seconds" << std::endl;

        std::cout << "Enter any char to continue; enter 'q' to exit." << std::endl;
        std::cin >> c;
    }

    return 0;
}
