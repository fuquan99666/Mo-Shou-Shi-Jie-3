//不容易啊

#include<iostream>
#include<string>
#include<iomanip>
#include<cstring>
#include<vector>
using namespace std;

//记录时间
int shi=0;
int fen=0;
int K;

//补全时间中的0
string bu(int shi){
	string bui;
	if (shi <= 9) {
		bui = "00";
	}
	if (shi > 9 and shi <= 99) {
		bui = "0";
	}
	if (shi > 99) {
		bui = "";
	}
	return bui;
}


string habu(int fen){
	string habui;
	if(fen<=9){
		habui="0";
	}
	if(fen>9 ){
		habui="";
	}
	return habui;
}

//每次事件的时间报告
void baoshi(int shi,int fen){
	string bushi=bu(shi);
	string bufen=habu(fen);
	cout << bushi << shi << ":" << bufen <<fen << " ";
}

vector <string> wuqixuanze={"sword","bomb","arrow"};

int shengmingzhi[5]={0};

int gongjili[5]={0};

string zhonglei[5]={"dragon","ninja","iceman","lion","wolf"};
string redlei[5]={"iceman","lion","wolf","ninja","dragon"};//没有变化
string bluelei[5]={"lion","dragon","ninja","iceman","wolf"};//没有变化

int redfei[5]={0};
int bluefei[5]={0};

class city{
	public:
	string flag;
	int xuhao;
	int life=0;
	bool b=false;
	bool r=false;
	int blue=0;
	int red=0;
	int redsha=0;
	int bluesha=0;
	int zhankuang=0;//如果战况是0，说明目前没有发生战争胜负，如果是1，说明红方胜利一次，2就是连续两次，蓝方相反
	city(int n)
	{
		xuhao=n;
		flag="";
	}
};

void feishe(){
	redfei[0]=shengmingzhi[2];
	redfei[1]=shengmingzhi[3];
	redfei[2]=shengmingzhi[4];
	redfei[3]=shengmingzhi[1];
	redfei[4]=shengmingzhi[0];
	bluefei[0]=shengmingzhi[3];
	bluefei[1]=shengmingzhi[0];
	bluefei[2]=shengmingzhi[1];
	bluefei[3]=shengmingzhi[2];
	bluefei[4]=shengmingzhi[4];
}

class wuqi{
	public:
	string zhonglei;
	int gongjili;
	int ci;//还能用多少次
	void yingshe(string a,int& ci){
		if(a=="sword"){
			ci=1000;
		}
		if(a=="bomb"){
			ci=1;
		}
		if(a=="arrow"){
			ci=3;
		}
		zhonglei=a;
	}
};

class creature{
	public:
	int xuhao;//该士兵是该阵营的第几号士兵
	string zhengying;//红方还是蓝方
	string zhonglei;
	int shanghai;
	vector <wuqi>  wuqichi={};//定义某个士兵的武器池，不超过10件
	int wuqishu=0;
	int life;
	int weizhi;
	bool zhongjian=false;
	bool v=false;
	double ha=0;
	int haha=0;

	virtual void getwuqi(){

	}

	virtual double& getshiqi(){
		double& a=ha;
		return a;
	}

	virtual int& getloyalty(){
		int & b=haha;
		return b;
	}

	//构造函数
	creature(string a,string b,int c,int d,int e,int f){
		
		xuhao=c;
		zhengying=a;
		zhonglei=b;
		shanghai=d;
		life=e;
		weizhi=f;
		wuqichi.clear();
	}
	creature(){

	}
};

class dragon:public creature{
	public:

	double morale;//士气值

	void getwuqi(){//该龙兵出生时获得的武器
		int bianhao=xuhao%3;
		string wuqi1=wuqixuanze[bianhao];
		wuqi new_wuqi; // 创建一个新的武器对象
        new_wuqi.yingshe(wuqi1, new_wuqi.ci); // 初始化武器
		if(wuqi1=="sword"){
			new_wuqi.gongjili=gongjili[0]*0.2;
			if(new_wuqi.gongjili>0){
				wuqichi.push_back(new_wuqi);
				wuqishu++;
			}
		}else{
        wuqichi.push_back(new_wuqi); // 将武器添加到武器池中
		wuqishu++;
		}
	}

	dragon(string a,string b,int c,int d,int e,int f,double g):creature(a,b,c,d,e,f){
			getwuqi();
			morale=g/life;
	}

	virtual double& getshiqi(){
		return morale;
	}
};


class ninjia:public creature{
	public:
	void getwuqi(){
		int bianhao1=xuhao%3;
		string wuqi1=wuqixuanze[bianhao1];
		wuqi new_wuqi; // 创建一个新的武器对象
        new_wuqi.yingshe(wuqi1, new_wuqi.ci); // 初始化武器
		if(wuqi1=="sword"){
			new_wuqi.gongjili=gongjili[1]*0.2;
			if(new_wuqi.gongjili>0){
				wuqichi.push_back(new_wuqi);
				wuqishu++;
			}
		}else{
        wuqichi.push_back(new_wuqi); // 将武器添加到武器池中
		wuqishu++;
		}
		int bianhao2=(xuhao+1)%3;
		string wuqi2=wuqixuanze[bianhao2];
		wuqi new_wuqi1; // 创建一个新的武器对象
        new_wuqi1.yingshe(wuqi2, new_wuqi1.ci); // 初始化武器
        if(wuqi2=="sword"){
			new_wuqi1.gongjili=gongjili[1]*0.2;
			if(new_wuqi1.gongjili>0){
				wuqichi.push_back(new_wuqi1);
				wuqishu++;
			}
		}else{
		wuqichi.push_back(new_wuqi1); // 将武器添加到武器池中
		wuqishu++;
		}
	}

	ninjia(string a,string b,int c,int d,int e,int f):creature(a,b,c,d,e,f){
		getwuqi();
	}
};

class iceman:public creature{
	public:
	void getwuqi(){
		int bianhao=xuhao%3;
		string wuqi1=wuqixuanze[bianhao];
		wuqi new_wuqi; // 创建一个新的武器对象
        new_wuqi.yingshe(wuqi1, new_wuqi.ci); // 初始化武器
       if(wuqi1=="sword"){
		new_wuqi.gongjili=gongjili[2]*0.2;
		if(new_wuqi.gongjili>0){
			wuqichi.push_back(new_wuqi);
			wuqishu++;
		}
	   }else{
		wuqichi.push_back(new_wuqi); // 将武器添加到武器池中
		wuqishu++;
	   }
	}

