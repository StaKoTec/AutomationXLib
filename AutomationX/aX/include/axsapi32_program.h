/********************************************************************************/
/* MODUL axsapi32.dll															*/
/*			   FILE: axsapi32_program.h											*/
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
 
#ifndef _AXS_API_32_PROGRAM_H_
#define _AXS_API_32_PROGRAM_H_

/********************************************************************************************/
/*	AxGetProgram																			*/
/*		This function gets the program description of each of the program (.tree) files in	*/
/*		the project.  It is meant to be run in a loop.  The first time the function is		*/
/*		called, the pPreviousProgram parameter is NULL.  Each successive time the function	*/
/*		is called, the pPreviousProgram parameter is set to the program data value returned	*/
/*		by the previous call.																*/
/*																							*/
/* Parameters:																				*/
/*		pPreviousProgram	Program description data from the previous call to AxGetProgram	*/
/*																							*/
/* Return Value:																			*/
/*		0 - The last program file had been found the previous time the function was called	*/
/*		Otherwise - The program data of the next program after pPreviousProgram				*/
/********************************************************************************************/
AX_EXPORT AX_PROGRAM AxGetProgram(AX_PROGRAM pPreviousProgram);

/********************************************************************************************/
/*	AxGetProgramName																		*/
/*		This function gets the name of a program from its program description data.			*/
/*																							*/
/* Parameters:																				*/
/*		pProgram	Program description data												*/
/*																							*/
/* Return Value:																			*/
/*		0 - The program description data was invalid										*/
/*		Otherwise - The name of the program													*/
/********************************************************************************************/
AX_EXPORT const char *AxGetProgramName(AX_PROGRAM pProgram);

/********************************************************************************************/
/*	AxQueryProgram																			*/
/*		This function finds the program data for a specifed program name.					*/
/*																							*/
/* Parameters:																				*/
/*		pszProgramName	Program name to search for in the project							*/
/*																							*/
/* Return Value:																			*/
/*		0 - The program name could not be found in the project								*/
/*		Otherwise - The program description data for the specified program name				*/
/********************************************************************************************/
AX_EXPORT AX_PROGRAM AxQueryProgram(char *pszProgramName);

/********************************************************************************************/
/*	AxGetInstance																			*/
/*		This function returns the class instance data of an object with the specified		*/
/*		class name.																			*/
/*																							*/
/*		Only one class instance data object is returned from this function. Successive		*/
/*		class objects are found by calling this function using the pPreviousInstance		*/
/*		parameter. Set the pPreviousInstance value to the class instance data returned by	*/
/*		this function the previous time it was called for the specified class name.  The	*/
/*		first time that this function is called for the specified class, the				*/
/*		pPreviousInstance value should be set to NULL.										*/
/*																							*/
/*		NOTE:	AX_INSTANCE and AX_PROGRAM are essentially the same type of data, the only	*/
/*				difference being that AX_PROGRAM stresses that the data represents main		*/
/*				program tree data.															*/
/*																							*/
/* Parameters:																				*/
/*		pPreviousInstance	The class instance data returned the previous time the function	*/
/*							was called														*/
/*		pszClassName		The class name to search for in the project						*/
/*																							*/
/* Return Value:																			*/
/*		0 - No instances of the specified class could be found								*/
/*		Otherwise the instance data of an object of the specified class						*/
/********************************************************************************************/
AX_EXPORT AX_INSTANCE AxGetInstance(AX_INSTANCE pPreviousInstance,
									char		*pszClassName);

