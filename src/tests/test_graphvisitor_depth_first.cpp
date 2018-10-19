
#include <iostream>
#include <string>
#include <cassert>
#include <list>
#include <vector>
#include <map>
#include <cmath>

#include "../libugly/graphvisitor/graphvisitor_depth_first.hpp"
#include "../../include/ugly/edge_weighted.hpp"
#include "../../include/ugly/edge_undirected.hpp"
#include "../../include/ugly/edge_directed.hpp"

using namespace ugly;
using namespace std;

int main(void){

    cout << "Testing: Constructor " << endl;
    {
      GraphVisitorDepthFirst graphvisitordepthfirst;
    }

    cout << "Testing: addEdge" << endl;
    {
      unique_ptr<EdgeWeighted> ed1( new EdgeWeighted(1,2));
      unique_ptr<EdgeWeighted> ed2( new EdgeWeighted(2,3));
      unique_ptr<EdgeWeighted> ed3( new EdgeWeighted(2,1));

      GraphVisitorDepthFirst graphvisitordepthfirst;
      
      bool throwError = false;
      try{
        graphvisitordepthfirst.addEdge(*ed1);
      }catch(...){
        throwError=true;
      }
      assert(throwError);

      graphvisitordepthfirst.setStartingVertex(1);
      cout << "Get Edge Type " << ed1->getEdgeType() << endl;
      graphvisitordepthfirst.addEdge(*ed1);
     
      // Cannot add the same edge twice 
      throwError=false;
      try{
        graphvisitordepthfirst.addEdge(*ed1);
      }catch(...){
        throwError = true;
      }
      assert(throwError);

      // Cannot add an edge that is not associated with a vertex that has been 
      // explored, currently the starting vertex is the only one that satisfies
      // that criteria
      throwError=false;
      try{
        graphvisitordepthfirst.addEdge(*ed2);
      }catch(...){
        throwError = true;
      }
      assert(throwError);

      cout << "edge " << constants::EdgeType::edge << endl;
      cout << "undirected " << constants::EdgeType::undirected << endl;
      cout << "weighted " << constants::EdgeType::weighted << endl;
      cout << "directed " << constants::EdgeType::directed << endl;

      // The depth first graph visitor only allows weighted edges 
      unique_ptr<Edge> ed4( new EdgeUndirected(4,1));

      throwError=false;
      try{
        graphvisitordepthfirst.addEdge(*ed4);
      }catch(...){
        throwError = true;
      }
      assert(throwError);

    }

    cout << "Testing: addEdges" << endl;
    {

      unique_ptr<Edge> ed1( new EdgeWeighted(1,2));
      unique_ptr<Edge> ed2( new EdgeWeighted(2,3));
      vector<reference_wrapper<Edge>> eds = { *ed1, *ed2 };        

      GraphVisitorDepthFirst graphvisitordepthfirst;
      bool throwError=false;
      try{
        graphvisitordepthfirst.addEdges(eds);
      }catch(...){
        throwError=true;
      }
      assert(throwError);

      graphvisitordepthfirst.setStartingVertex(1);

      throwError=false;
      try{
        graphvisitordepthfirst.addEdges(eds);
      }catch(...){
        throwError=true;
      }
      assert(throwError);

     
      unique_ptr<Edge> ed11( new EdgeUndirected(1,2));
      unique_ptr<Edge> ed22( new EdgeDirected(2,3));
      vector<reference_wrapper<Edge>> eds2 = { *ed11, *ed22 };        

      cout << "ed11 directional? " << ed11->directional() << endl;
      GraphVisitorDepthFirst graphvisitordepthfirst2;
      graphvisitordepthfirst2.setStartingVertex(2);
      
      // Only allows weighted edges
      throwError=false;
      try{
        graphvisitordepthfirst2.addEdges(eds2);
      }catch(...){
        throwError=true;
      }
      assert(throwError);

    }

    cout << "Testing: exploreEdge" << endl;
    {
      unique_ptr<Edge> ed1( new EdgeWeighted(1,2));
      unique_ptr<Edge> ed2( new EdgeWeighted(2,3));
      vector<reference_wrapper<Edge>> eds = { *ed1, *ed2 };        

      GraphVisitorDepthFirst graphvisitordepthfirst;

      bool throwError = false;
      try{
        graphvisitordepthfirst.exploreEdge(*ed1);
      }catch(...){
        throwError = true;
      }
      assert(throwError);

      graphvisitordepthfirst.setStartingVertex(2);
      graphvisitordepthfirst.addEdges(eds);

      graphvisitordepthfirst.exploreEdge(*ed1);

      // Should now throw an error because ed1 has now been explored
      throwError = false;
      try{
        graphvisitordepthfirst.exploreEdge(*ed1);
      }catch(...){
        throwError = true;
      }
      assert(throwError);

      graphvisitordepthfirst.exploreEdge(*ed2);
    }


    cout << "Testing: exploreEdge" << endl;
    {
      unique_ptr<Edge> ed1( new Edge(1,2));
      unique_ptr<Edge> ed2( new Edge(2,3));
      vector<reference_wrapper<Edge>> eds = { *ed1, *ed2 };

      GraphVisitor graphvisitor;

      bool throwError = false;
      try{
        graphvisitor.exploreEdge(*ed1);
      }catch(...){
        throwError = true;
      }
      assert(throwError);

    }

    cout << "Testing: getUnexploredVertex" << endl;
    {

      unique_ptr<Edge> ed1( new EdgeWeighted(1,2));
      unique_ptr<Edge> ed2( new EdgeWeighted(2,3));
      unique_ptr<Edge> ed3( new EdgeWeighted(2,4));
      unique_ptr<Edge> ed4( new EdgeWeighted(3,4));
      vector<reference_wrapper<Edge>> eds = { *ed1, *ed2 };

      GraphVisitorDepthFirst graphvisitordepthfirst;
      graphvisitordepthfirst.setStartingVertex(2);
      graphvisitordepthfirst.addEdges(eds);

      auto unexploredvertex = graphvisitordepthfirst.getUnexploredVertex(*ed1);
      assert(unexploredvertex==1);

      unexploredvertex = graphvisitordepthfirst.getUnexploredVertex(*ed3);
      assert(unexploredvertex==4);

      // Neither vertex of edge 4 is listed as explored so it will
      // throw an error
      bool throwError = false;
      try{
        graphvisitordepthfirst.getUnexploredVertex(*ed4);
      }catch(...){
        throwError = true;
      }
      assert(throwError);
    }

    cout << "Testing: getExploredVertex" << endl;
    {
      unique_ptr<Edge> ed1( new EdgeWeighted(1,2));
      unique_ptr<Edge> ed2( new EdgeWeighted(2,3));
      unique_ptr<Edge> ed3( new EdgeWeighted(4,3));
      vector<reference_wrapper<Edge>> eds = { *ed1, *ed2 };

      GraphVisitorDepthFirst graphvisitordepthfirst;
      graphvisitordepthfirst.setStartingVertex(2);
      graphvisitordepthfirst.addEdges(eds);

      bool throwError = false;
      try{
        graphvisitordepthfirst.getExploredVertex(*ed3);
      }catch(...){
        throwError = true;
      }
      assert(throwError);

      auto exploredvertex = graphvisitordepthfirst.getExploredVertex(*ed1);
      assert(exploredvertex==2);
    }

    cout << "Testing: allEdgesExplored" << endl;
    {
      unique_ptr<Edge> ed1( new EdgeWeighted(1,2));
      unique_ptr<Edge> ed2( new EdgeWeighted(2,3));
      vector<reference_wrapper<Edge>> eds = { *ed1, *ed2 };        
      GraphVisitorDepthFirst graphvisitordepthfirst;
      graphvisitordepthfirst.setStartingVertex(2);
      graphvisitordepthfirst.addEdges(eds);

      bool complete = graphvisitordepthfirst.allEdgesExplored();
      assert(complete==false);
      graphvisitordepthfirst.exploreEdge(*ed1);
      complete = graphvisitordepthfirst.allEdgesExplored();
      assert(complete==false);
      graphvisitordepthfirst.exploreEdge(*ed2);
      complete = graphvisitordepthfirst.allEdgesExplored();
      assert(complete==true);
    }

    cout << "Testing: getDistanceOfVertex" << endl;
    {
      unique_ptr<Edge> ed1( new EdgeWeighted(1,2));
      unique_ptr<Edge> ed2( new EdgeWeighted(2,3,32));
      vector<reference_wrapper<Edge>> eds = { *ed1, *ed2 };        
      GraphVisitorDepthFirst graphvisitordepthfirst;
      graphvisitordepthfirst.setStartingVertex(2);
      graphvisitordepthfirst.addEdges(eds);

      graphvisitordepthfirst.exploreEdge(*ed1);
      graphvisitordepthfirst.exploreEdge(*ed2);

      auto dist = graphvisitordepthfirst.getDistanceOfVertex(2);
      assert(static_cast<int>(round(dist))==0);
      dist = graphvisitordepthfirst.getDistanceOfVertex(1);
      assert(static_cast<int>(round(dist))==1);
      dist = graphvisitordepthfirst.getDistanceOfVertex(3);
      assert(static_cast<int>(round(dist))==32);
    }

    
    
    cout << "Testing: getNextEdge" << endl;
    {
      unique_ptr<EdgeWeighted> ed1( new EdgeWeighted(1,2,0.5));
      unique_ptr<EdgeWeighted> ed2( new EdgeWeighted(2,3,2.3));
      vector<reference_wrapper<Edge>> eds = { *ed1, *ed2 };        
      GraphVisitorDepthFirst graphvisitordepthfirst;
      graphvisitordepthfirst.setStartingVertex(2);
      graphvisitordepthfirst.addEdges(eds);

      auto ed = graphvisitordepthfirst.getNextEdge<EdgeWeighted>();
      assert(ed==*ed1);

      graphvisitordepthfirst.exploreEdge(ed);
      ed = graphvisitordepthfirst.getNextEdge<EdgeWeighted>();
      assert(ed==*ed2);
    }

    return 0;
}
