#ifndef PUBLIC_STRUCT_H_INCLUDED
#define PUBLIC_STRUCT_H_INCLUDED
#include <iostream>
#include <stdio.h>
#include <string>
#include <map>
#include <vector>
#include <list>

#define BBDS
#define REQID_LENGTH    50
#define COMPANYID_LENGTH    15
#define COMPANYNAME_LENGTH    45
#define COMPANYTYPEID_LENGTH    15
#define COMPANYTYPENAME_LENGTH    15
#define SCENEID_LENGTH    15
#define SCENENAME_LENGTH    15
#define SCENETYPENAME_LENGTH    15
#define CHARGENAME_LENGTH    20
#define DEVICETYPENAME_LENGTH    45
#define SENSORID_LENGTH    30

#define AI "3" //遥测
#define DI "2" //遥信

using namespace std;

typedef struct _t_signal
{
	string code;
	string name;
	string unit;
	string level;
	bool communicationErroFalg;
}t_signal_rule_elemet;


typedef struct _t_topic
{
	string source;
	string action;
	string destination;
}t_topic;


typedef struct _FsuKeyStruct
{
    string FsuId;     //FSU ID号，资源系统的ID
    string FsuCode;    //FSU  编码
    string Infos;
}FsuKeyStruct;

namespace boost
{
	namespace serialization
	{
		template <class Archive>
		void serialize(Archive &ar, FsuKeyStruct &his, const unsigned int version)
		{
			ar &his.FsuId;
			ar &his.FsuCode;
			ar &his.Infos;
		}
	}
}



typedef struct _DeviceKeyStruct
{
    string DeviceId;     //设备ID
    string DeviceCode;   //设备编码

    bool operator < (const _DeviceKeyStruct& key) const
    {
        if(DeviceId < key.DeviceId)
            return true;
        else
            return false;
    }
}DeviceKeyStruct;

namespace boost
{
	namespace serialization
	{
		template <class Archive>
		void serialize(Archive &ar, DeviceKeyStruct &his, const unsigned int version)
		{
			ar &his.DeviceId;
			ar &his.DeviceCode;
		}
	}
}

typedef struct _DeviceLoginStruct
{
    DeviceKeyStruct Device;
    string DeviceName;
    string DeviceType;
    string DeviceCoordinate;
    string DeviceArea;
    string DeviceHight; 
    bool operator < (const _DeviceLoginStruct& key) const
    {
        if(Device.DeviceId < key.Device.DeviceId)
            return true;
        else
            return false;
    }
}DeviceLoginStruct;

namespace boost
{
	namespace serialization
	{
		template <class Archive>
		void serialize(Archive &ar, DeviceLoginStruct &his, const unsigned int version)
		{
			ar &his.Device;
			ar &his.DeviceName;
			ar &his.DeviceType;
			ar &his.DeviceCoordinate;
			ar &his.DeviceArea;
			ar &his.DeviceHight;
		}
	}
}


typedef struct _DeviceInfo
{
    string devId;
    string devType;
    string port;
    string name;
    string desType;
    string version;
} DeviceInfo;

typedef struct _DevicePropStr
{
    string devId;
    string devName;
    string devType;
    string devGroup;
    string devTypeDesc;
    string devVer;
    string status;
} DevicePropStr;

typedef struct _UserInfoBean
{
     FsuKeyStruct FsuKey;       //FSU结构体
     string UserName;
     string Password;
     string FsuIP;
   //  string RightLevel;        //权限
     vector<DeviceKeyStruct> DeviceList;
}UserInfoBean;

typedef struct _TFTPUser
{
    FsuKeyStruct FsuKey;       //FSU结构体
    string  UserName;
    string  Password;
}TFTPUser;

typedef struct _TFSUStatus
{
    FsuKeyStruct FsuKey;       //FSU结构体
    string CPUUsage;     //CPU使用率
    string MEMUsage;     //内存使用率
}TFSUStatus;

//重要，map 重载

