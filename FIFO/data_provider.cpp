#include <string.h>
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

    if ((fd = open(FILEPATH, O_WRONLY)) == -1)
    {
        cout << "open file error" << endl;
        return 1;
    }

    string input;
    while (true)
    {
        cin >> input;
        write(fd, input.data(), input.length());
        cin >> input;
        write(fd, input.data(), input.length());
        
        if (strcmp(input.data(), "quit") == 0)
            break;
    }

    close(fd);
    return 0;

}
