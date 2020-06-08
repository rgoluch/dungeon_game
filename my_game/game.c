#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "dungeon_tools.h"

const int x_max = 80;
const int y_max = 21;

dungeon d; 
void map_set_up();
void room_generation(int num_rooms);
void room_

int main(){

    map_set_up();
    // printf("Map hardness at 79,0: %d\n", d.hardness[79][0]);
    room_generation(6);

    int i; 
    for(i = 0; i < 6; i++){
        printf("Room #%d\n", i);
        printf("Starting x,y: %d,%d\n", d.r[i].start_x, d.r[i].start_y);
        printf("Room width: %d\n", d.r[i].width);
        printf("Room height: %d\n", d.r[i].height);
    }
    

    return 0;
}

void map_set_up(){
    int i;
    for(i = 0; i < x_max; i++){
        d.map[i][0] = rock;
        d.hardness[i][0] = 100;
        d.map[i][20] = rock;
        d.hardness[i][20] = 100;
    }

    for(i = 0; i < y_max; i++){
        d.map[0][i] = rock;
        d.hardness[0][i] = 100;
        d.map[79][i] = rock;
        d.hardness[79][i] = 100;
    }
}

void room_generation(int num_rooms){
    
    srand(time(0));
    int i; 
    for (i = 0; i < num_rooms; i++){
        room temp; 
        int x = 0; 
        int y = 0; 

        //pick the starting corrdinates for the room
        while(x == 0 || y == 0){
            int r = rand()%80;
            if(r != 0){
                x = r;
            }
            r = rand()%21;
            if(r != 0){
                y = r;
            }
        }

        int h,w;
        do{
            w = rand() % 80;
        }while(w < 4);

        do{
            h = rand() % 21;
        }while(h < 3);

        temp.start_x = x; 
        temp.start_y = y;
        temp.height = h;
        temp.width = w;

        //TODO add in check for legal room placement

        d.r[i] = temp;
    }
    
}