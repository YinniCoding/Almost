//�ڻ��ݷ�ǰ���½��Almost����



#include <iostream>
#include <cstring>
#include <fstream>
#include <cmath>
#include <time.h>
#define N 1000
using namespace std;
int w[1000],w2[1000];  //�洢�Ѿ����������ɸ���,�ֱ�Ϊwi��pi���е��� 
int x[1000];  //��0��1����ʾ���Ƿ���뵱ǰ���� 
int M,sum=0; //sumΪ����Ԫ���ܺ� 
int static count3=0; //���ڼ�¼����������wi���е������ 
int static count=0,p[100]={0},count4=0; //������������������wi���ж�Ӧ������������pi���� 
/*
void Subset(int s,int k,int r��int M) 

s��ʾ��ǰѡ�е�w[i]*x[i]��ֵ��
k��ʾ��ǰѡ��ĵڼ�������
rΪ����Ԫ��֮�ͣ�����ʱ���������� 
MΪ������ֵ 
*/ 

//ʹ�õĸ�������ʽ���з�װ������ʱ�� 
class SortWays{
	public:
        /*��������*/		
		void QuickSort(int r1[],int r2[],int first,int end);
		int Partition(int r1[],int r2[],int first,int end);  //���ŵ�һ�λ��� 
		/*ϣ������*/ 
		void ShellSort(int r1[],int r2[],int n);
        /*������*/		 
        void HeapSort(int r1[],int n);
        void Sift(int k,int m);   //����Ϊ�����	
		
