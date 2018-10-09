
#include <iostream>
#include <string>
#include <cassert>

#include "GraphNode.hpp"

using namespace ugly;
using namespace std;

int main(void){
    
    cout << "Testing: Contstructor" << endl;
    {
        GraphNode<string,double> GN2(1,"One",1.1);
        GraphNode<double,int,double,string> GN3(2,3.4,1,45,"two");
    }
    
    cout << "Testing; == && !=" << endl;
    {
        GraphNode<string,double> GN2(1,"One",1.1);
        GraphNode<string,double> GN4(2,"One",1.1);
        assert(GN2==GN2);
        assert(GN2==GN4);

        GraphNode<string,double> GN3(2,"Two",-1.1);
        assert(GN2!=GN3);
    }

    cout << "Testing: < && >" << endl;
    {
        GraphNode<string,double,int> GN0(1,"One",1.1,4);
        GraphNode<string,double,int> GN1(2,"Two",1.1,4);
        GraphNode<string,double,int> GN2(3,"One",2.3,4);

        assert(GN0<GN1);
        assert(GN1>GN0);
        assert(GN0<GN2);
        assert(GN2>GN0);
    }

    cout << "Testing: str()"<< endl;
    {
        GraphNode<string,double,int> GN0(1,"One",1.3,4);
        string var = GN0.str();
        cout << var << endl; 
    }

    return 0;
}
