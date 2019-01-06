#include "index.h"

using namespace std;

int main(int argc, char *argv[])
{
    CEventReceiveThread *eventReceiveThread = new CEventReceiveThread();
    eventReceiveThread->GetReceive();
}