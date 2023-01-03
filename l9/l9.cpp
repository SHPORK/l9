#define _CRT_SECURE_NO_WARNINGS
#include "time.h"
#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"
#include <queue>
#include <iostream>
using namespace std;

int level = 0;
int levelDFS = 0, order = 0;

void BFSD(int v, int m, int** a, int* dist, int* lvl) {
	queue <int> q;
	q.push(v);
	dist[v] = 0;
	while (!q.empty()) {
		v = q.front();
		q.pop();
		printf("%3d|", v);
		lvl[level] = v;
		level++;
		for (int i = 1; i < m; i++) {
			if (a[v][i] == 1 && dist[i] == -1) {
				q.push(i);
				dist[i] = dist[v] + 1;
			}
		}
	}
}


void DFS(int v, int* vis, int m, int** a, int* lvlDFS) {
	vis[v] = 1;
	printf("%3d|", v);
	lvlDFS[order] = levelDFS;
	order++;
	for (int i = 0; i < m; i++) {
		if (a[v][i] == 1 && vis[i] == 0) {
			levelDFS++;
			DFS(i, vis, m, a, lvlDFS);
		}
	}
	levelDFS--;
}

int main(void)
{
	int m, distCount = 0;

	printf("Enter amount of peaks: \n");
	scanf("%d", &m);

	int* chck;
	chck = (int*)malloc(m * sizeof(int));
	for (int i = 0; i < m; i++) {
		chck[i] = 0;
	}
	int** a;
	a = (int**)malloc((m) * sizeof(int*));
	srand(time(NULL));

	// (1)
	printf("   ");
	for (int j = 0; j < m; j++) {  // цикл по столбцам
		printf("%5d", (j));
	}
	printf("\n   ");
	for (int j = 0; j < m; j++) {  // цикл по столбцам
		printf("-----");
	}
	for (int i = 0; i < m; i++) {
		a[i] = (int*)malloc(m * sizeof(int));
		for (int j = 0; j < m; j++) a[i][j] = 0;
	}

	for (int i = 0; i < m; i++) {
		for (int j = i + 1; j < m; j++) {
			if (i == 0) {
				a[j][i] = a[i][j] = rand() % 2;
				if (a[i][j] == 1) chck[j] = 1;
			}
			else if (chck[j] != 1) {
				a[j][i] = a[i][j] = rand() % 2;
				chck[j] = 1;
			}
		}
	}
	for (int i = 0; i < m; i++) {
		printf("\n %d |", (i)); // цикл по столбцам
		for (int j = 0; j < m; j++) {
			printf("%4d ", a[i][j]);
		}
	}

	int v = 0, vDist = v;
	int* dist, * lvl, * actualDist, * lvlDFS;
	dist = (int*)malloc(m * sizeof(int));
	lvl = (int*)malloc(m * sizeof(int));
	lvlDFS = (int*)malloc(m * sizeof(int));
	actualDist = (int*)malloc(m * sizeof(int));
	for (int i = 0; i < m; i++) {
		dist[i] = -1;
		actualDist[i] = 0;
		lvlDFS[i] = 0;
		lvl[i] = 0;
	}
	printf("\n\nBFSD\n");
	BFSD(v, m, a, dist, lvl);

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			if (lvl[i] == j) {
				actualDist[distCount] = dist[j];
				distCount++;
			}
		}
	}

	printf("\n");
	printf("%3d|", actualDist[vDist]);
	for (int i = 1; i < m; i++) {
		if (actualDist[i] != 0) printf("%3d|", actualDist[i]);
	}
	//----------
	v = 0;
	int* vis;
	vis = (int*)malloc(m * sizeof(int));
	for (int i = 0; i < m; i++) {
		vis[i] = 0;
	}
	printf("\n\nDFSD\n");

	DFS(v, vis, m, a, lvlDFS);
	printf("\n");
	printf("%3d|", lvlDFS[0]);
	for (int i = 0; i < m; i++) {
		if (lvlDFS[i] != 0) printf("%3d|", lvlDFS[i]);
	}

	free(a);
	free(dist);
	free(lvl);
	free(vis);
	free(chck);
	getchar();
	getchar();
	return(0);
}