	iceman(string a,string b,int c,int d,int e,int f):creature(a,b,c,d,e,f){
		getwuqi();
	}
};

class wolf:public creature{
	public:
	void getwuqi(){

	}
	
	wolf(string a,string b,int c,int d,int e,int f):creature(a,b,c,d,e,f){
		
	}
};

class lion:public creature{
	public:
	void getwuqi(){
		int bianhao=xuhao%3;
		string wuqi1=wuqixuanze[bianhao];
		wuqi new_wuqi; // 创建一个新的武器对象
        new_wuqi.yingshe(wuqi1, new_wuqi.ci); // 初始化武器
       if(wuqi1=="sword"){
		new_wuqi.gongjili=gongjili[3]*0.2;
		if(new_wuqi.gongjili>0){
			wuqichi.push_back(new_wuqi);
			wuqishu++;
		}
	   }else{
		wuqichi.push_back(new_wuqi); // 将武器添加到武器池中
		wuqishu++;
	   }
	}

	int loyalty;

	lion(string a,string b,int c,int d,int e,int f,int zhong):creature(a,b,c,d,e,f){
		loyalty=zhong;

	}
	virtual int& getloyalty(){
		return loyalty;
	}
};


class red{
	public:
	int hunli;//生命源
	int shu;//士兵的数量
	int dijun=0;
	creature*redarm[1000]={0};//红方所有的士兵

	red(int a,int b){
		hunli=a;
		shu=b;
	}
};

class blue{
	public:
	int hunli;
	int shu;
	int dijun=0;

	creature*bluearm[1000]={0};

	blue(int a,int b){
		hunli=a;
		shu=b;
	}

};

//判断时间是否结束
bool jieshulema(int T){
	if(shi*60+fen<=T){
		return false;
	}else{
		return true;
	}
}

//负责生产士兵
void lianbing(red*r,blue*b,int& redxu,int& bluexu,int N){
	//红方
	if(redfei[redxu]<=r->hunli){
		baoshi(shi,fen);
		//添加士兵
		if(redxu==0){
			r->redarm[r->shu]=new iceman("red","iceman",r->shu+1,gongjili[2],shengmingzhi[2],0);
		}
		if(redxu==1){
			r->redarm[r->shu]=new lion("red","lion",r->shu+1,gongjili[3],shengmingzhi[3],0,r->hunli-redfei[1]);
		}
		if(redxu==2){
			r->redarm[r->shu]=new wolf("red","wolf",r->shu+1,gongjili[4],shengmingzhi[4],0);
		}
		if(redxu==3){
			r->redarm[r->shu]=new ninjia("red","ninja",r->shu+1,gongjili[1],shengmingzhi[1],0);
		}
		if(redxu==4){
			r->redarm[r->shu]=new dragon("red","dragon",r->shu+1,gongjili[0],shengmingzhi[0],0,r->hunli-redfei[4]);
		}
		r->hunli=r->hunli-redfei[redxu];
		r->shu++;
		cout << "red "<< redlei[redxu]<< " " << r->shu << " born" << endl;
		if(redxu==1){
			cout<< "Its loyalty is " << r->hunli<< endl;
		}
		if(redxu==4){
			cout << "Its morale is " <<fixed << setprecision(2)<<  r->redarm[r->shu-1]->getshiqi() << endl;
		}
		redxu++;
		if(redxu==5){
			redxu=0;
		}
	}
	//蓝方
	if(bluefei[bluexu]<=b->hunli){
		baoshi(shi,fen);
		//添加士兵
		if(bluexu==3){
			b->bluearm[b->shu]=new iceman("blue","iceman",b->shu+1,gongjili[2],shengmingzhi[2],N+1);
		}
		if(bluexu==0){
			b->bluearm[b->shu]=new lion("blue","lion",b->shu+1,gongjili[3],shengmingzhi[3],N+1,b->hunli-bluefei[0]);
		}
		if(bluexu==4){
			b->bluearm[b->shu]=new wolf("blue","wolf",b->shu+1,gongjili[4],shengmingzhi[4],N+1);
		}
		if(bluexu==2){
			b->bluearm[b->shu]=new ninjia("blue","ninja",b->shu+1,gongjili[1],shengmingzhi[1],N+1);
		}
		if(bluexu==1){
			b->bluearm[b->shu]=new dragon("blue","dragon",b->shu+1,gongjili[0],shengmingzhi[0],N+1,b->hunli-bluefei[1]);
		}
		b->shu++;
		b->hunli=b->hunli-bluefei[bluexu];
		cout << "blue "<< bluelei[bluexu]<< " " << b->shu << " born" << endl;
		if(bluexu==0){
			cout << "Its loyalty is " << b->hunli << endl;
		}
		if(bluexu==1){
			cout << "Its morale is " <<fixed << setprecision(2) << b->bluearm[b->shu-1]->getshiqi() << endl;
		}

		bluexu++;
		if(bluexu==5){
			bluexu=0;
		}

	}
}

//狮子叛逃事件
void lionpantao(red*p,blue*q){
	for(int i=0;i<p->shu;i++){
		if(p->redarm[i]->zhonglei=="lion" and p->redarm[i]->getloyalty()<=0 and p->redarm[i]->life>0){
			p->redarm[i]->life=0;//狮子逃跑视为死亡
			baoshi(shi,fen);
			cout << "red lion "<< p->redarm[i]->xuhao << " ran away" << endl;
		}
	}
	for(int i=0;i<q->shu;i++){
		if(q->bluearm[i]->zhonglei=="lion" and q->bluearm[i]->getloyalty()<=0 and q->bluearm[i]->life>0){
			q->bluearm[i]->life=0;
			baoshi(shi,fen);
			cout << "blue lion "<< q->bluearm[i]->xuhao<< " ran away" << endl;
		}
	}
}

