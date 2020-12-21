#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

void drawTerminal(unsigned short rows, unsigned short cols, char output[rows][cols]);

int main(){
    //determine the terminal properties
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    
    char output[w.ws_row][w.ws_col];
    int x = 45;
    int y = 20;
    int ymotion = 1;
    int xmotion = 1;
    int tailLength = 5;

    while(1){
        for(int i = 0; i < w.ws_row; i++){
            for(int j = 0; j < w.ws_col; j++){
                if((x == i) && (y == j)){
                    output[i][j] = 'O';
                    for(int k = 1; k <= tailLength; k++){
                        //TODO: Fix this mess, delete ut and renew it.
                        if((i- k*ymotion) < w.ws_row && (j-k*xmotion) < w.ws_col && (i- k*ymotion) > 0 && (j-k*xmotion) > 0){
                            if(xmotion > 0){
                                output[x- k*ymotion][y- k*ymotion] = '+'; 
                            } else{
                                output[x+ k*ymotion][y+ k*ymotion] = '+'; 
                            }
                            
                        }
                    }
                } else{
                    output[i][j] = '.';
                }
            }
        }
        if(x < w.ws_row && x > 0){
            x += xmotion;
        } else{
            xmotion = -xmotion;
            x += xmotion;
        }
        if(y < w.ws_col && y > 0){
            y += ymotion;
        } else{
            ymotion = -ymotion;
            y += ymotion;
        }
        sleep(1);
        drawTerminal(w.ws_row, w.ws_col, output);
    }
}

void drawTerminal(unsigned short rows, unsigned short cols, char output[rows][cols]){
    //printf("\x1b[H");
    //we use system("clear"); because it will delete the history so the terminal doesn't get too big
    system("clear");
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            putchar(output[i][j]);
        }
        putchar('\n');
    }
}