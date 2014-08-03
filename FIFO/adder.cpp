#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
using namespace std;

#define FILEPATH "/tmp/myfifo"
int main()
{
    int fd = -1;
    unlink(FILEPATH);
    if (mkfifo(FILEPATH, 0777) == -1)
    {
        cout << "mkfifo error" << endl;
        return 1;
    }

    if ((fd = open(FILEPATH, O_RDONLY)) == -1)
    {
        cout << "open file error" << endl;
        return 1;
    }

    char buffer[80];
    while (true)
    {
        read(fd, buffer, sizeof(buffer));
        int a = atoi(buffer);
        cout << "get " << a << endl;
        read(fd, buffer, sizeof(buffer));
        int b = atoi(buffer);
        cout << "get " << b << endl;
        cout << a + b << endl;
        if (a + b == 0)
            break;
    }
    close(fd);
    return 0;

}
