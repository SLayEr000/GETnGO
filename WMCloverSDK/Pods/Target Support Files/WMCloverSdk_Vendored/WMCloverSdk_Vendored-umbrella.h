#ifdef __OBJC__
#import <UIKit/UIKit.h>
#else
#ifndef FOUNDATION_EXPORT
#if defined(__cplusplus)
#define FOUNDATION_EXPORT extern "C"
#else
#define FOUNDATION_EXPORT extern
#endif
#endif
#endif

#import "CatchCrash.h"
#import "SecKeyTools.h"
#import "WeiMaTool.h"
#import "SecureSDKManager.h"
#import "JitDefines.h"
#import "JitKCBase64.h"
#import "SSDKLib.h"

FOUNDATION_EXPORT double WMCloverSdk_VendoredVersionNumber;
FOUNDATION_EXPORT const unsigned char WMCloverSdk_VendoredVersionString[];

