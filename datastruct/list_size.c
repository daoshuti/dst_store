#include <stdio.h>
#include <stdlib.h>



typedef struct node{
	int* data;//再通过malloc的方式获取空间
	int last;//last == -1 为空
	int size;
}list_t;//重命名 类型


//创建
list_t* create_list(int size)
{
	if(size<=0)
		return NULL;

	list_t* list=malloc(sizeof(list_t));
	
	list->last=-1;//初始化为空

	list->size=size;

	list->data=malloc(sizeof(int)*list->size);//给data 足够的空间

	return list;//list_t* 类型 连续空间首地址
}
//判空
int isnull(list_t* list)
{
	if(list==NULL)//NULL   (void *)0   0地址不能访问其成员 段错误
		return 0;

	/*
	if(list->last==-1)
		return 1;
	else
		return 0;
		*/

	return list->last==-1;// 判断是否成立  == 返回1， 否则返回0

}
//判满
int isfull(list_t* list)
{
	if(list==NULL)
		return 0;

	return list->last==(list->size-1);//表示在最后一个元素的位置上


}
//增 从头部插入
int insert_head_list(list_t* list,int data)
{
	//1
	//判断执行条件  判满
	if(isfull(list)||list==NULL)
		return -1;
	//2
	//挪位置
	int i;
	for(i=list->last;i>=0;i--)
	{
		list->data[i+1]=list->data[i];
	
	}
	//3
	//放数据
	list->data[0]=data;

	//4
	//修改标识
	list->last++;


	return 0;

}

//删 
int delete_head_list(list_t* list)
{
	//1 判断是否为空
	if(list==NULL||isnull(list))
		return -1;

	//2 直接覆盖删除位置
	int i;
	for(i=0;i<list->last;i++)
	{
	
		list->data[i]=list->data[i+1];
	}

	//3 改变标识
	list->last--;

	return 0;
}
//查
int locate_list(list_t* list,int data)
{
	if(list==NULL||isnull(list))
		return -1;

	int i;
	for(i=0;i<=list->last;i++)
	{
		if(list->data[i]==data)
			return i;
	}

	return -1;

}
//指定位置修改
int change_index_list(list_t* list,int index,int data)
{
	if(list==NULL||isnull(list)||index<0||index>list->last)
		return -1;

	list->data[index]=data;

	return 0;

}
//指定位置插入
int insert_index_list(list_t* list,int index,int data)
{
	//1
	//判断执行条件  判满
	if(isfull(list)||list==NULL||index<0||index>list->last+1)
		return -1;
	//2
	//挪位置
	int i;
	for(i=list->last;i>=index;i--)// last+1位置不会引发挪的操作
	{
		list->data[i+1]=list->data[i];
	
	}
	//3
	//放数据
	list->data[index]=data;

	//4
	//修改标识
	list->last++;


	return 0;

}

//指定位置删除
int delete_index_list(list_t* list,int index)
{
	//1 判断是否为空
	if(list==NULL||isnull(list)||index<0||index>list->last)
		return -1;

	//2 直接覆盖删除位置
	int i;
	for(i=index;i<list->last;i++)
	{
	
		list->data[i]=list->data[i+1];
	}

	//3 改变标识
	list->last--;

	return 0;
}

//打印
int print_list(list_t* list)
{
	if(list==NULL||isnull(list))
		return -1;

	int i;
	for(i=0;i<=list->last;i++)
	{
		printf("%3d ",list->data[i] );
	
	}
	printf("\n");

	return 0;

}
//逆打印
int re_print(list_t* list)
{

	if(list==NULL||isnull(list))
		return -1;

	int i;
	for(i=list->last;i>=0;i--)
	{
		printf("%3d ",list->data[i] );
	
	}
	printf("\n");

	return 0;

}
//清空
int clear_list(list_t* list)
{
	if(list==NULL||isnull(list))
		return -1;


	list->last=-1;

	return 0;

}
//长度
int length_list(list_t* list)
{
	if(list==NULL||isnull(list))
		return 0;
	
	return list->last+1;
}
//销毁
int destroy_list(list_t* list)
{
	if(list==NULL)
		return -1;

	free(list->data);
	free(list);
	return 0;

}



int main(int argc, const char *argv[])
{
	list_t* list=create_list(20);

	int i;
	for(i=1;i<=17;i++)
	{
		if(insert_head_list(list,i)==0)
			print_list(list);
	}

	if(change_index_list(list,locate_list(list,15),250)==0)
		print_list(list);


	re_print(list);

	insert_index_list(list,locate_list(list,250),888);
	print_list(list);


	delete_index_list(list,locate_list(list,250));
	print_list(list);


	printf("length_list:%d\n",length_list(list));

	clear_list(list);


	printf("length_list:%d\n",length_list(list));
	

	destroy_list(list);

#if 0
	for(i=1;i<=20;i++)
	{
		if(delete_head_list(list)==0)
			print_list(list);
	
	}
#endif


	return 0;
}
