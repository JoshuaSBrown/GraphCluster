
#ifndef UGLY_GRAPHVISITORGENERIC_HPP
#define UGLY_GRAPHVISITORGENERIC_HPP

#include "graphvisitor.hpp"

namespace ugly {

  class GraphVisitorGenericGeneric : public GaphVisitor {
    public:
      GraphVisitorGeneric();

      void addEdges(std::vector<std::weak_ptr<Edge>> edges);

    protected:

      void addEdge_(std::weak_ptr<Edge> edge);
      void exploreEdge_(std::weak_ptr<Edge> edge);
      std::weak_ptr<Edge> getNextEdge_();
  };
}

#endif // UGLY_GRAPHVISITORGENERIC_HPP
