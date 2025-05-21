
#include<iostream>
#include<string>
#include <ciso646> // 包含替代标记的定义
#include<cstring>
#include<vector>

using namespace std;

//记录时间
int shi=0;
int fen=0;
int zhongcheng=0;



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
string redlei[5]={"iceman","lion","wolf","ninja","dragon"};
string bluelei[5]={"lion","dragon","ninja","iceman","wolf"};

int redfei[5]={0};
int bluefei[5]={0};

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
	int  bili;
	int ci;//还能用多少次
	void yingshe(string a,int& ci,int& bili){
		if(a=="sword"){
			ci=1000;
			bili=2;
		}
		if(a=="bomb"){
			ci=1;
			bili=4;
		}
		if(a=="arrow"){
			ci=2;
			bili=3;
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

	virtual void getwuqi(){

	}

	virtual void huanhu(){

	}

	virtual void buzhong(){//狮子不忠

	}

	virtual int zhongxin(){
		return 0;
	}

	virtual void kouxue(){

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
	void huanhu(){
		baoshi(shi,fen);
		cout << zhengying << " " << zhonglei << " " << xuhao << " yelled in city " << weizhi;
		cout << endl;
	}

	void getwuqi(){//该龙兵出生时获得的武器
		int bianhao=xuhao%3;
		string wuqi1=wuqixuanze[bianhao];
		wuqi new_wuqi; // 创建一个新的武器对象
        new_wuqi.yingshe(wuqi1, new_wuqi.ci,new_wuqi.bili); // 初始化武器
        wuqichi.push_back(new_wuqi); // 将武器添加到武器池中
		wuqishu++;
	}

	dragon(string a,string b,int c,int d,int e,int f):creature(a,b,c,d,e,f){
			getwuqi();
	}
};


class ninjia:public creature{
	public:
	void getwuqi(){
		int bianhao1=xuhao%3;
		string wuqi1=wuqixuanze[bianhao1];
		wuqi new_wuqi; // 创建一个新的武器对象
        new_wuqi.yingshe(wuqi1, new_wuqi.ci,new_wuqi.bili); // 初始化武器
        wuqichi.push_back(new_wuqi); // 将武器添加到武器池中
		wuqishu++;

		int bianhao2=(xuhao+1)%3;
		string wuqi2=wuqixuanze[bianhao2];
		wuqi new_wuqi1; // 创建一个新的武器对象
        new_wuqi1.yingshe(wuqi2, new_wuqi1.ci,new_wuqi1.bili); // 初始化武器
        wuqichi.push_back(new_wuqi1); // 将武器添加到武器池中
		wuqishu++;
	}

	ninjia(string a,string b,int c,int d,int e,int f):creature(a,b,c,d,e,f){
		getwuqi();
	}


	//ninjia使用bomb不会使自己受伤
	//待补充
};

class iceman:public creature{
	public:
	void getwuqi(){
		int bianhao=xuhao%3;
		string wuqi1=wuqixuanze[bianhao];
		wuqi new_wuqi; // 创建一个新的武器对象
        new_wuqi.yingshe(wuqi1, new_wuqi.ci,new_wuqi.bili); // 初始化武器
        wuqichi.push_back(new_wuqi); // 将武器添加到武器池中
		wuqishu++;
	}

	iceman(string a,string b,int c,int d,int e,int f):creature(a,b,c,d,e,f){
		getwuqi();
	}




	//每前进一步，生命值减去10%
	void kouxue(){
		int jian=life*1/10;
		life=life-jian;
	}
};

class wolf:public creature{
	public:
	void getwuqi(){

	}
	

	wolf(string a,string b,int c,int d,int e,int f):creature(a,b,c,d,e,f){
		
	}

	//抢走别人的武器
	//待补充
};

class lion:public creature{
	public:
	void getwuqi(){
		int bianhao=xuhao%3;
		string wuqi1=wuqixuanze[bianhao];
		wuqi new_wuqi; // 创建一个新的武器对象
        new_wuqi.yingshe(wuqi1, new_wuqi.ci,new_wuqi.bili); // 初始化武器
        wuqichi.push_back(new_wuqi); // 将武器添加到武器池中
		wuqishu++;
	}

	int loyalty;

	lion(string a,string b,int c,int d,int e,int f,int zhong):creature(a,b,c,d,e,f){
		loyalty=zhong;
		getwuqi();
	}


	

	void buzhong(){
		loyalty=loyalty-zhongcheng;
	}

	int zhongxin(){
		return loyalty;
	}
};


class red{
	public:
	int hunli;//生命源
	int shu;//士兵的数量
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
			
			r->redarm[r->shu]=new dragon("red","dragon",r->shu+1,gongjili[0],shengmingzhi[0],0);
		}

		r->hunli=r->hunli-redfei[redxu];
		r->shu++;

		cout << "red "<< redlei[redxu]<< " " << r->shu << " born" << endl;
		if(redxu==1){
			cout<< "Its loyalty is " << r->hunli<< endl;
		}

		redxu++;
		if(redxu==5){
			redxu=0;
		}

	}else{

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
			
			b->bluearm[b->shu]=new dragon("blue","dragon",b->shu+1,gongjili[0],shengmingzhi[0],N+1);
		}

	
		b->shu++;
		b->hunli=b->hunli-bluefei[bluexu];

		cout << "blue "<< bluelei[bluexu]<< " " << b->shu << " born" << endl;
		if(bluexu==0){
			cout << "Its loyalty is " << b->hunli << endl;
		}


		bluexu++;
		if(bluexu==5){
			bluexu=0;
		}

	}else{

	}
}






