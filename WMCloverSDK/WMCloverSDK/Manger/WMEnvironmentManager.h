//
//  WMEnvironmentManager.h
//  WMCloverSDK
//
//  Created by apple on 2021/4/14.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#define WMEnvironment_Base_URL      ([[WMEnvironmentManager defaultManager] wmf_Base_URL])
#define WMEnvironment_PKI_URL       ([[WMEnvironmentManager defaultManager] wmf_PKI_URL])
#define WMEnvironment_QRCODE_URL    ([[WMEnvironmentManager defaultManager] wmf_QRCODE_URL])
#define WMEnvironment_BURYPOINT_URL ([[WMEnvironmentManager defaultManager] wmf_BURYPOINT_URL])
#define WMEnvironment_SAFA_URL ([[WMEnvironmentManager defaultManager] wmf_SAFA_URL])

/**
 *  运行环境
 */
typedef NS_ENUM(NSInteger,WMFEnvironment) {
    
    WMFEnvironment_DEV = 0,/* dev环境 <==> 威马智行的Dev(Dev、Test) */
    
    WMFEnvironment_QA = 1,/* QA环境 <==> 威马智行的QA */
    
    WMFEnvironment_PP = 2,/* PP环境 <==> 威马智行的UAT */

    WMFEnvironment_P = 3,/* P环境 <==> 威马智行的Prod */
    
    WMFEnvironment_DEMO = 4,/* DEMO环境 <==> xxxxxx */
    
    WMFEnvironment_JKX = 5,/* 即客行 <==> */
};

UIKIT_EXTERN NSAttributedStringKey const _Nonnull NotificationName_WMEnvironmentChanged;

@interface WMEnvironmentManager : NSObject

@property (nonatomic , assign, readonly) WMFEnvironment currentEnvironment;
@property (nonatomic , strong, readonly) NSDictionary *_Nonnull currentEnvironmentDictionary;
//@property (nonatomic , assign, readonly) BOOL isInSDK;/* sdk内部使用 */

+ (WMEnvironmentManager*_Nonnull)defaultManager;

#pragma mark ==================================================
#pragma mark == 外部接口
#pragma mark ==================================================
- (void)changeEnvironment:(WMFEnvironment)aEnvironment;

- (NSString*_Nonnull)currentEnvironmentString;


#pragma mark ==================================================
#pragma mark == 资源
#pragma mark ==================================================
/* 好像程序没用到了 */
- (NSString* _Nullable)wmf_sourcePath_wm_icenter_cer;

- (NSString* _Nullable)wmf_sourcePath_WMCA_plist;

/* 好像程序没用到了 */
- (NSString* _Nullable)wmf_sourcePath_NLSSA0_dat;


#pragma mark ==================================================
#pragma mark == URL
#pragma mark ==================================================
- (NSString*_Nonnull)wmf_Base_URL;

- (NSString*_Nonnull)wmf_PKI_URL;

- (NSString*_Nonnull)wmf_QRCODE_URL;

- (NSString*_Nonnull)wmf_BURYPOINT_URL;

- (NSString*_Nonnull)wmf_SAFA_URL;

#pragma mark ==================================================
#pragma mark == UUID
#pragma mark ==================================================
- (NSString*_Nonnull)wmf_uuid_identifier;

- (NSString*_Nonnull)wmf_uuid_env;

#pragma mark ==================================================
#pragma mark == K_TspPub_Cert
#pragma mark ==================================================
/* 好像程序没用到了 */
- (NSString*_Nonnull)wmf_K_TspPub_Cert;

#pragma mark ==================================================
#pragma mark == 第三方平台的Key
#pragma mark ==================================================
- (NSString*_Nonnull)wmf_WXShareAppKey;

- (NSString*_Nonnull)wmf_WXShareAppId;

- (NSString*_Nonnull)wmf_WXUniversalLink;

- (NSString*_Nonnull)wmf_BaiduMapAppKey;

- (NSString*_Nonnull)wmf_JPushAppKey;

@end
