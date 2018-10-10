#ifndef UGLY_GRAPHALGORITHMS_HPP
#define UGLY_GRAPHALGORITHMS_HPP

#include <vector>
#include <unordered_map> 
#include <algorithm>

#include "../../src/libugly/edge/edge.hpp"
#include "graph_node.hpp"

namespace ugly {
  
  namespace graphalgorithms {
  
    double dijkstraGoingFrom(int start_vertex, int end_vertex,Graph graph);
      
      GraphVisitor graphvisitor;
      graphvisitor.setStartingVertex(start_vertex);

    }

  }

}
#endif // UGLY_GRAPHALGORITHMS_HPP
