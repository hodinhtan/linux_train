#include <stdio.h>
#include <unistd.h>

int main()
{
    FILE* stream;
    stream = popen ("sort", "w");
    fprintf( stream, "This is a Test \n");
    fprintf( stream, "Hello, world!\n");
    fprintf( stream, "The program is great\n");
    fprintf( stream, "This is a Test End \n");
    return pclose( stream );
}
