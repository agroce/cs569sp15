#include <stdio.h>

#include "fixdijkstra.h"

//#define GRAPHSIZE 2048
//#define INFINITY GRAPHSIZE*GRAPHSIZE
#define MAX(a, b) ((a > b) ? (a) : (b))

int e; /* The number of nonzero edges in the graph */
int nodeCount; /* The number of nodes in the graph */
long d[GRAPHSIZE]; /* d[i] is the length of the shortest path between the source (s) and node i */
int prev[GRAPHSIZE]; /* prev[i] is the node that comes right before i in the shortest path from the source to i*/


/*
 * Prints the shortest path from the source to dest.
 *
 * dijkstra(int) MUST be run at least once BEFORE
 * this is called
 */
void checkPath(int dest, int source) {
	if (dest == source) {
		printf("LOG: source = %d\n", source);
		return;
	}
	int v;
	long shortestPathCost = d[dest];
	long traversalCost = 0;
	printf ("LOG: shortestPathCost = %d\n", d[dest]);
	if (prev[dest] == -1) {
	  printf ("LOG: prev = -1 for %d, checking\n", dest);
	  int path[GRAPHSIZE];
	  int i;
	  path[0] = source;
	  for (i = 1; i < GRAPHSIZE; i++) {
	    path[i] = nondet_int();
	    __CPROVER_assume((path[i] >= 0) && (path[i] <= nodeCount));
	  }
	  int goodPath = 0;
	  for (i = 1; i < GRAPHSIZE; i++) {
	    __CPROVER_assume(dist[path[i-1]][path[i]] < INFINITY);
	    printf ("LOG: path[%d] = %d\n", i, path[i]);
	    if (path[i] == dest) {
	      goodPath = 1;
	      break;
	    }
	  } 
	  assert(goodPath == 0);
	  return;
	}

	for (v = dest; v!=source; v = prev[v]) {
		printf("LOG: v=%d, prev[v]=%d, nodecount=%d", v, prev[v], nodeCount);
		assert((v>=0 && v<=nodeCount) || (prev[v] == -1));
		traversalCost += dist[prev[v]][v];
		printf ("LOG: dist[%d][%d] = %d\n", prev[v], v, dist[prev[v]][v]);
		printf ("LOG: traversal cost so far, %d\n", traversalCost);
		if (prev[v] == -1) return;
	}
	assert(v == source);
	assert(shortestPathCost == traversalCost);
}

int nondet_int();

int main(int argc, char *argv[]) {
	int i, j;
	int u, v, w;

	//FILE *fin = fopen("dist.txt", "r");
	//fscanf(fin, "%d", &e);
	e = nondet_int();
	__CPROVER_assume (e < (GRAPHSIZE * GRAPHSIZE));
	printf ("LOG: e = %d\n", e);
	for (i = 0; i < GRAPHSIZE; ++i) {
		for (j = 0; j < GRAPHSIZE; ++j) {
			dist[i][j] = 0;
		}
	}
	nodeCount = -1;
	for (i = 0; i < e; ++i) {
		//fscanf(fin, "%d%d%d", &u, &v, &w);
		u = nondet_int();
		v = nondet_int();
		__CPROVER_assume (u >= 0 && (u <= (GRAPHSIZE-1)) && v>=0 && (v <= (GRAPHSIZE-1)));
		/* ADG */ __CPROVER_assume(u != v);
		w = nondet_int();
		__CPROVER_assume (w <= INFINITY);
		__CPROVER_assume (w >= 0);
		dist[u][v] = w;
		nodeCount = MAX(u, MAX(v, nodeCount));
		printf ("LOG: dist[%d][%d] = %d\n", u, v, w);
		printf ("LOG: nodeCount = %d\n", nodeCount);
	}

	int graphSize;
	int source;

	source = 0;

	dijkstra(source, d, prev, nodeCount);

	printf("\n");
	for (i = 0; i <= nodeCount; ++i) {
		printf("LOG: d[%d]=%d", i, d[i]);
		checkPath(i, source);
		assert(d[i] >= 0);
		assert(d[i] <= INFINITY);
	}
	//assert(0);
	return 0;
}

