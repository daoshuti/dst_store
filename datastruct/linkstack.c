#include <stdio.h>
#include <stdlib.h>


//
typedef struct node{
	int data;
	struct node * next;

}linkstack_t;

//创建
linkstack_t* create_linkstack()
{
	linkstack_t* stack=malloc(sizeof(linkstack_t));
	stack->next=NULL;

	return stack;
}
//判空
int isnull(linkstack_t* stack)
{
	if(stack==NULL)
		return 0;

	return stack->next==NULL;
}
//入栈
int push_linkstack(linkstack_t* stack,int data)
{
	if(stack==NULL)
		return -1;

	linkstack_t* newnode=create_linkstack();
	newnode->data=data;

	newnode->next=stack->next;

	stack->next=newnode;

	return 0;
}
//出栈
int pop_linkstack(linkstack_t* stack,int *  data)
{
	if(stack==NULL||isnull(stack))
		return -1;

	linkstack_t* temp=stack->next;

	*data=temp->data;

	stack->next=temp->next;

	free(temp);


	return 0;
}
//打印（假）
int print_linkstack_notreal(linkstack_t * stack)
{
	if(stack==NULL||isnull(stack))
		return -1;

	while(stack->next!=NULL)
	{
	
		printf("%3d ",stack->next->data);

		stack=stack->next;
	}

	printf("\n");

	return 0;

}
//长度
int length_linkstack_notreal(linkstack_t * stack)
{
	if(stack==NULL||isnull(stack))
		return 0;

	int sum=0;
	while(stack->next!=NULL)
	{
		sum++;
		stack=stack->next;
	}

	return sum;

}
//清空
int clear_linkstack(linkstack_t* stack)
{
	if(stack==NULL||isnull(stack))
		return -1;

	int data;
	while(!isnull(stack))
	{
		pop_linkstack(stack,&data);

	}
	return 0;

}
//销毁
int destroy_linkstack(linkstack_t* stack)
{
	if(stack==NULL)
		return -1;

	if(!isnull(stack))
		clear_linkstack(stack);

	free(stack);
	return 0;
}

//逆打印（真）
int reprint_linkstack_real(linkstack_t * stack)
{
	if(stack==NULL||isnull(stack))
		return -1;

	int data;
	linkstack_t* temp=create_linkstack();
	while(!isnull(stack))
	{
		pop_linkstack(stack,&data);
		push_linkstack(temp,data);
	}

	while(!isnull(temp))
	{
		printf("%3d ",temp->next->data);

		pop_linkstack(temp,&data);
		push_linkstack(stack,data);
	}
	printf("\n");
	destroy_linkstack(temp);
	
	return 0;

}




int main(int argc, const char *argv[])
{
	linkstack_t* stack=create_linkstack();

	int i;
	for(i=1;i<=20;i++)
	{
		push_linkstack(stack,i*10);
		print_linkstack_notreal(stack);
	}


	reprint_linkstack_real(stack);

	print_linkstack_notreal(stack);

//	int data;
#if 0
	for(i=1;i<=20;i++)
	{
		pop_linkstack(stack,&data);
		print_linkstack_notreal(stack);

	}
#endif
	
	return 0;
}
