#include <iostream>
#include "AdjacencyMatrix.h"
#include "List.h"
using namespace std; 

int main()
{ 
  AdjacencyMatrix airlines;
  airlines.Dijkstra();
  return 0;
}


/*SAMPLE OUTPUT
[hxu65@hills ~]$ ./a.out
Cost from SFO to SFO is $0
Cost from SFO to LAX is $120
Cost from SFO to LAS is $150
Cost from SFO to PHX is $195
Cost from SFO to DEN is $345
Cost from SFO to JFK is $470
*/