/********************************************************************************************/
/*	AxGetInstanceEx																			*/
/*		This function returns the class instance data of an object with the specified		*/
/*		class name. It seaches sub instances too.											*/
/*																							*/
/*		Only one class instance data object is returned from this function. Successive		*/
/*		class objects are found by calling this function using the pPreviousInstance		*/
/*		parameter. Set the pPreviousInstance value to the class instance data returned by	*/
/*		this function the previous time it was called for the specified class name.  The	*/
/*		first time that this function is called for the specified class, the				*/
/*		pPreviousInstance value should be set to NULL.										*/
/*																							*/
/*		NOTE:	AX_INSTANCE and AX_PROGRAM are essentially the same type of data, the only	*/
/*				difference being that AX_PROGRAM stresses that the data represents main		*/
/*				program tree data.															*/
/*																							*/
/* Parameters:																				*/
/*		pPreviousInstance	The class instance data returned the previous time the function	*/
/*							was called														*/
/*		pszClassName		The class name to search for in the project						*/
/*																							*/
/* Return Value:																			*/
/*		0 - No instances of the specified class could be found								*/
/*		Otherwise the instance data of an object of the specified class						*/
/********************************************************************************************/
AX_EXPORT AX_INSTANCE AxGetInstanceEx( AX_INSTANCE previous, char *class_name );

/********************************************************************************************/
/*	AxGetSubInstance																		*/
/*		This function returns the subclass instance data of an object with the specified	*/
/*		class name.																			*/
/*																							*/
/*		Only one subclass instance data object is returned from this function. Successive	*/
/*		subclass objects are found by calling this function using the pPreviousInstance		*/
/*		parameter. Set the pPreviousInstance value to the subclass instance data returned 	*/
/*		by this function the previous time it was called for the specified subclass name.  	*/
/*		The first time that this function is called for the specified subclass, the			*/
/*		pPreviousInstance value should be set to NULL.										*/
/*																							*/
/* Parameters:																				*/
/*		pParentInstance		The class instance of the parent class							*/
/*		pPreviousInstance	The subclass instance data returned the previous time			*/
/*							the function was called											*/
/*		pszClassName		The subclass name to search for in the parent class				*/
/*																							*/
/* Return Value:																			*/
/*		0 - No instances of the specified subclass could be found							*/
/*		Otherwise the instance data of an object of the specified subclass					*/
/********************************************************************************************/
AX_EXPORT AX_INSTANCE AxGetSubInstance(AX_INSTANCE	pParentInstance,
									   AX_INSTANCE	pPreviousInstance,
									   char			*pszClassName);

/********************************************************************************************/
/*	AxGetInstance_N																			*/
/*		This function returns an array of class instances of objects with the specified		*/
/*		class name.																			*/
/*																							*/
/*		The function will fill the class instance array, pInstanceList, up to the list size	*/
/*		specified by uiMaxListSize or until there are no more instances of the specified	*/
/*		class in the project, whichever is smaller.  If there are more class instances in	*/
/*		the project then there are positions in the list, the function can be called		*/
/*		successive times with the last instance object found in the previous call being		*/
/*		used for the pPreviousInstance parameter.  The calling function is responsible for	*/
/*		creating the class instance list.  The first time that this function is called for	*/
/*		the specified class, the pPreviousInstance value should be set to NULL.				*/
/*																							*/
/* Parameters:																				*/
/*		pPreviousInstance	The last class instance data returned the previous time the		*/
/*							function was called												*/
/*		pszClassName		The class name to search for in the project						*/
/*		pInstanceList		A class instance list to write the array of found class objects	*/
/*							to																*/
/*		uiMaxListSize		The maximum number of elements to write into the class instance	*/
/*							list.															*/
/*																							*/
/* Return Value:																			*/
/*		0 - No instances of the specified class could be found								*/
/*		Otherwise the number of class objects that were written into the list				*/
/********************************************************************************************/
AX_EXPORT int AxGetInstance_N(AX_INSTANCE	pPreviousInstance,
							  char			*pszClassName,
							  AX_INSTANCE	pInstanceList[],
							  unsigned int	uiMaxListSize);


