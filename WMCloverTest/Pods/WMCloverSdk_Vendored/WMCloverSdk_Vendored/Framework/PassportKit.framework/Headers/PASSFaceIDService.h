//
//  PASSFaceIDService.h
//  PassportKit
//
//  Created by jiangzhenjie on 2018/6/7.
//  Copyright © 2018年 Baidu Passport. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 人脸状态

 - PASSFaceIDStatusUnknown: 未知
 - PASSFaceIDStatusAvailable: 人脸可用，可直接调起刷脸验证
 - PASSFaceIDStatusUnregister: 未注册人脸，需调注册接口
 - PASSFaceIDStatusUnBindMobile: 未绑定手机
 */
typedef NS_ENUM(NSInteger, PASSFaceIDStatus) {
    PASSFaceIDStatusUnknown,
    PASSFaceIDStatusAvailable,
    PASSFaceIDStatusUnregister,
    PASSFaceIDStatusUnBindMobile,
};

// 网盘二级密码
FOUNDATION_EXPORT NSString * const PASSFaceIDSceneNetdisk2Pwd;
// 通用刷脸开关
FOUNDATION_EXPORT NSString * const PASSFaceIDSceneLoginSwitch;

/**
 刷脸配置参数
 */
@interface PASSFaceRecognConfig : NSObject

/**
 调起刷脸的源ViewController，一般为当前Controller。不可为空
 */
@property (nonatomic, strong) UIViewController *sourceViewController;

/**
 是否显示默认的刷脸引导页，默认为显示
 */
@property (nonatomic, assign) BOOL showGuidePage;

/**
 场景参数，不能为空
 */
@property (nonatomic, copy) NSString *scene;

/**
 子产品线标识，没有时传空即可
 */
@property (nonatomic, copy, nullable) NSString *subpro;

/**
 透传参数，可空
 */
@property (nonatomic, copy, nullable) NSDictionary *transParams;

@end

/**
 人脸检查接口结果
 */
@interface PASSFaceIDCheckResult : NSObject

/**
 人脸状态
 */
@property (nonatomic, assign, readonly) PASSFaceIDStatus status;

/**
 提示信息
 */
@property (nonatomic, copy, nullable, readonly) NSString *errMsg;

/**
 人脸帐号ID（加密的UID）
 */
@property (nonatomic, copy, nullable, readonly) NSString *livingUname;

/**
 授权凭证
 */
@property (nonatomic, copy, nullable, readonly) NSString *authsid;

/**
 验证控件地址
 */
@property (nonatomic, copy, nullable, readonly) NSString *authWidgetURL;

@end

@interface PASSFaceLoginStatus : PASSFaceIDCheckResult

/**
 刷脸开关是否开启
 */
@property (nonatomic, assign, readonly) BOOL faceLoginEnabled;

@end

@interface PASSFaceIDService : NSObject

/**
 检测当前用户人脸状态

 @param loginModel 登录模型，不可为空
 @param success 成功时回调
 @param failure 失败时回调
 */
- (void)checkUserFaceIDWithLoginModel:(SAPILoginModel *)loginModel
                              success:(void(^)(PASSFaceIDCheckResult *result))success
                              failure:(void(^)(PASSError *error))failure;

/**
 检测当前用户人脸状态

 @param loginModel 登录模型，不可为空
 @param extraParams 透传参数
 @param success 成功时回调
 @param failure 失败时回调
 */
- (void)checkUserFaceIDWithLoginModel:(SAPILoginModel *)loginModel
                          extraParams:(nullable NSDictionary *)extraParams
                              success:(void(^)(PASSFaceIDCheckResult *result))success
                              failure:(void(^)(PASSError *error))failure;

/**
 人脸录入接口

 @param loginModel 登录模型，不可为空
 @param config 刷脸配置参数，不可为空
 @param result 人脸状态检测结果，不可为空
 @param success 人脸录入成功时回调
 @param failure 人脸录入失败时回调
 */
- (void)registerUserFaceIDWithLoginModel:(SAPILoginModel *)loginModel
                        faceRecognConfig:(PASSFaceRecognConfig *)config
                             checkResult:(PASSFaceIDCheckResult *)result
                                 success:(void(^)(NSDictionary *info))success
                                 failure:(void(^)(PASSError *error))failure;

/**
 人脸验证接口

 @param loginModel 登录模型（对于实名刷脸验证，不可为空；对于非实名刷脸验证，可为空）
 @param config 刷脸配置参数，不可为空
 @param livingUname 人脸帐号ID（加密的UID）（对于实名刷脸验证，可空；对于非实名刷脸验证，不可为空）
 @param success 人脸验证通过时，回调成功
 @param failure 人脸验证失败或者发生其他错误时，回调失败
 */
- (void)verifyUserFaceIDWithLoginModel:(nullable SAPILoginModel *)loginModel
                      faceRecognConfig:(PASSFaceRecognConfig *)config
                           livingUname:(nullable NSString *)livingUname
                               success:(void(^)(NSDictionary *info))success
                               failure:(void(^)(PASSError *error))failure;

/**
 刷脸开关接口

 @param model        登录模型，不可为空
 @param callbackKey  人脸验证接口中返回，关闭时不用传
 @param open         打开/关闭 刷脸开关
 @param success      打开/关闭 刷脸开关，成功时回调
 @param failure      打开/关闭 刷脸开关，失败时回调
 */
- (void)switchFaceloginWithModel:(SAPILoginModel *)model
                     callbackKey:(nullable NSString *)callbackKey
                            open:(BOOL)open
                         success:(void(^)(NSDictionary *info))success
                         failure:(void(^)(PASSError *error))failure;


/**
 查询人脸登录开关状态
 
 @param loginModel 登录模型，不可为空
 @param extraParams 透传参数
 @param success 成功时回调
 @param failure 失败时回调
 */
- (void)faceLoginStatusWithLoginModel:(SAPILoginModel *)loginModel
                          extraParams:(nullable NSDictionary *)extraParams
                              success:(void(^)(PASSFaceLoginStatus *result))success
                              failure:(void(^)(PASSError *error))failure;

@end

NS_ASSUME_NONNULL_END
