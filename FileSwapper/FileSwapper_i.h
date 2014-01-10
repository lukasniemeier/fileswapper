

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Fri Jan 10 21:45:55 2014
 */
/* Compiler settings for FileSwapper.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __FileSwapper_i_h__
#define __FileSwapper_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IFileSwapper_FWD_DEFINED__
#define __IFileSwapper_FWD_DEFINED__
typedef interface IFileSwapper IFileSwapper;

#endif 	/* __IFileSwapper_FWD_DEFINED__ */


#ifndef __FileSwapper_FWD_DEFINED__
#define __FileSwapper_FWD_DEFINED__

#ifdef __cplusplus
typedef class FileSwapper FileSwapper;
#else
typedef struct FileSwapper FileSwapper;
#endif /* __cplusplus */

#endif 	/* __FileSwapper_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IFileSwapper_INTERFACE_DEFINED__
#define __IFileSwapper_INTERFACE_DEFINED__

/* interface IFileSwapper */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IFileSwapper;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8119CB34-CD9B-4E5F-B632-6C6BBEA5CE1D")
    IFileSwapper : public IUnknown
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IFileSwapperVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFileSwapper * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFileSwapper * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFileSwapper * This);
        
        END_INTERFACE
    } IFileSwapperVtbl;

    interface IFileSwapper
    {
        CONST_VTBL struct IFileSwapperVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFileSwapper_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFileSwapper_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFileSwapper_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFileSwapper_INTERFACE_DEFINED__ */



#ifndef __FileSwapperLib_LIBRARY_DEFINED__
#define __FileSwapperLib_LIBRARY_DEFINED__

/* library FileSwapperLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_FileSwapperLib;

EXTERN_C const CLSID CLSID_FileSwapper;

#ifdef __cplusplus

class DECLSPEC_UUID("9EEBD123-D499-47C1-AA58-F1C5FF795BB8")
FileSwapper;
#endif
#endif /* __FileSwapperLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


