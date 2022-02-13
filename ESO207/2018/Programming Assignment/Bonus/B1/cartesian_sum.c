#include <stdio.h>
#include<math.h>

typedef struct complex_number
{
    long double x;
    long double y;
}Z;

Z add(Z a, Z b)
{
    Z sum;
    sum.x=a.x+b.x;
    sum.y=a.y+b.y;
    return sum;
}

Z minus(Z a, Z b)
{
    Z diff;
    diff.x=a.x-b.x;
    diff.y=a.y-b.y;
    return diff;
}

Z multiply(Z a, Z b)
{
    Z prod;
    prod.x=(a.x*b.x)-(a.y*b.y);
    prod.y=(a.x*b.y)+(a.y*b.x);
    return prod;
}

long int power(int n)
{
    long int num=1;
    while(n>num)
        num=num*2;
    return num;
}

long int count(Z C[],long int n)
{
    long int i,c=0;
    for(i=0;i<n;i++)
    {
        if(C[i].x>0.9)
            c++;
    }
    return c;
}

int fft(Z A[], long int n, int flag)
{
    if(n==0)
        return 1;
    long int i;
    Z wn;
    Z* yodd=(Z*)malloc((n/2)*(sizeof(Z)));
    Z* yeven=(Z*)malloc((n/2)*(sizeof(Z)));
    for(i=0;i<n/2;i++)
    {
        yeven[i]=A[2*i];
        yodd[i]=A[(2*i)+1];
    }
    fft(yodd,n/2,flag);
    fft(yeven,n/2,flag);
    for(i=0;i<n/2;i++)
    {
        wn.x=cosl((2*i*acosl(-1))/n);
        wn.y=flag*sinl((2*i*acosl(-1))/n);
        A[i]=add(yeven[i],multiply(wn,yodd[i]));
        A[i+(n/2)]=minus(yeven[i],multiply(wn,yodd[i]));
    }
    return 1;
}

int main()
{
	long int t,n,var,i;
	scanf("%ld",&t);
	while(t--)
	{
	    scanf("%ld",&n);
	    long int num=power(20*(n+1));
	    Z* A=(Z*)malloc(num*(sizeof(Z)));
	    Z* B=(Z*)malloc(num*(sizeof(Z)));
	    for(i=0;i<num;i++)
	    {
	        A[i].x=0;
	        A[i].y=0;
	        B[i].x=0;
	        B[i].y=0;
	    }
	    for(i=0;i<n;i++)
	    {
	        scanf("%ld",&var);
	        A[var].x=A[var].x+1;
	    }
	    for(i=0;i<n;i++)
	    {
	        scanf("%ld",&var);
	        B[var].x=B[var].x+1;
	    }
	    fft(A,num,1);
	    fft(B,num,1);
	    Z* C=(Z*)malloc(num*(sizeof(Z)));
	    for(i=0;i<num;i++)
	        C[i]=multiply(A[i],B[i]);
	    fft(C,num,-1);
	    long int c=count(C,num);
	    printf("%ld\n",c);
	    for(i=0;i<num;i++)
	    {
	        if(C[i].x>0.9)
	            printf("%ld %.0Lf\n", i, (C[i].x)/num);
	    }
	    free(C);
	    free(A);
	    free(B);

	}
}
