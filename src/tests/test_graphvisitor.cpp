
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

    return 0;
}
