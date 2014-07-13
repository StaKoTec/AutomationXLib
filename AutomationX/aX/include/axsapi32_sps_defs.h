#ifndef _AX_SPS_DEFS_H_
#define _AX_SPS_DEFS_H_

// DONT CHANGE NOTHING HERE (OR YOU HAVE TO CHANGE FB-LIB Create_Process)

#ifdef __cplusplus
extern "C" {
#endif

#ifndef True
#define True 1
#define False 0
#endif
#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

#define SIDE_W 	0
#define SIDE_N 	1
#define SIDE_E 	2
#define SIDE_S 	3

#define CLASSID_DUMMY 0

#define FBLIB_CLIENT_SUPP 0x01
#define FBLIB_DEPEND_SUPP 0x02

// calc sizeof(struct_def) in sizeof(void*) 
#define BLOCK_SIZE_OF(struct_def) (((sizeof(struct_def)+sizeof(void*)-1)&~(sizeof(void*)-1))/sizeof(void*))
 	
#define AXFB_GET_EXECDATA_PARAM(par_index)	AxFb_getVardsc(program, (par_index))
#define AXFB_GET_LONG_PARAM(par_index)		AxFb_getLong(AXFB_GET_EXECDATA_PARAM(par_index))
#define AXFB_GET_FLOAT_PARAM(par_index)		AxFb_getFloat(AXFB_GET_EXECDATA_PARAM(par_index))
#define AXFB_GET_BIT_PARAM(par_index)		(AxFb_getLong(AXFB_GET_EXECDATA_PARAM(par_index)) ? 1 :0)

typedef struct
{
	char in_out_type;
	unsigned char base_type;
	char* var_type;
}SpsFuncArgDsc;

typedef struct
{
	double value;
	char inverted;
	char must_change;
}SpsDependencyArgDsc;

typedef struct
{
	int num_arg;
	int output_on;
	int output_sel;
	SpsDependencyArgDsc args[50];
}SpsDependencyFuncDsc;

#define SPS_FB_DLL_FORMAT 3

typedef struct SpsFunctionDsc
{	
	int  (*depend_func)(SpsDependencyFuncDsc* dsc);
	char* name;
	const SpsFuncArgDsc* arg_list;
	short arg_cnt;
	short priority;
	int  (*master_func)();
	int  (*client_func)();
}SpsFunctionDsc;


#ifdef __cplusplus
}
#endif

#endif
