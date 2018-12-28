#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 999999999;

typedef struct tagVertex {
	int vertNum;
	int level;//���� �������� �󸶳� ����� �ʿ�����
	struct tagEdge* parent;//Ʈ������ �ڽ��� �θ� ����
}Vert;

typedef struct tagEdge {
	int height;//����ġ
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
}//�������� �� ���� ŭ.


int main() {
	int i, j, N, M;
	int **arr;
	Edge **edge;//������ ����ġ �����ϴ� ���
	Vert **vert;
	scanf("%d %d\n", &N, &M);
	arr = (int**)malloc(sizeof(int*)*N);
	edge = (Edge**)malloc(sizeof(Edge*)*M);//M���� ����
	vert = (Vert**)malloc(sizeof(Vert*)*N);//N���� ����


	for (i = 0; i < N; i++) {
		arr[i] = (int*)malloc(sizeof(int)*N);
		vert[i] = (Vert*)calloc(sizeof(Vert), N);
		vert[i]->level = 9999999;//max�� ����.
		vert[i]->parent = NULL;//�θ�� NULL�� ����.
		vert[i]->vertNum = i + 1;
		for (j = 0; j < N; j++) {
			arr[i][j] = 0;//������ ���� ������, ����ġ�� 0���� �ʱ�ȭ
		}
	}//���� �ʱ�ȭ
	for (i = 0; i < M; i++) {
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		arr[x - 1][y - 1] = i + 1, arr[y - 1][x - 1] = i + 1;
		//i��° edge��� �Ҹ�. edge[i]�� ã��������.
		edge[i] = (Edge*)malloc(sizeof(Edge));
		edge[i]->height = z;
		edge[i]->vert1 = vert[x - 1];
		edge[i]->vert2 = vert[y - 1];
	}//���� �ʱ�ȭ

	Vert** queue = (Vert**)malloc(sizeof(Vert*)*N);//N���� ���� �� �ִ� queue ����
	int x = 0;//ť�� �� �ִ� ���Ұ� ����� �˷���. �Ѱ��� ���� �� 0
	vert[0]->level = 0;//0�� ������ level�� 0

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
			//			printf("%d������������\n", u->parent->height);
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