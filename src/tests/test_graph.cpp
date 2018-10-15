
#include <iostream>
#include <string>
#include <cassert>
#include <list>
#include <vector>
#include <map>

#include "../../include/ugly/graph.hpp"
#include "../../include/ugly/graph_node.hpp"
#include "../edge/edge.hpp"

using namespace ugly;
using namespace std;

int main(void){

    cout << "Testing: Constructor " << endl;
    {
        GraphNode<string> GN0("B");
        GraphNode<string> GN1("C");
        GraphNode<string> GN2("A");

        Edge ed1(1,2);
        Edge ed2(2,3);

        list<Edge> eds = { ed1, ed2 };        
    
        map<int,GraphNode<string>> nds;
        nds[1]=GN0;
        nds[2]=GN1;
        nds[3]=GN2;
        Graph<string> gc(eds,nds);
        assert(gc.getLabel()=="A,B,C,");
        
    }

    cout << "Testing: == & != " << endl;
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

        Edge ed1(1,2);
        Edge ed2(2,3);
        Edge ed3(3,4);
        Edge ed4(4,5);
        Edge ed5(5,1);

        list<Edge> eds = { ed1, ed2, ed3, ed4, ed5 };        

        map<int,GraphNode<string>> nds;
        nds[1]= GN0;
        nds[2]= GN1;
        nds[3]= GN2;
        nds[4]= GN3;
        nds[5]= GN4;

        Graph<string> gc(eds,nds);
        assert( gc.getLabel()=="C,C,C,C,C,");

        Graph<string> gc2(eds,nds);

        assert(gc==gc2);
        //
        //      -1c-
        //     |    |
        //    5H    2c
        //     |    |
        //    4c -- 3c
        //     
        GraphNode<string> GN5("H");
        map<int,GraphNode<string>> nds2;
        nds2[1]= GN0;
        nds2[2]= GN1;
        nds2[3]= GN2;
        nds2[4]= GN3;
        nds2[5]= GN5;


        Graph<string> gc3(eds,nds2);
        assert( gc3.getLabel()=="C,C,C,C,H,");

        assert(gc3!=gc2);
    }

    return 0;
}