/********************************************************************************************/
/*	AxGetInstanceFromProgram																*/
/*		This function behaves identically to the function AxGetInstance, with the exception	*/
/*		that it will only search for objects of the specified class in the specified		*/
/*		program (pProgram).	If pProgram is NULL, the entire project will be searched.		*/
/*																							*/
/*		Only one class instance data object is returned from this function. Successive		*/
/*		class objects are found by calling this function using the pPreviousInstance		*/
/*		parameter. Set the pPreviousInstance value to the class instance data returned by	*/
/*		this function the previous time it was called for the specified class name.  The	*/
/*		first time that this function is called for the specified class, the				*/
/*		pPreviousInstance value should be set to NULL.										*/
/*																							*/
/*		NOTE:	AX_INSTANCE and AX_PROGRAM are essentially the same type of data, the only	*/
/*				difference being that AX_PROGRAM stresses that the data represents main		*/
/*				program tree data. AX_INSTANCE data can be used as the pProgram parameter	*/
/*				to search for classes (sub-classes) within specific class objects			*/
/*																							*/
/* Parameters:																				*/
/*		pPreviousInstance	The class instance data returned the previous time the function	*/
/*							was called														*/
/*		pszClassName		The class name to search for in the project						*/
/*		pProgram			The program instance to search for the class objects in			*/
/*																							*/
/* Return Value:																			*/
/*		0 - No instances of the specified class could be found								*/
/*		Otherwise the instance data of an object of the specified class						*/
/********************************************************************************************/
AX_EXPORT AX_INSTANCE AxGetInstanceFromProgram(AX_INSTANCE	pPreviousInstance,
											   char			*pszClassName,
											   AX_PROGRAM	pProgram);

/********************************************************************************************/
/*	AxGetInstance_N																			*/
/*		This function behaves identically to the function AxGetInstance_N, with the			*/
/*		exception that it will only search for objects of the specified class in the		*/
/*		specified program (pProgram).	If pProgram is NULL, the entire project will be		*/
/*		searched.																			*/
/*																							*/
/*		The function will fill the class instance array, pInstanceList, up to the list size	*/
/*		specified by uiMaxListSize or until there are no more instances of the specified	*/
/*		class in the project, whichever is smaller.  If there are more class instances in	*/
/*		the project then there are positions in the list, the function can be called		*/
/*		successive times with the last instance object found in the previous call being		*/
/*		used for the pPreviousInstance parameter.  The calling function is responsible for	*/
/*		creating the class instance list.  The first time that this function is called for	*/
/*		the specified class, the pPreviousInstance value should be set to NULL.				*/
/*																							*/
/*		NOTE:	AX_INSTANCE and AX_PROGRAM are essentially the same type of data, the only	*/
/*				difference being that AX_PROGRAM stresses that the data represents main		*/
/*				program tree data. AX_INSTANCE data can be used as the pProgram parameter	*/
/*				to search for classes (sub-classes) within specific class objects			*/
/*																							*/
/* Parameters:																				*/
/*		pPreviousInstance	The last class instance data returned the previous time the		*/
/*							function was called												*/
/*		pszClassName		The class name to search for in the project						*/
/*		pInstanceList		A class instance list to write the array of found class objects	*/
/*							to																*/
/*		uiMaxListSize		The maximum number of elements to write into the class instance	*/
/*							list.															*/
/*		pProgram			The program instance to search for the class objects in			*/
/*																							*/
/* Return Value:																			*/
/*		0 - No instances of the specified class could be found								*/
/*		Otherwise the number of class objects that were written into the list				*/
/********************************************************************************************/
AX_EXPORT int AxGetInstanceFromProgram_N(AX_INSTANCE	pPreviousInstance,
										 char			*pszClassName,
										 AX_INSTANCE	pInstanceList[],
										 unsigned int	uiMaxListSize,
										 AX_PROGRAM		pProgram);

