/* /////////////////////////////////////////////////////////////////////////////
//
//                  INTEL CORPORATION PROPRIETARY INFORMATION
//     This software is supplied under the terms of a license agreement or
//     nondisclosure agreement with Intel Corporation and may not be copied
//     or disclosed except in accordance with the terms of that agreement.
//          Copyright(c) 2001-2014 Intel Corporation. All Rights Reserved.
//
//             Intel(R) Integrated Performance Primitives
//             Core (ippCore)
//
*/

#if !defined( __IPPCORE_H__ ) || defined( _OWN_BLDPCS )
#define __IPPCORE_H__

#if defined (_WIN32_WCE) && defined (_M_IX86) && defined (__stdcall)
  #define _IPP_STDCALL_CDECL
  #undef __stdcall
#endif

#ifndef __IPPDEFS_H__
  #include "ippdefs.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif


#if !defined( _IPP_NO_DEFAULT_LIB )
  #if defined( _IPP_SEQUENTIAL_DYNAMIC )
    #pragma comment( lib, __FILE__ "/../../lib/" _INTEL_PLATFORM "ippcore" )
  #elif defined( _IPP_SEQUENTIAL_STATIC )
    #pragma comment( lib, __FILE__ "/../../lib/" _INTEL_PLATFORM "ippcoremt" )
  #elif defined( _IPP_PARALLEL_DYNAMIC )
    #pragma comment( lib, __FILE__ "/../../lib/" _INTEL_PLATFORM "threaded/ippcore" )
  #elif defined( _IPP_PARALLEL_STATIC )
    #pragma comment( lib, __FILE__ "/../../lib/" _INTEL_PLATFORM "threaded/ippcoremt" )
  #endif
#endif


typedef enum {
    ippAffinityCompactFineCore, /* KMP_AFFINITY=granularity=fine,compact,n,offset, where n - level */
    ippAffinityCompactFineHT,   /* KMP_AFFINITY=granularity=fine,compact,0,offset */
    ippAffinityAllEnabled,      /* KMP_AFFINITY=respect */
    ippAffinityRestore,
    ippTstAffinityCompactFineCore, /* test mode for affinity type ippAffinityCompactFineCore */
    ippTstAffinityCompactFineHT    /* test mode for affinity type ippAffinityCompactFineHT   */
} IppAffinityType;


/* /////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//                   Functions declarations
////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippGetLibVersion
//  Purpose:    getting of the library version
//  Returns:    the structure of information about version
//              of ippcore library
//  Parameters:
//
//  Notes:      not necessary to release the returned structure
*/
IPPAPI( const IppLibraryVersion*, ippGetLibVersion, (void) )


/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippGetStatusString
//  Purpose:    convert the library status code to a readable string
//  Parameters:
//    StsCode   IPP status code
//  Returns:    pointer to string describing the library status code
//
//  Notes:      don't free the pointer
*/
IPPAPI( const char*, ippGetStatusString, ( IppStatus StsCode ) )


/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippGetCpuType
//  Purpose:    detects Intel(R) processor
//  Parameter:  none
//  Return:     IppCpuType
//
*/

IPP_DEPRECATED("is deprecated: use ippGetCpuFeatures() function instead of this one")\
IPPAPI( IppCpuType, ippGetCpuType, (void) )

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippGetCpuClocks
//  Purpose:    reading of time stamp counter (TSC) register value
//  Returns:    TSC value
//
//  Note:      An hardware exception is possible if TSC reading is not supported by
/              the current chipset
*/

IPPAPI( Ipp64u, ippGetCpuClocks, (void) )


/* ///////////////////////////////////////////////////////////////////////////
//  Names:  ippSetFlushToZero,
//          ippSetDenormAreZero.
//
//  Purpose: ippSetFlushToZero enables or disables the flush-to-zero mode,
//           ippSetDenormAreZero enables or disables the denormals-are-zeros
//           mode.
//
//  Arguments:
//     value       - !0 or 0 - set or clear the corresponding bit of MXCSR
//     pUMask      - pointer to user store current underflow exception mask
//                   ( may be NULL if don't want to store )
//
//  Return:
//   ippStsNoErr              - Ok
//   ippStsCpuNotSupportedErr - the mode is not supported
*/

IPPAPI( IppStatus, ippSetFlushToZero, ( int value, unsigned int* pUMask ))
IPPAPI( IppStatus, ippSetDenormAreZeros, ( int value ))



