#ifndef GRAPH_H
#define GRAPH_H

#include<stddef.h>
#include "../../../shared_structs/value/value.h"

#define MAX_VERTICES 100000
#define MAX_EDGES 1000000

/* ---------- Definitions of structs ---------- */

typedef struct Vertex Vertex;
typedef struct Edge Edge;
typedef struct Graph Graph;

struct Vertex {
    Value* val;
};

struct Edge {
    Vertex* v1;
    Vertex* v2;
};

struct Graph {
    Vertex** vertices;
    Edge** edges;
};

/* ---------- Construct and free methods ---------- */
Vertex* constructVertex(Value* val);
Vertex* emptyVertex(void);
Edge* constructEdge(Value* val1, Value* val2);
Edge* emptyEdge(void);
Graph* constructGraph(Vertex** vertices, Edge** edges);
Graph* emptyGraph(void);
void freeVertex(Vertex* v);
void freeEdge(Edge* e);
void freeGraph(Graph* graph);

/* ---------- Basic graph operations ---------- */
Value** graphElements(Graph* graph);
int positions(Graph* graph);
int graphSwap(Graph* graph, Vertex* v1, Vertex* v2);
Vertex** vertices(Graph* graph);
Edge** edges(Graph* graph);
int removeVertex(Graph** graph, Vertex* v);
int removeEdge(Graph** graph, Edge* e)

/* ---------- Basic graph properties ---------- */
size_t graphSize(Graph* graph);
size_t numVertices(Graph* graph);
size_t numEdges(Graph* graph);
int isVertexInGraph(Graph* graph, Vertex* v);
int isEdgeInGraph(Graph* graph, Edge* e);
int areAdjacent(Vertex* v1, Vertex* v2);
int isTwoSidedEdge(Edge* e1, Edge* e2);
int isTwoSidedGraph(Graph* g);
int isEmpty(Graph* graph);
int isTree(Graph* graph);

#endif