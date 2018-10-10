
#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#include <set>
#include <unordered_map>

#include "../libugly/edge/edge.hpp"

using namespace ugly;
using namespace std;

int main(){

    cout << "Beginning Test" << endl;
    cout << "Testing: Constructor" << endl;
    { 
        Edge edge(2,3);
    }

    cout << "Testing: operator << " << endl;
    {
        Edge edge(2,3);
        cout << edge << endl; 
    }

    cout << "Testing: ==" << endl;
    {
        Edge edge(2,3);
        Edge edge2(2,4);
        Edge edge3(3,2);
        assert(edge==edge);
        assert(edge==edge3);
        assert((edge==edge2)==0);
    }

    cout << "Testing: !=" << endl;
    {
        Edge edge(2,3);
        Edge edge2(2,4);
        assert(edge!=edge2);
        assert((edge!=edge)==0);
    }

    cout << "Testing: getVertex1 and getVertex2" << endl;
    {
        Edge edge(2,3);
        assert(edge.getVertex1()==2);
        assert(edge.getVertex2()==3);
    }

    cout << "Testing: < " << endl;
    {
        Edge edge1(1,2);
        Edge edge2(2,1);
        assert(!(edge1<edge2));
        Edge edge3(3,0);
        assert(edge3<edge1);
        Edge edge4(1,5);
        assert(edge1<edge4);
        Edge edge5(2,2);
        assert(edge4<edge5);
    }

    cout << "Testing: > " << endl;
    {
       
        Edge edge1(1,2);
        Edge edge2(2,1);
        assert(!(edge1>edge2));
        Edge edge3(3,0);
        assert(!(edge3>edge1));
    }

    cout << "Testing: Edge in set" << endl;
    {
        set<Edge> e_set;
        Edge edge(23,43);
        e_set.insert(edge);
    }

    cout << "Testing: Edge in unordered_map" << endl;
    {

        unordered_map<int,Edge> e_map;
        Edge edge(1,32);
        e_map[2] = edge;
    }
  return 0;
}
