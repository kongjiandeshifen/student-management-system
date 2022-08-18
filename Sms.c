#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//ѧ�� 
typedef struct _Student
{
	int stuNum;		//ѧ�� 
	char name[20];	//����
}Student;
//�ڵ� 
typedef struct _Node
{
	Student stu;
	struct _Node *pNext;
}Node;

Node *g_pHead = NULL;

//���� 
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
			case '1'://���
				InputStudent(); 
				break;
			case '2'://չʾ
				PrintStudent();
				break;
			case '3'://����
				SaveStudent();
				break;
			case '4'://��ȡ
				ReadStudent();
				break;
			case '5'://ͳ��
				CountStudent();
				break;
			case '6'://����
				p = FindStudent();
				if(p!=NULL)
				{
					printf("**************************************\n");
					printf("*             ѧ����Ϣ               *\n");
					printf("**************************************\n");
					printf("ѧ��:%5d            ����:%s             \n",p->stu.stuNum,p->stu.name);
					printf("**************************************\n");
					p = NULL;
				}
				else
				{
					printf("û���ҵ���ѧ��\n"); 
				}
				system("pause");
				system("cls");
				break;
			case '7'://�޸�
				ModifyStudent();
				break;
			case '8'://ɾ��
				DeleteStudent();
				break;
			case '0'://�˳�
				system("cls");
				printf("��лʹ�ô�ϵͳ!\n");
				return 0;
			default:
				system("cls");
				printf("��������ȷ�Ĳ�����!\n");
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
	printf("*         �͹�ѧ������ϵͳ           *\n");
	printf("**************************************\n");
	printf("*             ����ѡ��               *\n");
	printf("**************************************\n");
	printf("*         1.���ѧ����Ϣ             *\n");
	printf("*         2.չʾ������ѧ����Ϣ       *\n");
	printf("*         3.����ѧ����Ϣ���ļ���     *\n");
	printf("*         4.��ȡ�ļ�����ѧ����Ϣ     *\n");
	printf("*         5.ͳ��ѧ������             *\n");
	printf("*         6.����ѧ����Ϣ             *\n");
	printf("*         7.�޸�ѧ����Ϣ             *\n");
	printf("*         8.ɾ��ѧ����Ϣ             *\n");
	printf("*         0.�˳�ϵͳ                 *\n");
	printf("**************************************\n");
	
}

void InputStudent(void)
{
	system("cls");
	Node *pNewNode = (Node *)malloc(sizeof(Node));
	pNewNode -> pNext = NULL;
	//ͷ���ж� 
	if(g_pHead == NULL)
	{
		g_pHead = pNewNode;
	}
	else
	{
		pNewNode -> pNext = g_pHead;
		g_pHead = pNewNode;
	}
	
	printf("������ѧ��:");
	scanf("%d",&pNewNode->stu.stuNum);
	printf("����������:");
	scanf("%s",pNewNode->stu.name);
	printf("\n¼��ɹ���\n");
	system("pause");
	system("cls"); 
}

void PrintStudent(void)
{
	system("cls");
	printf("**************************************\n");
	printf("*             ������Ϣ               *\n");
	printf("**************************************\n");
	Node *p = g_pHead;
	if(p == NULL)
	{
		printf("*            ��ѧ����Ϣ              *\n");
	}
	else
	{
		printf("*       ѧ��             ����        *\n");
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
		printf("���ļ�ʧ��\n");
	}
	
	Node *p = g_pHead;
	
	while(p != NULL)
	{
		fwrite(&p->stu,1,sizeof(Student),fp);//д�ṹ�� 1�� 
		p = p->pNext;
	}
	fclose(fp);
	printf("����ɹ�!\n");
	system("pause");
	system("cls");
}

void ReadStudent(void)
{
	FILE *fp = fopen("student.txt","r");
	
	
	if(fp == NULL)
	{
		printf("���ļ�ʧ��\n");
		return; 
	}
	
	Student stu; 
	while(fread(&stu,1,sizeof(Student),fp))
	{
		Node *pNewNode = (Node *)malloc(sizeof(Node));
		pNewNode->pNext = NULL;
		
		memcpy(pNewNode, &stu, sizeof(Student));
		
		//ͷ���ж� 
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
	printf("�Ѷ�ȡ��������.\n");
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
	
	printf("��ǰ����������%d\n",nCount);
	system("pause");
	system("cls");
}

Node *FindStudent(void)
{
	system("cls");
	int nStudNum;
	
	printf("������ѧ��ѧ��:");
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
		printf("*             ѧ����Ϣ               *\n");
		printf("**************************************\n");
		printf("ѧ��:%5d            ����:%s             \n",p->stu.stuNum,p->stu.name);
		printf("**************************************\n");
		printf("�������޸ĵ�ѧ����Ϣ:");
		scanf("%d%*c%s",&p->stu.stuNum,p->stu.name);
		printf("�޸����!\n");
	}
	else
	{
		printf("û���ҵ���ѧ��\n");
	}
	system("pause");
	system("cls");
}

void DeleteStudent(void)
{
	system("cls");
	int nStuNum;
	printf("������ɾ��ѧ��:");
	scanf("%d",&nStuNum);
	Node *current = NULL;
	Node *last = NULL;
	
	if(g_pHead->stu.stuNum == nStuNum)
	{
		current = g_pHead;
		g_pHead = g_pHead->pNext;
		system("cls");
		printf("**************************************\n");
		printf("*         ɾ����ѧ����Ϣ             *\n");
		printf("**************************************\n");
		printf("ѧ��:%5d            ����:%s             \n",current->stu.stuNum,current->stu.name);
		printf("**************************************\n");
		free(current);
		printf("ɾ���ɹ�\n");
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
				printf("*         ɾ����ѧ����Ϣ             *\n");
				printf("**************************************\n");
				printf("ѧ��:%5d            ����:%s             \n",current->stu.stuNum,current->stu.name);
				printf("**************************************\n");
				free(current);
				printf("ɾ���ɹ�\n");
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
		printf("û���ҵ���ѧ��\n");
		system("pause");
		system("cls");
	}
	
}

