/********************************************************************************/
/* MODUL axsapi32.dll															*/
/*			   FILE: axsapi32_data												*/
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
 
#ifndef _AXS_API_32_DATA_H_
#define _AXS_API_32_DATA_H_


/********************************************************************************************/
/*	AxQueryGet																				*/
/*		This function gets the value of a variable represented by the character string		*/
/*		pszPath.  If found, the value of the variable is written into the pVt structure.	*/
/*																							*/
/* Parameters:																				*/
/*		pszPath			A string representing a variable in an automationX project			*/
/*		pVt				A union structure where the value of the requested variable will	*/
/*						be written.															*/
/*																							*/
/* Return Value:																			*/
/*		0 - Failure	(the variable was not found or the specified name was found but not a	*/
/*					 variable type)															*/
/*		1 - Success	(the variable was found in the project)									*/
/********************************************************************************************/
AX_EXPORT int AxQueryGet(char					*pszPath,
						 struct tagAxVariant	*pVt);

/********************************************************************************************/
/*	AxQuerySet																				*/
/*		This function sets the value of a variable represented by the character string		*/
/*		pszPath.  If found, the value of the variable is assigned based on the data			*/
/*		contained in the pVt structure.														*/
/*																							*/
/* Parameters:																				*/
/*		pszPath			A string representing a variable in an automationX project			*/
/*		pVt				A union structure where the data that is to be written to the		*/
/*						variable is contained.												*/
/*																							*/
/* Return Value:																			*/
/*		0 - Failure	(the variable was not found or the specified name was found but not a	*/
/*					 variable type)															*/
/*		1 - Success	(the variable was found in the project)									*/
/********************************************************************************************/
AX_EXPORT int AxQuerySet(char					*pszPath,
						 struct tagAxVariant	*pVt);

/********************************************************************************************/
/*	AxQueryExecDataEx																		*/
/*		This function finds the variable or object represented by the character string		*/
/*		pszPath and returns a pointer to the automationX executable data for it.  This		*/
/*		data is the real-time database information for the object and can be used to very	*/
/*		quickly access and read from, or write data to that object.				 			*/
/*																							*/
/*		The executable data returned from this function is allocated memory and must be		*/
/*		released using the AxFreeExecData function after it is no longer needed.			*/
/*																							*/
/* Parameters:																				*/
/*		pszPath			A string representing a variable or object in an automationX		*/
/*						project																*/
/*																							*/
/* Return Value:																			*/
/*		0 - Failure	(the variable or object was not found)									*/
/*		ELSE - Success																		*/
/********************************************************************************************/
AX_EXPORT AX_EXEC_DATA AxQueryExecDataEx(char *pszPath);

/********************************************************************************************/
/*	AxQueryExecDataAttrIdx																		*/
/*		This function finds the variable of pExecData[array_index].attr_index	*/
/*																							*/
/*		The executable data returned from this function is allocated memory and must be		*/
/*		released using the AxFreeExecData function after it is no longer needed.			*/
/*																							*/
/* Parameters:																				*/
/*		pszPath			A string representing a variable or object in an automationX		*/
/*						project																*/
/*																							*/
/* Return Value:																			*/
/*		0 - Failure	(the variable or object was not found)									*/
/*		ELSE - Success																		*/
/********************************************************************************************/
AX_EXPORT AX_EXEC_DATA AxQueryExecDataAttrIdx(AX_EXEC_DATA pExecData, int array_index, int attr_index);

/********************************************************************************************/
/*	AxQueryExecDataExParent																	*/
/*		This function finds the variable or object represented by the character string		*/
/*		pszPath and returns a pointer to the automationX executable data for it.  This		*/
/*		data is the real-time database information for the object and can be used to very	*/
/*		quickly access and read from, or write data to that object.  This function differs	*/
/*		from the AxQueryExecDataEx function in that it will only search for the specified	*/
/*		variable within the program instance defined by pInstance.  If pInstance is NULL	*/
/*		the entire project will be searched.									 			*/
/*																							*/
/*		The executable data returned from this function is allocated memory and must be		*/
/*		released using the AxFreeExecData function after it is no longer needed.			*/
/*																							*/
/* Parameters:																				*/
/*		pInstance		A object (i.e. class instance) residing in the automationX project	*/
/*						(see axsapi32_program.h)											*/
/*		pszName			A string representing a variable or object inside of an automationX	*/
/*						object																*/
/*																							*/
/* Return Value:																			*/
/*		0 - Failure	(the variable or object was not found)									*/
/*		ELSE - Success																		*/
/********************************************************************************************/
AX_EXPORT AX_EXEC_DATA AxQueryExecDataExParent(AX_INSTANCE	pInstance,
											   char			*pszName);

/********************************************************************************************/
/*	AxQueryVariable																			*/
/*		This function finds the variable or object represented by the character string		*/
/*		pszPath. If the variable or object is found, the executable data will be written	*/
/*		into the memory pointer pExecData passed into the function				 			*/
/*																							*/
/*		The executable data pointer passed into this application must have previously been	*/
/*		allocated (i.e. by a previous call to AxQueryExecDataEx).  This ability to re-use	*/
/*		an executable data pointer makes this a useful function to use in situations where	*/
/*		it is necessary to re-query for the same variable (i.e. after a program save)		*/
/*																							*/
/* Parameters:																				*/
/*		pszPath			A string representing a variable or object in an automationX		*/
/*						project																*/
/*		pExecData		The executable data pointer to write the variable or object data	*/
/*						to.  The memory for this must be previously defined.				*/
/*																							*/
/* Return Value:																			*/
/*		0 - Failure	(the variable or object was not found)									*/
/*		1 - Success																			*/
/********************************************************************************************/
AX_EXPORT int AxQueryVariable(char			*pszPath,
							  AX_EXEC_DATA	pExecData);

/********************************************************************************************/
/*	AxQueryVariable_N																			*/
/*		This function finds the variable or object represented by the character string		*/
/*		pszPath. If the variable or object is found, the executable data will be written	*/
/*		into the memory pointer pExecData passed into the function				 			*/
/*																							*/
/*		The executable data pointer passed into this application must have previously been	*/
/*		allocated (i.e. by a previous call to AxQueryExecDataEx).  This ability to re-use	*/
/*		an executable data pointer makes this a useful function to use in situations where	*/
/*		it is necessary to re-query for the same variable (i.e. after a program save)		*/
/*																							*/
/* Parameters:																				*/
/*		pszPath			A string representing a variable or object in an automationX		*/
/*						project																*/
/*		pExecData		The executable data pointer to write the variable or object data	*/
/*						to.  The memory for this must be previously defined.				*/
/*																							*/
/* Return Value:																			*/
/*		number of succeed-ed queries														*/
/********************************************************************************************/
AX_EXPORT int AxQueryVariable_N(char		*pszPath[], 
								AX_EXEC_DATA pExecData[], 
								char err[],
								unsigned nel );


/********************************************************************************************/
/*	AxQueryVariableFromInstance_N															*/
/*																							*/
/*		The function will fill the executable data array, pExecData, up to the list			*/
/*		size specified by uiMaxListSize or until there are no more variables in the	program	*/
/*		instance object, whichever is smaller.  If there are more variables in the program	*/
/*		instance object then there are positions in the list, the function can be called	*/
/*		successive times with the last executable data found in the previous call being		*/
/*		used for the pPreviousExecData parameter.  The calling function is responsible for	*/
/*		creating the variable descriptor list.												*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pInstance		The target program instance data									*/
/*		pPreviousExecData	The executable data found the previous time this function		*/
/*						was called for the pInstance program object							*/
/*		pExecData		A array of executable data pointers to write the found variables to.*/
/*		uiMaxListSize	The maximum number of elements to write into the variable			*/
/*						descriptor list.													*/
/*																							*/
/* Return Value:																			*/
/*		number of found queries																*/
/********************************************************************************************/
AX_EXPORT int AxQueryVariableFromInstance_N(AX_INSTANCE pInstance,			/*IN */
											AX_EXEC_DATA pPreviousExecData, /*IN null*/
											AX_EXEC_DATA pExecData[],		/*IN*/
											unsigned uiMaxListSize );		/*IN*/

