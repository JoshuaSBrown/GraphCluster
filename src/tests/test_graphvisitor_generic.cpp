
#include <cassert>
#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "../../include/ugly/edge_directed.hpp"
#include "../../include/ugly/edge_undirected.hpp"
#include "../../include/ugly/edge_weighted.hpp"
#include "../../include/ugly/graphvisitor/graphvisitor_generic.hpp"
#include "../libugly/weak_pointer_supplement.hpp"
using namespace ugly;
using namespace std;

int main(void) {

  cout << "Testing: Constructor " << endl;
  { GraphVisitorGeneric graphvisitorgeneric; }

  cout << "Testing: addEdge" << endl;
  {
    shared_ptr<EdgeWeighted> ed1(new EdgeWeighted(1, 2));
    shared_ptr<EdgeWeighted> ed2(new EdgeWeighted(2, 3));
    shared_ptr<EdgeWeighted> ed3(new EdgeWeighted(2, 1));

    GraphVisitorGeneric graphvisitorgeneric;

    bool throwError = false;
    try {
      graphvisitorgeneric.addEdge(ed1);
    } catch (...) {
      throwError = true;
    }
    assert(throwError);

    graphvisitorgeneric.setStartingVertex(1);
    graphvisitorgeneric.addEdge(ed1);

    // Cannot add the same edge twice
    throwError = false;
    try {
      graphvisitorgeneric.addEdge(ed1);
    } catch (...) {
      throwError = true;
    }
    assert(throwError);

    // Cannot add an edge that is not associated with a vertex that has been
    // explored, currently the starting vertex is the only one that satisfies
    // that criteria
    throwError = false;
    try {
      graphvisitorgeneric.addEdge(ed2);
    } catch (...) {
      throwError = true;
    }
    assert(throwError);

    // The generic graph visitor allows mixing of edges
    shared_ptr<Edge> ed4(new EdgeUndirected(4, 1));
    graphvisitorgeneric.addEdge(ed4);
  }

  cout << "Testing: addEdges" << endl;
  {

    shared_ptr<Edge>       ed1(new EdgeWeighted(1, 2));
    shared_ptr<Edge>       ed2(new EdgeWeighted(2, 3));
    vector<weak_ptr<Edge>> eds = {ed1, ed2};

    GraphVisitorGeneric graphvisitorgeneric;
    bool                throwError = false;
    try {
      graphvisitorgeneric.addEdges(eds);
    } catch (...) {
      throwError = true;
    }
    assert(throwError);

    graphvisitorgeneric.setStartingVertex(1);

    // Because edge 2 is not connected to vertex 1 this will throw an error
    throwError = false;
    try {
      graphvisitorgeneric.addEdges(eds);
    } catch (...) {
      throwError = true;
    }
    assert(throwError);

    shared_ptr<Edge>       ed11(new EdgeUndirected(1, 2));
    shared_ptr<Edge>       ed22(new EdgeDirected(2, 3));
    vector<weak_ptr<Edge>> eds2 = {ed11, ed22};

    cout << "ed11 directional? " << ed11->directional() << endl;
    GraphVisitorGeneric graphvisitorgeneric2;
    graphvisitorgeneric2.setStartingVertex(2);

    // Generic visitor allows mixing of edges
    graphvisitorgeneric2.addEdges(eds2);
  }

  cout << "Testing: exploreEdge" << endl;
  {
    shared_ptr<Edge>       ed1(new EdgeWeighted(1, 2));
    shared_ptr<Edge>       ed2(new EdgeWeighted(2, 3));
    vector<weak_ptr<Edge>> eds = {ed1, ed2};

    GraphVisitorGeneric graphvisitorgeneric;

    bool throwError = false;
    try {
      graphvisitorgeneric.exploreEdge(ed1);
    } catch (...) {
      throwError = true;
    }
    assert(throwError);

    graphvisitorgeneric.setStartingVertex(2);
    graphvisitorgeneric.addEdges(eds);

    graphvisitorgeneric.exploreEdge(ed1);

    // Should now throw an error because ed1 has now been explored
    throwError = false;
    try {
      graphvisitorgeneric.exploreEdge(ed1);
    } catch (...) {
      throwError = true;
    }
    assert(throwError);

    graphvisitorgeneric.exploreEdge(ed2);
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

    GraphVisitorGeneric graphvisitorgeneric;
    graphvisitorgeneric.setStartingVertex(2);
    graphvisitorgeneric.addEdges(eds);

    auto unexploredvertex = graphvisitorgeneric.getUnexploredVertex(ed1);
    assert(unexploredvertex == 1);

    unexploredvertex = graphvisitorgeneric.getUnexploredVertex(ed3);
    assert(unexploredvertex == 4);

    // Neither vertex of edge 4 is listed as explored so it will
    // throw an error
    bool throwError = false;
    try {
      graphvisitorgeneric.getUnexploredVertex(ed4);
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

    GraphVisitorGeneric graphvisitorgeneric;
    graphvisitorgeneric.setStartingVertex(2);
    graphvisitorgeneric.addEdges(eds);

    bool throwError = false;
    try {
      graphvisitorgeneric.getExploredVertex(ed3);
    } catch (...) {
      throwError = true;
    }
    assert(throwError);

    auto exploredvertex = graphvisitorgeneric.getExploredVertex(ed1);
    assert(exploredvertex == 2);
  }

  cout << "Testing: allEdgesExplored" << endl;
  {
    shared_ptr<Edge>       ed1(new EdgeWeighted(1, 2));
    shared_ptr<Edge>       ed2(new EdgeWeighted(2, 3));
    vector<weak_ptr<Edge>> eds = {ed1, ed2};
    GraphVisitorGeneric    graphvisitorgeneric;
    graphvisitorgeneric.setStartingVertex(2);
    graphvisitorgeneric.addEdges(eds);

    bool complete = graphvisitorgeneric.allEdgesExplored();
    assert(complete == false);
    graphvisitorgeneric.exploreEdge(ed1);
    complete = graphvisitorgeneric.allEdgesExplored();
    assert(complete == false);
    graphvisitorgeneric.exploreEdge(ed2);
    complete = graphvisitorgeneric.allEdgesExplored();
    assert(complete == true);
  }

  cout << "Testing: getNextEdge" << endl;
  {
    shared_ptr<EdgeWeighted> ed1(new EdgeWeighted(1, 2, 0.5));
    shared_ptr<EdgeWeighted> ed2(new EdgeWeighted(2, 3, 2.3));
    vector<weak_ptr<Edge>>   eds = {ed1, ed2};
    GraphVisitorGeneric      graphvisitorgeneric;
    graphvisitorgeneric.setStartingVertex(2);
    graphvisitorgeneric.addEdges(eds);

    vector<weak_ptr<EdgeWeighted>> edges;
    auto ed11 = graphvisitorgeneric.getNextEdge<EdgeWeighted>();
    edges.push_back(ed11);
    graphvisitorgeneric.exploreEdge(ed11);
    auto ed22 = graphvisitorgeneric.getNextEdge<EdgeWeighted>();
    edges.push_back(ed22);
    graphvisitorgeneric.exploreEdge(ed22);

    bool ed1_found = false;
    bool ed2_found = false;
    for (auto ed : edges) {
      if (ed == ed1) ed1_found = true;
      if (ed == ed2) ed2_found = true;
    }
    assert(ed1_found);
    assert(ed2_found);
  }
  return 0;
}
