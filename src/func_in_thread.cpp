//
// Created by guyang on 17-10-11.
//
#include <zconf.h>
#include <serialization.h>
#include "func_in_thread.h"
#include "mqtt_comm.h"

void * pub_payload(void *arg) {

    char * topic;
    if (select_payload == "login")
    {
        topic = make_topic(TOPIC_FSU_LOGIN_SVR, topic_arr[(int)arg], SENGINE_ID);
    }
    else if (select_payload == "history")
    {
        topic = make_topic(TOPIC_RSP_MONITOR_DATA, topic_arr[(int)arg], SENGINE_ID);
    }
    while(1) {
        if (connection_flag_arr[(int)arg]) {
            message_pub(PAYLOAD, PAYLOAD.size(), topic, (int) arg);
        } else {
            sleep(3);
            continue;
        }
    }
    free(topic);
    return (void *) nullptr;
}

void * pub_payload1(void *arg) {

    char * topic;
    if (select_payload == "login")
    {
        topic = make_topic(TOPIC_FSU_LOGIN_SVR, topic_arr[(int)arg], SENGINE_ID);
    }
    else if (select_payload == "history")
    {
        topic = make_topic(TOPIC_RSP_MONITOR_DATA, topic_arr[(int)arg], SENGINE_ID);
    }

    if (connection_flag_arr[(int)arg])
        message_pub(PAYLOAD, PAYLOAD.size(), topic, (int) arg);

    free(topic);
    return (void *) nullptr;
}
