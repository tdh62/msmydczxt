#include <stdio.h>

void main(){
	int p[4][5] = {0};
	float dq[4];
	//0到达时间，1所需时间，2剩余时间，3开始时间，4完成时间
	int i=0,j=0,t=0,q=1;
	float l=1;
	for (i=0;i<4;i++) {
		printf("请输入%d进程到达时间",i+1);
		scanf(" %d",&p[i][0]);
		printf("请输入%d进程所需时间",i+1);
		scanf(" %d",&p[i][1]);
		p[i][2] = p[i][1];
	}
	printf("请输入时间片长度：");
	scanf(" %d",&q);
	for (;;) {
		if (p[0][2] != 0 || p[1][2] != 0 || p[2][2] != 0|| p[3][2]!= 0) {
			for (i = 0;i<4;i++) {
				if (p[i][2] == 0) {
					continue;
				}
				if (t < p[i][0]) {
					continue;
				}
				else{
					if (p[i][1] == p[i][2])
						p[i][3] = t;
					if (p[i][2] <= q) {
						t = t + p[i][2];
						p[i][4] = t;
						p[i][2] = 0;
					}
					else{
						t = t + q;
						p[i][2] = p[i][2] - q;
					}
				}
			}
		}
		else{
			printf("处理完成");
			break;
		}
	}

	for (i = 0;i<4;i++) {
		dq[i] = (p[i][4]-p[i][3])/(float)p[i][1];
		printf("进程%d:到达时间：%d,服务时间：%d,",i,p[i][0],p[i][1]);
		printf("开始时间：%d,结束时间：%d\n",p[i][3],p[i][4]);
		printf("周转时间：%d，带权周转时间：%.3f\n",p[i][4]-p[i][3],dq[i]);
		printf("\n\n");
		l = (p[i][4]-p[i][3]) + l;
	}
	printf("平均周转时间:%.3f",l/4);
	printf("平均带权周转时间:%.3f\n",(dq[0]+dq[1]+dq[2]+dq[3])/4);
}
