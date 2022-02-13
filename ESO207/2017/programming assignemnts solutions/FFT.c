
#include <stdio.h>
#include <math.h>
#include <stdlib.h> 

typedef struct complexnum
{
    double x;
    double y;
}comp;

comp make(double x1, double y1)
{
    comp num;
    num.x=x1;
    num.y=y1;
    return num;
}
comp multiply(comp c1,comp c2)
{
    comp prod;
    prod.x=(c1.x)*(c2.x)-(c1.y)*(c2.y);
    prod.y=(c1.x)*(c2.y)+(c1.y)*(c2.x);
    return prod;
}

comp add(comp c1,comp c2)
{
    comp sum;
    sum.x=(c1.x)+(c2.x);
    sum.y=(c1.y)+(c2.y);
    return sum;
}

comp subtract(comp c1,comp c2)
{
    comp diff;
    diff.x=(c1.x)-(c2.x);
    diff.y=(c1.y)-(c2.y);
    return diff;
}

int FFT(comp coeff[],int n,int f)
{
    if(n==0)
        return 1;
    comp W,w;
    w.x=1;
    w.y=0;
    W.x=cos(2*acos(-1)/n);
    W.y=f*sin(2*acos(-1)/n);
    comp coeffeven[n/2],coeffodd[n/2];
    for(int i=0;i<n/2;i++)
    {
        coeffeven[i].x=coeff[2*i].x;
        coeffeven[i].y=coeff[2*i].y;
        coeffodd[i].x=coeff[2*i+1].x;
        coeffodd[i].y=coeff[2*i+1].y;
    }
    FFT(coeffeven,n/2,f);
    FFT(coeffodd,n/2,f);
    for(int k=0;k<n/2;k++)
    {
        coeff[k]=add(coeffeven[k],multiply(w,coeffodd[k]));
        coeff[n/2+k]=subtract(coeffeven[k],multiply(w,coeffodd[k]));
        w=multiply(w,W);
    }
    return 1;
}


int main()
{
    int t,f,n;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&f,&n);
        comp coeff[n];
        double x,y;
        for(int i=0;i<n;i++)
        {
            scanf("%lf",&x);
            scanf("%lf",&y);
            coeff[i]=make(x,y);
        }
        if(f==0)
            FFT(coeff,n,1);
        else
            FFT(coeff,n,-1);
        for(int i=0;i<n;i++)
            if(f==0)
                printf("%.6lf %.6lf\n",coeff[i].x,coeff[i].y);
            else
                printf("%.6lf %.6lf\n",coeff[i].x/n,coeff[i].y/n);
    }
    return 0;
}
