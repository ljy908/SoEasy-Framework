#include "EventReceiveThread.h"

CEventReceiveThread::CEventReceiveThread()
{
    mTcpClient = TCPClient();
    mTcpClient.setup("127.0.0.1", _TCP_PORT_);
}

CEventReceiveThread::~CEventReceiveThread()
{

}

bool CEventReceiveThread::GetReceive()
{
    string strGetMessage;
    while(1)
    {
        strGetMessage = mTcpClient.receive();
        cout << "TEST : " + strGetMessage << endl;
        sleep(1);
    }
}

static void Run(CEventReceiveThread* pArg)
{
    pArg->GetReceive();
}

bool CEventReceiveThread::Stop()
{

}