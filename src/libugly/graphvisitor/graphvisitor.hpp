
#ifndef UGLY_GRAPHVISITOR_HPP
#define UGLY_GRAPHVISITOR_HPP

#include <vector>
#include <list>
#include <set>
#include <map>
#include <memory>
#include <stdexcept>
#include <functional>

#include "../edge/edge.hpp"
#include "../../../include/ugly/constants.hpp"
#include "../../../include/ugly/edge_directed.hpp"
#include "../../../include/ugly/edge_weighted.hpp"
#include "../../../include/ugly/edge_undirected.hpp"
namespace ugly {

  class GraphVisitor{
    public:
      GraphVisitor() : starting_vertex_set_(false) {};
      void setStartingVertex(int vertex);

      bool exploredVertex(int vertex);

      template<typename T>  
      T& getNextEdge();

      void exploreEdge(Edge& edge);

      void addEdge(Edge& edge);

      virtual void addEdges(std::vector<std::reference_wrapper<Edge>> edges);

      /**
       * \brief Determine if an edge can be added
       *
       * If the edge is directed than the first vertex of the edge corresponds
       * to the source and the second to the drain: souce -> drain
       * A directed edge can only be added if a vertex has already been explroed
       * that is in the drain. For an undirected edge at least one of the 
       * vertices must have been explored. 
       **/
      bool edgeCanBeAdded(Edge& edge);

      /**
       * \brief Determine if both vertices in the edge have been explored
       **/
      bool verticesHaveBeenExplored(const Edge &edge) const;
      int getUnexploredVertex(const Edge &edge) const;
      int getExploredVertex(const Edge &edge) const;
/*      bool allEdgesExplored() const { return edges_to_explore_.size()==0 ;}*/
    protected:
      // First int is the vertex, the double is the distance
      std::map<int,double> explored_vertices_;
      std::set<Edge> explored_edges_;
      std::list<Edge> edges_to_explore_;
      std::list<constants::EdgeType> allowed_edge_types_;
      int starting_vertex_;
      bool starting_vertex_set_;

      virtual void addEdge_(Edge& edge);

      virtual void exploreEdge_(Edge& edge);
      
      bool potentialEdgeKnown_(const Edge & edge) const;
      
      bool edgeTypeAllowed_(const Edge & edge) const;
      /*
      template<typename T>
      std::vector<T&> getExploredEdges_();

      template<typename T>
      std::vector<T&> castEdgesToType_(std::vector<Edge&> edges);

      virtual std::vector<Edge&> getEdgesToExplore_();

*/
      virtual Edge& getNextEdge_();
  };

  template<typename T>
  T& GraphVisitor::getNextEdge() {
//    std::cout << "Calling getNextEdge from graphVisitor " << std::endl;
    auto edge = getNextEdge_();
//    std::cout << "class type " << T::getClassType() << std::endl;
//    std::cout << "object type " << edge.getEdgeType() << std::endl;
    if(T::getClassType()=="Edge"){
      return dynamic_cast<T&>(edge);
    }
    if(T::getClassType()==edge.getEdgeType()){
      return dynamic_cast<T&>(edge);
    }
    throw std::runtime_error("Error cannot retrive edge of the type sepcified.");
  }
/*
  template<typename T>
  std::vector<T&> GraphVisitor::getExploredEdges_(){
    std::vector<T&> convertedEdges;
    std::cout << "Number of edges " << explored_edges_.size() << std::endl;
    for( auto edge : explored_edges_ ){
      if(T::getClassType()==edge.getEdgeType()){
        convertedEdges.push_back(std::dynamic_cast<T>(edge));
      } else {
        throw std::runtime_error("edge cannot be converted");
      }
    } 
    return convertedEdges;
  }

  template<typename T>
  std::vector<T&> GraphVisitor::castEdgesToType_(std::vector<Edge&> edges){
    std::vector<T&> convertedEdges;
    for( auto edge : edges ){
      if(T::getClassType()==edge.getEdgeType()){
        std::cout << "Class Type " << T::getClassType() << std::endl;
        std::cout << "Object Type " << edge.getEdgeType() << std::endl;
        convertedEdges.push_back(std::dynamic_cast<T>(edge));
      } else {
        throw std::runtime_error("edge cannot be converted");
      }
    } 
    return convertedEdges;
  }
*/
}

#endif // UGLY_GRAPHVISITOR_HPP
