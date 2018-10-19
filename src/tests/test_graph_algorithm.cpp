
#include <iostream>
#include <string>
#include <cassert>
#include <list>
#include <vector>
#include <map>

#include "../../include/ugly/graph.hpp"
#include "../../include/ugly/graph_node.hpp"
#include "../../include/ugly/graph_algorithms.hpp"
#include "../../include/ugly/edge_weighted.hpp"

using namespace ugly;
using namespace std;
using namespace graphalgorithms;

int main(void){

  cout << "Testing: dijkstraGoingFrom" << endl;
  {

    // Let's begin by first creating a pentagon
    //
    //      -1c-
    //     |    |
    //    5c    2c
    //     |    |
    //    4c -- 3c
    //     
    GraphNode<string> GN0("C");
    GraphNode<string> GN1("C");
    GraphNode<string> GN2("C");
    GraphNode<string> GN3("C");
    GraphNode<string> GN4("C");

    // Edge 1->2
    shared_ptr<Edge> ed1( new EdgeWeighted(1,2,1.0));
    // Edge 2->3
    shared_ptr<Edge> ed2( new EdgeWeighted(2,3,1.0));
    // Edge 3->4
    shared_ptr<Edge> ed3( new EdgeWeighted(3,4,2.0));
    // Edge 4->5
    shared_ptr<Edge> ed4( new EdgeWeighted(4,5,1.0));
    // Edge 5->1
    shared_ptr<Edge> ed5( new EdgeWeighted(5,1,1.0));

    list<shared_ptr<Edge>> eds = { ed1, ed2, ed3, ed4, ed5 };        

    map<int,GraphNode<string>> nds;
    nds[1]= GN0;
    nds[2]= GN1;
    nds[3]= GN2;
    nds[4]= GN3;
    nds[5]= GN4;

    Graph<string> gc(eds,nds);

    double shortest_distance = dijkstraGoingFrom<string>(2,4,gc);

    cout << shortest_distance << endl; 
  }

  return 0;
}
