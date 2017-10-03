#include <stdio.h>
#include <stdlib.h>

typedef struct node{

	int *data;
	int size;
	int head;
	int tail;
}queue_t;


//创建
queue_t* create_queue(int size)
{
	if(size<=0)
		return NULL;


	queue_t* queue=malloc(sizeof(queue_t));

	queue->size=size;

	queue->data=malloc(sizeof(int)*size);

	queue->head=queue->tail=0;//初始都在0   说辞： “即将”  --》 tail即将放入数据  head 即将取出数据的位置

	return queue;
}
//判空
int isnull(queue_t* queue)
{
	if(queue==NULL)
		return 0;

	return queue->head==queue->tail;
}
//判满
int isfull(queue_t* queue)
{
	if(queue==NULL)
		return 0;

	return (queue->tail+1)%(queue->size)==queue->head;  
	//循环 利用空间时 超过了 0~size-1的范围  则对size取余    基于 空间
	//
	//return (queue->tail-queue->head+queue->size)%queue->size==queue->size-1;   基于 长度


}
//入队
int push(queue_t* queue,int data)
{
	if(queue==NULL||isfull(queue))    // 0=='\0'==NULL
		return -1;


	queue->data[queue->tail]=data;

	queue->tail=(queue->tail+1)%queue->size;


	return 0;


}
//出队
int pop(queue_t* queue,int * data)
{
	if(queue==NULL||isnull(queue))
		return -1;


	*data=queue->data[queue->head];

	queue->data[queue->head]=0;//非必须 只作为测试

	queue->head=(queue->head+1)%queue->size;

	return 0;
}

//打印（从0打印 到 size-1）
int print_queue_fromzero(queue_t* queue)
{
	if(queue==NULL||isnull(queue))
		return -1;

	int i;

	for(i=0;i<queue->size;i++)
	{
		printf("%3d ",queue->data[i]);
	}
	printf("\n");


	return 0;


}
//打印  （从head 打印到  tail）
int print_queue_fromhead(queue_t* queue)
{
	if(queue==NULL||isnull(queue))
		return -1;


	int i;
	i=queue->head;
	for(;;)//1. 初始条件  2. 成立条件  3. 每次循环后执行的操作  //切换  while（1）
	{
		if(i!=queue->tail)
		{
		
			printf("%3d ",queue->data[i]);
		}
		else
			break;

		i=(i+1)%queue->size;
	
	
	}

	/*
	for(i=queue->head;i!=queue->tail;i=(i+1)%queue->size)
	{
		printf("%3d ",queue->data[i]);
	}
	*/
	printf("\n");

	return 0;

}

//长度
int length_queue(queue_t* queue)
{
	if(queue==NULL||isnull(queue))
		return 0;


	return (queue->tail-queue->head+queue->size)%queue->size;



}
//清空
int clear_queue(queue_t* queue)
{
	if(queue==NULL||isnull(queue))
		return -1;


	queue->head=queue->tail=0;

	return 0;

}
//销毁


int destroy_queue(queue_t* queue)
{
	if(queue==NULL)
		return -1;

	free(queue->data);

	free(queue);

	return 0;
}


//逆打印（真）
int reprint_queue_real(queue_t* queue)
{

	//1. 判断是否为空
	if(queue==NULL||isnull(queue))
		return -1;
	//2. 创建  栈1，栈2， top 1和2
	int * stack1=malloc(sizeof(int)*length_queue(queue));
	int top1=-1;
	int * stack2=malloc(sizeof(int)*length_queue(queue));
	int top2=-1;


	int data;
	//3.只要队列不为空，则出队，入栈1
	while(!isnull(queue))
	{
		pop(queue,&data);

		stack1[++top1]=data;

	}


	//4.只要栈1不为空，出栈打印，入栈2
	while(top1!=-1)
	{
		data=stack1[top1--];
		
		printf("%3d ",data);

		stack2[++top2]=data;
	
	}
	printf("\n");
	//5.只要栈2不为空，出栈，入队列
	while(top2!=-1)
	{
		data=stack2[top2--];

		push(queue,data);
	}
	//6.销毁栈1，栈2
	//
	free(stack1);
	free(stack2);

	return 0;
}

int print_queue_real(queue_t* queue)
{
	if(queue==NULL||isnull(queue))
		return -1;


	queue_t* temp=create_queue(length_queue(queue)+1);


	int data;
	while(!isnull(queue))
	{
		pop(queue,&data);

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



int main(int argc, const char *argv[])
{
	
	queue_t* queue=create_queue(20);

	int i;

	for(i=1;i<=20;i++)
	{
		if(0==push(queue,i))
		{
		//	print_queue_fromzero(queue);
			print_queue_fromhead(queue);
		}
	
	}


	reprint_queue_real(queue);

//	print_queue_fromhead(queue);
	

	print_queue_real(queue);

//	int data;
#if 0
	for(i=1;i<=20;i++)
	{

		if(pop(queue,&data)==0)
		{
			printf("data:%d head:%d tail:%d\n",data,queue->head,queue->tail);
			//print_queue_fromzero(queue);
			print_queue_fromhead(queue);

		}
	
	
	}
#endif



	return 0;
}
