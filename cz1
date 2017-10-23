/*###########################################################
#实验目的：模拟生产者消费者问题，掌握进程同步问题的基本算法 #
#实验要求：													#
#1.设置公用缓冲池大小为10									#
#2.程序运行后可接受三种输入：P（模拟生产者进程）、C（模拟消 #
#费者进程）、Q（退出程序），对其他输入返回提示语句"输入非法"#
#并继续等待输入。											#
#3.每输入一个值时，显示当前空缓冲区与满缓冲区个数及当前缓冲 #
#池使用情况（输入P时应将一个空缓冲区的值置为1，输入C时应将一#
#个满缓冲区的值置为0）。									#
#4.当缓冲池满时，输入P应提示"缓冲池已满请等候"提示；当缓冲池#
#为空时，输入C应提示"缓冲池已空请等候"提示					#
#															#
#############################################################*/

#include "stdio.h"
#include "windows.h"
#include "conio.h"


//声明全局变量
int buffer[9];
int counter = 0;
int poi = 0;//指向当前buffer
int teshu = 0;
//声明函数
void exi();
void cls();
void inp8();
void cleinp();
void showinfo();
void scz();
int xfz();
int isfull();


int isfull(){
	if ( counter == 10 ){
		return 1;
	}
	else{
		return 0;
	}
}

int isempty(){
	if ( counter == 0 ){
		return 1;
	}
	else{
		return 0;
	}
}

void showinfo(){
	int i;
	printf("################################################################################");
	printf("#                                                                              #");
	printf("#      使用说明：                                                              #");
	printf("#                                                                              #");
	printf("#      1.生产者通过C(c)来调用生产者程序为缓冲区输入数据；                      #");
	printf("#      2.消费者通过P(p)来读取缓冲区的数据；                                    #");
	printf("#      3.输入Q(q)可以退出程序；                                                #");
	printf("#      4.通过F(f)可以重新加载显示区间                                          #");
	printf("#      5.通过T(t)来");
	if (teshu) {
		printf("禁用");
	}
	else{
		printf("启用");
	}
	printf("特殊模式(严格按照作业需求完成功能)       当前：");
	if (teshu) {
		printf("特殊");
	}
	else{
		printf("标准");
	}
	printf("     #");
	printf("#                                                                              #");
	printf("#                                                                              #");
	printf("################################################################################");
	printf("现在的缓冲区情况如下：\n");
	for(i=0;i<10;i++){
		printf("缓冲区 %d : %d",i,buffer[i]);
		if ( i % 4 == 0 && i) {
			printf("\n");
		}
		else{
			printf("\t");
		}
	}
	//输出缓冲区信息
	if (isempty()) {
		printf("\n\t当前缓冲区空");
	}
	else if (isfull()) {
		printf("\n\t当前缓冲区满");
	}
	else{
		printf("\n\t当前缓冲区已用空间： %d",counter);
	}
	if(!isfull()){
		printf("\n\t当前 输入 指针指向 缓冲区%d",poi);
	}
}


void star(){
	int i;
	for(i=0;i<10;i++){
		buffer[i] = 0;
	}
}

//*函数入口
void main(){
	star();//初始化
	inp8();
}
//*/

//*处理输入
void inp8(){
	int getcha;
	int temm;
	int needcls = 1;
	//定义临时变量存储输入的数据
	

	//谁定一个无限循环来持续获取输入，知道得到Q输入退出
	for(;;){
		if (needcls)
		cls(),//清屏
		showinfo();//显示当前信息//设定显示内容
		cleinp();
		//清理输入缓冲区
		getcha = 0;
		getcha = getch();

		//获取输入

		/*
		判断输入
		并获取变量
			如果为C调用生产者进程
			如果为P调用消费者进程
			若为Q调用退出程序
		*/
		if(getcha){
			if(getcha == 'P' || getcha == 'p'){
				if(isfull()){
					printf("缓冲区满，请等待");
					needcls = 1;
					printf("\n按任意键继续");
					cleinp();
					getch();
					continue;
				}
				if (teshu) {
					printf("特殊模式，将1置入缓冲区");
					scz(1);
					needcls = 1;
					continue;
				}
				printf("\nP--生产者进程，请输入输入缓冲区的变量（整型）");
				scanf("%d",&temm);
				printf("输入获得\n");
				scz(temm);
				printf("\n生产者进程结束，按任意键继续");
				cleinp();
				getch();
				needcls = 1;
			}
			else{
				if(getcha == 'C' || getcha == 'c'){
					printf("\nC--消费进程，调用消费者进程");
					if (isempty()) {
						printf("缓冲区为空，请等待生产者输入\n用F来刷新显示，现在你可以继续输入");
						needcls = 0;
						continue;
					}
					if (teshu) {
						printf("特殊模式，取出数据1并置0缓冲区");
						xfz();
						needcls = 1;
						continue;
					}
					else{
						temm = xfz();
						printf("得到了消费者程序的返回：  %d",temm);
					}
					printf("\n消费者进程结束，按任意键继续");
					cleinp();
					getch();
					needcls = 1;
				}
				else{
					if(getcha == 'Q' || getcha == 'q'){
						printf("\n程序结束，按任意键退出程序，或输入N取消退出");
						cleinp();
						getcha = 0;
						getcha = getch();
						if(getcha == 'N' || getcha == 'n'){
							needcls = 1;
							//如果输入了Ｎ继续循环，不会执行退出
						}else{
							exi();
						}
					}
					else{
						if(getcha == 'F' || getcha == 'f'){
							needcls = 1;
							continue;
						}
						else{
							if(getcha == 'T' || getcha == 't' ){
								if (teshu) {
									teshu = 0;
								}
								else{
									teshu = 1;
								}

							}else{
								needcls = 0;
								printf("\n你没有给出一个正确的输入，请尝试重新输入");

							}

						}
						
					}
				}

			}
		}
	}
}
//*/


//*模拟生产者进程
void scz(int a){
/*	if (poi = 9){
		poi = 0;
	}
	else{
		poi++;
	}
	//*/
	buffer[poi] = a;
	poi++;
	counter++;
}
//*/




//*模拟消费者进程
int xfz(){
	int temm;
	temm = buffer[poi-1];
 	buffer[poi-1] = 0;
	//清理缓冲区
	poi--;
	counter--;
	//printf("%d",temm);
	return temm;
}
//*/





//*程序结束
void exi(){
	cls();
	printf("Fin");
	exit(0);
}
//*/

//*清屏
void cls(){
	system("cls");
}
//*/
void cleinp(){
	fflush(stdin);
}