//所有士兵前进
void qianjin(red*p,blue*q,int N){
	for(int i=0;i<p->shu;i++){
		if(p->redarm[i]->life>0){//得活着
			if(p->redarm[i]->weizhi==N+1){
				continue;
			}
			p->redarm[i]->weizhi++;
			if(p->redarm[i]->zhonglei=="iceman"){
				if(p->redarm[i]->weizhi%2==0){
					if(p->redarm[i]->life>9){
						p->redarm[i]->life-=9;
						p->redarm[i]->shanghai+=20;
					}else{
						p->redarm[i]->life=1;
						p->redarm[i]->shanghai+=20;
					}
				}
			}
		}
	}
	for(int i=0;i<q->shu;i++){
		if(q->bluearm[i]->life>0){
			if(q->bluearm[i]->weizhi==0){
				continue;
			}
			q->bluearm[i]->weizhi--;
			if(q->bluearm[i]->zhonglei=="iceman"){
				if((N+1-q->bluearm[i]->weizhi)%2==0){
					if(q->bluearm[i]->life>9){
						q->bluearm[i]->life-=9;
						q->bluearm[i]->shanghai+=20;
					}else{
						q->bluearm[i]->life=1;
						q->bluearm[i]->shanghai+=20;
					}
				}
			}
		}
	}
	for(int i=0;i<=N+1;i++){
		for(int j=0;j<p->shu;j++){
			if(p->redarm[j]->weizhi==i and p->redarm[j]->life>0 and i!=N+1){
				baoshi(shi,fen);
				cout << "red " << p->redarm[j]->zhonglei<< " " << p->redarm[j]->xuhao<< " marched to city " << p->redarm[j]->weizhi<< " with "<< p->redarm[j]->life<< " elements and force "<<p->redarm[j]->shanghai<<endl;
			}
			if(p->redarm[j]->weizhi==i and p->redarm[j]->life>0 and i==N+1 and p->redarm[j]->v==false){
				baoshi(shi,fen);
				//输出样例：001:10 red iceman 1 reached blue headquarter with 20 elements and force 30
				cout << "red " << p->redarm[j]->zhonglei << " " << p->redarm[j]->xuhao << " reached blue headquarter with " << p->redarm[j]->life << " elements and force " << p->redarm[j]->shanghai << endl;
				q->dijun++;
				p->redarm[j]->v=true;
				if(q->dijun==2){
					baoshi(shi,fen);
					//输出样例：003:10 blue headquarter was taken
					cout << "blue headquarter was taken"<< endl;
				}
			}
		}
		for(int j=0;j<q->shu;j++){
			if(q->bluearm[j]->weizhi==i and q->bluearm[j]->life>0 and i!=0){
				baoshi(shi,fen);
				cout << "blue " <<q->bluearm[j]->zhonglei << " " << q->bluearm[j]->xuhao << " marched to city "<<q->bluearm[j]->weizhi<<" with "<< q->bluearm[j]->life << " elements and force "<< q->bluearm[j]->shanghai << endl;
			}
			if(q->bluearm[j]->weizhi==i and q->bluearm[j]->life>0 and i==0 and q->bluearm[j]->v==false){
				baoshi(shi,fen);
				cout << "blue " << q->bluearm[j]->zhonglei << " " << q->bluearm[j]->xuhao << " reached red headquarter with " << q->bluearm[j]->life << " elements and force " << q->bluearm[j] ->shanghai<< endl;
				p->dijun++;
				q->bluearm[j]->v=true;
				if(p->dijun==2){
					baoshi(shi,fen);
					cout << "red headquarter was taken" << endl;
				}
			}
		}
	}
}

//司令部报告生命源数量
void yuanreport(red*r,blue*b){
	baoshi(shi,fen);
	cout << r->hunli <<  " elements in red headquarter" << endl;
	baoshi(shi,fen);
	cout  << b->hunli << " elements in blue headquarter" << endl;

}

//每个士兵报告武器情况
void wuqireport(red*p,blue*q,int N){
	
	for(int i=0;i<=N+1;i++){
	
		for(int j=0;j<p->shu;j++){
			if(p->redarm[j]->weizhi==i and p->redarm[j]->life>0){
				baoshi(shi,fen);
			
				int sword=0;
				int bomb=0;
				int arrow=0;
				int sx=0;
				int bx=0;
				int ax=0;
				
				for(int k=0;k<p->redarm[j]->wuqishu;k++){
					if(p->redarm[j]->wuqichi[k].zhonglei=="sword"){
						sword++;
						sx=k;
					}
					if(p->redarm[j]->wuqichi[k].zhonglei=="bomb"){
						bomb++;
						bx=k;
					}
					if(p->redarm[j]->wuqichi[k].zhonglei=="arrow"){
						arrow++;
						ax=k;
					}
				}
				if(sword==0 and arrow==0 and bomb==0){
					cout << "red " << p->redarm[j]->zhonglei << " " << p->redarm[j]->xuhao << " has no weapon"<< endl;
				}else{
						//000:55 blue wolf 2 has 2 sword 3 bomb 0 arrow and 7 elements
						cout << "red " << p->redarm[j]->zhonglei<< " " << p->redarm[j]->xuhao << " has " ;
						if(arrow>0){
							cout << "arrow("<<p->redarm[j]->wuqichi[ax].ci<<")";
							if(bomb>0 or sword>0){
								cout << ",";
							}
						}
						if(bomb>0){
							cout << "bomb";
							if(sword>0){
								cout << ",";
							}
						}		
						if(sword>0){
							cout << "sword("<< p->redarm[j]->wuqichi[sx].gongjili<<")";
						}
						cout << endl;
					}
			}
		}
	}		
	for(int i=0;i<=N+1;i++){
		for(int j=0;j<q->shu;j++){
			if(q->bluearm[j]->weizhi==i and q->bluearm[j]->life>0){
				baoshi(shi,fen);
				int sword=0;
				int bomb=0;
				int arrow=0;
				int sx=0;
				int bx=0;
				int ax=0;

				for(int k=0;k<q->bluearm[j]->wuqishu;k++){
					if(q->bluearm[j]->wuqichi[k].zhonglei=="sword"){
						sword++;
						sx=k;
					}
					if(q->bluearm[j]->wuqichi[k].zhonglei=="bomb"){
						bomb++;
						bx=k;
					}
					if(q->bluearm[j]->wuqichi[k].zhonglei=="arrow"){
						arrow++;
						ax=k;
					}
				}
				//000:55 blue wolf 2 has 2 sword 3 bomb 0 arrow and 7 elements
				cout << "blue "<< q->bluearm[j]->zhonglei<< " " << q->bluearm[j]->xuhao << " has " ;
				if(sword==0 and arrow==0 and bomb==0){
					cout << "no weapon";
				}
				if(arrow>0){
					cout << "arrow(" << q->bluearm[j]->wuqichi[ax].ci <<")";
					if(bomb>0 or sword>0){
						cout << ",";
					}
				}
				if(bomb>0){
					cout << "bomb";
					if(sword>0){
						cout << ",";
					}
				}
				if(sword>0){
					cout << "sword(" << q->bluearm[j]->wuqichi[sx].gongjili<<")";
				}
				cout << endl;
						
			}
		}
	}
}

