#include "Driver.h"

UniversalSerialBus UsB;


void USB_RxIT(uint8_t* Buf, uint8_t Len)
{
	Sys.USB_Inc = 0;

	for(char i=0; i<Len; i++)
		{
			UsB.Rx_Buf[UsB.Rx_Len] = (uint8_t)(*(Buf+i));
			UsB.Rx_Len += 1;
		}
}


void USB_Tx_while()
{
	UsB.Tx_While_Inc +=1;

	if(UsB.Tx_While_Inc % 2)
		{
			memset(UsB.Tx_Buf, 0x00, sizeof(UsB.Tx_Buf));
			UsB.Tx_Len = sprintf((char *)UsB.Tx_Buf, "\n\rTime: %s \n\r",Cmn.Time);
			CDC_Transmit_FS((uint8_t*)UsB.Tx_Buf, UsB.Tx_Len);
		}
	else
		{
			memset(UsB.Tx_Buf, 0x00, sizeof(UsB.Tx_Buf));
			UsB.Tx_Len = sprintf((char *)UsB.Tx_Buf, "Relay1: On_Off -> %s \n\r",EE.Rly_R1);
			CDC_Transmit_FS((uint8_t*)UsB.Tx_Buf, UsB.Tx_Len);

			memset(UsB.Tx_Buf, 0x00, sizeof(UsB.Tx_Buf));
			UsB.Tx_Len = sprintf((char *)UsB.Tx_Buf, "Relay2: On_Off -> %s \n\r",EE.Rly_R2);
			CDC_Transmit_FS((uint8_t*)UsB.Tx_Buf, UsB.Tx_Len);
		}
}


void USB_Rx2Tx_Instant()
{
	if((Sys.USB_Inc > 10) && (UsB.Rx_Len > 0))
		{
			memset(UsB.Tx_Buf, 0x00, sizeof(UsB.Tx_Buf));
			UsB.Tx_Len = sprintf((char *)UsB.Tx_Buf, "USB_Tx: %s \n\r",UsB.Rx_Buf);
			CDC_Transmit_FS((uint8_t*)UsB.Tx_Buf, UsB.Tx_Len);

			if(USB_SetTime())
				CDC_Transmit_FS((uint8_t*)"USB_SetTime_Success \n\r\n\r", 24);
			else if(USB_Relay1_SetTime())
				CDC_Transmit_FS((uint8_t*)"USB_Relay1_SetTime_Success \n\r\n\r", 31);
			else if(USB_Relay2_SetTime())
				CDC_Transmit_FS((uint8_t*)"USB_Relay2_SetTime_Success \n\r\n\r", 31);
			else
				CDC_Transmit_FS((uint8_t*)"\n\r**** ReSet_Again ****\n\r\n\r", 33);

			memset(UsB.Rx_Buf, 0x00, sizeof(UsB.Rx_Buf));
			UsB.Rx_Len = 0;
		}
}


/****************************************************************************************/


uint8_t USB_SetTime()
{
	//SetTime= 07:20:00 Sat 28:06:25 	// Sun Mon Tue Wed Thu Fri Sat
	uint8_t Hr , Min , Sec , Week , Date , Month , Year , Status;
	char *Ptr = strstr((char *)UsB.Rx_Buf,"SetTime= ");

	if((*(Ptr+7) == '=') && (*(Ptr+27) == ':'))
		{
			Status	= 1;
			memset(Cmn.Test, 0x00, sizeof(Cmn.Test));

			for(uint8_t i=0; i<30; i++)
				Cmn.Test[i] = *(Ptr+i);

			Hr 		= (((*(Ptr+9)-0x30)*10) 	+ (*(Ptr+10)-0x30));
			Min 	= (((*(Ptr+12)-0x30)*10) 	+ (*(Ptr+13)-0x30));
			Sec 	= (((*(Ptr+15)-0x30)*10) 	+ (*(Ptr+16)-0x30));

			Date 	= (((*(Ptr+22)-0x30)*10) 	+ (*(Ptr+23)-0x30));
			Month 	= (((*(Ptr+25)-0x30)*10) 	+ (*(Ptr+26)-0x30));
			Year 	= (((*(Ptr+28)-0x30)*10) 	+ (*(Ptr+29)-0x30));

			if((*(Ptr+18) == 'S') && (*(Ptr+19) == 'u'))
				Week = Sunday;
			else if((*(Ptr+18) == 'M') && (*(Ptr+19) == 'o'))
				Week = Monday;
			else if((*(Ptr+18) == 'T') && (*(Ptr+19) == 'u'))
				Week = Tuesday;
			else if((*(Ptr+18) == 'W') && (*(Ptr+19) == 'e'))
				Week = Wednesday;
			else if((*(Ptr+18) == 'T') && (*(Ptr+19) == 'h'))
				Week = Thursday;
			else if((*(Ptr+18) == 'F') && (*(Ptr+19) == 'r'))
				Week = Friday;
			else if((*(Ptr+18) == 'S') && (*(Ptr+19) == 'a'))
				Week = Saturday;
			else
				Status = 0;

			if(Status)
				Set_Time(Sec, Min, Hr, Week, Date, Month, Year);
			else
				Hr = Min = Sec = Week = Date = Month = Year = Status = 0;
		}
	return Status;
}


uint8_t USB_Relay1_SetTime()
{
	//Relay1= On 18:00 Off 22:00
	char *Ptr = strstr((char *)UsB.Rx_Buf,"Relay1= ");

	if((*(Ptr+5) == '1') && (*(Ptr+6) == '=') && (*(Ptr+23) == ':'))
		{
			memset(Cmn.Test, 0x00, sizeof(Cmn.Test));
			for(uint8_t i=0; i<26; i++)
				Cmn.Test[i] = *(Ptr+i);

			EE_Write_Relay_Time(1, Cmn.Test);
			return 1;
		}

	return 0;
}


uint8_t USB_Relay2_SetTime()
{
	//Relay2= On 19:00 Off 21:00
	char *Ptr = strstr((char *)UsB.Rx_Buf,"Relay2= ");

	if((*(Ptr+5) == '2') && (*(Ptr+6) == '=') && (*(Ptr+23) == ':'))
		{
			memset(Cmn.Test, 0x00, sizeof(Cmn.Test));
			for(uint8_t i=0; i<26; i++)
				Cmn.Test[i] = *(Ptr+i);

			EE_Write_Relay_Time(2, Cmn.Test);
			return 1;
		}

	return 0;
}