//狮子叛逃事件
void lionpantao(red*p,blue*q){
	for(int i=0;i<p->shu;i++){
		if(p->redarm[i]->zhonglei=="lion" and p->redarm[i]->zhongxin()<=0 and p->redarm[i]->life>0){
			p->redarm[i]->life=0;//狮子逃跑视为死亡
			baoshi(shi,fen);
			cout << "red lion "<< p->redarm[i]->xuhao << " ran away" << endl;
		}
	}
	for(int i=0;i<q->shu;i++){
		if(q->bluearm[i]->zhonglei=="lion" and q->bluearm[i]->zhongxin()<=0 and q->bluearm[i]->life>0){
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
			p->redarm[i]->weizhi++;
			if(p->redarm[i]->zhonglei=="iceman"){
				p->redarm[i]->kouxue();
			}
			
			
			if(p->redarm[i]->zhonglei=="lion"){//顺便lion减忠心
				p->redarm[i]->buzhong();
			}

		
		}
	
	}
	for(int i=0;i<q->shu;i++){
		if(q->bluearm[i]->life>0){
			q->bluearm[i]->weizhi--;

			if(q->bluearm[i]->zhonglei=="iceman"){
				q->bluearm[i]->kouxue();
			}
		
			if(q->bluearm[i]->zhonglei=="lion"){
				q->bluearm[i]->buzhong();
			}
		}
		
	}

	for(int i=0;i<=N+1;i++){
		for(int j=0;j<p->shu;j++){
			if(p->redarm[j]->weizhi==i and p->redarm[j]->life>0 and i!=N+1){
				baoshi(shi,fen);
				cout << "red " << p->redarm[j]->zhonglei<< " " << p->redarm[j]->xuhao<< " marched to city " << p->redarm[j]->weizhi<< " with "<< p->redarm[j]->life<< " elements and force "<<p->redarm[j]->shanghai<<endl;
			}
			if(p->redarm[j]->weizhi==i and p->redarm[j]->life>0 and i==N+1){
				baoshi(shi,fen);
				//输出样例：001:10 red iceman 1 reached blue headquarter with 20 elements and force 30
				cout << "red " << p->redarm[j]->zhonglei << " " << p->redarm[j]->xuhao << " reached blue headquarter with " << p->redarm[j]->life << " elements and force " << p->redarm[j]->shanghai << endl;

				baoshi(shi,fen);
				//输出样例：003:10 blue headquarter was taken
				cout << "blue headquarter was taken"<< endl;
			}
		}
		for(int j=0;j<q->shu;j++){
			if(q->bluearm[j]->weizhi==i and q->bluearm[j]->life>0 and i!=0){
				baoshi(shi,fen);
				cout << "blue " <<q->bluearm[j]->zhonglei << " " << q->bluearm[j]->xuhao << " marched to city "<<q->bluearm[j]->weizhi<<" with "<< q->bluearm[j]->life << " elements and force "<< q->bluearm[j]->shanghai << endl;
			}
			if(q->bluearm[j]->weizhi==i and q->bluearm[j]->life>0 and i==0){
				baoshi(shi,fen);
				cout << "blue " << q->bluearm[j]->zhonglei << " " << q->bluearm[j]->xuhao << " reached red headquarter with " << q->bluearm[j]->life << " elements and force " << q->bluearm[j] ->shanghai<< endl;

				baoshi(shi,fen);
				cout << "red headquarter was taken" << endl;
			}
		}
	}
}


