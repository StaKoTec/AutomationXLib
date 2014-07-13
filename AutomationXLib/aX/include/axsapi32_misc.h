/********************************************************************************/
/* MODUL axsapi32.dll															*/
/*			   FILE: axsapi32_misc.h											*/
/*           SYSTEM: NT4.0 / 2000 / Linux								    	*/
/*        COMPONENT: Developer API to the automationX realtime Database     	*/
/*          COMPANY: AutomationX												*/
/*   IMPLEMENTATION: axsapi32.dll, axsapi32.lib, axsapi32.so axsapi32.a			*/
/*                       														*/
/* DATE OF CREATION: 22 AUG 2003 VERSION: 1.00									*/
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
 
#ifndef _AXS_API_32_MISC_H_
#define _AXS_API_32_MISC_H_


/********************************************************************************************/
/************************************ Messaging Functions ***********************************/
/********************************************************************************************/


/********************************************************************************************/
/*	AxLog																					*/
/*		This function writes a message into the automationX journal.						*/
/*																							*/
/* Parameters:																				*/
/*		pszPosition		The text for the "Position" column in the journal window			*/
/*		pszMessage		The text for the "Message" column in the journal window				*/
/*		pszValue		The text for the "Set To:" column in the journal window				*/
/*		pszFileName		The journal file to write the message into.  This can be one of the	*/
/*						pre-defined automationX journal files ("softplc", "system", or		*/
/*						"user") or a file specific to a particular application				*/
/*																							*/
/* Return Value:																			*/
/*		Not used																			*/
/********************************************************************************************/
AX_EXPORT int AxLog(char	*pszPosition,
					char	*pszMessage,
					char	*pszValue,
					char	*pszFname);

/********************************************************************************************/
/*	AxLogTS																					*/
/*		This function writes a message into the automationX journal and assigns it the		*/
/*		specified date/time information.  See the functions AxConvertDateTime_ToValue and	*/
/*		AxConvertValue_ToDateTime for getting the correct time stamp value.					*/
/*																							*/
/* Parameters:																				*/
/*		iPrio			The alarm priority value for the "Prio" column of the journal		*/
/*						window																*/
/*		pszPosition		The text for the "Position" column in the journal window			*/
/*		pszMessage		The text for the "Message" column in the journal window				*/
/*		pszValue		The text for the "Set To:" column in the journal window				*/
/*		pszFileName		The journal file to write the message into.  This can be one of the	*/
/*						pre-defined automationX journal files ("softplc", "system", or		*/
/*						"user") or a file specific to a particular application				*/
/*		dTimeStamp		The date and time information to attach to the journal message		*/
/*																							*/
/* Return Value:																			*/
/*		None																				*/
/********************************************************************************************/
AX_EXPORT void AxLogTS(int		iPrio,
					   char		*pszPosition,
					   char		*pszMessage,
					   char		*pszValue,
					   char		*pszFname,
					   double	dTimeStamp);


/********************************************************************************************/
/*	AxGetExLogMessages																		*/
/*		This gets the message entries from the automationX journal files (System, Soft-PLC,	*/
/*		and User).  Using this, an application could store all the automationX journal		*/
/*		messages into an external database.													*/
/*																							*/
/*		The journal entries are stored in an ring buffer that can manage up to 1000			*/
/*		messages.  The calling application is responsible for getting the messages from the	*/
/*		buffer in a reasonable fashion so that not messages are lost (over-written without	*/
/*		being read).  For most applications, a call to this function every 60 seconds is	*/
/*		sufficient.	See the example below.													*/
/*																							*/
/* NOTE:	To get the journal messages, external logging must be enabled.  To do this,		*/
/*			open the automationX registry and enable journal logging by turning on the		*/
/*			registry key "Parameter -> Journal -> External (System,PLC,User) Logger"		*/
/*																							*/
/* Parameters:																				*/
/*		pLogMsg			The structure to place a journal message into						*/
/*																							*/
/* Return Value:																			*/
/*		0 - The function was unable to access the journal system, or there were no new		*/
/*			journal messages																*/
/*		1 - A new journal message was found.
/********************************************************************************************/
//
// Example:
//		AXEXT_LogStruct	my_log_messages;	
//		while(AxGetExLogMessages(&my_log_messages))
//		{	
//          int iYear,iMonth,iHour,iMinutes,iSeconds,iMSeconds
//			AxConvertValue_ToDateTime(my_log_messages.time,&iYear,&iMonth,&iHour,&iMinutes,&iSeconds,&iMSeconds);
//			printf("Got new message <%s> at %2.2d.%2.2d",my_log_messages.msg,iHour,iMinutes);
//			...
//		}
//		AxSleep(60);
//
AX_EXPORT int AxGetExLogMessages(AXEXT_LogStruct *pLogMsg);


