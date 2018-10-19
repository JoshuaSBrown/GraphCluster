
#include <iostream>
#include <string>
#include <cassert>
#include <list>
#include <vector>
#include <map>

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
      unique_ptr<Edge> ed1( new EdgeWeighted(1,2));
      unique_ptr<Edge> ed2( new EdgeWeighted(2,3));
      unique_ptr<Edge> ed3( new EdgeWeighted(2,1));

      GraphVisitorDepthFirst graphvisitordepthfirst;
      
      bool throwError = false;
      try{
        graphvisitordepthfirst.addEdge(*ed1);
      }catch(...){
        throwError=true;
      }
      assert(throwError);

      graphvisitordepthfirst.setStartingVertex(1);
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

      // Cannot add an edge that is directed from a souce that is not currently
      // one of the explored vertices. This only matters in directed edges.
      throwError=false;
      if(ed3->directional()){
        try{
          graphvisitordepthfirst.addEdge(*ed3);
        }catch(...){
          throwError = true;
        }
      }
      assert(throwError);

      // The depth first graph visitor only allows weighted edges 
      unique_ptr<Edge> ed4( new EdgeUndirected(4,1));

      throwError=false;
      if(ed3->directional()){
        try{
          graphvisitordepthfirst.addEdge(*ed3);
        }catch(...){
          throwError = true;
        }
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
        graphvisitordepthfirst2.addEdges(eds);
      }catch(...){
        throwError=true;
      }
      assert(throwError);

    }
/*
    cout << "Testing: verticesHaveBeenExplored" << endl;
    {
      shared_ptr<Edge> ed1( new EdgeWeighted(1,2));
      shared_ptr<Edge> ed2( new EdgeWeighted(2,3));
      vector<shared_ptr<Edge>> eds = { ed1, ed2 };        

      GraphVisitorDepthFirst graphvisitordepthfirst;
      assert(graphvisitordepthfirst.verticesHaveBeenExplored(ed1)==false);
      graphvisitordepthfirst.addEdges(eds);
      assert(graphvisitordepthfirst.verticesHaveBeenExplored(ed1)==false);
      assert(graphvisitordepthfirst.verticesHaveBeenExplored(ed1)==false);

    }

    cout << "Testing: exploreEdge" << endl;
    {
      shared_ptr<Edge> ed1( new EdgeWeighted(1,2));
      shared_ptr<Edge> ed2( new EdgeWeighted(2,3));
      vector<shared_ptr<Edge>> eds = { ed1, ed2 };        

      GraphVisitorDepthFirst graphvisitordepthfirst;

      bool throwError = false;
      try{
        graphvisitordepthfirst.exploreEdge(ed1);
      }catch(...){
        throwError = true;
      }
      assert(throwError);

      graphvisitordepthfirst.addEdges(eds);

      throwError = false;
      try{
        graphvisitordepthfirst.exploreEdge(ed1);
      }catch(...){
        throwError = true;
      }
      assert(throwError);

      graphvisitordepthfirst.setStartingVertex(1);
      graphvisitordepthfirst.exploreEdge(ed1);
      graphvisitordepthfirst.exploreEdge(ed2);
    }

    cout << "Testing: getUnexploredVertex" << endl;
    {
      
      shared_ptr<Edge> ed1( new EdgeWeighted(1,2));
      shared_ptr<Edge> ed2( new EdgeWeighted(2,3));
      vector<shared_ptr<Edge>> eds = { ed1, ed2 };        

      GraphVisitorDepthFirst graphvisitordepthfirst;
      graphvisitordepthfirst.addEdges(eds);
      graphvisitordepthfirst.setStartingVertex(1);
      
      bool throwError = false;
      try{
        graphvisitordepthfirst.getUnexploredVertex(ed2); 
      }catch(...){
        throwError = true;
      }
      assert(throwError);

      auto unexploredvertex = graphvisitordepthfirst.getUnexploredVertex(ed1);
      assert(unexploredvertex==2);
    }

    cout << "Testing: getExploredVertex" << endl;
    {
      shared_ptr<Edge> ed1( new EdgeWeighted(1,2));
      shared_ptr<Edge> ed2( new EdgeWeighted(2,3));
      vector<shared_ptr<Edge>> eds = { ed1, ed2 };        
      
      GraphVisitorDepthFirst graphvisitordepthfirst;
      graphvisitordepthfirst.addEdges(eds);
      graphvisitordepthfirst.setStartingVertex(1);

      bool throwError = false;
      try{
        graphvisitordepthfirst.getExploredVertex(ed2); 
      }catch(...){
        throwError = true;
      }
      assert(throwError);

      auto exploredvertex = graphvisitordepthfirst.getExploredVertex(ed1);
      assert(exploredvertex==1);
    }

    cout << "Testing: allEdgesExplored" << endl;
    {
      shared_ptr<Edge> ed1( new EdgeWeighted(1,2));
      shared_ptr<Edge> ed2( new EdgeWeighted(2,3));
      vector<shared_ptr<Edge>> eds = { ed1, ed2 };        
      GraphVisitorDepthFirst graphvisitordepthfirst;
      graphvisitordepthfirst.addEdges(eds);
      graphvisitordepthfirst.setStartingVertex(1);

      bool complete = graphvisitordepthfirst.allEdgesExplored();
      assert(complete==false);
      graphvisitordepthfirst.exploreEdge(ed1);
      complete = graphvisitordepthfirst.allEdgesExplored();
      assert(complete==false);
      graphvisitordepthfirst.exploreEdge(ed2);
      complete = graphvisitordepthfirst.allEdgesExplored();
      assert(complete==true);
    }
    cout << "Testing: getNextEdge" << endl;
    {
      shared_ptr<EdgeWeighted> ed1( new EdgeWeighted(1,2));
      shared_ptr<EdgeWeighted> ed2( new EdgeWeighted(2,3));
      vector<shared_ptr<Edge>> eds = { ed1, ed2 };        
      GraphVisitorDepthFirst graphvisitordepthfirst;
      graphvisitordepthfirst.addEdges(eds);
      graphvisitordepthfirst.setStartingVertex(1);

      auto ed = graphvisitordepthfirst.getNextEdge<EdgeWeighted>();

    }
*/
    return 0;
}
