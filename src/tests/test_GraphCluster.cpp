
#include <iostream>
#include <string>
#include <cassert>
#include <list>
#include <vector>

#include "GraphCluster.hpp"
#include "../CPP_GraphNode/GraphNode.hpp"
#include "../CPP_EdgeClass/EdgeClass.hpp"

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
        
        GraphCluster<string> gc(eds,nds);
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

        GraphCluster<string> gc(eds,nds);
        cout << gc.getLabel() << endl;

        GraphCluster<string> gc2(eds,nds);

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
        GraphCluster<string> gc3(eds,nds2);

        assert(gc3!=gc2);
    }

    return 0;
}
