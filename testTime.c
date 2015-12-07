#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include "./ntp-server.h"
int main(){
	/*struct timeval start,end;
	gettimeofday(&start,NULL);
	sleep(3);
	gettimeofday(&end,NULL);
	int timeuse = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("time:%d us\n",timeuse );
	int sz = sizeof(end.tv_sec);
	char sec[sz]; 
	printf("sz = %d \n", sz);
	memcpy(sec,&end.tv_sec,sizeof(end.tv_sec));

	printf("char sec :%x tv_sec : %x\n",sec,end.tv_sec );

	memcpy(&end.tv_sec,sec,sizeof(end.tv_sec));

	printf("char sec :%x tv_sec : %x\n",sec,end.tv_sec );
	long int x = end.tv_sec;
	printf("end.tv_sec%x\n",x);*/
	
	/***************************************************************
	对精确时间拷贝做测试，满足64位机和32位机
	char nowtime[100];
	char sec[100];
	char usec[100];
	
	getLocalTime(nowtime);
	printf("-------------------------\n");
	printf("nowtime = %x\n",nowtime );
	memcpy(sec,nowtime,4);
	memcpy(usec,&nowtime[4],4);
	printf("sec = %x size = %d \n",sec,sizeof(sec) );
	printf("usec = %x size = %d \n",usec,sizeof(usec) );
	int intSec;
	int intUsec;
	memcpy(&intSec,sec,sizeof(intSec));
	memcpy(&intUsec,usec,sizeof(intUsec));
	printf("intSec = %x size = %d intUsec = %x size = %d \n",intSec,sizeof(intSec),intUsec,sizeof(intUsec) );
	*************************************************************/
	/*****************************************************************
	测试setBit----------------
	unsigned char b;
	unsigned char LI = 1;
	unsigned char VN = 3;
	unsigned char Mode = 3;
	unsigned char dest[4];
	memset(dest,0,4);
	setBit(LI,dest,0,1);
	setBit(VN,dest,1,4);
	setBit(Mode,dest,5,3);
	printf("dest = %x\n",dest[0] );
	while(dest[0]){
		printf("%x", dest[0] & 1);
		dest[0] >>= 1;
	}
	printf("\n");
	/*********************************************************************/
	NtpData data;
	memset(data.Head,0,4);
	initHead(&data);
	printf("data -> Head = %x\n",data.Head[0] );
	printf("data -> Head = %x\n",data.Head[1] );
	printf("data -> Head = %x\n",data.Head[2] );
	printf("data -> Head = %x\n",data.Head[3] );
	return 0;
}