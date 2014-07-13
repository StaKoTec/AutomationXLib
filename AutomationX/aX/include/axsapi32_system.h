/********************************************************************************/
/* MODUL axsapi32.dll															*/
/*			   FILE: axsapi32_system.h											*/
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
 
#ifndef _AXS_API_32_SYSTEM_H_
#define _AXS_API_32_SYSTEM_H_


/********************************************************************************************/
/*	AxInit																					*/
/*		This function sets up some function calls within the axsapi32 library.  Call this	*/
/*		function before any other axsapi32 functions in your program.						*/
/*																							*/
/* Parameters:																				*/
/*		None																				*/
/*																							*/
/* Return Value:																			*/
/*		None																				*/
/********************************************************************************************/
AX_EXPORT void AxInit(void);

/********************************************************************************************/
/*	AxOmAttachToObjectMemory																*/
/*		This function sets up the shared memory data that is used to access the automationX	*/
/*		system.  Call this function immediately after calling the AxInit function.  Almost	*/
/*		all functions in this library require the shared memory configured by this			*/
/*		function.																			*/
/*																							*/
/* Parameters:																				*/
/*		None																				*/
/*																							*/
/* Return Value:																			*/
/*		0 - Failure																			*/
/*		1 - Success																			*/
/********************************************************************************************/
AX_EXPORT int AxOmAttachToObjectMemory(void);

/********************************************************************************************/
/*	AxOmQueryProcessGroupInfo																*/
/*		This function sets up the shared memory data for terminal specific information.		*/
/*		Call this function immediately after calling the AxOmAttachToObjectMemory function.	*/
/*		Many functions in the library require this.  The return value from this function	*/
/*		can be ignored as it is not used as an input parameter of any other api function.	*/
/*																							*/
/* Parameters:																				*/
/*		None																				*/
/*																							*/
/* Return Value:																			*/
/*		None																				*/
/********************************************************************************************/
AX_EXPORT void *AxOmQueryProcessGroupInfo(void);

/********************************************************************************************/
/*	AxIsRunning																				*/
/*		This function determines if automationX is still running.  This can be used to		*/
/*		to trigger your application to exit when automationX is shutdown.					*/
/*																							*/
/* Parameters:																				*/
/*		None																				*/
/*																							*/
/* Return Value:																			*/
/*		0 - automationX is not running														*/
/*		1 - automationX is running															*/
/********************************************************************************************/
AX_EXPORT int AxIsRunning(void);

/********************************************************************************************/
/*	AxIsRunning																				*/
/*		This function determines if automationX is still running.  And the spc_count >= 5	*/
/*																							*/
/* Parameters:																				*/
/*		None																				*/
/*																							*/
/* Return Value:																			*/
/*		0 - automationX is not ready														*/
/*		1 - automationX is ready															*/
/********************************************************************************************/
AX_EXPORT int AxIsReady(void);

AX_EXPORT unsigned int AxSpsLifetick(unsigned int* post_lifetick);

/********************************************************************************************/
/*	AxShutdownEvent																			*/
/*		This function determines if one of the automationX applications has requested		*/
/*		automationX to shutdown.  This can be used to trigger your application to exit when	*/
/*		automationX is shutdown.															*/
/*																							*/
/* Parameters:																				*/
/*		None																				*/
/*																							*/
/* Return Value:																			*/
/*		0 - automationX is running															*/
/*		1 - automationX is shutting down													*/
/********************************************************************************************/
AX_EXPORT int AxShutdownEvent(void);

/********************************************************************************************/
/*	AxSendShutdownEvent																		*/
/*		This function can be used to tell the automationX system to shutdown.				*/
/*																							*/
/* Parameters:																				*/
/*		None																				*/
/*																							*/
/* Return Value:																			*/
/*		None																				*/
/********************************************************************************************/
AX_EXPORT void AxSendShutdownEvent(void);

/********************************************************************************************/
/*	AxIsHostMaster																			*/
/*		This function determines whether the local computer is running as the master or the	*/
/*		slave in a redudant server configuration.											*/
/*																							*/
/* Parameters:																				*/
/*		None																				*/
/*																							*/
/* Return Value:																			*/
/*		0 - The local computer is acting as the standby										*/
/*		1 - The local computer is acting as the master										*/
/********************************************************************************************/
AX_EXPORT int AxIsHostMaster(void);

