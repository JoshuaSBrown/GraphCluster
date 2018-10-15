
#ifndef UGLY_GRAPH_HPP
#define UGLY_GRAPH_HPP

#include <iostream>
#include <set>
#include <map>
#include <stdexcept>
#include <unordered_map> 
#include <vector>
#include <list>
#include <algorithm>

#include "../../src/libugly/edge/edge.hpp"
#include "graph_node.hpp"

namespace ugly {

  template<typename... Ts>
  class Graph {
    private: 
      std::map<int,GraphNode<Ts>...> nodes_;
      std::unordered_map<int,std::set<int>> neighboring_vertices_;
      std::string label_;
      void calculateLabel_();
    public:
      Graph() {};
      Graph(std::list<Edge> connections, std::map<int,GraphNode<Ts>...> nodes); 
      std::vector<Edge> getEdgesConnectedToVertex(int vertex);
      std::string getLabel();
      
      bool operator==(const Graph<Ts...>& graph) const { return label_==graph.label_;}
      bool operator!=(const Graph<Ts...>& graph) const { return !((*this)==graph);}

  };

  template<typename... Ts>
    void Graph<Ts...>::calculateLabel_() {
      std::vector<std::string> labels;
      for(auto item : nodes_ ) labels.push_back(item.second.getLabel());
      std::sort(labels.begin(),labels.end());
      label_ = "";
      for(auto label : labels ){
        label_+=label;
      }
    }

  template<typename... Ts>
  Graph<Ts...>::Graph(std::list<Edge> connections, std::map<int,GraphNode<Ts>...> nodes){
    for(auto item : nodes ) {
      nodes_[item.first] = item.second;
    }
    for( auto edge : connections ){
      neighboring_vertices_[edge.getVertex1()].insert(edge.getVertex2());
    }
    calculateLabel_();
  }

  template<typename... Ts>
  std::vector<Edge> Graph<Ts...>::getEdgesConnectedToVertex(int vertex){
    std::vector<Edge> neighbor_edges;
    for( auto neighboring_vertex : neighboring_vertices_[vertex]){
      Edge edge(vertex,neighboring_vertex);
      neighbor_edges.push_back(edge);
    }
    return neighbor_edges;
  }


  template<typename... Ts>
    std::string Graph<Ts...>::getLabel(){
      return label_;
    }
}
#endif // UGLY_GRAPH_HPP
