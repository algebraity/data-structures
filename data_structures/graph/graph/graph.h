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


/* ---------- Basic graph operations ---------- */


/* ---------- Basic graph properties ---------- */


#endif