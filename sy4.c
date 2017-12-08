#include "stdio.h"
#include "windows.h"
int buff[10] = {0,0,0,0,0,0,0,0,0,0};//缓冲
int zz1 = 0,zz2 = 0,zz3 = 0;//指针
int i=0;//循环变量初始化
int t;
int counter = 0 ;

void main(){
	for (;;) {
		system("cls");
		printf("现在的缓冲区情况如下：\n");
		for(i=0;i<10;i++){
			printf("缓冲区 %d : %d",i,buff[i]);
			if ( i % 4 == 0 && i) {
				printf("\n");
			}
			else{
				printf("\t");
			}
		}
		printf("\n当前输入指针：%d,工作指针：%d,输出指针：%d\n",zz1,zz2,zz3);
		//显示当前指针
		fflush(stdin);
		t = getch();
		//获取输入
		
		switch(t) {
		case 'q':
		case 'Q':
			//若为Q则退出
			exit(0);
			break;
		case 'P':
		case 'p':
			//若为P且缓冲区不满则生产
			if (counter == 9){
				printf("缓冲区满，无法放入\n按任意键继续");
				getch();
				
			}
			else{
				buff[zz1] = 1;
				counter++;
				if (zz1 == 9) {
					zz1 = 0;
				}else{
					zz1++;
				}
			}
			break;
		case 'C':
		case 'c':
			//若为C+缓冲区不空则消费
			if (counter == 0 || zz2 == zz3)
			{
				printf("允许取出的缓冲为空，无法取出\n按任意键继续");
				getch();
				
			}
			else{
				counter--;
				buff[zz3] = 0;
				if (zz3 == 9) {
					zz3 = 0;
				}else{
					zz3++;
				}
			}
			break;
		case 'W':
		case 'w':
			if (zz1 == zz2){
				printf("允许工作的缓冲为空，请存入缓冲后再试\n按任意键继续");
				getch();
			}else{
				buff[zz2] = 2;
				if (zz2 == 9) {
					zz2 = 0;
				}else{
					zz2++;
				}
			}
			break;
		default:
			printf("输入错误\n按任意键继续");
			getch();
		}
	}
}
