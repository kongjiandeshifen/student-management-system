#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//学生 
typedef struct _Student
{
	int stuNum;		//学号 
	char name[20];	//姓名
}Student;
//节点 
typedef struct _Node
{
	Student stu;
	struct _Node *pNext;
}Node;

Node *g_pHead = NULL;

//函数 
void Welcome(void);
void InputStudent(void);
void PrintStudent(void);
void SaveStudent(void); 
void ReadStudent(void);
void CountStudent(void);
Node *FindStudent(void);
void ModifyStudent(void);
void DeleteStudent(void);

int main(void)
{
	char ch;
	Node *p = NULL;
	
	while(1)
	{
		Welcome();
		ch = getch();
		
		switch(ch)
		{
			case '1'://添加
				InputStudent(); 
				break;
			case '2'://展示
				PrintStudent();
				break;
			case '3'://保存
				SaveStudent();
				break;
			case '4'://读取
				ReadStudent();
				break;
			case '5'://统计
				CountStudent();
				break;
			case '6'://查找
				p = FindStudent();
				if(p!=NULL)
				{
					printf("**************************************\n");
					printf("*             学生信息               *\n");
					printf("**************************************\n");
					printf("学号:%5d            姓名:%s             \n",p->stu.stuNum,p->stu.name);
					printf("**************************************\n");
					p = NULL;
				}
				else
				{
					printf("没有找到该学生\n"); 
				}
				system("pause");
				system("cls");
				break;
			case '7'://修改
				ModifyStudent();
				break;
			case '8'://删除
				DeleteStudent();
				break;
			case '0'://退出
				system("cls");
				printf("感谢使用此系统!\n");
				return 0;
			default:
				system("cls");
				printf("请输入正确的操作码!\n");
				system("pause");
				system("cls");
				break;
		}
	}
	
	return 0;
}

void Welcome(void)
{
	printf("**************************************\n");
	printf("*         和光学生管理系统           *\n");
	printf("**************************************\n");
	printf("*             功能选择               *\n");
	printf("**************************************\n");
	printf("*         1.添加学生信息             *\n");
	printf("*         2.展示缓冲区学生信息       *\n");
	printf("*         3.保存学生信息到文件夹     *\n");
	printf("*         4.读取文件夹中学生信息     *\n");
	printf("*         5.统计学生人数             *\n");
	printf("*         6.查找学生信息             *\n");
	printf("*         7.修改学生信息             *\n");
	printf("*         8.删除学生信息             *\n");
	printf("*         0.退出系统                 *\n");
	printf("**************************************\n");
	
}

void InputStudent(void)
{
	system("cls");
	Node *pNewNode = (Node *)malloc(sizeof(Node));
	pNewNode -> pNext = NULL;
	//头插判断 
	if(g_pHead == NULL)
	{
		g_pHead = pNewNode;
	}
	else
	{
		pNewNode -> pNext = g_pHead;
		g_pHead = pNewNode;
	}
	
	printf("请输入学号:");
	scanf("%d",&pNewNode->stu.stuNum);
	printf("请输入姓名:");
	scanf("%s",pNewNode->stu.name);
	printf("\n录入成功！\n");
	system("pause");
	system("cls"); 
}

void PrintStudent(void)
{
	system("cls");
	printf("**************************************\n");
	printf("*             缓存信息               *\n");
	printf("**************************************\n");
	Node *p = g_pHead;
	if(p == NULL)
	{
		printf("*            无学生信息              *\n");
	}
	else
	{
		printf("*       学号             姓名        *\n");
		printf("**************************************\n");
		while(p != NULL)
		{
			printf("       %5d             %s             \n",p->stu.stuNum,p->stu.name);
			p = p->pNext;
		}
	} 
	
	printf("**************************************\n");
	system("pause");
	system("cls");
}

