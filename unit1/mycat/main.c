#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int myCatfd(int ifd, int ofd);
int myCatfp(FILE *ifp, FILE *ofp);

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        if (myCatfd(0, 1) != 0)
            fprintf(stderr, "failed to copy standard input\n");
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            int fd = open(argv[i], O_RDONLY); // had to include fcntl.h to get O_RDONLY
            if (fd < 0)
                fprintf(stderr, "failed to open %s for reading\n", argv[i]);
            else
            {
                if (myCatfd(fd, 1) != 0)
                    //fprintf(stderr, "failed to copy %d to standard output\n", argv[i]);
                close(fd); // had to include unistd.h to get close()
            }
        }
    }

    return 0;
}

int myCatfd(int ifd, int ofd)
{
    char buffer[4096];
    ssize_t nbytes;
    while ((nbytes = read(ifd, buffer, sizeof(buffer))) > 0)
    {
        if (write(ofd, buffer, nbytes) != nbytes)
            return -1;
    }
    return (nbytes < 0) ? -1 : 0;
}