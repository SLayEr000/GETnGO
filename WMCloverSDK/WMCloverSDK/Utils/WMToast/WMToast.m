//
//  WMToast.m
//  WMCloverSDK
//
//  Created by apple on 2021/4/14.
//

#import "WMToast.h"

#if !__has_feature(objc_arc)
#error WMToast requires ARC
#endif

#if __IPHONE_OS_VERSION_MIN_REQUIRED < 80000
#error WMToast requires deployment target iOS 8.0 or higher
#endif


#define TABBAR_OFFSET (44.0)
#define SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(v)  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedAscending)

@interface WMToast()

@property (nonatomic) NSInteger duration;
@property (nonatomic) BOOL roundedCorners;
@property (nonatomic) WMToastGravity gravity;
@property (nonatomic,strong)NSMutableArray *textStrings;
@property (nonatomic,strong)UILabel *textLabel;

@end

static NSString *tempText = nil;

@implementation WMToast

- (id)initWithFrame:(CGRect)frame {
    if ((self = [super initWithFrame:frame]) != nil) {
        _duration = kWTShort;
        _roundedCorners = YES;
        self.userInteractionEnabled = NO;
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(windowWillAnimateRotation) name:@"UIWindowWillAnimateRotationNotification" object:nil];
    }
    return self;
}

