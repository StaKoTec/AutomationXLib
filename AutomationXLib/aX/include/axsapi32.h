/********************************************************************************/
/* MODUL axsapi32.dll															*/
/*			   FILE: axsapi32.h													*/
/*           SYSTEM: NT4.0 / 2000										    	*/
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
/*      use the (aXHome)/lib/axsapi.lib in Your Project Settings		!	    */
/*      The axsapi32.dll is compiled    with an alignment from 4 Bytes  !       */
/*                       														*/
/********************************************************************************/
 
#ifndef _AXS_API_32_H_
#define _AXS_API_32_H_

#ifndef _IN_AX_
#pragma pack(push,4)
#endif

#undef AX_EXPORT
#if !linux

#define DLL_EXPORT __declspec(dllexport)
 
#ifdef AX_MAKE_DLL
#define AX_EXPORT __declspec(dllexport)
#else
#define AX_EXPORT __declspec(dllimport)
#endif
#else
#define AX_EXPORT
#endif

#define DLL_EXPORT __declspec(dllexport)

#ifdef __cplusplus
extern "C" {
#endif

#include "axvariant.h"
#include "axsapi32_data.h"
#include "axsapi32_program.h"
#include "axsapi32_system.h"
#include "axsapi32_misc.h"
#include "axsapi32_custom_fb.h"
	
#ifdef __cplusplus
}
#endif

#ifndef _IN_AX_
#pragma pack(pop)
#endif

#endif

#if 0

/******************************************************************************************/
/******************************************************************************************/
/***																					***/
/***				automationX Status and System Functions								***/
/***																					***/
/***	The following functions have been moved to the file axsapi32_system.h			***/
/***																					***/
/******************************************************************************************/
/******************************************************************************************/

AxInit						// Initialize aX function information
AxOmAttachToObjectMemory	// Attach to aX Global Data structures
AxOmQueryProcessGroupInfo	// Initialize Host Process information
AxIsRunning					// Is aX still running
AxShutdownEvent				// Has a process requested aX to shutdown
AxSendShutdownEvent			// Request aX to shutdown
AxIsHostMaster				// Is aX the master in a redundant configuration
AxHostStandAlone			// Is aX running without redundancy
AxIsHostConfiguredAsMaster	// Is aX configured as the default master
AxGetHostName				// The host name of the local computer
AxGetRemoteHost				// The host name of the remote redundant computer
AxGetProjectDir				// Get the directory of the running project
AxGetBinDir					// Get the directory of the aX binaries
AxUPsetReadySignal			// Setup the lifetick signal information
AxUPlifetick				// Send a lifetick to the aX process monitor program
AxSleep						// Pause program execution
AxInstallDataSM				// Install data into the aX shared memory
AxQueryDataSM				// Get data from the aX shared memory
AxFreeDataSM				// Free data in the aX shared memory
AxSHM_getFreeSize			// Get the amount of free aX shared memory available
AxFree						// Free allocated memory.
AxStartProcess				// Start an external process
AxKill						// Stop an process with a given PID
AxHasSpsIdChanged			// See if a new sps image has been created


/******************************************************************************************/
/******************************************************************************************/
/***																					***/
/***							Data-Access Functions									***/
/***																					***/
/***	The following functions have been moved to the file axsapi32_data.h				***/
/***																					***/
/******************************************************************************************/
/******************************************************************************************/


/******************************************************************************************/
/*** Functions based on a variable/object name											***/
/******************************************************************************************/

AxQueryGet					// Get the value of a variable
AxQuerySet					// Set the value of a variable

AxQueryExecDataEx			// Get the ExecData memory of an object (creates memory)
AxQueryExecDataExParent		// Get the ExecData memory for the parent of an object
							// (creates memory)
AxQueryVariable				// Get the ExecData memory of a variable
AxQueryVariableEx			// Get the ExecData memory of a variable in a particular
							// program.
AxQueryVariableInterface	// Get the ExecData memory of a variable and see if it is
							// a remote interface variable (Windows aX 4.6 only)
AxQueryVariableExInterface	// Get the ExecData memory of a variable in a particular
							// program and see if it is a remote interface variable
							// (Windows aX 4.6 only)
AxFreeExecData				// Free ExecData memory create using one of the get functions

/******************************************************************************************/
/*** Functions based on using the ExecData (Executable Data) of a variable/object		***/
/******************************************************************************************/