//抢劫，之前给武器排顺序
void wuqipaixu1(red*p,blue*q){
	for(int i=0;i<p->shu;i++){
		   for(int j=0;j<p->redarm[i]->wuqishu-1;j++){
				for(int k=0;k<=p->redarm[i]->wuqishu-2-j;k++){
						if(p->redarm[i]->wuqichi[k].zhonglei=="sword"){

						}else{
							if(p->redarm[i]->wuqichi[k].zhonglei=="bomb" and p->redarm[i]->wuqichi[k+1].zhonglei=="sword"){
									wuqi temp;
									temp=p->redarm[i]->wuqichi[k];
									p->redarm[i]->wuqichi[k]=p->redarm[i]->wuqichi[k+1];
									p->redarm[i]->wuqichi[k+1]=temp;
									continue;
							}
							if(p->redarm[i]->wuqichi[k].zhonglei=="arrow" and p->redarm[i]->wuqichi[k+1].zhonglei=="sword"){
								wuqi temp;
								temp=p->redarm[i]->wuqichi[k];
								p->redarm[i]->wuqichi[k]=p->redarm[i]->wuqichi[k+1];
								p->redarm[i]->wuqichi[k+1]=temp;
								continue;
							}
							if(p->redarm[i]->wuqichi[k].zhonglei=="arrow" and p->redarm[i]->wuqichi[k+1].zhonglei=="bomb"){
								wuqi temp;
								temp=p->redarm[i]->wuqichi[k];
								p->redarm[i]->wuqichi[k]=p->redarm[i]->wuqichi[k+1];
								p->redarm[i]->wuqichi[k+1]=temp;
								continue;
							}
							if(p->redarm[i]->wuqichi[k].zhonglei=="arrow" and p->redarm[i]->wuqichi[k+1].zhonglei=="arrow" and p->redarm[i]->wuqichi[k].ci<p->redarm[i]->wuqichi[k+1].ci){
								wuqi temp;
								temp=p->redarm[i]->wuqichi[k];
								p->redarm[i]->wuqichi[k]=p->redarm[i]->wuqichi[k+1];
								p->redarm[i]->wuqichi[k+1]=temp;
								continue;
							}
						}
				}
		   }
	}
	for(int i=0;i<q->shu;i++){
		for(int j=0;j<q->bluearm[i]->wuqishu-1;j++){
			 for(int k=0;k<=q->bluearm[i]->wuqishu-2-j;k++){
					 if(q->bluearm[i]->wuqichi[k].zhonglei=="sword"){

					 }else{
						 if(q->bluearm[i]->wuqichi[k].zhonglei=="bomb" and q->bluearm[i]->wuqichi[k+1].zhonglei=="sword"){
								 wuqi temp;
								 temp=q->bluearm[i]->wuqichi[k];
								 q->bluearm[i]->wuqichi[k]=q->bluearm[i]->wuqichi[k+1];
								 q->bluearm[i]->wuqichi[k+1]=temp;
								 continue;
						 }
						 if(q->bluearm[i]->wuqichi[k].zhonglei=="arrow" and q->bluearm[i]->wuqichi[k+1].zhonglei=="sword"){
							 wuqi temp;
							 temp=q->bluearm[i]->wuqichi[k];
							 q->bluearm[i]->wuqichi[k]=q->bluearm[i]->wuqichi[k+1];
							 q->bluearm[i]->wuqichi[k+1]=temp;
							 continue;
						 }
						 if(q->bluearm[i]->wuqichi[k].zhonglei=="arrow" and q->bluearm[i]->wuqichi[k+1].zhonglei=="bomb"){
							 wuqi temp;
							 temp=q->bluearm[i]->wuqichi[k];
							 q->bluearm[i]->wuqichi[k]=q->bluearm[i]->wuqichi[k+1];
							 q->bluearm[i]->wuqichi[k+1]=temp;
							 continue;
						 }
						 if(q->bluearm[i]->wuqichi[k].zhonglei=="arrow" and q->bluearm[i]->wuqichi[k+1].zhonglei=="arrow" and q->bluearm[i]->wuqichi[k].ci<q->bluearm[i]->wuqichi[k+1].ci){
							 wuqi temp;
							 temp=q->bluearm[i]->wuqichi[k];
							 q->bluearm[i]->wuqichi[k]=q->bluearm[i]->wuqichi[k+1];
							 q->bluearm[i]->wuqichi[k+1]=temp;
							 continue;
						 }
					 }
			 }
		}
    }
}

