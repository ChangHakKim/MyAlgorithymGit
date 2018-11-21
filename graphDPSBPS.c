#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

typedef struct tagVertex {
	int num;
	int fresh;//�湮�ߴ� ��忴���� Ȯ���ϱ� ����
	struct tagNode *head;
}Vertex;//����

typedef struct tagNode {
	struct tagNode* nextNode;
	struct tagEdge* edge;
	struct tagVertex* vert;
}Node;

typedef struct tagEdge {
	int weight;//������ �켱����. ������ �ǹ̾���.
	int fresh;//�湮�ߴ� ��忴���� Ȯ���ϱ� ����
	Vertex* vert1;
	Vertex* vert2;
}Edge;//����

Vertex* makeVertexNode(int i) {
	Vertex* vert = (Vertex*)malloc(sizeof(Vertex));
	vert->num = i;
	vert->fresh = 0;//���� �湮���� ����
	vert->head = (Node*)malloc(sizeof(Node));//dummy head node;
	vert->head->vert = vert;
	vert->head->edge = NULL;
	vert->head->nextNode = NULL;
	return vert;
}

Edge* makeEdgeNode(int a, int b,Vertex** vert) {
	Edge* edge = (Edge*)malloc(sizeof(Edge));
	if (a < b) swap(&a, &b);//a�� b�� ���ų� ����.
	edge->vert1 = vert[a - 1];
	edge->vert2 = vert[b - 1];
	edge->fresh = 0;//���� �湮���� ����
	edge->weight = 0; //dummy
	return edge;
}

void insertNode(Vertex* vert, Edge* edge) {
	Node* tmp = vert->head;
	int x;
	if (vert->num != edge->vert1->num) x = edge->vert1->num;
	else x = edge->vert2->num;
	while (tmp->nextNode != NULL) {
		int x2;
		if (vert->num != tmp->nextNode->edge->vert1->num) 
			x2 = tmp->nextNode->edge->vert1->num;
		else x2 = tmp->nextNode->edge->vert2->num;
		if (x < x2) break;
		tmp = tmp->nextNode;
	}
	Node *tmp2 = (Node*)malloc(sizeof(Node));
	tmp2->edge = edge;
	tmp2->vert = vert;
	tmp2->nextNode = tmp->nextNode;
	tmp->nextNode = tmp2;
}

void DepthFirstSearch(Vertex* vert) {
	printf("%d\n",vert->num);
	vert->fresh = 1;//��尡 ���Ǿ��ٴ� ���� ǥ��.
	Node* tmp = vert->head;
	while (tmp->nextNode != NULL) {
		tmp = tmp->nextNode;
		if (tmp->edge->fresh == 1) continue;
		else {
			tmp->edge->fresh = 1;
			if (tmp->edge->vert1 == vert && tmp->edge->vert2->fresh == 0) DepthFirstSearch(tmp->edge->vert2);
			else if(tmp->edge->vert1->fresh == 0) DepthFirstSearch(tmp->edge->vert1);
		}
	}
}

void BreadthFirstSearch(Vertex* vert,int N) {
	printf("%d\n", vert->num);
	vert->fresh = 1;
	Vertex** oldHeap = (Vertex**)calloc(sizeof(Vertex*),N);
	Vertex** newHeap = (Vertex**)calloc(sizeof(Vertex*),N);
	int x = 0, y = 0, z = 0;//�� ��� �迭�� ��带 �߰��ϱ� ���� ����. ó������ �Ѱ� �������.
	oldHeap[x] = vert;//ó�� �ʱ�ȭ.
	x++;
	while (1) {
		y = 0, z = 0;
		for (y = 0; y < x; y++)
		{
			Node* tmp = oldHeap[y]->head;
			while (tmp->nextNode != NULL) {
				tmp = tmp->nextNode;
				if (tmp->vert == tmp->edge->vert1) {
					if (tmp->edge->vert2->fresh == 1) continue;
					else {
						newHeap[z] = tmp->edge->vert2;
						z++;
						tmp->edge->vert2->fresh = 1;
					}
				}
				else if (tmp->edge->vert1->fresh == 1) continue;
				else {
					newHeap[z] = tmp->edge->vert1;
					z++;
					tmp->edge->vert1->fresh = 1;
				}
			}
		}//newvert�� ����.
		if (z == 0) break;
		x = z;
		for (y = 0; y < x; y++) {
			oldHeap[y] = newHeap[y];
		}
		int t = 0;
		while (t < z) {
			printf("%d\n", newHeap[t]->num);
			t++;
		}
	}
	free(oldHeap);
	free(newHeap);
}

void printEdge(Vertex** vert) {
	int n;
	scanf("%d", &n);
	Node *tmp = vert[n]->head->nextNode;
	while (tmp != NULL) {
		int result;
		if (tmp->edge->vert1->num == vert[n]->num) result = tmp->edge->vert2->num;
		else result = tmp->edge->vert1->num;
		printf(" %d ����ġ: %d\n", result, tmp->edge->weight);
		tmp = tmp->nextNode;
	}
}

int main() {
	int N, M, S,i;
	printf("��� ���ڿ� ���� ���ڸ� �Է����ּ���:\n");//����Ʈ �������ε� ���� �� �ִ�.
	scanf("%d %d %d", &N, &M, &S);//��� ����,���� ����,�����ϴ� ����� ����
	Vertex** vert = (Vertex**)malloc(sizeof(Vertex*)*N);//N���� ��带 ������ �ִ� �迭
	Edge** edge = (Edge**)malloc(sizeof(Edge*)*M);//M���� ������ ������ �ִ� �迭

	for (i = 0; i < N; i++) vert[i] = makeVertexNode(i+1);//������ ����� �ʱ�ȭ
	for (i = 0; i < M; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		edge[i] = makeEdgeNode(a, b, vert);
		insertNode(vert[a - 1], edge[i]);
		if (edge[i]->vert1 != edge[i]->vert2) insertNode(vert[b - 1], edge[i]);
	}//������ ����� �ʱ�ȭ.


	printf("DepthFirstSearch\n");
	DepthFirstSearch(vert[S-1]);

	for (i = 0; i < N; i++) {
		vert[i]->fresh = 0;
	}
	for (i = 0; i < M; i++) {
		edge[i]->fresh = 0;
	}

	printf("\nBreadthFirstSearch\n");
	BreadthFirstSearch(vert[S - 1],N);
	scanf("%d", &i);
	return 0;
}