
#include <iostream>
#include <string>
#include <cassert>
#include <list>
#include <vector>
#include <map>

#include "../libugly/graphvisitor/graphvisitor.hpp"
#include "../../include/ugly/edge_weighted.hpp"

using namespace ugly;
using namespace std;

int main(void){

    cout << "Testing: Constructor " << endl;
    {
      GraphVisitor graphvisitor;
    }

    cout << "Testing: addEdge" << endl;
    {
      unique_ptr<Edge> ed1( new EdgeWeighted(1,2));
      unique_ptr<Edge> ed2( new EdgeWeighted(2,3));

      GraphVisitor graphvisitor;
      
      bool throwError = false;
      try{
        graphvisitor.addEdge(*ed1); 
      }catch(...){
        throwError=true;
      }
      assert(throwError);
    }

    cout << "Testing: setStartingVertex" << endl;
    {
      GraphVisitor graphvisitor;
      graphvisitor.setStartingVertex(1);
    }

    cout << "Testing: edgeCanBeAdded" << endl;
    {
      unique_ptr<Edge> ed1( new EdgeWeighted(1,2));
      unique_ptr<Edge> ed2( new EdgeWeighted(2,3));

      GraphVisitor graphvisitor;

      bool edgecanbeadded = graphvisitor.edgeCanBeAdded(*ed1);
      assert(!edgecanbeadded);

      graphvisitor.setStartingVertex(1);
      edgecanbeadded = graphvisitor.edgeCanBeAdded(*ed1);
      assert(edgecanbeadded);
    }

    cout << "Testing: addEdges" << endl;
    {

      unique_ptr<Edge> ed1( new EdgeWeighted(1,2));
      unique_ptr<Edge> ed2( new EdgeWeighted(2,3));
      vector<reference_wrapper<Edge>> eds;
      eds.push_back( *ed1 );
      eds.push_back( *ed2 );        

      GraphVisitor graphvisitor;
      bool throwError=false;
      try{
        graphvisitor.addEdges(eds);
      }catch(...){
        throwError=true;
      }
      assert(throwError);
    }

    cout << "Testing: verticesHaveBeenExplored" << endl;
    {
      unique_ptr<Edge> ed1( new EdgeWeighted(2,1));
      unique_ptr<Edge> ed2( new EdgeWeighted(2,3));
      vector<reference_wrapper<Edge>> eds = { *ed1, *ed2 };        

      GraphVisitor graphvisitor;
      graphvisitor.setStartingVertex(2);
      assert(graphvisitor.verticesHaveBeenExplored(*ed1)==false);

    }

/*
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