//战斗前的武器排序
void wuqipaixu2(red*p,blue*q){
	for(int i=0;i<p->shu;i++){
		for(int j=0;j<p->redarm[i]->wuqishu-1;j++){
			 for(int k=0;k<=p->redarm[i]->wuqishu-2-j;k++){
					 if(p->redarm[i]->wuqichi[k].zhonglei=="sword"){

					 }else{
						 if(p->redarm[i]->wuqichi[k].zhonglei=="bomb" and p->redarm[i]->wuqichi[k+1].zhonglei=="sword"){
								 wuqi temp;
								 temp=p->redarm[i]->wuqichi[k];
								 p->redarm[i]->wuqichi[k]=p->redarm[i]->wuqichi[k+1];
								 p->redarm[i]->wuqichi[k+1]=temp;
								 continue;
						 }
						 if(p->redarm[i]->wuqichi[k].zhonglei=="arrow" and p->redarm[i]->wuqichi[k+1].zhonglei=="sword"){
							 wuqi temp;
							 temp=p->redarm[i]->wuqichi[k];
							 p->redarm[i]->wuqichi[k]=p->redarm[i]->wuqichi[k+1];
							 p->redarm[i]->wuqichi[k+1]=temp;
							 continue;
						 }
						 if(p->redarm[i]->wuqichi[k].zhonglei=="arrow" and p->redarm[i]->wuqichi[k+1].zhonglei=="bomb"){
							 wuqi temp;
							 temp=p->redarm[i]->wuqichi[k];
							 p->redarm[i]->wuqichi[k]=p->redarm[i]->wuqichi[k+1];
							 p->redarm[i]->wuqichi[k+1]=temp;
							 continue;
						 }
						 if(p->redarm[i]->wuqichi[k].zhonglei=="arrow" and p->redarm[i]->wuqichi[k+1].zhonglei=="arrow" and p->redarm[i]->wuqichi[k].ci>p->redarm[i]->wuqichi[k+1].ci){
							 wuqi temp;
							 temp=p->redarm[i]->wuqichi[k];
							 p->redarm[i]->wuqichi[k]=p->redarm[i]->wuqichi[k+1];
							 p->redarm[i]->wuqichi[k+1]=temp;
							 continue;
						 }
					 }
			 }
		}
    }
	for(int i=0;i<q->shu;i++){
		for(int j=0;j<q->bluearm[i]->wuqishu-1;j++){
			 for(int k=0;k<=q->bluearm[i]->wuqishu-2-j;k++){
					 if(q->bluearm[i]->wuqichi[k].zhonglei=="sword"){

					 }else{
						 if(q->bluearm[i]->wuqichi[k].zhonglei=="bomb" and q->bluearm[i]->wuqichi[k+1].zhonglei=="sword"){
								 wuqi temp;
								 temp=q->bluearm[i]->wuqichi[k];
								 q->bluearm[i]->wuqichi[k]=q->bluearm[i]->wuqichi[k+1];
								 q->bluearm[i]->wuqichi[k+1]=temp;
								 continue;
						 }
						 if(q->bluearm[i]->wuqichi[k].zhonglei=="arrow" and q->bluearm[i]->wuqichi[k+1].zhonglei=="sword"){
							 wuqi temp;
							 temp=q->bluearm[i]->wuqichi[k];
							 q->bluearm[i]->wuqichi[k]=q->bluearm[i]->wuqichi[k+1];
							 q->bluearm[i]->wuqichi[k+1]=temp;
							 continue;
						 }
						 if(q->bluearm[i]->wuqichi[k].zhonglei=="arrow" and q->bluearm[i]->wuqichi[k+1].zhonglei=="bomb"){
							 wuqi temp;
							 temp=q->bluearm[i]->wuqichi[k];
							 q->bluearm[i]->wuqichi[k]=q->bluearm[i]->wuqichi[k+1];
							 q->bluearm[i]->wuqichi[k+1]=temp;
							 continue;
						 }
						 if(q->bluearm[i]->wuqichi[k].zhonglei=="arrow" and q->bluearm[i]->wuqichi[k+1].zhonglei=="arrow" and q->bluearm[i]->wuqichi[k].ci>q->bluearm[i]->wuqichi[k+1].ci){
							 wuqi temp;
							 temp=q->bluearm[i]->wuqichi[k];
							 q->bluearm[i]->wuqichi[k]=q->bluearm[i]->wuqichi[k+1];
							 q->bluearm[i]->wuqichi[k+1]=temp;
							 continue;
						 }
					 }
			 }
		}
    }
}