/********************************************************************************************/
/*	AxQueryVariableEx																		*/
/*		This function finds the variable or object represented by the character string		*/
/*		pszPath. If the variable or object is found, the executable data will be written	*/
/*		into the memory pointer pExecData passed into the function.  This function differs	*/
/*		from the AxQueryVariable function in that it will search for the specified			*/
/*		variable or object from within the program object specified by pProgram.  If		*/
/*		pProgram is NULL, the entire project will be searched.					 			*/
/*																							*/
/*		The executable data pointer passed into this application must have previously been	*/
/*		allocated (i.e. by a previous call to AxQueryExecDataEx).  This ability to re-use	*/
/*		an executable data pointer makes this a useful function to use in situations where	*/
/*		it is necessary to re-query for the same variable (i.e. after a program save)		*/
/*																							*/
/* Parameters:																				*/
/*		pProgram		An automationX program object (see axsapi32_program.h)				*/
/*		pszSubPath		A string representing a variable or object within an automationX	*/
/*						program object														*/
/*		pExecData		The executable data pointer to write the variable or object data	*/
/*						to.  The memory for this must be previously defined.				*/
/*																							*/
/* Return Value:																			*/
/*		0 - Failure	(the variable or object was not found)									*/
/*		1 - Success																			*/
/********************************************************************************************/
AX_EXPORT int AxQueryVariableEx(AX_PROGRAM		pProgram,
								char			*pszSubPath,
								AX_EXEC_DATA	pExecData);

/********************************************************************************************/
/*	AxQueryVariableInterface																*/
/*		This function is basically identical to the AxQueryVariable function.  Its only		*/
/*		difference is that it also assigns a flag indicating whether the varible or object	*/
/*		is an interface object.													 			*/
/*																							*/
/*		The executable data pointer passed into this application must have previously been	*/
/*		allocated (i.e. by a previous call to AxQueryExecDataEx).  This ability to re-use	*/
/*		an executable data pointer makes this a useful function to use in situations where	*/
/*		it is necessary to re-query for the same variable (i.e. after a program save)		*/
/*																							*/
/* Parameters:																				*/
/*		pszPath			A string representing a variable or object in an automationX		*/
/*						project																*/
/*		pExecData		The executable data pointer to write the variable or object data	*/
/*						to.  The memory for this must be previously defined.				*/
/*		piInterfaceFlag	An flag indicating whether the requested variable is defined as an	*/
/*						interface variable (1 - Interface Variable, 0 - Not an Interface	*/
/*						Variable)															*/
/*																							*/
/* Return Value:																			*/
/*				0  var found and interface flag is set										*/
/*				1  var not found															*/
/*				2  var found and interface flag is reset									*/
/********************************************************************************************/
#if !AX_VER_46ML
AX_EXPORT int AxQueryVariableInterface(char			*pszPath,
									   AX_EXEC_DATA	pExecData
									   );

/********************************************************************************************/
/*	AxQueryVariableInterface_N																*/
/*		This function is basically identical to the AxQueryVariable function.  Its only		*/
/*		difference is that it also assigns a flag indicating whether the varible or object	*/
/*		is an interface object.													 			*/
/*																							*/
/*		The executable data pointer passed into this application must have previously been	*/
/*		allocated (i.e. by a previous call to AxQueryExecDataEx).  This ability to re-use	*/
/*		an executable data pointer makes this a useful function to use in situations where	*/
/*		it is necessary to re-query for the same variable (i.e. after a program save)		*/
/*																							*/
/* Parameters:																				*/
/*		pszPath			A string representing a variable or object in an automationX		*/
/*						project																*/
/*		pExecData		The executable data pointer to write the variable or object data	*/
/*						to.  The memory for this must be previously defined.				*/
/*		piInterfaceFlag	An flag indicating whether the requested variable is defined as an	*/
/*						interface variable (1 - Interface Variable, 0 - Not an Interface	*/
/*						Variable)															*/
/*																							*/
/* Return Value:																			*/
/*		0 - Failure	(the variable or object was not found)									*/
/*		1 - Success																			*/
/********************************************************************************************/

AX_EXPORT int AxQueryVariableInterface_N(char* pszPath[],
										 AX_EXEC_DATA pExecData[], 
										 char err[],
										 unsigned nel );

#endif

/********************************************************************************************/
/*	AxQueryVariableExInterface																*/
/*		This function is basically identical to the AxQueryVariableEx function.  Its only	*/
/*		difference is that it also assigns a flag indicating whether the varible or object	*/
/*		is an interface object.													 			*/
/*																							*/
/*		The executable data pointer passed into this application must have previously been	*/
/*		allocated (i.e. by a previous call to AxQueryExecDataEx).  This ability to re-use	*/
/*		an executable data pointer makes this a useful function to use in situations where	*/
/*		it is necessary to re-query for the same variable (i.e. after a program save)		*/
/*																							*/
/* Parameters:																				*/
/*		pProgram		An automationX program object (see axsapi32_program.h)				*/
/*		pszSubPath		A string representing a variable or object within an automationX	*/
/*						program object														*/
/*		pExecData		The executable data pointer to write the variable or object data	*/
/*						to.  The memory for this must be previously defined.				*/
/*		piInterfaceFlag	An flag indicating whether the requested variable is defined as an	*/
/*						interface variable (1 - Interface Variable, 0 - Not an Interface	*/
/*						Variable)															*/
/*																							*/
/* Return Value:																			*/
/*		0 - Failure	(the variable or object was not found)									*/
/*		1 - Success																			*/
/********************************************************************************************/
#if !AX_VER_46ML
/* obsolate
AX_EXPORT int AxQueryVariableExInterface(AX_PROGRAM		pProgram,
										 char			*pszSubPath,
										 AX_EXEC_DATA	pExecData,
										 int			*piInterfaceFlag);
*/
#endif

/********************************************************************************************/
/*	AxFreeExecData																			*/
/*		This function frees the memory that was assigned by calling either the				*/
/*		AxQueryExecData or AxQueryExecDataEx function.							 			*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The executable data memory to free									*/
/*																							*/
/* Return Value:																			*/
/*		None																				*/
/********************************************************************************************/
AX_EXPORT void AxFreeExecData(AX_EXEC_DATA pExecData);

/********************************************************************************************/
/*	AxGet																					*/
/*		This function gets the value of a varaible using its executable data information.	*/
/*		This is more efficient than using AxQueryGet if many reads of the same data are		*/
/*		necessary.																 			*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*		pVt				A union structure where the value of the requested variable will	*/
/*						be written.															*/
/*																							*/
/* Return Value:																			*/
/*		0 - Failure	(the executable data was invalid or did not represent a variable type	*/
/*					 object)																*/
/*		1 - Success																			*/
/********************************************************************************************/
AX_EXPORT int AxGet(AX_EXEC_DATA		pExecData,
					struct tagAxVariant	*pVt);

// Gets the value of variable using a string or a double as value
AX_EXPORT int AxGetValueEx(AX_EXEC_DATA	pExecData,
						   char			*pszBuff,
						   double		*pdValue);

/********************************************************************************************/
/*	AxGetLong																				*/
/*		This function gets the value of an integer type varaible using its executable data	*/
/*		information.																		*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*		plVal			A long integer variable to write the result of the function call to	*/
/*																							*/
/* Return Value:																			*/
/*		0 - Failure	(the executable data or integer pointer passed into the function was	*/
/*					 NULL)																	*/
/*		1 - Success																			*/
/********************************************************************************************/
AX_EXPORT int AxGetLong(AX_EXEC_DATA	pExecData,
						long			*plVal);

/********************************************************************************************/
/*	AxGetLongFromArray																		*/
/*		This function gets the value of an integer type varaible array using its executable */
/*		data information.																	*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*		plVal			A long integer variable to write the result of the function call to	*/
/*		iIndex			The array index position to read the data from in the varaible		*/
/*						array																*/
/*																							*/
/* Return Value:																			*/
/*		0 - Failure	(the executable data or integer pointer passed into the function was	*/
/*					 NULL)																	*/
/*		1 - Success																			*/
/********************************************************************************************/
AX_EXPORT int AxGetLongFromArray(AX_EXEC_DATA	pExecData,
								long			*plVal,
								int				iIndex);

/********************************************************************************************/
/*	AxGetDouble																				*/
/*		This function gets the value of a floating point type varaible using its executable	*/
/*		 data information.																	*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*		pdVal			A double floating point variable to write the result of the 		*/
/*						function call to													*/
/*																							*/
/* Return Value:																			*/
/*		0 - Failure	(the executable data or integer pointer passed into the function was	*/
/*					 NULL)																	*/
/*		1 - Success																			*/
/********************************************************************************************/
AX_EXPORT int AxGetDouble(AX_EXEC_DATA	pExecData,
						  double		*pdVal);

/********************************************************************************************/
/*	AxGetDoubleFromArray																	*/
/*		This function gets the value of a floating point type varaible array using its		*/
/*		executable data information.														*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*		pdVal			A double floating point variable to write the result of the 		*/
/*						function call to													*/
/*		iIndex			The array index position to read the data from in the varaible		*/
/*						array																*/
/*																							*/
/* Return Value:																			*/
/*		0 - Failure	(the executable data or integer pointer passed into the function was	*/
/*					 NULL)																	*/
/*		1 - Success																			*/
/********************************************************************************************/
AX_EXPORT int AxGetDoubleFromArray(AX_EXEC_DATA	pExecData,
									double		*pdVal,
									int			iIndex);

