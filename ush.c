#include <stdio.h>  // fflush(), printf()
#include <unistd.h> // sleep(), system()
#include <time.h>   // ctime(), time()

int main() {
    char *spinChar = "|/-\\";
    int i;
    time_t connected;
    time(&connected);

    system("clear");

    while(1) {
        for (i = 0; i < 4; i++) {
            system("tput cup 0 0"); // move cursor to top left of screen
            printf("%c\t", spinChar[i]);
            printf("Connected since %s", ctime(&connected));
            sleep(1);
        }
    }
    return(0);
}
