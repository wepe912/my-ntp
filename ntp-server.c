#include <sys/types.h>

#include <sys/socket.h>

#include <netinet/in.h>

#include <arpa/inet.h>

#include <unistd.h>

#include <stdio.h>

#include <errno.h>

#include <string.h>
#include <sys/time.h>
#include "ntp-server.h"





#define PORT 8888

int setBit(unsigned char value ,unsigned char* dest,int bitlocat,int bitsize  ){
    int n = bitlocat + bitsize;
    if(n <= 8){
        value <<= (8 - n);
        (*dest) |= value;
        return 0;
    }else{
        return -1;
    }
}


int initHead( NtpData* ntpdata){
    unsigned char LI = 1;
    unsigned char VN = 3;
    unsigned char Mode = 3;
    unsigned char Stratum = 5;
    unsigned char Poll = 12;
    unsigned char Precision = 32;
    if(!setBit(LI,ntpdata->Head,0,2) && !setBit(VN,ntpdata->Head,2,3) &&
       !setBit(Mode,ntpdata->Head,5,3)  && !setBit(Stratum,ntpdata->Head + 1,0,8)  && 
       !setBit(Poll,ntpdata->Head + 2,0,8) && !setBit(Precision,ntpdata->Head + 3,0,8) )
    {
        return 0;
    }else{
        return -1;
    }
}

int setLocalTiem(const char* localT){

}

int getLocalTime(char* localT){
   
    struct timeval now;
    if(gettimeofday(&now,NULL) != 0){
        return -1;
    }
    int secSize = sizeof(now.tv_sec);
   
    if(memcpy(localT,&now.tv_sec,4/*secSize*/) == NULL ||
    memcpy(localT + 4,&now.tv_usec,4/*sizeof(now.tv_usec)*/ ) == NULL){

        memset(localT,0,8);
    return -1;
    }else{
        /******************************
        >>just test!
        int sec;
        int usec;
        memcpy(&sec,&now.tv_sec,4);
        memcpy(&usec,&now.tv_usec,4);
        printf("sec4 == %x usec4 == %x \n",sec,usec );
        printf("now.tv_sec == %x  now.tv_usec == %x \n",now.tv_sec,now.tv_usec);
        *****************************/
        return 0;
    }
   
}

int startBroadCast(){

	setvbuf(stdout,NULL,_IONBF,0);

	fflush(stdout);

	int sock = -1;

	

	if((sock = socket(AF_INET,SOCK_DGRAM,0)) == -1){

		printf("socket errno\n");

		

		return -1;

	}



	const int opt = 1;

	 int nb = 0;

	//设置该socket为广播类型

	nb = setsockopt(sock,SOL_SOCKET,SO_BROADCAST,(char *)&opt,sizeof(opt));

	if(nb == -1){

		printf("set socket be BroadCast faild\n");

	

		return -1;

	}



	struct sockaddr_in addrto;

	bzero(&addrto,sizeof(struct sockaddr_in));

	addrto.sin_family = AF_INET;

	addrto.sin_addr.s_addr = htonl(INADDR_BROADCAST);

	addrto.sin_port = htons(PORT);

	int nlen = sizeof(addrto);



	while(1){

		sleep(1);

		char smsg[12] ; //change
        NtpData ntpdata;
        memset(&ntpdata,0,sizeof(NtpData));
        initHead(&ntpdata);
        getLocalTime(ntpdata.OriginateTS);

		int ret = sendto(sock,&ntpdata,sizeof(NtpData),0,(struct sockaddr*)&addrto,nlen);
        addrto.sin_addr.s_addr = htonl("192.168.0.234");//change
        //ret=recvfrom(sock, smsg, sizeof(smsg), 0, (struct sockaddr*)&addrto,(socklen_t*)&nlen);//change
        ret=recvfrom(sock, &ntpdata, sizeof(ntpdata), 0, (struct sockaddr*)&addrto,(socklen_t*)&nlen);
		if(ret < 0){

			printf("send message faild\n");

			

		}else{

			printf("send message success!\n");
           // printf("ntpdata = %x\n",ntpdata.Head[0] );
            printf("ntpdata.OriginateTS = %x\n",ntpdata.OriginateTS[0]);
            printf("ntpdata.ReceiveTS= %x\n",ntpdata.ReceiveTS[0] );
            printf("ntpdata.TransmitTs= %x\n",ntpdata.TransmitTs[0] );

			

		}

	}

}

void startBroadCastRV(){

	setvbuf(stdout, NULL, _IONBF, 0);   

    fflush(stdout);   

  

    // 绑定地址  

    struct sockaddr_in addrto;  

    bzero(&addrto, sizeof(struct sockaddr_in));  

    addrto.sin_family = AF_INET;  

    addrto.sin_addr.s_addr = htonl(INADDR_ANY);  

    addrto.sin_port = htons(PORT);  

      

    // 广播地址  

    struct sockaddr_in from;  

    bzero(&from, sizeof(struct sockaddr_in));  

    from.sin_family = AF_INET;  

    from.sin_addr.s_addr = htonl(INADDR_ANY);  

    from.sin_port = htons(PORT);  

      

    int sock = -1;  

    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)   

    {     

        printf("can not create recieve sock\n"); 

        

        return -1;  

    }     

  

    const int opt = 1;  

    //设置该套接字为广播类型，  

    int nb = 0;  

    nb = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char *)&opt, sizeof(opt));  

    if(nb == -1)  

    {  

        printf("set socket error...\n");  

       

        return -1;  

    }  

  

    if(bind(sock,(struct sockaddr *)&(addrto), sizeof(struct sockaddr_in)) == -1)   

    {     

        printf("bind error...\n");  

       

        return -1;  

    }  

  

    int len = sizeof(struct sockaddr_in);  

    char smsg[100] = {0}; 
    NtpData ntpdata;
    memset(&ntpdata,0,sizeof(ntpdata)); 

  

    while(1)  

    {  

        //从广播地址接受消息  
        int ret=recvfrom(sock, &ntpdata, sizeof(ntpdata), 0, (struct sockaddr*)&from,(socklen_t*)&len); 
        /**************************************************
         * @Description: get the time recieve the client 
         *                  request
         * @Author:      Knight
         * @DateTime:    2015-12-11 16:48:11
        **************************************************/
        getLocalTime(ntpdata.ReceiveTS);
        if(ret<=0)  

        {  

            printf("read error....\n");  
            return -1;

        } 
        /**************************************************
           * @Description: add --- send to client
           * @Author:      Knight
           * @DateTime:    2015-12-11 16:46:38
          **************************************************/ 
         getLocalTime(ntpdata.TransmitTs);
       // ret = sendto(sock,"copy it ",8,0,(struct sockaddr*)&from,len);
        ret = sendto(sock,&ntpdata,sizeof(NtpData),0,(struct sockaddr*)&from,len);
        if(ret<=0)  

        {  

            printf("read error....\n");  

        }  

        else  

        {         

            printf("send message success!\n");
           // printf("ntpdata = %x\n",ntpdata.Head[0] );
            printf("ntpdata.OriginateTS = %x\n",ntpdata.OriginateTS[0]);
            printf("ntpdata.ReceiveTS= %x\n",ntpdata.ReceiveTS[0] );
            printf("ntpdata.TransmitTs= %x\n",ntpdata.TransmitTs[0] );

        }  

  

        sleep(1);  

    }  

}