typedef struct _CmpFunc
{
    bool operator () (const DeviceKeyStruct& k1, const DeviceKeyStruct& k2) const
    {
        if(k1.DeviceId != k2.DeviceId)
            return true;
        else
            return false;
    }

}CmpFunc;


typedef struct _Warning
{
	string SerialNo;           //告警序号
	string ID;                 //ID描述
	FsuKeyStruct FsuKey;       //FSU结构体
	DeviceKeyStruct DeviceKey;
	string AlarmTime;          //告警时间
	string AlarmLevel;         //告警级别
	string AlarmFlag;          //告警标志
	string AlarmDesc;          //告警文本
	string Enterprise;		   //告警企业
	string Alarmvalue;		   //告警实测值
}Warning;

typedef struct _TTime
{
	string Years;
	string Month;
	string Day;
	string Hour;
	string Minute;
	string Second;
}TTime;

namespace boost
{
    namespace serialization
    {
        template <class Archive>
        void serialize(Archive &ar, TTime &his, const unsigned int version)
        {
            ar &his.Years;
            ar &his.Month;
            ar &his.Day;
            ar &his.Hour;
            ar &his.Minute;
            ar &his.Second;
        }
    }
}

//时间信息
typedef struct _TimeInfo
{
	short year;
    unsigned char month;
    unsigned char day;
    unsigned char hour;
    unsigned char minute;
    unsigned char second;
} TimeInfo;

namespace boost
{
	namespace serialization
	{
		template <class Archive>
		void serialize(Archive &ar, TimeInfo &his, const unsigned int version)
		{
			ar &his.year;
			ar &his.month;
			ar &his.day;
			ar &his.hour;
			ar &his.minute;
			ar &his.second;
		}
	}
}

//信号量的门限值
typedef struct _TThreshold
{
     string Type;      //数据类型
     string ID;        //监控点ID
     string Threshold;  //门限值
     string AbsoluteVal;   //绝对阈值
     string RelativeVal;   //百分比阈值
     string Status;   //状态
}TThreshold;

namespace boost
{
	namespace serialization
	{
		template <class Archive>
		void serialize(Archive &ar, TThreshold &his, const unsigned int version)
		{
			ar &his.Type;
			ar &his.ID;
			ar &his.Threshold;
			ar &his.AbsoluteVal;
			ar &his.RelativeVal;
			ar &his.Status;
		}
	}
}

//信号量的值  (监控点)
typedef struct _TSemaphore
{
     string Type;      //数据类型
     string ID;        //监控点ID
     string MeasuredVal;  //实测值
     string SetupVal;   //设置值,对应bucket中的value（数据库）,遥控
     string Status;   //状态
     string RecordTime;    //记录时间，对应bucket中的时间（数据库）
}TSemaphore;

namespace boost
{
	namespace serialization
	{
		template <class Archive>
		void serialize(Archive &ar, TSemaphore &his, const unsigned int version)
		{
			ar &his.Type;
			ar &his.ID;
			ar &his.MeasuredVal;
			ar &his.SetupVal;
			ar &his.Status;
			ar &his.RecordTime;
		}
	}
}

//FSU注册信息(新)
typedef struct _FsuLoginInfo
{
	FsuKeyStruct FsuKey;       //FSU结构体
	map<DeviceKeyStruct, vector<TThreshold> > MapThresholdData;		//门限信息
	map<DeviceKeyStruct, vector<TSemaphore> > MapSemaphoreData;		//监控点信息
	string Enterprise;
}FsuLoginInfo;

namespace boost
{
	namespace serialization
	{
		template <class Archive>
		void serialize(Archive &ar, FsuLoginInfo &his, const unsigned int version)
		{
			ar &his.FsuKey;
			ar &his.MapThresholdData;
			ar &his.MapSemaphoreData;
			ar &his.Enterprise;
		}
	}
}