/********************************************************************************************/
/*	AxGetSystemMsg																			*/
/*																							*/
/* Parameters:																				*/
/*																							*/
/* Return Value:																			*/
/********************************************************************************************/
AX_EXPORT int AxGetSystemMsg(int iCntMax, AXEXT_LogStruct *pMsg );

/********************************************************************************************/
/*	AxGetJournalMsg																			*/
/*																							*/
/* Parameters:																				*/
/*																							*/
/* Return Value:																			*/
/********************************************************************************************/
AX_EXPORT int AxGetJournalMsg(int iCntMax, AXEXT_LogStruct *pMsg );
	
/********************************************************************************************/
/*	AxGetUserMsg																			*/
/*																							*/
/* Parameters:																				*/
/*																							*/
/* Return Value:																			*/
/********************************************************************************************/
AX_EXPORT int AxGetUserMsg(int iCntMax, AXEXT_LogStruct *pMsg );

/********************************************************************************************/
/*	AxWsTrendRecordArrayPt																	*/
/*																							*/
/* Parameters:																				*/
/*																							*/
/* Return Value:																			*/
/********************************************************************************************/

AX_EXPORT AxWsTrendRecordArrayPt AxGetRecordsToBeSaved();


/********************************************************************************************/
/*	AxDebug																					*/
/*		This function writes a message into the automationX run-time messages window.  This	*/
/*		window is commonly used to provide a method of debugging a process.					*/
/*																							*/
/* Parameters:																				*/
/*		pszArea			The debug category for the message.  This corresponds to the		*/
/*						entries in the "Debug Symbols" column of the run-time messages		*/
/*						window																*/
/*		pszMessage		The message text to be shown when the debug symbol specified by		*/
/*						pszArea is active													*/
/*																							*/
/* Return Value:																			*/
/*		Not used																			*/
/********************************************************************************************/
AX_EXPORT int AxDebug(char	*pszArea,
					  char	*pszMessage);

AX_EXPORT int AxDebugVarArgs(char *pszArea, const char *pszFormat, ...);


/********************************************************************************************/
/*	AxSendSMTPMail																			*/
/*		This function sends an e-mail message												*/
/*																							*/
/* Parameters:																				*/
/*		pszMailServer	The mail server to send the e-mail message from						*/
/*		pszMailAddress	The destination address to sent the e-mail message to				*/
/*		pszSubject		The subject line text of the e-mail message							*/
/*		pszMessage		The message text of the e-mail message								*/
/*																							*/
/* Return Value:																			*/
/*		0 - The e-mail message was not sent													*/
/*		1 - The e-mail message was sent														*/
/********************************************************************************************/
#if __NUTC__
AX_EXPORT int AxSendSMTPMail(const char	*pszMailServer,
							 const char	*pszMailAddress, 
							 const char	*pszSubject,
							 const char	*pszMessage);
#endif


/********************************************************************************************/
/******************************* Historical Data-Access Functions ***************************/
/********************************************************************************************/


/********************************************************************************************/
/*	AxGetHistoricalData																		*/
/*		This function gets the historical data from the automationX trend system for the	*/
/*		specified varaible.																	*/
/*																							*/
/* Parameters:																				*/
/*		pszName			The variable name to search for in the automationX trend system		*/
/*		pDataList		The data structure to write the trend information into				*/
/*		iCnt			The number of elements to get from the trend system.  This must not	*/
/*						be greater then the number of elements created in pDataList			*/
/*		dStartTime_Sec	The oldest time to get data from (see AxConvertDateTime_ToValue to	*/
/*						derive a correct value for this parameter)							*/
/*		dResolution_Sec	The number of seconds that the retreived trend data should span		*/
/*																							*/
/* Return Value:																			*/
/*		0 - The data could not be retrieved													*/
/*		1 - The trend information was retrieved												*/
/********************************************************************************************/
AX_EXPORT int AxGetHistoricalData(char			*pszName,
								  AXHistData	*pDataList,
								  int			iCnt,
								  double		dStartTime_Sec,
								  double		dResoulution_Sec);