/********************************************************************************************/
/*	AxGetString																				*/
/*		This function gets the value of a string type varaible using its executable			*/
/*		 data information.																	*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*		pszBuff			A character string to write the result of the function	call to		*/
/*		iBuffSize		The maximum number of characters to write into the string			*/
/*																							*/
/* Return Value:																			*/
/*		The number of characters (not including the null terminator) written into the 		*/
/*		pszBuff string																		*/
/********************************************************************************************/
AX_EXPORT int AxGetString(AX_EXEC_DATA	pExecData,
						  char			*pszBuff,
						  int			iBuffSize);

/********************************************************************************************/
/*	AxGetStringFromArray																	*/
/*		This function gets the value of a string type varaible array using its executable	*/
/*		 data information.																	*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*		pszBuff			A character string to write the result of the function	call to		*/
/*		iBuffSize		The maximum number of characters to write into the string			*/
/*		iIndex			The array index position to read the data from in the varaible		*/
/*						array																*/
/*																							*/
/* Return Value:																			*/
/*		The number of characters (not including the null terminator) written into the 		*/
/*		pszBuff string																		*/
/********************************************************************************************/
AX_EXPORT int AxGetStringFromArray(AX_EXEC_DATA	pExecData,
									char		*pszBuff,
									int			iBuffSize,
									int			iIndex);

/********************************************************************************************/
/*	AxGetValueAsString																		*/
/*		This function gets the value of a varaible using its executable	data information.	*/
/*		The data retreived is returned as a character string (i.e. "123.456")				*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*		pszBuff			A character string to write the result of the function	call to		*/
/*																							*/
/* Return Value:																			*/
/*		The string that is written into pszBuff												*/
/********************************************************************************************/
AX_EXPORT char* AxGetValueAsString(AX_EXEC_DATA	pExecData,
								   char			*pszBuff);

/********************************************************************************************/
/*	AxGetArray																				*/
/*		This function gets the value of a varaible array at a specific index position using	*/
/*		its executable data information.													*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*		pVt				A union structure where the value of the requested variable will	*/
/*						be written.															*/
/*		iIndex			The array index position to read the data from in the varaible		*/
/*						array																*/
/*																							*/
/* Return Value:																			*/
/*		0 - Failure	(the executable data was invalid or did not represent a variable type	*/
/*					 object OR the index was out of range)									*/
/*		1 - Success																			*/
/********************************************************************************************/
AX_EXPORT int AxGetArray(AX_EXEC_DATA			pExecData,
						 struct tagAxVariant	*pVt,
						 int					iIndex);


/********************************************************************************************/
/*	AxSet																					*/
/*		This function sets the value of a varaible using its executable data information.	*/
/*		This is more efficient than using AxQuerySet if many writes of the same data are	*/
/*		necessary.																 			*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*		pVt				A union structure where the new value of the requested variable is	*/
/*						stored.																*/
/*																							*/
/* Return Value:																			*/
/*		0 - Failure	(the executable data was invalid or did not represent a variable type	*/
/*					 object)																*/
/*		1 - Success																			*/
/********************************************************************************************/
AX_EXPORT int AxSet(AX_EXEC_DATA		pExecData,
					struct tagAxVariant	*pVt);

// Sets the value of variable using a string or a double as value
// To set with a double Value the char *str_value must be NULL ! 
AX_EXPORT int AxSetValueEx(AX_EXEC_DATA	pExecData,
						   char			*pszStr,
						   double		dValue);

/********************************************************************************************/
/*	AxSetLong																				*/
/*		This function sets the value of an integer type varaible using its executable data	*/
/*		information.															 			*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*		lVal			The value to set the variable to									*/
/*																							*/
/* Return Value:																			*/
/*		0 - Failure	(the executable data was invalid)										*/
/*		1 - Success																			*/
/********************************************************************************************/
AX_EXPORT int AxSetLong(AX_EXEC_DATA	pExecData,
						long			lVal);

/********************************************************************************************/
/*	AxSetLongToArray																		*/
/*		This function sets the value of an integer type varaible array using its executable */
/*		data information.															 		*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*		lVal			The value to set the variable to									*/
/*		iIndex			The array index position to write the data to in the varaible array	*/
/*																							*/
/* Return Value:																			*/
/*		0 - Failure	(the executable data was invalid)										*/
/*		1 - Success																			*/
/********************************************************************************************/
AX_EXPORT int AxSetLongToArray(AX_EXEC_DATA	pExecData,
								long			lVal,
								int				iIndex);

/********************************************************************************************/
/*	AxSetDouble																				*/
/*		This function sets the value of a floating point type varaible using its executable	*/
/*		data information.														 			*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*		dVal			The value to set the variable to									*/
/*																							*/
/* Return Value:																			*/
/*		0 - Failure	(the executable data was invalid)										*/
/*		1 - Success																			*/
/********************************************************************************************/
AX_EXPORT int AxSetDouble(AX_EXEC_DATA	pExecData,
						  double		dVal);

/********************************************************************************************/
/*	AxSetDoubleToArray																		*/
/*		This function sets the value of a floating point type varaible array using its		*/
/*		executable data information.														*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*		dVal			The value to set the variable to									*/
/*		iIndex			The array index position to write the data to in the varaible array	*/
/*																							*/
/* Return Value:																			*/
/*		0 - Failure	(the executable data was invalid)										*/
/*		1 - Success																			*/
/********************************************************************************************/
AX_EXPORT int AxSetDoubleToArray(AX_EXEC_DATA	pExecData,
									double		dVal,
									int			iIndex);

/********************************************************************************************/
/*	AxSetString																				*/
/*		This function sets the value of a character string type varaible using its			*/
/*		executable	data information.											 			*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*		pszStr			The value to set the variable to									*/
/*																							*/
/* Return Value:																			*/
/*		0 - Failure	(the executable data was invalid)										*/
/*		1 - Success																			*/
/********************************************************************************************/
AX_EXPORT int AxSetString(AX_EXEC_DATA	pExecData,
						  char			*pszStr);

/********************************************************************************************/
/*	AxSetStringToArray																		*/
/*		This function sets the value of a character string type varaible array using its	*/
/*		executable	data information.											 			*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*		pszStr			The value to set the variable to									*/
/*		iIndex			The array index position to write the data to in the varaible array	*/
/*																							*/
/* Return Value:																			*/
/*		0 - Failure	(the executable data was invalid)										*/
/*		1 - Success																			*/
/********************************************************************************************/
AX_EXPORT int AxSetStringToArray(AX_EXEC_DATA	pExecData,
									char		*pszStr,
									int			iIndex);

/********************************************************************************************/
/*	AxSetArray																				*/
/*		This function sets the value of a varaible array at a specific index position using	*/
/*		its executable data information.													*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*		pVt				A union structure where the new value of the requested variable is	*/
/*						stored.																*/
/*		iIndex			The array index position to write the data to in the varaible array	*/
/*																							*/
/* Return Value:																			*/
/*		0 - Failure	(the executable data was invalid or did not represent a variable type	*/
/*					 object OR the index was out of range)									*/
/*		1 - Success																			*/
/********************************************************************************************/
AX_EXPORT int AxSetArray(AX_EXEC_DATA		pExecData,
						struct tagAxVariant	*pVt,
						int					iIndex);

/********************************************************************************************/
/*	AxSetAlarm																				*/
/*		This function sets the state and event time of an alarm variable using its			*/
/*		executable data information.														*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The alarm variable's executable data memory							*/
/*		pszPosition		Substitute position text to use for the alarm window position text	*/
/*		pszRemark		Substitute remark text to use for the alarm window remark/comment	*/
/*						text																*/
/*		ucValue			The new status of the alarm (0 or 1)								*/
/*		dTimeStamp		The time stamp to attach to the alarms change of state				*/
/*																							*/
/* Return Value:																			*/
/*		0 - Failure	(the executable data was invalid or did not represent a variable of		*/
/*					 type ALARM)															*/
/*		1 - Success																			*/
/********************************************************************************************/
AX_EXPORT int AxSetAlarm(AX_EXEC_DATA	pExecData,
						 char			*pszPosition,
						 char			*pszRemark,
						 unsigned char	ucValue,
						 double			dTimeStamp);

/********************************************************************************************/
/*	AxGetRemark																				*/
/*		This function gets the remark text configured for the variable using its executable	*/
/*		data information.																	*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*																							*/
/* Return Value:																			*/
/*		A string containing the remark text													*/
/********************************************************************************************/
AX_EXPORT const char*  AxGetRemark(AX_EXEC_DATA pExecData);


/********************************************************************************************/
/*	AxSetExtId																				*/
/*		This function sets the remark text for the variable	using its executable data		*/
/*		information.																		*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*		pRemark			The remark															*/
/*																							*/
/* Return Value:																			*/
/*		0 - Failure	(the variable was not found or the specified name was found but not a	*/
/*					 variable type)															*/
/*		1 - Success	(the variable was found in the project)									*/
/********************************************************************************************/
AX_EXPORT int  AxSetRemark(AX_EXEC_DATA pExecData, char *pRemark);

