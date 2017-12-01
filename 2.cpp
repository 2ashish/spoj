#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

struct node{
	int index,finish;
};

bool comp(node x,node y){
	return (x.finish<y.finish);
}

bool comp1(node x,node y){
	return (x.index<y.index);
}

void rDFS(vector<int> radj[],int i,stack<int> &st,vector<int> &visit){
	visit[i]=1;
	st.push(i);
	for(int j=0;j<radj[i].size();j++){
		if(visit[radj[i][j]]==0){
			rDFS(radj,radj[i][j],st,visit);
			//radj[i].erase(radj[i].begin()+j);j--;
		}
	}
}

void DFS(vector<int> adj[],int i,vector<int> &visit,vector<int> &s,vector<int> &f,int &count){
	visit[i]=1;
	s[i]=count;count++;
	for(int j=0;j<adj[i].size();j++){
		if(visit[adj[i][j]]==0)DFS(adj,adj[i][j],visit,s,f,count);
	}
	f[i]=count;count++;
}

int main() {
	// your code goes here
	int n,i,j,k,count=0;
	cin>>n;
	vector<int> adj[n],radj[n],visit(n,0),s(n),f(n);
	for(i=0;i<n;i++){
		cin>>k;
		while(k!=-1){
			adj[i].push_back(k);
			radj[k].push_back(i);
			cin>>k;
		}
	}
	
	for(i=0;i<n;i++){
		if(visit[i]==0)DFS(adj,i,visit,s,f,count);
	}

	//for(i=0;i<n;i++)cout<<s[i]<<" "<<f[i]<<'\n';
	vector<node> v(n);
	for(i=0;i<n;i++){
		v[i].index=i;
		v[i].finish=f[i];
		visit[i]=0;
	}
	sort(v.begin(),v.end(),comp);
	//for(i=0;i<n;i++)cout<<v[i].index<<" "<<v[i].finish<<'\n';
	vector<int> scc(n);
	for(i=n-1;i>=0;i--){
		stack<int> st,st1;
		int mins=100000;
		if(visit[v[i].index]==0)rDFS(radj,v[i].index,st,visit);	
		while(!st.empty()){
			k=st.top();st.pop();
			if(k<mins)mins=k;
			st1.push(k);
		}
		while(!st1.empty()){
			k=st1.top();st1.pop();
			scc[k]=mins;
		}
	}
//	for(i=0;i<n;i++)cout<<scc[i]<<" ";
	
	vector<node> v1(n);
	for(i=0;i<n;i++){
		v1[i].index=i;
		v1[i].finish=scc[i];
	}
	sort(v1.begin(),v1.end(),comp);
	count=0;
	for(i=0;i<n;i++){
		k=v1[i].finish;
		v1[i].finish=count;
		if(i<(n-1)&&v1[i+1].finish==k);
		else count++;
	}
	sort(v1.begin(),v1.end(),comp1);
	for(i=0;i<n;i++){scc[i]=v1[i].finish;}

	cout<<count<<'\n';
	vector<int> fadj[count];
	for(i=0;i<n;i++){
		for(j=0;j<adj[i].size();j++){
			k=adj[i][j];
			if(scc[i]!=scc[k])fadj[scc[i]].push_back(scc[k]);
		}
	}

	for(i=0;i<count;i++){
		sort(fadj[i].begin(),fadj[i].end());
		for(j=0;j<fadj[i].size();j++){
			if(j>0&&fadj[i][j]==fadj[i][j-1])continue;
			cout<<fadj[i][j]<<" ";
		}
		cout<<"-1"<<'\n';
	}
	
//	for(i=0;i<n;i++)if(adj[i].size()!=0)cout<<adj[i][0]<<'\n';
	return 0;
}
