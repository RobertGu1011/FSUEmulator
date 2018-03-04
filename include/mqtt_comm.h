//
// Created by guyang on 17-10-11.
//

#ifndef EMULATOR_MQTT_H
#define EMULATOR_MQTT_H

#include <MQTTAsync.h>
#include <MQTTClientPersistence.h>
#include "shared_variable.h"

#define TOPIC_FSU_LOGOUT      "+/FSULogout/+" //FSU离线
#define TOPIC_FSU_LOGOUT_ACTION      "FSULogout" //FSU离线
#define TOPIC_SVR_LOGOUT      "+/SVRLogout/+" //SC离线
#define TOPIC_SVR_LOGOUT_ACTION      "SVRLogout" //SC离线

#define TOPIC_FSU_LOGIN_SVR     "+/LoginSVR/+" //FSU注册登录SC
#define TOPIC_FSU_LOGIN_SVR_ACTION     "LoginSVR" //FSU注册登录SC
#define TOPIC_RSP_LOGINSVR_ACK      "+/RspLoginSVR/+" //FSU注册登录SC响应
#define TOPIC_RSP_LOGINSVR_ACK_ACTION      "RspLoginSVR" //FSU注册登录SC响应

#define TOPIC_REQ_MONITOR_DATA      "+/ReqMonitorData/+"    //SVR轮询FSU监控点数据
#define TOPIC_REQ_MONITOR_DATA_ACTION      "ReqMonitorData"    //SVR轮询FSU监控点数据ACTION
#define TOPIC_RSP_MONITOR_DATA      "+/RspMonitorDataSVR/+"  //FSU回复SVR轮询结果
#define TOPIC_RSP_MONITOR_DATA_ACTION     "RspMonitorDataSVR"  //FSU回复SVR轮询结果

/**
 * \brief MQTT客户端初始化
 * @return 成功或失败
 */
int mqtt_init(int client_id, int process_id);

int mqtt_reconnect(int client_id);

bool init_client_arr(int client_id);

/**
 * \brief 建立MQTT链接
 * @return 成功或失败
 */
int mqtt_connect(int id);

/**
 * \brief 销毁MQTT资源
 */
void mqtt_destory(int id);

int message_pub(string payload, const size_t length, char *topic, int client_id);

char * make_topic(const char *strbuf, string source, string destr); //字符串替换处理函数 (用于topic通配符替换)

#endif //EMULATOR_MQTT_H
