//
//  SAPILoginManager.h
//  SAPILib
//
//  Created by jinsong on 1/14/15.
//  Copyright (c) 2015 passport. All rights reserved.
//
//  v6.8.3  2015.04.27
//  优化bduss、cookie的处理策略
//
//  v6.8.2  2015.04.21
//  新增错误码定义；优化帐号正常化逻辑
//
//  v6.8.1  2015.04.13
//  新增错误码定义
//
//  v6.8.0  2015.04.09
//  支持无密码注册；增加若干统计事件
//
//  v6.7.11 2015.03.30
//  短信登录界面支持选择互通；调整选择互通跳转到native界面的回调方式

#import <Foundation/Foundation.h>
#import "SAPILoginModel.h"
#import "SAPIDefine.h"

@protocol SAPILoginManagerDelegate;

// 普通登录错误码定义
typedef NS_ENUM(NSUInteger, SAPILoginError) {
    SAPILoginErrorInvalidCaptcha = 10, // 验证码错误
    SAPILoginErrorInvalidPassword = 12, // 密码错误
};

// 手机注册错误码定义
typedef NS_ENUM(NSInteger, SAPIRegisterError) {
    SAPIRegErrorMobileExisted = 8, // 手机号已注册
};

// 快推注册错误码定义
typedef NS_ENUM(NSInteger, SAPIQuickRegisterError) {
    SAPIQRegErrorUsernameExisted = 5, // 用户名已存在
};

typedef NS_ENUM(NSInteger, SAPIAccountType) {
    SAPIAccountTypeDefault = SAPILoginAccountTypeDefault, // 默认情况
    SAPIAccountTypeMobile = SAPILoginAccountTypeMobile, // 登录帐号类型为手机号码格式
    SAPIAccountTypeUsername = SAPILoginAccountTypeUsername, // 登录帐号类型为用户名格式
};

@interface SAPILoginManager : NSObject

@property (nonatomic, weak) id<SAPILoginManagerDelegate> loginDelegate;

/**
 *  此block用于从选择互通的webview跳转回其他native登录界面
 */
@property (nonatomic, copy) void(^switchToNativeInterfaceForLoginBlock)(void);

/**
 *  当前登录帐号类型是用户名或者手机号，
 */
@property (nonatomic, assign) SAPIAccountType accountType;

/**
 *  是否支持无密码注册
 */
@property (nonatomic, assign) BOOL enableNoPwdRegister;

+ (instancetype)sharedManager;

/**
 *  根据用户名、明文密码、验证码（可能为nil）进行常规登录
 *  调用此接口时需实现SAPILoginManagerDelegate所有方法
 *
 *  @param username 用户名
 *  @param password 明文密码
 *  @param captcha  验证码，没有该字段时传入nil
 */
- (void)loginWithUsername:(NSString *)username
                 password:(NSString *)password
                  captcha:(NSString *)captcha;

/**
 *  根据用户名、明文密码、验证码（可能为nil）进行常规登录
 *  调用此接口时需实现SAPILoginManagerDelegate所有方法
 *
 *  @param username    用户名
 *  @param password    明文密码
 *  @param captcha     验证码，没有该字段时传入nil
 *  @param extraParams 透传参数
 */
- (void)loginWithUsername:(NSString *)username
                 password:(NSString *)password
                  captcha:(NSString *)captcha
              extraParams:(NSDictionary *)extraParams;

/**
 *  获取、刷新验证码
 *  成功、失败时均会回调sapiLoginManagerNeedCaptchaForLogin:，成功时返回一个UIImage对象，失败时返回nil
 */
- (void)getCaptchaForLogin;

/**
 *  取消当前所有网络请求
 */
- (void)cancenlAllRequest;

/**
 *  注册时获取手机验证码
 *
 *  @param mobile  手机号
 *  @param success 给手机号下行发送验证码成功时的回调，返回一个内容格式如@{ @"errCode": @"0", @"errMsg": @"" }的键值对
 *  @param failure 给手机号下行发送验证码失败时的回调，返回一个NSError实例
 */
- (void)getVerifyCodeForRegisterWithMobile:(NSString *)mobile
                                   success:(void (^)(NSDictionary *info))success
                                   failure:(void (^)(NSError *error))failure;

