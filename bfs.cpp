#include<iostream>
#include <list>
#include <set>
#include <vector>

// This class represents a directed graph using
// adjacency list representation
class Graph {
  const int V;
  std::list<int> *adj;

public:
  Graph(int V) : V(V) {
    adj = new std::list<int>[V];
  }

  // function to add an edge to graph
  void addEdge(int v, int w) {
    adj[v].push_back(w);
  }

  void topDown(const std::set<int> frontier, std::set<int>& next, std::vector<int>& parents) {
    for (auto const& v : frontier) {
      std::cout << "top " << v << " " << adj[v].size() <<'\n';
      for (auto const& n: adj[v]) {
        if (parents[n] == -1) {
          parents[n] = v;
          next.insert(n);
        }
      }
    }
  }

  void bottomUp(std::set<int> frontier, std::set<int>& next, std::vector<int>& parents) {
    for (auto const& v : frontier) {
      std::cout << "bottom " << v <<" "<< parents[v] <<'\n';
      if (parents[v] == -1) {
        for (auto const& n: adj[v]) {
          parents[n] = v;
          next.insert(n);
          break;
        }
      }
    }
  }

  // prints BFS traversal from a given source s
  void BFS(int s) {
    int source[1] = {s};
    std::set<int> frontier(source, source+1);
    std::set<int> next;
    std::vector<int> parents(V,-1);

    while (frontier.size() > 0) {
      if (frontier.size() > V/2) {
        bottomUp(frontier, next, parents);
      } else {
        topDown(frontier, next, parents);
      }

      frontier = next;
      std::set<int> temp;
      next = temp;
    }
  }
};

// Driver program to test methods of graph class
int main()
{
    // Create a graph given in the above diagram
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    std::cout << "Following is Breadth First Traversal "
         << "(starting from vertex 2) \n";
    g.BFS(2);

    return 0;
}
