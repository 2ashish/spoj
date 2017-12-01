#include <iostream>
#include <stdio.h>
#include <vector>
#include <cmath>
#define pi acos(-1.0)
using namespace std;
struct com{
	double r,i;
};
void fft(int n,vector<com> &v,vector<com> &f,double x,double y){
	if(n==1){f[0].r=v[0].r;f[0].i=v[0].i;return;}
	com q;int i,j;
	vector<com> ve(n/2),vo(n/2),fe(n/2),fo(n/2);
	for(i=0;i<n/2;i++){
		ve[i]=v[2*i];vo[i]=v[2*i+1];
	}
	fft(n/2,ve,fe,x*x-y*y,2*x*y);
	fft(n/2,vo,fo,x*x-y*y,2*x*y);
	q.r=1;q.i=0;com ans;
	for(i=0;i<n/2;++i){
		
		ans.r=q.r*fo[i].r-q.i*fo[i].i;
		ans.i=q.r*fo[i].i+q.i*fo[i].r;
		f[i].r=fe[i].r+ans.r;
		f[i].i=fe[i].i+ans.i;
		f[i+(n/2)].r=fe[i].r-ans.r;
		f[i+(n/2)].i=fe[i].i-ans.i;
		ans.r=q.r*x-q.i*y;
		ans.i=q.r*y+q.i*x;
		q.r=ans.r;q.i=ans.i;
	}
}
int main() {
	// your code goes here
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t;
	cin>>t;
	while(t--){
		int op,n,i,jk;
		cin>>op>>n;
		com un;
		vector<com> v(n),f(n);
		for(i=0;i<n;i++)cin>>v[i].r>>v[i].i;
		un.r=cos(2*pi/n);
		un.i=sin(2*pi/n);if(op)un.i=-un.i;
		fft(n,v,f,un.r,un.i);
		if(op)for(i=0;i<n;i++){f[i].r/=n;f[i].i/=n;}
		for(i=0;i<n;i++){
			printf("%.6lf %.6lf\n",f[i].r,f[i].i);
		}
	}
	return 0;
}