/*TODO: 添加供电设备属性名称字段*/
//蓄电池特殊设备属性
typedef struct _BBDS_DeviceProp
{
    long long id;                 ///< 设备ID
    string name;                  ///< 设备名称
    string desc;                  ///< 设备描述
    string productor;             ///< 生产厂商
    string model;                 ///< 型号
    string beginRunTime;          ///< 投入运行时间
    int powerSysNo;               ///< UPS或充电机编号
    int parCircuitNo;             ///< 并联回路编号
    int batNum;                   ///< 蓄电池节数
    int batVolt;                  ///< 蓄电池电压,2V:0 6V:1 12V:2
    int batVoltClass;             ///< 蓄电池电压等级 如220V
    int batCapacity;              ///< 蓄电池电池容量（如1000AH）
	uint16_t currentProbeRange;   ///< 电流传感器量程（如50A）单位:A
	uint32_t resFiducial;         ///< 内阻基准值（如3500 uΩ）单位:uΩ
} BBDS_DeviceProp;

namespace boost
{
    namespace serialization
    {
        template <class Archive>
        void serialize(Archive &ar, BBDS_DeviceProp &his, const unsigned int version)
        {
            ar &his.id;
            ar &his.name;
            ar &his.desc;
            ar &his.productor;
            ar &his.model;
            ar &his.beginRunTime;
            ar &his.powerSysNo;
            ar &his.parCircuitNo;
            ar &his.batNum;
            ar &his.batVolt;
            ar &his.batVoltClass;
            ar &his.batCapacity;
			ar &his.currentProbeRange;
			ar &his.resFiducial;
        }
    }
}

//监控点数据
typedef  struct _MonitorDataBean
{
    string Enterprise ;
    string reqId;              //请求实时数据时的 线程请求ID;
    FsuKeyStruct FsuKey;       //FSU结构体
    string Result;
    map<DeviceKeyStruct,vector<TSemaphore> > MapData;
                       //实时数据返回标志
} MonitorDataBean;

namespace boost
{
	namespace serialization
	{
		template <class Archive>
		void serialize(Archive &ar, MonitorDataBean &his, const unsigned int version)
		{
            ar &his.Enterprise;
			ar &his.reqId;
			ar &his.FsuKey;
			ar &his.Result;
			ar &his.MapData;
		}
	}
}
//监控点数据
typedef  struct _HisMonitorDataBean
{
    FsuKeyStruct FsuKey;       //FSU结构体
    string Result;
    string StartTime;
    string EndTime;
    map<DeviceKeyStruct, vector<TSemaphore> > MapData;
} HisMonitorDataBean;

//监控点门限数据
typedef struct _ThresholdDataBean
{
    string Enterprise;
    string reqId;
    FsuKeyStruct FsuKey;       //FSU结构体
    string Result;
    map<DeviceKeyStruct, vector<TThreshold> > MapData;
} ThresholdDataBean;

namespace boost
{
	namespace serialization
	{
		template <class Archive>
		void serialize(Archive &ar, ThresholdDataBean &his, const unsigned int version)
		{
			ar &his.Enterprise;
			ar &his.reqId;
			ar &his.FsuKey;
			ar &his.Result;
			ar &his.MapData;
		}
	}
}

//工作模式
typedef struct _RuntimeModeBean
{
    FsuKeyStruct fsuKey;
    string mode;
    string result;
} RuntimeModeBean;

//设备列表
typedef struct _DeviceInfoBean
{
    FsuKeyStruct fsuKey;
    string result;
    list<DeviceInfo> devInfoList;
} DeviceInfoBean;

//适配层版本
typedef struct _ALVersionBean
{
    FsuKeyStruct fsuKey;
    string version;
} ALVersionBean;

//设备属性
typedef struct _DevicePropBean
{
    FsuKeyStruct fsuKey;
    list<DevicePropStr> devicePropList;
} DevicePropBean;


typedef struct _CurrentValQuery
{
	string reqId;
	string uniqueCode;//企业
	string deviceOid;
}CurrentValQuery;


typedef struct _ThresholdSetReq
{
	string reqId;
	string uniqueCode;
	string deviceOid;
	string signalOid;
	string threshold;
}ThresholdSetReq;

