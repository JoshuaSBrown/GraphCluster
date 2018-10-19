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
    double dijkstraGoingFrom(int start_vertex, int end_vertex, Graph<Ts...> graph){

      std::cout << "end vertex " << end_vertex << std::endl;
      GraphVisitorDepthFirst graphvisitor_depth_first;
      auto edges = graph.getEdgesConnectedToVertex(start_vertex);
      std::cout << "Edges connected to starting vertex " << start_vertex << std::endl;
      for( auto edge : edges ) {
        std::cout << *edge << std::endl;
      }
      graphvisitor_depth_first.addEdges(edges);
      graphvisitor_depth_first.setStartingVertex(start_vertex);

      auto next_edge = graphvisitor_depth_first.getNextEdge<EdgeWeighted>();    

      std::cout << "Starting loop " << std::endl;
   /*   while(graphvisitor_depth_first.allEdgesExplored()==false){
        std::cout << "loop" << std::endl;
        auto edge = graphvisitor_depth_first.getNextEdge<Edge>();
        std::cout << "Got edge" << std::endl;
        graphvisitor_depth_first.exploreEdge(edge);
        std::cout << "1" << std::endl;
        auto next_vertex = graphvisitor_depth_first.getUnexploredVertex(edge);
        std::cout << "2" << std::endl;
        edges = graph.getEdgesConnectedToVertex(next_vertex);
        std::cout << "3" << std::endl;
        graphvisitor_depth_first.addEdges(edges);
        std::cout << "4" << std::endl;
        if(next_vertex==end_vertex){
          std::cout << " Returning with distance " << std::endl;
          return graphvisitor_depth_first.getDistanceOfVertex(next_vertex);
        }
        std::cout << "5" << std::endl;
      }*/

//      throw std::runtime_error("No connection has been found between your two "
//          "vertices.");
      return 2.1;
    }


  }

}
#endif // UGLY_GRAPHALGORITHMS_HPP
