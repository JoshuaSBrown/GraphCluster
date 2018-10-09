
#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#include <set>
#include <unordered_map>

#include "EdgeClass.hpp"

using namespace std;

int main(){

    cout << "Beginning Test" << endl;
    cout << "Testing: Constructor" << endl;
    { 
        Edge ed(2,3);
    }

    cout << "Testing: operator << " << endl;
    {
        Edge ed(2,3);
        cout << ed << endl; 
    }

    cout << "Testing: ==" << endl;
    {
        Edge ed(2,3);
        Edge ed2(2,4);
        Edge ed3(3,2);
        assert(ed==ed);
        assert(ed==ed3);
        assert((ed==ed2)==0);
    }

    cout << "Testing: !=" << endl;
    {
        Edge ed(2,3);
        Edge ed2(2,4);
        assert(ed!=ed2);
        assert((ed!=ed)==0);
    }

    cout << "Testing: getV1 and getV2" << endl;
    {
        Edge ed(2,3);
        assert(ed.getV1()==2);
        assert(ed.getV2()==3);
    }

    cout << "Testing: < " << endl;
    {
        Edge ed1(1,2);
        Edge ed2(2,1);
        assert(!(ed1<ed2));
        Edge ed3(3,0);
        assert(ed3<ed1);
        Edge ed4(1,5);
        assert(ed1<ed4);
        Edge ed5(2,2);
        assert(ed4<ed5);
    }

    cout << "Testing: > " << endl;
    {
       
        Edge ed1(1,2);
        Edge ed2(2,1);
        assert(!(ed1>ed2));
        Edge ed3(3,0);
        assert(!(ed3>ed1));
    }

    cout << "Testing: Edge in set" << endl;
    {
        set<Edge> e_set;
        Edge ed(23,43);
        e_set.insert(ed);
    }

    cout << "Testing: Edge in unordered_map" << endl;
    {

        unordered_map<int,Edge> e_map;
        Edge ed(1,32);
        e_map[2] = ed;
    }
  return 0;
}