typedef struct _MultiThresholdSetReq
{
	string reqId;
	string uniqueCode;
	list<string> bbdsCodes;
	string voltageLevel;    ///< 蓄电池电压等级 如220V
	string specVoltage;     ///< 蓄电池电压,2V:0 6V:1 12V:2
	string specCapacity;    ///< 蓄电池电池容量（如1000AH）
	string signalType;
	string threshold;
}MultiThresholdSetReq;

typedef struct _MonitorSetReq
{
	string reqId;
	string uniqueCode;
	string deviceOid;
	string signalOid;
	string type;//遥控,遥测,,,,,,,
	string value;//AI遥控空调时value=0,关闭空调
}MonitorSetReq;

typedef struct _topics {
	int count;
	int *qos;
	char **topics_str;
}topics;

///< 时间的结构体
typedef struct _TimeValInfo {
	time_t second;   ///< 单位: 秒
	int millsecond;  ///< 单位: 毫秒
}TimeValInfo;

///< 时间的结构体
typedef struct _EventBatInfo {
	float vol;   ///< 单节蓄电池电压 V
	float temp;  ///< 单节蓄电池温度 ℃
}EventBatInfo;

typedef struct _EventInfo {
	uint32_t event_id;     ///< 事件的序号
	uint16_t type;         ///< 事件的类型  0:充电 1：放电
	uint16_t soe;		   ///< 事件标志    0：开始 1：结束
	uint64_t device_code;  ///< 蓄电池组设备ID(33010400010070001)
	uint64_t time_sec;     ///< 时间戳中的秒数部分
}EventInfo;

typedef struct _EventListInfo {
	string fsu_index;      ///< enterprise + fsuid
	uint32_t event_id;     ///< 事件的序号
	uint64_t device_code;  ///< 蓄电池组设备ID(33010400010070001)
	bool operator == (const _EventListInfo& event) const
	{
		if((fsu_index == event.fsu_index) && (event_id == event.event_id) &&
				(device_code == event.device_code))
			return true;
		else
			return false;
	}
}EventListInfo;

typedef struct _DiagnoseMsgType {
	uint32_t id;           // 故障上报序号
	uint32_t code;         // 故障码，例如01H
	uint16_t status;       // 0：故障结束, 1：产生
	uint16_t reserved;     //保留
	uint32_t source_type;  // 产生故障源的类型: 1 - BBDS, 2 - BDM, 3 - CDM
	uint64_t source_id;    // 如果为BBDS，该值没意义
	                       //如果是BDM或CDM，则代表device_code(17位)。例如：33010400011070002

	uint64_t sub_sourceId;  //如果是BBDS或BDM，该值没有意义。
	                        //如果是CDM，则代表蓄电池节号（1~255）

	uint64_t time_sec;       //上报时间戳单位 s

}DiagnoseMsgType;

#pragma pack(1)
typedef struct _EventDataHeader {
	uint8_t version;       ///< 版本号 默认是0
	uint8_t flag; 	       ///<  0 – 没数据 1 – 有数据 2 – last 结束
	uint8_t data_number;   ///< 时间点的个数
	uint8_t reverse;	   ///< 保留
	uint32_t event_id;     ///< 事件的序号
	uint64_t device_code;  ///< 蓄电池组设备ID(33010400010070001)
	uint32_t bat_num;      ///< 该电池组设备的电池数
}EventDataHeader;

typedef struct _EventDataGroupSample {
    uint64_t time_sec;  ///< 时间戳中的秒数部分
    uint32_t time_ms;	///< 时间戳中的毫秒数部分
    uint32_t voltage;   ///< 组电压 mV
    int32_t electric;  ///< 组电流值 mA
}EventDataGroupSample;

typedef struct _EventDataCellSample {
    uint32_t vol;   ///< 单节蓄电池电压 mV
    int32_t temp;  ///< 单节蓄电池温度 ℃
}EventDataCellSample;

#pragma pack()

#endif // PUBLICSTRUCT_H_INCLUDED
