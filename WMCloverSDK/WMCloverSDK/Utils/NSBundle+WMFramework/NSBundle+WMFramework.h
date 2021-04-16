//
//  NSBundle+WMFramework.h
//  WMCloverSDK
//
//  Created by apple on 2021/4/14.
//

#import <UIKit/UIKit.h>

#define WMF_FRAMEWORK_Bundle_Name @"WMCloverSDKResource"

//#define WMF_FrameworkBundle ([NSBundle wmf_FrameworkBundle])

#define ColoverSDKEnable [NSBundle isWMFrameworkEnable]

#define WMF_ResourceBundle ([NSBundle wmf_ResourceBundle])

#define WMF_NibWithName(aNibName) ([NSBundle wmf_LoadNibWithName:aNibName])

#define WMF_ViewWithNibName(aNibName,aIsFirst) ([NSBundle wmf_LoadViewWithNibName:aNibName isFirst:aIsFirst])

@interface NSBundle (WMFramework)

+ (BOOL)isWMFrameworkEnable;

+ (NSBundle*)wmf_ResourceBundle;

+ (UINib*)wmf_LoadNibWithName:(NSString*)aName;

+ (id)wmf_LoadViewWithNibName:(NSString*)aName isFirst:(BOOL)isFirst;

@end
