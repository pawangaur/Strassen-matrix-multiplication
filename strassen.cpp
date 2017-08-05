#include<iostream>
using namespace std;
#define SIZE 20


void display_matrix(int a[SIZE][SIZE],int r,int c)
{
	int i,j;
	for(i=0;i<r;i++)
	{
		for(j=0;j<c;j++)
			cout<<a[i][j]<<" ";
		cout<<endl;
	}
}
void sub_mat(int a[SIZE][SIZE],int b[SIZE][SIZE],int c[SIZE][SIZE],int row,int col)
{
int i,j;
for(i=0;i<row;i++)
for(j=0;j<col;j++)
c[i][j]=a[i][j]-b[i][j];
return;
}
void add_mat(int a[SIZE][SIZE],int b[SIZE][SIZE],int c[SIZE][SIZE],int row,int col)
{
int i,j;
for(i=0;i<row;i++)
for(j=0;j<col;j++)
c[i][j]=a[i][j]+b[i][j];
return;
}

//following function calculate a*b and store it in c :: a,b,c areof size n*n
//n is power of 2 
void strassen_mult(int a[SIZE][SIZE],int b[SIZE][SIZE],int c[SIZE][SIZE],int n)
{
//A matrix=a  b  B matrix is=e f
//         c  d              g h
int temp1[SIZE][SIZE],temp2[SIZE][SIZE],temp3[SIZE][SIZE],temp4[SIZE][SIZE],p1[SIZE][SIZE],p2[SIZE][SIZE],p3[SIZE][SIZE],p4[SIZE][SIZE],p5[SIZE][SIZE],p6[SIZE][SIZE],p7[SIZE][SIZE];
int i,j;

if(n==1)
{
	c[0][0]=a[0][0]*b[0][0];
	return;
}
//p1=a(f-h)
//get h and f
for(i=n/2;i<n;i++)
{
	for(j=n/2;j<n;j++)
		temp1[i-n/2][j-n/2]=b[i][j];
}

for(i=0;i<n/2;i++)
{
	for(j=n/2;j<n;j++)
		temp2[i][j-n/2]=b[i][j];
}

sub_mat(temp2,temp1,temp3,n/2,n/2);

for(i=0;i<n/2;i++)
{
	for(j=0;j<n/2;j++)
		temp2[i][j]=a[i][j];
}

strassen_mult(temp2,temp3,p1,n/2);
display_matrix(p1,n/2,n/2);


// temp1 has h temp2 has a 
//p2=(a+b)h
//get b

for(i=0;i<n/2;i++)
{
	for(j=n/2;j<n;j++)
		temp3[i][j-n/2]=a[i][j];
}
add_mat(temp3,temp2,temp3,n/2,n/2);
strassen_mult(temp3,temp1,p2,n/2);
display_matrix(p2,n/2,n/2);


//p3=(c+d)e
//calculating c,d,e
for(i=n/2;i<n;i++)
{
	for(j=0;j<n/2;j++)
		temp1[i-n/2][j]=a[i][j];
}

for(i=n/2;i<n;i++)
{
	for(j=n/2;j<n;j++)
		temp2[i-n/2][j-n/2]=a[i][j];
}

add_mat(temp1,temp2,temp1,n/2,n/2);

for(i=0;i<n/2;i++)
{
	for(j=0;j<n/2;j++)
		temp3[i][j]=b[i][j];
}

strassen_mult(temp1,temp3,p3,n/2);

display_matrix(p3,n/2,n/2);

// temp2 has d temp3 has e 
//p4=d(g-e)
//get g

for(i=n/2;i<n;i++)
{
	for(j=0;j<n/2;j++)
		temp1[i-n/2][j]=b[i][j];
}
sub_mat(temp1,temp3,temp1,n/2,n/2);
strassen_mult(temp2,temp1,p4,n/2);

display_matrix(p4,n/2,n/2);

// temp2 has d temp3 has e 
//p5=(a+d)(e+h)
//get a

for(i=0;i<n/2;i++)
{
	for(j=0;j<n/2;j++)
		temp1[i][j]=a[i][j];
}
add_mat(temp1,temp2,temp1,n/2,n/2);
//get h
for(i=n/2;i<n;i++)
{
	for(j=n/2;j<n;j++)
		temp4[i-n/2][j-n/2]=b[i][j];
}
add_mat(temp3,temp4,temp3,n/2,n/2);
strassen_mult(temp1,temp3,p5,n/2);

display_matrix(p5,n/2,n/2);

// temp2 has d temp4 has h
//p6=(b-d)(g+h)
//get b
for(i=0;i<n/2;i++)
{
	for(j=n/2;j<n;j++)
		temp1[i][j-n/2]=a[i][j];
}
sub_mat(temp1,temp2,temp1,n/2,n/2);

//get g
for(i=n/2;i<n;i++)
{
	for(j=0;j<n/2;j++)
		temp3[i-n/2][j]=b[i][j];
}
add_mat(temp3,temp4,temp3,n/2,n/2);
strassen_mult(temp1,temp3,p6,n/2);

display_matrix(p6,n/2,n/2);

//p7=(a-c)(e+f)
//get a,c

for(i=0;i<n/2;i++)
{
	for(j=0;j<n/2;j++)
		temp1[i][j]=a[i][j];
}
for(i=n/2;i<n;i++)
{
	for(j=0;j<n/2;j++)
		temp2[i-n/2][j]=a[i][j];
}
sub_mat(temp1,temp2,temp1,n/2,n/2);
//get e,f

for(i=0;i<n/2;i++)
{
	for(j=0;j<n/2;j++)
		temp3[i][j]=b[i][j];
}
for(i=0;i<n/2;i++)
{
	for(j=n/2;j<n;j++)
		temp4[i][j-n/2]=b[i][j];
}
add_mat(temp3,temp4,temp3,n/2,n/2);

strassen_mult(temp1,temp3,p7,n/2);

display_matrix(p7,n/2,n/2);

//get c mattrix

//C matrix=p5+p4-p2+p6  p1+p2 
//         	p3+p4       p1+p5-p3-p7
for(i=0;i<n/2;i++)
{
	for(j=0;j<n/2;j++)
		c[i][j]=p5[i][j]+p4[i][j]-p2[i][j]+p6[i][j];
}
for(i=0;i<n/2;i++)
{
	for(j=0;j<n/2;j++)
		c[i][j+n/2]=p1[i][j]+p2[i][j];
}
for(i=0;i<n/2;i++)
{
	for(j=0;j<n/2;j++)
		c[i+n/2][j]=p3[i][j]+p4[i][j];
}
for(i=0;i<n/2;i++)
{
	for(j=0;j<n/2;j++)
		c[i+n/2][j+n/2]=p1[i][j]+p5[i][j]-p3[i][j]-p7[i][j];
}

return;
}


int main()
{
	int n=2;
	int i,j;
	int mat1[SIZE][SIZE],mat2[SIZE][SIZE],mat3[SIZE][SIZE];
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			cin>>mat1[i][j];
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			cin>>mat2[i][j];
	strassen_mult(mat1,mat2,mat3,n);
	display_matrix(mat3,n,n);
	return 0;
}
