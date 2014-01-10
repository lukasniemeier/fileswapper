

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Fri Jan 10 22:38:35 2014
 */
/* Compiler settings for FileSwapperState.idl:
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

#ifndef __FileSwapperState_i_h__
#define __FileSwapperState_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IFileSwapperStateHandler_FWD_DEFINED__
#define __IFileSwapperStateHandler_FWD_DEFINED__
typedef interface IFileSwapperStateHandler IFileSwapperStateHandler;

#endif 	/* __IFileSwapperStateHandler_FWD_DEFINED__ */


#ifndef __FileSwapperStateHandler_FWD_DEFINED__
#define __FileSwapperStateHandler_FWD_DEFINED__

#ifdef __cplusplus
typedef class FileSwapperStateHandler FileSwapperStateHandler;
#else
typedef struct FileSwapperStateHandler FileSwapperStateHandler;
#endif /* __cplusplus */

#endif 	/* __FileSwapperStateHandler_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IFileSwapperStateHandler_INTERFACE_DEFINED__
#define __IFileSwapperStateHandler_INTERFACE_DEFINED__

/* interface IFileSwapperStateHandler */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IFileSwapperStateHandler;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B65E08C7-C9A0-448E-A5F8-D101D21EA1E5")
    IFileSwapperStateHandler : public IUnknown
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IFileSwapperStateHandlerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFileSwapperStateHandler * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFileSwapperStateHandler * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFileSwapperStateHandler * This);
        
        END_INTERFACE
    } IFileSwapperStateHandlerVtbl;

    interface IFileSwapperStateHandler
    {
        CONST_VTBL struct IFileSwapperStateHandlerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFileSwapperStateHandler_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFileSwapperStateHandler_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFileSwapperStateHandler_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFileSwapperStateHandler_INTERFACE_DEFINED__ */



#ifndef __FileSwapperStateLib_LIBRARY_DEFINED__
#define __FileSwapperStateLib_LIBRARY_DEFINED__

/* library FileSwapperStateLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_FileSwapperStateLib;

EXTERN_C const CLSID CLSID_FileSwapperStateHandler;

#ifdef __cplusplus

class DECLSPEC_UUID("D8B8ADC6-FD0D-41E0-82B5-5D2024510574")
FileSwapperStateHandler;
#endif
#endif /* __FileSwapperStateLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


