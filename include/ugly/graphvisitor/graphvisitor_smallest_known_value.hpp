
#ifndef UGLY_GRAPHVISITORSMALLESTKNOWNVALUE_HPP
#define UGLY_GRAPHVISITORSMALLESTKNOWNVALUE_HPP

#include "../../../src/libugly/graphvisitor/graphvisitor.hpp"

namespace ugly {

class Edge;

/**
 * \brief Explores based on the smallest weight
 *
 * This class is different from the depth first exploration because depth first
 * explores by looking at the shortest path from the starting point. This class
 * simply explores edges based on their weights regradless of whether they are
 * the shortest distance from the starting point or not.
 **/

class GraphVisitorSmallestKnownValue : public GraphVisitor {
 public:
  GraphVisitorSmallestKnownValue();

  void addEdges(std::vector<std::weak_ptr<Edge>> edges);

 protected:
  void addEdge_(std::weak_ptr<Edge> edge);
  void exploreEdge_(std::weak_ptr<Edge> edge);
  std::weak_ptr<Edge> getNextEdge_();
};
}

#endif  // UGLY_GRAPHVISITORSMALLESTKNOWNVALUE_HPP