/********************************************************************************************/
/*	AxHostStandAlone																		*/
/*		This function determines whether the automationX system is running in a redundant	*/
/*		server or stand-alone server modes.													*/
/*																							*/
/* Parameters:																				*/
/*		None																				*/
/*																							*/
/* Return Value:																			*/
/*		0 - The automationX system is running in redundant mode								*/
/*		1 - The automationX system is running in stand-alone mode							*/
/********************************************************************************************/
AX_EXPORT int AxHostStandAlone(void);

/********************************************************************************************/
/*	AxIsHostConfiguredAsMaster																*/
/*		This function determines whether the local computer in the redundant system is		*/
/*		configured to be the redundancy master.  This parameter is used in the rare			*/
/*		occurance when the two servers are started at the same time and need to determine	*/
/*		which of the two will take control and be the master.								*/
/*																							*/
/* NOTE:	This parameter is unrelated to the actual running state of the redundancy sytem	*/
/*																							*/
/* Parameters:																				*/
/*		None																				*/
/*																							*/
/* Return Value:																			*/
/*		0 - The local computer is configured as the standby									*/
/*		1 - The local computer is configured as the master									*/
/********************************************************************************************/
AX_EXPORT int AxIsHostConfiguredAsMaster(void);

/********************************************************************************************/
/*	AxGetSPSTimeAbsolut																		*/
/*		This function gets the absolut SPS Time from the system.   							*/
/*																							*/
/* Parameters:																				*/
/*		None																				*/
/*																							*/
/* Return Value:																			*/
/*		The absolut SPS Time (unix time incl. msec)											*/
/********************************************************************************************/
AX_EXPORT double AxGetSPSTimeAbsolut(void);

/********************************************************************************************/
/*	AxGetSPSTimeRelative																	*/
/*		This function gets the realative SPS Time from the system. (the time from the		*/
/*		startup of the system )  															*/
/*																							*/
/* Parameters:																				*/
/*		None																				*/
/*																							*/
/* Return Value:																			*/
/*		The realtive SPS Time (unix time incl. msec)										*/
/********************************************************************************************/
AX_EXPORT double AxGetSPSTimeRelative(void);

/********************************************************************************************/
/*	AxGetHostName																			*/
/*		This function gets the host name of the local computer.								*/
/*																							*/
/* Parameters:																				*/
/*		pszBuff		The string buffer to write the host name into							*/
/*		iBuffLen	The length of the string buffer											*/
/*																							*/
/* Return Value:																			*/
/*		0 - Failure																			*/
/*		Otherwise pszBuff																	*/
/********************************************************************************************/
AX_EXPORT char *AxGetHostName(char	*pszBuff,
							  int	iBuffLen);
#define axGetHostName	AxGetHostName

/********************************************************************************************/
/*	AxGetRemoteHost																			*/
/*		This function gets the host name of the remote computer in a redundancy				*/
/*		configuration.																		*/
/*																							*/
/* Parameters:																				*/
/*		None																				*/
/*																							*/
/* Return Value:																			*/
/*		0 - Failure																			*/
/*		Otherwise the name of the remote host												*/
/********************************************************************************************/
AX_EXPORT const char *AxGetRemoteHost(void);

/********************************************************************************************/
/*	AxGetProjectDir																			*/
/*		This function gets the directory of the currently running project as a deflection	*/
/*		from the main automationX directory.  i.e. If the full path to your project			*/
/*		directory is "C:\automationX\projects\demo", the string returned is					*/
/*		"projects\demo".																	*/
/*																							*/
/* Parameters:																				*/
/*		None																				*/
/*																							*/
/* Return Value:																			*/
/*		0 - Failure																			*/
/*		Otherwise the project directory														*/
/********************************************************************************************/
AX_EXPORT char *AxGetProjectDir(void);

/********************************************************************************************/
/*	AxGetBinDir																				*/
/*		This function gets the directory of the currently running automationX binaries as a	*/
/*		deflection from the main automationX directory.  i.e. If the automationX binaries	*/
/*		are located in the directory "C:\automationX\bin", the string returned is "bin"		*/
/*																							*/
/* Parameters:																				*/
/*		None																				*/
/*																							*/
/* Return Value:																			*/
/*		0 - Failure																			*/
/*		Otherwise the automationX binaries directory										*/
/********************************************************************************************/
AX_EXPORT char *AxGetBinDir(void);

