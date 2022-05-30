/*
 * File:   mycat.c
 * Author: galortega
 *
 * Created on May 28, 2022, 18:17 PM
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFFER_SIZE 1024

int myCatfd(int ifd, int ofd);

int main(int argc, char *argv[])
{
    if (argc == 1) // stdin to stdout
    {
        if (myCatfd(0, 1) != 0)
        {
            fprintf(stderr, "failed to copy standard input\n");
            perror(NULL); // print error message
        }
    }
    else // if argument is given
    {
        for (int i = 1; i < argc; i++)
        {
            int fd = open(argv[i], O_RDONLY); // had to include fcntl.h to get O_RDONLY
            if (fd < 0)
            {
                fprintf(stderr, "failed to open %s for reading\n", argv[i]);
                perror(NULL);
            }
            else
            {
                if (myCatfd(fd, 1) != 0)
                {
                    fprintf(stderr, "failed to copy %s to standard output\n", argv[i]);
                    perror(NULL);
                }
                close(fd); // had to include unistd.h to get close()
            }
        }
    }

    return 0;
}

// myCatfd: copies the contents of the file descriptor ifd to the file descriptor ofd
int myCatfd(int ifd, int ofd)
{
    char buffer[BUFFER_SIZE];
    ssize_t nbytes;
    while ((nbytes = read(ifd, buffer, sizeof(buffer))) > 0) // had to include unistd.h to get read()
    {
        if (write(ofd, buffer, nbytes) != nbytes) // had to include unistd.h to get write()
        {
            perror(NULL);
            fprintf(stderr, "failed to write to standard output\n");
            return -1; // had to include stdlib.h to get EXIT_FAILURE
        }
    }
    return (nbytes < 0) ? -1 : 0; // -1 if error, 0 if success
}