/********************************************************************************************/
/*	AxTrendGetSetRealPts																	*/
/*		This function gets the historical real point data from the automationX trend system */
/*		for the	specified varaible.															*/
/*																							*/
/* Parameters:																				*/
/*		pszName			The variable name to search for in the automationX trend system		*/
/*		pDataList		The data structure to write the trend information into				*/
/*		iCnt			The number of elements to get from the trend system.  This must not	*/
/*						be greater then the number of elements created in pDataList			*/
/*		dStartTime_Sec	The oldest time to get data from (see AxConvertDateTime_ToValue to	*/
/*						derive a correct value for this parameter)							*/
/*		dResolution_Sec	The number of seconds that the retreived trend data should span		*/
/*																							*/
/* Return Value:																			*/
/*		0 - The data could not be retrieved													*/
/*		1 - The trend information was retrieved												*/
/********************************************************************************************/
AX_EXPORT int AxTrendGetSetRealPts(char *pszName, 
								   AXHistData *pDataList,
								   int iCnt, 
								   double dStartTime_Sec, 
								   double dEndTime_Sec);


/********************************************************************************************/
/*	AxGetHistoricalDataInfo																	*/
/*		This function gets the trend configuration information that is defined for the		*/
/*		specified variable in the automationX trend system. (i.e. trend mode, scaling, etc)	*/
/*																							*/
/* Parameters:																				*/
/*		pszName			The variable name to search for in the automationX trend system		*/
/*		pDataInfo		The data structure to write the trend configuration data into		*/
/*																							*/
/* Return Value:																			*/
/*		0 - The data could not be retrieved													*/
/*		1 - The trend configuration data was retrieved										*/
/********************************************************************************************/
AX_EXPORT int AxGetHistoricalDataInfo(char				*pszName,
									  AXHistDataInfo	*pDataInfo);



/********************************************************************************************/
/********************************* Redundancy File Functions ********************************/
/********************************************************************************************/

/********************************************************************************************/
/*	AxCopyFileToRDHost																		*/
/*		This function copies a file from the local computer to the remote computer in a		*/
/*		redundant automationX configuration.  The file name specified must be relative to	*/
/*		the automationX home directory.  i.e. if the file to be copied is:					*/
/*		"C:\automationX\projects\demo\my_file.txt", then the file name passed into the		*/
/*		function must be "projects\demo\my_file.txt".  The file will be place in the same	*/
/*		directory (relative to the automationX home directory) on the remote computer.		*/
/*																							*/
/* NOTE:	automationX must be running on the remote computer for the copy to succeed.		*/
/*																							*/
/* Parameters:																				*/
/*		pszFileName		The file to be copied to the remote computer						*/
/*																							*/
/* Return Value:																			*/
/*		<=0 - The file was not copied														*/
/*		1 - Success																			*/
/********************************************************************************************/
AX_EXPORT int AxCopyFileToRDHost(char *pszFileName);

/********************************************************************************************/
/*	AxDeleteFileRD																			*/
/*		This function deletes a file from the remote computer in a redundant automationX	*/
/*		configuration.  The file name specified must be relative to	the automationX home	*/
/*		directory.  i.e. if the file to be copied is:										*/
/*		"C:\automationX\projects\demo\my_file.txt", then the file name passed into the		*/
/*		function must be "projects\demo\my_file.txt".										*/
/*																							*/
/* NOTE:	automationX must be running on the remote computer for the delete to succeed.	*/
/*																							*/
/* Parameters:																				*/
/*		pszFileName		The file to be deleted from the remote computer						*/
/*																							*/
/* Return Value:																			*/
/*		<=0 - The file was not deleted														*/
/*		1 - Success																			*/
/********************************************************************************************/
AX_EXPORT int AxDeleteFileRD(char *pszFileName);

