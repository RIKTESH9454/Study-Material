#include <stdio.h>

long int msort(long int arr[],long int sarr[],long int f,long int mid,long int l);

long int count(long int arr[],long int sarr[],long int f,long int l)
{
    if(l<=f)
        return 0;
    long int inv=0;
    long int mid=(f+l)/2;
    inv+=count(arr,sarr,f,mid)+count(arr,sarr,mid+1,l);
    inv+=msort(arr,sarr,f,mid,l);
    return inv;
}

long int msort(long int arr[],long int sarr[],long int f,long int mid,long int l)
{
    long int i=f,j=mid+1,k=f;
    long int inv=0;
    while((i<=mid)&&(j<=l))
    {
        if(arr[i]>2*arr[j])
        {
            inv+=(mid-i+1);
            j++;
        }
        else
            i++;
    }

    i=f;
    j=mid+1;

    while((i<=mid)&&(j<=l))
    {
        if(arr[i]<=arr[j])
            sarr[k++]=arr[i++];
        else
            sarr[k++]=arr[j++];
    }
    while(i<=mid)
        sarr[k++]=arr[i++];
    while(j<=l)
        sarr[k++]=arr[j++];

    for(i=f;i<=l;i++)
        arr[i]=sarr[i];

    return inv;
}

int main(){
	long int t,n,i;
	scanf("%ld",&t);
	while(t--)
	{
	    scanf("%ld",&n);
	    long int* arr= (long int*)malloc(n*(sizeof(long int)));
	    long int *sorted= (long int*)malloc(n*(sizeof(long int)));
	    for(i=0;i<n;i++)
	        scanf("%ld",&arr[i]);
	    printf("%ld\n",count(arr,sorted,0,n-1));
	    free(arr);
	    free(sorted);
	}
}