/********************************************************************************************/
/*	AxGetSubInstanceFromProgram_N															*/
/*		This function behaves identically to the function AxGetInstance_N, with the			*/
/*		exception that it will only search for objects of the specified class in the		*/
/*		specified program (pProgram).	If pProgram is NULL, the entire project will be		*/
/*		searched.																			*/
/*																							*/
/*		The function will fill the class instance array, pInstanceList, up to the list size	*/
/*		specified by uiMaxListSize or until there are no more instances of the specified	*/
/*		class in the project, whichever is smaller.  If there are more class instances in	*/
/*		the project then there are positions in the list, the function can be called		*/
/*		successive times with the last instance object found in the previous call being		*/
/*		used for the pPreviousInstance parameter.  The calling function is responsible for	*/
/*		creating the class instance list.  The first time that this function is called for	*/
/*		the specified class, the pPreviousInstance value should be set to NULL.				*/
/*																							*/
/*		NOTE:	AX_INSTANCE and AX_PROGRAM are essentially the same type of data, the only	*/
/*				difference being that AX_PROGRAM stresses that the data represents main		*/
/*				program tree data. AX_INSTANCE data can be used as the pProgram parameter	*/
/*				to search for classes (sub-classes) within specific class objects			*/
/*																							*/
/* Parameters:																				*/
/*		pParentInstance		The class instance of the parent class							*/
/*		pPreviousInstance	The last class instance data returned the previous time the		*/
/*							function was called												*/
/*		pszClassName		The class name to search for in the project						*/
/*		pInstanceList		A class instance list to write the array of found class objects	*/
/*							to																*/
/*		uiMaxListSize		The maximum number of elements to write into the class instance	*/
/*							list.															*/
/*		pProgram			The program instance to search for the class objects in			*/
/*																							*/
/* Return Value:																			*/
/*		0 - No instances of the specified class could be found								*/
/*		Otherwise the number of class objects that were written into the list				*/
/********************************************************************************************/
AX_EXPORT int AxGetSubInstanceFromProgram_N(AX_INSTANCE pParentInstance,
											AX_INSTANCE pPreviousInstance,
											char *pszClassName, 
											void* pInstanceList[],
											unsigned int uiMaxListSize,
											AX_PROGRAM pProgram);

/********************************************************************************************/
/*	AxGetTree																				*/
/********************************************************************************************/
AX_EXPORT AX_TREE AxGetTree( AX_TREE previous);

/********************************************************************************************/
/*	AxQueryInstance																			*/
/*		This function searches for a specified class instance name in the project and		*/
/*		returns the instance data if it was found.	Only main class instances can be found	*/
/*		using this function, it has no ability to search for sub-class instances.			*/
/*																							*/
/* Parameters:																				*/
/*		pszName		The instance name to search for in the project							*/
/*																							*/
/* Return Value:																			*/
/*		0 - No specified class instance could not be found									*/
/*		Otherwise the instance data of an object of the specified class						*/
/********************************************************************************************/
AX_EXPORT AX_INSTANCE AxQueryInstance(char *pszName);

AX_EXPORT AX_INSTANCE AxQueryInstanceFromParent(AX_INSTANCE parent, char *pszName);

/********************************************************************************************/
/*	AxGetInstancefromVariable																*/
/*		This function gets the program instance data for a object from the object's			*/
/*		executable data.																	*/
/*																							*/
/* Parameters:																				*/
/*		pExecData	The executable data for an object in the project						*/
/*																							*/
/* Return Value:																			*/
/*		0 - The executable data was invalid													*/
/*		Otherwise the instance data the object												*/
/********************************************************************************************/
AX_EXPORT AX_INSTANCE AxGetInstancefromVariable(AX_EXEC_DATA pExecData);

/********************************************************************************************/
/*	AxGetReferencedInstance																	*/
/*		This function gets the program instance referenced by 'refname' member of inst		*/
/*		executable data.																	*/
/*																							*/
/* Parameters:																				*/
/*		'inst'	instance that contains 'refname' as a member								*/
/*																							*/
/* Return Value:																			*/
/*		instance data if found																*/
/*		Otherwise 0																			*/
/********************************************************************************************/
AX_EXPORT AX_INSTANCE AxGetReferencedInstance(AX_INSTANCE inst, char* refname);

/********************************************************************************************/
/*	AxGetInstanceName																		*/
/*		This function gets the name of a specified program instance.						*/
/*																							*/
/* Parameters:																				*/
/*		pInstance	The program instance data of an object in the project					*/
/*																							*/
/* Return Value:																			*/
/*		0 - The program instance data was invalid											*/
/*		Otherwise the name of the object													*/
/********************************************************************************************/
AX_EXPORT const char *AxGetInstanceName(AX_INSTANCE pInstance);

