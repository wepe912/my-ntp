/*******************************************************
	>	NtpData为ntp协议的数据报格式
*******************************************************/
typedef struct 
{
	unsigned char Head[4];
	unsigned char RootDelay[4];
	unsigned char RootDispersion[4];
	unsigned char ReferenceIdentifier[4];
	unsigned char ReferenceTS[8];
	unsigned char OriginateTS[8];
	unsigned char ReceiveTS[8];
	unsigned char TransmitTs[8];
	unsigned char Authenticator[96];
	
}NtpData;

/********************************************************
>	功能：设置dest指向的这个字节第bitnum位后开始的bitsize
>		   个位的值为value
>	参数：value-需要设置的值	dest-指向的一个字节
> 		  bitnum-开始的位置      bitsize-总共要改变的位数
>	返回值：-1-失败   0-成功
>	说明：第一次传入dest之前，一定要将dest置0
********************************************************/
int setBit(unsigned char value ,unsigned char* dest,int bitnum,int bitsize  );
/********************************************************
>	功能：设置NtpData结构中的Head
>	参数：ntpdata为输出参数，主要是对Head的设置
>	返回值：0--成功  -1--失败
>	说明：使用时要把ntpdata->Head置零
>
>
>
********************************************************/

int initHead( NtpData* ntpdata);
int startBroadCast();
void startBroadCastRV();
/*****************************************************
	>	功能：得到本地精确时间，精确到us级
	>	参数：localT 为传出参数，返回本地精确时间
	>		  一般情况下前8byte为秒数，后8byte为
	>		  微秒数
	>	返回值：成功为0，失败为-1
	>	说明：已经在64位linux系统下测试过，秒数和微秒
	> 		  数都为8byte,但是报头只有8byte，所以这里是
	>		  将时间的秒数和微秒数分别以4byte拷出，不会
	>		  让精度损失
*****************************************************/
int getLocalTime(char* localT);
/**************************************************
 * @Description: 设置本地时间
 * @param:	localT传入的本地时间，8byte，前4byte为sec
 *			后4byte为usec
 * @return: 0--成功 -1--失败
 **************************************************/
 int setLocalTiem(const char* localT);