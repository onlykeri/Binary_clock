/*
 *	������ʱ�ӣ�
 *	��3*6�����ʾʱ�䣬��һ��6������Ϊ��ʱ�����ڶ���6������Ϊ���֡���������6������Ϊ���롱
 *	��ɫ�����ʾ��ʱʱ�䣬6��������Ϊ��ɫ��������ֱ��ʾ2^0��2^1��������2^5
 *	δ�����룺ʱ�䲻һ��Ҫ�����ֻ���ʾ������������֪��ȡʱ�䣬�ɴ˹��벢�����һ���������ɫʱ��
*/
#include <graphics.h>	//	ͼ�ο�ͷ�ļ�
#include <math.h>

#define High 300	//	���ô��ڴ�С
#define Width 600

int arry[6] = {0};	
int *p = &arry[6];

int* fun(int, int);	//	���ڽ�ʱ����ֱ�ת��Ϊ�����ƴ���������
void time(SYSTEMTIME);	//	ʱ������
void time_2(int, SYSTEMTIME);	//	ʱ���֧��Ŀ�ģ�Ϊ��ʹ��ʱ���롱����ͬһ���������ٴ������࣬��Լ�ռ�
int oldMinute = 0;	
int oldHour = 0;

int main()
{
	initgraph(Width, High);	
	BeginBatchDraw();	//	��ʼ��ͼ

	while (1)	
	{
		SYSTEMTIME ti;
		GetLocalTime(&ti);		// ��ȡ��ǰʱ��
		time(ti);				//	ʱ������
		oldMinute = ti.wMinute;	//	������ʱ���趨Ϊ��ʱ��
		oldHour = ti.wHour;
		FlushBatchDraw();		//	������˸
//		Sleep(1);
//		cleardevice();
	}

	EndBatchDraw();		//	������ͼ
	closegraph();		// �رջ�ͼ����
	return 0;
}

//	���ڽ�ʱ����ֱ�ת��Ϊ�����ƴ���������
int* fun(int n, int sum)	//	����ȡ��2������2�������Ϊ0�����������������ȡ��2ʱ���Ϊ1��λ�ô洢��������
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

//	ʱ������
void time(SYSTEMTIME ti)
{
	setlinecolor(BLACK);	//	������ı�Ե����ɫ��Ϊ��ɫ
	//for(int i=3; i > 0; i--)
	//	time_2(i, ti);
	time_2(3, ti);

	//	Ϊ�˲�ʱ�̸��¡�ʱ���͡��֡�����Լ���ģ����Ч��
	if (ti.wMinute != oldMinute)
		time_2(2, ti);
	if (ti.wHour != oldHour)
		time_2(1, ti);
}

//	ʱ���֧��Ŀ�ģ�Ϊ��ʹ��ʱ���롱����ͬһ���������ٴ������࣬��Լ�ռ�
void time_2(int num, SYSTEMTIME ti)
{
	int j = 0;
	for(int i=0; i<6; i++)	//	��������0, Ŀ�ģ�Ϊ��ʹ֮�����fun()����ʱ�����ᵼ���ظ�ʹ�������д洢��ֵ����ɡ��������󡱣���Ӱ��֣�ʱ����Ӱ��ʱ��
		arry[i] = 0;

	switch(num)	//	ѡ��ʱ��ģʽΪ��ʱ/��/��
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
	for (j=6; j > 0; j--)	//	��Ļ��ʾ������ʱ�䣨�÷�����ɫ��ʾ��
	{
		if(arry[6-j] == 1)	//	��������ֵΪ1����Ϊ��ɫ������Ϊ��ɫ
		{
			setfillcolor(WHITE);	// ���ɫΪ����ɫ����ʾ��ʱ��ʱ��
			//solidrectangle(100*(j-1), 200, 100*j,300);
			fillrectangle(100*(j-1), (num-1)*100, 100*j, num*100);   
        }else
        {
			setfillcolor(BLACK);    // ���ɫΪ����ɫ����ʾ��ʱ��ʱ��
            solidrectangle(100*(j-1), (num-1)*100, 100*j, num*100);
        }		
    }

}

/************************************************
*												*
*				�����ߣ�keri					*
*			����޸�ʱ�䣺2020/2/21				*
*				��Ȩ����Դ						*
*												*
************************************************/