AxGet						// Get the value of a variable (using aX tag variant)
AxGetValueEx				// Get the value of a variable
AxGetLong					// Get the value of an integer type variable
AxGetDouble					// Get the value of a floating point type variable
AxGetString					// Get the value of a string type variable
AxGetValueAsString			// Get the value of any type of variable as a string
AxGetArray					// Get the value of a variable at an array position

AxSet						// Set the value of a variable (using aX tag variant)
AxSetValueEx				// Set the value of a variable
AxSetLong					// Set the value of an integer type variable
AxSetDouble					// Set the value of a floating point type variable
AxSetString					// Set the value of a string type variable
AxSetArray					// Set the value of a variable at an array position
AxSetAlarm					// Set the value of an alarm type variable (Linux aX 4.6ML
							// only)

AxGetName					// Get the name of a variable
AxGetRemark					// Get the remark of a variable
AxGetVarReference			// Get the reference string of a reference type variable
AxGetVarDeclaration			// Get how the variable is declared (input, output, etc.)
AxGetType					// Get the data type of a variable/object
AxGetBaseType				// Get the type of a variable as a string
AxIsComplexType				// Is the variable data a complex type (i.e. alarm/odbc)
AxGetComplexTypeName		// Get the name of the complex variable type as a string
AxVarIsEnum					// Is the variable an enumerator
AxGetDimension				// Get the dimension string of a variable
AxGetArrayCnt				// Get the array count of an arrayed variable/object
AxGetDecPoint				// Get the number of decimal points a floating point
							// variable displays.
AxGetSubrange				// Get the subrange and decimal points of a variable
AxGetSegSize				// Get the size of the memory holding a variables value.
AxGetAlarmInfo				// Get the alarm parameters of an alarm type variable
AxGetAttributes				// Get various attributes of a varaible

AxGetNcFlag					// Get the not connected flag for a referance variable/object
AxGetNcFlag_Subrange_Dimension_Remark	// Get the not connected flag, dimesion,
										// sub-range and remark for a variable
AxGetValidFlag				// Get the status of a variables valid flag
AxGetTrendingFlag			// Get the status of a variables trending flag
AxGetRetentiveFlag			// Get the status of a variables retentive flag
AxGetConstantFlag			// Get the status of a variables constant flag
AxGetPrivateFlag			// Get the status of a variables private flag
AxGetIOVarFlag				// Get the status of a variables IO variable flag
AxGetLocalFlag				// Get the status of a variables local flag
AxGetConfValueFlag			// Get the status of a variables configuration value flag
AxGetParameterFlag			// Get the status of a variables parameter flag
AxGetRemoteFlag				// Get the status of a variables remote data flag
AxGetInterfaceFlag			// Get the status of a variables interface variable flag


AxSetDecPoint				// Set the number of decimal points a floating point
							// variable displays.
AxSetAttributes				// Set various attributes of a varaible
AxSetNcFlag					// Set the not connected flag for a referance variable/object
AxSetNcFlag_Subrange_Dimension_Remark	// Set the not connected flag, dimesion,
										// sub-range and remark for a variable
AxSetValidFlag				// Set the status of a variables valid flag

AxGetExecDataInfo			// Get a string describing the data structure (variable data
							// memory address and name)
AxGetAddressFromExecData	// Get the pointer to the actual data for a variable.
AxGetSubVarList				// Get the list of variables contained within an object.

/******************************************************************************************/
/*** Functions based on using the Variable Descriptor Data of a variable				***/
/******************************************************************************************/

AxVarDscFromInstance		// Gets the next variable in a particular class instance
AxVarDscFromInstance_N		// Gets an array of variables in a particular class instance

AxGetNameFromVarDSC			// Get the name of a variable
AxGetRemarkFromVarDSC		// Get the remark of a variable
AxGetReferenceFromVarDSC	// Get the reference string of a reference type variable
AxGetNameCRCFromVarDSC		// Get the CRC value of the variable name
AxGetReferenceCRCFromVarDSC	// Get the CRC value of the variable reference name
AxGetAxTypeFromVarDSC		// Get the data type of the variable
AxGetTypeFromVarDSC			// Get the data type of the variable as a string
AXGetDimensionFromVarDSC	// Get the dimension string of a variable
AxGetArrayCntFromVarDSC		// Get the array count of an arrayed variable
AxGetSubrangeLowFromVarDSC	// Get the minimum range for a variable used in aX
AxGetSubrangeHighFromVarDSC	// Get the maximum range for a variable used in aX	
AxGetMinScaleFromVarDSC		// Get the minimum range configured for an IO var in the field
AxGetMaxScaleFromVarDSC		// Get the maximum range configured for an IO var in the field
AxGetMinIOFromVarDSC		// Get the minimum PLC comunication register value
AxGetMaxIOFromVarDSC		// Get the maximum PLC comunication register value
AxGetAlarmInfoFromVarDSC	// Get the alarm parameters of an alarm type variable