/********************************************************************************************/
/*	AxUPsetReadySignal																		*/
/*		This function sets up the itentifier needed for lifetick communication between the	*/
/*		automationX process control program and the client program.  This is needed for		*/
/*		programs which should be restarted by automationX if they stop running for some		*/
/*		reason. Such programs must be listed in the UserProcesses.pls configuration file	*/
/*		in the project directory.															*/
/*																							*/
/*		Call this function before calling the AxUPlifetick function.						*/
/*																							*/
/* NOTE:	The pszProcess parameter must be the same as the program executable name.		*/
/*			i.e. if your program name is "my_program.exe", the pszProcess parameter must be	*/
/*			"my_program"																	*/
/*																							*/
/* Parameters:																				*/
/*		pszProcess	The process name to register with automationX							*/
/*																							*/
/* Return Value:																			*/
/*		None																				*/
/********************************************************************************************/
AX_EXPORT void AxUPsetReadySignal(char* pszProcess);

/********************************************************************************************/
/*	AxUPlifetick																			*/
/*		This function sends a lifetick to the automationX process control program.  This is	*/
/*		needed for programs which should be restarted by automationX if they stop running	*/
/*		for some reason. Such programs must be listed in the UserProcesses.pls				*/
/*		configuration file in the project directory.										*/
/*																							*/
/*		Call AxUPsetReadySignal before calling this function.								*/
/*																							*/
/* NOTE:	The pszProcess parameter must be the same as the program executable name.		*/
/*			i.e. if your program name is "my_program.exe", the pszProcess parameter must be	*/
/*			"my_program"																	*/
/*																							*/
/* Parameters:																				*/
/*		pszProcess	The process name registered with automationX							*/
/*																							*/
/* Return Value:																			*/
/*		None																				*/
/********************************************************************************************/
AX_EXPORT void AxUPlifetick(char* pszProcess);

/********************************************************************************************/
/*	AxSleep																					*/
/*		This function causes a program to be idle for the specified amount of time.  This	*/
/*		is used reduce processor usage and to let other applications on the computer run in */
/*		a smooth fashion.																	*/
/*																							*/
/* Parameters:																				*/
/*		iSeconds	The number of seconds that the program should remain idle				*/
/*																							*/
/* Return Value:																			*/
/*		None																				*/
/********************************************************************************************/
AX_EXPORT void AxSleep(int iSeconds);


/********************************************************************************************/
/*	AxInstallDataSM																			*/
/*		This function creates a memory block of the specified size in the shared memory		*/
/*		area of automationX.  The created memory is identified by the name character		*/
/*		string.  If the specified identifier name has already been used to create a shared	*/
/*		memory block, then the function will not create the new memory.						*/
/*																							*/
/*		This function can be used to create memory that is to be shared between	different	*/
/*		applications.																		*/
/*																							*/
/* Parameters:																				*/
/*		pszName		The identifier name of the shared memory block to be created			*/
/*		iSize		The size of the memory block to create									*/
/*																							*/
/* Return Value:																			*/
/*		0 - The memory could not be created													*/
/*		Otherwise a pointer to the new shared memory block									*/
/********************************************************************************************/
AX_EXPORT void *AxInstallDataSM(char	*pszName,
								int		iSize);

/********************************************************************************************/
/*	AxQueryDataSM																			*/
/*		This function finds and existing shared memory block that has the specified			*/
/*		identifier name.																	*/
/*																							*/
/* Parameters:																				*/
/*		pszName		The identifier name of the shared memory block							*/
/*																							*/
/* Return Value:																			*/
/*		0 - The identifier could not be found in the shared memory							*/
/*		Otherwise a pointer to the shared memory block										*/
/********************************************************************************************/
AX_EXPORT void *AxQueryDataSM(char *pszName);

/********************************************************************************************/
/*	AxFreeDataSM																			*/
/*		This function frees the shared memory block with the specified name					*/
/*																							*/
/* Parameters:																				*/
/*		pszName		The identifier name of the shared memory block							*/
/*																							*/
/* Return Value:																			*/
/*		0 - Failure (Possibly the identifier could not be found in the shared memory)		*/
/*		1 - Success																			*/
/********************************************************************************************/
AX_EXPORT int AxFreeDataSM(char *pszName);

