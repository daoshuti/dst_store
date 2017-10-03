#include<stdio.h>
#include<sqlite3.h>

int network_16081(void *p,int n,char **f_value,char **f_name)
{
	int i;
	
	int ctl = *(int *)p;

	if(ctl == 1)
	{
		for(i = 0;i < n;i ++)
		{
			printf("%s\t",f_name[i]);
		}
		printf("\n");
	} 
//	ctl = 0;
	*(int *)p = 0;
	for(i = 0;i < n;i ++)
	{
		printf("%s\t",f_value[i]);
	}
	printf("\n");

	sleep(1);
	return 0;
}

int main(int argc, const char *argv[])
{
	sqlite3 *db;

	if(sqlite3_open("./1.db",&db) != SQLITE_OK)//打开或者创建数据库文件的功能
	{
		printf("%s\n",sqlite3_errmsg(db));
		return -1;
	}

	char *errmsg;
	char sqlbuf[128];

	sprintf(sqlbuf,"create table stu(name,score);");
	if(sqlite3_exec(db,sqlbuf,NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
		return -1;
	}

	int i;
	char name[15];
	int score;
	for(i = 0;i < 3;i ++)
	{
		scanf("%s%d",name,&score);

		sprintf(sqlbuf,"insert into stu values('%s',%d);",name,score);

		sqlite3_exec(db,sqlbuf,NULL,NULL,NULL);

	}


	sprintf(sqlbuf,"select * from stu where name='a';");

	int ctl = 1;

	if(sqlite3_exec(db,sqlbuf,network_16081,(void *)&ctl,&errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
		return -1;
	}

	printf("华丽的分割线\n");	
	sprintf(sqlbuf,"select * from stu where name='a';");
	
	char **resultp;
	int r;
	int c;
	int count = 0;
	sqlite3_get_table(db,sqlbuf,&resultp,&r,&c,&errmsg);

//	printf("%d,%d\n",r,c);


	for(i = 0;i < c;i ++)
	{
		printf("%s\t",resultp[i]);
	}
	printf("\n");

	for(i = c;i < (r + 1)*c;i ++)
	{
		printf("%s\t",resultp[i]);
		count ++;

		if(count % c == 0)
			printf("\n");
	}
	return 0;
}