AxGetRemoteFlagFromVarDSC	// Get the status of a variables remote data flag
AxGetInterfaceFlagFromVarDSC // Get the status of a variables interface variable flag
AxGetFlagsFromVarDSC		// Get the status of various variable flags.


/******************************************************************************************/
/******************************************************************************************/
/***																					***/
/***					Program and Class Instance functions							***/
/***																					***/
/***	The following functions have been moved to the file axsapi32_program.h			***/
/***																					***/
/******************************************************************************************/
/******************************************************************************************/


AxGetProgram				// Gets the next program in the project tree.
AxGetProgramName			// Gets the name of a program as a string
AxQueryProgram				// Gets the program descriptor for a requested program name
AxGetInstance				// Gets the next instance of a particular class
AxGetInstance_N				// Gets an array of instances of a particular class
AxGetInstanceFromProgram	// Gets the next instance of a particular class in a program
AxGetInstanceFromProgram_N	// Gets an array of instances of a particular class in a program
AxQueryInstance				// Gets a program instance for a requested instance name
AxGetInstancefromVariable	// Get the program instance data of an object from executable data
AxGetInstanceName			// Gets the instance name from a class instance description
AxGetInstanceRemark			// Gets the instance remark from a class instance description
AxGetInstanceClassPath		// Gets the class library directory path of a class
AxGetInstanceParentName		// Gets the names of the parents of a class instance
AxGetSiteNameFromRemoteInstance		// Gets the remote site name from a remote class
									// instance
AxGetInstanceNameFromRemoteInstance	// Gets the instance name on the remote site of a 
									//	remote instance.
AxGetDirectSubInstances		// Get an array of sub instances of a specified class instance
AxGetSubInstanceList		// Get a list off all the sub instancess of a specified class
							// instance
AxFreeSubInstanceList		// Free the sub instance list.
AxGetNumberOfAllClasses		// Counts the number of all class instances in a project
AxGetAllClasses				// Counts the number of all class instances in a project and


/******************************************************************************************/
/******************************************************************************************/
/***																					***/
/***							Miscellaneous Functions									***/
/***																					***/
/***	The following functions have been moved to the file axsapi32_misc.h				***/
/***																					***/
/******************************************************************************************/
/******************************************************************************************/

/******************************************************************************************/
/*** Messaging Functions																***/
/******************************************************************************************/

AxLog						// Send a message to the journal system
AxLogTS						// Send a message to the journal system with particular 
							// time stamp (Linux aX 4.6ML only)
AxGetExLogMessages			// Get the messages out of the journal system
AxDebug						// Send a message to the run-time messages debug window
AxSendSMTPMail				// Send an e-mail message (Windows aX only)


/******************************************************************************************/
/*** Historical Data-Access Functions													***/
/******************************************************************************************/

AxGetHistoricalData			// Get the trend data of a particular variable
AxGetHistoricalDataInfo		// Get the trend configuration data of a particular variable


/******************************************************************************************/
/*** Redundancy File Functions															***/
/******************************************************************************************/

AxCopyFileToRDHost			// Copy a file to the redundant computer
AxDeleteFileRD				// Delete a file on the redundant computer
AxAppendFileRD				// Append data to a file on the redundant computer.


/******************************************************************************************/
/*** Enumerator Functions																***/
/******************************************************************************************/

AxGetGlobalEnum				// Get the global enumerator at the specified index
AxGetEnumDsc				// Get the enumerator description of the specified enumerator
GetNextEnumValue			// Get the enumerator text and value at a specified index
GetEnumValue				// Get the enumerator value for a specified pneumonic


/******************************************************************************************/
/*** Time Conversion Functions															***/
/******************************************************************************************/

AxConvertDateTime_ToValue	// Get a number representing a specified time.
AxConvertValue_ToDateTime	// Convert a number to a real date and time.
AxGetActUnixTime			// Get the current time as a unix time (time_t) number.

#endif