int redwolf(red*p,blue*q,int j,int i,string wuqi){
	if(p->redarm[j]->wuqishu<10 and q->bluearm[i]->wuqishu>0){
		p->redarm[j]->wuqichi.push_back(move(q->bluearm[i]->wuqichi[0]));
		q->bluearm[i]->wuqichi.erase(q->bluearm[i]->wuqichi.begin()+0);
		q->bluearm[i]->wuqishu--;
		p->redarm[j]->wuqishu++;
		if(q->bluearm[i]->wuqishu>0 and q->bluearm[i]->wuqichi[0].zhonglei==wuqi){
			return redwolf(p,q,j,i,wuqi)+1;
		}else{
			return 1;
		}
	}else{
		return 0;
	}
	
}

int  bluewolf(red*p,blue*q,int j,int i,string wuqi){
	if(q->bluearm[i]->wuqishu<10 and p->redarm[j]->wuqishu>0){
		q->bluearm[i]->wuqichi.push_back(move(p->redarm[j]->wuqichi[0]));
		p->redarm[j]->wuqichi.erase(p->redarm[j]->wuqichi.begin()+0);
		p->redarm[j]->wuqishu--;
		q->bluearm[i]->wuqishu++;
		if(p->redarm[j]->wuqishu>0 and p->redarm[j]->wuqichi[0].zhonglei==wuqi){
			return 1+bluewolf(p,q,j,i,wuqi);
		}else{
			return 1;
		}
	}else{
		return 0;
	}
}


//wolf抢劫武器事件
void wolfqiangjie(red*p,blue*q){
	for(int i=0;i<q->shu;i++){
		if(q->bluearm[i]->life>0 ){
			for(int j=0;j<p->shu;j++){
				if(p->redarm[j]->weizhi==q->bluearm[i]->weizhi and p->redarm[j]->life>0){
						if(p->redarm[j]->zhonglei=="wolf" and q->bluearm[i]->zhonglei!="wolf"){
							if(p->redarm[j]->wuqishu<10 and q->bluearm[i]->wuqishu>0){
				
								string wuqi=q->bluearm[i]->wuqichi[0].zhonglei;
								int jige=redwolf(p,q,j,i,q->bluearm[i]->wuqichi[0].zhonglei);
								baoshi(shi,fen);
								cout <<"red wolf "<< j+1 <<" took " << jige << " " << wuqi<<" from blue "<<q->bluearm[i]->zhonglei<<" " <<i+1 <<" in city " << q->bluearm[i]->weizhi<<endl;
							}
						
							
						}
						if(q->bluearm[i]->zhonglei=="wolf" and p->redarm[j]->zhonglei!="wolf"){
							if(p->redarm[j]->wuqishu>0 and q->bluearm[i]->wuqishu<10){
								string wuqi=p->redarm[j]->wuqichi[0].zhonglei;
								int shu=bluewolf(p,q,j,i,p->redarm[j]->wuqichi[0].zhonglei);
								baoshi(shi,fen);
								cout<< "blue wolf "<< i+1 << " took " << shu <<" " << wuqi <<" from red " << p->redarm[j]->zhonglei << " " <<j+1 <<" in city " << p->redarm[j]->weizhi<< endl;
							}
						
						}
						break;
				}
			}
		}
	
	}
}

bool dajiajieshu(red*p,blue*q,int r,int b,int rwx,int bwx){
	if(p->redarm[r]->wuqishu==0 and q->bluearm[b]->wuqishu==0){
		return true;
	}
	if(p->redarm[r]->life<=0 or q->bluearm[b]->life<=0){
		return  true;
	}
	if((p->redarm[r]->wuqishu==0 or (p->redarm[r]->wuqishu>0 and p->redarm[r]->wuqichi[rwx].bili*p->redarm[r]->shanghai/10==0)) and (q->bluearm[b]->wuqishu==0 or (q->bluearm[b]->wuqishu>0 and q->bluearm[b]->wuqichi[bwx].bili*q->bluearm[b]->shanghai/10==0))){
		for(int i=0;i<p->redarm[r]->wuqishu;i++){
			if(p->redarm[r]->wuqichi[i].zhonglei=="bomb" or p->redarm[r]->wuqichi[i].zhonglei=="arrow"){
				return false;
			}
		}
		for(int i=0;i<q->bluearm[b]->wuqishu;i++){
			if(q->bluearm[b]->wuqichi[i].zhonglei=="bomb" or q->bluearm[b]->wuqichi[i].zhonglei=="arrow"){
				return false;
			}
		}
		return true;
	}
	return false;
}



