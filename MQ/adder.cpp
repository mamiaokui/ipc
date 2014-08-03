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
        int a, b;
        if (msgrcv(msgqid, &msgbuf, 80, 1, 0) == -1)
        {
            cout << "msgrcv return value is -1" << endl;
            return 1;
        }
        a = atoi(msgbuf.msg);
        cout << a << endl;
        if (strcmp(msgbuf.msg, "quit") == 0)
        {
            break;
        }


        if (msgrcv(msgqid, &msgbuf, 80, 1, 0) == -1)
        {
            cout << "msgrcv return value is -1" << endl;
            return 1;
        }
        b = atoi(msgbuf.msg);
        cout << b << endl;

        cout << a + b << endl;
    }

    msgctl(msgqid, IPC_RMID, 0);
    return 0;
}
