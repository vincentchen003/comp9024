//
//  graph.h
//  comp9024assi2
//
//  Created by apple on 2018/10/2.
//  Copyright © 2018年 apple. All rights reserved.
//

#ifndef graph_h
#define graph_h

#include <stdio.h>

#endif /* graph_h */
// Graph ADT interface ... COMP9024 18s2
#include <stdbool.h>

typedef struct GraphRep *Graph;

// vertices are ints
typedef int Vertex;

// edges are pairs of vertices (end-points)
typedef struct Edge {
    Vertex v;
    Vertex w;
} Edge;

Graph newGraph(int);
int   numOfVertices(Graph);
void  insertEdge(Graph, Edge);
void  removeEdge(Graph, Edge);
bool  adjacent(Graph, Vertex, Vertex);
void  showGraph(Graph);
void  freeGraph(Graph);
