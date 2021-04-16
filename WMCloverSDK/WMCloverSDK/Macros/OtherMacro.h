//
//  Header.h
//  WMCloverSDK
//
//  Created by apple on 2021/4/14.
//

#ifndef Header_h
#define Header_h

//转换字符串
#define objcString(str) [NSString stringWithFormat:@"%@",str]

#define objcString_name(str,name) [NSString stringWithFormat:@"%@%@",str,name]


//判断是否为空
#define WM_IS_BLANK_OBJ(obj) [WMCommon isBlankObject:obj]


///存入沙盒
#define WMUserDefaultUtil(object, key)                                                                                                 \
({                                                                                                                                             \
NSUserDefaults * defaults = [NSUserDefaults standardUserDefaults];                                                                         \
[defaults setObject:object forKey:key];                                                                                                    \
[defaults synchronize];                                                                                                                    \
})


///获取沙盒
#define WMGetUserDefaultUtil(key) [[NSUserDefaults standardUserDefaults] objectForKey:key]


///删除沙盒某一个对象
#define kRemoveUserDefaults(key)                                         \
({                                                                       \
NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];        \
[defaults removeObjectForKey:key];                                       \
[defaults synchronize];                                                  \
})


///清除沙盒保存的所有数据
#define kRemoveAllUserDefaults  [[NSUserDefaults standardUserDefaults] removePersistentDomainForName:[[NSBundle mainBundle] bundleIdentifier]]



///归档地址
#define KDocumentPath [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,NSUserDomainMask, YES) lastObject]

#define WS(weakSelf) __weak __typeof(&*self)weakSelf = self
#define SS(strongSelf)  __strong __typeof(&*self)strongSelf = weakSelf



//GCD - 一次性执行
#define kDISPATCH_ONCE_BLOCK(onceBlock) static dispatch_once_t onceToken; dispatch_once(&onceToken, onceBlock);


//GCD - 在Main线程上运行
#define kDISPATCH_MAIN_THREAD(mainQueueBlock) dispatch_async(dispatch_get_main_queue(), mainQueueBlock);


//GCD - 开启异步线程
#define kDISPATCH_GLOBAL_QUEUE_DEFAULT(globalQueueBlock) dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), globalQueueBlocl);


#endif /* Header_h */
