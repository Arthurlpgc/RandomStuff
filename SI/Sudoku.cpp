#include <string>
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

string lines[Big];
int quant[Big];
int quantSqr[Big][Big];
int quantLne[Big][Big];
int quantCol[Big][Big];

void putEl(int row,int col,int el){
	quant[el]++;
	quantSqr[int(row/Small)*Small+col/Small][el]++;
	quantLne[row][el]++;
	quantCol[col][el]++;
}

void takeEl(int row,int col,int el){
	quant[el]--;
	quantSqr[int(row/Small)*Small+col/Small][el]--;
	quantLne[row][el]--;
	quantCol[col][el]--;
}

bool can(int row,int col,int el){
	/*cout<<"can "<<row<<" "<<col<<" "<<el<<endl;
	for(int i=0;i<Big;i++)cout<<lines[i]<<endl;
	cout<<(quantLne[row][el]==0&&quantSqr[int(row/Small)*Small+col/Small][el]==0&&quantCol[col][el]==0)<<endl;*/
	return quantLne[row][el]==0&&quantSqr[int(row/Small)*Small+col/Small][el]==0&&quantCol[col][el]==0;
}
int done;
void go(int col,int el){
	if(done)return;
	//cerr<<col<<" "<<el<<endl;
	if(el==Big){
		done=true;
		for(int i=0;i<Big;i++)cout<<lines[i]<<endl;
		return;
	}
	if(quant[el]==Big){
		go(0,el+1);
		return;
	}
	if(quantCol[col][el]){
		go(col+1,el);
		return;
	}
	for(int i=0;!done&&i<Big;i++){
		if(lines[i][col]=='0'&&can(i,col,el)){
			putEl(i,col,el);
			lines[i][col]=el+'0'+1;
			go(col+1,el);
			takeEl(i,col,el);
			lines[i][col]='0';
		}
	}
}

int main(){
	int Ntests;
	cin>>Ntests;
	while(Ntests--){
		done=false;
		int i=0,j=Big;
		memset(quant,0,sizeof quant);
		memset(quantLne,0,sizeof quantLne);
		memset(quantCol,0,sizeof quantCol);
		memset(quantSqr,0,sizeof quantSqr);
		while(j--){
			cin>>lines[i];
			for(int z=0;z<Big;z++)if(lines[i][z]-'0')putEl(i,z,lines[i][z]-'0'-1);
			i++;
		}
		go(0,0);
	}
}
