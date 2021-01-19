/*
 *	二进制时钟：
 *	用3*6方格表示时间，第一行6个方格为“时”，第二行6个方格为“分”，第三行6个方格为“秒”
 *	白色方格表示此时时间，6个方格软为白色从右至左分别表示2^0，2^1，……，2^5
 *	未来设想：时间不一定要用数字化表示，可以依靠感知获取时间，由此构想并设计另一款软件：颜色时钟
*/
#include <graphics.h>	//	图形库头文件
#include <math.h>

#define High 300	//	设置窗口大小
#define Width 600

int arry[6] = {0};	
int *p = &arry[6];

int* fun(int, int);	//	用于将时分秒分别转换为二进制存于数组中
void time(SYSTEMTIME);	//	时间主体
void time_2(int, SYSTEMTIME);	//	时间分支，目的：为了使“时分秒”调用同一函数，减少代码冗余，节约空间
int oldMinute = 0;	
int oldHour = 0;

int main()
{
	initgraph(Width, High);	
	BeginBatchDraw();	//	开始绘图

	while (1)	
	{
		SYSTEMTIME ti;
		GetLocalTime(&ti);		// 获取当前时间
		time(ti);				//	时间运算
		oldMinute = ti.wMinute;	//	将现在时间设定为旧时间
		oldHour = ti.wHour;
		FlushBatchDraw();		//	避免闪烁
//		Sleep(1);
//		cleardevice();
	}

	EndBatchDraw();		//	结束绘图
	closegraph();		// 关闭绘图窗口
	return 0;
}

//	用于将时分秒分别转换为二进制存于数组中
int* fun(int n, int sum)	//	不断取余2，除以2，最后结果为0则运算结束，将其中取余2时结果为1的位置存储在数组中
{
//	arry[sum] = 0;	
    if (n%2 == 1)
		arry[sum] = 1;
       // *(p+sum) = 1;
    if (n == 0)
        return 0;
	sum++;
    fun(n/2, sum);
    return p;
}

//	时间主体
void time(SYSTEMTIME ti)
{
	setlinecolor(BLACK);	//	将方块的边缘线颜色置为黑色
	//for(int i=3; i > 0; i--)
	//	time_2(i, ti);
	time_2(3, ti);

	//	为了不时刻更新“时”和“分”，节约消耗，提高效能
	if (ti.wMinute != oldMinute)
		time_2(2, ti);
	if (ti.wHour != oldHour)
		time_2(1, ti);
}

//	时间分支，目的：为了使“时分秒”调用同一函数，减少代码冗余，节约空间
void time_2(int num, SYSTEMTIME ti)
{
	int j = 0;
	for(int i=0; i<6; i++)	//	将数组置0, 目的：为了使之后调用fun()函数时，不会导致重复使用数组中存储的值，造成“跟随现象”（秒影响分，时；分影响时）
		arry[i] = 0;

	switch(num)	//	选择时间模式为：时/分/秒
	{
	case 1: 
		fun(ti.wHour, 0);
		break;
	case 2: 
		fun(ti.wMinute, 0);
		break;
	default: 
		fun(ti.wSecond, 0);
		break;
	}
	for (j=6; j > 0; j--)	//	屏幕显示二进制时间（用方块颜色表示）
	{
		if(arry[6-j] == 1)	//	若数组中值为1，则为白色，否则为黑色
		{
			setfillcolor(WHITE);	// 填充色为：白色，表示此时有时间
			//solidrectangle(100*(j-1), 200, 100*j,300);
			fillrectangle(100*(j-1), (num-1)*100, 100*j, num*100);   
        }else
        {
			setfillcolor(BLACK);    // 填充色为：黑色，表示此时无时间
            solidrectangle(100*(j-1), (num-1)*100, 100*j, num*100);
        }		
    }

}

/************************************************
*												*
*				制作者：onlykeri					*
*			最后修改时间：2020/2/21				*
*				版本：v1.0.0						*
*												*
************************************************/
