#include <stdio.h>
#include <stdlib.h>

#define num 100

class mydata
{
public:
	int i;//行
	int j;//列
	mydata(){};
	mydata(int x,int y):i(x),j(y){};
};

class stack
{
public:
	mydata data[num];
	int top;
	void push(mydata x);//入栈
	mydata pop();//出栈
	bool Full();//栈满
	bool Empty();//栈空
	stack():top(-1){};
	void copy(stack *s);//栈内内容复制
};

void stack::push(mydata x)//入栈
{
	if(top<num-1)    data[++top]=x;
}

mydata stack::pop()//出栈
{
	if(top>-1)    return data[top--];
}

bool stack::Full()//栈满
{
	return (top==num-1)?true:false;
}

bool stack::Empty()//栈空
{
	return (top==-1)?true:false;
}

void stack::copy(stack *s)//栈内内容复制
{
	for(int i=0;i<=s->top;i++)
	{
		push(s->data[i]);
	}
}

int main()
{
	int a[8];//第j列有无皇后
	int b[15];//第(i-j+7)主对角线(左上至右下)有无皇后
	int c[15];//第(i+j)副对角线(右上至左下)有无皇后
	int number=0;//符合条件的总数
	for(int i=0;i<8;i++)     a[i]=0;
	for(int i=0;i<15;i++)    b[i]=0;
	for(int i=0;i<15;i++)    c[i]=0;
	stack *s=new stack;
	int result[100][8];//用于最终存储符合条件的8个皇后的位置(第i行的皇后在第?列)
	int i=0,j=0;
	//freopen("out.txt","w",stdout);
	while(i<8)//逐行扫描
	{
		if(j>=8)//当栈顶元素已经j=7时，弹栈后j+1后则j=8，说明此行仍无法满足要求，则继续弹栈
		{
			if(s->Empty())//如果j=8时且栈已空，则说明弹栈前栈里只有一个元素(第0行，i=0)，且值为7(j=7)，则说明所有方法已经全部枚举完毕，退出最外层循环即可
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
		while(j<8)//逐列扫描
		{
			if(a[j]==0 && b[i-j+7]==0 && c[i+j]==0)//找到了符合第i个皇后(第i行)条件的位置(此行第j列)
			{
				mydata md(i,j);
				s->push(md);
				a[j]=1;
				b[i-j+7]=1;
				c[i+j]=1;
				result[number][i]=j;//第i行的皇后在第j列
				if(i==7)//第8个皇后已经成功放置，8个皇后的位置均符合条件
				{
					for(int k=0;k<8;k++)    printf("result[%d][%d]=%d\t",number,k,result[number][k]);
					printf("\n");
					for(int k=0;k<8;k++)    result[number+1][k]=result[number][k];//由于整体采用回溯算法，当弹栈时如果没有将栈弹空，如果此处不赋值，则数组中内容前几行与上一种情况相同的部分(栈内剩余的部分)将永远未赋值
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
				else//8个皇后尚未全部放置，继续放置第(i+1)个皇后
				{
					i++;//继续下一行
				    j=0;//下一行从第0列开始扫描
				    break;
				}
			}
			else if(j==7)//此行的8列扫描完毕却未发现可以放置第i个皇后的位置
			{
				mydata md=s->pop();
				i=md.i;
				j=md.j;
				a[j]=0;
				b[i-j+7]=0;
				c[i+j]=0;
			    j++;
			}
			else//此行的8列尚未全部扫描完毕，继续计算此行的第(j+1)列是否符合要求
			{
				j++;//继续扫描下一列
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