/********************************************************************************************/
/*	AxAppendFileRD																			*/
/*		This function appends data to a file on the remote computer in a redundant			*/
/*		automationX	configuration.  The file name specified must be relative to	the			*/
/*		automationX home directory.  i.e. if the file to be appended to is:					*/
/*		"C:\automationX\projects\demo\my_file.txt", then the file name passed into the		*/
/*		function must be "projects\demo\my_file.txt".  If the file does not already exist	*/
/*		on the remote computer, it will be created.											*/
/*																							*/
/* NOTE:	automationX must be running on the remote computer for the append to succeed.	*/
/*																							*/
/* Parameters:																				*/
/*		pszFileName		The file to be appended on the remote computer						*/
/*		pszData			The data to be appended to the file									*/
/*		iDataLength		The amount of data (in Bytes) to be appended to the file			*/
/*																							*/
/* Return Value:																			*/
/*		<=0 - The file was not deleted														*/
/*		1 - Success																			*/
/********************************************************************************************/
AX_EXPORT int AxAppendFileRD(char	*pszFileName,
							 char	*pszData,
							 int	iDataLength);



/********************************************************************************************/
/********************************* Enumerator Data Functions ********************************/
/********************************************************************************************/


/********************************************************************************************/
/*	AxGetGlobalEnum																			*/
/*		This function gets the names of the global enumerators configured in the project.	*/
/*		Each enumerator name can be retreived by calling the function repeatedly,			*/
/*		incrementing the iIndex value.  The return value will be an empty string once the	*/
/*		last enumerator has been retrieved.													*/
/*																							*/
/* Parameters:																				*/
/*		iIndex		The index to each global enumerator										*/
/*																							*/
/* Return Value:																			*/
/*		The global enumerator name string													*/
/********************************************************************************************/
AX_EXPORT const char *AxGetGlobalEnum(int iIndex);

/********************************************************************************************/
/*	AxGetEnumDsc																			*/
/*		This function gets enumerator descriptor data for the specified enumerator name.	*/
/*																							*/
/* Parameters:																				*/
/*		pszName		The name of the enumerator to get the enumerator descriptor data for	*/
/*																							*/
/* Return Value:																			*/
/*		0 - The enumerator could not be found												*/
/*		Otherwise the enumerator descriptor data											*/
/********************************************************************************************/
AX_EXPORT AX_ENUM_DSC AxGetEnumDsc(char *pszName);

/********************************************************************************************/
/*	GetNextEnumValue																		*/
/*		This function gets enumerator value data for the specified index position in a		*/
/*		global enumerator.  The recommended method of using this function is to get all		*/
/*		the enumerator values at once. i.e.													*/
/*			iIndex = 0																		*/
/*			while (GetNextEnumValue(pEnumDsc, iIndex, pszValue, iValue) {					*/
/*				.....																		*/
/*			}																				*/
/*		Do not assume that an index value will be valid unless this form is followed.		*/
/*																							*/
/* Parameters:																				*/
/*		pEnumDsc	The enumerator descriptor data of the global enumerator					*/
/*		iIndex		The index inside of the global enumerator to get the values from		*/
/*		pszValue	A variable to place the mnemonic text of the enumerator position		*/
/*		iValue		A variable to place the integer value of the enumerator position		*/
/*																							*/
/* Return Value:																			*/
/*		0 - The enumerator descriptor data was invalid of the last index position has been	*/
/*			reached																			*/
/*		1 - Success																			*/
/********************************************************************************************/
AX_EXPORT int GetNextEnumValue(AX_ENUM_DSC	pEnumDsc,
							   int			iIndex,
							   char			*pszValue,
							   int			*iValue);