/********************************************************************************************/
/*	AxGetInstanceName																		*/
/*		This function gets the full name of a specified program instance.					*/
/*		Warning this function is not thread save. The name is written in a temprary buffer.	*/
/*																							*/
/* Parameters:																				*/
/*		pInstance	The program instance data of an object in the project					*/
/*																							*/
/* Return Value:																			*/
/*		0 - The program instance data was invalid											*/
/*		Otherwise the name of the object													*/
/********************************************************************************************/
AX_EXPORT const char* AxGetInstanceNameEx(AX_INSTANCE instance);

/********************************************************************************************/
/*	AxGetInstanceRemark																		*/
/*		This function gets the remark text of a specified program instance.					*/
/*																							*/
/* Parameters:																				*/
/*		pInstance	The program instance data of an object in the project					*/
/*																							*/
/* Return Value:																			*/
/*		The remark text of the object (if any)												*/
/********************************************************************************************/
AX_EXPORT const char *AxGetInstanceRemark(AX_INSTANCE pInstance);

/********************************************************************************************/
/*	AxSetInstanceRemark																		*/
/*		This function sets the remark text of a specified program instance.					*/
/*																							*/
/* Parameters:																				*/
/*		pInstance	The program instance data of an object in the project					*/
/*		pszRemark	The remark text	to be set												*/
/*																							*/
/* Return Value:																			*/
/*																							*/
/********************************************************************************************/
AX_EXPORT int AxSetInstanceRemark(AX_INSTANCE pInstance, char *pszRemark);

/********************************************************************************************/
/*	AxGetInstanceClassPath																	*/
/*		This function gets the directory path of the class symbol file of the specified		*/
/*		class instance.																		*/
/*																							*/
/* Parameters:																				*/
/*		pInstance	The program instance data of an object in the project					*/
/*																							*/
/* Return Value:																			*/
/*		0 - The program instance data was invalid											*/
/*		Otherwise the directory path of the symbol file for the class						*/
/********************************************************************************************/
AX_EXPORT const char *AxGetInstanceClassPath(AX_INSTANCE pInstance);


/********************************************************************************************/
/*	AxGetInstanceExtId																		*/
/*		This function gets the ExtID ( Extended ID ) of a specified program instance.		*/
/*																							*/
/* Parameters:																				*/
/*		pInstance	The program instance data of an object in the project					*/
/*																							*/
/* Return Value:																			*/
/*		The ExtID of the object (if any)													*/
/********************************************************************************************/
AX_EXPORT const char *AxGetInstanceExtId(AX_INSTANCE pInstance);

/********************************************************************************************/
/*	AxSetInstanceExtId																		*/
/*		This function sets the ExtID ( Extended ID ) of a specified program instance.		*/
/*																							*/
/* Parameters:																				*/
/*		pInstance	The program instance data of an object in the project					*/
/*		pszExtID	The ExtID to be set														*/
/*																							*/
/* Return Value:																			*/
/*																							*/
/********************************************************************************************/
AX_EXPORT int AxSetInstanceExtId(AX_INSTANCE pInstance, char *pszExtID);

/********************************************************************************************/
/*	AxGetInstanceClassPath																	*/
/*		This function gets the directory path of the class symbol file of the specified		*/
/*		class instance.																		*/
/*																							*/
/* Parameters:																				*/
/*		pInstance	The program instance data of an object in the project					*/
/*																							*/
/* Return Value:																			*/
/*		0 - The program instance data was invalid											*/
/*		Otherwise the directory path of the symbol file for the class						*/
/********************************************************************************************/
AX_EXPORT const char *AxGetInstanceClassPath(AX_INSTANCE pInstance);

/********************************************************************************************/
/*	AxGetInstanceParentName																	*/
/*		This function gets name of the parent object of the specified program instance.		*/
/*																							*/
/* Parameters:																				*/
/*		pInstance		The program instance data of an object in the project				*/
/*		pszParentName	A character string variable to set to the name of the parent object	*/
/*																							*/
/* Return Value:																			*/
/*		0 - The program instance data was invalid or there was no parent of the specified	*/
/*			program instance																*/
/*		Otherwise the name of the parent obect												*/
/********************************************************************************************/
AX_EXPORT const char* AxGetInstanceParentName(AX_INSTANCE	pInstance,
											  const char	**pszParentName);

