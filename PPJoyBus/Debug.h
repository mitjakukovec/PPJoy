/***************************************************************************
 *   PPJoy Virtual Joystick for Microsoft Windows                          *
 *   Copyright (C) 2011 Deon van der Westhuysen                            *
 *                                                                         *
 *   This program is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 *                                                                         *
 ***************************************************************************/


/***************************************************************************/
/**                                                                       **/
/**  Parallel port joystick bus driver, (C) Deon van der Westhuysen 2002  **/
/**                                                                       **/
/**  Debug.h    Debug support routines for the Parallel Port Joystick     **/
/**             Bus driver.                                               **/
/**                                                                       **/
/**                                                                       **/
/**                                                                       **/
/**  Portions of this file derived from the Windows 2000 DDK              **/
/**                                                                       **/
/***************************************************************************/



/**************************************************************************/
/* #defines                                                               */
/**************************************************************************/

/* Define constants to indicate catagories for Debug output */
#define FILE_PPJOYBUS				0x00010000
#define FILE_PNP					0x00020000
#define FILE_POWER					0x00040000
#define FILE_IOCTL					0x00080000
#define FILE_PARPORTS				0x00100000
#define FILE_IRPUTIL				0x00200000
#define FILE_EVENTLOG				0x00400000


#define PPJOY_ERROR					0x00000001
#define PPJOY_WARN					0x00000002
#define PPJOY_BABBLE				0x00000004
#define PPJOY_BABBLE2				0x00000008
#define PPJOY_FENTRY				0x00000010
#define PPJOY_FEXIT					0x00000020
#define PPJOY_FEXIT_STATUSOK		0x00001000


/* Define the default debug level */
//#define PPJOY_DEFAULT_DEBUGLEVEL	0x00000003
#define PPJOY_DEFAULT_DEBUGLEVEL	0xFFFFFFFF
//#define PPJOY_DEFAULT_DEBUGLEVEL	FILE_PPJOYBUS|FILE_PNP|FILE_POWER|FILE_IOCTL|FILE_PARPORTS
//#define PPJOY_DEFAULT_DEBUGLEVEL	FILE_POWER


/* Pool tag (identifier) for the memory allocated by us */
#define PPJOYBUS_POOL_TAG			('BJPP')



/**************************************************************************/
/* Macros for including debugging info in debug builds                    */
/**************************************************************************/

/* Make sure that the symbol DBG is both defined and not zero */
#ifdef DBG
#if DBG
#define TRAP()  DbgBreakPoint()
#endif
#endif

#ifdef TRAP


extern ULONG PPJoyBus_DebugLevel;

#define PPJOY_DBGPRINT(_debugMask_,_x_)							\
			if ( (_debugMask_)&PPJoyBus_DebugLevel )			\
			{													\
			 DbgPrint(BUS_DRIVER_FILENAME ": ");				\
             DbgPrint _x_ ; /* Brackets are included in _x_	*/	\
             DbgPrint("\n");									\
			}
#define PPJOY_EXITPROC(_debugMask_,_x_,ntStatus)												\
			if ( ((_debugMask_)&PPJOY_FEXIT_STATUSOK) && !NT_SUCCESS(ntStatus) )				\
			{																					\
			 PPJOY_DBGPRINT ( (_debugMask_|PPJOY_ERROR),(_x_ "  ntStatus(0x%x)",ntStatus) );	\
			}																					\
			else																				\
			{																					\
			 PPJOY_DBGPRINT((_debugMask_), (_x_ " ntStatus(0x%x)", ntStatus));					\
			}
#define ExAllocPool(Type,Size)		ExAllocatePoolWithTag (Type,Size,PPJOY_POOL_TAG)

#else

/* We are building a free build. Use dummy macros to filter out debug info */
#define PPJOY_DBGPRINT(_x_,_y_)
#define PPJOY_EXITPROC(_x_,_y_,_z_)
#define TRAP()
#define ExAllocPool(Type,Size)		ExAllocatePool( Type, Size )

#endif
