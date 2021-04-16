//
//  UIView+Edge.h
//  WMCloverSDK
//
//  Created by apple on 2021/4/14.
//

#import <UIKit/UIKit.h>

@interface UIView (Edge)

@property (nonatomic, assign) CGFloat x;
@property (nonatomic, assign) CGFloat y;
@property (nonatomic, assign) CGFloat width;
@property (nonatomic, assign) CGFloat height;
@property (nonatomic, assign) CGFloat left;
@property (nonatomic, assign, readonly) CGFloat right;
@property (nonatomic, assign) CGFloat top;
@property (nonatomic, assign, readonly) CGFloat bottom;
@property (nonatomic, assign) CGFloat centerX;
@property (nonatomic, assign) CGFloat centerY;

@end