/********************************************************************************************/
/*	GetEnumValue																			*/
/*		This function gets enumerator value (integer) data for the specified mnemonic in	*/
/*		the enumerator with the specified name.												*/
/*																							*/
/* Parameters:																				*/
/*		pszEnumName			The name of the enumerator to get the value from				*/
/*		pszEnumValueName	The mnemonic text of the enumerator value to be retreived		*/
/*																							*/
/* Return Value:																			*/
/*		-1 - The enumerator could not be found, or the mnemonic text value for one of its	*/
/*			 values could not be found														*/
/*		Otherwise, the value that the mnemonic represents in the enumerator					*/
/********************************************************************************************/
AX_EXPORT int GetEnumValue(char	*pszEnumName,
						   char	*pszEnumValueName);


/********************************************************************************************/
/********************************* Time Conversion Functions ********************************/
/********************************************************************************************/


/********************************************************************************************/
/*	AxConvertDateTime_ToValue																*/
/*		This function converts date/time values to a double floating point value that can	*/
/*		be used for time-stamping in journal messages, or for specifying the start time		*/
/*		to use when getting historical trend data.  The integer portion of the returned		*/
/*		value is seconds (a unix time value), and the decimal portion of the returned value	*/
/*		is fractions of seconds.  To get the current time, set all the input parameters to	*/
/*		-1.																					*/
/*																							*/
/* Parameters:																				*/
/*		iYear			The year portion of the time value to be created (i.e. 2003)		*/
/*		iMonth			The month portion of the time value to be created (1->12)			*/
/*		iDay			The day portion of the time value to be created (1->28,29,30,31)	*/
/*		iHour			The hour portion of the time value to be created (0-23)				*/
/*		iMinute			The minute portion of the time value to be created (0->59)			*/
/*		iSecond			The second portion of the time value to be created (0->59)			*/
/*		iMillisecond	The millisecond portion of the time value to be created (0->999)	*/
/*																							*/
/* Return Value:																			*/
/*		The double floating point date/time representation									*/
/********************************************************************************************/
#define AxConvertDataTime_ToValue	AxConvertDateTime_ToValue
AX_EXPORT double AxConvertDateTime_ToValue(int	iYear,
										   int	iMonth,
										   int	iDay,
										   int	iHour,
										   int	iMinute,
										   int	iSecond,
										   int	iMillisecond);

/********************************************************************************************/
/*	AxConvertValue_ToDateTime																*/
/*		This function performs the opposite of the AxConvertDateTime_ToValue function.  It	*/
/*		takes a double floating point value representing a specific time, and separates		*/
/*		out its individual components.  This could be used to get meaningful times from		*/
/*		from the data retreived when reading information from the trend system.	 If the		*/
/*		value passed into the function through dValue is invalid, all the date/time			*/
/*		parameters will be set to 0.														*/
/*																							*/
/* Parameters:																				*/
/*		dValue			The value to convert to real date and time information				*/
/*		piYear			The year portion of the value converted (i.e. 2003)					*/
/*		piMonth			The month portion of value converted (1->12)						*/
/*		piDay			The day portion of the value converted (1->28,29,30,31)				*/
/*		piHour			The hour portion of the value converted (0-23)						*/
/*		piMinute		The minute portion of the value converted (0->59)					*/
/*		piSecond		The second portion of the value converted (0->59)					*/
/*		piMillisecond	The millisecond portion of the value converted (0->999)				*/
/*																							*/
/* Return Value:																			*/
/*		None																				*/
/********************************************************************************************/
#define AxConvertValue_ToDataTime	AxConvertValue_ToDateTime
AX_EXPORT void AxConvertValue_ToDateTime(double	dValue,
										 int	*piYear,
										 int	*piMonth,
										 int	*piDay,
										 int	*piHour,
										 int	*piMinute,
										 int	*piSecond,
										 int	*piMillisecond);

/********************************************************************************************/
/*	AxGetActUnixTime																		*/
/*		This function gets the current time (unix time) as a double floating point value.	*/
/*																							*/
/* Parameters:																				*/
/*		None																				*/
/*																							*/
/* Return Value:																			*/
/*		The current time (unix time) as a double floating point value						*/
/********************************************************************************************/
AX_EXPORT double AxGetActUnixTime(void);


/********************************************************************************************/
/*	AxGetActUnixTimeMS																		*/
/*		This function gets the current time (unix time) in seconds as a double floating		*/
/*		point value. In contrast to AxGetActUnixTime this result contains milliseconds too.	*/
/*																							*/
/* Parameters:																				*/
/*		None																				*/
/*																							*/
/* Return Value:																			*/
/*		The current time (unix time) as a double floating point value						*/
/********************************************************************************************/
AX_EXPORT double AxGetActUnixTimeMS(void);


