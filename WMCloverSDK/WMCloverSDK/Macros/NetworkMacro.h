//
//  NetworkMacro.h
//  WMCloverSDK
//
//  Created by apple on 2021/4/14.
//

#ifndef NetworkMacro_h
#define NetworkMacro_h


///根据编码获取字典详情
#define GetDictionaryList @"/system/base/dictionary/get_detail_code"

///销售机会、机会信息列表
#define SalesLeadsPage @"/system/sign/cloudSell/salesLeads/appQueryPage"

///添加机会
#define SalesLeadsSave @"/system/sign/cloudSell/salesLeads/save"

///获取组织列表
#define GetListOrganization @"/system/base/organization/get_list_by_type"

///获取站点
#define GetStationlist @"/system/base/organization/get_station_list"

///获取原物料
#define GetRawMaterials @"/system/sign/basics/rawMaterials/QueryList"

///登记工程
#define EngineeringManagement @"/system/sign/cloudSell/engineeringManagement/saveOrUpdate"


///1.快速检测；2.批量检测；3.复检，4.抽检
#define Querypage @"/system/sign/intelligent/make/querypage"


///回弹检验、出场检测
#define ConcreteQuerypage @"/system/sign/intelligent/concrete/queryPage"


///混凝土其他检测
#define ConcreteQueryOtherPage @"/system/sign/intelligent/concrete/queryOtherPage"


///登记工程修改状态
#define AssignOrRedeploy @"/system/sign/cloudSell/salesLeads/assignOrRedeploy"


///泵送任务
#define AppQueryPages @"/system/sign/basics/plan/appQueryPages"


///回弹养护
#define MaintenanceHistory @"/system/sign/intelligent/maintenanceHistory/queryPage"


///检测依据
#define JJGconefficient @"/system/sign/basics/JJGconefficient/getAllList"


///获取供应商列表
#define SupplierQueryPage @"/system/sign/dataCollection/supplier/QueryPage"


///日供应计划列表
#define SupplierPlanQueryPage @"/system/sign/dataCollection/productPlan/QueryPage"



///日供应计划详情
#define getPlanDetailById @"/system/sign/dataCollection/supplierPlan/getPlanDetailById"



///供应清单列表
#define supplierlistQueryPage @"/system/sign/dataCollection/supplierPlanDetail/QueryPage"



///获取检验标准
#define getStationNormByDetection @"/system/sign/basics/qualityDetection/getStationNormByDetection"


///泵机确认
#define pumpAffirm @"/system/sign/intelligent/pumpAffirm/save"


///泵机检查项
#define checkItem @"/system/sign/basics/checkItem/queryList"


///泵送人员列表
#define appAssignList @"/system/sign/basics/plan/assign/appAssignList"


///罐车调度列表
#define truckDispatch @"/system/sign/intelligent/proDispatchLogistics/appQueryPage"

///调度
#define truckDispatchsave @"/system/sign/basics/truckDispatch/save"


///扫码卸料
#define codeDischargesave @"/system/sign/intelligent/codeDischarge/save"


///在排队的车辆列表
#define tankerQueueUp @"/system/sign/intelligent/tankerQueueUp/queryList"


///车辆排队
#define tankerQueueUpsave @"/system/sign/intelligent/tankerQueueUp/save"


///查询是否绑定车辆
#define tankerBinding @"/system/sign/intelligent/tankerBinding/getBinding"


///发料通知
#define noticesave @"/system/sign/basics/plan/notice/save"


///发料记录列表
#define appStoreIssueNotice @"/system/sign/basics/plan/notice/appStoreIssueNotice"


///运输任务
#define appTankerList @"/system/sign/basics/plan/appTankerList"


///获取罐车离场申请浇筑方式
#define appPourings @"/system/sign/intelligent/departure/appPourings"

///运输任务详情
#define appTankerDetails @"/system/sign/basics/plan/appTankerDetails"


///罐车离场申请详情
#define appGetDetail @"/system/sign/intelligent/departure/appGetDetail"


///前场工长离场审核列表
#define LeaceQueryPage @"/system/sign/intelligent/departure/appFrontQueryPage"


///罐车司机离场申请列表
#define LeaceCarQueryPage @"/system/sign/intelligent/departure/appQueryPage"


///前场工长获取工地位置、浇筑任务列表、工作日志
#define appPouringTasksPlace @"/system/sign/basics/plan/appPouringTasks"


///banner获取
#define bannerqueryList @"/system/sign/basicsterrace/banner/queryList"


///通讯录
#define QueryMaillist @"/system/app/client/query_mail_list"


///浇筑任务详情
#define Plandetail @"/system/sign/basics/plan/plan_detail?id="



///跟进记录
#define SaveOrUpdateList @"/system/sign/cloudSell/saleProgress/saveOrUpdate"



///请求头参数
#define  User_Agent(language,country,timezone)  [NSString stringWithFormat:@"catchtoy.app.ios vs_%@_ve lang_%@_lang   country_%@_country  timezone_%@_timezone cs_%@_ce",[[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleVersion"],language,country,timezone,cType]


///webview请求头参数
#define  Web_Agent(language,country,timezone)   [NSString stringWithFormat:@"catchtoy.app.ios vs_%@_ve lang_%@_lang   country_%@_country  timezone_%@_timezone cs_%@_ce",[[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleVersion"],language,country,timezone,cType]



#endif /* NetworkMacro_h */
