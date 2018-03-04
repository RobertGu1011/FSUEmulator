//
// Created by guyang on 17-10-10.
//

#include "mqtt_comm.h"
#include <unistd.h>
#include "log.h"

static MQTTAsync client[2000];
static MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
static MQTTAsync_willOptions will = MQTTAsync_willOptions_initializer;

bool init_client_arr(int client_id) {
    client[client_id] = nullptr;
}

void connlost(void *context, char *cause)
{
    log_e("Connection lost  cause[%s]",cause);
    MQTTAsync client_temp = (MQTTAsync) context;

    for (int i = 0; i < THREAD_NUM;) {

        if (client_temp == client[i])
        {
            connection_flag_arr[i] = false;
            mqtt_reconnect(i);
            break;
        }else i++;
    }

}

void onConnectFailure(void* context, MQTTAsync_failureData* response)
{
    if(response != NULL) {
        log_e("Connect failed, rc [%d], message[%s]", response->code, response->message);
    }
    MQTTAsync client_temp = (MQTTAsync) context;

    for (int i = 0; i < THREAD_NUM;) {
        if (client_temp == client[i]){
            connection_flag_arr[i] = false;
            mqtt_reconnect(i);
            break;
        } else i++;
    }


}

void onSubscribe(void* context, MQTTAsync_successData* response)
{
    log_i("Subscribe succeeded");
    MQTTAsync client_temp = (MQTTAsync) context;

    for (int i = 0; i < THREAD_NUM;) {
        if (client_temp == client[i]){
            connection_flag_arr[i] = true;
            break;
        } else i++;
    }
}

void onSubscribeFailure(void* context, MQTTAsync_failureData* response)
{
    log_e("Subscribe failed rc[%d] sleep 5s and reconnect", response ? response->code : 0);
    MQTTAsync client_temp = (MQTTAsync) context;

    for (int i = 0; i < THREAD_NUM;) {
        if (client_temp == client[i]) {
            connection_flag_arr[i] = false;
            mqtt_reconnect(i);
            break;
        } else i++;
    }
}

int connection_mosquitto_server_count = 0;
void onConnect(void* context, MQTTAsync_successData* response)
{
    int rc;
    MQTTAsync client_temp = (MQTTAsync)context;

//    string dest_fsu = "";

    for (int i = 0; i < THREAD_NUM;) {
        if (client_temp == client[i])
        {
//            dest_fsu = topic_arr[i];
            connection_flag_arr[i] = true;
            break;
        } else i++;
    }

    MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;

    string dest_fsu = ENTERPRISE+FSU_ID;
    string src_server = SENGINE_ID;
    char * topic_fsu_loginscack = make_topic(TOPIC_RSP_LOGINSVR_ACK, src_server, dest_fsu);
    char * topic_svr_logout = make_topic(TOPIC_SVR_LOGOUT, src_server, "+");
    char * topic_get_monitordata = make_topic(TOPIC_REQ_MONITOR_DATA, src_server, dest_fsu);

    log_i("Successful connection mosquitto server---client[%d]",connection_mosquitto_server_count);
    if (connection_mosquitto_server_count < thread_num)
        connection_mosquitto_server_count++;
    else connection_mosquitto_server_count = 0;

    opts.onSuccess = onSubscribe;
    opts.onFailure = onSubscribeFailure;
    opts.context = client_temp;

    if ((rc = MQTTAsync_subscribe(client_temp, topic_fsu_loginscack, QOS, &opts)) != MQTTASYNC_SUCCESS) {
        log_e("Failed to start subscribe[%s], return code[%d]", topic_fsu_loginscack, rc);
    }
    if ((rc = MQTTAsync_subscribe(client_temp, topic_svr_logout, QOS, &opts)) != MQTTASYNC_SUCCESS) {
        log_e("Failed to start subscribe[%s], return code[%d]", topic_svr_logout, rc);
    }
    if ((rc = MQTTAsync_subscribe(client_temp, topic_get_monitordata, QOS, &opts)) != MQTTASYNC_SUCCESS) {
        log_e("Failed to start subscribe[%s], return code[%d]", topic_get_monitordata, rc);
    }

    free(topic_fsu_loginscack);
    free(topic_svr_logout);
    free(topic_get_monitordata);

}

void MQTTAsync_setwillopts(MQTTAsync_willOptions * will)
{
    string ein = ENTERPRISE;
    will->message = ein.c_str();
    will->topicName = make_topic(TOPIC_FSU_LOGOUT, FSU_ID, SENGINE_ID);
    will->qos = 2;
}