//是否有士兵到达敌方指挥部，那么战争结束
bool zhanzhengjieshu(red*p,blue*q,int N){
	if(p->dijun==2 or q->dijun==2){
		return true;
	}
	return false;
}

void chanchu(city*p[],int N){
	for(int i=1;i<=N;i++){
		p[i]->life+=10;
	}
}

void nazou(city*p[],red*a,blue*b,int N){
	for(int i=1;i<=N;i++){
		int h;
		int l;
		bool hong=false;
		bool lan=false;
		for(int j=0;j<a->shu;j++){
			if(a->redarm[j]->weizhi==p[i]->xuhao and a->redarm[j]->life>0){
				hong=true;
				h=j;//记录哪个武士在这座城市
				break;
			}
		}
		for(int j=0;j<b->shu;j++){
			if(b->bluearm[j]->weizhi==p[i]->xuhao and b->bluearm[j]->life>0){
				lan=true;
				l=j;//记录哪个武士在这座城市
				break;
			}
		}
		if(hong and !lan){
			a->hunli+=p[i]->life;
			baoshi(shi,fen);
			cout << "red " << a->redarm[h]->zhonglei << " " << a->redarm[h]->xuhao << " earned " << p[i]->life << " elements for his headquarter" << endl;
			p[i]->life=0;
		}
		if(lan and !hong){
			b->hunli+=p[i]->life;
			baoshi(shi,fen);
			cout << "blue " << b->bluearm[l]->zhonglei << " " << b->bluearm[l]->xuhao << " earned " << p[i]->life << " elements for his headquarter" << endl;
			p[i]->life=0;
		}
	}
}


void wanjianqifa(red*p,blue*q,int R,int N,city* a[]){
	bool lan1=false;
	int bwei1=0;
	bool lan2=false;
	int bwei2=0;
	int life2=0;
	int hwei2=0;
	int life1=0;
	int hwei1=0;
	for(int h=1;h<=N;h++){//逐个城市来看
		lan1=lan2;
		bwei1=bwei2;
		hwei1=hwei2;
		life1=life2;
		lan2=false;
		for(int i=0;i<p->shu;i++){
			if(h==N){
				break;
			}
			if(p->redarm[i]->life>0 and p->redarm[i]->weizhi==h){
				bool youdiren=false;
				int l;//哪一个蓝军
				for(int j=0;j<q->shu;j++){
					if(q->bluearm[j]->weizhi==h+1 and q->bluearm[j]->life>0){
						youdiren=true;
						l=j;
						break;
					}
				}

				bool hj=false;
				bool lj=false;
				if(youdiren){
					for(int j=0;j<p->redarm[i]->wuqishu;j++){
						if(p->redarm[i]->wuqichi[j].zhonglei=="arrow"){
							hj=true;
							p->redarm[i]->wuqichi[j].ci--;
							if(p->redarm[i]->wuqichi[j].ci==0){
								p->redarm[i]->wuqichi.erase(p->redarm[i]->wuqichi.begin()+j);
								p->redarm[i]->wuqishu--;
							}
							break;//说明有arrow
						}
					}
					for(int j=0;j<q->bluearm[l]->wuqishu;j++){
						if(q->bluearm[l]->wuqichi[j].zhonglei=="arrow"){
							q->bluearm[l]->wuqichi[j].ci--;
							lj=true;
							if(q->bluearm[l]->wuqichi[j].ci==0){
								q->bluearm[l]->wuqichi.erase(q->bluearm[l]->wuqichi.begin()+j);
								q->bluearm[l]->wuqishu--;
							}
							break;
						}
					}
				}else{
					continue;
				}
				if(hj){
					q->bluearm[l]->life-=R;
					if(q->bluearm[l]->life>0){
						baoshi(shi,fen);
						cout << "red " << p->redarm[i]->zhonglei << " " << p->redarm[i]->xuhao << " shot" << endl;
					}

					if(q->bluearm[l]->life<=0){
						q->bluearm[l]->zhongjian=true;
						q->bluearm[l]->life+=R;
						baoshi(shi,fen);
						cout<< "red " << p->redarm[i]->zhonglei << " " << p->redarm[i]->xuhao<< " shot and killed blue " << q->bluearm[l]->zhonglei << " " << q->bluearm[l]->xuhao << endl;

					}
					
				}
				if(lj){
					p->redarm[i]->life-=R;
					lan2=true;
					bwei2=l;//蓝军的位置
					life2=p->redarm[i]->life;//红军的生命值（扣血之后）
					hwei2=i;//红军的位置
					if(p->redarm[i]->life<=0){
						p->redarm[i]->zhongjian=true;
						p->redarm[i]->life+=R;
					}
				}
			}
		}
		if(lan1){//蓝军在
			if(life1>0){
				baoshi(shi,fen);
				cout<< "blue " << q->bluearm[bwei1]->zhonglei << " " << q->bluearm[bwei1]->xuhao << " shot" << endl;
				lan1=false;
			}else{
				baoshi(shi,fen);
				cout << "blue " << q->bluearm[bwei1]->zhonglei << " " << q->bluearm[bwei1]->xuhao << " shot and killed red " << p->redarm[hwei1]->zhonglei <<" " << p->redarm[hwei1]->xuhao << endl; 
				lan1=false;
			}
		}
	}	
}


