#ifndef QPOINTER_H
#define QPOINTER_H

#ifdef __cplusplus
extern "C" {
#endif

#define Q_EXPORT extern
 

Q_EXPORT int QStrcmp( char* s1, char* s2);
Q_EXPORT int QStrncmp( char* s1, char* s2,int );

#define QInsertPointerNoCheck(list,ptr)         _InsertPointerNoCheck((void**)list,(void*)ptr)
#define QInsertPointer(list,ptr)                _InsertPointer((void**)list,(void*)ptr)
#define QInsertPointerAfter(list,ptr,after)     _InsertPointerAfter((void**)list,(void*)ptr,(void*)after)
#define QInsertPointerAt(list,ptr,at)           _InsertPointerAt((void**)list,(void*)ptr,(int)at)
#define QPointerExist(list,ptr)                 _PointerExist((void**)list,(void*)ptr)
#define QNumOfPointers(list)                    _NumOfPointers((void**)list)
#define QPointerOffset(list,ptr)                _PointerOffset((void**)list,(void*)ptr)
#define QPointerAtOffset(list,at)               _PointerAtOffset((void**)list,(int)at)
#define QRemovePointer(list,ptr)                _RemovePointer((void**)list,(void*)ptr)
#define QRemoveAllPointers(list)                _RemoveAllPointers((void**)list)
#define QRemovePointerAtOffset(list,at)         _RemovePointerAtOffset((void**)list,(int)at)
#define QInvertPointerList(list)                _InvertPointerList((void**)list)
#define QShiftPointerUp(list,ptr)               _ShiftPointerUp((void**)list,(void*)ptr)
#define QShiftPointerDown(list,ptr)             _ShiftPointerDown((void**)list,(void*)ptr)
#define QBringPointerUp(list,ptr)               _BringPointerUp((void**)list,(void*)ptr)
#define QPushPointerDown(list,ptr)             	_PushPointerDown((void**)list,(void*)ptr)
#define QSwapPointer(list,ptr1,ptr2)            _SwapPointer((void**)list,(void*)ptr1,(void*)ptr2)


Q_EXPORT int QMemBlockSize(void** mem_block);

#define QMemBlockCapacity(mem_block,type)       (QMemBlockSize(mem_block)/sizeof(type))
#define QMalloc(elm_type,n)                     (elm_type*)QAlloc(sizeof(elm_type)*n)

#define QFree(mem_block)                        _QFree(mem_block)

//static void (*QAllocMemErrHandler)(int size);

Q_EXPORT void     QFlushFreeList();
Q_EXPORT void*     QRealloc(void* block,int new_size);
Q_EXPORT void*     _QFree(void* mblock);
Q_EXPORT char*    QAllocString(char* text);
Q_EXPORT char* QAllocCachedString(char* text);
Q_EXPORT char*    QAlloc(int size);
Q_EXPORT char*    QAllocRaw(int size);
Q_EXPORT void** 	QAllocExpandable(int elm_size);
Q_EXPORT void** QFreeExpandable(void** block);
#define QReplaceString(text,new_text)  (text= (QFree(text)||1)?QAllocString(new_text):0)

Q_EXPORT int QGetStringIndexInArray(char** list, char* name);
Q_EXPORT int QFindStringInArray(char** list, char* name);
Q_EXPORT char** QFreeStringArray(char** list);
Q_EXPORT char** QAllocStringInArray(char** list,char* str);

Q_EXPORT void**   _InsertPointerNoCheck(void**,void*);
Q_EXPORT void**   _InsertPointer(void**,void*);
Q_EXPORT int      _PointerExist(void**,void*);
Q_EXPORT void**   _InsertPointerAfter(void**,void*,void*);
Q_EXPORT int      _NumOfPointers(void**);
Q_EXPORT int      _PointerOffset(void**,void*);
Q_EXPORT void*    _PointerAtOffset(void**,int);
Q_EXPORT void**   _RemovePointer(void**,void*);
Q_EXPORT void**   _RemoveAllPointers(void**);
Q_EXPORT void**   _RemovePointerAtOffset(void**,int);
Q_EXPORT void**   _InvertPointerList(register void** list);
Q_EXPORT void**   _ShiftPointerUp(register void** list,register void* ptr);
Q_EXPORT void**   _ShiftPointerDown(register void** list,register void* ptr);
Q_EXPORT void**   _BringPointerUp(register void** list,register void* ptr);
Q_EXPORT void**   _PushPointerDown(register void** list,register void* ptr);
Q_EXPORT void**   _InsertPointerAt(void** list,void* ptr,int pos);
Q_EXPORT void**   _SwapPointer(void** list,void* ptr1,void* ptr2);

Q_EXPORT int QStringTable_GetOffset(register char*** list,register char* ptr); 
Q_EXPORT int QStringTable_Dump(register char*** list,register char* ptr); 
Q_EXPORT int QStringTable_Destroy(register char*** list);
Q_EXPORT char* QStringTable_GetStringAtOffset(register char*** list,int req_offset);
Q_EXPORT unsigned int QCreateSearchKey(char* name);


#ifdef __cplusplus
}
#endif

#endif //QPOINTER_H

