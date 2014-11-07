#include "main.h"
extern int Ticker;
int main(void)
{
	char str[100] = {0};

    while(1)
    {
    	while(Ticker > 100){
    		transmit_uart1_s(str);
    	}
    }
}
