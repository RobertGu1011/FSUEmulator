//
// Created by guyang on 17-10-10.
//

#ifndef FSUEMULATOR_PUBLIC_STRUCT_H
#define FSUEMULATOR_PUBLIC_STRUCT_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <map>
#include <vector>
#include <list>
#include "public_struct.h"

using namespace std;

extern string CONFIG_PATH;
extern string BROKER_IP;
extern string SENGINE_ID;
extern string ENTERPRISE;
extern string FSU_ID;
extern string PAYLOAD;

#define thread_num 500
extern string THREAD_NUM_str;
extern int THREAD_NUM;
extern string select_payload;
extern string topic_arr[2000];
extern bool connection_flag_arr[2000];

#define QOS 2

#define FUNC_SUCCESS 0
#define FUNC_FAIL 1

#endif //FSUEMULATOR_PUBLIC_STRUCT_H
