#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(){
    char* path = "SoundsTemp/set space.txt";
    rename(path, "SoundsTemp/test space.txt");
    printf("%s\n", strerror(errno));
    return 1;
}