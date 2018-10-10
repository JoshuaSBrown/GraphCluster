
#ifndef UGLY_GRAPHVISITORDEPTHVIRST_HPP
#define UGLY_GRAPHVISITORDEPTHVIRST_HPP

#include "graphvisitor.hpp"
#include "../edge/edge_weighted.hpp"

namespace ugly {

  class GraphVisitorDepthFirst : public GraphVisitor {
    public:
      EdgeWeighted getNextEdge();
      void addEdge(EdgeWeighted edgeweighted);
      void addEdges(vector<EdgeWeighted> edgesweighted);
      void exploreEdge(EdgeWeighted edgeweighted);
      double getDistanceOfVertex(int vertex);
    private:
      EdgeWeighted getEdgeShortestDistance_();
      double getDistanceFromStartingVertexToEdge_(EdgeWeighted edge);
  };

}

#endif // UGLY_GRAPHVISITORDEPTHFIRST_HPP
