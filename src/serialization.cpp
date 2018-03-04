//
// Created by hf on 15-11-20.
//

#include <sstream>
#include <string>
#include "serialization.h"
#include "public_struct.h"
#include "log.h"

#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
using namespace std;

/*
 * 将MonitorDataBean数据结构的数据打印出来
 */
void print_MonitorDataBean(MonitorDataBean &bean)
{
    log_d("HisMonitorDataBean:");
    log_d("Result: %s", bean.Result.c_str());
    log_d("  FsuKey:");
    log_d("  %s %s %s", bean.FsuKey.FsuId.c_str(),  bean.FsuKey.FsuCode.c_str(), bean.FsuKey.Infos.c_str());

    map<DeviceKeyStruct, vector<TSemaphore> >::iterator it;
    for(it = bean.MapData.begin(); it != bean.MapData.end(); it++)
    {
        log_d("\tDevice:");

        log_d("\t%s %s", it->first.DeviceId.c_str(), it->first.DeviceCode.c_str());
        vector<TSemaphore>vt = it->second;
        for(unsigned int i = 0; i < vt.size(); i++)
        {
            log_d("\tTSemphore:");
            log_d("\t  Type = %s ID = %s MeasuredVal = %s SetupVal = %s Status = %s RecordTime = %s",
                  vt[i].Type.c_str(), vt[i].ID.c_str(), vt[i].MeasuredVal.c_str(),
                  vt[i].SetupVal.c_str(), vt[i].Status.c_str(), vt[i].RecordTime.c_str());
        }
        log_d("");
    }
}

/*
 * 将门限值(ThresholdDataBean数据结构)的数据打印出来
 */
//void print_ThresholdDataBean(ThresholdDataBean &threshold)
//{
//    log_i("ThresholdDataBean:");
//    log_i("  %s", threshold.Result.c_str());
//    log_i("  FsuKey:");
//    log_i("  %s %s %s", threshold.FsuKey.FsuId.c_str(), threshold.FsuKey.FsuCode.c_str(),
//          threshold.FsuKey.Infos.c_str());
//
//    map<DeviceKeyStruct, vector<TThreshold> >::iterator it;
//    for(it = threshold.MapData.begin(); it != threshold.MapData.end(); it++)
//    {
//        log_i("\tDevice:");
//
//        log_i("\t%s %s", it->first.DeviceId.c_str(), it->first.DeviceCode.c_str());
//        vector<TThreshold>vt = it->second;
//
//        for(unsigned int i = 0; i < vt.size(); i++)
//        {
//            log_i("\tTThreshold:");
//            log_i("\t  Type = %s ID = %s Threshold = %s AbsoluteVal = %s RelativeVal = %s Status = %s",
//                  vt[i].Type.c_str(), vt[i].ID.c_str(), vt[i].Threshold.c_str(), vt[i].AbsoluteVal.c_str(),
//                  vt[i].RelativeVal.c_str(), vt[i].Status.c_str());
//        }
//    }
//}

/*
 * 序列化ThresholdDataBean数据结构
 */
void threshold_serialization(string &dst, ThresholdDataBean &src)
{
    ostringstream os;
    boost::archive::text_oarchive oa(os);
    oa << src;
    dst = os.str();
}

/*
 * 将string反序列化为ThresholdDataBean数据结构
 */
void threshold_deserialization(string &src, ThresholdDataBean &dst)
{
//    istringstream is(src);
//    boost::archive::text_iarchive ia(is);
//    ia >> dst;
    try {
        if (src.size() == 0) {
            log_e("src.size()[%u]", src.size());
        }
        istringstream is(src);
        if (is.good()) {
            log_i("istringstream is good");
            boost::archive::text_iarchive ia(is);
            log_i("iarchive ia is good");
            ia >> dst;
            log_i("iarchive ia>>dst good");
        } else {
            log_e("istringstream is not complete");
        }
    } catch(std::exception &ex) {
        log_e("threshold_deserialization error[%s]", ex.what());
    }
}

/*
 * 序列化MonitorDataBean数据结构
 */
void monitor_serialization(string &dst, MonitorDataBean &src)
{
    ostringstream os;
    boost::archive::text_oarchive oa(os);
	oa << src;
    dst = os.str();
}

/*
 * 将string反序列化为MonitorDataBean数据结构
 */
void monitor_deserialization(string &src, MonitorDataBean &dst)
{
//    istringstream is(src);
//	boost::archive::text_iarchive ia(is);
//	ia >> dst;
    try {
        if (src.size() == 0) {
            log_e("src.size()[%u]", src.size());
        }
        istringstream is(src);
        if (is.good()) {
            log_i("istringstream is good");
            boost::archive::text_iarchive ia(is);
            log_i("iarchive ia is good");
            ia >> dst;
            log_i("iarchive ia>>dst good");
        } else {
            log_e("istringstream is not complete");
        }
    } catch(std::exception &ex) {
        log_e("monitor_deserialization error[%s]", ex.what());
    }
}

int fsu_logininfo_serialization(string &dst, FsuLoginInfo &src)
{
    ostringstream os;
    boost::archive::text_oarchive oa(os);
    oa << src;
    dst = os.str();
}

/*
 * 将string反序列化为FsuLoginInfo数据结构
 */
int fsu_logininfo_deserialization(string &src, FsuLoginInfo &dst)
{
    int result = -1;

    try {
        if (src.size() == 0) {
            log_e("src.size()[%u]", src.size());
            return result;
        }
        istringstream is(src);
        if (is.good()) {
            log_i("istringstream is good");
            boost::archive::text_iarchive ia(is);
            log_i("iarchive ia is good");
            ia >> dst;
            log_i("iarchive ia>>dst good");
            result = 0;
        } else {
            log_e("istringstream is not complete");
        }
    } catch(std::exception &ex) {
        result = -1;
        log_e("fsu_logininfo_deserialization error[%s]", ex.what());
    }

    return result;
}

/*
 * 将string反序列化为vector<BBDS_DeviceProp>数据结构
 */

void device_prop_deserialization(string &src, vector<BBDS_DeviceProp> &dst)
{
//    istringstream is(src);
//    boost::archive::text_iarchive ia(is);
//    ia >> dst;

    try {
        if (src.size() == 0) {
            log_e("src.size()[%u]", src.size());
        }
        istringstream is(src);
        if (is.good()) {
            log_i("istringstream is good");
            boost::archive::text_iarchive ia(is);
            log_i("iarchive ia is good");
            ia >> dst;
            log_i("iarchive ia>>dst good");
        } else {
            log_e("istringstream is not complete");
        }
    } catch(std::exception &ex) {
        log_e("device_prop_deserialization error[%s]", ex.what());
    }
}

/*
 * 序列化TTime数据结构
 */
void timeinfo_serialization(TTime &src, string &dst)
{
    ostringstream os;
    boost::archive::text_oarchive oa(os);
    oa << src;
    dst = os.str();
}