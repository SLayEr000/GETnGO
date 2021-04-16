//
//  PASSBindWidgetViewController.h
//  PassportKit
//
//  Created by jiangzhenjie on 2017/4/4.
//  Copyright © 2017年 Baidu Passport. All rights reserved.
//

#import <PassportKit/PassportKit.h>

/**
 绑定控件页面
 绑定手机、换绑手机、解绑手机、绑定邮箱、换绑邮箱、解绑邮箱都通过该类实现
 */
@interface PASSBindWidgetViewController : PASSWebViewController

/**
 绑定控件类型
 */
@property (nonatomic, assign) SAPIBindWidgetType type;

/**
 登录态，如果传空，则用当前登录帐号
 */
@property (nonatomic, copy) NSString *bduss;

/**
 完成时回调，回调中的 userInfo 为扩展字段，暂未使用；
 操作成功时，回调中的 error 为空；
 操作失败时，比如用户中途取消，回调中的 error 不为空；
 */
@property (nonatomic, copy) void(^completionHandler)(NSDictionary *userInfo, NSError *error);

/**
 处理绑定冲突，产品线在回调中调起短信登录页
 注意：如果该回调不实现，则调起默认的短信登录页
 */
@property (nonatomic, copy) void(^handleBindConflictBlock)(NSDictionary *userInfo);

/**
 初始化

 @param type 绑定控件类型
 @param bduss 登录态，如果传空，则用当前登录帐号
 @return 页面实例
 */
- (instancetype)initWithType:(SAPIBindWidgetType)type bduss:(NSString *)bduss;

@end
