#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct tagNode {
	int element;
	struct tagNode *left;
	struct tagNode *right;
}Node;

Node* createNode(int element,Node *left,Node *right){
	Node *tmp = (Node*)malloc(sizeof(Node));
	tmp->element = element;
	tmp->left = left;
	tmp->right = right;
	return tmp;
}
Node* searchNode(int element,Node *tmp) {
	if (tmp == NULL) {
		printf("ã�� ���Ұ� �����ϴ�.\n");
		return NULL;
	}
	if (element == tmp->element) {
		printf("ã�ҽ��ϴ�. ��带 ��ȯ�մϴ�\n");
		return tmp;
	}
	else if (tmp->element<element){
		searchNode(element, tmp->right);
	}
	else {
		searchNode(element, tmp->left);
	}
}
void appendNode(int element,Node *root) {
	Node *tmp;
	if(element>root->element){
		if (root->right == NULL)
		{
			tmp = createNode(element,NULL,NULL);
			root->right = tmp;
		}
		else appendNode(element, root->right);
	}
	else if (element < root->element) {
		if (root->left == NULL) {
			tmp = createNode(element, NULL, NULL);
			root->left = tmp;
		}
		else appendNode(element, root->left);
	}
	else printf("�̹� �� ���Ұ� Ʈ�� �ȿ� �ֽ��ϴ�.\n");
}
Node* deleteNode(int element,Node *parent,Node *tmp) {
	Node *Removed;
	if (tmp == NULL) printf("������ ��尡 �����ϴ�");
	else {
		if (tmp->element > element) Removed = deleteNode(element,tmp, tmp->left);
		else if (tmp->element < element) Removed = deleteNode(element,tmp, tmp->right);
		else//��ǥ�� ã���� ��
		{
			Removed = tmp;
			if (tmp->left == NULL && tmp->right == NULL) {
				if (parent->left == tmp) {
					parent->left = NULL;
				}
				else parent->right = NULL;
				free(tmp);
			}//no children
			else if (tmp->left != NULL && tmp->right != NULL) {
				Node *min = tmp->right;//������ ����� ���� ������.
				while (min->left != NULL) min = min->left;
				int x = min->element;
				Removed = deleteNode(min->element,NULL, tmp);
				tmp->element = x;
			}//two children
			else {
				Node *tmp2 = NULL;
				if(tmp->left != NULL)
					tmp2 = tmp->left;
				else tmp2 = tmp->right;
				if (parent->left == tmp) parent->left = tmp2;
				else parent->right = tmp2;//tmp�� ���ڽ� ��带 �θ��忡 ���� 
				free(tmp);
			}//one child
		}
	}
	return Removed;
}
void printTree(Node *tmp) {
	
	if (tmp->left != NULL)
		printTree(tmp->left);
	printf("%d ", tmp->element);
	if (tmp->right != NULL)
		printTree(tmp->right);
}//������ȸ�� ���

int main() {
	int i, x;
	Node *tmp;
	Node *root = createNode(-1,NULL,NULL);//��Ʈ ����
	while(1){
		if(root->element == -1){
			printf("������ �ۼ��ϼ���:");
			scanf("%d",&root->element);
		}//ù ������ �ۼ�

		printf("1 : Ʈ�� �߰�, 2 : Ʈ�� ����, 3 : Ʈ�� �˻�, 4:Ʈ�� ���, ������ : ����\n");
		scanf("%d", &x);

		switch (x) {
		case 1: {
			printf("�߰��� Ʈ���� element�� �����ּ���:");
			scanf("%d", &i);
			appendNode(i,root);
			break;
		}
		case 2: {
			printf("������ Ʈ���� element�� �����ּ���:");
			scanf("%d", &i);
			tmp = deleteNode(i,root,root);
			break;
		}
		case 3: {
			printf("ã�� Ʈ���� element�� �����ּ���:");
			scanf("%d", &i);
			tmp = searchNode(i, root);
			break;
		}
		case 4: {
			printf("Ʈ�� ���\n");
			printTree(root);
			printf("\n");
			break;
		}
		default: return;
		}
	}

	return 0;
}