/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippAlignPtr
//  Purpose:    pointer aligning
//  Returns:    aligned pointer
//
//  Parameter:
//    ptr        - pointer
//    alignBytes - number of bytes to align
//
*/
IPPAPI( void*, ippAlignPtr, ( void * ptr, int alignBytes ) )

/* /////////////////////////////////////////////////////////////////////////////
//                   Functions to allocate and free memory
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippMalloc
//  Purpose:    64-byte aligned memory allocation
//  Parameter:
//    len       number of bytes
//  Returns:    pointer to allocated memory
//
//  Notes:      the memory allocated by ippMalloc has to be free by ippFree
//              function only.
*/

IPPAPI( void*, ippMalloc,  (int length) )


/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippFree
//  Purpose:    free memory allocated by the ippMalloc function
//  Parameter:
//    ptr       pointer to the memory allocated by the ippMalloc function
//
//  Notes:      use the function to free memory allocated by ippMalloc
*/
IPPAPI( void, ippFree, (void* ptr) )


/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippStaticInit
//  Purpose:    Automatic switching to best for current cpu library code using.
//  Returns:
//   ippStsNoErr       - the best code (static) successfully set
//   ippStsNonIntelCpu - px version (static) of code was set
//   ippStsNoOperationInDll - function does nothing in the dynamic version of the library
//
//  Parameter:  nothing
//
//  Notes:      At the moment of this function execution no any other IPP function
//              has to be working
*/
IPP_DEPRECATED("is deprecated: use ippInit() function instead of this one")\
IPPAPI( IppStatus, ippStaticInit, ( void ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippInit
//  Purpose:    Automatic switching to best for current cpu library code using.
//  Returns:
//   ippStsNoErr
//
//  Parameter:  nothing
//
//  Notes:      At the moment of this function execution no any other IPP function
//              has to be working
*/
IPPAPI( IppStatus, ippInit, ( void ))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippInitCpu
//  Purpose:    switching to user defined target cpu library code using
//
//  Returns:
//   ippStsNoErr       - required target cpu library code is successfully set
//   ippStsCpuMismatch - required target cpu library can't be set, the previous
//                       set is used
//  Parameter:  IppCpuType
//
//  Notes:      At the moment of this function execution no any other IPP function
//              has to be working
*/
IPP_DEPRECATED("is deprecated: use ippSetCpuFeatures() function instead of this one")\
IPPAPI( IppStatus, ippInitCpu, ( IppCpuType cpu ) )


/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippEnableCpu
//  Purpose:    allows dispatching CPU specific IPP library. It doesn't dispatch the code.
//              The following call ippInit(), if it follows ippEnableCpu, does that if application
//              is executed on CPU enabled platform or CPU simulator.
//              Introducing this function in IPP 6.1 was needed to allow IPP users run the codes
//              with Intel(R) AVX instructions in the case they have an Intel(R) AVX-enabled hardware
//              or simulator
//
//  Returns:
//   ippStsNoErr
//
//  Parameter:  IppCpuType
//
//  Notes: The ippInit() call without calling ippEnableCpu() as well as ippEnableCpu
//         without ippInit() call will not dispatch Intel(R) AVX code, even if you run code on Intel(R) AVX
//         enabled platform. Call the functions sequentially:
//         ippEnableCpu(ippCpuAVX); ippInit(); to dispatch Intel(R) AVX code.
//         The function works and could be useful for ippCpuAVX processor type only.
//
*/
IPP_DEPRECATED("is deprecated. This function is obsolete and will be removed in one of the future IPP releases. Use the following link for details: https://software.intel.com/sites/products/ipp-deprecated-features-feedback/")\
IPPAPI( IppStatus, ippEnableCpu, ( IppCpuType cpu ) )


/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippGetCpuFreqMhz
//
//  Purpose:    the function estimates cpu frequency and returns
//              its value in MHz as a integer
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         null pointer to the freq value
//    ippStsSizeErr            wrong num of tries, internal var
//  Arguments:
//    pMhz                     pointer to the integer to write
//                             cpu freq value estimated
//
//  Notes:      no exact value is guaranteed, the value could
//              vary with cpu workloading
*/

IPPAPI(IppStatus, ippGetCpuFreqMhz, ( int* pMhz ) )

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippSetNumThreads
//
//  Purpose:
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNoOperation        For static library internal threading is not supported
//    ippStsSizeErr            Desired number of threads less or equal zero
//
//  Arguments:
//    numThr                   Desired number of threads
*/
IPP_DEPRECATED("is deprecated. This function is obsolete and will be removed in one of the future IPP releases. Use the following link for details: https://software.intel.com/sites/products/ipp-deprecated-features-feedback/")\
IPPAPI( IppStatus, ippSetNumThreads, ( int numThr ) )

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippGetNumThreads
//
//  Purpose:
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         Pointer to numThr is Null
//    ippStsNoOperation        For static library internal threading is not supported
//                             and return value is always == 1
//
//  Arguments:
//    pNumThr                  Pointer to memory location where to store current numThr
*/
IPP_DEPRECATED("is deprecated. This function is obsolete and will be removed in one of the future IPP releases. Use the following link for details: https://software.intel.com/sites/products/ipp-deprecated-features-feedback/")\
IPPAPI( IppStatus, ippGetNumThreads, (int* pNumThr) )

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippGetMaxCacheSizeB
//
//  Purpose:  Detects maximal from the sizes of L2 or L3 in bytes
//
//  Return:
//    ippStsNullPtrErr         The result's pointer is NULL.
//    ippStsNotSupportedCpu    The cpu is not supported.
//    ippStsUnknownCacheSize   The cpu is supported, but the size of the cache is unknown.
//    ippStsNoErr              Ok
//
//  Arguments:
//    pSizeByte                Pointer to the result
//
//  Note:
//    1). Intel(R) processors are supported only.
//    2). Intel(R) Itanium(R) processors and platforms with Intel XScale(R) technology are unsupported
//    3). For unsupported processors the result is "0",
//        and the return status is "ippStsNotSupportedCpu".
//    4). For supported processors the result is "0",
//        and the return status is "ippStsUnknownCacheSize".
//        if sizes of the cache is unknown.
//
*/
IPPAPI( IppStatus, ippGetMaxCacheSizeB, ( int* pSizeByte ) )

/*
//  Name:       ippGetNumCoresOnDie
//  Purpose:    to distinguish MultiCore processors from other
//  Returns:    number of cores
//
*/
IPP_DEPRECATED("is deprecated. This function is obsolete and will be removed in one of the future IPP releases. Use the following link for details: https://software.intel.com/sites/products/ipp-deprecated-features-feedback/")\
IPPAPI( int, ippGetNumCoresOnDie,( void ))

/*
//  Name:       ippGetCpuFeatures
//  Purpose:    Detects CPU features.
//  Parameters:
//    pFeaturesMask   Pointer to the features mask.
//                    Nonzero value of bit means the corresponding feature is supported.
//                    Features mask values are defined in the ippdefs.h
//                      [ 0] - MMX        ( ippCPUID_MMX   )
//                      [ 1] - SSE        ( ippCPUID_SSE   )
//                      [ 2] - SSE2       ( ippCPUID_SSE2  )
//                      [ 3] - SSE3       ( ippCPUID_SSE3  )
//                      [ 4] - SSSE3      ( ippCPUID_SSSE3 )
//                      [ 5] - MOVBE      ( ippCPUID_MOVBE )
//                      [ 6] - SSE41      ( ippCPUID_SSE41 )
//                      [ 7] - SSE42      ( ippCPUID_SSE42 )
//                      [ 8] - AVX        ( ippCPUID_AVX   )
//                      [ 9] - ENABLEDBYOS( ippAVX_ENABLEDBYOS )
//                      [10] - AES        ( ippCPUID_AES   )
//                      [11] - PCLMULQDQ  ( ippCPUID_CLMUL )
//                      [12] - ABR        ( ippCPUID_ABR )
//                      [13] - RDRAND     ( ippCPUID_RDRAND )
//                      [14] - F16C       ( ippCPUID_F16C )
//                      [15] - AVX2       ( ippCPUID_AVX2 )
//                      [16] - ADOX/ADCX  ( ippCPUID_ADCOX )      ADCX and ADOX instructions
//                      [17] - RDSEED     ( ippCPUID_RDSEED )     The RDSEED instruction
//                      [18] - PREFETCHW  ( ippCPUID_PREFETCHW )  The PREFETCHW instruction
//                      [19] - SHA        ( ippCPUID_SHA )        Intel (R) SHA Extensions
//                      [20:63] - Reserved
//
//    pCpuidInfoRegs  Pointer to the 4-element vector.
//                    Result of CPUID.1 are stored in this vector.
//                      [0] - register EAX
//                      [1] - register EBX
//                      [2] - register ECX
//                      [3] - register EDX
//                    If pointer pCpuidInfoRegs is set to NULL, registers are not stored.
//
//  Returns:
//    ippStsNullPtrErr         The pointer to the features mask (pFeaturesMask) is NULL.
//    ippStsNotSupportedCpu    CPU is not supported.
//    ippStsNoErr              Ok
//
//  Note: Only IA-32 and Intel(R) 64 are supported
*/
IPPAPI( IppStatus, ippGetCpuFeatures, ( Ipp64u* pFeaturesMask,
                                        Ipp32u  pCpuidInfoRegs[4] ) )

/*
//  Name:       ippGetEnabledCpuFeatures
//  Purpose:    Detects enabled features for loaded libraries
//  Returns:    Features mask
//                    Features mask values are defined in the ippdefs.h
//                      [ 0] - ippCPUID_MMX
//                      [ 1] - ippCPUID_SSE
//                      [ 2] - ippCPUID_SSE2
//                      [ 3] - ippCPUID_SSE3
//                      [ 4] - ippCPUID_SSSE3
//                      [ 5] - ippCPUID_MOVBE
//                      [ 6] - ippCPUID_SSE41
//                      [ 7] - ippCPUID_SSE42
//                      [ 8] - ippCPUID_AVX
//                      [ 9] - ippAVX_ENABLEDBYOS
//                      [10] - ippCPUID_AES
//                      [11] - ippCPUID_CLMUL
//                      [12] - ippCPUID_ABR
//                      [13] - ippCPUID_RDRAND
//                      [14] - ippCPUID_F16C
//                      [15] - ippCPUID_AVX2
//                      [16] - ippCPUID_ADCOX 
//                      [17] - ippCPUID_RDSEED
//                      [18] - ippCPUID_PREFETCHW 
//                      [19] - ippCPUID_SHA 
//                      [20:63] - Reserved
//
*/
IPPAPI( Ipp64u, ippGetEnabledCpuFeatures, ( void ) )

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippSetCpuFeatures
//
//  Purpose: Changes the set of enabled/disabled CPU features.  
//           This function sets the processor-specific code of the Intel IPP 
//           library according to the processor features specified in cpuFeatures.
//
//  Return:
//    ippStsNoErr                 No errors.
//    Warnings:
//    ippStsFeatureNotSupported   Current CPU doesn't support at least 1 of the
//                                desired features;
//    ippStsUnknownFeature        At least one of the desired features is unknown;
//    ippStsFeaturesCombination   Wrong combination of features;
//    ippStsCpuMismatch           Indicates that the specified processor features
//                                are not valid. Previously set code is used.
//
//  Arguments:
//    cpuFeatures                 Desired features to support by the library 
//                                (see ippdefs.h for ippCPUID_XX definition)
//
//  NOTE:       this function can re-initializes dispatcher and after the 
//              call another library (letter) may work
//  CAUTION:    At the moment of this function excecution no any other IPP 
//              function has to be working
//
//  The next pre-defined sets of features can be used:
//  32-bit code:
// #define PX_FM ( ippCPUID_MMX | ippCPUID_SSE )
// #define W7_FM ( PX_FM | ippCPUID_SSE2 )
// #define V8_FM ( W7_FM | ippCPUID_SSE3 | ippCPUID_SSSE3 )
// #define S8_FM ( V8_FM | ippCPUID_MOVBE )
// #define P8_FM ( V8_FM | ippCPUID_SSE41 | ippCPUID_SSE42 | ippCPUID_AES | ippCPUID_CLMUL | ippCPUID_SHA )
// #define G9_FM ( P8_FM | ippCPUID_AVX | ippAVX_ENABLEDBYOS | ippCPUID_RDRAND | ippCPUID_F16C )
// #define H9_FM ( G9_FM | ippCPUID_AVX2 | ippCPUID_MOVBE | ippCPUID_ADCOX | ippCPUID_RDSEED | ippCPUID_PREFETCHW )
// 
// 64-bit code:
// #define PX_FM ( ippCPUID_MMX | ippCPUID_SSE | ippCPUID_SSE2 )
// #define M7_FM ( PX_FM | ippCPUID_SSE3 )
// #define N8_FM ( S8_FM )
// #define U8_FM ( V8_FM )
// #define Y8_FM ( P8_FM )
// #define E9_FM ( G9_FM )
// #define L9_FM ( H9_FM )
// 
*/

IPPAPI( IppStatus, ippSetCpuFeatures,( Ipp64u cpuFeatures ))

/* /////////////////////////////////////////////////////////////////////////////
//                   i18n functions to operate with Message Catalogs
///////////////////////////////////////////////////////////////////////////// */

#if !defined( _OWN_BLDPCS )
   DECLARE_IPPCONTEXT( IppMsgCatalog );
   #if defined (_WIN32)
   typedef unsigned short* IppMsg;
   #else
     typedef char* IppMsg;
   #endif
#endif /* _OWN_BLDPCS */

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippMessageCatalogOpenI18n
//  Purpose:    Opens i18n Message Catalog
//  Parameters:
//
//  Returns:
//    ippStsMemAllocErr
//    ippStsNullPtrErr
//    ippStsI18nUnsupportedErr
//    ippStsI18nMsgCatalogOpenErr
//    ippStsNoErr
//
//  Notes: function allocates memory, this memory has to be freed by ippMessageCatalogCloseI18n
//         ippMessageCatalogCloseI18n It should be used, despite of the returned status code
*/
IPP_DEPRECATED("is deprecated. This function is obsolete and will be removed in one of the future IPP releases. Use the following link for details: https://software.intel.com/sites/products/ipp-deprecated-features-feedback/")\
IPPAPI( IppStatus, ippMessageCatalogOpenI18n, ( IppMsgCatalog** pMsgCatalog ) )

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippMessageCatalogCloseI18n
//  Purpose:    Closes i18n Message Catalog, which was opened by ippMessageCatalogOpenI18n
//  Parameters:
//
//  Returns:
//  ippStsContextMatchErr
//  ippStsNullPtrErr
//  ippStsI18nMsgCatalogCloseErr
//  ippStsI18nUnsupportedErr
//
//  Notes:
*/
IPP_DEPRECATED("is deprecated. This function is obsolete and will be removed in one of the future IPP releases. Use the following link for details: https://software.intel.com/sites/products/ipp-deprecated-features-feedback/")\
IPPAPI( IppStatus, ippMessageCatalogCloseI18n, ( IppMsgCatalog* pMsgCatalog ) )

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippGetMessageStatusI18n
//  Purpose:    gets localized message corresponding to IppStatus
//  Parameters:
//  Returns:
//    ippStsMemAllocErr
//    ippStsNullPtrErr
//    ippStsContextMatchErr
//    ippStsI18nMsgCatalogInvalid
//    ippStsI18nGetMessageFail
//    ippStsUnknownStatusCodeErr
//
//  Notes:
//
*/
IPP_DEPRECATED("is deprecated. This function is obsolete and will be removed in one of the future IPP releases. Use the following link for details: https://software.intel.com/sites/products/ipp-deprecated-features-feedback/")\
IPPAPI( IppStatus, ippGetMessageStatusI18n, ( const IppMsgCatalog* pMsgCatalog, IppStatus StsCode, IppMsg* pMsg ) )

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippStatusToMessageIdI18n
//  Purpose:    transforms of IPP status to message ID for Message Catalog
//  Parameters:
//    StsCode   IPP status code
//
//  Returns:    Message ID for i18n catalogs
//
//  Notes:      Function is useful for direct Message Catalogs access
//
*/
IPP_DEPRECATED("is deprecated. This function is obsolete and will be removed in one of the future IPP releases. Use the following link for details: https://software.intel.com/sites/products/ipp-deprecated-features-feedback/")\
IPPAPI( Ipp32u, ippStatusToMessageIdI18n, ( IppStatus StsCode ) )

/* ///////////////////////////////////////////////////////////////////////////
Name:
ippSetAffinity
  Purpose:
    Binds OpenMP threads to OS processors.
  Parameters:
           affType  Type of affinity settings, the possible values:
           ippAffinityCompactFineCore
           ippAffinityCompactFineHT
           ippAffinityRestore
           ippTstAffinityCompactFineCore
           ippTstAffinityCompactFineHT
           offset  - Specified the starting position for thread assignment.
  Returns:
     ippStsNoErr            - no errors.
     ippStsLLADisabled      - Low Level Affinity API was disabled.
     ippStsNotSupportedCpu  - the cpu is not supported.
*/

IPP_DEPRECATED("is deprecated. This function is obsolete and will be removed in one of the future IPP releases. Use the following link for details: https://software.intel.com/sites/products/ipp-deprecated-features-feedback/")\
IPPAPI(IppStatus, ippSetAffinity,(IppAffinityType aType, int offset))


#if defined (_IPP_STDCALL_CDECL)
  #undef  _IPP_STDCALL_CDECL
  #define __stdcall __cdecl
#endif

#ifdef __cplusplus
}
#endif

#endif /* __IPPCORE_H__ */