/********************************************************************************************/
/*	AxGetSiteNameFromRemoteInstance															*/
/*		This function gets the site name (for aX distributed control network systems) of	*/
/*		the site where the actual instance of a remote instance object exists.  Only call	*/
/*		this function after checking if the remote flag for this program instance is on		*/
/*		(See the AxGetRemoteFlagFromVarDSC function in axsapi32_data.h)						*/
/*																							*/
/* Parameters:																				*/
/*		pInstance		The program instance data of an remote object in the project		*/
/*																							*/
/* Return Value:																			*/
/*		0 - The program instance data was invalid											*/
/*		Otherwise the name of the remote site												*/
/********************************************************************************************/
AX_EXPORT const char *AxGetSiteNameFromRemoteInstance(AX_INSTANCE pInstance);

/********************************************************************************************/
/*	AxGetInstanceNameFromRemoteInstance														*/
/*		This function gets the instance name (for aX distributed control network systems) 	*/
/*		the a remote instance object as it is on the remote site.  Only call this function	*/
/*		after checking if the remote flag for this program instance is on (See the			*/
/*		AxGetRemoteFlagFromVarDSC function in axsapi32_data.h)								*/
/*																							*/
/* Parameters:																				*/
/*		pInstance		The program instance data of an remote object in the project		*/
/*																							*/
/* Return Value:																			*/
/*		0 - The program instance data was invalid											*/
/*		Otherwise the instance name of the object on the remote site												*/
/********************************************************************************************/
AX_EXPORT const char *AxGetInstanceNameFromRemoteInstance(AX_INSTANCE pInstance);

/********************************************************************************************/
/*	AxGetDirectSubInstances																	*/
/*		This function returns an array of program instances of objects inside the specified	*/
/*		progarm instance.																	*/
/*																							*/
/*		The function will fill the program instance array, pInstanceList, up to the list	*/
/*		size specified by uiMaxListSize or until there are no more program instances inside	*/
/*		the specified progarm instance, whichever is smaller.  If there are more program	*/
/*		instances parent object then there are positions in the list, the function can be	*/
/*		called successive times with the last instance object found in the previous call	*/
/*		being used for the pPreviousInstance parameter.  The calling function is			*/
/*		responsible for creating the class instance list.  The first time that this			*/
/*		function is called for the specified program instance, the pPreviousInstance value	*/
/*		should be set to NULL.																*/
/*																							*/
/* Parameters:																				*/
/*		pParentInstance		The parent instance data to search for sub-objects in			*/
/*		pPreviousInstance	The last instance data returned the previous time the function	*/
/*							was called														*/
/*		pInstanceList		An instance list to write the array of found objects to			*/
/*		uiMaxListSize		The maximum number of elements to write into the instance list	*/
/*																							*/
/* Return Value:																			*/
/*		0 - No sub-instances could be found or the parent instance data was invalid			*/
/*		Otherwise the number of sub-instances that were written into the list				*/
/********************************************************************************************/
AX_EXPORT int AxGetDirectSubInstances(AX_INSTANCE	pParentInstance,
									  AX_INSTANCE	pPreviousInstance, 
									  AX_INSTANCE	pInstaceList[],
									  unsigned int	uiMaxListSize);

/********************************************************************************************/
/*	AxGetSubInstanceList																	*/
/*		This creates a list of all the sub-objects of a specified program instance.  This	*/
/*		function allocates the memory used in the returned list.  The calling function is	*/
/*		responsible for freeing the allocated memory by calling the AxFreeSubInstanceList	*/
/*		function once the list is no longer needed.  This function will fail to execute		*/
/*		if it is called with a instance list that has already been created.					*/
/*																							*/
/* Parameters:																				*/
/*		pParentInstance		The parent instance data to search for sub-objects in			*/
/*		pInstanceList		A pointer to instance list object where the created list will	*/
/*							be written														*/
/*																							*/
/* Return Value:																			*/
/*		0 - No sub-instances could be found or the parent instance data was invalid			*/
/*		Otherwise the number of sub-instances that were written into the list				*/
/********************************************************************************************/
AX_EXPORT int AxGetSubInstanceList(AX_INSTANCE					pParentInstance,
								   AxSubInstanceList_StructPt	*pInstanceList);


