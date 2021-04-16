//
//  PASSRouter.h
//  PassportKit
//
//  Created by jiangzhenjie on 2017/7/20.
//  Copyright © 2017年 Baidu Passport. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 PASS路由器，主要用于处理PASS相关功能跳转
 */
@interface PASSRouter : NSObject

@end

/**
 处理二维码扫码结果
 */
@interface PASSRouter (PASSQRCode)

/**
 是否能处理二维码内容
 
 @param content 二维码内容
 @return 能处理时返回YES，其他情况返回NO
 */
+ (BOOL)canHandleQRCodeContent:(NSString *)content;

/**
 处理二维码内容，打开相应页面
 
 @param content 二维码内容
 @param nav 导航栏控制器，内部固定使用 push 打开页面
 @param handler 需要打开登录页回调
 */
+ (void)handleQRCodeContent:(NSString *)content rootVC:(UINavigationController *)nav presentLoginVCHandler:(void(^)(NSDictionary *params))handler;

/**
 处理二维码内容，打开相应页面
 
 @param content 二维码内容
 @param nav 导航栏控制器，内部固定使用 push 打开页面
 @param handler 需要打开登录页回调
 @param completion 处理完成回调（目前只有二维码登录会回调）
 */
+ (void)handleQRCodeContent:(NSString *)content rootVC:(UINavigationController *)nav presentLoginVCHandler:(void(^)(NSDictionary *params))handler completionHandler:(void(^)(NSDictionary *info))completion;

@end

@protocol PASSOpenURLHandleDelegate;
/**
 处理App调起及回跳
 */
@interface PASSRouter (PASSOpenURL)

+ (BOOL)canHandleOpenURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication;

+ (BOOL)canHandleOpenURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey, id> *)options NS_AVAILABLE_IOS(9_0);

+ (BOOL)handleOpenURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication delegate:(id<PASSOpenURLHandleDelegate>)delegate;

+ (BOOL)handleOpenURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey, id> *)options delegate:(id<PASSOpenURLHandleDelegate>)delegate NS_AVAILABLE_IOS(9_0);

@end

/**
 处理PASS SDK端能力调用
 */
@interface PASSRouter (PASSAbility)

/**
 调起PASS SDK端能力

 @param context 上下文
 @param params 参数
 @param completion 回调
 */
+ (void)callAbilityWithContext:(UIViewController *)context params:(NSDictionary *)params completion:(void(^)(NSDictionary *result))completion;

@end