/**
 *  通过手机号、密码、验证码注册并登录该帐号
 *  如果要支持无密码注册，可配置enableNoPwdRegister项为YES，同时password可传入nil
 *
 *  @param mobile     手机号
 *  @param password   密码
 *  @param verifyCode 手机验证码
 *  @param success    注册并登录成功时的回调，返回一个SAPILoginModel实例
 *  @param failure    注册、登录失败时的回调，返回一个NSError实例
 */
- (void)registerWithMobile:(NSString *)mobile
                  password:(NSString *)password
                verifyCode:(NSString *)verifyCode
                   success:(void (^)(SAPILoginModel *loginModel))success
                   failure:(void (^)(NSError *error))failure;

/**
 *  通过手机号、密码、验证码注册并登录该帐号
 *  如果要支持无密码注册，可配置enableNoPwdRegister项为YES，同时password可传入nil
 *
 *  @param mobile      手机号
 *  @param password    密码
 *  @param verifyCode  手机验证码
 *  @param extraParams 透传参数
 *  @param success     注册并登录成功时的回调，返回一个SAPILoginModel实例
 *  @param failure     注册、登录失败时的回调，返回一个NSError实例
 */
- (void)registerWithMobile:(NSString *)mobile
                  password:(NSString *)password
                verifyCode:(NSString *)verifyCode
               extraParams:(NSDictionary *)extraParams
                   success:(void (^)(SAPILoginModel *loginModel))success
                   failure:(void (^)(NSError *error))failure;

/**
 *  短信登录获取动态密码需要输入图形验证码时，可通过此方法刷新验证码
 *
 *  @param callback 成功时返回一个UIImage对象，失败时返回nil
 */
- (void)getCaptchaForSMSLogin:(void(^)(UIImage *captchaImage))callback;

@end

@interface SAPILoginManager (SAPILoginManagerRefactorMethods)

/**
 *  根据用户名、明文密码尝试重登录
 *  仅在没有触发反作弊、用户帐号类型不明确等各类其他情况时才能重登录成功
 *  没有用户名、明文密码或已使用SAPI库登录的帐号，可调用SAPILoginSever中的reloginWithUid:success:failure:接口来尝试重登录
 *
 *  @param username 用户名
 *  @param password 明文密码
 *  @param success  登录成功时的回调，返回一个SAPILoginModel实例
 *  @param failure  登录失败时的回调，返回一个NSError实例
 */
- (void)reloginWithUsername:(NSString *)username
                   password:(NSString *)password
                    success:(void (^)(SAPILoginModel *loginModel))success
                    failure:(void (^)(NSError *error))failure;

/**
 *  根据用户名、明文密码尝试重登录（仅支持百度帐号，第三方帐号不支持重登录）
 *
 *  重登录成功时，如果重登录后帐号的uid与当前已登录帐号的uid不一致，则会回调失败，错误码为-710；如果当前未登录或uid一致，则会用重登录得到的信息更新本地信息并回调成功。 <br />
 *  仅在没有触发反作弊、用户帐号类型不明确等各类其他情况时才能重登录成功。 <br />
 *  没有用户名、明文密码或已接入SAPI SDK登录的帐号，可调用reloginWithUid:success:failure:接口来尝试重登录。 <br />
 *
 *  @param username 用户名
 *  @param password 明文密码
 *  @param success  登录成功时的回调，返回一个SAPILoginModel实例
 *  @param failure  登录失败时的回调，返回一个NSError实例,其中domain为错误文案，code为错误码
 *
 */
- (void)reloginIfNeededWithUsername:(NSString *)username
                           password:(NSString *)password
                            success:(void (^)(SAPILoginModel *))success
                            failure:(void (^)(NSError *))failure;

/**
 *  通过手机号获取动态密码
 *  如果命中反作弊策略，需要输入图形验证码，验证码为数字字母组合。
 *
 *  @param mobile  手机号
 *  @param captcha 图形验证码，没有时传nil
 *  @param success 获取成功时的回调，返回一个内容格式如@{ @"errCode": @"0", @"errMsg": @"" }的键值对
 *  @param failure 获取失败时的回调，返回一个NSError实例,其中domain为错误文案，code为错误码；
 *                                  如果需要输入图形验证码，则返回一个UIImage实例，否则返回nil。
 */
