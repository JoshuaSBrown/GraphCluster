
#ifndef UGLY_GRAPHVISITOR_HPP
#define UGLY_GRAPHVISITOR_HPP

#include <vector>
#include <list>
#include <set>
#include <map>
#include <memory>
#include <stdexcept>

#include "../edge/edge.hpp"

namespace ugly {

  class GraphVisitor{
    public:
      GraphVisitor() {};
      void setStartingVertex(int vertex);
      bool exploredVertex(int vertex);

      template<typename T>  
      std::shared_ptr<T> getNextEdge();

      virtual void exploreEdge(std::shared_ptr<Edge> edge);
      virtual void addEdge(std::shared_ptr<Edge> edge);
      virtual void addEdges(std::vector<std::shared_ptr<Edge>> edges);
      bool verticesHaveBeenExplored(std::shared_ptr<Edge> edge) const;
      int getUnexploredVertex(std::shared_ptr<Edge> edge) const;
      int getExploredVertex(std::shared_ptr<Edge> edge) const;
      bool allEdgesExplored() const { return edges_to_explore_.size()==0 ;}
    protected:
      // First int is the vertex, the double is the distance
      std::map<int,double> explored_vertices_;
      int starting_vertex_;

      template<typename T>
      std::vector<std::shared_ptr<T>> getExploredEdges_();

      template<typename T>
      std::vector<std::shared_ptr<T>> getEdgesToExplore_();

      virtual std::shared_ptr<Edge> getNextEdge_();

      std::set<std::shared_ptr<Edge>> explored_edges_;
      std::list<std::shared_ptr<Edge>> edges_to_explore_;
  };

  template<typename T>
  std::shared_ptr<T> GraphVisitor::getNextEdge() {
    auto edge = getNextEdge_();
    if(T::getClassType()=="Edge"){
      return std::dynamic_pointer_cast<T>(edge);
    }
    if(T::getClassType()==edge->getEdgeType()){
      return std::dynamic_pointer_cast<T>(edge);
    }
  }

  template<typename T>
  std::vector<std::shared_ptr<T>> GraphVisitor::getExploredEdges_(){
    std::vector<std::shared_ptr<T>> convertedEdges;
    for( auto edge : explored_edges_ ){
      if(T::getClassType()==edge->getEdgeType()){
        convertedEdges.push_back(std::dynamic_pointer_cast<T>(edge));
      } else {
        throw std::runtime_error("edge cannot be converted");
      }
    } 
    return convertedEdges;
  }

  template<typename T>
  std::vector<std::shared_ptr<T>> GraphVisitor::getEdgesToExplore_(){
    std::vector<std::shared_ptr<T>> convertedEdges;
    for( auto edge : edges_to_explore_ ){
      if(T::getClassType()==edge->getEdgeType()){
        convertedEdges.push_back(std::dynamic_pointer_cast<T>(edge));
      } else {
        throw std::runtime_error("edge cannot be converted");
      }
    } 
    return convertedEdges;
  }

}

#endif // UGLY_GRAPHVISITOR_HPP
