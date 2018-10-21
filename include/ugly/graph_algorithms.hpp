#ifndef UGLY_GRAPHALGORITHMS_HPP
#define UGLY_GRAPHALGORITHMS_HPP

#include <vector>
#include <unordered_map> 
#include <algorithm>
#include <stdexcept>

#include "../../src/libugly/edge/edge.hpp"
#include "../../src/libugly/graphvisitor/graphvisitor_depth_first.hpp"
#include "graph.hpp"
#include "graph_node.hpp"

namespace ugly {
  
  namespace graphalgorithms {
  
    template<class... Ts> 
    double dijkstraGoingFrom(int start_vertex, int end_vertex, Graph<Ts...>& graph){

      GraphVisitorDepthFirst graphvisitor_depth_first;
      auto edges = graph.getEdgesOriginatingFromVertex(start_vertex);
      graphvisitor_depth_first.setStartingVertex(start_vertex);
      graphvisitor_depth_first.addEdges(edges);

      auto next_edge = graphvisitor_depth_first.getNextEdge<EdgeWeighted>();
      while(graphvisitor_depth_first.allEdgesExplored()==false){

        std::cout << "Looking for uexplored edge" << std::endl;
        next_edge = graphvisitor_depth_first.getNextEdge<EdgeWeighted>();
        std::cout << "Exploring Edge" << std::endl;
        if(auto ed = next_edge.lock() ) std::cout << *ed << std::endl;
        auto next_vertex = graphvisitor_depth_first.chooseTerminalVertex(next_edge);
        std::cout << "Exploring" << std::endl;
        graphvisitor_depth_first.exploreEdge(next_edge);
        edges = graph.getEdgesOriginatingFromVertex(next_vertex);

        for (auto ed : edges ){
          std::cout << "Adding edges" << std::endl;
          if(graphvisitor_depth_first.edgeCanBeAdded(ed)){
            if(auto ed_temp = ed.lock()) std::cout << *ed_temp << std::endl;
            graphvisitor_depth_first.addEdge(ed);
          }
        }

        if(end_vertex==next_vertex){
          return graphvisitor_depth_first.getDistanceOfVertex(end_vertex);
        }

      }

      throw std::runtime_error("No connection has been found between your two "
          "vertices.");
    }


  }

}
#endif // UGLY_GRAPHALGORITHMS_HPP
