#include <stdio.h>
float dq[4];
	int i=0,t=0,q=1;
	//循环变量，当前时间，时间片
	float l=0;
	//存放平均值
	struct jc {
		int id;//ID
		int ddtime;//到达时间
		int need;//服务时间（需要时间
		int start;//开始时间
		int used;//已经执行时间
		int end;//结束时间
		int isstart ;//开始标识
		int isend ;//结束标识
	};
	struct jc p[4],o;//进程列表，临时变量
	
void cc(){
	//将结构体第一位移到最后，其余依次前移
	o = p[0];
	for (i = 0; i<3 ;i++) {
		p[i] = p[i+1];
	}
	p[3] = o;
}
void main(){
	
	for (i=0;i<4;i++) {
		//获取输入
		printf("%d进程到达时间",i+1);
		scanf(" %d",&p[i].ddtime);
		printf("%d进程所需时间",i+1);
		scanf(" %d",&p[i].need);
		p[i].id = i;
		p[i].used = 0;
		p[i].isstart = 0;
		p[i].isend = 0;
	}
	//输入时间片长度
	printf("时间片长度：");
	scanf(" %d",&q);

	for (;;) {
		if(p[0].isend+p[1].isend+p[2].isend+p[3].isend == 4){
			//如果全部完成均为1则跳出循环
			break;
		}
		if (p[0].isend || p[0].ddtime > t) {
			//如果进程已经结束或者还未开始则继续执行下一个进程
			cc();
			continue;
		}
		if (p[0].isstart == 0) {
			//为新开始的进程记录开始时间
			p[0].isstart = 1;
			p[0].start = t;
		}
		if (p[0].need - p[0].used <=q) {
			//如果当前时间片能使当前进程完成
			p[0].isend = 1;//标记完成
			t = t + p[0].need - p[0].used;//时间+
			p[0].end = t;//记录结束时间
			p[0].used = p[0].need;//使用时间增加
		}
		else{
			t = t + q;//时间+
			p[0].used = p[0].used + q;//使用时间+
		}
		cc();

	}




	for (i = 0;i<4;i++) {
		//循环输出
		dq[i] = (p[i].end-p[i].start)/(float)p[i].need;//计算带权周转时间
		printf("进程%d:\n到达：%d\n服务：%d\n",p[i].id,p[i].ddtime,p[i].need);
		printf("开始：%d\n结束：%d\n",p[i].start,p[i].end);
		printf("周转：%d\n带权周转：%.3f\n\n",p[i].end-p[i].start,dq[i]);
		l = (p[i].end-p[i].start) + l;//服务时间累加（为计算平均数
	}
	printf("平均周转:%.3f",l/4);
	printf("平均带权周转:%.3f\n",(dq[0]+dq[1]+dq[2]+dq[3])/4);
}
