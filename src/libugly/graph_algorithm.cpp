#include "../../include/ugly/graph_algorithms.hpp"

namespace ugly {

  double dijkstraGoingFrom(int start_vertex, int end_vertex, Graph graph){

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

    throw runtime_error("No connection has been found between your two "
      "vertices.");
  }

}
