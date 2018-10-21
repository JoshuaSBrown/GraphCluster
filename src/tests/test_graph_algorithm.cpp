
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
  cout << "Test: 1" << endl;
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

    // Edge 1-2
    shared_ptr<Edge> ed1( new EdgeWeighted(1,2,1.0));
    // Edge 2-3
    shared_ptr<Edge> ed2( new EdgeWeighted(2,3,1.0));
    // Edge 3-4
    shared_ptr<Edge> ed3( new EdgeWeighted(3,4,2.0));
    // Edge 4-5
    shared_ptr<Edge> ed4( new EdgeWeighted(4,5,1.0));
    // Edge 5-1
    shared_ptr<Edge> ed5( new EdgeWeighted(5,1,1.0));

    list<weak_ptr<Edge>> eds = { ed1, ed2, ed3, ed4, ed5 };        

    map<int,GraphNode<string>> nds;
    nds[1]= GN0;
    nds[2]= GN1;
    nds[3]= GN2;
    nds[4]= GN3;
    nds[5]= GN4;

    Graph<string> gc(eds,nds);

    double shortest_distance = dijkstraGoingFrom<string>(2,4,gc);
    assert(static_cast<int>(round(shortest_distance))==3);

    shortest_distance = dijkstraGoingFrom<string>(3,4,gc);
    assert(static_cast<int>(round(shortest_distance))==2);
  }

  cout << "Test: 2" << endl;
  {
    // Let's begin by first creating a pentagon
    //
    //      -1c-     7c - 8c
    //     |    |     |   |
    //    5c    2c - 9c - 6c
    //     |    |
    //    4c -- 3c
    //     
    GraphNode<string> GN0("C");
    GraphNode<string> GN1("C");
    GraphNode<string> GN2("C");
    GraphNode<string> GN3("C");
    GraphNode<string> GN4("C");

    // Edge 1-2
    shared_ptr<Edge> ed1( new EdgeWeighted(1,2,1.0));
    // Edge 2-3
    shared_ptr<Edge> ed2( new EdgeWeighted(2,3,1.0));
    // Edge 3-4
    shared_ptr<Edge> ed3( new EdgeWeighted(3,4,1.0));
    // Edge 4-5
    shared_ptr<Edge> ed4( new EdgeWeighted(4,5,1.0));
    // Edge 5-1
    shared_ptr<Edge> ed5( new EdgeWeighted(5,1,1.0));
    // Edge 9-2
    shared_ptr<Edge> ed6( new EdgeWeighted(9,2,1.0));
    // Edge 9-7
    shared_ptr<Edge> ed7( new EdgeWeighted(9,7,1.0));
    // Edge 7-8
    shared_ptr<Edge> ed8( new EdgeWeighted(7,8,1.0));
    // Edge 8-6
    shared_ptr<Edge> ed9( new EdgeWeighted(8,6,1.0));
    // Edge 9-6
    shared_ptr<Edge> ed10( new EdgeWeighted(9,6,1.0));

    list<weak_ptr<Edge>> eds = { ed1, ed2, ed3, ed4, ed5, ed6, ed7, ed8, ed9, ed10 };        

    map<int,GraphNode<string>> nds;
    nds[1]= GN0;
    nds[2]= GN1;
    nds[3]= GN2;
    nds[4]= GN3;
    nds[5]= GN4;

    Graph<string> gc(eds,nds);

    double shortest_distance = dijkstraGoingFrom<string>(4,8,gc);
    assert(static_cast<int>(round(shortest_distance))==5);

    shortest_distance = dijkstraGoingFrom<string>(1,6,gc);
    assert(static_cast<int>(round(shortest_distance))==3);
  }
  return 0;
}
