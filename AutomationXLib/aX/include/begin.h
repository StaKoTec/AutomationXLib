#if !linux

#undef  AX_EXT_CLASS
#define AX_EXT_CLASS __declspec(dllimport)

#undef  AX_EXT_API
#define AX_EXT_API __declspec(dllimport)

#undef  AX_EXT_DATA
#define AX_EXT_DATA __declspec(dllimport)

#else 

#undef  AX_EXT_CLASS 
#define AX_EXT_CLASS 

#undef  AX_EXT_API
#define AX_EXT_API 

#undef  AX_EXT_DATA
#define AX_EXT_DATA 

#endif 