void jianchawuqir(red*p,int r,int& rwx){

	if(p->redarm[r]->wuqichi[rwx].ci==0){
		p->redarm[r]->wuqichi.erase(p->redarm[r]->wuqichi.begin()+rwx);
		p->redarm[r]->wuqishu--;	
		if(p->redarm[r]->wuqishu-1>=rwx){
			
		}else{
			rwx=0;
		}
	}else{
		if(p->redarm[r]->wuqishu-1>rwx){
			rwx++;
		}else{
			rwx=0;
		}
	}

}

void jianchawuqib(blue*q,int b,int &bwx){
	if(q->bluearm[b]->wuqichi[bwx].ci==0){
		q->bluearm[b]->wuqichi.erase(q->bluearm[b]->wuqichi.begin()+bwx);
		q->bluearm[b]->wuqishu--;
			//切换下一件武器
		if(q->bluearm[b]->wuqishu-1>=bwx){
		
		}else{
			bwx=0;
		}

	}else{
		if(q->bluearm[b]->wuqishu-1>bwx){
			bwx++;
		}else{
			bwx=0;
		}
	}
}

void rgongji(int r,int b,red*p,blue*q,int& rwx){
	if(p->redarm[r]->wuqichi[rwx].ci!=0){
		if(p->redarm[r]->wuqichi[rwx].zhonglei=="sword"){
			int shanghai=p->redarm[r]->shanghai*2/10;
			q->bluearm[b]->life=q->bluearm[b]->life-shanghai;
		}
		if(p->redarm[r]->wuqichi[rwx].zhonglei=="bomb"){
			int di=p->redarm[r]->shanghai*4/10;
			q->bluearm[b]->life=q->bluearm[b]->life-di;
			int wo=di/2;
			if(p->redarm[r]->zhonglei!="ninja"){
				p->redarm[r]->life=p->redarm[r]->life-wo;
			}
		
			p->redarm[r]->wuqichi[rwx].ci--;
		}
		if(p->redarm[r]->wuqichi[rwx].zhonglei=="arrow"){
			int shanghai=p->redarm[r]->shanghai*3/10;
			q->bluearm[b]->life=q->bluearm[b]->life-shanghai;
			p->redarm[r]->wuqichi[rwx].ci--;
		}
	}

	jianchawuqir(p,r,rwx);




	if(p->redarm[r]->wuqichi[rwx].ci==0){

	
		int flag=0;
		for(int i=0;i<p->redarm[r]->wuqishu;i++){
			if(p->redarm[r]->wuqichi[i].ci>0){
				flag=1;
				break;
			}
		}
		if(flag==1){
	
			label:
			if(p->redarm[r]->wuqishu-1>rwx){
				rwx++;
				haha:
					if(p->redarm[r]->wuqichi[rwx].ci==0){
						goto label;
					}
			}else{
				rwx=0;
				goto haha;
			}
		}else{
			return;
		}
	}
	
}

void bgongji(int r,int b,red*p,blue*q,int& bwx){
	if(q->bluearm[b]->wuqichi[bwx].ci!=0){
		if(q->bluearm[b]->wuqichi[bwx].zhonglei=="sword"){
			int shanghai=q->bluearm[b]->shanghai*2/10;
			p->redarm[r]->life=p->redarm[r]->life-shanghai;
		}
		if(q->bluearm[b]->wuqichi[bwx].zhonglei=="bomb"){
			int di=q->bluearm[b]->shanghai*4/10;
			p->redarm[r]->life=p->redarm[r]->life-di;
			int wo=di/2;
			if(q->bluearm[b]->zhonglei!="ninja"){
				q->bluearm[b]->life=q->bluearm[b]->life-wo;
			}
	
			q->bluearm[b]->wuqichi[bwx].ci--;
		}
		if(q->bluearm[b]->wuqichi[bwx].zhonglei=="arrow"){
			int shanghai=q->bluearm[b]->shanghai*3/10;
			p->redarm[r]->life=p->redarm[r]->life-shanghai;
			q->bluearm[b]->wuqichi[bwx].ci--;
		}
	}

	jianchawuqib(q,b,bwx);



	
	if(q->bluearm[b]->wuqichi[bwx].ci==0){

	
		int flag=0;
		for(int i=0;i<q->bluearm[b]->wuqishu;i++){
			if(q->bluearm[b]->wuqichi[i].ci>0){
				flag=1;
				break;
			}
		}
		if(flag==1){
	
			label:
			if(q->bluearm[b]->wuqishu-1>bwx){
				bwx++;
				haha:
					if(q->bluearm[b]->wuqichi[bwx].ci==0){
						goto label;
					}
			}else{
				bwx=0;
				goto haha;
			}
		}else{
			return;
		}
	}
}