/********************************************************************************************/
/*	AxGetExtId																				*/
/*		This function gets the ExtID ( Extended ID ) configured for the variable			*/
/*		using its executable data information.												*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*																							*/
/* Return Value:																			*/
/*		A string containing the ExtID														*/
/********************************************************************************************/
AX_EXPORT const char*  AxGetExtId(AX_EXEC_DATA pExecData);


/********************************************************************************************/
/*	AxSetExtId																				*/
/*		This function sets the ExtID ( Extended ID ) configured for the variable			*/
/*		using its executable data information.												*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*		pExtID			The ExtID															*/
/*																							*/
/* Return Value:																			*/
/*		0 - Failure	(the variable was not found or the specified name was found but not a	*/
/*					 variable type)															*/
/*		1 - Success	(the variable was found in the project)									*/
/********************************************************************************************/
AX_EXPORT int  AxSetExtId(AX_EXEC_DATA pExecData, char *pExtID);

/********************************************************************************************/
/*	AxGetName																				*/
/*		This function gets a variable's name text using its executable data information.	*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*																							*/
/* Return Value:																			*/
/*		Failure - NULL (the executable data was invalid)									*/
/*		Success - A string containing the name text											*/
/********************************************************************************************/
AX_EXPORT const char*  AxGetName(AX_EXEC_DATA pExecData);

/********************************************************************************************/
/*	AxGetVarReference																		*/
/*		This function gets the reference name text for a variable that is a reference type	*/
/*		(i.e. VAR_GLOBAL, VAR_INPUT, etc.) using its executable data information.			*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*																							*/
/* Return Value:																			*/
/*		Failure - NULL (the executable data was invalid, the variable was not a reference	*/
/*						type varaible, or the variable was "not connected"					*/
/*		Success - A string containing the reference text									*/
/********************************************************************************************/
AX_EXPORT const char* AxGetVarReference(AX_EXEC_DATA pExecData); 

/********************************************************************************************/
/*	AxGetVarReference																		*/
/*		This function gets the declaration type (i.e. VAR, VAR_INPUT, etc) of a variable	*/
/*		using its executable data information.												*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*																							*/
/* Return Value:																			*/
/*		-1	- Failure (the executable data was invalid)										*/
/*		0	- VAR																			*/
/*		1	- VAR_INPUT																		*/
/*		2	- VAR_OUTPUT																	*/
/*		3	- VAR_IN_OUT																	*/
/*		4	- VAR_EXTERNAL																	*/
/*		5	- VAR_GLOBAL																	*/
/********************************************************************************************/
AX_EXPORT int AxGetVarDeclaration(AX_EXEC_DATA pExecData);

/********************************************************************************************/
/*	AxGetType																				*/
/*		This function gets the basetype (i.e. REAL, UDINT, ALARM, etc.) of a variable using	*/
/*		its executable data information.													*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*																							*/
/* Return Value:																			*/
/*		-1	- Failure (the executable data was invalid)										*/
/*		See the type definitions in axvariant.h												*/
/********************************************************************************************/
AX_EXPORT int AxGetType(AX_EXEC_DATA pExecData );

/********************************************************************************************/
/*	AxGetBaseType																			*/
/*		This function gets the basetype of a variable as a string (i.e. "REAL", "UDINT",	*/
/*		"ALARM", etc.) using its executable data information.								*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*																							*/
/* Return Value:																			*/
/*		"?"	- Failure (the executable data was invalid or the basetype inforamtion was		*/
/*					   unknown)																*/
/*		"BOOL"		- Type AX_BT_BOOL														*/
/*		"BYTE"		- Type AX_BT_BYTE														*/
/*		"SINT"		- Type AX_BT_SINT														*/
/*		"USINT"		- Type AX_BT_USINT														*/
/*		"INT"		- Type AX_BT_INT														*/
/*		"UINT"		- Type AX_BT_UINT														*/
/*		"DINT"		- Type AX_BT_DINT														*/
/*		"UDINT"		- Type AX_BT_UDINT														*/
/*		"REAL"		- Type AX_BT_REAL														*/
/*		"STRING"	- Type AX_BT_STRING														*/
/*		"ALARM"		- Type AX_BT_ALARM														*/
/*		"POINTER"	- Type AX_BT_POINTER													*/
/*		"LREAL"		- Type AX_BT_LREAL														*/
/********************************************************************************************/
AX_EXPORT const char*	AxGetBaseType(AX_EXEC_DATA pExecData);

/********************************************************************************************/
/*	AxIsComplexType																			*/
/*		This function determines whether an object is a complex data type (i.e. a structure	*/
/*		or multi-variable type of some form) using its executable data information.			*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*																							*/
/* Return Value:																			*/
/*		0 - The object is not a complex type or the executable data was invalid				*/
/*		Otherwise - The object defined by the executable data is a complex object type		*/
/********************************************************************************************/
AX_EXPORT int AxIsComplexType(AX_EXEC_DATA pExecData);

/********************************************************************************************/
/*	AxGetComplexTypeName																	*/
/*		This function gets the name of the complex type of a variable using its executable	*/
/*		data information.																	*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*																							*/
/* Return Value:																			*/
/*		0 - The object is not a complex type or the executable data was invalid				*/
/*		Otherwise - The complex type string													*/
/********************************************************************************************/
AX_EXPORT const char *AxGetComplexTypeName(AX_EXEC_DATA pExecData);

/********************************************************************************************/
/*	AxVarIsEnum																				*/
/*		This function determines whether a variable is an enumerator type using its			*/
/*		executable data information.														*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*																							*/
/* Return Value:																			*/
/*		0 - The variable is not an enumerator type or the executable data was invalid		*/
/*		Otherwise - The variable is an enumerator type variable								*/
/********************************************************************************************/
AX_EXPORT int AxVarIsEnum(AX_EXEC_DATA pExecData);

/********************************************************************************************/
/*	AxGetDimension																			*/
/*		This function gets the dimension string of a variable using its executable data		*/
/*		information.																		*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*																							*/
/* Return Value:																			*/
/*		0 - The dimension string is not defined or the executable data was invalid			*/
/*		Otherwise - The dimension string													*/
/********************************************************************************************/
AX_EXPORT const char *AxGetDimension(AX_EXEC_DATA pExecData);

/********************************************************************************************/
/*	AxGetArrayCnt																			*/
/*		This function gets the array count of a variable using its executable data			*/
/*		information.																		*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*																							*/
/* Return Value:																			*/
/*		0 - The executable data was invalid													*/
/*		Otherwise - The array count															*/
/********************************************************************************************/
AX_EXPORT int AxGetArrayCnt(AX_EXEC_DATA pExecData);

/********************************************************************************************/
/*	AxGetDecPoint																			*/
/*		This function gets the number of decimal points defined for a floating point type	*/
/*		variable using its executable data information. automtionX uses the decimal poinst	*/
/*		value when displaying all floating point numbers. The value of the variable is not	*/
/*		actually truncated to to fit this decimal point value.								*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*																							*/
/* Return Value:																			*/
/*		0 - There are not decimal points defined or the executable data was invalid			*/
/*		Otherwise - The defined number of decimal points									*/
/********************************************************************************************/
AX_EXPORT int AxGetDecPoint(AX_EXEC_DATA pExecData);

/********************************************************************************************/
/*	AxGetSubrange																			*/
/*		This function gets the minimum and maximum scale values of any integer or floating	*/
/*		point type variable using its executable data information.  automationX uses these	*/
/*		values as default 0->100% ranges for trending and sliders. The actual engineering	*/
/*		range of a variable may be outside of these numbers. It also gets the number of		*/
/*		decimal points defined for a floating point type variable.							*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*		pdMinScale		The variable to write the minimum engineering scale value into		*/
/*		pdMaxScale		The variable to write the maximum engineering scale value into		*/
/*		piDecimalPoints	The variable to write the decimal point information into			*/
/*																							*/
/* Return Value:																			*/
/*		0 - The executable data was invalid													*/
/*		1 - Success																			*/
/********************************************************************************************/
AX_EXPORT int AxGetSubrange(AX_EXEC_DATA	pExecData,
							double			*pdMinScale,
							double			*pdMaxScale,
							int				*piDecimalPoints);

AX_EXPORT int AxGetScaleFactors(AX_EXEC_DATA	pExecData,
							double			*physOffset,
							double			*physRange,
							double			*scale,
							double			*offset);


/********************************************************************************************/
/*	AxGetSegSize																			*/
/*		This function gets the amount of memory used by this object							*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*																							*/
/* Return Value:																			*/
/*		-1 - The executable data was invalid												*/
/*		Otherwise - The objects memory size													*/
/********************************************************************************************/
AX_EXPORT int AxGetSegSize(AX_EXEC_DATA pExecData);

