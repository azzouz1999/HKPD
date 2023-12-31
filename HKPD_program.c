/************************************/
/* Author		: Ali Azzouz		*/
/* SWC			: HKPD				*/
/* Layer		: HAL			    */
/* Version		: 1.0				*/
/* Date			: December 16,2023	*/
/* Last Edit	: N/A			 	*/
/************************************/
#include "LBIT_math.h"
#include "LSTD_types.h"

#include "MDIO_interface.h"
#include "HKPD_interface.h"
#include "HKPD_config.h"
#include "HKPD_private.h"

char HKPD_charGetKey(void)
{
	u8 L_u8Row,L_u8Col;
	MDIO_voidSetPortDirection(HKPD_PORT,0xf0);
	MDIO_voidSetPortValue(HKPD_PORT, 0x0F);
	do
	{
		L_u8Row=MDIO_u8GetPortValue(HKPD_PORT);
	}while(0x0f==L_u8Row);
	MDIO_voidSetPortDirection(HKPD_PORT,0x0f);
	MDIO_voidSetPortValue(HKPD_PORT, 0xF0);
	L_u8Col=MDIO_u8GetPortValue(HKPD_PORT);
	L_u8Col=((~L_u8Col)&0xf0)>>4;  //shift from 11110000 to 00001111 to view no as 1,2,3,4 not magical numbers
	L_u8Row=(~L_u8Row)&0x0f;      //to view no as 1,2,3,4 not magical numbers

	switch(L_u8Col)
	{
	case 1: L_u8Col=0;break;
	case 2: L_u8Col=1;break;
	case 4: L_u8Col=2;break;
	case 8: L_u8Col=3;break;
	default: L_u8Col=4;break;

	}
	switch(L_u8Row)
	{
	case 1: L_u8Row=0;break;
	case 2: L_u8Row=1;break;
	case 4: L_u8Row=2;break;
	case 8: L_u8Row=3;break;
	default: L_u8Row=4;break;
	}
	return KPD_charmap[L_u8Row][L_u8Col];

}