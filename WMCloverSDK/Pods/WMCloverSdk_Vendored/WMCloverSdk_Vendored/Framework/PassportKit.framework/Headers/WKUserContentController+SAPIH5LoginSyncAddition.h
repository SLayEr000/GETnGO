//
//  WKUserContentController+SAPIH5LoginSyncAddition.h
//  SAPILib
//
//  Created by jiangzhenjie on 2016/10/19.
//  Copyright © 2016年 baidu. All rights reserved.
//

#import <WebKit/WebKit.h>

@interface WKUserContentController (SAPIH5LoginSyncAddition) <WKScriptMessageHandler>

/**
 *  @brief 增加 WKWebView H5登录态同步到 NA 处理。H5登录成功后，将根据策略同步 H5 与 NA 的登录态。具体的策略见-[SAPIMainManager naH5SyncStrategy]和-[SAPIMainManager naH5SyncCallbackStrategy]配置项
 *
 *  @since 6.15.16
 */
- (void)sapi_addH5LoginSyncHandler;

@end
