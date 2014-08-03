#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
using namespace std;

struct MsgBuf {
    long mtype;
    char msg[80];
};
int main()
{
    key_t key = ftok(".", 'k');
    cout << "key is " << key << endl;
    int msgqid = msgget(key, IPC_CREAT|0666);
    if (msgqid == -1)
    {
        cout << "msgqid == -1 " << errno << endl;
        return 1;
    }

    MsgBuf msgbuf;
    while (true)
    {
        string a, b;
        cin >> a >> b;

        msgbuf.mtype = 1;
        memcpy(msgbuf.msg, a.data(), a.size());
        if (msgsnd(msgqid, &msgbuf, 80,  0) == -1)
        {
            cout << "msgsnd return value is -1 " << errno << endl;
            return 1;
        }

        memcpy(msgbuf.msg, b.data(), b.size());
        if (msgsnd(msgqid, &msgbuf, 80,  0) == -1)
        {
            cout << "msgsnd return value is -1" << endl;
            return 1;
        }
    }

    return 0;
}