- (void)windowWillAnimateRotation {
    [self __flipViewAccordingToStatusBarOrientation];
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (void)__show {
    __weak typeof(self) weakSelf = self;
    __block NSInteger bDuration = _duration;

    [UIView
     animateWithDuration:0.2
     animations:^{
         weakSelf.alpha = 1.0;
     }
     completion:^(BOOL finished) {
        if (bDuration != -1) {
            [weakSelf performSelector:@selector(__hide) withObject:nil afterDelay:bDuration];
        }
     }];
}

- (void)__hide {
    __weak typeof(self) weakSelf = self;

    [UIView
     animateWithDuration:1.5
     animations:^{
         weakSelf.alpha = 0.0;
     }
     completion:^(BOOL finished) {
         [weakSelf removeFromSuperview];
         tempText = nil;
     }];
}

- (void)setRoundedCorners:(BOOL)roundedCorners {
    CALayer *layer = self.layer;
    layer.masksToBounds = YES;
    layer.cornerRadius = 9* SCALE_2X;
}

- (NSMutableArray<NSString *> *)textStrings{
    if (!_textStrings) {
        _textStrings = [NSMutableArray arrayWithCapacity:10];
    }
    return _textStrings;
}

- (void)updateFrames{
    CGSize screenSize = [UIScreen mainScreen].bounds.size;
    CGFloat screenWidth = screenSize.width;
    CGFloat screenHeight = screenSize.height;
    
    //toast最大宽度620,最小宽度320 高度100 两行高度156 文本距左边间距56
    CGFloat maxWidth = 310*SCALE_2X - 56*SCALE_2X;
    CGFloat minWidth = 160*SCALE_2X - 56*SCALE_2X;
    
    //计算text所占的rect
    CGRect textRect = [_textLabel.text boundingRectWithSize:CGSizeMake(maxWidth, FLT_MAX)
                                         options:NSStringDrawingUsesLineFragmentOrigin
                                      attributes:@{NSFontAttributeName: _textLabel.font}
                                         context:nil];
    
    CGFloat textWidth = minWidth;
    if (textRect.size.width > minWidth) {
        textWidth = MIN(textRect.size.width, maxWidth);
    }

    CGFloat textHeight = textRect.size.height;
    //一行96 两行120
    CGFloat toastHeight = textHeight < 20*SCALE_2X ? 55*SCALE_2X : 78*SCALE_2X;
    CGFloat toastWidth = textWidth + 56*SCALE_2X;
    CGFloat toastX = (screenWidth - toastWidth) / 2;
    CGFloat toastY = (screenHeight - toastHeight) / 2;
    
    CGFloat textX = 28*SCALE_2X;
    CGFloat textY = (toastHeight - textHeight) / 2;
    self.frame = CGRectMake(toastX, toastY, toastWidth, toastHeight);
    _textLabel.frame = CGRectMake(textX, textY, textWidth, textHeight);
    
   
}

- (void)addTextLabel:(NSString *)text {
    UILabel *textLabel = [[UILabel alloc] init];
    textLabel.backgroundColor = [UIColor clearColor];
    textLabel.textAlignment = NSTextAlignmentCenter;
    textLabel.font = [UIFont systemFontOfSize:12];
    textLabel.textColor =  RGBA(255, 255, 255, 1);
    textLabel.numberOfLines = 2;
    textLabel.text = text;
    textLabel.lineBreakMode = NSLineBreakByWordWrapping;
    self.backgroundColor = HEXCOLOR(000000, 0.94);
    [self addSubview:textLabel];
    self.alpha = 0.0;
    _textLabel = textLabel;
    self.gravity = kWTGravityMiddle;
}

- (void)showText:(NSString *)text{
    UIWindow *mainWindow = [UIApplication sharedApplication].keyWindow;
    if (![self isDescendantOfView:mainWindow]) {
        [mainWindow addSubview:self];
    }
    [self.textStrings addObject:text];
    if (showing) {
        return;
    }
    if (!_textLabel) {
        [self addTextLabel:text];
    }
    [self updateTxtShow:text];
}

- (void)updateTxtShow:(NSString *)text{
    [_textLabel setText:text];
    self.roundedCorners = YES;
    [self updateFrames];
    [self __flipViewAccordingToStatusBarOrientation];
    [self show];
}

static BOOL showing = NO;

- (void)show {
    __weak typeof(self) weakSelf = self;
    __block NSInteger bDuration = _duration;
//    [self setHidden:NO];
    showing = YES;
    [UIView
     animateWithDuration:0.2
     animations:^{
         weakSelf.alpha = 1.0;
     }
     completion:^(BOOL finished) {
         [weakSelf performSelector:@selector(hide) withObject:nil afterDelay:bDuration];
     }];
}

- (void)hide{
    __weak typeof(self) weakSelf = self;

    [UIView
     animateWithDuration:0.5
     animations:^{
         weakSelf.alpha = 0.0;
     }
     completion:^(BOOL finished) {
        if ([self.textStrings indexOfObject:self.textLabel.text]) {
            [self.textStrings removeObject:self.textLabel.text];
        }
        if (self.textStrings.count) {
            [self updateTxtShow:self.textStrings.firstObject];
        }else{
            showing = NO;
            [self setHidden:YES];
            tempText = nil;
        }
     }];
}

- (void)dismiss{
    [self removeFromSuperview];
    showing = NO;
    tempText = nil;
}

+ (void)showWithText:(NSString *)text image:(UIImage *)image layoutDirection:(WMToastLayoutDirection)direction{
    WMToast *toast;
    if (direction == WMLayoutDirectionVertical) {
       toast =  [WMToast __createVerticalText:text image:image];
    }else{
       toast = [WMToast __createWithText:text andImage:image];
    }
    toast.duration = kWTShort;
    toast.roundedCorners = YES;
    toast.gravity = kWTGravityMiddle;
    
    UIWindow *mainWindow = [UIApplication sharedApplication].keyWindow;
    [mainWindow addSubview:toast];
    
    [toast __flipViewAccordingToStatusBarOrientation];
    [toast __show];
}

+ (WMToast *)__createVerticalText:(NSString *)text image:(UIImage *)image{
    CGSize screenSize = [UIScreen mainScreen].bounds.size;
    CGFloat screenWidth = screenSize.width;
    CGFloat screenHeight = screenSize.height;
    
    //label 与 imageView 如何 layout
    CGFloat maxToastW = 310 * SCALE_2X;
    CGFloat minToastW = 85 * SCALE_2X;
    
    //setup imageView
    UIImageView *imageView = [[UIImageView alloc] initWithImage:image];
    [imageView sizeToFit];
    
    CGFloat imageViewW = CGRectGetWidth(imageView.frame);
    CGFloat imageViewH = CGRectGetHeight(imageView.frame);
    
    UILabel *textLabel = [[UILabel alloc] init];
    textLabel.backgroundColor = [UIColor clearColor];
    textLabel.textAlignment = NSTextAlignmentCenter;
    textLabel.font = DEFAULT_FONT(12);
    textLabel.textColor = RGBA(255, 255, 255, 255);
    textLabel.numberOfLines = 0;
    textLabel.text = text;
    textLabel.lineBreakMode = NSLineBreakByWordWrapping;
    [textLabel sizeToFit];
    
    CGFloat maxTextW = maxToastW - (30*SCALE_2X);
    if (maxTextW > CGRectGetWidth(textLabel.frame)) {
        maxTextW = CGRectGetWidth(textLabel.frame);
    }
    //计算text所占的rect
    CGRect textRect = [text boundingRectWithSize:CGSizeMake(maxTextW, FLT_MAX)
                                         options:NSStringDrawingUsesLineFragmentOrigin
                                      attributes:@{NSFontAttributeName: textLabel.font}
                                         context:nil];
    
    CGFloat textWidth = textRect.size.width;
    CGFloat textHeight = textRect.size.height;
    
    CGFloat imageViewY = 15 * SCALE_2X;

    CGFloat textY =  imageViewY + imageViewH + 8 * SCALE_2X;

    
    CGFloat toastW = (textWidth>imageViewW?textWidth:imageViewW)+ 28 * SCALE_2X;
    CGFloat toastH = imageViewH + textHeight + 15 * 2 * SCALE_2X + 8 * SCALE_2X;
    CGFloat toastX = (screenWidth - toastW) / 2;
    CGFloat toastY = (screenHeight - toastH) / 2;
    if (toastW < 85) {
        toastW = minToastW;
    }
    if (toastW > maxToastW) {
        toastW = 310;
    }
    CGFloat imageViewX = (toastW-imageViewW)/2;
    CGFloat textX = imageViewX;


    
    WMToast *toast = [[WMToast alloc] initWithFrame:CGRectMake(toastX, toastY, toastW, toastH)];
    toast.backgroundColor = HEXCOLOR(000000, 0.94);
    textLabel.frame = CGRectMake(textX, textY, textWidth, textHeight);
    imageView.frame = CGRectMake(imageViewX, imageViewY, imageViewW, imageViewH);
    
    [toast addSubview:imageView];
    [toast addSubview:textLabel];
    textLabel.centerX = imageView.centerX;
    toast.alpha = 0.0;
    return toast;
}

+ (WMToast *)__createWithText:(NSString *)text andImage:(UIImage *)image {
    CGSize screenSize = [UIScreen mainScreen].bounds.size;
    CGFloat screenWidth = screenSize.width;
    CGFloat screenHeight = screenSize.height;
    
    //label 与 imageView 如何 layout
    //default layout :
    CGFloat maxToastW = 310 * SCALE_2X;
    CGFloat minToastW = 160 * SCALE_2X;
    
    //setup imageView
    UIImageView *imageView = [[UIImageView alloc] initWithImage:image];
    [imageView sizeToFit];
    
    CGFloat imageViewW = CGRectGetWidth(imageView.frame);
    CGFloat imageViewH = CGRectGetHeight(imageView.frame);
    
    UILabel *textLabel = [[UILabel alloc] init];
    textLabel.backgroundColor = [UIColor clearColor];
    textLabel.textAlignment = NSTextAlignmentCenter;
    textLabel.font = DEFAULT_FONT(12);
    textLabel.textColor = RGB(255, 255, 255);
    textLabel.numberOfLines = 1;
    textLabel.text = text;
    textLabel.lineBreakMode = NSLineBreakByWordWrapping;
    [textLabel sizeToFit];

    CGFloat maxTextW = maxToastW - (imageViewW+56*SCALE_2X+8*SCALE_2X);
    if (maxTextW > CGRectGetWidth(textLabel.frame)) {
        maxTextW = CGRectGetWidth(textLabel.frame);
    }
    //计算text所占的rect
    CGRect textRect = [text boundingRectWithSize:CGSizeMake(maxTextW, FLT_MAX)
                                         options:NSStringDrawingUsesLineFragmentOrigin
                                      attributes:@{NSFontAttributeName: textLabel.font}
                                         context:nil];
    
    CGFloat textWidth = textRect.size.width;
    CGFloat textHeight = textRect.size.height;
    CGFloat textY = 19 * SCALE_2X;
    
    CGFloat imageViewX = (minToastW - (textWidth+8*SCALE_2X))/2;
    CGFloat textX = imageViewX + imageViewW + 8 * SCALE_2X;
    
    if (imageViewW+8*SCALE_2X+textWidth+56*SCALE_2X > maxTextW) {
        imageViewX = 28*SCALE_2X;
        textX = imageViewX + imageViewW + 8 * SCALE_2X;
    }
    
    
    CGFloat toastW = textWidth + textX + 28 * SCALE_2X;
    CGFloat toastH = textHeight + 19 * 2 * SCALE_2X;
    CGFloat toastX = (screenWidth - toastW) / 2;
    CGFloat toastY = (screenHeight - toastH) / 2;
    CGFloat imageViewY = (toastH - imageViewH) / 2;

    imageView.frame = CGRectMake(imageViewX, imageViewY, imageViewW, imageViewH);

    WMToast *toast = [[WMToast alloc] initWithFrame:CGRectMake(toastX, toastY, toastW, toastH)];
    toast.backgroundColor = HEXCOLOR(000000, 0.94);
    textLabel.frame = CGRectMake(textX, textY, textWidth, textHeight);
    
    [toast addSubview:textLabel];
    [toast addSubview:imageView];
    
    toast.alpha = 0.0;
    return toast;
}

+ (WMToast *)__createWithText:(NSString *)text {

    CGSize screenSize = [UIScreen mainScreen].bounds.size;
    CGFloat screenWidth = screenSize.width;
    CGFloat screenHeight = screenSize.height;
    
    //toast最大宽度620,最小宽度320 高度100 两行高度156 文本距左边间距56
    CGFloat maxWidth = 310*SCALE_2X - 56*SCALE_2X;
    CGFloat minWidth = 160*SCALE_2X - 56*SCALE_2X;
    
    UILabel *textLabel = [[UILabel alloc] init];
    textLabel.backgroundColor = [UIColor clearColor];
    textLabel.textAlignment = NSTextAlignmentCenter;
    textLabel.font = [UIFont systemFontOfSize:16];
    textLabel.textColor = RGB(255, 255, 255);
    textLabel.numberOfLines = 2;
    textLabel.text = text;
    textLabel.lineBreakMode = NSLineBreakByWordWrapping;
    
    //计算text所占的rect
    CGRect textRect = [text boundingRectWithSize:CGSizeMake(maxWidth, FLT_MAX)
                                         options:NSStringDrawingUsesLineFragmentOrigin
                                      attributes:@{NSFontAttributeName: textLabel.font}
                                         context:nil];
    
    CGFloat textWidth = minWidth;
    if (textRect.size.width > minWidth) {
        textWidth = MIN(textRect.size.width, maxWidth);
    }

    CGFloat textHeight = textRect.size.height;
    //一行96 两行120
    CGFloat toastHeight = textHeight < 20*SCALE_2X ? 55*SCALE_2X : 78*SCALE_2X;
    CGFloat toastWidth = textWidth + 56*SCALE_2X;
    CGFloat toastX = (screenWidth - toastWidth) / 2;
    CGFloat toastY = (screenHeight - toastHeight) / 2;
    
    CGFloat textX = 28*SCALE_2X;
    CGFloat textY = (toastHeight - textHeight) / 2;
    
    WMToast *toast = [[WMToast alloc] initWithFrame:CGRectMake(toastX, toastY, toastWidth, toastHeight)];
    toast.backgroundColor = HEXCOLOR(000000, 0.94);
    
    textLabel.frame = CGRectMake(textX, textY, textWidth, textHeight);
    [toast addSubview:textLabel];
    
    toast.alpha = 0.0;
    return toast;
}

+ (WMToast *)__createWithImage:(UIImage *)image {
    CGSize screenSize = [UIScreen mainScreen].bounds.size;
    CGFloat screenWidth = screenSize.width;
    
    CGFloat x = 10.0;
    CGFloat width = screenWidth - x * 2.0;

    UIImageView *imageView = [[UIImageView alloc] initWithImage:image];
    CGSize sz = imageView.frame.size;

    CGRect frame = CGRectZero;
    frame.size.width = width;
    frame.size.height = MAX(sz.height + 20.0, 38.0);

    WMToast *toast = [[WMToast alloc] initWithFrame:frame];
    toast.backgroundColor = RGBA(0, 0, 0, 0.8);

    frame.origin.x = floor((toast.frame.size.width - sz.width) / 2.0);
    frame.origin.y = floor((toast.frame.size.height - sz.height) / 2.0);
    frame.size = sz;
    imageView.frame = frame;
    [toast addSubview:imageView];

    toast.alpha = 0.0;
    
    return toast;
}

- (void)__flipViewAccordingToStatusBarOrientation {
    CGSize screenSize = [UIScreen mainScreen].bounds.size;
    CGFloat x = floor((screenSize.width - self.bounds.size.width) / 2.0);
    CGFloat y;
    
    switch (self.gravity) {
        case kWTGravityTop: {
            y = MIN([UIApplication sharedApplication].statusBarFrame.size.width, [UIApplication sharedApplication].statusBarFrame.size.height) + 15.0;
            break;
        }
        case kWTGravityMiddle: {
            y = floor((screenSize.height - self.bounds.size.height) * 0.5);
            break;
        }
        case kWTGravityBottom:
        default: {
            y = screenSize.height - self.bounds.size.height - 15.0 - TABBAR_OFFSET;
            break;
        }
    }

    CGRect f = self.bounds;
    f.origin = CGPointMake(x, y);
    self.frame = f;
}

/**
 * Show toast with text in application window
 * @param text Text to print in toast window
 */
+ (void)showWithText:(NSString *)text {
    if([@"success" isEqualToString:text]) return;
    if([@"token error" isEqualToString:text]) return;
    if (tempText && [tempText isEqualToString:text]) {
//        NSLog(@"text:%@",text);
        VBLog(@"--- 两次弹框文字一致, 屏蔽一个... ---");
        return;
    }
    if (WM_IS_BLANK_OBJ(text)) {
        return;
    }
    tempText = text;
    dispatch_async(dispatch_get_main_queue(), ^{
        UIWindow *mainWindow = [[UIApplication sharedApplication] keyWindow];
        for (UIView *view in mainWindow.subviews) {
            if([view isKindOfClass:[WMToast class]]){
                [view removeFromSuperview];
            }
        }
        [WMToast showWithText:text gravity:kWTGravityMiddle];
    });
}

+ (void)show2WithText:(NSString *)text {
    if (WM_IS_BLANK_OBJ(text)) {
        return;
    }
    tempText = text;
    dispatch_async(dispatch_get_main_queue(), ^{
        UIWindow *mainWindow = [[UIApplication sharedApplication] keyWindow];
        for (UIView *view in mainWindow.subviews) {
            if([view isKindOfClass:[WMToast class]]){
                [view removeFromSuperview];
            }
        }
        [WMToast showWithText:text gravity:kWTGravityMiddle];
    });
}

/**
 * Show toast with text in application window
 * @param text Text to print in toast window
 * @param gravity Toast position in window
 */

+ (void)showWithText:(NSString *)text gravity:(WMToastGravity)gravity {
    [WMToast showWithText:text duration:kWTShort roundedCorners:NO gravity:gravity];
}

/**
 * Show toast with image in application window
 * @param image Image to show in toast window
 */
+ (void)showWithImage:(UIImage *)image {
    [WMToast showWithImage:image gravity:kWTGravityBottom];
}

/**
 * Show toast with image in application window
 * @param image Image to show in toast window
 * @param gravity Toast position in window
 */
+ (void)showWithImage:(UIImage *)image gravity:(WMToastGravity)gravity {
    [WMToast showWithImage:image duration:kWTShort roundedCorners:NO gravity:gravity];
}

/**
 * Show toast with text in application window
 * @param text Text to print in toast window
 * @param length Toast visibility duration
 */
+ (void)showWithText:(NSString *)text duration:(NSInteger)duration {
    [WMToast showWithText:text duration:kWTShort gravity:kWTGravityBottom];
}

/**
 * Show toast with text in application window
 * @param text Text to print in toast window
 * @param length Toast visibility duration
 * @param gravity Toast position in window
 */
+ (void)showWithText:(NSString *)text duration:(NSInteger)duration gravity:(WMToastGravity)gravity {
    [WMToast showWithText:text duration:kWTShort roundedCorners:NO gravity:gravity];
}

+ (void)showWithTextLong:(NSString *)text {
    [WMToast showWithText:text duration:-1 roundedCorners:NO gravity:1];
}
/**
 * Show toast with image in application window
 * @param image Image to show in toast window
 * @param length Toast visibility duration
 */
+ (void)showWithImage:(UIImage *)image duration:(NSInteger)duration {
    [WMToast showWithImage:image duration:kWTShort roundedCorners:NO gravity:kWTGravityBottom];
}

/**
 * Show toast with image in application window
 * @param image Image to show in toast window
 * @param length Toast visibility duration
 * @param gravity Toast position in window
 */
+ (void)showWithImage:(UIImage *)image duration:(NSInteger)duration gravity:(WMToastGravity)gravity {
    [WMToast showWithImage:image duration:kWTShort roundedCorners:NO gravity:gravity];
}

/**
 * Show toast with text in application window
 * @param image Image to show in toast window
 * @param length Toast visibility duration
 * @param roundedCorners Make corners of toast rounded
 */
+ (void)showWithText:(NSString *)text duration:(NSInteger)duration roundedCorners:(BOOL)roundedCorners {
    [WMToast showWithText:text duration:duration roundedCorners:roundedCorners gravity:kWTGravityBottom];
}

/**
 * Show toast with text in application window
 * @param roundedCorners Make corners of toast rounded
 * @param gravity Toast position in window
 */
+ (void)showWithText:(NSString *)text duration:(NSInteger)duration roundedCorners:(BOOL)roundedCorners gravity:(WMToastGravity)gravity {
    WMToast *toast = [WMToast __createWithText:text];
    toast.duration = duration;
    toast.roundedCorners = roundedCorners;
    toast.gravity = gravity;
    
    UIWindow *mainWindow = [UIApplication sharedApplication].keyWindow;
    [mainWindow addSubview:toast];
    
    [toast __flipViewAccordingToStatusBarOrientation];
    [toast __show];
}

+ (void)showWithText:(NSString *)text image:(UIImage *)image {
    WMToast *toast = [WMToast __createWithText:text andImage:image];
    toast.duration = kWTShort;
    toast.roundedCorners = YES;
    toast.gravity = kWTGravityMiddle;
    
    UIWindow *mainWindow = [UIApplication sharedApplication].keyWindow;
    [mainWindow addSubview:toast];
    
    [toast __flipViewAccordingToStatusBarOrientation];
    [toast __show];
}

/**
 * Show toast with image in application window
 * @param image Image to show in toast window
 * @param length Toast visibility duration
 * @param roundedCorners Make corners of toast rounded
 */
+ (void)showWithImage:(UIImage *)image duration:(NSInteger)duration roundedCorners:(BOOL)roundedCorners {
    [WMToast showWithImage:image duration:duration roundedCorners:roundedCorners gravity:kWTGravityBottom];
}

/**
 * Show toast with image in application window
 * @param image Image to show in toast window
 * @param length Toast visibility duration
 * @param roundedCorners Make corners of toast rounded
 */
+ (void)showWithImage:(UIImage *)image duration:(NSInteger)duration roundedCorners:(BOOL)roundedCorners gravity:(WMToastGravity)gravity {
    WMToast *toast = [WMToast __createWithImage:image];
    toast.duration = duration;
    toast.roundedCorners = roundedCorners;
    toast.gravity = gravity;
    
    UIWindow *mainWindow = [UIApplication sharedApplication].keyWindow;
    [mainWindow addSubview:toast];
    
    [toast __flipViewAccordingToStatusBarOrientation];
    [toast __show];
}

@end
