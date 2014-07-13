#if !linux

#ifndef _WIN32
#define _WIN32
#endif

#undef  AX_EXT_CLASS
#define AX_EXT_CLASS __declspec(dllexport)

#undef  AX_EXT_API
#define AX_EXT_API __declspec(dllexport)

#undef  AX_EXT_DATA
#define AX_EXT_DATA __declspec(dllexport)

#else // ifdef _WIN32

#undef  AX_EXT_CLASS
#define AX_EXT_CLASS 

#undef  AX_EXT_API
#define AX_EXT_API 

#undef  AX_EXT_DATA
#define AX_EXT_DATA 


#endif // ifdef _WIN32

