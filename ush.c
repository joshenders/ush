#include <stdio.h>  // fflush(), printf()
#include <unistd.h> // sleep(), system()
#include <time.h>   // ctime(), time()

void spin() {
    char spinChar[4];

    spinChar[0] = '|';
    spinChar[1] = '/';
    spinChar[2] = '-';
    spinChar[3] = '\\';
    spinChar[4] = '\0';

    int i;

    for (i = 0; i < 4; i++) {
        system("tput cub 1");
        printf("%c", spinChar[i]);
        fflush(stdout);
        sleep(1);
    }

}

int main() {
    time_t now;
    time(&now);

    printf("Connected since %s", ctime(&now));
    while(1) {
        spin();
    }
    return(0);
}