/********************************************************************************************/
/*	AxGetAlarmInfo																			*/
/*		This function gets the parameter data of an alarm type variable using the variables	*/
/*		executable data information															*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*		piPrio			The variable to write the alarms priority to						*/
/*		piLocked		The variable to write the alarms locked (not displayed) status to	*/
/*		piAck			The variable to write the alarms acknowledged status to				*/
/*		piBeepOn		The variable to write the alarms audible bell on flag to			*/
/*		piJournalOn		The variable to write the alarms journal write enable flag to		*/
/*		piAckNecessary	The variable to write the alarms acknowledge necessary flag to		*/
/*		pszAlarmText	The variable to write the alarms alternate alarm comment text to	*/
/*																							*/
/* Return Value:																			*/
/*		0 - The executable data was invalid, or one of the alarm parameter variables was	*/
/*			NULL, or the variable was not of type ALARM										*/
/*		1 - Success																			*/
/********************************************************************************************/
AX_EXPORT int AxGetAlarmInfo(AX_EXEC_DATA	pExecData,
							 int			*piPrio,
							 int			*piLocked,
							 int			*piAck,
							 int			*piBeepOn,
							 int			*piJournalOn,
							 int			*piAckNecessary,
							 char			*pszAlarmText);

AX_EXPORT int AxGetShortAlarmInfo(void* pExecData, void* vpShortAlarmBit);
AX_EXPORT int AxSetShortAlarmInfo(void* pExecData, void* vpShortAlarmBit, unsigned mask);

AX_EXPORT int AxGetScaleFactors(AX_EXEC_DATA	pExecData,
							double			*physOffset,
							double			*physRange,
							double			*scale,
							double			*offset);


/********************************************************************************************/
/*	AxGetAlarmRaiseTime																			*/
/*		This function gets the raise time of an alarm type variable using the variables	*/
/*		executable data information															*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*																							*/
/* Return Value:																			*/
/*		raise time																				*/
/********************************************************************************************/
AX_EXPORT double AxGetAlarmRaiseTime(AX_EXEC_DATA	pExecData);


/********************************************************************************************/
/*	AxGetAlarmFallingTime																	*/
/*		This function gets the falling time of an alarm type variable using the variables	*/
/*		executable data information															*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*																							*/
/* Return Value:																			*/
/*		falling time																		*/
/********************************************************************************************/
AX_EXPORT double AxGetAlarmFallingTime(AX_EXEC_DATA	pExecData);

/********************************************************************************************/
/*	AxGetAttributes																			*/
/*		This function gets the attributes (described by the AX_ATTR structure) of a			*/
/*		varaible using its executable data information										*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*		pAttr			The structure to write the attribute data into						*/
/*																							*/
/* Return Value:																			*/
/*		0 - The executable data was invalid													*/
/*		1 - Success																			*/
/********************************************************************************************/
AX_EXPORT int AxGetAttributes(AX_EXEC_DATA	pExecData,
							  AX_ATTR		*pAttr);

/********************************************************************************************/
/*	AxGetNcFlag																				*/
/*		This function gets the "not connected" (NC) flag of a varaible using its executable	*/
/*		data information																	*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*																							*/
/* Return Value:																			*/
/*		0 - The executable data was invalid	or the not connected flag is off				*/
/*		1 - The not connected flag is on													*/
/********************************************************************************************/
AX_EXPORT int AxGetNcFlag(AX_EXEC_DATA pExecData);

/********************************************************************************************/
/*	AxGetNcFlag_Subrange_Dimension_Remark													*/
/*		This function gets the "not connected" (NC) flag of a varaible using its executable	*/
/*		data information.  It also gets the minimum and maximum scale values of the			*/
/*		variable, the variables dimension string, and the variables remark string			*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*		pdMinScale		The variable to write the minimum engineering scale value into		*/
/*		pdMaxScale		The variable to write the maximum engineering scale value into		*/
/*		pszDimension	The variable to write the dimension string into						*/
/*		pszRemark		The variable to write the remark string into						*/
/*																							*/
/* Return Value:																			*/
/*		0 - The executable data was invalid	or the variable was not an "I/O" variable		*/
/*		1 - The not connected flag is off													*/
/*		2 - The not connected flag is on													*/
/********************************************************************************************/
AX_EXPORT int AxGetNcFlag_Subrange_Dimension_Remark(AX_EXEC_DATA	pExecData,
													double			*pdMinScale,
													double			*pdMaxScale,
													char			**pszDimension,
													char			**pszRemark);


/********************************************************************************************/
/*	AxGetValidFlag																			*/
/*		This function gets the .VALID parameter of a varaible using its executable data		*/
/*		information.  The valid parameter is used by many automationX classes for alarm and	*/
/*		display functionality																*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*																							*/
/* Return Value:																			*/
/*		-1 - The executable data was invalid												*/
/*		0 - The valid parameter is off														*/
/*		1 - The valid parameter is on														*/
/********************************************************************************************/
AX_EXPORT int AxGetValidFlag(AX_EXEC_DATA pExecData);


/********************************************************************************************/
/*	AxGet*Flag																				*/
/*		The following series of functions retreive the status of the various configuration	*/
/*		flags that are set when a variable is defined in an automationX project.			*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*																							*/
/* Return Value:																			*/
/*		-1 - The executable data was invalid												*/
/*		0 - The flag is off																	*/
/*		1 - The flag is on																	*/
/********************************************************************************************/

#define AxGetTrendignFlag	AxGetTrendingFlag
AX_EXPORT int AxGetTrendingFlag(AX_EXEC_DATA pExecData);
AX_EXPORT int AxGetRetentiveFlag(AX_EXEC_DATA pExecData);
AX_EXPORT int AxGetConstantFlag(AX_EXEC_DATA pExecData);
AX_EXPORT int AxGetPrivateFlag(AX_EXEC_DATA pExecData);
AX_EXPORT int AxGetIOVarFlag(AX_EXEC_DATA pExecData);
AX_EXPORT int AxGetLocalFlag(AX_EXEC_DATA pExecData);
AX_EXPORT int AxGetConfValueFlag(AX_EXEC_DATA pExecData);
AX_EXPORT int AxGetParameterFlag(AX_EXEC_DATA pExecData);
AX_EXPORT int AxGetRemoteFlag(AX_EXEC_DATA pExecData);
AX_EXPORT int AxGetInterfaceFlag(AX_EXEC_DATA pExecData); // do not use this function
AX_EXPORT int AxGetUserFlag(AX_EXEC_DATA pExecData);
AX_EXPORT int AxGetSpecifiedUserFlag(void* pExecData, int iFlagNr);
AX_EXPORT int AxSetUserFlag(void* pExecData, int iValue );
AX_EXPORT int AxSetSpecifiedUserFlag(void* pExecData, int iValue, int iFlagNr );

/********************************************************************************************/
/*	AxSetDecPoint																			*/
/*		This function sets the number of decimal points that automationX will use to		*/
/*		to display a floating point type variable with										*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*		iDecimalPoints	The number of decimal points to configure the variable for			*/
/*																							*/
/* Return Value:																			*/
/*		0 - The executable data was invalid													*/
/*		1 - Success																			*/
/********************************************************************************************/
AX_EXPORT int AxSetDecPoint(AX_EXEC_DATA	pExecData,
							int				iDecimalPoints);

/********************************************************************************************/
/*	AxSetAttributes																			*/
/*		This function sets the attributes (described by the AX_ATTR structure) of a			*/
/*		varaible using its executable data information										*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*		pAttr			The structure to write the attribute data into						*/
/*																							*/
/* Return Value:																			*/
/*		0 - The executable data was invalid													*/
/*		1 - Success																			*/
/********************************************************************************************/
AX_EXPORT int AxSetAttributes(AX_EXEC_DATA	pExecData,
							  AX_ATTR		*pAttr);

/********************************************************************************************/
/*	AxSetNcFlag																				*/
/*		This function sets the "not connected" (NC) flag of a varaible using its executable	*/
/*		data information																	*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*		iNotConnected	The value to set the not connected status of the varaible to		*/
/*																							*/
/* Return Value:																			*/
/*		1 - The executable data was invalid													*/
/*		0 - Success																			*/
/********************************************************************************************/
AX_EXPORT int AxSetNcFlag(AX_EXEC_DATA	pExecData,
						  int			iNotConnected);

