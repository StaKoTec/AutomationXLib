/*
 * $Log: /AutomationX/src/libraries/axfunc/AXPtrArray.h $
 * 
 * 2     18.02.00 14:10 Apreitler
 * 
 * 1     1.09.99 17:54 Apreitler
 * 
 * 5     23.08.99 16:45 Sklug
 * 
 * 4     12.07.99 9:51 Sklug
 * 
 * 3     14.05.99 14:42 Sklug
 * 
 * 2     30.03.99 22:08 Sklug
 * #1286
 * 
 * 1     29.03.99 19:56 Sklug
 */

#ifndef _AXPTRARRAY_H
#define _AXPTRARRAY_H


class AX_EXT_API CAXPtrArray
{
private:
	void**			m_ppTable;
	unsigned long	m_ulUpperBound;
	unsigned long	m_ulSize;

	void*			m_pPtr;

protected:
public:


private:
protected:
public:
	CAXPtrArray();
	CAXPtrArray(void** ppList);
	~CAXPtrArray();

	//access-functions
	unsigned long GetSize(void);
	unsigned long GetUpperBound(void);

	
	//needed func.
	long Add(void* pPtr);
	
	long SetAt(unsigned long ulIndex, void* pPtr);
	void* GetAt(unsigned long ulIndex);
	
	long InsertAt(unsigned long ulIndex, void* pPtr);
	long RemoveAt(unsigned long ulIndex);
	long RemoveAt(unsigned long ulIndex, unsigned long ulCount);
	void FreeAll(void);

	long SetAtGrow(unsigned long ulIndex, void* pPtr);
	
	//operators
	void*& operator []( unsigned long ulIndex );
	unsigned long operator []( void* pPtr ) const;
	
	void*** GetTableAddress(void) { return &m_ppTable; };
};


#endif