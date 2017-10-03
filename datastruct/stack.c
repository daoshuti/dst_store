#include <stdio.h>
#include <stdlib.h>

//类型
typedef int data_t;


typedef struct node{
	
	data_t *data;
	int size;
	int top;//类似于  last的作用

}newstack_t;

//创建
newstack_t* create_stack(int size)
{
	if(size<=0)
		return NULL;

	newstack_t* stack=malloc(sizeof(newstack_t));

	stack->size=size;
	stack->data=malloc(sizeof(int)*size);
	stack->top=-1;

	return stack;
}
//判空
int isnull(newstack_t* stack)
{
	if(stack==NULL)
		return 0;

	return stack->top==-1;
}
//判满
int isfull(newstack_t* stack)
{
	if(stack==NULL)
		return 0;

	return stack->top==stack->size-1;
}
//push
int push(newstack_t* stack,data_t data)
{
	if(stack==NULL||isfull(stack))
		return -1;


	stack->data[stack->top+1]=data;

	stack->top++;

	return 0;

}
//pop   (将取出数据 拿出来)
int pop(newstack_t* stack,data_t* data)
{
	if(stack==NULL||isnull(stack))
		return -1;

	*data=stack->data[stack->top--];

	return 0;//不做数据出口，防止出现歧义  使用*data
}




//看一眼（查看栈顶元素）
int view(newstack_t* stack)
{
	if(stack==NULL||isnull(stack))
		return -1;


	printf("%3d ",stack->data[stack->top]);

	return 0;
}
//打印（假）
int print_stack_notreal(newstack_t* stack)
{
	if(stack==NULL||isnull(stack))
		return -1;


	int i;

	for(i=stack->top;i>=0;i--)
	{
		printf("%3d ",stack->data[i]);
	}
	printf("\n");

	return 0;

}

//长度
int length_stack(newstack_t* stack)
{
	if(stack==NULL||isnull(stack))
		return 0;


	return stack->top+1;

}

//清空
int clear_stack(newstack_t* stack)
{
	if(stack==NULL||isnull(stack))
		return -1;

	stack->top=-1;

	return 0;
}
//销毁
int destroy_stack(newstack_t* stack)
{
	if(stack==NULL)
		return -1;

	free(stack->data);
	free(stack);

	return 0;
}


//打印（真）
int print_stack_real(newstack_t* stack)
{
	if(stack==NULL||isnull(stack))
		return -1;


	newstack_t* temp=create_stack(length_stack(stack));

	data_t data;
	while(!isnull(stack))
	{
		view(stack);
		pop(stack,&data);
		push(temp,data);
	}
	printf("\n");

	while(!isnull(temp))
	{
		pop(temp,&data);

		push(stack,data);
	}
	destroy_stack(temp);
	return 0;

}
//逆打印（假）
//逆打印（真）
int reprint_stack_real(newstack_t* stack)
{
	if(stack==NULL||isnull(stack))
		return -1;


	newstack_t* temp=create_stack(length_stack(stack));

	data_t data;
	while(!isnull(stack))
	{
		pop(stack,&data);
		push(temp,data);
	}
	while(!isnull(temp))
	{
		view(temp);

		pop(temp,&data);

		push(stack,data);
	}
	printf("\n");


	destroy_stack(temp);
	return 0;

}


int main(int argc, const char *argv[])
{
	newstack_t * stack;


	stack=create_stack(30);


	int i;

	for(i=1;i<=20;i++)
	{
		push(stack,i);

		print_stack_notreal(stack);
	
	}



	print_stack_real(stack);
	reprint_stack_real(stack);
	print_stack_notreal(stack);

#if 0
	data_t data;

	for(i=1;i<=20;i++)
	{
		pop(stack,&data);
	
		printf("pop data:%d\n",data);

		print_stack_notreal(stack);
	
	}
#endif
	
	return 0;
}