void bomb(int N,red*p,blue*q,city*n[]){
	for(int i=1;i<=N;i++){
		for(int j=0;j<p->shu;j++){
			if(p->redarm[j]->life>0 and p->redarm[j]->weizhi==i){
				for(int k=0;k<q->shu;k++){
					if(q->bluearm[k]->life>0 and q->bluearm[k]->weizhi==i){
						//此时有两个人在同一座城市
						if(p->redarm[j]->zhongjian or q->bluearm[k]->zhongjian){
							break;
						}
				
							//模拟战斗
							int redg=p->redarm[j]->shanghai;
							for(int m=0;m<p->redarm[j]->wuqishu;m++){
								if(p->redarm[j]->wuqichi[m].zhonglei=="sword"){
									redg=p->redarm[j]->shanghai+p->redarm[j]->wuqichi[m].gongjili;
									break;
								}
							}

							int blueg=q->bluearm[k]->shanghai;
							for(int n=0;n<q->bluearm[k]->wuqishu;n++){
								if(q->bluearm[k]->wuqichi[n].zhonglei=="sword"){
									blueg=q->bluearm[k]->shanghai+q->bluearm[k]->wuqichi[n].gongjili;
								}
							}//先模拟二者可能的伤害值

							if(n[i]->flag=="red" or (i%2==1 and n[i]->flag=="")){
								if(redg<q->bluearm[k]->life){
									//蓝方没死
									blueg=blueg-q->bluearm[k]->shanghai+q->bluearm[k]->shanghai/2;
									if(q->bluearm[k]->zhonglei=="ninja"){
										blueg=0;
									}
									if(blueg>=p->redarm[j]->life){
										//红方使用炸弹
										for(int m=0;m<p->redarm[j]->wuqishu;m++){
											if(p->redarm[j]->wuqichi[m].zhonglei=="bomb"){
												q->bluearm[k]->life=0;
												p->redarm[j]->life=0;
												p->redarm[j]->wuqichi.erase(p->redarm[j]->wuqichi.begin()+m);
												p->redarm[j]->wuqishu--;
												baoshi(shi,fen);
												cout<< "red " << p->redarm[j]->zhonglei << " " << p->redarm[j]->xuhao << " used a bomb and killed blue " << q->bluearm[k]->zhonglei << " " << q->bluearm[k]->xuhao << endl;
												break;
											}
										}
									}
								}else{
									//蓝方死了
									for(int m=0;m<q->bluearm[k]->wuqishu;m++){
										if(q->bluearm[k]->wuqichi[m].zhonglei=="bomb"){
											p->redarm[j]->life=0;
											q->bluearm[k]->life=0;
											q->bluearm[k]->wuqichi.erase(q->bluearm[k]->wuqichi.begin()+m);
											q->bluearm[k]->wuqishu--;
											baoshi(shi,fen);
											cout << "blue " << q->bluearm[k]->zhonglei << " " << q->bluearm[k]->xuhao << " used a bomb and killed red " << p->redarm[j]->zhonglei << " " << p->redarm[j]->xuhao << endl;
											break;
										}
									}
								}
							}else{
								if(blueg<p->redarm[j]->life){
									//红方没死
									redg=redg-p->redarm[j]->shanghai+p->redarm[j]->shanghai/2;
									if(p->redarm[j]->zhonglei=="ninja"){
										redg=0;
									}
									if(redg>=q->bluearm[k]->life){
										for(int m=0;m<q->bluearm[k]->wuqishu;m++){
											if(q->bluearm[k]->wuqichi[m].zhonglei=="bomb"){
												p->redarm[j]->life=0;
												q->bluearm[k]->life=0;
												q->bluearm[k]->wuqichi.erase(q->bluearm[k]->wuqichi.begin()+m);
												q->bluearm[k]->wuqishu--;
												baoshi(shi,fen);
												cout << "blue " << q->bluearm[k]->zhonglei << " " << q->bluearm[k]->xuhao << " used a bomb and killed red " << p->redarm[j]->zhonglei << " " << p->redarm[j]->xuhao << endl;
												break;
											}
										}
									}
								}else{
									//红方直接死了
									for(int m=0;m<p->redarm[j]->wuqishu;m++){
										if(p->redarm[j]->wuqichi[m].zhonglei=="bomb"){
											q->bluearm[k]->life=0;
											p->redarm[j]->life=0;
											p->redarm[j]->wuqichi.erase(p->redarm[j]->wuqichi.begin()+m);
											p->redarm[j]->wuqishu--;
											baoshi(shi,fen);
											cout<< "red " << p->redarm[j]->zhonglei << " " << p->redarm[j]->xuhao << " used a bomb and killed blue " << q->bluearm[k]->zhonglei << " " << q->bluearm[k]->xuhao << endl;
											break;
										}
									}
								}
							}
					}
				}
			}
		}
	}
}

