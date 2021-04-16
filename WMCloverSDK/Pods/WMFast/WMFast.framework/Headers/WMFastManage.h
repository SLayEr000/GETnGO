//
//  WMFastManage.h
//  Fansbot
//
//  Created by 杨康 on 2021/3/11.
//

#import <Foundation/Foundation.h>

//contentType 请求参数格式
//requestType 请求方式
typedef NSString* _Nullable  (^SignSuccess) (NSString * _Nullable url,NSDictionary * _Nullable query,NSDictionary * _Nullable header,NSDictionary * _Nullable body,NSDictionary * _Nullable formData,NSString * _Nullable contentType,NSString * _Nullable requestType);
typedef NSString* _Nullable  (^SignBack) (NSString * _Nullable preSign);

/// 定义一个HTTPBaseUrl的字符串类型作为枚举类型
typedef NSString *HTTPBaseUrl NS_STRING_ENUM;
/// 声明以下枚举值
/// qa_base_url
FOUNDATION_EXPORT HTTPBaseUrl const _Nonnull QA_FAT_URL;
/// pp_base_url
FOUNDATION_EXPORT HTTPBaseUrl const _Nonnull PP_UAT_URL;
/// p_base_url
FOUNDATION_EXPORT HTTPBaseUrl const _Nonnull P_PROD_URL;
/// dev_base_url
FOUNDATION_EXPORT HTTPBaseUrl const _Nonnull DEV_URL;

NS_ASSUME_NONNULL_BEGIN

@interface WMFastManage : NSObject


/// 进入威马快捷模块UI_参数初始化
/// @param baseUrl 请求环境
/// @param vin vin号
/// @param accountId 用户ID
/// @param wmtoken 用户token
/// @param deviceId 设备id
/// @param signSuccess  签名回调
+(void)WMFast:(HTTPBaseUrl)baseUrl
          vin:(NSString *)vin
    accountId:(NSString *)accountId
      wmtoken:(NSString *)wmtoken
     deviceId:(NSString *)deviceId
     signBack:(SignSuccess)signSuccess;





/// 进入威马快捷模块UI_参数初始化
/// @param baseUrl 请求环境
/// @param vin vin号
/// @param accountId 用户ID
/// @param wmtoken 用户token
/// @param deviceId 设备id
/// @param signBack  签名回调
+(void)WMFast2:(HTTPBaseUrl)baseUrl
          vin:(NSString *)vin
    accountId:(NSString *)accountId
      wmtoken:(NSString *)wmtoken
     deviceId:(NSString *)deviceId
     signBack:(SignBack)signBack;

@end

NS_ASSUME_NONNULL_END
