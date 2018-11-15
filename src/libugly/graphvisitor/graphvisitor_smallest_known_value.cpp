#include "../../../include/ugly/edge_directed.hpp"
#include "../../../include/ugly/edge_directed_weighted.hpp"
#include "../../../include/ugly/edge_undirected.hpp"
#include "../../../include/ugly/edge_weighted.hpp"
#include "../../../include/ugly/graphvisitor/graphvisitor_smallest_known_value.hpp"

#include "../edge/edge.hpp"
#include "../weak_pointer_supplement.hpp"

#include <algorithm>
#include <iostream>
#include <stdexcept>

using namespace std;

namespace ugly {

/****************************************************************************
 * External public facing methods
 ****************************************************************************/
GraphVisitorSmallestKnownValue::GraphVisitorSmallestKnownValue() {
  allowed_edge_types_.push_back(constants::EdgeType::directed_weighted);
  allowed_edge_types_.push_back(constants::EdgeType::weighted);

  allowed_conversions_[constants::EdgeType::directed_weighted].push_back(
      constants::EdgeType::edge);
  allowed_conversions_[constants::EdgeType::weighted].push_back(
      constants::EdgeType::edge);
}

void GraphVisitorSmallestKnownValue::exploreEdge_(weak_ptr<Edge> edge_ptr) {
  if (!verticesHaveBeenExplored(edge_ptr)) {
    explored_vertices_[getUnexploredVertex(edge_ptr)] = 1.0;
  }
}

void GraphVisitorSmallestKnownValue::addEdges(vector<weak_ptr<Edge>> edges) {
  for (auto edge_ptr : edges) {
    addEdge(edge_ptr);
  }
}

/****************************************************************************
 * Internal private functions
 ****************************************************************************/

void GraphVisitorSmallestKnownValue::addEdge_(weak_ptr<Edge>) { return; }

weak_ptr<Edge> GraphVisitorSmallestKnownValue::getNextEdge_() {
  double initial_weight = 0.0;
  auto   edge_to_explore = edges_to_explore_.begin();
  auto   edge            = *edge_to_explore;
  if (auto ed = edge.lock()) {
    auto edge_weighted_ptr = static_pointer_cast<EdgeWeighted>(ed);
    initial_weight         = edge_weighted_ptr->getWeight();
  }else{
    throw runtime_error("edge is not accesible");
  }
  while (edge_to_explore != edges_to_explore_.end()) {
    if (auto ed = edge_to_explore->lock()) {
      auto edge_weighted_ptr = static_pointer_cast<EdgeWeighted>(ed);
      if (edge_weighted_ptr->getWeight() < initial_weight) {
        initial_weight = edge_weighted_ptr->getWeight();
        edge           = *edge_to_explore;
      }
    }
    ++edge_to_explore;
  }
  return edge;
}
}
