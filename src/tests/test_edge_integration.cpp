
#include <cassert>
#include <iostream>
#include <list>
#include <set>
#include <unordered_map>
#include <vector>

#include "../../include/ugly/edge_directed.hpp"
#include "../../include/ugly/edge_directed_weighted.hpp"
#include "../../include/ugly/edge_undirected.hpp"
#include "../../include/ugly/edge_weighted.hpp"
#include "../libugly/edge/edge.hpp"

using namespace ugly;
using namespace std;

int main() {

  cout << "Beginning Test" << endl;
  cout << "Testing: makeEdge" << endl;
  {
    EdgeUndirected edgeundirected(2, 3);
    auto edgeundirected_ptr = make_shared<EdgeUndirected>(edgeundirected);
    EdgeDirected edgedirected(4, 5);
    auto         edgedirected_ptr = make_shared<EdgeDirected>(edgedirected);
    EdgeWeighted edgeweighted(1, 3, 2.3);
    auto         edgeweighted_ptr = make_shared<EdgeWeighted>(edgeweighted);
    EdgeDirectedWeighted edgedirectedweighted(4, 3, 5.0);
    auto                 edgedirectedweighted_ptr =
        make_shared<EdgeDirectedWeighted>(edgedirectedweighted);

    cout << "make undirected edge" << endl;
    shared_ptr<Edge> edgeNew = makeEdge<EdgeUndirected>(edgeundirected_ptr);
    assert((*edgeNew) == edgeundirected);
    cout << "make directed edge" << endl;
    shared_ptr<Edge> edgeNew2 = makeEdge<EdgeDirected>(edgedirected_ptr);
    assert((*edgeNew2) == edgedirected);
    cout << "make weighted edge" << endl;
    shared_ptr<Edge> edgeNew3 = makeEdge<EdgeWeighted>(edgeweighted_ptr);
    assert((*edgeNew3) == edgeweighted);
    auto edgeweighted3 = static_pointer_cast<EdgeWeighted>(edgeNew3);
    cout << "Edge weight " << edgeweighted3->getWeight() << endl;
    cout << "make directed weighted edge" << endl;
    shared_ptr<Edge> edgeNew4 =
        makeEdge<EdgeDirectedWeighted>(edgedirectedweighted_ptr);
    assert((*edgeNew4) == edgedirectedweighted);
  }
  return 0;
}
