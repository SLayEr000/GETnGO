//
//  PASSLoginConfig.h
//  PassportKit
//
//  Created by jiangzhenjie on 2018/3/9.
//  Copyright © 2018年 Baidu Passport. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 登录配置项
 */
@interface PASSLoginConfig: NSObject

/**
 登录方式，可选帐号密码登录、短信登录、注册
 默认为帐号密码登录
 
 如果支持个性化登录，则使用个性化登录方式，具体见 -[SAPIMainManager supportPersonalizedLogin] 配置项
 */
@property (nonatomic, assign) PASSLoginWay loginWay;

// PASSLoginWay to SAPILoginType
@property (nonatomic, assign, readonly) SAPILoginType loginType;

/**
 与 -[SAPIMainManager showLoginLink] 功能相同
 登录入口显示判断：短信登录页面是否显示普通登录入口 1 显示  0 隐藏
 默认与 -[SAPIMainManager showLoginLink] 相同
 */
@property (nonatomic, assign) BOOL showLoginLink;

/**
 与 -[SAPIMainManager showSMSLoginLink] 功能相同
 登录入口显示判断：普通登录界面是否显示短信登录入口 1 显示 0 隐藏
 默认与 -[SAPIMainManager showSMSLoginLink] 相同
 */
@property (nonatomic, assign) BOOL showSMSLoginLink;

/**
 与 -[SAPIMainManager showThirdLoginOnSMSLogin] 功能相同
 短信登录界面是否显示第三方登录入口
 默认与 -[SAPIMainManager showThirdLoginOnSMSLogin] 相同
 */
@property (nonatomic, assign) BOOL showThirdLoginOnSMSLogin;

/**
 支持的第三方登录
 数组元素为 SAPILoginOptionType 枚举值，数组为nil或者空数组时，表示不支持第三方登录
 
 默认与 -[SAPIMainManager addLoginOption:] 相同
 
 @code
 NSMutableArray *fastLoginOptions = [NSMutableArray array];
 [fastLoginOptions addObject:@(SAPILoginOptionWeiXinSSO)];
 [fastLoginOptions addObject:@(SAPILoginOptionQQSSO)];
 ...
 @endcode
 
 */
@property (nonatomic, copy) NSArray<NSNumber *> *supportFastLoginOptions;


/**
 联合登陆中需要用户同意的用户协议，格式：
 @[
  @{@"name":@"度秘协议",@"url":@"https://www.baidu.com"},
  @{@"name":@"苏宁协议",@"url":@"https://www.suning.com"}
 ]
 */
@property (nonatomic, copy) NSArray<NSDictionary<NSString *, NSString *> *> *joinLoginAgreements;
/**
 自定义登录页 css 样式文件的路径，默认为 mainBundle 下 sapi-custom-style.css 文件所在的路径
 
 注意：传的必须是 File URL，举例：
 
 @code
 NSString *path = [[NSBundle mainBundle] pathForResource:@"CssStyle.bundle/pass-custom-style-1" ofType:@"css"];
 NSURL *fileURL = [NSURL fileURLWithPath:path];
 @endcode
 */
@property (nonatomic, strong) NSURL *customCssStyleFileURL;

/**
 短信登录页面是否隐藏密码框下面的一排入口，默认为NO，不隐藏
 */
@property (nonatomic, assign) BOOL hideExtraEntry;

/**
 关闭选择互通页面，仅对白名单产品线生效
 */
@property (nonatomic, assign) BOOL disableChoiceShareLogin;

/**
 创建 PASSLoginConfig 实例

 @return PASSLoginConfig 实例
 */
+ (instancetype)config;

@end
