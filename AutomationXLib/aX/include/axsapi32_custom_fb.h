#ifndef _AX_CUSTOM_FB_H_
#define _AX_CUSTOM_FB_H_

#ifdef __cplusplus
extern "C" {
#endif

//
// axfb defines and interface functions 
//

typedef void** (*InitLibrary)(void**);

AX_EXPORT void** AxFb_initLibrary(char* Name,char* Pixmap_name);
AX_EXPORT void AxFb_initBlock(char* Name,char* Button_name,char* Header,
							 char* Button_pixmap,int Header_inside,int Header_dynamic,
							 int Init_width,int InternalVars,int LocalVars,int ClientFuncSupp);

AX_EXPORT void AxFb_initPriority(int PrioRange,int DefPrio);

AX_EXPORT void AxFb_initConn(char* Header,int Input_type,char* Type,int Side,int Min,int Max,
					        char* Default_input,int Pointer_type,int Generate_name);


AX_EXPORT void AxCreate_sps_lib(InitLibrary initlib);

#if WIN32
#define INIT_LIBRARY(LibName,Name,Pixmap_name)	\
DLL_EXPORT void** QmLoadInitLibrary(void** Lib_tree) {	\
	Lib_tree = AxFb_initLibrary(Name,Pixmap_name);
#else
#define INIT_LIBRARY(LibName,Name,Pixmap_name)	\
void** QmLoadInitLibrary(void** Lib_tree) {	\
	Lib_tree = AxFb_initLibrary(Name,Pixmap_name);
#endif

#define END_LIBRARY return Lib_tree; } 

#define INIT_BLOCK(Name,Button_name,class_id,Header,Button_pixmap,Header_inside,Header_dynamic,Init_width,InternalVars,LocalVars,ClientFuncSupp) \
	AxFb_initBlock(Name,Button_name,Header,Button_pixmap,\
		Header_inside,Header_dynamic,Init_width,InternalVars,LocalVars,ClientFuncSupp);

#define INIT_PRIORITY(PrioRange,DefPrio) AxFb_initPriority(PrioRange,DefPrio);

#define DUMMY_BLOCK 

#define INIT_CONNECTION(Header,Input_type,Type,Side,Min,Max,Default_input,Pointer_type,Generate_name) \
AxFb_initConn(Header,Input_type,Type,Side,Min,Max,Default_input,Pointer_type,Generate_name);


//
// axfb user's defines and interface functions 
//
#define AX_EXEC_CODE void*

AX_EXPORT int AxFb_getArgCount(AX_EXEC_CODE pProgram);

AX_EXPORT AX_EXEC_DATA AxFb_getVardsc(AX_EXEC_CODE pProgram, int num_par);

AX_EXPORT void* AxFb_getCustomData(AX_EXEC_CODE pProgram,int num_par);


AX_EXPORT int AxFb_getLong(AX_EXEC_DATA pExecData);

AX_EXPORT double AxFb_getFloat(AX_EXEC_DATA pExecData);

AX_EXPORT int AxFb_getSpsId();

AX_EXPORT double AxFb_getTime();

#ifdef __cplusplus
}
#endif

#endif
