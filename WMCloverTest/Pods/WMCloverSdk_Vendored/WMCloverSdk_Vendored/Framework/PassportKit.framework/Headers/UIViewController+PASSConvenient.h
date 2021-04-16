//
//  UIViewController+PASSConvenient.h
//  PassportKit
//
//  Created by jiangzhenjie on 2017/4/18.
//  Copyright © 2017年 Baidu Passport. All rights reserved.
//

#import <UIKit/UIKit.h>

@class PASSContainerController;

@interface UIViewController (PASSConvenient)

/**
 获取PASS容器
 */
@property (nonatomic, strong, readonly) PASSContainerController *passContainerController;

/**
 以 present 方式打开 ViewController。
 该方法会在 ViewController 上嵌套一层 UINavigationController

 @param viewControllerToPresent 被打开的ViewController
 @param animated 是否动画
 @param completion 完成回调
 */
- (void)pass_presentViewController:(UIViewController *)viewControllerToPresent animated:(BOOL)animated completion:(void (^)(void))completion;

/**
 以 present 方式打开 viewController，并添加底返回框架

 @param viewControllerToPresent 被打开的ViewController，该 viewController 不能是 UINavigationController 实例
 @param animated 是否动画
 @param completion 完成回调
 */
- (void)pass_presentViewControllerInContainer:(UIViewController *)viewControllerToPresent animated:(BOOL)animated completion:(void (^)(void))completion;

@end
