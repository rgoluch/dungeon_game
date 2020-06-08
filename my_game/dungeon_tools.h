static const char rock = ' ';
static const char room_floor = '.';
static const char corridor = '#';
static const char up_stair = '<';
static const char down_stair = '>';

typedef struct room{
    int start_x;
    int start_y;
    int width; 
    int height;

}room;

typedef struct dungeon{
    room r[6];
    char map[80][21];
    int hardness[80][21];
}dungeon;