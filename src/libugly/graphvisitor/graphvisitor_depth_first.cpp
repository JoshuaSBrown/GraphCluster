
#include <memory>
#include "graphvisitor_depth_first.hpp"
#include "../../../include/ugly/edge_weighted.hpp"

using namespace std;

namespace ugly {

  GraphVisitorDepthFirst::GraphVisitorDepthFirst(){
    allowed_edge_types_ = list<constants::EdgeType>(constants::EdgeType::weighted);
  }

  void GraphVisitorDepthFirst::exploreEdge_(Edge& edge){
 
    auto distance = getDistanceFromStartingVertexToEdge_(edge);
    explored_vertices_[getUnexploredVertex(edge)]=distance;


  }

  void GraphVisitorDepthFirst::addEdge_(Edge& ){
    return;
  }

  void GraphVisitorDepthFirst::addEdges(vector<reference_wrapper<Edge>> edges){
    for( auto edge : edges){
      addEdge(edge);
    }
  }
/*
  double GraphVisitorDepthFirst::getDistanceOfVertex(int vertex){
    if(explored_vertices_.count(vertex)){
      return explored_vertices_[vertex];
    }
    throw invalid_argument("Cannot get distance to vertex as the vertex has not"
        " yet been explored.");
  }
*/
  /****************************************************************************
   * Private Internal Methods
   ****************************************************************************/
/*
  shared_ptr<Edge> GraphVisitorDepthFirst::getEdgeShortestDistance_(){
    double distance;
    bool edge_uninitialized = true;
    shared_ptr<EdgeWeighted> edge_shortest_distance_away;
    cout << "Getting edges to explore" << endl;
    auto edges = getEdgesToExplore_();
    auto weighted_edges_to_explore = castEdgesToType_<EdgeWeighted>(edges);
    cout << "Cycling edges size " << weighted_edges_to_explore.size() << endl;
    for(auto weighted_edge : weighted_edges_to_explore ){
      cout << "printing weighted edge" << endl;
      cout << *weighted_edge << endl;
      cout << "verticesHave been explored" << endl;
      if(!verticesHaveBeenExplored(weighted_edge)){
        std::cout << "getting distance from start" << std::endl; 
        auto edge_distance = getDistanceFromStartingVertexToEdge_(weighted_edge);
        if(edge_uninitialized){
          distance = edge_distance;
          edge_shortest_distance_away = weighted_edge;
          edge_uninitialized=true;
        }else if(edge_distance<distance){
          distance = edge_distance;
          edge_shortest_distance_away = weighted_edge;
        }
      }
      cout << "end of loop" << endl;
    }
    if(edge_uninitialized){
      throw runtime_error("Cannot grab edge shortest distance away because "
          "there are no more edges to be explored");
    }
   
    std::cout << "Edge shortest distance away" << std::endl;
    std::cout << *edge_shortest_distance_away << std::endl; 
    return edge_shortest_distance_away;
  }

  shared_ptr<Edge> GraphVisitorDepthFirst::getNextEdge_(){
    std::cout << "Calling getNextEdge_ from GraphVisitorDepthFirst" << std::endl;
    return GraphVisitorDepthFirst::getEdgeShortestDistance_();
  }
*/

  double GraphVisitorDepthFirst::getDistanceFromStartingVertexToEdge_(const Edge& edge){

    auto exploredVertex = getExploredVertex(edge);
    auto edge_distance = explored_vertices_[exploredVertex];

    if(!edgeTypeAllowed_(edge)){
      throw invalid_argument("Edge type is not allowed in the depth first graph"
          " visitor.");
    }
    auto edge_weighted = static_cast<const EdgeWeighted&>(edge); 
    edge_distance += edge_weighted.getWeight();
    return edge_distance;
  }
}

