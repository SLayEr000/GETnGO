//
//  hmisdk.h
//  hmisdk
//
//  Created by v_xiaowenzhang on 2020/2/4.
//  Copyright © 2020 baidu. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BaiduHMI : NSObject

@property(nonatomic, readonly, copy) NSString *sdkVersion;

- (int)init:(NSString*)aid code:(NSString*)code operatorId:(NSString*)operatorId token:(NSMutableString*)token;

- (int)getParkingList:(float)lon lat:(float)lat distance:(float)distance page:(int)page pageNum:(int)pageNum parkingList:(NSMutableArray<ParkingInfo*>*)parkingList;

- (int)parking:(int)parkId entranceId:(int)entranceId orderId:(NSMutableString*)orderId;
- (int)summon:(int)parkId exitId:(int)exitId orderId:(NSMutableString*)orderId;

- (int)getOrderInfo:(NSString*)orderId orderInfo:(OrderInfo*)orderInfo;
- (int)getOrderList:(int)page pageNum:(int)pageNum orderInfoList:(NSMutableArray<OrderInfo*>*)orderInfoList;

- (int)getParkingMap:(int)parkId mode:(int)mode theme:(int)theme floor:(NSString*)floor data:(NSData*)data;

- (int)getCarInfo:(CarInfo*)carInfo;
- (int)getObstacleInfoList:(NSMutableArray<ObstacleInfo*>*)obsInfoList;
- (int)getNavigationInfo:(NavigationInfo*)navInfo;

- (int)getPathList:(NSMutableArray<PathInfo*>*)pathInfoList;
- (int)savePath:(PathInfo*)pathInfo;

- (int)registerNotice:(id<NoticeCallback>)callback;

@end

