//
//  UINavigationController+PASSConvenient.h
//  PassportKit
//
//  Created by jiangzhenjie on 2018/3/8.
//  Copyright © 2018年 Baidu Passport. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UINavigationController (PASSConvenient)

/**
 以 push 方式打开 viewController。
 如果当前使用底返回框架，则自动加上。
 
 内部必须使用该方法打开，外部可以选择使用。

 @param viewController 要打开的 viewController
 @param animated 是否动画
 */
- (void)pass_pushViewController:(UIViewController *)viewController animated:(BOOL)animated;

/**
 以 push 方式打开 viewController，并加上底返回框架。

 @param viewController 要打开的 viewController
 @param animated 是否动画
 */
- (void)pass_pushViewControllerInContainer:(UIViewController *)viewController animated:(BOOL)animated;

/**
 pop 导航栈到特定 VC，该方法会自动兼容底返回框架。
 
 内部必须使用该方法，外部可以选择使用。
 
 @param viewController 回退到的VC
 @param animated 是否动画
 @return 导航栈
 */
- (NSArray<UIViewController *> *)pass_popToViewController:(UIViewController *)viewController animated:(BOOL)animated;

@end
