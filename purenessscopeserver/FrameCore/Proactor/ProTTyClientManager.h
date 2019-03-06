#ifndef _PROTTYCLIENTMANAGER_H
#define _PROTTYCLIENTMANAGER_H

//TTy�豸��Proactorʵ��
//add by freeeyes

#include "TimerManager.h"
#include "ITTyClientManager.h"
#include "ProTTyHandler.h"
#include "HashTable.h"
#include "XmlConfig.h"

class CProTTyClientManager : public ACE_Task<ACE_MT_SYNCH>, public ITTyClientManager
{
public:
    CProTTyClientManager();
    virtual ~CProTTyClientManager();

    bool StartConnectTask();                                                                             //������ʱ��
    void CancelConnectTask();                                                                            //�رն�ʱ��

    bool Init(ACE_Proactor* pProactor, uint16 u2MaxTTyCount, uint16 u2TimeCheck);                        //��ʼ��������
    void Close();                                                                                        //�ر���������

    virtual int Connect(uint16 u2ConnectID, const char* pName, _TTyDevParam& inParam, ITTyMessage* pMessageRecv);  // ���ӣ��򿪣��˿�

    virtual bool GetClientDevInfo(uint16 u2ConnectID, _TTyDevParam& outParam);                           // ��ȡ����������Ϣ
    virtual bool IsConnect(uint16 u2ConnectID);                                                          // �Ƿ����ӣ��򿪣�״̬

    virtual bool Close(uint16 u2ConnectID);                                                              // �رն˿�
    virtual bool Pause(uint16 u2ConnectID);                                                              // ��ͣ�˿�
    virtual bool Resume(uint16 u2ConnectID);                                                             // �ָ���ͣ�˿�

    virtual bool SendMessage(uint16 u2ConnectID, char*& pMessage, uint32 u4Len);                         // ��������

    virtual int handle_timeout(const ACE_Time_Value& tv, const void* arg);                               //��ʱ���
private:
    CHashTable<CProTTyHandler> m_objTTyClientHandlerList;            //�����豸�б�
    ACE_Recursive_Thread_Mutex m_ThreadWritrLock;                    //�߳���
    ACE_Proactor*              m_pProactor;                          //��Ӧ�����
    uint16                     m_u2MaxListCount;                     //����豸����
    uint16                     m_u2TimeCheck;                        //��ʱ�����ʱ��
    int                        m_nTaskID;                            //��ʱ��ID
};

typedef ACE_Singleton<CProTTyClientManager, ACE_Recursive_Thread_Mutex> App_ProTTyClientManager;


#endif