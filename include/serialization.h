//
// Created by hf on 15-11-20.
//

#ifndef SC_SERIALIZATION_H
#define SC_SERIALIZATION_H
#include "public_struct.h"
#include <string>

/**
 * \brief 序列化ThresholdDataBean数据结构
 *
 * \param dst 序列化后的字符串
 * \param src 待序列化的数据结构
 *
 */
void threshold_serialization(string &dst, ThresholdDataBean &src);

/**
 * \brief 将string反序列化为ThresholdDataBean数据结构
 *
 * \param src 源字符串
 * \param dst 反序列化的数据结构
 *
 */
void threshold_deserialization(string &src, ThresholdDataBean &dst);

/**
 * \brief 序列化MonitorDataBean数据结构
 *
 * \param dst 序列化后的字符串
 * \param src 待序列化的数据结构
 *
 */
void monitor_serialization(string &dst, MonitorDataBean &src);

/**
 * \brief 将string反序列化为MonitorDataBean数据结构
 *
 * \param src 源字符串
 * \param dst 反序列化的数据结构
 *
 */
void monitor_deserialization(string &src, MonitorDataBean &dst);

/**
 * \brief 将string反序列化为FsuLoginInfo数据结构
 *
 * \param src 源字符串
 * \param dst 反序列化的数据结构
 *
 */
int fsu_logininfo_deserialization(string &src, FsuLoginInfo &dst);

/**
 * \brief 将FsuLoginInfo数据结构序列化为string
 * \param dst 目标字符串
 * \param src 要序列化的数据结构
 *
 */
int fsu_logininfo_serialization(string &dst, FsuLoginInfo &src);

/**
 * \brief 将string反序列化为vector<BBDS_DeviceProp>数据结构
 *
 * \param src 源字符串
 * \param dst 反序列化的数据结构
 *
 */
void device_prop_deserialization(string &src, vector<BBDS_DeviceProp> &dst);

void timeinfo_serialization(TTime &src, string &dst);

/**
 * \brief 将MonitorDataBean数据结构的数据打印出来
 *
 * \param bean MonitorDataBean数据结构
 *
 */
void print_MonitorDataBean(MonitorDataBean &bean);

/**
 * \brief 将门限值(ThresholdDataBean数据结构)的数据打印出来
 *
 * \param bean ThresholdDataBean数据结构
 *
 */
//void print_ThresholdDataBean(ThresholdDataBean &threshold);

#endif //SC_SERIALIZATION_H