- (void)getDpassWithMobile:(NSString *)mobile
                   captcha:(NSString *)captcha
                   success:(void (^)(NSDictionary *info))success
                   failure:(void (^)(UIImage *captchaImage, NSError *error))failure;

/**
 *  根据手机号、动态密码登录
 *
 *  @param mobile      手机号
 *  @param dpass       动态密码，通过getDpassWithMobile:success:failure:获取
 *  @param success     登录成功时的回调，返回一个SAPILoginModel实例
 *  @param failure     登录失败时的回调，返回一个NSError实例
 */
- (void)loginWithMobile:(NSString *)mobile
                  dpass:(NSString *)dpass
                success:(void (^)(SAPILoginModel *loginModel))success
                failure:(void (^)(NSError *error))failure;

/**
 *  根据手机号、动态密码登录
 *
 *  @param mobile      手机号
 *  @param dpass       动态密码，通过getDpassWithMobile:success:failure:获取
 *  @param extraParams 透传参数
 *  @param success     登录成功时的回调，返回一个SAPILoginModel实例
 *  @param failure     登录失败时的回调，返回一个NSError实例
 */
- (void)loginWithMobile:(NSString *)mobile
                  dpass:(NSString *)dpass
            extraParams:(NSDictionary *)extraParams
                success:(void (^)(SAPILoginModel *loginModel))success
                failure:(void (^)(NSError *error))failure;

/**
 *  生成短信内容，用于上行短信注册、登录等操作
 *
 *  @return 生成的短信内容
 */
- (NSString *)getUpwardSMSContentForRegister;

/**
 *  通过上行短信注册并登录帐号
 *
 *  @param sms     上行短信的内容，通过getUpwardSMSContentForRegister接口获取
 *  @param timeout 本次注册、登录操作的超时时间
 *  @param success 注册并登录成功时的回调，返回一个SAPILoginModel实例
 *  @param failure 注册、登录失败时的回调，返回一个NSError实例
 */
- (void)registerBySendSMS:(NSString *)sms
                  timeout:(NSTimeInterval)timeout
                  success:(void (^)(SAPILoginModel *loginModel))success
                  failure:(void (^)(NSError *error))failure;

/**
 *  通过上行短信注册并登录帐号
 *
 *  @param sms          上行短信的内容，通过getUpwardSMSContentForRegister接口获取
 *  @param timeout      本次注册、登录操作的超时时间
 *  @param extraParams  透传参数
 *  @param success      注册并登录成功时的回调，返回一个SAPILoginModel实例
 *  @param failure      注册、登录失败时的回调，返回一个NSError实例
 */
- (void)registerBySendSMS:(NSString *)sms
                  timeout:(NSTimeInterval)timeout
              extraParams:(NSDictionary *)extraParams
                  success:(void (^)(SAPILoginModel *loginModel))success
                  failure:(void (^)(NSError *error))failure;

@end

@protocol SAPILoginManagerDelegate <NSObject>

// 调用普通登录界面时以下所有回调均需实现
@required
/**
 *  登录成功时的回调，返回一个SAPILoginModel实例
 */
- (void)sapiLoginManagerDidLoginSucceed:(SAPILoginModel *)model;
/**
 *  登录失败时的回调，返回一个NSError实例
 */
- (void)sapiLoginManagerDidLoginFailed:(NSError *)error;
/**
 *  登录需要输入验证码，获取成功时返回一个UIImage对象，失败时返回nil
 */
- (void)sapiLoginManagerNeedCaptchaForLogin:(UIImage *)captchaImage;
/**
 *  登录需要用户确认当前的登录帐号类型是手机号还是用户名
 */
- (void)sapiLoginManagerNeedConfirmAccountTypeForLogin;
/**
 *  登录触发了两步验证等需要通过进入H5页面来完成登录操作
 */
- (void)sapiLoginManagerNeedAdditionalActionForLogin:(NSString * )urlString;

@end
