#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 999999999;

typedef struct tagVertex {
	int vertNum;
	int level;//奄層 骨是拭辞 杖原蟹 搾遂戚 琶推廃走
	struct tagEdge* parent;//闘軒拭辞 切重税 採乞 娃識
}Vert;

typedef struct tagEdge {
	int height;//亜掻帖
	struct tagVertex* vert1;
	struct tagVertex* vert2;
}Edge;

Vert* opposite(Edge *edge, Vert* vert) {

	if (edge->vert1 == vert) return edge->vert2;
	else return edge->vert1;
}


Vert* removeMin(Vert** queue, int x) {
	int min = MAX, mini = 0, i;
	Vert* minVert;
	for (i = 0; i < x; i++) {
		if (min > queue[i]->level) {
			min = queue[i]->level;
			minVert = queue[i];
			mini = i;
		}
	}
	for (i = mini; i < x - 1; i++) {
		queue[i] = queue[i + 1];
	}
	return minVert;
}//図楕生稽 哀 呪系 鏑.


int main() {
	int i, j, N, M;
	int **arr;
	Edge **edge;//娃識引 亜掻帖 匂敗馬澗 楳慶
	Vert **vert;
	scanf("%d %d\n", &N, &M);
	arr = (int**)malloc(sizeof(int*)*N);
	edge = (Edge**)malloc(sizeof(Edge*)*M);//M鯵税 娃識
	vert = (Vert**)malloc(sizeof(Vert*)*N);//N鯵税 舛繊


	for (i = 0; i < N; i++) {
		arr[i] = (int*)malloc(sizeof(int)*N);
		vert[i] = (Vert*)calloc(sizeof(Vert), N);
		vert[i]->level = 9999999;//max稽 竺舛.
		vert[i]->parent = NULL;//採乞澗 NULL稽 竺舛.
		vert[i]->vertNum = i + 1;
		for (j = 0; j < N; j++) {
			arr[i][j] = 0;//娃識精 蒸澗 依生稽, 亜掻帖澗 0生稽 段奄鉢
		}
	}//舛繊 段奄鉢
	for (i = 0; i < M; i++) {
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		arr[x - 1][y - 1] = i + 1, arr[y - 1][x - 1] = i + 1;
		//i腰属 edge虞澗 社軒. edge[i]稽 達聖呪赤製.
		edge[i] = (Edge*)malloc(sizeof(Edge));
		edge[i]->height = z;
		edge[i]->vert1 = vert[x - 1];
		edge[i]->vert2 = vert[y - 1];
	}//娃識 段奄鉢

	Vert** queue = (Vert**)malloc(sizeof(Vert*)*N);//N鯵研 隔聖 呪 赤澗 queue 竺舛
	int x = 0;//泥拭 級嬢亜 赤澗 据社亜 護鯵昔走 硝形捜. 廃鯵亀 蒸聖 凶 0
	vert[0]->level = 0;//0腰 舛繊税 level精 0

	for (i = 0; i < N; i++) {
		queue[x] = vert[i];
		x++;
	}
	int result = 0;
	while (x > 0) {
		int flag = 0;
		Vert* u = removeMin(queue, x);
		printf(" %d", u->vertNum);
		x--;
		if (u->parent != NULL) {
			//			printf("%dしししししし\n", u->parent->height);
			result += u->parent->height;
		}
		for (i = 0; i<N; i++) {
			if (arr[u->vertNum - 1][i] != 0) {
				Vert* tmp = opposite(edge[arr[u->vertNum - 1][i] - 1], u);

				flag = -1;
				for (j = 0; j < x; j++) {
					if (queue[j] == tmp) {
						flag = j;
						break;
					}
				}
				if (flag == -1) continue;
				if (tmp->level > edge[arr[u->vertNum - 1][i] - 1]->height) {
					tmp->level = edge[arr[u->vertNum - 1][i] - 1]->height;
					tmp->parent = edge[arr[u->vertNum - 1][i] - 1];
					queue[flag]->level = edge[arr[u->vertNum - 1][i] - 1]->height;
				}
			}
		}

	}
	printf("\n%d", result);
	scanf("%d", &i);
	return 0;
}