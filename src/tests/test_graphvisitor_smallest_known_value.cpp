
#include <cassert>
#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "../../include/ugly/edge_directed.hpp"
#include "../../include/ugly/edge_undirected.hpp"
#include "../../include/ugly/edge_weighted.hpp"
#include "../libugly/graphvisitor/graphvisitor_smallest_known_value.hpp"
#include "../libugly/weak_pointer_supplement.hpp"
using namespace ugly;
using namespace std;

int main(void) {

  cout << "Testing: Constructor " << endl;
  { GraphVisitorSmallestKnownValue graphvisitorsmallestknownvalue; }

  cout << "Testing: addEdge" << endl;
  {
    shared_ptr<EdgeWeighted> ed1(new EdgeWeighted(1, 2));
    shared_ptr<EdgeWeighted> ed2(new EdgeWeighted(2, 3));
    shared_ptr<EdgeWeighted> ed3(new EdgeWeighted(2, 1));

    GraphVisitorSmallestKnownValue graphvisitorsmallestknownvalue;

    bool throwError = false;
    try {
      graphvisitorsmallestknownvalue.addEdge(ed1);
    } catch (...) {
      throwError = true;
    }
    assert(throwError);

    graphvisitorsmallestknownvalue.setStartingVertex(1);
    graphvisitorsmallestknownvalue.addEdge(ed1);

    // Cannot add the same edge twice
    throwError = false;
    try {
      graphvisitorsmallestknownvalue.addEdge(ed1);
    } catch (...) {
      throwError = true;
    }
    assert(throwError);

    // Cannot add an edge that is not associated with a vertex that has been
    // explored, currently the starting vertex is the only one that satisfies
    // that criteria
    throwError = false;
    try {
      graphvisitorsmallestknownvalue.addEdge(ed2);
    } catch (...) {
      throwError = true;
    }
    assert(throwError);

    // The smallestknownvalue graph visitor allows mixing of edges
    shared_ptr<Edge> ed4(new EdgeUndirected(4, 1));
    throwError = false;
    try {
      graphvisitorsmallestknownvalue.addEdge(ed4);
    } catch (...) {
      throwError = true;
    }
    assert(throwError);
  }

  cout << "Testing: addEdges" << endl;
  {

    shared_ptr<Edge>       ed1(new EdgeWeighted(1, 2));
    shared_ptr<Edge>       ed2(new EdgeWeighted(2, 3));
    vector<weak_ptr<Edge>> eds = {ed1, ed2};

    GraphVisitorSmallestKnownValue graphvisitorsmallestknownvalue;
    bool                           throwError = false;
    try {
      graphvisitorsmallestknownvalue.addEdges(eds);
    } catch (...) {
      throwError = true;
    }
    assert(throwError);

    graphvisitorsmallestknownvalue.setStartingVertex(1);

    // Because edge 2 is not connected to vertex 1 this will throw an error
    throwError = false;
    try {
      graphvisitorsmallestknownvalue.addEdges(eds);
    } catch (...) {
      throwError = true;
    }
    assert(throwError);

    shared_ptr<Edge>       ed11(new EdgeUndirected(1, 2));
    shared_ptr<Edge>       ed22(new EdgeDirected(2, 3));
    vector<weak_ptr<Edge>> eds2 = {ed11, ed22};

    cout << "ed11 directional? " << ed11->directional() << endl;
    GraphVisitorSmallestKnownValue graphvisitorsmallestknownvalue2;
    graphvisitorsmallestknownvalue2.setStartingVertex(2);

    throwError = false;
    try {
      graphvisitorsmallestknownvalue2.addEdges(eds2);
    } catch (...) {
      throwError = true;
    }
    assert(throwError);
  }

  cout << "Testing: exploreEdge" << endl;
  {
    shared_ptr<Edge>       ed1(new EdgeWeighted(1, 2));
    shared_ptr<Edge>       ed2(new EdgeWeighted(2, 3));
    vector<weak_ptr<Edge>> eds = {ed1, ed2};

    GraphVisitorSmallestKnownValue graphvisitorsmallestknownvalue;

    bool throwError = false;
    try {
      graphvisitorsmallestknownvalue.exploreEdge(ed1);
    } catch (...) {
      throwError = true;
    }
    assert(throwError);

    graphvisitorsmallestknownvalue.setStartingVertex(2);
    graphvisitorsmallestknownvalue.addEdges(eds);

    graphvisitorsmallestknownvalue.exploreEdge(ed1);

    // Should now throw an error because ed1 has now been explored
    throwError = false;
    try {
      graphvisitorsmallestknownvalue.exploreEdge(ed1);
    } catch (...) {
      throwError = true;
    }
    assert(throwError);

    graphvisitorsmallestknownvalue.exploreEdge(ed2);
  }

  cout << "Testing: exploreEdge" << endl;
  {
    shared_ptr<Edge>       ed1(new Edge(1, 2));
    shared_ptr<Edge>       ed2(new Edge(2, 3));
    vector<weak_ptr<Edge>> eds = {ed1, ed2};

    GraphVisitor graphvisitor;

    bool throwError = false;
    try {
      graphvisitor.exploreEdge(ed1);
    } catch (...) {
      throwError = true;
    }
    assert(throwError);
  }

  cout << "Testing: getUnexploredVertex" << endl;
  {

    shared_ptr<Edge>       ed1(new EdgeWeighted(1, 2));
    shared_ptr<Edge>       ed2(new EdgeWeighted(2, 3));
    shared_ptr<Edge>       ed3(new EdgeWeighted(2, 4));
    shared_ptr<Edge>       ed4(new EdgeWeighted(3, 4));
    vector<weak_ptr<Edge>> eds = {ed1, ed2};

    GraphVisitorSmallestKnownValue graphvisitorsmallestknownvalue;
    graphvisitorsmallestknownvalue.setStartingVertex(2);
    graphvisitorsmallestknownvalue.addEdges(eds);

    auto unexploredvertex =
        graphvisitorsmallestknownvalue.getUnexploredVertex(ed1);
    assert(unexploredvertex == 1);

    unexploredvertex = graphvisitorsmallestknownvalue.getUnexploredVertex(ed3);
    assert(unexploredvertex == 4);

    // Neither vertex of edge 4 is listed as explored so it will
    // throw an error
    bool throwError = false;
    try {
      graphvisitorsmallestknownvalue.getUnexploredVertex(ed4);
    } catch (...) {
      throwError = true;
    }
    assert(throwError);
  }

  cout << "Testing: getExploredVertex" << endl;
  {
    shared_ptr<Edge>       ed1(new EdgeWeighted(1, 2));
    shared_ptr<Edge>       ed2(new EdgeWeighted(2, 3));
    shared_ptr<Edge>       ed3(new EdgeWeighted(4, 3));
    vector<weak_ptr<Edge>> eds = {ed1, ed2};

    GraphVisitorSmallestKnownValue graphvisitorsmallestknownvalue;
    graphvisitorsmallestknownvalue.setStartingVertex(2);
    graphvisitorsmallestknownvalue.addEdges(eds);

    bool throwError = false;
    try {
      graphvisitorsmallestknownvalue.getExploredVertex(ed3);
    } catch (...) {
      throwError = true;
    }
    assert(throwError);

    auto exploredvertex = graphvisitorsmallestknownvalue.getExploredVertex(ed1);
    assert(exploredvertex == 2);
  }

  cout << "Testing: allEdgesExplored" << endl;
  {
    shared_ptr<Edge>               ed1(new EdgeWeighted(1, 2));
    shared_ptr<Edge>               ed2(new EdgeWeighted(2, 3));
    vector<weak_ptr<Edge>>         eds = {ed1, ed2};
    GraphVisitorSmallestKnownValue graphvisitorsmallestknownvalue;
    graphvisitorsmallestknownvalue.setStartingVertex(2);
    graphvisitorsmallestknownvalue.addEdges(eds);

    bool complete = graphvisitorsmallestknownvalue.allEdgesExplored();
    assert(complete == false);
    graphvisitorsmallestknownvalue.exploreEdge(ed1);
    complete = graphvisitorsmallestknownvalue.allEdgesExplored();
    assert(complete == false);
    graphvisitorsmallestknownvalue.exploreEdge(ed2);
    complete = graphvisitorsmallestknownvalue.allEdgesExplored();
    assert(complete == true);
  }

  // Should always grab the edge with the smallest value
  cout << "Testing: getNextEdge" << endl;
  {
    shared_ptr<EdgeWeighted>       ed1(new EdgeWeighted(1, 2, 0.5));
    shared_ptr<EdgeWeighted>       ed2(new EdgeWeighted(2, 3, 2.3));
    shared_ptr<EdgeWeighted>       ed3(new EdgeWeighted(2, 4, 0.1));
    vector<weak_ptr<Edge>>         eds = {ed1, ed2, ed3};
    GraphVisitorSmallestKnownValue graphvisitorsmallestknownvalue;
    graphvisitorsmallestknownvalue.setStartingVertex(2);
    graphvisitorsmallestknownvalue.addEdges(eds);

    vector<weak_ptr<EdgeWeighted>> edges;
    auto ed11 = graphvisitorsmallestknownvalue.getNextEdge<EdgeWeighted>();
    assert(ed11 == ed3);
    edges.push_back(ed11);
    graphvisitorsmallestknownvalue.exploreEdge(ed11);
    auto ed22 = graphvisitorsmallestknownvalue.getNextEdge<EdgeWeighted>();
    assert(ed22 == ed1);
    edges.push_back(ed22);
    graphvisitorsmallestknownvalue.exploreEdge(ed22);
    auto ed33 = graphvisitorsmallestknownvalue.getNextEdge<EdgeWeighted>();
    assert(ed33 == ed2);
    graphvisitorsmallestknownvalue.exploreEdge(ed33);
  }

  // Should always grab the edge with the smallest known weight
  cout << "Testing: getNextEdge 2" << endl;
  {
    shared_ptr<EdgeWeighted>       ed1(new EdgeWeighted(1, 2, 0.5));
    shared_ptr<EdgeWeighted>       ed2(new EdgeWeighted(2, 3, 2.3));
    shared_ptr<EdgeWeighted>       ed3(new EdgeWeighted(2, 4, 0.2));
    vector<weak_ptr<Edge>>         eds = {ed1, ed2, ed3};
    GraphVisitorSmallestKnownValue graphvisitorsmallestknownvalue;
    graphvisitorsmallestknownvalue.setStartingVertex(2);
    graphvisitorsmallestknownvalue.addEdges(eds);

    vector<weak_ptr<EdgeWeighted>> edges;
    auto ed11 = graphvisitorsmallestknownvalue.getNextEdge<EdgeWeighted>();
    assert(ed11 == ed3);
    edges.push_back(ed11);
    graphvisitorsmallestknownvalue.exploreEdge(ed11);
    auto ed22 = graphvisitorsmallestknownvalue.getNextEdge<EdgeWeighted>();
    assert(ed22 == ed1);
    edges.push_back(ed22);
    graphvisitorsmallestknownvalue.exploreEdge(ed22);

    // Now that we have explored vertex 1 we can add these edges
    // Now edge 5 rpresents the smallest known value as ed3 has already been
    // explored
    shared_ptr<EdgeWeighted> ed4(new EdgeWeighted(1, 5, 3.1));
    shared_ptr<EdgeWeighted> ed5(new EdgeWeighted(1, 6, 0.4));
    vector<weak_ptr<Edge>>   eds2 = {ed4, ed5};
    graphvisitorsmallestknownvalue.addEdges(eds2);

    auto ed33 = graphvisitorsmallestknownvalue.getNextEdge<EdgeWeighted>();
    assert(ed33 == ed5);
    graphvisitorsmallestknownvalue.exploreEdge(ed33);
    auto ed44 = graphvisitorsmallestknownvalue.getNextEdge<EdgeWeighted>();
    assert(ed44 == ed2);
    graphvisitorsmallestknownvalue.exploreEdge(ed44);
    auto ed55 = graphvisitorsmallestknownvalue.getNextEdge<EdgeWeighted>();
    assert(ed55 == ed4);
    graphvisitorsmallestknownvalue.exploreEdge(ed55);
  }
  return 0;
}
