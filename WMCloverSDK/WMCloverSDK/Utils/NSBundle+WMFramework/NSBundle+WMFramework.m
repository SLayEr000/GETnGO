//
//  NSBundle+WMFramework.m
//  WMCloverSDK
//
//  Created by apple on 2021/4/14.
//

#import "NSBundle+WMFramework.h"

@implementation NSBundle (WMFramework)

+ (BOOL)isWMFrameworkEnable{
    NSString *bundlePath = [[NSBundle mainBundle] pathForResource:@"WMCloverSDKResource.bundle" ofType:nil];
    if (bundlePath) {
        return YES;
    }
    else {
        return NO;
    }
}

+ (NSBundle*)wmf_ResourceBundle{
    NSString *bundlePath = [[NSBundle mainBundle] pathForResource:@"WMCloverSDKResource.bundle" ofType:nil];
    if (bundlePath) {
        NSBundle *bundle = [NSBundle bundleWithPath:bundlePath];
        return bundle;
    }
    else {
        return [NSBundle mainBundle];
    }
}

+ (UINib*)wmf_LoadNibWithName:(NSString*)aName{
    UINib *nib = [UINib nibWithNibName:aName bundle:WMF_ResourceBundle];
    if (nib) {
        return nib;
    }
    else{
        NSLog(@"AAAAAAAA: 没找到xib资源 %@",aName);
        return nil;
    }
}

+ (UIView*)wmf_LoadViewWithNibName:(NSString*)aName isFirst:(BOOL)isFirst{

    if (isFirst) {
        return [WMF_ResourceBundle loadNibNamed:aName owner:self options:nil].firstObject;
    } else {
        return [WMF_ResourceBundle loadNibNamed:aName owner:self options:nil].lastObject;
    }
}

@end