/********************************************************************************************/
/*	AxSHM_getFreeSize																		*/
/*		This function gets the amount of free space that is available in the automationX	*/
/*		shared memory space.																*/
/*																							*/
/* Parameters:																				*/
/*		None																				*/
/*																							*/
/* Return Value:																			*/
/*		The amount of free space (in Bytes)													*/
/********************************************************************************************/
AX_EXPORT unsigned int AxSHM_getFreeSize(void);

/********************************************************************************************/
/*	AxSHM_getFreeSize																		*/
/*		This function frees memory that has been allocated using malloc, calloc, or			*/
/*		realloc.																			*/
/*																							*/
/* NOTE:	DO NOT use this function to free memory blocks created in the automationX		*/
/*			shared memory area.  Use AxFreeDataSM to do this!								*/
/*																							*/
/* Parameters:																				*/
/*		None																				*/
/*																							*/
/* Return Value:																			*/
/*		The amount of free space (in Bytes)													*/
/********************************************************************************************/
AX_EXPORT void AxFree(void* p);

/********************************************************************************************/
/*	AxStartProcess																			*/
/*		This function starts an external program.  The program must be located in the		*/
/*		automationX bin Directory.															*/
/*																							*/
/* Parameters:																				*/
/*		pszName		The name of the process to launch (plus any arguements)					*/
/*																							*/
/* Return Value:																			*/
/*		0 - The external program failed to start											*/
/*		Otherwise the pid (process identity) number of the new process						*/
/********************************************************************************************/
AX_EXPORT int AxStartProcess(char *pszName);

/********************************************************************************************/
/*	AxKill																					*/
/*		This function sends a "kill" command the the program with the given process			*/
/*		identity (pid) number.  The command is sent with the specified kill signal.			*/
/*																							*/
/* Parameters:																				*/
/*		pid			The process identity number of the process to "kill"					*/
/*		iSignal		The signal to send with the kill command								*/
/*																							*/
/* Return Value:																			*/
/*		-1 - Failure																		*/
/*		0 - Success																			*/
/********************************************************************************************/
#if linux
AX_EXPORT int AxKill(long	pid,
					 int	iSignal);
#endif

/********************************************************************************************/
/*	AxHasSpsIdChanged																		*/
/*		This function checks to see if the SPS Id of the running automationX system has		*/
/*		changed.  This lets the calling application know when a program or class in the		*/
/*		project has been saved, or if the "warmstart" button in the project configuration	*/
/*		window has been pressed.															*/
/*																							*/
/*		This function is also used to determine when an	application can start accessing the	*/
/*		automationX run-time memory.  Normally, an application should not start execution	*/
/*		until the SPS Id number is 2 or higher.												*/
/*																							*/
/* NOTE:	If the SPS Id number changes, the executable and variable descriptor data used	*/
/*			in the application MUST be refreshed.  Failure to do so will result in an		*/
/*			unstable application.  Call this function before all calls using AX_EXEC_DATA	*/
/*			and AX_VAR_DSC data pointers.													*/
/*																							*/
/* Parameters:																				*/
/*		piOldId		A variable containing the last known value of the SPS Id.  This			*/
/*					variable will be updated to the current SPS Id number in the process	*/
/*					of the functions execution												*/
/*																							*/
/* Return Value:																			*/
/*		0 - The SPS Id has not changed														*/
/*		1 - The SPS Id has changed															*/
/********************************************************************************************/
AX_EXPORT int AxHasSpsIdChanged(int* piOldId);

// neat
AX_EXPORT void* AxGetMem();

AX_EXPORT int AxGetNumberOfTreeData();
AX_EXPORT int AxGetTreeData(AXTreeData pTreeData[], int size);
AX_EXPORT int AxSpsIsRunning();
AX_EXPORT int AxCheckLoginUserPassword(char* username, char* password, int remote, int* plevel);
AX_EXPORT int AxCryptDecrypt(const char *pIn, char *pOut );
AX_EXPORT int AxGetLevelId(int UserID);
AX_EXPORT int AxProcessRunningCount( const char *name );


#endif
