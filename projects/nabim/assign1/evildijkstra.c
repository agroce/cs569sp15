#include "dijkstra.h"

void dijkstra(int source, long dist[GRAPHSIZE][GRAPHSIZE], long d[], int prev[], int nodeCount) {
	int i, k, mini;
	int visited[GRAPHSIZE];

	for (i = 1; i <= nodeCount; ++i) {
		d[i] = INFINITY;
		prev[i] = -1; /* no path has yet been found to i */
		visited[i] = 0; /* the i-th element has not yet been visited */
	}

	d[source] = 0;

	for (k = 1; k <= nodeCount; ++k) {
		mini = -1;
		for (i = 1; i <= nodeCount; ++i)
			if (!visited[i] && ((mini == -1) || (d[i] > d[mini])))
				mini = i;

		visited[mini] = 1;

		for (i = 1; i <= nodeCount; ++i)
			if (dist[mini][i])
				if (d[mini] + dist[mini][i] <  d[i]) {
					d[i] = d[mini] + dist[mini][i];
					prev[i] = mini;
				}
	}
}