		/*����ʱ��*/
		void TimeTest();		 
};
/*void SortWays::TimeTest() {
	int i;
	cout<<"1��2��3���α�ʾ��������ϣ�����򡢶�����ѡ������һ��������ԭʼ��������\n";
	cin>>i;
	double start,end;
	switch(i) {
		case 1:
			start=clock();
			QuickSort(w,w2,0,999);
			end=clock();
			cout<<"ʹ�ÿ������򹲻���ʱ��Ϊ��"<<(end-start)/1000<<"�롣\n";
			break;
		case 2: 
			start=clock();
			ShellSort(w,w2,1000);
			end=clock();
			cout<<"ʹ�ÿ������򹲻���ʱ��Ϊ��"<<(end-start)/1000<<"�롣\n";
			break;
		case 3:
			start=clock();
			HeapSort(w,1000);
			end=clock();
			cout<<"ʹ�ö����򹲻���ʱ��Ϊ��"<<(end-start)/1000<<"�롣\n";
			break;
		default: 
		    cout<<"�밴��Ҫ��������룡\n";
		    TimeTest();
	}
	
}*/
void Readfile() //��ȡ.in�ļ�,����ȡ����Ԫ�صĺ� 
{
   ifstream infile("D://���/���ݽṹ���㷨/�����ѧ�����ݽṹʵϰ/almost/1000/1000/test.01.in",ios::in);
		if(!infile)
		{
		   cout<<"Error opening file!"<<'\t';
		   exit(1);
	    }
	    int num,wi,pi;
	    //ofstream fout("D://���/���ݽṹ���㷨/�����ѧ�����ݽṹʵϰ/almost/1000/1000/test.01.in",ofstream::out);
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
int Partition(int r[],int r2[],int first,int end)    //���������һ�λ��� 
{
	int i=first;       //��ʼ�� 
	int j=end;
	while(i<j)
	{
		while(i<j && r[i]<=r[j]) j--;     //�Ҳ�ɨ��
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
		while(i<j && r[i]<=r[j]) i++;     //���ɨ��
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
		pivot=Partition(r,r2,first,end);    //һ�λ���
		QuickSort(r,r2,first,pivot-1);         //�ݹ��������н�������
		QuickSort(r,r2,pivot+1,end);           //�ݹ���Ҳ����н������� 
	}
}
void Subset(int s,int k,int r,int M) {
	x[k]=1;
	if(s+w[k]==M)  //����������M,��������
	{ 
	   count3++;
	   int count2=0,p2[100]={0}; 
	   int j=0;
	   for(int i=0;i<=k;i++) {
	   	//����ֵ���x[i]=1,���Ѿ������������ 
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
	else if(s+w[k]+w[k+1]<=M) //�������������Ԫ��ʱ�������Ȼ<=M,�򽫵�ǰ�ĵ�k��Ԫ�ؼ���s,kȡ��һԪ�أ������ݹ�
	{
		Subset(s+w[k],k+1,r-w[k],M);
	} 
	if ((s+r-w[k])>=M && (s+w[k+1])<=M) //������w[k]ʱ��ȫ��Ԫ��>=M,����s+��һ��Ԫ�صĺ�<=M,��������ǰ��k��Ԫ�أ�������һ�� 
	{
	  x[k]=0;
	  Subset(s,k+1,r-w[k],M);	
	} 
} 
//��Ѱ��Сֵ(��ͷ)���������մӴ�С��� 
void Subset2(int r[],int n) {
	int i,j;          //j���ڼ�¼���������Ԫ�ص����һ��Ԫ��λ��
	int s1=0;       //�Ѽӽ���ǰi�����ĺ�
	for(i=0;i<N;i++) {
		s1+=w[i];
		//�ٽ������ 
		if(s1<n && (s1+w[i+1])>n) {
			j=i;              //��¼���һ��λ��
			//n-=s1;         //��ͷ����n
			break; 
		}
	} 
	//Ѱ����Сֵ
	int n2=n-s1;
	for(int k=j+1;k<N;k++) {
		if(n2>w[k]) break;
	    if(n==w[k]) {
	    	cout<<"���ҵ�����������һ��wi����,��������Ԫ�ظ���Ψһ��Ԫ��Ϊ:\t"<<w[k]<<",���������������Ԫ�ظ���Ϊ��\t"<<j+1<<'\n';
			return; 
		}	 
	} 
    //��Ѱ������Сֵ
	for(int l=j;l>=0;l--) {
		n2=n-s1+w[l];    //���滻��ͷ 
		int n3=n2/2,m;   //��ȡ��ͷ����ʲ��洢 
		for(int l2=j+1;l2<N;l2++) {
		    if(n3==w[l2] || (n3>w[l2] && n3<w[l2+1])) {
		    	m=l2;
			}	
			int m2=m-1;
			//��m���������˽��м��� 
			for(int l3=m2;l3>j;l3++) {
				for(int l4=m;l4<N;l4++) {
					if(w[l3]+w[l4]<n2) {
						cout<<"δ�ҵ�����������wi����!\n";
						break; 
					}
					if(w[l3]+w[l4]==n2) {
						cout<<"���ҵ�����������һ��wi����,��������Ԫ�ظ���Ψһ��Ԫ��Ϊ:\t"<<w[l4]<<",���������������Ԫ�ظ���Ϊ��\t"<<j+1<<'\n';
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
	cout<<"������ָ����0-1��Χ�ڵ�һ��r��"<<'\n';
	cin>>r;
	Readfile();
	cout<<"����wi�ܺ�Ϊ��"<<sum<<'\n';
	int c=r*sum;
	cout<<"��������rȷ����cΪ��"<<c<<'\n'; 
	cout<<"���pi��ǰ10��Ԫ�أ�\n";
	for(int l=0;l<10;l++)
	cout<<w2[l]<<'\t';
	cout<<'\n';
	QuickSort(w,w2,0,999);
	cout<<"����ʹ�ÿ��ź��wi��ǰ10�����ݣ�"<<'\n';
	for(int i=0;i<10;i++)
	cout<<w[i]<<'\t';
	cout<<'\n'; 
//	QuickSort(w2,0,999);
	cout<<"����ʹ�ÿ��ź��pi��ǰ10�������Ƿ���wi���Ӧ��"<<'\n';
	for(int m=0;m<10;m++)
	cout<<w2[m]<<'\t';
	cout<<'\n';
	cout<<"���п�������Ԫ��֮Ϊ"<<c<<"�ľ���������£�\n"; 
	Subset(0,0,sum,c);
	cout<<"�������������"<<count3<<"��\n"; 
	cout<<"����������wi��϶�Ӧ��pi��������������Ϊ��\n";
	for(int j=0;j<count4;j++)
	cout<<p[j]<<'\t';
	cout<<'\n';
	Subset2(w,c);
	return 0;
}