void setConn_opts(MQTTAsync_connectOptions * conn_opts , int keepAliveInterval , int cleansession ,
                         MQTTAsync_onSuccess * onSuccess, MQTTAsync_onFailure * onFailure , void * context, MQTTAsync_willOptions * will )
{
    conn_opts->keepAliveInterval = keepAliveInterval;
    conn_opts->cleansession = cleansession;
    conn_opts->onSuccess = onSuccess;
    conn_opts->onFailure = onFailure;
    conn_opts->context = context;
    conn_opts->will = will;
}

void onSendpub(void* context, MQTTAsync_successData* response)
{
    log_i("Message with token value %d delivery confirmed", response->token);
}

char * make_topic(const char *strbuf, string source, string destr)
{
    char * p;
    string action, topic;
    int len;
    topic = strbuf;
    len = (int) topic.length();
    action = topic.substr(1, len-2);
    topic = source + action + destr;
    len = (int) topic.length();
    p = (char*)malloc(sizeof(char)*len + 1);
    strcpy(p, topic.c_str());
    return p;
}

int message_pub(string payload, const size_t length, char *topic, int client_id){
    int rc;
    char * buffer;
    MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
    MQTTAsync_message pubmsg = MQTTAsync_message_initializer;

    opts.onSuccess = onSendpub;
    opts.context = client[client_id];

    buffer = (char *)malloc( payload.length() * sizeof(char) );
    memcpy(buffer, payload.c_str(), payload.length());

    pubmsg.payload = buffer;
    pubmsg.payloadlen = (int) length;
    pubmsg.qos = QOS;
    pubmsg.retained = 0;

    if ((rc = MQTTAsync_sendMessage(client[client_id], topic, &pubmsg, &opts)) != MQTTASYNC_SUCCESS) {
        log_e("Failed to start sendMessage, return code %d", rc);
        rc = -1;
    }
    log_i("Send message with topic : \"%s\" ",topic);
    log_d("message :len:%d", length);
    free(buffer);
    return rc;
}

int msgarrvd(void *context, char *topicName, int topicLen, MQTTAsync_message *message)
{
    if(message->payload == nullptr) {
        log_e("empty payload rcv topic[%s],throw it", topicName);
        return 0;
    }

    log_i("arrived topic name is [%s]", topicName);
    log_i("arrived message is [%s]", (char *) message->payload);
    return 1;
}

int mqtt_connect(int client_id)
{
    log_i("starting connect broker[%d]...", client_id);
    int rc = MQTTAsync_connect(client[client_id], &conn_opts);
    if ( rc != MQTTASYNC_SUCCESS) {
        log_e("Failed to start connect, return code %d\n", rc);
        connection_flag_arr[client_id] = false;
        return rc;
    }
    connection_flag_arr[client_id] = true;
    log_i("connect broker success");
    return rc;
}

int mqtt_init(int client_id, int process_id)
{
    MQTTAsync_setwillopts(&will);
    string mqtt_client_id = "FSU"+ to_string(process_id) + to_string(client_id)+"_Client_" + ENTERPRISE + FSU_ID;
//    string mqtt_client_id = "FSU_Client_"  + ENTERPRISE + FSU_ID;
    topic_arr[client_id] = mqtt_client_id;
    int rc = MQTTAsync_create(&client[client_id], BROKER_IP.c_str(), mqtt_client_id.c_str(), MQTTCLIENT_PERSISTENCE_NONE, nullptr);
    if(rc != MQTTASYNC_SUCCESS) {
        log_e("MQTT client create error code[%d] message", rc);
        goto out;
    }
    rc = MQTTAsync_setCallbacks(client[client_id], client[client_id], connlost, msgarrvd, nullptr);
    if(rc != MQTTASYNC_SUCCESS) {
        log_e("MQTT callbacks set error code[%d] message", rc);
        goto out;
    }
    setConn_opts(&conn_opts, 20, 1, onConnect, onConnectFailure, client[client_id], &will);

    out:
    if(rc == FUNC_SUCCESS) {
        log_i("mqtt init success");
    } else {
        log_e("mqtt init fail");
    }
    return rc;
}

int mqtt_reconnect(int client_id)
{
    log_i("starting reconnect broker...");

    int rc = MQTTAsync_connect(client[client_id], &conn_opts);
    if ( rc != MQTTASYNC_SUCCESS) {
        log_e("Failed to start connect, return code %d\n", rc);
        connection_flag_arr[client_id] = false;
    }

    connection_flag_arr[client_id] = true;
    return rc;
}

void mqtt_destory(int client_id)
{
    MQTTAsync_destroy(&client[client_id]);
    connection_flag_arr[client_id] = false;
    log_i("destory mqtt resources");
}
