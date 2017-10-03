#include <stdio.h>
#include <stdlib.h>


typedef int data_t;

//类型
typedef struct node{
	data_t data;
	struct node * next;//使用linklist_t * 声明时会报错 ，编译器不识别
	//linklist_t* next;

}linklist_t;

//创建
linklist_t* create_linklist()
{
	linklist_t* list=malloc(sizeof(linklist_t));

	list->next=NULL;

	return list;

}
//判空
int isnull(linklist_t* list)
{
	if(list==NULL)
		return 0;

	return list->next==NULL;
}
//增
int insert_linklist(linklist_t* list,data_t data)
{
	//1 判断条件
	if(list==NULL)
		return -1;

	//2 
	linklist_t* newnode=create_linklist();
	newnode->data=data;

	//3
	newnode->next=list->next;

	//4
	list->next=newnode;

	return 0;
}
//删
//查
//改
//指定位置增
//指定位置删
//打印
int print_linklist(linklist_t* list)
{
	if(list==NULL||isnull(list))
		return -1;


	while(list->next!=NULL)
	{
		printf("%3d ",list->next->data);
		list=list->next;
	}

	printf("\n");

	return 0;

}
//逆打印法1
//逆打印法2
//长度
//清空
//销毁




int main(int argc, const char *argv[])
{

	linklist_t* list=create_linklist();

	int i;
	for(i=1;i<=20;i++)
	{
		insert_linklist(list,i);
		print_linklist(list);
	}
	
	return 0;
}
