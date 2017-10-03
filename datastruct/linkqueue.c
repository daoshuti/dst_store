#include <stdio.h>
#include <stdlib.h>

typedef struct listnode{
	int data;
	struct listnode* next;
}list_t;//用来构建成链表，实际负责数据的存储

typedef struct queuenode{
	list_t* head;
	list_t* tail;
}linkqueue_t;//用来保存 链表的头尾节点地址  实际负责引导 入队 出队


//创建
linkqueue_t* create_linkqueue()
{
	linkqueue_t* queue=malloc(sizeof(linkqueue_t));

	queue->head=malloc(sizeof(list_t));

	queue->head->next=NULL;

	queue->tail=queue->head;
	
	return queue;
}
//判空
int isnull(linkqueue_t* queue)
{
	if(queue==NULL)
		return 0;

	return queue->head==queue->tail;//queue->head->next==NULL;
}
//入队
int push(linkqueue_t* queue,int data)
{
	if(queue==NULL)
		return -1;
	
	list_t* newnode=malloc(sizeof(list_t));
	newnode->data=data;
	newnode->next=NULL;


	queue->tail->next=newnode;

	queue->tail=newnode;

	return 0;

}
//出队
int pop(linkqueue_t* queue,int *data)
{
	if(queue==NULL||isnull(queue))
		return -1;

	*data=queue->head->next->data;

	list_t* temp=queue->head->next;

	if(temp==queue->tail)//有且仅当 即将删除的数据是最后一个元素，tail需要归位，否则野指针
	{
		queue->tail=queue->head;
	
	}

	queue->head->next=temp->next;

	free(temp);

	return 0;
}
//长度
int length_linkqueue(linkqueue_t* queue)
{
	if(queue==NULL||isnull(queue))
		return 0;

	list_t* temp=queue->head;
	int sum=0;

	while(temp->next!=NULL)
	{
		sum++;
		temp=temp->next;
	}
	
	return sum;
}

//打印（假）
int print_linkqueue_notreal(linkqueue_t* queue)
{
	if(queue==NULL||isnull(queue))
		return -1;

	//	queue->head=queue->head->next;//这样使用  queue 是局部变量 并无大碍
	//	queue指向的head 会被永久修改，导致只能打印一次就不能正常使用。
	
	list_t* temp=queue->head;

	while(temp->next!=NULL)
	{
		printf("%3d ",temp->next->data);
		temp=temp->next;
	}
	printf("\n");
	return 0;
}
//清空
int clear_linkqueue(linkqueue_t* queue)
{
	if(queue==NULL||isnull(queue))
		return -1;

	int data;

	while(!isnull(queue))
	{
		pop(queue,&data);
	
	}
	return 0;
}
//销毁
int destroy_queue(linkqueue_t* queue)
{
	if(queue==NULL)
		return -1;

	if(!isnull(queue))
		clear_linkqueue(queue);

	free(queue->head);

	free(queue);
	
	return 0;

}
//打印（真）
int print_linkqueue_real(linkqueue_t* queue)
{

	if(queue==NULL||isnull(queue))
		return -1;

	linkqueue_t* temp=create_linkqueue();

	int data;

	while(!isnull(queue))
	{
		pop(queue ,&data);

		printf("%3d ",data);
		
		push(temp,data);
	}
	printf("\n");


	while(!isnull(temp))
	{
		pop(temp,&data);

		push(queue,data);
	}

	destroy_queue(temp);

	return 0;
}

//打印（真）  法2
int print_linkqueue_real2(linkqueue_t* queue)
{

	if(queue==NULL||isnull(queue))
		return -1;
	
	int count=length_linkqueue(queue);


	int data;
	while(count--)
	{
		pop(queue,&data);

		printf("%3d ",data);

		push(queue,data);
	}
	printf("\n");


	return 0;
}



//逆打印 （真）提示：两个栈实现一个队列（经典面试题）
//
int reprint_linkqueue_real(linkqueue_t* queue)
{
	if(queue==NULL||isnull(queue))
		return -1;



	int * stack1=malloc(sizeof(int)*length_linkqueue(queue));

	int top1=-1;

	int * stack2=malloc(sizeof(int)*length_linkqueue(queue));
	int top2=-1;


	int data;

	while(!isnull(queue))
	{
		pop(queue,&data);
	
		stack1[++top1]=data;
	
	}

	while(top1!=-1)
	{
		data=stack1[top1--];
		printf("%3d ",data);
		stack2[++top2]=data;
	}
	printf("\n");

	while(top2!=-1)
	{
		data=stack2[top2--];

		push(queue,data);
	}

	free(stack2);
	free(stack1);
	
	return 0;

}








int main(int argc, const char *argv[])
{
	linkqueue_t* queue=create_linkqueue();


	int i;

	for(i=1;i<=20;i++)
	{
		push(queue,i*10);
	//	print_linkqueue_notreal(queue);
	//	print_linkqueue_real(queue);
		print_linkqueue_real2(queue);
	
	}


	reprint_linkqueue_real(queue);


#if 0
	int data;
	for(i=1;i<=20;i++)
	{
		pop(queue,&data);
		print_linkqueue_notreal(queue);
	
	}
#endif

	push(queue,888);
	push(queue,250);

	print_linkqueue_notreal(queue);
	return 0;
}