void zhandoubaogao(red*p,blue*q,int rwei,int bwei);



//在某座城市发生战斗
void zhandou(red*p,blue*q,int N){
	for(int i=1;i<=N;i++){//第i座城市
		int rwei,bwei;
		int flag=0;
		//双方选手入场
		for(int j=0;j<p->shu;j++){
			if(p->redarm[j]->weizhi==i and p->redarm[j]->life>0){
				rwei=j;
				flag++;
				break;
			}
		}
 		for(int j=0;j<q->shu;j++){
			if(q->bluearm[j]->weizhi==i and q->bluearm[j]->life>0){
				bwei=j;
				flag++;
				break;
			}
		}

		if(flag==2){
			if(i%2==1){//红武士先打
				int rwx=0;
				int bwx=0;
					while(!dajiajieshu(p,q,rwei,bwei,rwx,bwx)){
						if(p->redarm[rwei]->wuqishu>0){
							rgongji(rwei,bwei,p,q,rwx);
						}
						
						if(q->bluearm[bwei]->wuqishu>0 and p->redarm[rwei]->life>0 and q->bluearm[bwei]->life>0){
							bgongji(rwei,bwei,p,q,bwx);
						}
					
					}

		
			}else{//蓝武士先打
				int rwx=0;
				int bwx=0;
					while(!dajiajieshu(p,q,rwei,bwei,rwx,bwx)){
						if(q->bluearm[bwei]->wuqishu>0){
							bgongji(rwei,bwei,p,q,bwx);
						}
						
						if(p->redarm[rwei]->wuqishu>0 and p->redarm[rwei]->life>0 and q->bluearm[bwei]->life>0){
							rgongji(rwei,bwei,p,q,rwx);
						}
					
					}
			}

			zhandoubaogao(p,q,rwei,bwei);

	
		}

		
	}	
}

