#include <iostream>
#include <malloc.h>
#include <vector>
#include <climits>

using namespace std;
struct node {
    long long int v;
    long long int w;
};

struct MinHeap
{
    long long int size ;
    long long int *array ;
};
long long int dist[100005],pos[100005];

void swap(long long int *n1, long long int *n2) {
    long long int temp = *n1 ;
    *n1 = *n2 ;
    *n2 = temp ;
}
 
void heapify(MinHeap *hp, long long int i) {
	long long int smallest, left, right;
    smallest = i;
    left = 2 * i + 1;
    right = 2 * i + 2;
    if (left < hp->size && dist[hp->array[left]] < dist[hp->array[smallest]] )
      smallest = left;
 
    if (right < hp->size && dist[hp->array[right]] < dist[hp->array[smallest]] )
      smallest = right;
    if(smallest != i) {
    	long long int temp=pos[hp->array[i]];
    	pos[hp->array[i]]=pos[hp->array[smallest]];
    	pos[hp->array[smallest]]=temp;
        swap(&(hp->array[i]), &(hp->array[smallest])) ;
        heapify(hp, smallest) ;
    }
}
 
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
    long long int i,j,k,n,s,c1,c2,d,d1,d2,w1,w2,w3,degree;
    cin>>n>>s>>d>>c1>>c2>>d1>>d2>>w1>>w2>>w3;
    c2%=d;d2%=d;
    c1%=n;d1%=n;
    w1%=w3;w2%=w3;
    vector<node> adj[n+1];
    for(i=1;i<=n;i++){
        degree = ((i*c2)%d+(i*i*d2)%d)%d;
        for(j=1;j<=degree;j++){
            long long int v=((i*c1)%n+(j*d1)%n)%n+1;
            long long int w=((i*w1)%w3+(j*w2)%w3)%w3;
            if(v==i)continue;
            node vw;
            vw.v=v;
            vw.w=w;
            adj[i].push_back(vw);
        }
    }
    
    long long int* arr=(long long int*)malloc(n*sizeof(long long int));
    for(i=0;i<n;i++){arr[i]=i+1;}
    arr[s-1]=1;arr[0]=s;
	
	for(i=1;i<=n;i++){dist[i]=INT_MAX;pos[i]=i-1;}
	dist[s]=0;
	pos[s]=0;pos[1]=s-1;

	struct MinHeap* hp = (struct MinHeap*) malloc(sizeof(struct MinHeap));
	hp->size=n;
	hp->array=arr;
	//for(i=1;i<=n;i++)cout<<i<<" "<<dist[i]<<" "<<pos[i]<<'\n';

	for(i=0;i<adj[s].size();i++){
		long long int v=adj[s][i].v;
		long long int w=adj[s][i].w;
		dist[v]=w;
	}
	for(i = (hp->size - 1) / 2; i >= 0; i--) {
        heapify(hp, i) ;
    }
	//for(i=1;i<=n;i++)cout<<i<<" "<<dist[i]<<" "<<pos[i]<<'\n';

    while(hp->size>0){
    	long long int mi=hp->array[0];
    	pos[hp->array[hp->size-1]]=0;
    	pos[mi]=hp->size-1;
    	hp->array[0]=hp->array[hp->size-1];
    	hp->array[hp->size-1]= mi;
    	hp->size--;
    	heapify(hp,0);
    	//cout<<mi<<'\n';
    	//for(i=1;i<=n;i++)cout<<i<<" "<<dist[i]<<" "<<pos[i]<<'\n';

    	//cout<<'\n';
    	//for(i=1;i<=n;i++)cout<<pos[i]<<" ";

    	//cout<<'\n';
    	for(i=0;i<adj[mi].size();i++){
			long long int v=adj[mi][i].v;
			long long int w=adj[mi][i].w;
			if(pos[v]>=hp->size)continue;
			if((dist[mi]+w)<dist[v])dist[v]=w+dist[mi];
			//heapify(hp,pos[v]);
			j=pos[v];
			while (j>0 && dist[v] < dist[hp->array[(j - 1) / 2]])
			    {
			        // Swap this node with its parent

			        pos[v] = (j-1)/2;
			        pos[hp->array[(j-1)/2]] = j;
			        swap(&(hp->array[j]),  &(hp->array[(j - 1) / 2]));
			 
			        // move to parent index
			        j = (j - 1) / 2;
			    }
		}
		//for(i=1;i<=n;i++)cout<<i<<" after "<<dist[i]<<" "<<pos[i]<<'\n';
    }

    for(i=1;i<=n;i++){
    	if(dist[i]==INT_MAX)dist[i]=-1;
    	cout<<i<<" "<<dist[i]<<'\n';
    }
    // for(i=1;i<=n;i++){
    //     for(j=0;j<adj[i].size();j++)cout<<adj[i][j].v<<" "<<adj[i][j].w<<'\t';
    //     cout<<'\n';
    // }
    return 0;
}