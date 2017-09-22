#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;
struct BTreeNode
{
	ElemType data;
	struct BTreeNode*left;
	struct BTreeNode*right;
};
struct BTreeNode* CreateHuffman(ElemType a[], int n)
{
	int i, j;
	struct BTreeNode **b;
	struct BTreeNode *q = NULL;
	b = malloc(n * sizeof(struct BTreeNode));
	for (i = 0; i < n; i++)
	{
		b[i] = malloc(sizeof(struct BTreeNode));
		b[i]->data = a[i];
		b[i]->left = b[i]->right = NULL;

	}


	for (i = 1; i < n; i++)
	{
		int c1 = -1,c2;
		for (j = 0; j < n; j++)
		{
			if (b[j] != NULL &&c1 == -1)
			{
				c1 = j;
				continue;
			}
			if (b[j] != NULL)
			{
				c2 = j;
				break;
			}
		}
		for (j = c2; j < n; j++)
		{
			if (b[j] != NULL)
			{
				if (b[j]->data < b[c1]->data)
				{
					c2 = c1;
					c1= j;
				}
				else if (b[j]->data < b[c2]->data)
					c2 = j;
			}
		}
		
		q=malloc(sizeof(struct BTreeNode));
		q->data = b[c1]->data + b[c2]->data;
		q->left = b[c1];
		q->right = b[c2];
		b[c1] = q;
		b[c2] = NULL;
	}
	free(b);
	return q;
}
void Huffmancoding(struct BTreeNode*HBT, int len)
{
	static int a[20];
	if (HBT != NULL)
	{
		if (HBT->left == NULL&&HBT->right == NULL)
		{
			int i;
			printf("结点权值为%d的编码：", HBT->data);
			for (i = 0; i < len; i++)
				printf("%d", a[i]);
			printf("\n");
		}
		else
		{
			a[len] = 0;
			Huffmancoding(HBT->left, len + 1);
			a[len] = 1;
			Huffmancoding(HBT->right, len + 1);
		}
	}

}
int main()
{

	int n, i;
	ElemType* a;
	struct BTreeNode*HBT;
	printf("从键盘输入的叶子结点树n:");
	while (1)
	{
		scanf_s("%d", &n);
		if (n > 1)
			break;
		else
			printf("重输n");



	}
	a = malloc(n * sizeof(ElemType));
	printf("从键盘输入%d个数作为权值:", n);
	for (i = 0; i < n; i++)
		scanf_s("%d", &a[i]);
	HBT = CreateHuffman(a, n);
	printf("哈夫曼树中各叶子结点的编码:\n");
	Huffmancoding(HBT, 0);
	system("pause");
}