/********************************************************************************************/
/*	AxSetRegistryEnvironmentName															*/
/*		This function sets the Registry Environment name. Call this once to initialize the  */
/*		Registry Envirnoment																*/
/* Parameters:																				*/
/*		pszEnvironmentName: Name of the Registry Environment. Appear in the aXRegister 		*/
/*							Window as a separate Subfolder.									*/
/* Return Value:																			*/
/*		None																				*/
/********************************************************************************************/
AX_EXPORT int AxSetRegistryEnvironmentName(char *pszEnvironmentName);

/********************************************************************************************/
/*	AxSetRegistryEnvironmentName															*/
/*		This function get the access from a certain AccessPath. If the AccessPath doesn't   */
/*		exists's the System will create an entry automatically.	Make sure that the 			*/
/*		Registry Environment is initialized with the function AxSetRegistryEnvironmentName()*/
/* Parameters:																				*/
/*		pszAccessPath: Name of the AccessPath												*/
/*																							*/
/* Return Value:																			*/
/*		Access: True or False 																*/
/********************************************************************************************/
AX_EXPORT int AxGetAccess(char *pszAccessPath);

/********************************************************************************************/
/*	AxRegisterValue																			*/
/*		This function register the AccessPath with the default value.						*/
/*		After registration it can be changed from the User in the aXregistry				*/
/* Parameters:																				*/
/*		pszAccessPath: Name of the AccessPath												*/
/*		pszDefaultValue: default Value														*/
/* Return Value:																			*/
/*		Value: Return Value  																*/
/********************************************************************************************/
AX_EXPORT char *AxRegisterValue(char *pszAccessPath,char *pszDefaultValue);

/********************************************************************************************/
/*	AxGetAccessLevel																		*/
/*		This function get the access level													*/
/* Parameters:																				*/
/*		user : user name																	*/
/*		password : password of user															*/
/*		accessLevel : pointer on required access level										*/
/*																							*/
/* Return Value:																			*/
/*		error		: 0																		*/
/*		success	: 1																			*/
/********************************************************************************************/
AX_EXPORT int AxGetAccessLevel(char *user, char* password, int* accessLevel);


/********************************************************************************************/
/*	AxCrypPassword																			*/
/*		This function crypts the password													*/
/* Parameters:																				*/
/*		password : password of user															*/
/*		crypt : crypted password															*/
/*																							*/
/* Return Value:																			*/
/*		error		: 0																		*/
/*		success	: 1																			*/
/********************************************************************************************/
AX_EXPORT int AxCrypPassword(char *password, char* crypt);
///////////////////////////
AX_EXPORT int AxsapiStoreParameter(char* path,char* inst_name,char* file_name,int append,int max_entries,char* num_array_var);
AX_EXPORT int AxsapiReplaceParameter(char* path,char* inst_name,char* file_name,int pos);
AX_EXPORT int AxsapiReadParameter(char* path,char* inst_name,char* file_name,char* var_val,int whence,char* num_array_var);
AX_EXPORT int AxsapiDeleteParameter(char* path,char* inst_name,char* file_name,char* var_val,int whence,char* num_array_var);

AX_EXPORT char* AxsapiGetLanguageText(char *class_name, char* original_text);
AX_EXPORT char* AxsapiGetLanguageExtension();
AX_EXPORT char* AxsapiRegistryGetValue(char* keyword, char* retbuff, int buffsize);
AX_EXPORT int AxsapiRegistrySetValue(char* keyword, char* buff);

AX_EXPORT int AxMakeDir(char* dirpath);

AX_EXPORT int AxsapiCheckLoginUserPassword(char* username, char* password, int* level);
AX_EXPORT int AxsapiGetAccess(char* item, int  level);

AX_EXPORT int AxsapiCreateUserRemote(char* username, char* password, int level);
AX_EXPORT int AxsapiChangePasswordRemote(char* username, char* password_old, char* password_new, int nocheck);

#endif
