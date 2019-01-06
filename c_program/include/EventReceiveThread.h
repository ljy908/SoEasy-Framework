#ifndef EVENT_RECEIVE_THREAD_H
#define EVENT_RECEIVE_THREAD_H

#include "index.h"

#define _TCP_PORT_ 8000

class CEventReceiveThread
{
    public:
        CEventReceiveThread();
        ~CEventReceiveThread();
        bool GetReceive();

        static void Run(CEventReceiveThread* pArg);
        bool Stop();
    private:
        TCPClient mTcpClient;
};

#endif