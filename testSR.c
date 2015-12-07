#include <stdio.h>
#include "./ntp-server.h"
#include <string.h>
/**************************************
对ntp数据报的格式进行发收测试
**************************************/
int main(int argc, char const *argv[])
{
	if(argc < 2){
		printf("less para\n");
		return 0;
	}else if(!strcmp(argv[1],"send")){
		startBroadCast();
	}else if(!strcmp(argv[1],"recieve")){
		startBroadCastRV();
	}
	return 0;
}