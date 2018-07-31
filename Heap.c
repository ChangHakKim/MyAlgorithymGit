#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct tagHeapNode {
	int element;
}HeapNode;//�迭�� ����
//�ڽ��� �ּҴ� 2k,2k+1�� ����.(index�� 1���� ����)
//�θ��� �ּҴ� 2�� ������ ��.(index 0�� ������� �ʱ� ������ �ణ ������)

typedef struct tagHead {
	HeapNode *Nodes;
	int Capacity;
	int UsedSize;
}Heap;


void Heap_SwapNodes(Heap *H, int index1, int index2) {
	int Size = sizeof(HeapNode);
	HeapNode *tmp = (HeapNode*)malloc(sizeof(HeapNode));
	memcpy(tmp, &H->Nodes[index1], Size);
	memcpy(&H->Nodes[index1], &H->Nodes[index2], Size);
	memcpy(&H->Nodes[index2], tmp, Size);
	free(tmp);
}

Heap* Heap_Create(int Size) {
	Heap *NewHeap = (Heap*)malloc(sizeof(Heap));
	NewHeap->Capacity = Size;
	NewHeap->UsedSize = 1;//0�� index�� ������� ����.
	NewHeap->Nodes = (HeapNode*)malloc(sizeof(HeapNode)*NewHeap->Capacity);
	return NewHeap;
}

void Heap_Destroy(Heap *H) {
	free(H->Nodes);
	free(H);
}

void Heap_Insert(Heap *H, int element) {
	int CurrentPosition = H->UsedSize;
	int ParentPosition = CurrentPosition/2;//�θ� ��带 ã��.
	if (H->UsedSize == H->Capacity) {
		H->Capacity *= 2;
		H->Nodes = (HeapNode*)realloc(H->Nodes, sizeof(HeapNode)*H->Capacity);
	}
	H->Nodes[CurrentPosition].element = element;

	while (CurrentPosition > 0 && H->Nodes[CurrentPosition].element < H->Nodes[ParentPosition].element) {
		Heap_SwapNodes(H, CurrentPosition, ParentPosition);
		CurrentPosition/=2;//�θ� ����.
		ParentPosition/=2;//�θ��� �θ� ����
	}
	H->UsedSize++;
}

void Heap_DeleteMin(Heap *H) {
	int ParentPosition = 1;
	int LeftPosition;
	int RightPosition;
	int Size = sizeof(HeapNode);
	H->UsedSize--;
	Heap_SwapNodes(H, 1, H->UsedSize);
	LeftPosition = ParentPosition * 2;
	RightPosition = ParentPosition * 2 + 1;

	while (1) {
		int SelectedChild;
		if (LeftPosition >= H->UsedSize) break;
		if (RightPosition >= H->UsedSize) SelectedChild = LeftPosition;
		else {
			if (H->Nodes[LeftPosition].element > H->Nodes[RightPosition].element) SelectedChild = RightPosition;
			else SelectedChild = LeftPosition;
		}
		if (H->Nodes[SelectedChild].element < H->Nodes[ParentPosition].element) {
			Heap_SwapNodes(H, ParentPosition, SelectedChild);
			ParentPosition = SelectedChild;
		}
		else break;
		LeftPosition = ParentPosition * 2;
		RightPosition = ParentPosition * 2 + 1;

	}
}

void Heap_PrintNodes(Heap *H) {
	int t = 1;
	for (int i = 1; i < H->UsedSize; i++) {
		printf("%d ", H->Nodes[i].element);
		if (i == t) {
			printf("\n");
			t = t*2+1;
		}
	}
}


int main() {
	int i=1;
	Heap *H = Heap_Create(1024);
	while (1) {
		printf("������ ��带 �Է����ּ���. 0�� �Է��ϸ� �����մϴ�:");
		scanf("%d", &i);
		if (i < 1) break;
		Heap_Insert(H, i);
	}
	Heap_PrintNodes(H);
	printf("\n�ּ� ��� �Ѱ��� �������ϴ�\n");
	Heap_DeleteMin(H);
	Heap_PrintNodes(H);
	printf("\n�ּ� ��� �Ѱ��� �������ϴ�\n");
	Heap_DeleteMin(H);
	Heap_PrintNodes(H);
	scanf("%d", &i);
	return 0;
}