/********************************************************************************************/
/*	AxSetNcFlag_Subrange_Dimension_Remark													*/
/*		This function sets the "not connected" (NC) flag of a varaible using its executable	*/
/*		data information.  It also sets the minimum and maximum scale values of the			*/
/*		variable, the variables dimension string, and the variables remark string			*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*		iNotConnected	The value to set the not connected status of the varaible to		*/
/*		dMinScale		The value to set the minimum engineering scale of the variable to	*/
/*		dMaxScale		The value to set the minimum engineering scale of the variable to	*/
/*		pszDimension	The value to set the dimension string of the variable to (this		*/
/*						cannot contain more then 10 characters								*/
/*		pszRemark		The value to set the remark string of the variable to (this value	*/
/*						cannot contain more characters then the previous remark string		*/
/*						contained															*/
/*																							*/
/* Return Value:																			*/
/*		1 - The executable data was invalid													*/
/*		0 - Success																			*/
/********************************************************************************************/
AX_EXPORT int AxSetNcFlag_Subrange_Dimension_Remark(AX_EXEC_DATA	pExecData,
													int				iNotConnected,
													float			*pfMinScale,
													float			*pfMaxScale,
													char			*pszDimension,
													char			*pszRemark);

/********************************************************************************************/
/*	AxSetValidFlag																			*/
/*		This function sets the .VALID parameter of a varaible using its executable data		*/
/*		information.  The valid parameter is used by many automationX classes for alarm and	*/
/*		display functionality																*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*		iValue			The value to set the valid parameter of the variable to				*/
/*																							*/
/* Return Value:																			*/
/*		0 - The executable data was invalid													*/
/*		1 - Success																			*/
/********************************************************************************************/
AX_EXPORT int AxSetValidFlag(AX_EXEC_DATA	pExecData,
							 int			iValue);

/********************************************************************************************/
/*	AxGetExecDataInfo																		*/
/*		This function gets possible debug information of a varaible using its executable	*/
/*		data information.  This function is most often used to get a unique identifier		*/
/*		string representing the variable.													*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*																							*/
/* Return Value:																			*/
/*		A string of length 0 - The executable data was invalid								*/
/*		A string in the form of "Address: %d, Name = %s", where the address number is the	*/
/*			memory address of the variable data, and Name is the variable name string		*/
/********************************************************************************************/
AX_EXPORT char *AxGetExecDataInfo(AX_EXEC_DATA pExecData);

/********************************************************************************************/
/*	AxGetAddressFromExecData																*/
/*		This function gets memory address of the data of a varaible using its executable	*/
/*		data information.																	*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pExecData		The variable's executable data memory								*/
/*																							*/
/* Return Value:																			*/
/*		0 - The executable data was invalid													*/
/*		Otherwise the memory address of the variables data value							*/
/********************************************************************************************/
AX_EXPORT void *AxGetAddressFromExecData(AX_EXEC_DATA pExecData);

/********************************************************************************************/
/*	AxGetSubVarList																			*/
/*		This function returns any sub-variables of the object with the specified executable	*/
/*		data information.																	*/
/*																							*/
/*		Only one sub-variable name string is returned from this function. Successive		*/
/*		sub-variables are found by calling this function in two different ways.  The first	*/
/*		method is to use the pszPreviousVarName parameter.  The function with then return	*/
/*		the first variable it finds after finding the pszPreviousVarName variable.  The		*/
/*		second method involves setting the pszPreviousVarName parameter to NULL and calling	*/
/*		the function many times in succession with the same pParentExecData value.  Using	*/
/*		this method, the function will return each sub-variable of the pParentExecData		*/
/*		object in succession.																*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pParentExecData		The objects's executable data memory							*/
/*		pszPrevousVarName	The variable name found the previous time this function was		*/
/*							called for the pParentExecData object							*/
/*																							*/
/* Return Value:																			*/
/*		0 - The executable data was invalid	or no sub-variable was found, or there are no	*/
/*			more sub-variables in the objects sub-variable list.							*/
/*		Otherwise a sub-variable name string												*/
/********************************************************************************************/
AX_EXPORT char	*AxGetSubVarList(AX_EXEC_DATA	pParentExecData,
								 char			*pszPreviousVar);


/********************************************************************************************/
/*	AxVarDscFromInstance																	*/
/*		This function returns any sub-variable descriptor data of the object with the		*/
/*		specified program instance information (see axsapi32_program.h)						*/
/*																							*/
/*		Only one variable descriptor is returned from this function. Successive	variable	*/
/*		descriptors are found by calling this function using the pPreviousVarDsc parameter.	*/
/*		Set the pPreviousVarDsc to the variable descriptor returned by this function the	*/
/*		last time it was called for the specified program instance							*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pInstance		The parent objects's program instance data							*/
/*		pPrevousVarDsc	The variable descriptor data found the previous time this function	*/
/*						was called for the pInstance program object							*/
/*																							*/
/* Return Value:																			*/
/*		0 - The program instance data was invalid OR there were no variables found OR there	*/
/*			were not more variables to be found after the specifed previous variable		*/
/*		Otherwise a variable descriptor memory pointer										*/
/********************************************************************************************/
AX_EXPORT AX_VAR_DSC AxVarDscFromInstance(AX_INSTANCE	pInstance,
										  AX_VAR_DSC	pPreviousVarDsc);



AX_EXPORT int AxQueryVariableFromInstance_N(AX_INSTANCE instance,
											AX_EXEC_DATA pPrevEcecData,
											AX_EXEC_DATA pExecData[],
											unsigned N );

/********************************************************************************************/
/*	AxVarDscFromInstance_N																	*/
/*		This function returns an array of sub-variable descriptors from the object with the	*/
/*		specified program instance information (see axsapi32_program.h)						*/
/*																							*/
/*		The function will fill the variable descriptor array, pVarDscList, up to the list	*/
/*		size specified by uiMaxListSize or until there are no more variables in the	program	*/
/*		instance object, whichever is smaller.  If there are more variables in the program	*/
/*		instance object then there are positions in the list, the function can be called	*/
/*		successive times with the last variable descriptor found in the previous call being	*/
/*		used for the pPreviousVarDsc parameter.  The calling function is responsible for	*/
/*		creating the variable descriptor list.												*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pInstance		The parent objects's program instance data							*/
/*		pPrevousVarDsc	The variable descriptor data found the previous time this function	*/
/*						was called for the pInstance program object							*/
/*		pVarDscList		A variable descriptor list to write the array of found variable		*/
/*						descriptors to.														*/
/*		uiMaxListSize	The maximum number of elements to write into the variable			*/
/*						descriptor list.													*/
/*																							*/
/* Return Value:																			*/
/*		0 - The program instance data was invalid OR there were no variables found OR there	*/
/*			were not more variables to be found after the specifed previous variable		*/
/*		Otherwise the number of variable descriptors written into the list					*/
/********************************************************************************************/
AX_EXPORT int AxVarDscFromInstance_N(AX_INSTANCE	pInstance,
									 AX_VAR_DSC		pPreviousVarDsc,
									 AX_VAR_DSC		pVarDscList[],
									 unsigned int	uiMaxListSize);

/********************************************************************************************/
/*	AxGetNameFromVarDSC																		*/
/*		This function gets a variable's name text using its variable descriptor				*/
/*		information.																		*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pVarDsc		The variable descriptor data			 								*/
/*																							*/
/* Return Value:																			*/
/*		Failure - NULL (the variable descriptor data was invalid)							*/
/*		Success - A string containing the name text											*/
/********************************************************************************************/
AX_EXPORT const char *AxGetNameFromVarDSC(AX_VAR_DSC pVarDsc);

/********************************************************************************************/
/*	AxGetRemarkFromVarDSC																	*/
/*		This function gets the remark text configured for the variable using its variable	*/
/*		descriptor information.																*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pVarDsc		The variable descriptor data			 								*/
/*																							*/
/* Return Value:																			*/
/*		A string containing the remark text													*/
/********************************************************************************************/
AX_EXPORT const char *AxGetRemarkFromVarDSC(AX_VAR_DSC pVarDsc);

/********************************************************************************************/
/*	AxGetReferenceFromVarDSC																*/
/*		This function gets the reference name text for a variable that is a reference type	*/
/*		(i.e. VAR_GLOBAL, VAR_INPUT, etc.) using its variable descriptor information.		*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pVarDsc		The variable descriptor data			 								*/
/*																							*/
/* Return Value:																			*/
/*		Failure - NULL (the executable data was invalid, the variable was not a reference	*/
/*						type varaible, or the variable was "not connected"					*/
/*		Success - A string containing the reference text									*/
/********************************************************************************************/
AX_EXPORT const char *AxGetReferenceFromVarDSC(AX_VAR_DSC pVarDsc);

/********************************************************************************************/
/*	AxGetNameCRCFromVarDSC																	*/
/*		This function gets the cyclic redundancy check value of the variable's name text	*/
/*		using its variable descriptor information.											*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pVarDsc		The variable descriptor data			 								*/
/*																							*/
/* Return Value:																			*/
/*		0 - the variable descriptor data was invalid										*/
/*		Otherwise - The CRC value of the variable name text									*/
/********************************************************************************************/
AX_EXPORT unsigned short  AxGetNameCRCFromVarDSC(AX_VAR_DSC pVarDsc);

