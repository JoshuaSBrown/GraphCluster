
#include <iostream>
#include <string>
#include <cassert>
#include <list>
#include <vector>

#include "../../include/ugly/graph.hpp"
#include "../../include/ugly/graph_node.hpp"
#include "../edge/edge.hpp"

using namespace ugly;
using namespace std;

int main(void){

    cout << "Testing: Constructor " << endl;
    {
        GraphNode<string> GN0(1,"One");
        GraphNode<string> GN1(2,"Two");
        GraphNode<string> GN2(3,"One");

        Edge ed1(1,2);
        Edge ed2(2,3);

        list<Edge> eds = { ed1, ed2 };        
    
        vector<GraphNode<string>> nds = { GN0, GN1, GN2 };
        
        Graph<string> gc(eds,nds);
        cout << gc.getLabel() << endl;
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
        GraphNode<string> GN0(1,"C");
        GraphNode<string> GN1(2,"C");
        GraphNode<string> GN2(3,"C");
        GraphNode<string> GN3(4,"C");
        GraphNode<string> GN4(5,"C");

        Edge ed1(1,2);
        Edge ed2(2,3);
        Edge ed3(3,4);
        Edge ed4(4,5);
        Edge ed5(5,1);

        list<Edge> eds = { ed1, ed2, ed3, ed4, ed5 };        

        vector<GraphNode<string>> nds = { GN0, GN1, GN2, GN3, GN4 };

        Graph<string> gc(eds,nds);
        cout << gc.getLabel() << endl;

        Graph<string> gc2(eds,nds);

        assert(gc==gc2);

        //
        //      -1c-
        //     |    |
        //    5H    2c
        //     |    |
        //    4c -- 3c
        //     
        GraphNode<string> GN5(5,"H");
        vector<GraphNode<string>> nds2 = { GN0, GN1, GN2, GN3, GN5 };
        Graph<string> gc3(eds,nds2);

        assert(gc3!=gc2);
    }

    return 0;
}
