
#ifndef UGLY_GRAPHVISITORDEPTHVIRST_HPP
#define UGLY_GRAPHVISITORDEPTHVIRST_HPP

#include "graphvisitor.hpp"

namespace ugly {

  class EdgeWeighted;

  class GraphVisitorDepthFirst : public GraphVisitor {
    public:
      GraphVisitorDepthFirst();
      void addEdges(std::vector<std::reference_wrapper<Edge>> edges);
      double getDistanceOfVertex(int vertex);
    private:
      void exploreEdge_(Edge& edge);
      void addEdge_(Edge&);
      Edge& getNextEdge_();
      Edge& getEdgeShortestDistance_();
      double getDistanceFromStartingVertexToEdge_(const Edge& edge);

  };

}

#endif // UGLY_GRAPHVISITORDEPTHFIRST_HPP
