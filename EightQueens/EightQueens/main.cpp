#include <stdio.h>
#include <stdlib.h>

#define num 100

class mydata
{
public:
	int i;//��
	int j;//��
	mydata(){};
	mydata(int x,int y):i(x),j(y){};
};

class stack
{
public:
	mydata data[num];
	int top;
	void push(mydata x);//��ջ
	mydata pop();//��ջ
	bool Full();//ջ��
	bool Empty();//ջ��
	stack():top(-1){};
	void copy(stack *s);//ջ�����ݸ���
};

void stack::push(mydata x)//��ջ
{
	if(top<num-1)    data[++top]=x;
}

mydata stack::pop()//��ջ
{
	if(top>-1)    return data[top--];
}

bool stack::Full()//ջ��
{
	return (top==num-1)?true:false;
}

bool stack::Empty()//ջ��
{
	return (top==-1)?true:false;
}

void stack::copy(stack *s)//ջ�����ݸ���
{
	for(int i=0;i<=s->top;i++)
	{
		push(s->data[i]);
	}
}

int main()
{
	int a[8];//��j�����޻ʺ�
	int b[15];//��(i-j+7)���Խ���(����������)���޻ʺ�
	int c[15];//��(i+j)���Խ���(����������)���޻ʺ�
	int number=0;//��������������
	for(int i=0;i<8;i++)     a[i]=0;
	for(int i=0;i<15;i++)    b[i]=0;
	for(int i=0;i<15;i++)    c[i]=0;
	stack *s=new stack;
	int result[100][8];//�������մ洢����������8���ʺ��λ��(��i�еĻʺ��ڵ�?��)
	int i=0,j=0;
	//freopen("out.txt","w",stdout);
	while(i<8)//����ɨ��
	{
		if(j>=8)//��ջ��Ԫ���Ѿ�j=7ʱ����ջ��j+1����j=8��˵���������޷�����Ҫ���������ջ
		{
			if(s->Empty())//���j=8ʱ��ջ�ѿգ���˵����ջǰջ��ֻ��һ��Ԫ��(��0�У�i=0)����ֵΪ7(j=7)����˵�����з����Ѿ�ȫ��ö����ϣ��˳������ѭ������
			{
				break;
			}
			mydata md=s->pop();
			i=md.i;
			j=md.j;
			a[j]=0;
			b[i-j+7]=0;
			c[i+j]=0;
			j++;
		}
		while(j<8)//����ɨ��
		{
			if(a[j]==0 && b[i-j+7]==0 && c[i+j]==0)//�ҵ��˷��ϵ�i���ʺ�(��i��)������λ��(���е�j��)
			{
				mydata md(i,j);
				s->push(md);
				a[j]=1;
				b[i-j+7]=1;
				c[i+j]=1;
				result[number][i]=j;//��i�еĻʺ��ڵ�j��
				if(i==7)//��8���ʺ��Ѿ��ɹ����ã�8���ʺ��λ�þ���������
				{
					for(int k=0;k<8;k++)    printf("result[%d][%d]=%d\t",number,k,result[number][k]);
					printf("\n");
					for(int k=0;k<8;k++)    result[number+1][k]=result[number][k];//����������û����㷨������ջʱ���û�н�ջ���գ�����˴�����ֵ��������������ǰ��������һ�������ͬ�Ĳ���(ջ��ʣ��Ĳ���)����Զδ��ֵ
					number++;
					mydata md=s->pop();
				    i=md.i;
				    j=md.j;
				    a[j]=0;
				    b[i-j+7]=0;
				    c[i+j]=0;
				    j++;
				    break;
				}
				else//8���ʺ���δȫ�����ã��������õ�(i+1)���ʺ�
				{
					i++;//������һ��
				    j=0;//��һ�дӵ�0�п�ʼɨ��
				    break;
				}
			}
			else if(j==7)//���е�8��ɨ�����ȴδ���ֿ��Է��õ�i���ʺ��λ��
			{
				mydata md=s->pop();
				i=md.i;
				j=md.j;
				a[j]=0;
				b[i-j+7]=0;
				c[i+j]=0;
			    j++;
			}
			else//���е�8����δȫ��ɨ����ϣ�����������еĵ�(j+1)���Ƿ����Ҫ��
			{
				j++;//����ɨ����һ��
			}
		}
	}
	delete s;
	printf("number=%d\n",number);
	//fclose(stdout);
	//freopen("con","w",stdout);
	system("pause");
	//fclose(stdout);
	return 0;
}