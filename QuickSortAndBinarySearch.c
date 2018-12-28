#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void Swap(int *arr, int x, int y) {
	int tmp = arr[x];
	arr[x] = arr[y];
	arr[y] = tmp;
}

int partition(int *arr, int left, int right) {
	int x1 = rand() % (right - left + 1) + left, x2 = rand() % (right - left + 1) + left, x3 = rand() % (right - left + 1) + left, pivot;
	if (left + 2 > right) pivot = x1;//���� �ΰ� �����϶� ������ ���ʰŰ� pivot
	else {
		if ((arr[x1] >= arr[x2] && arr[x3] >= arr[x1]) || (arr[x1] <= arr[x2] && arr[x3] <= arr[x1])) pivot = x1;
		else if ((arr[x2] >= arr[x1] && arr[x3] >= arr[x2]) || (arr[x2] <= arr[x1] && arr[x3] <= arr[x2])) pivot = x2;//x1�� ��ŭ
		else pivot = x3;
	}//pivot �߰��� ã�� ���. pivot���� left�� ����.
	Swap(arr, left, pivot);//���� ���ҷ� hide*/
	int low = left + 1, high = right;
	while (low <= high) {
		while (arr[left] >= arr[low] && low <= high) low++;
		while (arr[left] <= arr[high] && high >= low) high--;//�ߺ��� ã�� ����
		if (low <= high) Swap(arr, low, high);
	}
	Swap(arr, left, high);
	return high;
}

void QuickSort(int *arr, int l, int r) {
	if (l <= r) {
		int pivot = partition(arr, l, r);
		QuickSort(arr, l, pivot - 1);
		QuickSort(arr, pivot + 1, r);
	}
}

int binarySearch(int *arr, int left, int right, int k) {
	while (left <= right)
	{
		int pivot = (right + left) / 2;
		if (arr[pivot] == k) return pivot;
		else if (arr[pivot] < k) left = pivot + 1;
		else right = pivot - 1;
	}
	return left;
}

int main() {
	int i, n, *arr, x, result;
	scanf("%d", &n);
	arr = (int*)malloc(sizeof(int)*n);
	for (i = 0; i < n; i++) scanf("%d", &arr[i]);
	QuickSort(arr, 0, n - 1);
	for (i = 0; i < n; i++) printf(" %d", arr[i]);
	printf("\n");
	scanf("%d", &x);
	result = binarySearch(arr, 0, n - 1, x);
	if (arr[result] == x) printf("�� %d�� %d��° �ε����� �����մϴ�.", x, result + 1);
	else {
		printf("�� %d�� �������� �ʽ��ϴ�.\n", x);
		if (result == 0) printf("%d��° �ε��� �� %d �տ� ���ϴ�.", result, arr[result]);
		else if (result == n) printf("%d��° �ε��� �� %d �ڿ� ���ϴ�", result - 1, arr[result - 1]);
		else printf("%d��° �ε��� �� %d�� %d��° �ε��� �� %d ���̿� ���ϴ�.", result - 1, arr[result - 1], result, arr[result]);
	}
	free(arr);
	scanf("%d", &x);
	return 0;
}