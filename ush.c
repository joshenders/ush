#include <unistd.h>
#include <stdlib.h>

int main() {
    while(1) {
        //system("clear");
        fputs(".", stdout); // prints dots so you know it's doing something
        fflush(stdout);
        sleep(1);
    }
    return(0);
}
