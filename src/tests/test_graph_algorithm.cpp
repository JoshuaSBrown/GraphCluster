
#include <cassert>
#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <vector>

#include "../../include/ugly/edge_directed_weighted.hpp"
#include "../../include/ugly/edge_weighted.hpp"
#include "../../include/ugly/graph.hpp"
#include "../../include/ugly/graph_algorithms.hpp"
#include "../../include/ugly/graph_node.hpp"

using namespace ugly;
using namespace std;
using namespace graphalgorithms;

int main(void) {

  cout << "Testing: dijkstraGoingFrom" << endl;
  cout << "Test: with weighted edges 1" << endl;
  {
    // Let's begin by first creating a pentagon
    //
    //      -1c-
    //     |    |
    //    5c    2c
    //     |    |
    //    4c -- 3c
    //
    auto GN0 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN1 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN2 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN3 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN4 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));

    // Edge 1-2
    shared_ptr<Edge> ed1(new EdgeWeighted(1, 2, 1.0));
    // Edge 2-3
    shared_ptr<Edge> ed2(new EdgeWeighted(2, 3, 1.0));
    // Edge 3-4
    shared_ptr<Edge> ed3(new EdgeWeighted(3, 4, 2.0));
    // Edge 4-5
    shared_ptr<Edge> ed4(new EdgeWeighted(4, 5, 1.0));
    // Edge 5-1
    shared_ptr<Edge> ed5(new EdgeWeighted(5, 1, 1.0));

    list<weak_ptr<Edge>> eds = {ed1, ed2, ed3, ed4, ed5};

    unordered_map<int, weak_ptr<GraphNode<string>>> nds;
    nds[1] = GN0;
    nds[2] = GN1;
    nds[3] = GN2;
    nds[4] = GN3;
    nds[5] = GN4;

    Graph<string> gc(eds, nds);

    double shortest_distance = dijkstraGoingFrom<string>(2, 4, gc);
    assert(static_cast<int>(round(shortest_distance)) == 3);

    shortest_distance = dijkstraGoingFrom<string>(3, 4, gc);
    assert(static_cast<int>(round(shortest_distance)) == 2);
  }

  cout << "Test: with weighted edges 2" << endl;
  {
    // Let's begin by first creating a pentagon
    //
    //      -1c-     7c - 8c
    //     |    |     |   |
    //    5c    2c - 9c - 6c
    //     |    |
    //    4c -- 3c
    //
    auto GN0 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN1 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN2 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN3 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN4 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));

    // Edge 1-2
    shared_ptr<Edge> ed1(new EdgeWeighted(1, 2, 1.0));
    // Edge 2-3
    shared_ptr<Edge> ed2(new EdgeWeighted(2, 3, 1.0));
    // Edge 3-4
    shared_ptr<Edge> ed3(new EdgeWeighted(3, 4, 1.0));
    // Edge 4-5
    shared_ptr<Edge> ed4(new EdgeWeighted(4, 5, 1.0));
    // Edge 5-1
    shared_ptr<Edge> ed5(new EdgeWeighted(5, 1, 1.0));
    // Edge 9-2
    shared_ptr<Edge> ed6(new EdgeWeighted(9, 2, 1.0));
    // Edge 9-7
    shared_ptr<Edge> ed7(new EdgeWeighted(9, 7, 1.0));
    // Edge 7-8
    shared_ptr<Edge> ed8(new EdgeWeighted(7, 8, 1.0));
    // Edge 8-6
    shared_ptr<Edge> ed9(new EdgeWeighted(8, 6, 1.0));
    // Edge 9-6
    shared_ptr<Edge> ed10(new EdgeWeighted(9, 6, 1.0));

    list<weak_ptr<Edge>> eds = {ed1, ed2, ed3, ed4, ed5,
                                ed6, ed7, ed8, ed9, ed10};

    unordered_map<int, weak_ptr<GraphNode<string>>> nds;
    nds[1] = GN0;
    nds[2] = GN1;
    nds[3] = GN2;
    nds[4] = GN3;
    nds[5] = GN4;

    Graph<string> gc(eds, nds);

    double shortest_distance = dijkstraGoingFrom<string>(4, 8, gc);
    assert(static_cast<int>(round(shortest_distance)) == 5);

    shortest_distance = dijkstraGoingFrom<string>(1, 6, gc);
    assert(static_cast<int>(round(shortest_distance)) == 3);
  }

  cout << "Test: with directed and weighted edges 3" << endl;
  {
    // Let's begin by first creating a pentagon
    //
    //      -1c-
    //     |    |
    //    5c    2c
    //     |    |
    //    4c -- 3c
    //
    auto GN0 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN1 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN2 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN3 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN4 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));

    // Edge 1->2
    shared_ptr<Edge> ed1(new EdgeDirectedWeighted(1, 2, 1.0));
    // Edge 2->3
    shared_ptr<Edge> ed2(new EdgeDirectedWeighted(2, 3, 1.0));
    // Edge 3->4
    shared_ptr<Edge> ed3(new EdgeDirectedWeighted(3, 4, 2.0));
    // Edge 4->5
    shared_ptr<Edge> ed4(new EdgeDirectedWeighted(4, 5, 1.0));
    // Edge 5->1
    shared_ptr<Edge> ed5(new EdgeDirectedWeighted(5, 1, 1.0));

    list<weak_ptr<Edge>> eds = {ed1, ed2, ed3, ed4, ed5};

    unordered_map<int, weak_ptr<GraphNode<string>>> nds;
    nds[1] = GN0;
    nds[2] = GN1;
    nds[3] = GN2;
    nds[4] = GN3;
    nds[5] = GN4;

    Graph<string> gc(eds, nds);

    double shortest_distance = dijkstraGoingFrom<string>(2, 3, gc);
    assert(static_cast<int>(round(shortest_distance)) == 1);

    shortest_distance = dijkstraGoingFrom<string>(3, 2, gc);
    assert(static_cast<int>(round(shortest_distance)) == 5);
  }

  cout << "Test: with directed and weighted edges 4" << endl;
  {
    // Let's begin by first creating a pentagon
    //
    //      -1c-
    //     |    |
    //    5c    2c
    //     |    |
    //    4c -- 3c
    //
    auto GN0 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN1 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN2 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN3 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN4 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));

    // Switched the order so it should not be possible to find a shortest
    // distance between the vertices
    // Edge 2->1
    shared_ptr<Edge> ed1(new EdgeDirectedWeighted(2, 1, 1.0));
    // Edge 2->3
    shared_ptr<Edge> ed2(new EdgeDirectedWeighted(2, 3, 1.0));
    // Edge 3->4
    shared_ptr<Edge> ed3(new EdgeDirectedWeighted(3, 4, 2.0));
    // Edge 4->5
    shared_ptr<Edge> ed4(new EdgeDirectedWeighted(4, 5, 1.0));
    // Edge 5->1
    shared_ptr<Edge> ed5(new EdgeDirectedWeighted(5, 1, 1.0));

    list<weak_ptr<Edge>> eds = {ed1, ed2, ed3, ed4, ed5};

    unordered_map<int, weak_ptr<GraphNode<string>>> nds;
    nds[1] = GN0;
    nds[2] = GN1;
    nds[3] = GN2;
    nds[4] = GN3;
    nds[5] = GN4;

    Graph<string> gc(eds, nds);

    double shortest_distance = dijkstraGoingFrom<string>(2, 3, gc);
    assert(static_cast<int>(round(shortest_distance)) == 1);

    bool throwError = false;
    try {
      shortest_distance = dijkstraGoingFrom<string>(3, 2, gc);
    } catch (...) {
      throwError = true;
    }
    assert(throwError);
  }

  cout << "Testing: maxMinimumDistanceBetweenEveryVertex" << endl;
  cout << "Testing: Test 1" << endl;
  {

    // Let's begin by first creating a pentagon
    //
    //      -1c-
    //     |    |
    //    5c    2c
    //     |    |
    //    4c -- 3c
    //
    auto GN0 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN1 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN2 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN3 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN4 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));

    // Switched the order so it should not be possible to find a shortest
    // distance between the vertices
    // Edge 1->2
    shared_ptr<Edge> ed1(new EdgeDirectedWeighted(1, 2, 2.0));
    // Edge 2->3
    shared_ptr<Edge> ed2(new EdgeDirectedWeighted(2, 3, 1.0));
    // Edge 3->4
    shared_ptr<Edge> ed3(new EdgeDirectedWeighted(3, 4, 1.0));
    // Edge 4->5
    shared_ptr<Edge> ed4(new EdgeDirectedWeighted(4, 5, 1.0));
    // Edge 5->1
    shared_ptr<Edge> ed5(new EdgeDirectedWeighted(5, 1, 1.0));

    list<weak_ptr<Edge>> eds = {ed1, ed2, ed3, ed4, ed5};

    unordered_map<int, weak_ptr<GraphNode<string>>> nds;
    nds[1] = GN0;
    nds[2] = GN1;
    nds[3] = GN2;
    nds[4] = GN3;
    nds[5] = GN4;

    Graph<string> gc(eds, nds);

    auto maxMinDistances = maxMinimumDistanceBetweenEveryVertex<string>(gc);
    assert(maxMinDistances.size() == 5);

    // Max distance starting at vertex
    // 1 should be a distance of 5
    // 2 should be a distance of 4
    // 3 should be a distance of 5
    // 4 should be a distance of 5
    // 5 should be a distance of 5

    int count4s = 0;
    int count5s = 0;
    for (auto map_iterator : maxMinDistances) {
      if (static_cast<int>(round(map_iterator.second)) == 4) ++count4s;
      if (static_cast<int>(round(map_iterator.second)) == 5) ++count5s;
    }

    assert(count4s == 1);
    assert(count5s == 4);
  }

  cout << "Testing: Test 2" << endl;
  {

    // Let's begin by first creating a single edge with nodes
    //
    //  1c - 2c
    //
    auto GN0 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN1 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));

    // Switched the order so it should not be possible to find a shortest
    // distance between the vertices
    // Edge 1->2
    shared_ptr<Edge> ed1(new EdgeDirectedWeighted(1, 2, 2.0));
    // Edge 2<-1
    shared_ptr<Edge> ed2(new EdgeDirectedWeighted(2, 1, 1.0));

    list<weak_ptr<Edge>> eds = {ed1, ed2};

    unordered_map<int, weak_ptr<GraphNode<string>>> nds;
    nds[1] = GN0;
    nds[2] = GN1;

    Graph<string> gc(eds, nds);

    auto maxMinDistances = maxMinimumDistanceBetweenEveryVertex<string>(gc);
    assert(maxMinDistances.size() == 2);

    // Max distance starting at vertex
    // 1 should be a distance of 2
    // 2 should be a distance of 1
    bool dist2found = false;
    bool dist1found = false;
    for (auto map_iterator : maxMinDistances) {
      if (static_cast<int>(round(map_iterator.second)) == 2) dist2found = true;
      if (static_cast<int>(round(map_iterator.second)) == 1) dist1found = true;
    }
    assert(dist1found);
    assert(dist2found);
  }

  cout << "Testing: findSubGraphs" << endl;
  cout << "Test1" << endl;
  {

    // Let's begin by first creating a pentagon
    //
    //      -1c-
    //     |    |
    //    5c    2c
    //     |    |
    //    4c -- 3c
    //
    auto GN0 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN1 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN2 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN3 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN4 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));

    // Edge 1->2
    shared_ptr<Edge> ed12(new EdgeDirected(1, 2));
    // Edge 2->1
    shared_ptr<Edge> ed21(new EdgeDirected(2, 1));
    // Edge 2->3
    shared_ptr<Edge> ed23(new EdgeDirectedWeighted(2, 3, 1.0));
    shared_ptr<Edge> ed32(new EdgeDirectedWeighted(3, 2, 1.0));
    // Edge 3->4
    shared_ptr<Edge> ed34(new EdgeDirected(3, 4));
    shared_ptr<Edge> ed43(new EdgeDirected(4, 3));
    // Edge 4->5
    shared_ptr<Edge> ed45(new EdgeDirectedWeighted(4, 5, 1.0));
    shared_ptr<Edge> ed54(new EdgeDirectedWeighted(5, 4, 1.0));
    // Edge 5->1
    shared_ptr<Edge> ed51(new EdgeDirectedWeighted(5, 1, 1.0));
    shared_ptr<Edge> ed15(new EdgeDirectedWeighted(1, 5, 1.0));

    list<weak_ptr<Edge>> eds = {ed12, ed21, ed23, ed32, ed34,
                                ed43, ed54, ed45, ed51, ed15};

    unordered_map<int, weak_ptr<GraphNode<string>>> nds;
    nds[1] = GN0;
    nds[2] = GN1;
    nds[3] = GN2;
    nds[4] = GN3;
    nds[5] = GN4;

    Graph<string> gc(eds, nds);

    auto subgraphs = findSubGraphs<string>(gc);
    assert(subgraphs.size() == 1);

    bool found_vertex1 = false;
    bool found_vertex2 = false;
    bool found_vertex3 = false;
    bool found_vertex4 = false;
    bool found_vertex5 = false;
    for (auto vertex : subgraphs.at(0)) {
      if (vertex == 1) found_vertex1 = true;
      if (vertex == 2) found_vertex2 = true;
      if (vertex == 3) found_vertex3 = true;
      if (vertex == 4) found_vertex4 = true;
      if (vertex == 5) found_vertex5 = true;
    }

    assert(found_vertex1);
    assert(found_vertex2);
    assert(found_vertex3);
    assert(found_vertex4);
    assert(found_vertex5);
  }

  cout << "Test2" << endl;
  {

    // Let's begin by first creating a pentagon
    //
    //      -1c-
    //     |    |    6c    7c-8c
    //    5c    2c
    //     |    |
    //    4c -- 3c
    //
    auto GN0 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN1 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN2 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN3 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN4 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN5 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN6 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN7 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));

    // Edge 1->2
    shared_ptr<Edge> ed12(new EdgeDirected(1, 2));
    // Edge 2->1
    shared_ptr<Edge> ed21(new EdgeDirected(2, 1));
    // Edge 2->3
    shared_ptr<Edge> ed23(new EdgeDirectedWeighted(2, 3, 1.0));
    shared_ptr<Edge> ed32(new EdgeDirectedWeighted(3, 2, 1.0));
    // Edge 3->4
    shared_ptr<Edge> ed34(new EdgeDirected(3, 4));
    shared_ptr<Edge> ed43(new EdgeDirected(4, 3));
    // Edge 4->5
    shared_ptr<Edge> ed45(new EdgeDirectedWeighted(4, 5, 1.0));
    shared_ptr<Edge> ed54(new EdgeDirectedWeighted(5, 4, 1.0));
    // Edge 5->1
    shared_ptr<Edge> ed51(new EdgeDirectedWeighted(5, 1, 1.0));
    shared_ptr<Edge> ed15(new EdgeDirectedWeighted(1, 5, 1.0));

    shared_ptr<Edge> ed78(new EdgeDirected(7, 8));
    shared_ptr<Edge> ed87(new EdgeDirected(8, 7));

    list<weak_ptr<Edge>> eds = {ed12, ed21, ed23, ed32, ed34, ed43,
                                ed54, ed45, ed51, ed15, ed78, ed87};

    unordered_map<int, weak_ptr<GraphNode<string>>> nds;
    nds[1] = GN0;
    nds[2] = GN1;
    nds[3] = GN2;
    nds[4] = GN3;
    nds[5] = GN4;
    nds[6] = GN5;
    nds[7] = GN6;
    nds[8] = GN7;

    Graph<string> gc(eds, nds);

    auto subgraphs = findSubGraphs<string>(gc);
    assert(subgraphs.size() == 3);

    bool found_vertex1 = false;
    bool found_vertex2 = false;
    bool found_vertex3 = false;
    bool found_vertex4 = false;
    bool found_vertex5 = false;
    bool found_vertex6 = false;
    bool found_vertex7 = false;
    bool found_vertex8 = false;

    for (auto subgraph : subgraphs) {
      for (auto vertex : subgraph) {
        if (vertex == 1) found_vertex1 = true;
        if (vertex == 2) found_vertex2 = true;
        if (vertex == 3) found_vertex3 = true;
        if (vertex == 4) found_vertex4 = true;
        if (vertex == 5) found_vertex5 = true;
        if (vertex == 6) found_vertex6 = true;
        if (vertex == 7) found_vertex7 = true;
        if (vertex == 8) found_vertex8 = true;
      }
    }
    assert(found_vertex1);
    assert(found_vertex2);
    assert(found_vertex3);
    assert(found_vertex4);
    assert(found_vertex5);
    assert(found_vertex6);
    assert(found_vertex7);
    assert(found_vertex8);
  }

  cout << "Testing: getSubGraph" << endl;
  {
    // Let's begin by first creating a pentagon
    //
    //      -1c-
    //     |    |    6c    7c-8c
    //    5c    2c
    //     |    |
    //    4c -- 3c
    //
    auto GN0 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN1 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN2 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN3 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN4 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN5 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN6 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));
    auto GN7 = shared_ptr<GraphNode<string>>(new GraphNode<string>("C"));

    // Edge 1->2
    shared_ptr<Edge> ed12(new EdgeDirected(1, 2));
    // Edge 2->1
    shared_ptr<Edge> ed21(new EdgeDirected(2, 1));
    // Edge 2->3
    shared_ptr<Edge> ed23(new EdgeDirectedWeighted(2, 3, 1.0));
    shared_ptr<Edge> ed32(new EdgeDirectedWeighted(3, 2, 1.0));
    // Edge 3->4
    shared_ptr<Edge> ed34(new EdgeDirected(3, 4));
    shared_ptr<Edge> ed43(new EdgeDirected(4, 3));
    // Edge 4->5
    shared_ptr<Edge> ed45(new EdgeDirectedWeighted(4, 5, 1.0));
    shared_ptr<Edge> ed54(new EdgeDirectedWeighted(5, 4, 1.0));
    // Edge 5->1
    shared_ptr<Edge> ed51(new EdgeDirectedWeighted(5, 1, 1.0));
    shared_ptr<Edge> ed15(new EdgeDirectedWeighted(1, 5, 1.0));

    shared_ptr<Edge> ed78(new EdgeDirected(7, 8));
    shared_ptr<Edge> ed87(new EdgeDirected(8, 7));

    list<weak_ptr<Edge>> eds = {ed12, ed21, ed23, ed32, ed34, ed43,
                                ed54, ed45, ed51, ed15, ed78, ed87};

    unordered_map<int, weak_ptr<GraphNode<string>>> nds;
    nds[1] = GN0;
    nds[2] = GN1;
    nds[3] = GN2;
    nds[4] = GN3;
    nds[5] = GN4;
    nds[6] = GN5;
    nds[7] = GN6;
    nds[8] = GN7;

    Graph<string> gc(eds, nds);

    // The vertex 10 is not in the graph so should throw an error
    vector<int> faulty_vertices = {1, 10};

    bool throwError = false;
    try {
      gc.getSubGraph(faulty_vertices);
    } catch (...) {
      throwError = true;
    }
    assert(throwError);

    vector<int> new_graph_vertices = {1, 2, 7};
    auto        sub_gc             = gc.getSubGraph(new_graph_vertices);

    // The new graph should have 2 edges and 3 vertices
    auto vertices       = sub_gc->getVertices();
    bool found_vertex_1 = false;
    bool found_vertex_2 = false;
    bool found_vertex_7 = false;
    for (auto vertex : vertices) {
      if (vertex == 1) found_vertex_1 = true;
      if (vertex == 2) found_vertex_2 = true;
      if (vertex == 7) found_vertex_7 = true;
    }
    assert(found_vertex_1);
    assert(found_vertex_2);
    assert(found_vertex_7);

    auto edges_from_1 = sub_gc->getEdgesOriginatingFromVertex(1);
    auto edges_from_2 = sub_gc->getEdgesOriginatingFromVertex(2);
    auto edges_from_7 = sub_gc->getEdgesOriginatingFromVertex(7);
    assert(edges_from_1.size() == 1);
    auto ed_val12 = edges_from_1.at(0).lock();
    assert(*ed_val12 == *ed12);
    assert(edges_from_2.size() == 1);
    auto ed_val21 = edges_from_2.at(0).lock();
    assert(*ed_val21 == *ed21);
    assert(edges_from_7.size() == 0);
  }
  return 0;
}
