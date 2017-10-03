#include <stdio.h>
#include <stdlib.h>

typedef int data_t;

typedef struct node{
	data_t data;
	struct node * front;
	struct node * next;

}duolist_t;

//创建
duolist_t* create_duolist()
{
	duolist_t* list=malloc(sizeof(duolist_t));

	list->front=NULL;
	list->next=malloc(sizeof(duolist_t));
	list->next->front=list;
	list->next->next=NULL;

	return list;
}
//判空
int isnull(duolist_t* list)
{
	if(list==NULL)
		return 0;

	return list->next->next==NULL;

}
//增
int insert_duolist(duolist_t* list, data_t data)
{
	//1
	if(list==NULL)
		return -1;

	//2
	duolist_t* newnode=malloc(sizeof(duolist_t));
	newnode->data=data;

	//3
	newnode->front=list;
	newnode->next=list->next;

	//4
	newnode->front->next=newnode;
	newnode->next->front=newnode;

	/*
	list->next->front=newnode;
	list->next=newnode;
	*/

	return 0;

}
//删
int delete_duolist(duolist_t* list)
{
	//1
	if(list==NULL||isnull(list))
		return -1;


	//2
	duolist_t* temp=list->next;

	//3
	temp->front->next=temp->next;
	temp->next->front=temp->front;

	//4
	free(temp);

	return 0;

}
//查
duolist_t* locate_duolist(duolist_t* list, data_t data)
{

	if(list==NULL||isnull(list))
		return NULL;

	while(list->next->next!=NULL)
	{
		if(list->next->data==data)
			return list->next;

		list=list->next;
	}
		
	return NULL;

}
//
//改
int change_duolist(duolist_t* list,data_t data)
{
	if(list==NULL)
		return -1;

	list->data=data;

	return 0;

}
//
//打印
int print_duolist(duolist_t* list)
{
	if(list==NULL||isnull(list))
		return -1;

	while(list->next->next!=NULL)
	{
		printf("%3d ",list->next->data);
		list=list->next;
	}
	printf("\n");
	
	return 0;
}
//逆打印
//?????
int reprint_duolist(duolist_t* list)
{
	if(list==NULL||isnull(list))
		return -1;

	while(list->next->next!=NULL)
	{
		list=list->next;
	}
	list=list->next;


	while(list->front->front!=NULL)
	{
		printf("%3d ",list->front->data);
		list=list->front;
	
	}
	printf("\n");
	
	return 0;
}
//清空
int clear_duolist(duolist_t* list)
{
	if(list==NULL||isnull(list))
		return -1;

	while(!isnull(list))
	{
		delete_duolist(list);
	}

	return 0;

}
//长度
int length_duolist(duolist_t* list)
{


	if(list==NULL||isnull(list))
		return 0;

	int sum=0;
	while(list->next->next!=NULL)
	{
		sum++;
		list=list->next;
	}
	
	return sum;


}
//销毁
int destroy_duolist(duolist_t* list)
{
	if(list==NULL)
		return -1;

	if(!isnull(list))
		clear_duolist(list);

	free(list->next);
	free(list);
	return 0;
}



int main(int argc, const char *argv[])
{
	
	duolist_t* list=create_duolist();

	int i;
	for(i=1;i<=20;i++)
	{
		insert_duolist(list,i);
		print_duolist(list);
	
	}


	change_duolist(locate_duolist(list,15),250);

	print_duolist(list);


	insert_duolist(locate_duolist(list,250)->front,15);

	print_duolist(list);

	delete_duolist(locate_duolist(list,250)->front);

	print_duolist(list);


	reprint_duolist(list);

	print_duolist(list);



	printf("length_duolist:%d\n",length_duolist(list));

	clear_duolist(list);


	printf("length_duolist:%d\n",length_duolist(list));

	destroy_duolist(list);
#if 0
	for(i=1;i<=20;i++)
	{
		delete_duolist(list);

		print_duolist(list);
	}

#endif
	return 0;
}
