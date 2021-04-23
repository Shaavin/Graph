#ifndef MYGRAPH_HPP
#define MYGRAPH_HPP

#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <vector>

class myGraph
{
  public:
    myGraph(char* filename)
    {
      // Open the input file
      std::ifstream inFile;
      inFile.open(filename);

      int src; // a source vertex
      int tgt; // a target vertex
      char ch; // to dump all of the misc. commas into
      while(inFile >> src >> ch >> tgt >> ch)
      {
        theGraph[src].push_back(tgt);
      }

      // Close the input file
      inFile.close();
    }
    ~myGraph() { /* no heap allocated memory used, so no-op */ }

    void print()
    {
      // Create a vector to store all of the key values
      std::vector<int> keys;
      // Reserve the needed space for all of the keys
      keys.reserve(theGraph.size());
      // Push back all of the key values into the vector
      for(auto key_val_pair : theGraph)
        keys.push_back(key_val_pair.first);
      // Print the value corresponding to each key
      for(int aKey = 0; aKey <= keys[keys.size()-1]; aKey++)
      {
        std::cout << aKey << ":";
        for(auto edge : theGraph[aKey])
          std::cout << ' ' << edge;
        std::cout << '\n';
      }
    }

    void BFS(int source)
    {
      // To remember which vertices we have already visited
      bool visited[theGraph.size()];
      for(int i = 0; i < theGraph.size(); i++)
        visited[i] = false;

      // To track the edges to visit from the source
      std::queue<int> edges;

      // Start by pushing the source vertex
      edges.push(source);
      visited[source] = true;

      // At each vertex in the queue, dequeue the front vertex, report its
        // value, then push all of its outbound edges into the queue and
        // repeat until the queue is empty
      int front;
      while(!edges.empty())
      {
        // Find and remove the front of the queue
        front = edges.front();
        edges.pop();

        // Report what the front was
        std::cout << front << '\n';

        // Push all edges from this vertex to the queue...
        for(auto edge : theGraph[front])
        { // ...but only if it has not been visited before
          if(!visited[edge])
          {
            edges.push(edge);
            visited[edge] = true;
          }
        }
      }
    }
    void DFS(int source)
    {
      // To remember which vertices we have already visited
      std::vector<bool> visited(theGraph.size(), false);

      if(theGraph.size() <= 70000) // data set is not too large;
      {                               //  recursion is possible
        DFS_helper_recursive(source, visited);
      }
      else // the data set is too large to recurse; attempting a recursive
      {     // method will cause stack overflow so we change strategies
        DFS_helper_iterative(source, visited);
      }
    }

  private:
    std::map<int, std::vector<int>> theGraph;

    void DFS_helper_recursive(int top, std::vector<bool> & visited)
    {
      std::cout << top << '\n';
      visited[top] = true;
      for(auto edge : theGraph[top])
      {
        if(!visited[edge])
          DFS_helper_recursive(edge, visited);
      }
    }

    void DFS_helper_iterative(int source, std::vector<bool> & visited)
    {
      // To track the edges to visit from the source
      std::stack<int> edges;

      // Start by pushing the source vertex
      edges.push(source);

      // At each vertex in the stack, pop the top vertex, report its value,
        // then push all of its outbound edges into the stack and repeat
        // until the stack is empty
      while(!edges.empty())
      {
        // Find and remove the top of the stack
        int top = edges.top();
        edges.pop();

        if(!visited[top])
        {
          // Report what the top was
          std::cout << top << '\n';
          visited[top] = true;

          auto aVertex = theGraph[top];
          // Push all edges from this vertex to the stack
          for(int i = aVertex.size()-1; i >= 0; i--)
            edges.push(aVertex[i]);
        }
      }
    }
};

#endif
