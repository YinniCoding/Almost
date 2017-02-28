//在回溯法前提下解决Almost问题



#include <iostream>
#include <cstring>
#include <fstream>
#include <cmath>
#include <time.h>
#define N 1000
using namespace std;
int w[1000],w2[1000];  //存储已经给定的若干个数,分别为wi和pi两列的数 
int x[1000];  //以0和1来表示数是否加入当前序列 
int M,sum=0; //sum为所有元素总和 
int static count3=0; //用于记录满足条件的wi序列的组合数 
int static count=0,p[100]={0},count4=0; //用来保存满足条件的wi序列对应的满足条件的pi序列 
/*
void Subset(int s,int k,int r，int M) 

s表示当前选中的w[i]*x[i]的值，
k表示当前选择的第几个数，
r为所给元素之和，起到临时变量的作用 
M为所给定值 
*/ 

//使用的各种排序方式进行封装来测试时间 
class SortWays{
	public:
        /*快速排序*/		
		void QuickSort(int r1[],int r2[],int first,int end);
		int Partition(int r1[],int r2[],int first,int end);  //快排第一次划分 
		/*希尔排序*/ 
		void ShellSort(int r1[],int r2[],int n);
        /*堆排序*/		 
        void HeapSort(int r1[],int n);
        void Sift(int k,int m);   //调整为大根堆	
		
