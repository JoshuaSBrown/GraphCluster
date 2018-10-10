
#ifndef UGLY_GRAPHVISITORDEPTHVIRST_HPP
#define UGLY_GRAPHVISITORDEPTHVIRST_HPP

#include "graphvisitor.hpp"

namespace ugly {

  class EdgeWeighted;

  class GraphVisitorDepthFirst : public GraphVisitor {
    public:
      void addEdge(std::shared_ptr<Edge> edge);
      void addEdges(std::vector<std::shared_ptr<Edge>> edges);
      void exploreEdge(std::shared_ptr<Edge> edge);
      double getDistanceOfVertex(int vertex);
    private:
      std::shared_ptr<Edge> getNextEdge();
      std::shared_ptr<Edge> getEdgeShortestDistance_();
      double getDistanceFromStartingVertexToEdge_(std::shared_ptr<EdgeWeighted> edge);
  };

  template<typename T>
  std::shared_ptr<T> getNextEdge(){

  }
}

#endif // UGLY_GRAPHVISITORDEPTHFIRST_HPP