/********************************************************************************************/
/*	AxGetReferenceCRCFromVarDSC																*/
/*		This function gets the cyclic redundancy check value of the variable's reference	*/
/*		text using its variable descriptor information.										*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pVarDsc		The variable descriptor data			 								*/
/*																							*/
/* Return Value:																			*/
/*		0 - the variable descriptor data was invalid										*/
/*		Otherwise - The CRC value of the variable reference text							*/
/********************************************************************************************/
AX_EXPORT unsigned short  AxGetReferenceCRCFromVarDSC(AX_VAR_DSC pVarDsc);

/********************************************************************************************/
/*	AxGetAxTypeFromVarDSC																	*/
/*		This function gets the basetype (i.e. REAL, UDINT, ALARM, etc.) of a variable using	*/
/*		its variable descriptor information.												*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pVarDsc		The variable descriptor data			 								*/
/*																							*/
/* Return Value:																			*/
/*		0	- the variable descriptor data was invalid or the type was unknown				*/
/*		See the type definitions in axvariant.h												*/
/********************************************************************************************/
AX_EXPORT int	AxGetAxTypeFromVarDSC(AX_VAR_DSC pVarDsc);

/********************************************************************************************/
/*	AxGetTypeFromVarDSC																		*/
/*		This function gets the basetype of a variable as a string (i.e. "REAL", "UDINT",	*/
/*		"ALARM", etc.) using its variable descriptor information.							*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pVarDsc		The variable descriptor data			 								*/
/*																							*/
/* Return Value:																			*/
/*		0	- the variable descriptor data was invalid										*/
/*		Otherwise the type string															*/
/********************************************************************************************/
AX_EXPORT const char *AxGetTypeFromVarDSC(AX_VAR_DSC pVarDsc);

/********************************************************************************************/
/*	AXGetDimensionFromVarDSC																*/
/*		This function gets the dimension string of a variable using its variable descriptor	*/
/*		information.																		*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pVarDsc		The variable descriptor data			 								*/
/*																							*/
/* Return Value:																			*/
/*		0 - The dimension string is not defined or the variable descriptor data was invalid	*/
/*		Otherwise - The dimension string													*/
/********************************************************************************************/
AX_EXPORT const char* AXGetDimensionFromVarDSC(AX_VAR_DSC pVarDsc);

/********************************************************************************************/
/*	AxGetArrayCntFromVarDSC																	*/
/*		This function gets the array count of a variable using its variable descriptor		*/
/*		information.																		*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pVarDsc		The variable descriptor data			 								*/
/*																							*/
/* Return Value:																			*/
/*		-1 - The variable descriptor data was invalid										*/
/*		Otherwise - The array count															*/
/********************************************************************************************/
AX_EXPORT int AxGetArrayCntFromVarDSC(AX_VAR_DSC pVarDsc);


/********************************************************************************************/
/*	AxGetEnumText 																			*/
/*		This function gets the enum text of a enum value from ar varibale entry    			*/
/*																							*/
/* Parameters:																				*/
/*		pExecData	: handle of the varibale entry											*/
/*		iEnumId		: is the enum value														*/
/*		pBuffer		: is the pointer to the text buffer										*/
/*		iSize		: size of the text buffer												*/
/*																							*/
/* Return Value:																			*/
/*		1 - if an enum text was found														*/
/*		Otherwise - 0																		*/
/********************************************************************************************/
AX_EXPORT int AxGetEnumText(void* pExecData,int iEnumId,char *pBuffer,int iSize);

/********************************************************************************************/
/*	AxGetSubrangeLowFromVarDSC																*/
/*		This function gets the minimum scale value of any integer or floating point type	*/
/*		variable using its variable descriptor information.  automationX uses this value	*/
/*		values as the default 0% value for sliders and the trend system.  For I/O variables	*/
/*		this value may not be the actual minimum engineering range.  See the				*/
/*		AxGetMinScaleFromVarDSC function													*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pVarDsc		The variable descriptor data			 								*/
/*																							*/
/* Return Value:																			*/
/*		0 - The variable descriptor data was invalid OR the minimum scale value is 0		*/
/*		Otherwise - the minimum scale value													*/
/********************************************************************************************/
AX_EXPORT float  AxGetSubrangeLowFromVarDSC(AX_VAR_DSC pVarDsc);

/********************************************************************************************/
/*	AxGetSubrangeHighFromVarDSC																*/
/*		This function gets the maximum scale value of any integer or floating point type	*/
/*		variable using its variable descriptor information.  automationX uses this value	*/
/*		values as the default 100% value for sliders and the trend system.  For I/O			*/
/*		variables this value may not be the actual maximum engineering range.  See the		*/
/*		AxGetMinScaleFromVarDSC function													*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pVarDsc		The variable descriptor data			 								*/
/*																							*/
/* Return Value:																			*/
/*		0 - The variable descriptor data was invalid OR the maximum scale value is 0		*/
/*		Otherwise - the maximum scale value													*/
/********************************************************************************************/
AX_EXPORT float  AxGetSubrangeHighFromVarDSC(AX_VAR_DSC pVarDsc);

/********************************************************************************************/
/*	AxGetMinScaleFromVarDSC																	*/
/*		This function gets the minimum engineering scale value of any integer or floating	*/
/*		point type	I/O variable using its variable descriptor information.  Some			*/
/*		automationX communication classes use this value as the real minimum engineering	*/
/*		scale value of a variable (which is not necessarily the same as the value returned	*/
/*		from the AxGetSubrangeLowFromVarDSC function).										*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pVarDsc		The variable descriptor data			 								*/
/*																							*/
/* Return Value:																			*/
/*		0 - The variable descriptor data was invalid OR the minimum scale value is 0		*/
/*		Otherwise - the minimum scale value													*/
/********************************************************************************************/
AX_EXPORT double AxGetMinScaleFromVarDSC(AX_VAR_DSC pVarDsc);

/********************************************************************************************/
/*	AxGetMaxScaleFromVarDSC																	*/
/*		This function gets the maximum engineering scale value of any integer or floating	*/
/*		point type	I/O variable using its variable descriptor information.  Some			*/
/*		automationX communication classes use this value as the real maximum engineering	*/
/*		scale value of a variable (which is not necessarily the same as the value returned	*/
/*		from the AxGetSubrangeHighFromVarDSC function).										*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pVarDsc		The variable descriptor data			 								*/
/*																							*/
/* Return Value:																			*/
/*		0 - The variable descriptor data was invalid OR the maximum scale value is 0		*/
/*		Otherwise - the maximum scale value													*/
/********************************************************************************************/
AX_EXPORT double AxGetMaxScaleFromVarDSC(AX_VAR_DSC pVarDsc);

/********************************************************************************************/
/*	AxGetMinIOFromVarDSC																	*/
/*		This function gets the minimum PLC register value associate with an I/O variable	*/
/*		using its variable descriptor information.  Some automationX communication classes	*/
/*		use this value for deriving a real engineering value from a PLC (or other I/O		*/
/*		device) register value.																*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pVarDsc		The variable descriptor data			 								*/
/*																							*/
/* Return Value:																			*/
/*		0 - The variable descriptor data was invalid OR the minimum scale value is 0		*/
/*		Otherwise - the minimum scale value													*/
/********************************************************************************************/
AX_EXPORT double AxGetMinIOFromVarDSC(AX_VAR_DSC pVarDsc);

/********************************************************************************************/
/*	AxGetMaxIOFromVarDSC																	*/
/*		This function gets the maximum PLC register value associate with an I/O variable	*/
/*		using its variable descriptor information.  Some automationX communication classes	*/
/*		use this value for deriving a real engineering value from a PLC (or other I/O		*/
/*		device) register value.																*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pVarDsc		The variable descriptor data			 								*/
/*																							*/
/* Return Value:																			*/
/*		0 - The variable descriptor data was invalid OR the maximum scale value is 0		*/
/*		Otherwise - the minimum scale value													*/
/********************************************************************************************/
AX_EXPORT double AxGetMaxIOFromVarDSC(AX_VAR_DSC pVarDsc);

/********************************************************************************************/
/*	AxGetAlarmInfoFromVarDSC																*/
/*		This function gets the parameter data of an alarm type variable using the variables	*/
/*		variable descriptor information														*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pVarDsc			The variable descriptor data			 							*/
/*		piPrio			The variable to write the alarms priority to						*/
/*		piLocked		The variable to write the alarms locked (not displayed) status to	*/
/*		piAck			The variable to write the alarms acknowledged status to				*/
/*		piBeepOn		The variable to write the alarms audible bell on flag to			*/
/*		piJournalOn		The variable to write the alarms journal write enable flag to		*/
/*		piAckNecessary	The variable to write the alarms acknowledge necessary flag to		*/
/*		pszAlarmText	The variable to write the alarms alternate alarm comment text to	*/
/*																							*/
/* Return Value:																			*/
/*		0 - The variable descriptor data was invalid, or one of the alarm parameter			*/
/*			variables was NULL, or the variable was not of type ALARM						*/
/*		1 - Success																			*/
/********************************************************************************************/
AX_EXPORT int AxGetAlarmInfoFromVarDSC(AX_VAR_DSC	pVarDsc,
									   int			*piPrio,
									   int			*piLocked,
									   int			*piAck,
									   int			*piBeepOn,
									   int			*piJournalOn,
									   int			*piAckNecessary,
									   char const	**pszAlarmText);

