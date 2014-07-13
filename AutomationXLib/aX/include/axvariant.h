/********************************************************************************/
/* MODUL axsapi32.dll															*/
/*			   FILE: axvariant.h												*/
/*           SYSTEM: NT4.0 / 2000 / LINUX								    	*/
/*        COMPONENT: Developer API to the automationX realtime Database     	*/
/*          COMPANY: AutomationX												*/
/*   IMPLEMENTATION: axsapi32.dll, axsapi32.lib, axsapi32.so axsapi32.a			*/
/*                       														*/
/* DATE OF CREATION: 18 JAN 2002 VERSION: 1.00									*/
/*                       														*/
/********************************************************************************/
/*                       														*/
/*  NOTE:                     													*/
/*                       														*/
/*      use the (aXHome)/lib/axsapi.lib in Your Project Settings.			    */
/*      The axsapi32.dll is compiled    with a 4 byte alignment.				*/
/*                       														*/
/*		DO NOT INCLUDE THIS FILE DIRECTLY !!!									*/
/*		include axsapi32.h in your application.									*/
/*                       														*/
/********************************************************************************/

//AutomationX - Types
//VARIANT


#ifndef _AX_VARIANT_H_
#define _AX_VARIANT_H_

#ifdef __cplusplus
extern "C" {
#endif

#define AX_VER_46ML	1


#define		AX_TREE					void*
#define		AX_INSTANCE				void*
#define     AX_PROGRAM              void*
#define		AX_EXEC_DATA			void*
#define		AX_VAR_DSC				void*
#define		AX_ENUM_DSC				void*
#define		AX_ALARM_BIT_ELM		void*


#define AX_BT_EMPTY		0
#define AX_BT_NULL		1
#define	AX_BT_BOOL		2
#define AX_BT_BYTE		3
#define AX_BT_SINT		4
#define AX_BT_USINT		5
#define AX_BT_INT		6
#define AX_BT_UINT		7
#define AX_BT_DINT		8
#define AX_BT_UDINT		9
#define AX_BT_REAL		10	
#define AX_BT_POINTER	11
#define AX_BT_LREAL		12
#define AX_BT_STRING	13
#define AX_BT_DATE		14
#define AX_BT_TIME		15
#define AX_BT_TIMESTAMP	16
#define AX_BT_IMAGE		17
#define AX_BT_ALARM		18
#define AX_VARIANT_REF	0x80

typedef struct tagAxVariant	AxVariant;
typedef struct tagAxVariant AXVARIANT;


typedef struct charArray_
{
	unsigned long  m_size;
	unsigned char* m_img;
} CharArray;

typedef struct tagAxVariant
{
	unsigned char ucVarType;
	unsigned char pad1[3];
	union
	{
		char				btBOOL;
		char*				pbtBOOL;
		unsigned char		btBYTE;
		unsigned char*		pbtBYTE;
		char				btSINT;
		char*				pbtSINT;
		unsigned char		btUSINT;
		unsigned char*		pbtUSINT;
		short int			btINT;
		short int*			pbtINT;
		unsigned short int	btUINT;
		unsigned short int* pbtUINT;
		long				btDINT;
		long*				pbtDINT;
		unsigned long		btUDINT;
		unsigned long*		pbtUDINT;
		float				btREAL;
		float*				pbtREAL;
		void*				btPOINTER;
		void**				pbtPOINTER;
		double				btLREAL;
		double*				pbtLREAL;
		char				btSTRING[1024];
		char*				pbtSTRING;
		CharArray			btIMAGE;
	}AXVAL;
	unsigned char  pad2[2];
}tagAXVARIANT;	

// Historical Data

typedef struct 
{
	double		dTime;	 // Unix Time in sec. since 1.1. 1970
	double		dValue;  // Value
	int			iValid;  // Valid
} AXHistData;

typedef struct 
{
	char		pszDimension[256];
	float		fValue_min;
	float		fValue_max;
	float		fCalibration_lower;
	float		fCalibration_upper;
	float		fVariation;
	double		dKeeping_time;
  	double  	dScantime;
	int			iRecording_mode;
} AXHistDataInfo;

#define RECORDING_MODE_OFF			(0)
#define RECORDING_MODE_SAMPLING		(1)
#define RECORDING_MODE_RAILCAR		(2)
#define RECORDING_MODE_FAST			(3)
#define RECORDING_MODE_CONDITIONAL	(4)

#define PHP_LOG_MSG_RINGBUFFER_SIZE		1000 
#define PHP_LOG_QUEUE_NAME				"$$_ext_log_queue" 

#define EXT_LOG_MAX_AREA_LENGTH			50
#define EXT_LOG_MAX_POS_LENGTH			60
#define EXT_LOG_MAX_MSG_LENGTH			120
#define EXT_LOG_MAX_USER_LENGTH			20
#define EXT_LOG_MAX_DISPLAY_LENGTH		20
#define EXT_LOG_MAX_VALUE_LENGTH		20


typedef struct {
	double		time;
	char		area[EXT_LOG_MAX_AREA_LENGTH];
	char		pos[EXT_LOG_MAX_POS_LENGTH];
	char		msg[EXT_LOG_MAX_MSG_LENGTH];
	char		user[EXT_LOG_MAX_USER_LENGTH];
	char		host[EXT_LOG_MAX_DISPLAY_LENGTH];
	char		value[EXT_LOG_MAX_VALUE_LENGTH];
	int			id;									// alarm priority
}AXEXT_LogStruct, *AXEXT_LogStructPt;

typedef struct {
	int				last_entry;
	int				actual_entry;
	AXEXT_LogStruct	msg[PHP_LOG_MSG_RINGBUFFER_SIZE];
}AXEXT_LogMsgQueue,	*AXEXT_LogMsgQueuePt;

/* important : please keep this struct consistent with AxVarFlags struct in axsapiRemote.h 
	and with ns__Flags struct in axsapiws.h   !!!!
*/
typedef struct {
	unsigned char	basetype;
	unsigned char	force_flag;
	unsigned char	io_flag; 
	unsigned char	subrange; 
	unsigned short	dec_points; 
	unsigned short	seg_size;
	unsigned int	enum_type; 
	unsigned int	param;
} FLAGS, AX_FLAGS;

typedef	struct{
	int		Prio;
	int		Locked;
	int		Ack;
	int		BeepOn;
	int		JournalOn;
	int		AckNecessary;
	char	AlarmText[52];
} ALARMS, AX_ALARMS;


typedef struct 
{
	unsigned char nc;	// NC 0/1
/*	// NC: 0 --> not IO var
	//	   1 --> IO var & NC=0
	//	   2 --> IO var & NC=1
*/
	unsigned char dec_point;
	unsigned char rem;	// 0 --> no GLOBAL var
						// 1 --> GLOBAL var & remark = 0
						// 2 --> GLOBAL var & remark!= 0
	unsigned char trend;// [0,1]
	double minr, maxr;
	char* dim, *remark;
} AX_ATTR;


typedef struct {
	AX_INSTANCE		instance;
	char			treeName[128];
	char			instancePath[512];
} AxSubInstanceList_Struct, *AxSubInstanceList_StructPt;


typedef struct
{
	char		relPathName[0x100];
	long		offset;
	int			direction;
	int			item_length;
	int			items;
	unsigned char *data;	
} AxWsTrendRecord;

typedef struct
{
	AxWsTrendRecord * ptr;
	int size;
} AxWsTrendRecordArray, *AxWsTrendRecordArrayPt;


typedef struct
{
	int			iExists;
	int			iSize;
	int			iMTime;
	int			iATime;
}AxFileInfo ;

#define EXT_MAX_FNAME_LEN		255

typedef struct 
{
	char	szFname[EXT_MAX_FNAME_LEN+1];
	long	tTime;
	int		iSize;
}AxWsDirRecord, *AxWsDirRecordPt;

typedef struct
{
	AxWsDirRecord * ptr;
	int size;
} AxWsDirRecordArray, *AxWsDirRecordArrayPt;

#if !defined(AX_TREND_DATA)
#define AX_TREND_DATA

typedef struct{
  	double  	dTime;
  	double  	dValue;
  	char		cValid;
} AXTrendData;

typedef struct 
{
	char		pszName[255];
	char		pszDimension[255];
	float		fValue_min;
	float		fValue_max;
	float		fCal_lower;
	float		fCal_upper;
	float		fVariation;
  	float		fConsumption;
	int         iRecType;
	
} AXTrendVarInfo;

typedef struct AXTreeData
{
	char* name;
	char* remark;
	double execTime;	// ms
	double peakTime;	// ms
	unsigned modified;	// seconds since begin of 1970
	double licPoints;
	void* res1;
} AXTreeData;


#endif

// Internal Declarations - END
// *************************************************************************************
// *************************************************************************************
#ifdef __cplusplus
}
#endif

#endif
