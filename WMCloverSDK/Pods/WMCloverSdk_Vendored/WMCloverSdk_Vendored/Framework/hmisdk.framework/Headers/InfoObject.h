//
//  InfoObject.h
//  hmisdk
//
//  Created by v_xiaowenzhang on 2020/2/11.
//  Copyright © 2020 baidu. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Point2D : NSObject

@property (nonatomic) float x;
@property (nonatomic) float y;

@end

@interface ParkingPoint : NSObject

@property (nonatomic) int id;
@property (nonatomic, copy) NSString* name;

@end


@interface ParkingInfo : NSObject

@property (nonatomic) int parkId;
@property (nonatomic, copy) NSString* name;
@property (nonatomic, copy) NSString* addr;
@property (nonatomic, strong) Point2D* pos;
@property (nonatomic) float distance;
@property (nonatomic) int idleNum;
@property (nonatomic) int totalNum;
@property (nonatomic, strong) NSMutableArray<ParkingPoint*>* entranceList;
@property (nonatomic, strong) NSMutableArray<ParkingPoint*>* exitList;
@property (nonatomic, strong) NSMutableArray<NSString*>* floorList;

@end


@interface OrderInfo : NSObject

@property (nonatomic, copy) NSString* orderId;
@property (nonatomic) int orderType;
@property (nonatomic) int orderState;
@property (nonatomic) int parkId;
@property (nonatomic) int entranceId;
@property (nonatomic) int exitId;
@property (nonatomic) int ts;
@property (nonatomic, copy) NSString* vin;
@property (nonatomic, copy) NSString* aid;

@end


@interface CarInfo : NSObject


@property (nonatomic, strong) Point2D* pos;
@property (nonatomic) int parkId;
@property (nonatomic, copy) NSString* floor;
@property (nonatomic) int state;
@property (nonatomic, strong) Point2D* ori;
@property (nonatomic, strong) NSMutableArray<Point2D*>* trajectory;

@end


@interface LinkInfo  : NSObject

@property (nonatomic, strong) NSMutableArray<Point2D*>* posList;
@property (nonatomic, copy) NSString* floor;

@end


@interface NavigationInfo : NSObject

@property (nonatomic, strong) NSMutableArray<LinkInfo*>* linkList;
@property (nonatomic) int parkId;
@property (nonatomic) float dis;
@property (nonatomic) float leftTime;

@end


@interface ObstacleInfo : NSObject

@property (nonatomic, strong) Point2D* pos;
@property (nonatomic) int parkId;
@property (nonatomic, copy) NSString* floor;
@property (nonatomic) int type;
@property (nonatomic, strong) Point2D* ori;
@property (nonatomic) float speed;

@end


@interface PathInfo : NSObject

@property (nonatomic) int pathID;
@property (nonatomic, copy) NSString* pathName;
@property (nonatomic) int pathType;
@property (nonatomic) float pathDistance;
@property (nonatomic) int spaceType;
@property (nonatomic, copy) NSString* vin;
@property (nonatomic) float learnRate;
@property (nonatomic) int state;
@property (nonatomic) int updateTime;

@end
