#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct tagVertex {
	struct inEdgeNode *inHead;
	struct outEdgeNode *outHead;
	int inDegree;
	int fresh;
	char vert;
}Vert;

typedef struct inEdgeNode {
	Vert* vert;
	Vert* inEdge;//�� �������� ���� ������ ����
	struct inEdgeNode* nextNode;
}inEdgeNode;//������ ������ ��Ƴ��� ���

typedef struct outEdgeNode {
	Vert* vert;
	Vert* outEdge;//�� vert���� ������ �����ϴ� ������ ����
	struct outEdgeNode* nextNode;
}outEdgeNode;//������ ������ ��Ƴ��� ���


Vert* insertVertex(char c) {
	Vert* tmp = (Vert*)malloc(sizeof(Vert));
	tmp->inHead = NULL;
	tmp->outHead = NULL;
	tmp->vert = c;
	tmp->inDegree = 0;
	tmp->fresh = 0;
	return tmp;
}

void insertDirectEdge(Vert* v1, Vert* v2) {
	outEdgeNode* tmp1 = (outEdgeNode*)malloc(sizeof(outEdgeNode));
	tmp1->vert = v1;
	tmp1->outEdge = v2;
	tmp1->nextNode = NULL;
	inEdgeNode* tmp2 = (inEdgeNode*)malloc(sizeof(inEdgeNode));
	tmp2->vert = v2;
	tmp2->inEdge = v1;
	tmp2->nextNode = NULL;
	if (v1->outHead == NULL) v1->outHead = tmp1;
	else {
		tmp1->nextNode = v1->outHead;
		v1->outHead = tmp1;
	}//v1�� ���Ⱓ�� �߰�
	if (v2->inHead == NULL) v2->inHead = tmp2;
	else {
		tmp2->nextNode = v2->inHead;
		v2->inHead = tmp2;
	}//v2�� ���԰��� �߰�
	v2->inDegree++;//������������ �������� ����
}//v1���� v2�� ���� ���� ���.

Vert** buildGraph(int N) {
	int i, M;
	Vert** myVert = (Vert**)malloc(sizeof(Vert*)*N);
	for (i = 0; i < N; i++) {
		char c;
		scanf("\n%c", &c);
		myVert[i] = insertVertex(c);
	}
	scanf("%d", &M);

	for (i = 0; i < M; i++) {
		char a;
		char b;
		Vert* v1 = NULL;
		Vert* v2 = NULL;
		scanf("\n%c %c", &a, &b);
		for (int j = 0; j < N; j++) {
			if (a == myVert[j]->vert) v1 = myVert[j];
			if (b == myVert[j]->vert) v2 = myVert[j];
		}
		insertDirectEdge(v1, v2);
	}
	return myVert;
}

void topologicalSort(Vert** graph, int N) {
	int i, x = 0, y = N - 1, z = 0, t = 0;
	int start = 0, end = 0;
	Vert** queue = (Vert**)calloc(sizeof(Vert**), N);
	char* topOrder = (char*)calloc(sizeof(char), N);

	for (i = 0; i < N; i++)
	{
		if (graph[i]->inDegree == 0) {
			queue[end] = graph[i];
			end++;
		}
	}
	
	while (start < end) {
		Vert* tmp = queue[start];
		tmp->fresh = 1;
		topOrder[start] = tmp->vert;
		start++;

		outEdgeNode* node = tmp->outHead;
		while (node!=NULL)
		{	
			if(node->outEdge->fresh == 0){
				node->outEdge->inDegree--;
				if (node->outEdge->inDegree == 0) {
					queue[end] = node->outEdge;
					end++;
				}
			}			
			node = node->nextNode;
		}
	}
	if (end < N-1) printf("0\n");
	else {
		for (i = 0; i < N; i++) {
			printf("%c ", topOrder[i]);
		}
	}
}

int main() {
	int N, i, x = 0, y = 0;
	printf("�ӳ�?");
	scanf("%d", &N);//������ ����
	Vert** myGraph = buildGraph(N);
	printf("��������\n");
	for (i = 0; i < N; i++) {
		printf("%d\n", myGraph[i]->inDegree);
	}
	return 0;
}