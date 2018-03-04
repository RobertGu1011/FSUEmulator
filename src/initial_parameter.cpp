//
// Created by guyang on 17-10-11.
//
#include "initial_parameter.h"
#include <zconf.h>
#include <shared_variable.h>
#include <log.h>
#include "tinyxml.h"
#include "mqtt_comm.h"


/*
 *  根据根节点和子节点名，获取该子节点的指针
 */
bool GetNodePointerByName(TiXmlElement *pRootEle, const string &strNodeName, TiXmlElement* &node) {
    //假如等于根节点名，就退出
    if (pRootEle == NULL)
        return false;

    if(strNodeName == pRootEle->Value()) {
        node = pRootEle;
        return true;
    }
    TiXmlElement *pEle = pRootEle;
    for(pEle = pRootEle->FirstChildElement(); pEle; pEle = pEle->NextSiblingElement()) {
        //递归处理子节点，获取节点指针
        if(GetNodePointerByName(pEle, strNodeName, node))
            return true;
    }
    return false;
}

/*
 *  根据文档节点和子节点名，获取子节点的内容
 */
bool QueryNode_Text(TiXmlDocument *pDoc, const string &strNodeName, string &strText)
{
    if(pDoc == NULL) return false;

    pDoc->LoadFile(TIXML_ENCODING_UTF8);
    TiXmlElement *pRootEle = pDoc->RootElement();
    if(pRootEle == NULL) return false;

    TiXmlElement *pNode = NULL;
    GetNodePointerByName(pRootEle, strNodeName, pNode);
    if(pNode != NULL) {
        strText = pNode->GetText();
        return true;
    } else {
        return false;
    }
}

int get_config(std::string file_path) {

    log_i("get config start.....");

    if (access(file_path.c_str(), 0) != 0)
        return 0;

    TiXmlDocument *doc = new TiXmlDocument();
    doc->LoadFile(CONFIG_PATH.c_str(), TIXML_ENCODING_UTF8);
    QueryNode_Text(doc, "BROKERIP", BROKER_IP);
    QueryNode_Text(doc, "SENGINEID", SENGINE_ID);
    QueryNode_Text(doc, "ENTERPRISE", ENTERPRISE);
    QueryNode_Text(doc, "FSUID", FSU_ID);
    QueryNode_Text(doc, "THREAD_NUM", THREAD_NUM_str);
    QueryNode_Text(doc, "SELECT_PAYLOAD", select_payload);
    if (select_payload == "login")
    {
        QueryNode_Text(doc, "PAYLOAD_LOGIN", PAYLOAD);
    } else if (select_payload == "history")
    {
        QueryNode_Text(doc, "PAYLOAD_HISTORY", PAYLOAD);
    }

    delete(doc);

    THREAD_NUM = atoi(THREAD_NUM_str.c_str());

    for (int i = 0; i < 2000; ++i) {
        connection_flag_arr[i] = false;
        init_client_arr(i);
    }
}

