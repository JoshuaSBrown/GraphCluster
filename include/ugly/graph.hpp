
#ifndef UGLY_GRAPH_HPP
#define UGLY_GRAPH_HPP

#include <vector>
#include <set>
#include <unordered_map> 

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

}
#endif // UGLY_GRAPH_HPP