/********************************************************************************************/
/*	AxGetLevelSubInstanceList																*/
/*		This creates a list of all the sub-objects of a specified program instance at		*/
/*		a specified level. This function allocates the memory used in the returned list.	*/
/*      The calling function is responsible for freeing the allocated memory by				*/
/*		calling the AxFreeSubInstanceList function once the list is no longer needed.		*/
/*      This function will fail to execute if it is called with a instance list that has	*/
/*		already been created.																*/
/*																							*/
/* Parameters:																				*/
/*		pParentInstance		The parent instance data to search for sub-objects in			*/
/*		pInstanceList		A pointer to instance list object where the created list will	*/
/*							be written														*/
/*		level				Level how "deep" to go											*/
/* Return Value:																			*/
/*		0 - No sub-instances could be found or the parent instance data was invalid			*/
/*		Otherwise the number of sub-instances that were written into the list				*/
/********************************************************************************************/
AX_EXPORT int AxGetLevelSubInstanceList(AX_INSTANCE					pParentInstance,
										AxSubInstanceList_StructPt	*pInstanceList,
										int level);

/********************************************************************************************/
/*	AxFreeSubInstanceList																	*/
/*		This function frees the memory created by a call to AxGetSubInstanceList			*/
/*																							*/
/* Parameters:																				*/
/*		pInstanceList	The instance list memory to free									*/
/*																							*/
/* Return Value:																			*/
/*		None																				*/
/********************************************************************************************/
AX_EXPORT void AxFreeSubInstanceList(AxSubInstanceList_StructPt *pInstanceList);

/********************************************************************************************/
/*	AxGetAllClasses																			*/
/*																							*/
/*		NOTE:	Call this function before calling AxGetNumberOfAllClasses					*/
/*																							*/
/* Parameters:																				*/
/*		pInstanceList	The instance list memory to free									*/
/*																							*/
/* Return Value:																			*/
/*		None																				*/
/********************************************************************************************/
AX_EXPORT int AxGetAllClasses(char	*pszClasses[],
							  int	iSize );
AX_EXPORT int AxGetNumberOfAllClasses();

AX_EXPORT const char * AxGetAlarmBitPath(AX_ALARM_BIT_ELM element,int);


AX_EXPORT int AxGetListOfAlarmBits( void*(*alloc)(unsigned), AX_INSTANCE** pppAlarms, char*** pppPicNames);
AX_EXPORT void AxPrepareAlarmData(AX_INSTANCE alarm , char* position, char* remark);
AX_EXPORT void AxAckAllAlarm(char* picname);
AX_EXPORT void AxAckAlarm(AX_INSTANCE elm_id);
AX_EXPORT char** AxGetListOfActiveAlarms(int,int);


/// classNames is an array of pointers allocated from caller
/// nSize is classNames size
/// returns number of class definitions found.
///         -number if nSize is to small!!!
AX_EXPORT int Sps_GetNumberOfClassDefs(char* classNames[], int nSize);
AX_EXPORT void SPS_ScanClass(struct SPS_ProgData*, void* userdata, int (*visitor)(void* userdata, void const * const varStru));
AX_EXPORT int SPS_ScanClassN(struct SPS_ProgData*, char* mdibuff, int buffsize);

AX_EXPORT struct SPS_ProgData** AxAttachSpsClassDir();
AX_EXPORT void AxDettachSpsClassDir(struct SPS_ProgData**);

AX_EXPORT char** AxGetDatalogEnumList();
AX_EXPORT int AxGetDatalogEnumFromVar(struct SPS_BlockDesc* bdsc);
AX_EXPORT int AxGetDatalogRecFlagFromVar(struct SPS_BlockDesc* bdsc);
AX_EXPORT int AxGetDatalogRecResetFlagFromVar(struct SPS_BlockDesc* bdsc);

AX_EXPORT int AxGetParentOfSubInstance_N(
									 char *sub_instance_class_name, 
									 char* sub_instance_name,
									 void* pProg[],		/* OUT array of descriptors */
									 unsigned int N);	/* IN pProg size */

#endif


