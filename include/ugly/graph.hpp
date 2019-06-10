
#ifndef UGLY_GRAPH_HPP
#define UGLY_GRAPH_HPP

#include <algorithm>
#include <iostream>
#include <list>
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <vector>

#include "../../src/libugly/edge/edge.hpp"
#include "edge_weighted.hpp"
#include "graph_node.hpp"

namespace ugly {

template <typename... Ts>
class Graph {
 private:
  std::unordered_map<int, std::weak_ptr<GraphNode<Ts>>...> nodes_;
  std::unordered_map<int, std::vector<std::pair<int, std::weak_ptr<Edge>>>>
              neighboring_vertices_;
  std::string label_;
  void        calculateLabel_();

 public:
  Graph(){};
  Graph(std::list<std::weak_ptr<Edge>> connections,
        std::unordered_map<int, std::weak_ptr<GraphNode<Ts>>...> nodes);
  std::vector<std::weak_ptr<Edge>> getEdgesConnectedToVertex(int vertex);
  std::vector<std::weak_ptr<Edge>> getEdgesOriginatingFromVertex(int vertex);
  std::vector<int> getVertices();
  std::string      getLabel();

  std::unique_ptr<Graph<Ts...>> getSubGraph(std::vector<int> vertices);
  /// Determine if the graph is directional this will be true if any single
  /// one of the stored edges are directional, else it will be false
  bool directional();
  bool operator==(const Graph<Ts...>& graph) const {
    return label_ == graph.label_;
  }
  bool operator!=(const Graph<Ts...>& graph) const {
    return !((*this) == graph);
  }
};

template <typename... Ts>
std::unique_ptr<Graph<Ts...>> Graph<Ts...>::getSubGraph(
    std::vector<int> vertices) {
  // Check that all vertices are valid nodes
  for (auto vertex : vertices) {
    if (nodes_.count(vertex) == 0) {
      throw std::invalid_argument(
          "Cannot create a sub graph as not all the"
          " vertices you are trying to make the subgraph from are valid.");
    }
  }

  std::list<std::weak_ptr<Edge>> edges;
  std::unordered_map<int, std::weak_ptr<GraphNode<Ts>>...> nodes;
  // Cycle through the internal edges
  for (auto vertex : vertices) {
    nodes[vertex] = nodes_[vertex];
  }

  for (auto vertex : vertices) {
    for (auto edge_pair : neighboring_vertices_[vertex]) {
      if (nodes.count(edge_pair.first)) {
        edges.push_back(edge_pair.second);
      }
    }
  }

  auto sub_graph =
      std::unique_ptr<Graph<Ts...>>(new Graph<Ts...>(edges, nodes));
  return sub_graph;
}

template <typename... Ts>
bool Graph<Ts...>::directional() {
  for (auto map_pair : neighboring_vertices_) {
    for (auto vector_pair_vertexIdAndEdge : map_pair.second) {
      if (auto edge_ptr = vector_pair_vertexIdAndEdge.second.lock()) {
        if (edge_ptr->directional()) return true;
      }
    }
  }
  return false;
}

template <typename... Ts>
void Graph<Ts...>::calculateLabel_() {
  std::vector<std::string> labels;
  for (auto item : nodes_) {
    if (auto node = item.second.lock()) {
      labels.push_back(node->getLabel());
    }
  }
  std::sort(labels.begin(), labels.end());
  label_ = "";
  for (auto label : labels) {
    label_ += label;
  }
}

template <typename... Ts>
Graph<Ts...>::Graph(
    std::list<std::weak_ptr<Edge>> connections,
    std::unordered_map<int, std::weak_ptr<GraphNode<Ts>>...> nodes) {

  for (auto item : nodes) {
    nodes_[item.first] = item.second;
  }
  for (auto edge_ptr : connections) {
    if (auto edge = edge_ptr.lock()) {
      neighboring_vertices_[edge->getVertex1()].push_back(
          std::pair<int, std::weak_ptr<Edge>>(edge->getVertex2(), edge_ptr));

      if (!edge->directional()) {
        neighboring_vertices_[edge->getVertex2()].push_back(
            std::pair<int, std::weak_ptr<Edge>>(edge->getVertex1(), edge_ptr));
      }
    }
  }

  calculateLabel_();
}

template <typename... Ts>
std::vector<std::weak_ptr<Edge>> Graph<Ts...>::getEdgesConnectedToVertex(
    int vertex) {

  std::vector<std::weak_ptr<Edge>> neighbor_edges;
  for (auto neighboring_vertex : neighboring_vertices_[vertex]) {
    neighbor_edges.push_back(neighboring_vertex.second);
  }
  return neighbor_edges;
}

template <typename... Ts>
std::vector<std::weak_ptr<Edge>> Graph<Ts...>::getEdgesOriginatingFromVertex(
    int vertex) {
  std::vector<std::weak_ptr<Edge>> neighbor_edges;
  for (auto neighboring_vertex : neighboring_vertices_[vertex]) {

    if (auto edge = neighboring_vertex.second.lock()) {
      if (edge->directional()) {
        if (edge->getVertex1() == vertex) {
          neighbor_edges.push_back(neighboring_vertex.second);
        }
      } else {
        neighbor_edges.push_back(neighboring_vertex.second);
      }
    }
  }
  return neighbor_edges;
}

template <typename... Ts>
std::vector<int> Graph<Ts...>::getVertices() {

  std::vector<int> vertices;
  for (auto vertex_it : nodes_) {
    vertices.push_back(vertex_it.first);
  }
  return vertices;
}

template <typename... Ts>
std::string Graph<Ts...>::getLabel() {
  return label_;
}
}
#endif  // UGLY_GRAPH_HPP
