#include <bits/stdc++.h>
#define f(a,b,c) for(int a=b;a<c;a++)
#define frg(a,b) for(int a=adj[b];~a;a=ant[a])
using namespace std;
typedef long long ll;
vector<pair<double,double> > v;
long long coeficientesFixos[10000];//equivalente ao binomio de newton
double t,subT;//t=t do ponto atual, subT= 1-t, do ponto atual
double tArr[10000],subTArr[10000];//array que guarda as potencias
int main(){//Geraçao de Bezier em O(N^2+NP) por bernstein, em contraste com a geraçao em O(N^2*P) feita por de casteljau
	int p,n;double a,b;//p= numero de pontos gerados,n=numeros de pontos que caracterizam a curva
	scanf("%d%d",&n,&p);
	for(int i=0;i<n;i++){
		scanf("%lf%lf",&a,&b);
		v.push_back(make_pair(a,b));
	}
	coeficientesFixos[1]=1;
	for(int i=1;i<n;i++){//O(N^2), para gerar os binomios de newton
		for(int j=i+1;j>=1;j--){
			coeficientesFixos[j]=coeficientesFixos[j]+coeficientesFixos[j-1];
		}
	}p--;
	tArr[0]=subTArr[0]=1;
	for(int i=0;i<=p;i++){//O(P*N)
		t=double(i)/double(p);
		subT=1-t;
		for(int j=1;j<n;j++){//Preprocessando potencias em O(N)
			tArr[j]=t*tArr[j-1];
			subTArr[j]=subT*subTArr[j-1];
		}
		a=b=0;
		for(int j=0;j<n;j++){//fazendo a formula em O(N)
			a+=tArr[j]*subTArr[n-j-1]*double(coeficientesFixos[j+1])*v[j].first;
			b+=tArr[j]*subTArr[n-j-1]*double(coeficientesFixos[j+1])*v[j].second;
		}
		printf("(%lf,%lf)\n",a,b);
	}
}