void jingong(int N,red*p,blue*q,city* a[]){
	for(int i=1;i<=N;i++){
		for(int j=0;j<p->shu;j++){
			if(p->redarm[j]->weizhi==i and p->redarm[j]->life>0){
				for(int k=0;k<q->shu;k++){
					if(q->bluearm[k]->life>0 and q->bluearm[k]->weizhi==i){
						if(p->redarm[j]->zhongjian==false and q->bluearm[k]->zhongjian==false){
							if(a[i]->flag=="red" or (i%2==1 and a[i]->flag=="")){
								//红方率先发起进攻

								int redg=p->redarm[j]->shanghai;
								for(int m=0;m<p->redarm[j]->wuqishu;m++){
									if(p->redarm[j]->wuqichi[m].zhonglei=="sword"){
										redg=redg+p->redarm[j]->wuqichi[m].gongjili;
										p->redarm[j]->wuqichi[m].gongjili*=0.8;
										if(p->redarm[j]->wuqichi[m].gongjili==0){
											p->redarm[j]->wuqichi.erase(p->redarm[j]->wuqichi.begin()+m);
											p->redarm[j]->wuqishu--;
										}
										break;
									}
								}
								q->bluearm[k]->life-=redg;
								baoshi(shi,fen);
								cout << "red " << p->redarm[j]->zhonglei << " " << p->redarm[j]->xuhao << " attacked blue " << q->bluearm[k]->zhonglei << " " << q->bluearm[k]->xuhao<< " in city " << i << " with " << p->redarm[j]->life << " elements and force "<< p->redarm[j]->shanghai <<endl; 
								if(q->bluearm[k]->life<=0){
									a[i]->b=true;
									a[i]->blue=k;
									a[i]->redsha=j;
									baoshi(shi,fen);
									cout << "blue " << q->bluearm[k]->zhonglei << " " << q->bluearm[k]->xuhao << " was killed in city " << i << endl;


									if(a[i]->zhankuang<=0){
										a[i]->zhankuang=1;
									}
									else if(a[i]->zhankuang==1){
										a[i]->zhankuang=2;
									}
									if(p->redarm[j]->zhonglei=="dragon"){
										p->redarm[j]->getshiqi()+=0.2;
										if(p->redarm[j]->getshiqi()>0.8){
											baoshi(shi,fen);
											cout << "red dragon " << p->redarm[j]->xuhao << " yelled in city " << i << endl;
										}
									}
									if(p->redarm[j]->zhonglei=="wolf"){
										for(int u=0;u<q->bluearm[k]->wuqishu;u++){
											bool you=false;
											for(int v=0;v<p->redarm[j]->wuqishu;v++){
												if(p->redarm[j]->wuqichi[v].zhonglei==q->bluearm[k]->wuqichi[u].zhonglei){
													you=true;
													break;
												}
											}
											if(you==false){//发现没有这个武器
												p->redarm[j]->wuqichi.push_back(q->bluearm[k]->wuqichi[u]);
												p->redarm[j]->wuqishu++;
												q->bluearm[k]->wuqichi.erase(q->bluearm[k]->wuqichi.begin()+u);
												q->bluearm[k]->wuqishu--;
												u--;
											}
										}
									}
									baoshi(shi,fen);
									cout << "red " << p->redarm[j]->zhonglei << " " << p->redarm[j]->xuhao << " earned " << a[i]->life << " elements for his headquarter" << endl;
									p->hunli+=a[i]->life;
									a[i]->life=0;
									if(q->bluearm[k]->zhonglei=="lion"){
										p->redarm[j]->life+=q->bluearm[k]->life+redg;
									}
								}else{
									if(p->redarm[j]->zhonglei=="dragon"){
										p->redarm[j]->getshiqi()-=0.2;
									}
									if(p->redarm[j]->zhonglei=="lion"){
										p->redarm[j]->getloyalty()-=K;
									}
									int blueg=q->bluearm[k]->shanghai*0.5;
								if(q->bluearm[k]->zhonglei!="ninja"){
									for(int m=0;m<q->bluearm[k]->wuqishu;m++){
										if(q->bluearm[k]->wuqichi[m].zhonglei=="sword"){
											blueg=blueg+q->bluearm[k]->wuqichi[m].gongjili;
											q->bluearm[k]->wuqichi[m].gongjili*=0.8;
											if(q->bluearm[k]->wuqichi[m].gongjili==0){
												q->bluearm[k]->wuqichi.erase(q->bluearm[k]->wuqichi.begin()+m);
												q->bluearm[k]->wuqishu--;
											}
											break;
										}
									}
								}
									if(q->bluearm[k]->zhonglei=="ninja"){
										blueg=0;
									}
									if(q->bluearm[k]->zhonglei!="ninja"){
										p->redarm[j]->life-=blueg;
										baoshi(shi,fen);
										cout << "blue " << q->bluearm[k]->zhonglei << " " << q->bluearm[k]->xuhao << " fought back against red " << p->redarm[j]->zhonglei << " " << p->redarm[j]->xuhao << " in city " << i << endl;
									}
									if(p->redarm[j]->life<=0){
										a[i]->r=true;
										a[i]->red=j;//记录死掉的战士
										a[i]->bluesha=k;
										baoshi(shi,fen);
										cout << "red " << p->redarm[j]->zhonglei << " " << p->redarm[j]->xuhao << " was killed in city " << i << endl;
										if(p->redarm[j]->zhonglei=="lion"){
											q->bluearm[k]->life+=p->redarm[j]->life+blueg;
										}
									
											if(a[i]->zhankuang>=0){
												a[i]->zhankuang=-1;
											}else if(a[i]->zhankuang==-1){
												a[i]->zhankuang=-2;
											}
											if(q->bluearm[k]->zhonglei=="dragon"){
												q->bluearm[k]->getshiqi()+=0.2;
											}
											if(q->bluearm[k]->zhonglei=="wolf"){
												for(int u=0;u<p->redarm[j]->wuqishu;u++){
													bool you=false;
													for(int v=0;v<q->bluearm[k]->wuqishu;v++){
														if(q->bluearm[k]->wuqichi[v].zhonglei==p->redarm[j]->wuqichi[u].zhonglei){
															you=true;
															break;
														}
													}
													if(you==false){
														q->bluearm[k]->wuqichi.push_back(p->redarm[j]->wuqichi[u]);
														q->bluearm[k]->wuqishu++;
														p->redarm[j]->wuqichi.erase(p->redarm[j]->wuqichi.begin()+u);
														p->redarm[j]->wuqishu--;
														u--;
													}
												}
											}
											baoshi(shi,fen);
											cout << "blue " << q->bluearm[k]->zhonglei << " " << q->bluearm[k]->xuhao << " earned " << a[i]->life << " elements for his headquarter"<< endl;
											q->hunli+=a[i]->life;
											a[i]->life=0;

									}else{
										if(q->bluearm[k]->zhonglei=="dragon"){
											q->bluearm[k]->getshiqi()-=0.2;
										}
										if(p->redarm[j]->getshiqi()>0.8){
											baoshi(shi,fen);
											cout << "red dragon " << p->redarm[j]->xuhao << " yelled in city " << i << endl;
										}
										if(q->bluearm[k]->zhonglei=="lion"){
											q->bluearm[k]->getloyalty()-=K;
										}
										a[i]->zhankuang=0;
									}

								}

							}else{
								int blueg=q->bluearm[k]->shanghai;
								for(int m=0;m<q->bluearm[k]->wuqishu;m++){
									if(q->bluearm[k]->wuqichi[m].zhonglei=="sword"){
										blueg=blueg+q->bluearm[k]->wuqichi[m].gongjili;
										q->bluearm[k]->wuqichi[m].gongjili*=0.8;
										if(q->bluearm[k]->wuqichi[m].gongjili==0){
											q->bluearm[k]->wuqichi.erase(q->bluearm[k]->wuqichi.begin()+m);
											q->bluearm[k]->wuqishu--;
										}
										break;
									}
								}
								p->redarm[j]->life-=blueg;
								baoshi(shi,fen);
								cout << "blue " << q->bluearm[k]->zhonglei << " " << q->bluearm[k]->xuhao << " attacked red " << p->redarm[j]->zhonglei << " " << p->redarm[j]->xuhao << " in city " << i << " with " << q->bluearm[k]->life << " elements and force " << q->bluearm[k]->shanghai <<endl;
								if(p->redarm[j]->life<=0){
									a[i]->r=true;
									a[i]->red=j;
									a[i]->bluesha=k;
									baoshi(shi,fen);
									cout << "red " << p->redarm[j]->zhonglei << " " << p->redarm[j]->xuhao << " was killed in city "<< i << endl;

									if(a[i]->zhankuang>=0){
										a[i]->zhankuang=-1;
									}else if(a[i]->zhankuang==-1){
										a[i]->zhankuang=-2;
									}
									if(q->bluearm[k]->zhonglei=="dragon"){
										q->bluearm[k]->getshiqi()+=0.2;	
										if(q->bluearm[k]->getshiqi()>0.8){
											baoshi(shi,fen);
											cout << "blue dragon " << q->bluearm[k]->xuhao << " yelled in city " << i << endl;
										}							
									}
									if(q->bluearm[k]->zhonglei=="wolf"){
										for(int u=0;u<p->redarm[j]->wuqishu;u++){
											bool you=false;
											for(int v=0;v<q->bluearm[k]->wuqishu;v++){
												if(q->bluearm[k]->wuqichi[v].zhonglei==p->redarm[j]->wuqichi[u].zhonglei){
													you=true;
													break;
												}
											}
											if(you==false){
												q->bluearm[k]->wuqichi.push_back(p->redarm[j]->wuqichi[u]);
												q->bluearm[k]->wuqishu++;
												p->redarm[j]->wuqichi.erase(p->redarm[j]->wuqichi.begin()+u);
												p->redarm[j]->wuqishu--;
												u--;
											}
										}
									}
									baoshi(shi,fen);
									cout << "blue " << q->bluearm[k]->zhonglei << " " << q->bluearm[k]->xuhao << " earned " << a[i]->life << " elements for his headquarter" << endl;
									q->hunli+=a[i]->life;
									a[i]->life=0;
									if(p->redarm[j]->zhonglei=="lion"){
										q->bluearm[k]->life+=p->redarm[j]->life+blueg;
									}
								}else{
									if(q->bluearm[k]->zhonglei=="dragon"){
										q->bluearm[k]->getshiqi()-=0.2;
									}
									if(q->bluearm[k]->zhonglei=="lion"){
										q->bluearm[k]->getloyalty()-=K;
									}
									int redg=p->redarm[j]->shanghai*0.5;
								if(p->redarm[j]->zhonglei!="ninja"){
									for(int m=0;m<p->redarm[j]->wuqishu;m++){
										if(p->redarm[j]->wuqichi[m].zhonglei=="sword"){
											redg=redg+p->redarm[j]->wuqichi[m].gongjili;
											p->redarm[j]->wuqichi[m].gongjili*=0.8;
											if(p->redarm[j]->wuqichi[m].gongjili==0){
												p->redarm[j]->wuqichi.erase(p->redarm[j]->wuqichi.begin()+m);
												p->redarm[j]->wuqishu--;
											}
											break;
										}
									}
								}
									if(p->redarm[j]->zhonglei=="ninja"){
										redg=0;
									}
								if(p->redarm[j]->zhonglei!="ninja"){
									q->bluearm[k]->life-=redg;
									baoshi(shi,fen);
									cout << "red " << p->redarm[j]->zhonglei << " " << p->redarm[j]->xuhao << " fought back against blue " << q->bluearm[k]->zhonglei << " " << q->bluearm[k]->xuhao<< " in city " << i <<endl; 
								}		
									if(q->bluearm[k]->life<=0){
										a[i]->b=true;
										a[i]->blue=k;
										a[i]->redsha=j;
										baoshi(shi,fen);
										cout << "blue " << q->bluearm[k]->zhonglei << " " << q->bluearm[k]->xuhao << " was killed in city " << i << endl;
										if(a[i]->zhankuang<=0){
											a[i]->zhankuang=1;
										}else if(a[i]->zhankuang==1){
											a[i]->zhankuang=2;
										}
										if(p->redarm[j]->zhonglei=="dragon"){
											p->redarm[j]->getshiqi()+=0.2;
										}
										if(p->redarm[j]->zhonglei=="wolf"){
											for(int u=0;u<q->bluearm[k]->wuqishu;u++){
												bool you=false;
												for(int v=0;v<p->redarm[j]->wuqishu;v++){
													if(p->redarm[j]->wuqichi[v].zhonglei==q->bluearm[k]->wuqichi[u].zhonglei){
														you=true;
														break;
													}
												}
												if(you==false){//发现没有这个武器
													p->redarm[j]->wuqichi.push_back(q->bluearm[k]->wuqichi[u]);
													p->redarm[j]->wuqishu++;
													q->bluearm[k]->wuqichi.erase(q->bluearm[k]->wuqichi.begin()+u);
													q->bluearm[k]->wuqishu--;
													u--;
												}
											}
										}
										baoshi(shi,fen);
										cout << "red " << p->redarm[j]->zhonglei << " " << p->redarm[j]->xuhao << " earned " << a[i]->life << " elements for his headquarter" << endl;
										p->hunli+=a[i]->life;
										a[i]->life=0;
										if(q->bluearm[k]->zhonglei=="lion"){
											p->redarm[j]->life+=q->bluearm[k]->life+redg;
										}
									}else{
										if(p->redarm[j]->zhonglei=="dragon"){
											p->redarm[j]->getshiqi()-=0.2;
										}
										if(q->bluearm[k]->getshiqi()>0.8){
											baoshi(shi,fen);
											cout << "blue dragon " << q->bluearm[k]->xuhao << " yelled in city " << i << endl;
										}	
										if(p->redarm[j]->zhonglei=="lion"){
											p->redarm[j]->getloyalty()-=K;
										}
										a[i]->zhankuang=0;
									}
								}
							}
						}else{
							if(p->redarm[j]->zhongjian and q->bluearm[k]->zhongjian){
								p->redarm[j]->life=0;
								q->bluearm[k]->life=0;
							}
							if(p->redarm[j]->zhongjian and !q->bluearm[k]->zhongjian){
								p->redarm[j]->life=0;
								a[i]->r=true;
									if(a[i]->zhankuang>=0){
										a[i]->zhankuang=-1;
									}else if(a[i]->zhankuang==-1){
										a[i]->zhankuang=-2;
									}
									if(q->bluearm[k]->zhonglei=="dragon"){
										q->bluearm[k]->getshiqi()+=0.2;	
										if(q->bluearm[k]->getshiqi()>0.8 and (a[i]->flag=="blue" or (a[i]->flag=="" and i%2==0) )){
											baoshi(shi,fen);
											cout << "blue dragon " << q->bluearm[k]->xuhao << " yelled in city " << i << endl;
										}							
									}
									if(q->bluearm[k]->zhonglei=="wolf"){
										for(int u=0;u<p->redarm[j]->wuqishu;u++){
											bool you=false;
											for(int v=0;v<q->bluearm[k]->wuqishu;v++){
												if(q->bluearm[k]->wuqichi[v].zhonglei==p->redarm[j]->wuqichi[u].zhonglei){
													you=true;
													break;
												}
											}
											if(you==false){
												q->bluearm[k]->wuqichi.push_back(p->redarm[j]->wuqichi[u]);
												q->bluearm[k]->wuqishu++;
												p->redarm[j]->wuqichi.erase(p->redarm[j]->wuqichi.begin()+u);
												p->redarm[j]->wuqishu--;
												u--;
											}
										}
									}
									baoshi(shi,fen);
									cout << "blue " << q->bluearm[k]->zhonglei << " " << q->bluearm[k]->xuhao << " earned " << a[i]->life << " elements for his headquarter" << endl;
									q->hunli+=a[i]->life;
									a[i]->life=0;
							}
							if(!p->redarm[j]->zhongjian and q->bluearm[k]->zhongjian){
								q->bluearm[k]->life=0;
								a[i]->b=true;
										if(a[i]->zhankuang<=0){
											a[i]->zhankuang=1;
										}else if(a[i]->zhankuang==1){
											a[i]->zhankuang=2;
										}
										if(p->redarm[j]->zhonglei=="dragon"){
											p->redarm[j]->getshiqi()+=0.2;
											if(p->redarm[j]->getshiqi()>0.8 and (a[i]->flag=="red" or (a[i]->flag=="" and i%2==1))){
												baoshi(shi,fen);
												cout << "red dragon " << p->redarm[j]->xuhao << " yelled in city " << i << endl;
											}
										}
										if(p->redarm[j]->zhonglei=="wolf"){
											for(int u=0;u<q->bluearm[k]->wuqishu;u++){
												bool you=false;
												for(int v=0;v<p->redarm[j]->wuqishu;v++){
													if(p->redarm[j]->wuqichi[v].zhonglei==q->bluearm[k]->wuqichi[u].zhonglei){
														you=true;
														break;
													}
												}
												if(you==false){//发现没有这个武器
													p->redarm[j]->wuqichi.push_back(q->bluearm[k]->wuqichi[u]);
													p->redarm[j]->wuqishu++;
													q->bluearm[k]->wuqichi.erase(q->bluearm[k]->wuqichi.begin()+u);
													q->bluearm[k]->wuqishu--;
													u--;
												}
											}
										}
										baoshi(shi,fen);
										cout << "red " << p->redarm[j]->zhonglei << " " << p->redarm[j]->xuhao << " earned " << a[i]->life << " elements for his headquarter" << endl;
										p->hunli+=a[i]->life;
										a[i]->life=0;								
							}
						}
							if(a[i]->zhankuang==2 and a[i]->flag!="red"){
								a[i]->flag="red";
								a[i]->zhankuang=0;
								baoshi(shi,fen);
								cout << "red flag raised in city " << i << endl;
							}
							if(a[i]->zhankuang==-2 and a[i]->flag!="blue"){
								a[i]->flag="blue";
								a[i]->zhankuang=0;
								baoshi(shi,fen);
								cout << "blue flag raised in city " << i << endl;
							}
					}
				}
			}

		}
		for(int j=0;j<p->shu;j++){
			if(p->redarm[j]->life>0 and p->redarm[j]->weizhi==i and p->redarm[j]->zhongjian){
				p->redarm[j]->life=0;
			}
		}
		for(int j=0;j<q->shu;j++){
			if(q->bluearm[j]->life>0 and q->bluearm[j]->weizhi==i and q->bluearm[j]->zhongjian){
				q->bluearm[j]->life=0;
			}
		}
	}
}


