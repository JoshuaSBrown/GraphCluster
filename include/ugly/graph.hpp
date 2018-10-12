
#ifndef UGLY_GRAPH_HPP
#define UGLY_GRAPH_HPP

#include <set>
#include <unordered_map> 
#include <vector>
#include <list>

#include "../../src/libugly/edge/edge.hpp"
#include "graph_node.hpp"

namespace ugly {

  template<class... Ts>
    class Graph {
      public:
        Graph(std::list<Edge> connections, std::vector<GraphNode<Ts...>> nodes);

        std::vector<Edge> getEdgesConnectedToVertex(int vertex);
      private: 
        std::unordered_map<int,GraphNode<Ts...>> nodes_;
        std::unordered_map<int,std::set<int>> neighboring_vertices_;

    };


  template<class... Ts>
    Graph::Graph(std::list<Edge> connections, std::vector<GraphNode<Ts...>> nodes){
      nodes_ = nodes;
      for( auto edge : connections ){
        neighboring_vertices_[edge.getVertex1()].insert(edge.getVertex2());
      }
    }

  template<class... Ts>
    std::vector<Edge> Graph::getEdgesConnectedToVertex(int vertex){
      std::vector<Edge> neighbor_edges;
      for( auto neighboring_vertex : neighboring_vertices_[vertex]){
        Edge edge(vertex,neighboring_vertex);
        neighbor_edges.push_back(edge);
      }
      return neighbor_edges;
    }

}
#endif // UGLY_GRAPH_HPP