		/*测试时间*/
		void TimeTest();		 
};
/*void SortWays::TimeTest() {
	int i;
	cout<<"1、2、3依次表示快速排序、希尔排序、堆排序，选择其中一种来进行原始数据排序：\n";
	cin>>i;
	double start,end;
	switch(i) {
		case 1:
			start=clock();
			QuickSort(w,w2,0,999);
			end=clock();
			cout<<"使用快速排序共花费时间为："<<(end-start)/1000<<"秒。\n";
			break;
		case 2: 
			start=clock();
			ShellSort(w,w2,1000);
			end=clock();
			cout<<"使用快速排序共花费时间为："<<(end-start)/1000<<"秒。\n";
			break;
		case 3:
			start=clock();
			HeapSort(w,1000);
			end=clock();
			cout<<"使用堆排序共花费时间为："<<(end-start)/1000<<"秒。\n";
			break;
		default: 
		    cout<<"请按照要求进行输入！\n";
		    TimeTest();
	}
	
}*/
void Readfile() //读取.in文件,并求取所有元素的和 
{
   ifstream infile("D://软件/数据结构与算法/大二下学期数据结构实习/almost/1000/1000/test.01.in",ios::in);
		if(!infile)
		{
		   cout<<"Error opening file!"<<'\t';
		   exit(1);
	    }
	    int num,wi,pi;
	    //ofstream fout("D://软件/数据结构与算法/大二下学期数据结构实习/almost/1000/1000/test.01.in",ofstream::out);
	    int i=0;
	    while(infile.peek()!=EOF)
		{
			infile>>num>>wi>>pi;
			//cout<<wi<<'\t'<<pi<<'\n';
			w[i]=wi;
			w2[i]=pi; 
			sum+=w[i++];
		}	
} 
int Partition(int r[],int r2[],int first,int end)    //快速排序第一次划分 
{
	int i=first;       //初始化 
	int j=end;
	while(i<j)
	{
		while(i<j && r[i]<=r[j]) j--;     //右侧扫描
		if(i<j)
		{
			int temp=r[i];
			r[i]=r[j];
			r[j]=temp;
			int temp3=r2[i];
			r2[i]=r2[j];
			r2[j]=temp3;
			i++;
		} 
		while(i<j && r[i]<=r[j]) i++;     //左侧扫描
		{
			if(i<j)
			{
				int temp2;
				temp2=r[i];
				r[i]=r[j];
				r[j]=temp2;
				int temp4=r2[i];
				r2[i]=r2[j];
				r2[j]=temp4;
				j--;
			}
		} 
	}
	return i; 
}
void QuickSort(int r[],int r2[],int first,int end)
{
	if(first<end)
	{
		int pivot;
		pivot=Partition(r,r2,first,end);    //一次划分
		QuickSort(r,r2,first,pivot-1);         //递归对左侧序列进行排序
		QuickSort(r,r2,pivot+1,end);           //递归对右侧序列进行排序 
	}
}
void Subset(int s,int k,int r,int M) {
	x[k]=1;
	if(s+w[k]==M)  //如果结果等于M,则输出结果
	{ 
	   count3++;
	   int count2=0,p2[100]={0}; 
	   int j=0;
	   for(int i=0;i<=k;i++) {
	   	//控制值输出x[i]=1,即已经加入数组的数 
	   	if(x[i]==1) 
		   {
		    cout<<w[i]<<'\t';
		    count2+=w2[i];
		    p2[j++]=w2[i];
		   } 
	   }
	   	cout<<'\n';
	   	if(count2>count) {
	   		count=count2;
	   		count4=j;
	   		for(int l=0;l<j;l++)
	   		p[l]=p2[l];
		   } 
	} 
	else if(s+w[k]+w[k+1]<=M) //当往后添加两个元素时，结果仍然<=M,则将当前的第k个元素加入s,k取下一元素，继续递归
	{
		Subset(s+w[k],k+1,r-w[k],M);
	} 
	if ((s+r-w[k])>=M && (s+w[k+1])<=M) //当包括w[k]时，全体元素>=M,并且s+下一个元素的和<=M,则舍弃当前第k个元素，继续下一个 
	{
	  x[k]=0;
	  Subset(s,k+1,r-w[k],M);	
	} 
} 
//搜寻最小值(零头)方法、按照从大到小填充 
void Subset2(int r[],int n) {
	int i,j;          //j用于记录不能再添加元素的最后一个元素位置
	int s1=0;       //已加进来前i个数的和
	for(i=0;i<N;i++) {
		s1+=w[i];
		//临界点条件 
		if(s1<n && (s1+w[i+1])>n) {
			j=i;              //记录最后一个位置
			//n-=s1;         //零头赋给n
			break; 
		}
	} 
	//寻找最小值
	int n2=n-s1;
	for(int k=j+1;k<N;k++) {
		if(n2>w[k]) break;
	    if(n==w[k]) {
	    	cout<<"已找到满足条件的一种wi序列,其中序列元素个数唯一的元素为:\t"<<w[k]<<",满足条件序列最多元素个数为：\t"<<j+1<<'\n';
			return; 
		}	 
	} 
    //搜寻不到最小值
	for(int l=j;l>=0;l--) {
		n2=n-s1+w[l];    //逐步替换零头 
		int n3=n2/2,m;   //折取零头如合适并存储 
		for(int l2=j+1;l2<N;l2++) {
		    if(n3==w[l2] || (n3>w[l2] && n3<w[l2+1])) {
		    	m=l2;
			}	
			int m2=m-1;
			//从m分裂向两端进行检索 
			for(int l3=m2;l3>j;l3++) {
				for(int l4=m;l4<N;l4++) {
					if(w[l3]+w[l4]<n2) {
						cout<<"未找到满足条件的wi序列!\n";
						break; 
					}
					if(w[l3]+w[l4]==n2) {
						cout<<"已找到满足条件的一种wi序列,其中序列元素个数唯一的元素为:\t"<<w[l4]<<",满足条件序列最多元素个数为：\t"<<j+1<<'\n';
					}
				}
			}
		}
	}	 
}
int main() {
	//for(int i=0;i<10;i++)
	//w[i]=i+1;
	//w[10]={1,2,3,4,5,6,7,8,9,10};
	float r; 
	cout<<"请输入指定在0-1范围内的一个r："<<'\n';
	cin>>r;
	Readfile();
	cout<<"所有wi总和为："<<sum<<'\n';
	int c=r*sum;
	cout<<"根据所给r确定的c为："<<c<<'\n'; 
	cout<<"检测pi列前10个元素：\n";
	for(int l=0;l<10;l++)
	cout<<w2[l]<<'\t';
	cout<<'\n';
	QuickSort(w,w2,0,999);
	cout<<"测试使用快排后的wi列前10个数据："<<'\n';
	for(int i=0;i<10;i++)
	cout<<w[i]<<'\t';
	cout<<'\n'; 
//	QuickSort(w2,0,999);
	cout<<"测试使用快排后的pi列前10个数据是否与wi相对应："<<'\n';
	for(int m=0;m<10;m++)
	cout<<w2[m]<<'\t';
	cout<<'\n';
	cout<<"所有可能序列元素之为"<<c<<"的具体组合如下：\n"; 
	Subset(0,0,sum,c);
	cout<<"共有这样的组合"<<count3<<"组\n"; 
	cout<<"满足条件的wi组合对应的pi组合其和最大的序列为：\n";
	for(int j=0;j<count4;j++)
	cout<<p[j]<<'\t';
	cout<<'\n';
	Subset2(w,c);
	return 0;
}