void SaveStudent(void)
{
	FILE *fp = fopen("student.txt","w");
	
	if(fp == NULL)
	{
		printf("打开文件失败\n");
	}
	
	Node *p = g_pHead;
	
	while(p != NULL)
	{
		fwrite(&p->stu,1,sizeof(Student),fp);//写结构体 1次 
		p = p->pNext;
	}
	fclose(fp);
	printf("保存成功!\n");
	system("pause");
	system("cls");
}

void ReadStudent(void)
{
	FILE *fp = fopen("student.txt","r");
	
	
	if(fp == NULL)
	{
		printf("打开文件失败\n");
		return; 
	}
	
	Student stu; 
	while(fread(&stu,1,sizeof(Student),fp))
	{
		Node *pNewNode = (Node *)malloc(sizeof(Node));
		pNewNode->pNext = NULL;
		
		memcpy(pNewNode, &stu, sizeof(Student));
		
		//头插判断 
		if(g_pHead == NULL)
		{
			g_pHead = pNewNode;
		}
		else
		{
			pNewNode -> pNext = g_pHead;
			g_pHead = pNewNode;
		}
		
	}
	
	fclose(fp);
	printf("已读取至缓冲区.\n");
	system("pause");
	system("cls");
}

void CountStudent(void)
{
	int nCount = 0;
	
	Node *p = g_pHead;
	while(p != NULL)
	{
		nCount++;
		p = p->pNext;
	}
	
	printf("当前缓冲区人数%d\n",nCount);
	system("pause");
	system("cls");
}

Node *FindStudent(void)
{
	system("cls");
	int nStudNum;
	
	printf("请输入学生学号:");
	scanf("%d",&nStudNum);
	
	Node *p = g_pHead;
	while(p != NULL)
	{
		if(p->stu.stuNum == nStudNum)
		{
			return p;
		}
		p = p->pNext;
	}
	
	return NULL;
}

void ModifyStudent(void)
{
	Node *p = FindStudent();
	if(p != NULL)
	{
		printf("**************************************\n");
		printf("*             学生信息               *\n");
		printf("**************************************\n");
		printf("学号:%5d            姓名:%s             \n",p->stu.stuNum,p->stu.name);
		printf("**************************************\n");
		printf("请输入修改的学生信息:");
		scanf("%d%*c%s",&p->stu.stuNum,p->stu.name);
		printf("修改完成!\n");
	}
	else
	{
		printf("没有找到该学生\n");
	}
	system("pause");
	system("cls");
}

void DeleteStudent(void)
{
	system("cls");
	int nStuNum;
	printf("请输入删除学号:");
	scanf("%d",&nStuNum);
	Node *current = NULL;
	Node *last = NULL;
	
	if(g_pHead->stu.stuNum == nStuNum)
	{
		current = g_pHead;
		g_pHead = g_pHead->pNext;
		system("cls");
		printf("**************************************\n");
		printf("*         删除该学生信息             *\n");
		printf("**************************************\n");
		printf("学号:%5d            姓名:%s             \n",current->stu.stuNum,current->stu.name);
		printf("**************************************\n");
		free(current);
		printf("删除成功\n");
		system("pause");
		system("cls");
		return;
	}
	else
	{
		last = g_pHead;
		while(last->pNext != NULL)
		{
			if(last->pNext->stu.stuNum == nStuNum)
			{	
				current = last->pNext;
				last->pNext = current->pNext;
				system("cls");
				printf("**************************************\n");
				printf("*         删除该学生信息             *\n");
				printf("**************************************\n");
				printf("学号:%5d            姓名:%s             \n",current->stu.stuNum,current->stu.name);
				printf("**************************************\n");
				free(current);
				printf("删除成功\n");
				system("pause");
				system("cls");
				return;
			}
			last = last->pNext;
			if(last->pNext == NULL)
			{
				break;
			}
		}
		printf("没有找到该学生\n");
		system("pause");
		system("cls");
	}
	
}

