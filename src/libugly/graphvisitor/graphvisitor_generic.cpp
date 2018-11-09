#include "../../../include/ugly/edge_directed.hpp"
#include "../../../include/ugly/edge_directed_weighted.hpp"
#include "../../../include/ugly/edge_undirected.hpp"
#include "../../../include/ugly/edge_weighted.hpp"
#include "../../../include/ugly/graphvisitor/graphvisitor_generic.hpp"

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
GraphVisitorGeneric::GraphVisitorGeneric() {
  allowed_edge_types_.push_back(constants::EdgeType::undirected);
  allowed_edge_types_.push_back(constants::EdgeType::directed);
  allowed_edge_types_.push_back(constants::EdgeType::directed_weighted);
  allowed_edge_types_.push_back(constants::EdgeType::weighted);

  allowed_conversions_[constants::EdgeType::undirected].push_back(
      constants::EdgeType::edge);
  allowed_conversions_[constants::EdgeType::directed].push_back(
      constants::EdgeType::edge);
  allowed_conversions_[constants::EdgeType::directed_weighted].push_back(
      constants::EdgeType::edge);
  allowed_conversions_[constants::EdgeType::weighted].push_back(
      constants::EdgeType::edge);
}

void GraphVisitorGeneric::exploreEdge_(weak_ptr<Edge> edge_ptr) {
  if (!verticesHaveBeenExplored(edge_ptr)) {
    explored_vertices_[getUnexploredVertex(edge_ptr)] = 1.0;
  }
}

void GraphVisitorGeneric::addEdges(vector<weak_ptr<Edge>> edges) {
  for (auto edge_ptr : edges) {
    addEdge(edge_ptr);
  }
}

/****************************************************************************
 * Internal private functions
 ****************************************************************************/

void GraphVisitorGeneric::addEdge_(weak_ptr<Edge>) { return; }

weak_ptr<Edge> GraphVisitorGeneric::getNextEdge_() {
  return (*edges_to_explore_.begin());
}
}