void jiangli(int n,red*p,blue*q,city*a []){
	for(int i=1;i<=n;i++){//对于蓝方来说
		for(int j=0;j<q->shu;j++){
			if(q->bluearm[j]->weizhi==i and q->bluearm[j]->life>0 and a[i]->r){
				//红方被击败了，应该给蓝军发送奖励
				if(q->hunli>=8){
					q->bluearm[j]->life+=8;
					q->hunli-=8;
					a[i]->r=false;
				}
			}
		}
	}
	for(int i=n;i>=1;i--){
		for(int j=0;j<p->shu;j++){
			if(p->redarm[j]->life>0 and p->redarm[j]->weizhi==i and a[i]->b){
				//蓝军被杀，给红军发奖励
				if(p->hunli>=8){
					p->redarm[j]->life+=8;
					p->hunli-=8;
					a[i]->b=false;
				}
			}
		}
	}
}
			

int main(){
	
	int zu;
	cin >> zu;
	int fuzu=zu;

	while(zu--){

		shi=0;
		fen=0;
			//红蓝方造士兵的序号
		int redxu=0;
		int bluexu=0;

		int M,N,T;
		int R;//R 是arrow的攻击力
		cin >> M >> N >> R >> K >> T;//N是城市数量，K是lion每前进一步忠诚值的减少量
		
		red red(M,0);
		blue blue(M,0);

		for(int i=0;i<5;i++){
			cin >> shengmingzhi[i];
		}

		feishe();//将费用转化成red和blue的顺序

		for(int i=0;i<5;i++){
			cin >> gongjili[i];
		}

		city* p[1000];
		for(int i=1;i<=N;i++){
			p[i]=new city(i);
		}//对城市进行初始化

		cout << "Case " << fuzu-zu << ":"<< endl;

		while(!jieshulema(T)){
			if(!zhanzhengjieshu(&red,&blue,N)){//战争进行时发生的一系列事件
	
				lianbing(&red,&blue,redxu,bluexu,N);//完成

				fen=5;

				if(jieshulema(T)){
					break;
				}
	
				lionpantao(&red,&blue);//完成

				fen=10;
				if(jieshulema(T)){
					break;
				}
	
				qianjin(&red,&blue,N);//完成

				if(!zhanzhengjieshu(&red,&blue,N)){

					fen=20;
					if(jieshulema(T)){
						break;
					}
					chanchu(p,N);//每一个城市生产十个生命源
	
					fen=30;
					if(jieshulema(T)){
						break;
					}
					nazou(p,&red,&blue,N);
	
					fen=35;
					if(jieshulema(T)){
						break;
					}
					wanjianqifa(&red,&blue,R,N,p);

					fen=38;
					if(jieshulema(T)){
						break;
					}
					bomb(N,&red,&blue,p);

					fen=40;
					if(jieshulema(T)){
						break;
					}
					
					jingong(N,&red,&blue,p);

					jiangli(N,&red,&blue,p);

					fen=50;
					if(jieshulema(T)){
						break;
					}
			
					yuanreport(&red,&blue);//ok

					fen=55;
					if(jieshulema(T)){
						break;
					}
	
					wuqireport(&red,&blue,N);

					fen=0;

				}else{
				
				}
			}
			shi++;
		}
	}

	return 0;
}