/********************************************************************************************/
/*	AxGe*FlagFromVarDSC																		*/
/*		This functions gets the variable flags of a variable using its						*/
/*		variable descriptor information.													*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pVarDsc			The variable descriptor data			 							*/
/*																							*/
/* Return Value:																			*/
/*		-1 - The variable descriptor data was invalid										*/
/*		0 - The flag is off																	*/
/*		1 - The flag is on																	*/
/********************************************************************************************/
AX_EXPORT int AxGetRemoteFlagFromVarDSC(AX_VAR_DSC pVarDsc);
AX_EXPORT int AxGetTrendingFlagFromVarDSC(AX_VAR_DSC pVarDsc);
AX_EXPORT int AxGetRetentiveFlagFromVarDSC(AX_VAR_DSC pVarDsc);
AX_EXPORT int AxGetConstantFlagFromVarDSC(AX_VAR_DSC pVarDsc);
AX_EXPORT int AxGetIOVarFlagFromVarDSC(AX_VAR_DSC pVarDsc);
AX_EXPORT int AxGetLocalFlagFromVarDSC(AX_VAR_DSC pVarDsc);
AX_EXPORT int AxGetConfValueFlagFromVarDSC(AX_VAR_DSC pVarDsc);
AX_EXPORT int AxGetParameterFlagFromVarDSC(AX_VAR_DSC pVarDsc);
AX_EXPORT int AxGetUserFlagFromVarDSC(AX_VAR_DSC pVarDsc);
AX_EXPORT int AxGetInterfaceFlagFromVarDSC(AX_VAR_DSC pVarDsc);

/********************************************************************************************/
/*	AxGetAttributes																			*/
/*		This function gets the configuration flags (described by the AX_FLAGS structure) of	*/
/*		a varaible using its varible descriptor data information							*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pVarDsc			The variable descriptor data			 							*/
/*		pFlags			The structure to write the configuration flag data into				*/
/*																							*/
/* Return Value:																			*/
/*		0 - The executable data was invalid													*/
/*		1 - Success																			*/
/********************************************************************************************/
AX_EXPORT int AxGetFlagsFromVarDSC(AX_VAR_DSC	pVarDsc,
								   AX_FLAGS		*pFlags);
/********************************************************************************************/
/*	AxGe*FlagFromVarDSC																		*/
/*		This functions gets the variable flags of a variable using its						*/
/*		variable descriptor information.													*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pVarDsc			The variable descriptor data			 							*/
/*																							*/
/* Return Value:																			*/
/*		-1 - The variable descriptor data was invalid										*/
/*		0 - The flag is off																	*/
/*		1 - The flag is on																	*/
/********************************************************************************************/
AX_EXPORT int AxGetRemoteFlagFromVarDSC(AX_VAR_DSC pVarDsc);
AX_EXPORT int AxGetTrendingFlagFromVarDSC(AX_VAR_DSC pVarDsc);
AX_EXPORT int AxGetRetentiveFlagFromVarDSC(AX_VAR_DSC pVarDsc);
AX_EXPORT int AxGetConstantFlagFromVarDSC(AX_VAR_DSC pVarDsc);
AX_EXPORT int AxGetIOVarFlagFromVarDSC(AX_VAR_DSC pVarDsc);
AX_EXPORT int AxGetLocalFlagFromVarDSC(AX_VAR_DSC pVarDsc);
AX_EXPORT int AxGetConfValueFlagFromVarDSC(AX_VAR_DSC pVarDsc);
AX_EXPORT int AxGetParameterFlagFromVarDSC(AX_VAR_DSC pVarDsc);
//AX_EXPORT int AxGetUserFlagFromVarDSC(AX_VAR_DSC pVarDsc);
AX_EXPORT int AxGetInterfaceFlagFromVarDSC(AX_VAR_DSC pVarDsc);

/********************************************************************************************/
/*	AxGetVarDeclFromVarDSC																			*/
/*		This function gets the configuration flags (described by the AX_FLAGS structure) of	*/
/*		a varaible using its varible descriptor data information							*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pVarDsc			The variable descriptor data			 							*/
/*		pFlags			The structure to write the configuration flag data into				*/
/*																							*/
/* Return Value:																			*/
/*		0 - The executable data was invalid													*/
/*		1 - Success																			*/
/********************************************************************************************/
AX_EXPORT int AxGetVarDeclFromVarDSC(AX_VAR_DSC dsc);

/********************************************************************************************/
/*	AxGetRemoteParamFromVarDSC																			*/
/*		This function gets the configuration flags (described by the AX_FLAGS structure) of	*/
/*		a varaible using its varible descriptor data information							*/
/*																							*/
/*		Be sure to check the real time database status using AxHasSpsIdChanged before		*/
/*		calling this function.																*/
/*																							*/
/* Parameters:																				*/
/*		pVarDsc			The variable descriptor data			 							*/
/*		pFlags			The structure to write the configuration flag data into				*/
/*																							*/
/* Return Value:																			*/
/*		0 - The executable data was invalid													*/
/*		1 - Success																			*/
/********************************************************************************************/
AX_EXPORT int AxGetRemoteParamFromVarDSC(AX_VAR_DSC dsc);



//#if !AX_VER_46ML

/********************************************************************************************/
/*	AxQc_QueryVariable																		*/
/*																							*/
/* NOTE:																					*/			
/*																							*/
/* Parameters:																				*/
/*																							*/
/* Return Value:																			*/
/*																							*/
/********************************************************************************************/
AX_EXPORT int AxQc_QueryVariable(char* path, AX_EXEC_DATA execData);

/********************************************************************************************/
/*	AxQc_QueryVariable_N																	*/
/*																							*/
/* NOTE:																					*/			
/*																							*/
/* Parameters:																				*/
/*																							*/
/* Return Value:																			*/
/*																							*/
/********************************************************************************************/
AX_EXPORT int AxQc_QueryVariable_N(	char* aPath[], AX_EXEC_DATA pExecData[], 
									char err[], unsigned nel );

/********************************************************************************************/
/*	AxQc_QueryVariableInterface																*/
/*																							*/
/* NOTE:																					*/			
/*																							*/
/* Parameters:																				*/
/*																							*/
/* Return Value:																			*/
/*		0  var found and interface flag is set												*/
/*		1  var not found																	*/
/*		2  var found and interface flag is reset											*/
/*																							*/
/********************************************************************************************/
AX_EXPORT int AxQc_QueryVariableInterface(char* path, AX_EXEC_DATA pExecData);

/********************************************************************************************/
/*	AxQc_QueryVariableInterface_N															*/
/*																							*/
/* NOTE:																					*/			
/*																							*/
/* Parameters:																				*/
/*																							*/
/* Return Value:																			*/
/*																							*/
/********************************************************************************************/
AX_EXPORT int AxQc_QueryVariableInterface_N(char* aPath[], void* aExecData[], 
											char err[], unsigned nel );

/********************************************************************************************/
/*	AxQc_Create																		*/
/*																							*/
/* NOTE:																					*/			
/*																							*/
/* Parameters:																				*/
/*																							*/
/* Return Value:																			*/
/*																							*/
/********************************************************************************************/
AX_EXPORT void* AxQc_Create( //Query_context
									char* buf,
									unsigned buflen,
									unsigned flags	// = 0 --> user processes 
									);

/********************************************************************************************/
/*	AxQc_QueryVariableFromQc																*/
/*																							*/
/* NOTE:																					*/			
/*																							*/
/* Parameters:																				*/
/*																							*/
/* Return Value:																			*/
/*																							*/
/********************************************************************************************/
AX_EXPORT int AxQc_QueryVariableFromQc(void * pqc,	//Query_context
								char* path, 
								AX_EXEC_DATA pExec_data
								);

AX_EXPORT int AxQtree_QueryVariable(void* tree);	// Q_tree

AX_EXPORT int ED_free_index_handle(void* pExec_data);
AX_EXPORT int ED_free_index_handle_N(void* pExec_data, unsigned nel);

///#endif	/* !AX_VER_46ML */

AX_EXPORT int SendDataToMaster(AX_EXEC_DATA pExec_data,void* pval);

AX_EXPORT int AxIsWriteVariable(void* execdata);
AX_EXPORT int AxIsReadVariable(void* execdata);

#endif

