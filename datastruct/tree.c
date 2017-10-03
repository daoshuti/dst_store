#include <stdio.h>
#include <stdlib.h>

//type
typedef struct treenode{
	int data;//索引号
	struct treenode* leftchild;//左孩子地址
	struct treenode* rightchild;//右孩子地址

}tree_t;
//创建
tree_t* create_tree(int data,int max)
{
	if(data>max)
		return NULL;

	tree_t* tree=malloc(sizeof(tree_t));

	tree->data=data;

	tree->leftchild=create_tree(2*data,max);
	tree->rightchild=create_tree(2*data+1,max);

	return tree;

}
//先序打印   （根-> 左 -> 右）
void print_pre(tree_t* tree)
{
	if(tree==NULL)
		return ;

	printf("%2d ",tree->data);

	print_pre(tree->leftchild);

	print_pre(tree->rightchild);

	return ;

}
//
//中序打印    （左 根 右）
void print_mid(tree_t* tree)
{
	if(tree==NULL)
		return ;

	print_mid(tree->leftchild);

	printf("%2d ",tree->data);

	print_mid(tree->rightchild);

	return ;

}

//后序打印    （左 右 根）
void print_post(tree_t* tree)
{
	if(tree==NULL)
		return ;

	print_post(tree->leftchild);

	print_post(tree->rightchild);

	printf("%2d ",tree->data);

	return ;
}


//
//层次打印  (1->7    从上往下  从左往右)
//
void print_level(tree_t* tree)
{
	if(tree==NULL)
		return ;
	//造数组   tree_t* []   头尾索引  int head  tail
	tree_t* queue[30];
	int head,tail;
	head=tail=0;
	queue[tail++]=tree;//入队
	//循环  ：
	while(head!=tail)//条件
	{
	//有没有左子树
	//有则入队
		if(queue[head]->leftchild!=NULL)
			queue[tail++]=queue[head]->leftchild;
	//有没有右子树
		if(queue[head]->rightchild!=NULL)
			queue[tail++]=queue[head]->rightchild;
	//出队打印
		printf("%3d ",queue[head++]->data);
	}
	printf("\n");
	return ;
}


int main(int argc, const char *argv[])
{
	tree_t* tree=create_tree(1,7);
	print_pre(tree);
	printf("\n");
	print_mid(tree);
	printf("\n");
	print_post(tree);
	printf("\n");
	print_level(tree);
	return 0;
}