void zhandoubaogao(red*p,blue*q,int rwei,int bwei){
	if(p->redarm[rwei]->life<=0 and q->bluearm[bwei]->life<=0){
					
		baoshi(shi,fen);
		cout << "both red "<< p->redarm[rwei]->zhonglei<< " " << p->redarm[rwei]->xuhao<< " and blue " << q->bluearm[bwei]->zhonglei<< " "<< q->bluearm[bwei]->xuhao<<" died in city " << q->bluearm[bwei]->weizhi << endl;

		
	}
	if(p->redarm[rwei]->life<=0 and q->bluearm[bwei]->life>0){
		baoshi(shi,fen);
		//000:40 red iceman 1 killed blue lion 12 in city 2 remaining 20 elements
		cout << "blue " << q->bluearm[bwei]->zhonglei<< " " << q->bluearm[bwei]->xuhao << " killed red " << p->redarm[rwei]->zhonglei << " " << p->redarm[rwei]->xuhao<< " in city " << p->redarm[rwei]->weizhi << " remaining "<< q->bluearm[bwei]->life << " elements" << endl;
		//缴获胜利武器
		wuqipaixu1(p,q);
		while(q->bluearm[bwei]->wuqishu<10 and p->redarm[rwei]->wuqishu>0){
			q->bluearm[bwei]->wuqichi.push_back(move(p->redarm[rwei]->wuqichi[0]));
			p->redarm[rwei]->wuqichi.erase(p->redarm[rwei]->wuqichi.begin()+0);
			q->bluearm[bwei]->wuqishu++;
			p->redarm[rwei]->wuqishu--;
		}

		if(q->bluearm[bwei]->zhonglei=="dragon"){
			q->bluearm[bwei]->huanhu();
		}
	}
	if(q->bluearm[bwei]->life<=0 and p->redarm[rwei]->life>0){
		baoshi(shi,fen);
		cout << "red " << p->redarm[rwei] ->zhonglei << " " << p->redarm[rwei] ->xuhao << " killed blue " << q->bluearm[bwei]->zhonglei << " " << q->bluearm[bwei]->xuhao << " in city "<< q->bluearm[bwei]-> weizhi << " remaining " << p->redarm[rwei] ->life << " elements"<< endl;
		while(p->redarm[rwei]->wuqishu<10 and q->bluearm[bwei]->wuqishu>0){
			p->redarm[rwei]->wuqichi.push_back(move(q->bluearm[bwei]->wuqichi[0]));
			q->bluearm[bwei]->wuqichi.erase(q->bluearm[bwei]->wuqichi.begin()+0);
			p->redarm[rwei]->wuqishu++;
			q->bluearm[bwei]->wuqishu--;
		}
		if(p->redarm[rwei]->zhonglei=="dragon"){
			p->redarm[rwei]->huanhu();
		}
	}
	if(q->bluearm[bwei]->life>0 and p->redarm[rwei]->life>0){
		//000:40 both red iceman 1 and blue lion 12 were alive in city 2
		baoshi(shi,fen);
		cout << "both red " << p->redarm[rwei]->zhonglei<< " " << p->redarm[rwei]->xuhao << " and blue " << q->bluearm[bwei]->zhonglei << " " << q->bluearm[bwei]->xuhao << " were alive in city " << p->redarm[rwei]->weizhi<< endl;
		if(p->redarm[rwei]->zhonglei=="dragon"){
			p->redarm[rwei]->huanhu();
		}
		if(q->bluearm[bwei]->zhonglei=="dragon"){
			q->bluearm[bwei]->huanhu();
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
	
	for(int i=1;i<=N;i++){
	
		for(int j=0;j<p->shu;j++){
			if(p->redarm[j]->weizhi==i and p->redarm[j]->life>0){
				baoshi(shi,fen);
			
				int sword=0;
				int bomb=0;
				int arrow=0;
				
				for(int k=0;k<p->redarm[j]->wuqishu;k++){
					if(p->redarm[j]->wuqichi[k].zhonglei=="sword"){
						sword++;
					}
					if(p->redarm[j]->wuqichi[k].zhonglei=="bomb"){
						bomb++;
					}
					if(p->redarm[j]->wuqichi[k].zhonglei=="arrow"){
						arrow++;
					}
				}
						//000:55 blue wolf 2 has 2 sword 3 bomb 0 arrow and 7 elements
						cout << "red " << p->redarm[j]->zhonglei<< " " << p->redarm[j]->xuhao << " has " << sword <<" sword"<< " " << bomb << " bomb "<< arrow << " arrow and " << p->redarm[j]->life << " elements" << endl;
			}
		}
			
		
		for(int j=0;j<q->shu;j++){
			if(q->bluearm[j]->weizhi==i and q->bluearm[j]->life>0){
				baoshi(shi,fen);
			

				int sword=0;
				int bomb=0;
				int arrow=0;

				for(int k=0;k<q->bluearm[j]->wuqishu;k++){
					if(q->bluearm[j]->wuqichi[k].zhonglei=="sword"){
						sword++;
					}
					if(q->bluearm[j]->wuqichi[k].zhonglei=="bomb"){
						bomb++;
					}
					if(q->bluearm[j]->wuqichi[k].zhonglei=="arrow"){
						arrow++;
					}
				}
				//000:55 blue wolf 2 has 2 sword 3 bomb 0 arrow and 7 elements
				cout << "blue "<< q->bluearm[j]->zhonglei<< " " << q->bluearm[j]->xuhao << " has " << sword << " sword " << bomb << " bomb " << arrow << " arrow and " << q->bluearm[j]->life<< " elements" << endl;
			}
		}
	}

}

//是否有士兵到达敌方指挥部，那么战争结束
bool zhanzhengjieshu(red*p,blue*q,int N){
	for(int i=0;i<p->shu;i++){
		if(p->redarm[i]->weizhi==N+1){
			return true;

		}
	}
	for(int j=0;j<q->shu;j++){
		if(q->bluearm[j]->weizhi==0){
			return true;
		}
	}
	return false;
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

		
		


		int M,N,K,T;
		cin >> M >> N >> K >> T;//N是城市数量，K是lion每前进一步忠诚值的减少量

		zhongcheng=K;
		

		red red(M,0);
		blue blue(M,0);


		for(int i=0;i<5;i++){
			cin >> shengmingzhi[i];
		}

		feishe();//将费用转化成red和blue的顺序


	

		for(int i=0;i<5;i++){
			cin >> gongjili[i];
		}



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


					fen=35;

					if(jieshulema(T)){
						break;
					}
				

					wuqipaixu1(&red,&blue);//完成
					wolfqiangjie(&red,&blue);//完成

					fen=40;
					if(jieshulema(T)){
						break;
					}
					
					wuqipaixu2(&red,&blue);
					zhandou(&red,&blue,N);

				

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
			}else{
			
			}

			shi++;
		}
	




	}



	return 0;
}