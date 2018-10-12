#ifndef UGLY_GRAPHALGORITHMS_HPP
#define UGLY_GRAPHALGORITHMS_HPP

#include <vector>
#include <unordered_map> 
#include <algorithm>
#include <stdexcept>

#include "../../src/libugly/edge/edge.hpp"
#include "graph.hpp"
#include "graph_node.hpp"

namespace ugly {
  
  namespace graphalgorithms {
  
    template<class... Ts> 
    double dijkstraGoingFrom(int start_vertex, int end_vertex, Graph<Ts...> graph){

      GraphVisitor graphvisitor;
      graphvisitor.setStartingVertex(start_vertex);

      auto edges = graph.getEdgesConnectedToVertex(start_vertex);
      graphvisitor.addEdges(edges);

      while(graphvisitor.allEdgesExplored()==false){
        auto edge = graphvisitor.getNextEdge();
        graphvisitor.exploreEdge(edge);
        auto next_vertex = graphvisitor.getUnexploredVertex();
        edges = graph.getEdgesConnectedToVertex(next_vertex);
        graphvisitor.addEdges(edges);
        if(next_vertex==end_vertex){
          return graphvisitor.getDistanceOfVertex(next_vertex);
        }
      }

      throw std::runtime_error("No connection has been found between your two "
          "vertices.");
    }


  }

}
#endif // UGLY_GRAPHALGORITHMS_HPP
