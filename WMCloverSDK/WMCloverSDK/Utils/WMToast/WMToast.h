//
//  WMToast.h
//  WMCloverSDK
//
//  Created by apple on 2021/4/14.
//

@import Foundation;
@import UIKit;

typedef NS_ENUM(NSInteger, WMToastDuration) {
    kWTShort = 1,
    kWTLong = 5
};

typedef NS_ENUM(NSInteger, WMToastGravity) {
    kWTGravityBottom = 0,
    kWTGravityMiddle = 1,
    kWTGravityTop = 2
};
typedef NS_ENUM(NSInteger, WMToastLayoutDirection) {
    WMLayoutDirectionHorizonzal = 0,
    WMLayoutDirectionVertical = 1,
};


@interface WMToast : UIView

+ (void)show2WithText:(NSString *)text;
+ (void)showWithText:(NSString *)text;
+ (void)showWithImage:(UIImage *)image;
+ (void)showWithText:(NSString *)text image:(UIImage *)image;
+ (void)showWithText:(NSString *)text image:(UIImage *)image layoutDirection:(WMToastLayoutDirection)direction;

+ (void)showWithText:(NSString *)text duration:(NSInteger)duration;
+ (void)showWithImage:(UIImage *)image duration:(NSInteger)duration;

+ (void)showWithText:(NSString *)text duration:(NSInteger)duration roundedCorners:(BOOL)roundedCorners;
+ (void)showWithImage:(UIImage *)image duration:(NSInteger)duration roundedCorners:(BOOL)roundedCorners;

+ (void)showWithText:(NSString *)text gravity:(WMToastGravity)gravity;
+ (void)showWithImage:(UIImage *)image gravity:(WMToastGravity)gravity;

+ (void)showWithText:(NSString *)text duration:(NSInteger)duration gravity:(WMToastGravity)gravity;
+ (void)showWithImage:(UIImage *)image duration:(NSInteger)duration gravity:(WMToastGravity)gravity;

+ (void)showWithText:(NSString *)text duration:(NSInteger)duration roundedCorners:(BOOL)roundedCorners gravity:(WMToastGravity)gravity;
+ (void)showWithImage:(UIImage *)image duration:(NSInteger)duration roundedCorners:(BOOL)roundedCorners gravity:(WMToastGravity)gravity;
+ (void)showWithTextLong:(NSString *)text;

- (void)showText:(NSString *)text;
- (void)dismiss;
@end
