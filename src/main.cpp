#include <iostream>
#include  <sstream>

// Inspired by pseudo code in wikipedia article (https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)
/*
"In the following pseudocode algorithm, 
dist is an array that contains the current distances from the source to other vertices, 
i.e. dist[u] is the current distance from the source to the vertex u. The prev array contains pointers to previous-hop nodes on the shortest path from source to the given vertex (equivalently, it is the next-hop on the path from the given vertex to the source). The code u ← vertex in Q with min dist[u], searches for the vertex u in the vertex set Q that has the least dist[u] value. Graph.Edges(u, v) returns the length of the edge joining (i.e. the distance between) the two neighbor-nodes u and v. The variable alt on line 14 is the length of the path from the root node to the neighbor node v if it were to go through u. If this path is shorter than the current shortest path recorded for v, that current path is replaced with this alt path.[7]"
1  function Dijkstra(Graph, source):
 2      
 3      for each vertex v in Graph.Vertices:
 4          dist[v] ← INFINITY
 5          prev[v] ← UNDEFINED
 6          add v to Q
 7      dist[source] ← 0
 8      
 9      while Q is not empty:
10          u ← vertex in Q with min dist[u]
11          remove u from Q
12          
13          for each neighbor v of u still in Q:
14              alt ← dist[u] + Graph.Edges(u, v)
15              if alt < dist[v]:
16                  dist[v] ← alt
17                  prev[v] ← u
18
19      return dist[], prev[]
*/  

/*
1  S ← empty sequence
2  u ← target
3  if prev[u] is defined or u = source:          // Do something only if the vertex is reachable
4      while u is defined:                       // Construct the shortest path with a stack S
5          insert u at the beginning of S        // Push the vertex onto the stack
6          u ← prev[u]                           // Traverse from target to source
*/

// From youtube "Dijkstra Algorithm Coding C++ | Shortest Path | Implementation | Graphs | Greedy" (https://youtu.be/a1Z1GmKzcPs )
namespace youtube_a1Z1GmKzcPs {
  // From https://gist.github.com/nateshmbhat/1a79daa00a148e44ad79c3e338977440#file-dijkstra_algorithm-cpp
  char const* szExample = R"(0 4 999 999 999 999 999 8 999
4 0 8 999 999 999 999 8 999
999 999 7 0 9 14 999 999 999
999 999 999 9 0 10 999 999 999
999 999 4 14 10 0 1 6
8 11 999 999 999 999 1 0 7
999 999 2 999 999 999 6 7 0)";
  int cost[100][100], n;
  int getMin(int dist[], bool visited[]) {
    int key = 0;
    int min = INT_MAX;
    for (int i = 0; i < n; i++)
    {
      if (!visited[i] && dist[i] < min)
      {
        min = dist[i];
        key = i;
      }
    }
    return key;
  }
  void display(int dist[], int par[]) {    
    for (int i = 0; i < n; i++)
    {
      int temp = par[i];
      std::cout << i << " <- ";
      while (temp != -1)
      {
        std::cout << temp << " <- ";
        temp = par[temp];
      }
      std::cout << "\n";
      std::cout << "::::Distance = " << dist[i];
      std::cout << "\n";
    }
  }
  void dijkstra(int src) {
    int par[100], dist[100];
    bool visited[100] = {0};
    std::fill(dist, dist + n, INT_MAX);
    dist[src] = 0;
    par[src] = -1;
    for (int g = 0; g < n - 1; g++)
    {
      int u = getMin(dist, visited);
      visited[u] = true;
      std::cout << " min = " << u << "\n";
      for (int v = 0; v < n; v++)
      {
        if (!visited[v] && (dist[u] + cost[u][v]) < dist[v] && cost[u][v] != 9999)
        {
          par[v] = u;
          dist[v] = dist[u] + cost[u][v];
        }
      }
    }
    display(dist, par);
  }
  void main(void) {
    char y_or_n{'y'};
    std::cout << "\nUse default data (y/n)?";
    std::cin >> y_or_n;
    if (y_or_n == 'y') {
      n = 9;
      std::istringstream in{szExample};
      for (int i = 0; i < n; i++)
      {
        for (int j = 0; j < n; j++) {
          in >> cost[i][j];
          std::cout << "\ncost[" << i << "][" << j << "]=" << cost[i][j];
        }
      }
    }
    else {
      std::cout << "\nEnter n (vertex count) : ";
      std::cin >> n;
      std::cout << "Enter cost matrix : \n";
      for (int i = 0; i < n; i++)
      {
        for (int j = 0; j < n; j++)
          std::cin >> cost[i][j];
      }
    }
    int src;
    std::cout << "\nEnter source : ";
    std::cin >> src;
    dijkstra(src);
  }
}

int main(int argc, char *argv[]) {
  youtube_a1Z1GmKzcPs::main();
  return 0;
}              