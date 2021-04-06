/*表驱动应用，播放器player状态机转化*/
#include<iostream>
using namespace std;

enum player_state
{
    PLAY_STOP,
    PLAY_PAUSE,
    PLAY_PLAY,

    PLAY_STATE_BUTT
};
enum player_cmd
{
    DO_PLAY,
    DO_PAUSE,
    DO_STOP,

    DO_BUTT
};

typedef struct my_player_s
{
    int state;
}my_player_t;

void do_play(my_player_t& player)
{
    cout<<"this is do play"<<endl;
    player.state=PLAY_PLAY;
}

void do_pause(my_player_t& player)
{
    cout<<"this is do pause"<<endl;
    player.state=PLAY_PAUSE;
}

void do_stop(my_player_t& player)
{
    cout<<"this is do stop"<<endl;
    player.state=PLAY_STOP;
}

typedef void(*doCmdFunc_t)(my_player_t& player);

/* state|STOP|PAUSE|PLAY*/
static const doCmdFunc_t g_state_map[][PLAY_STATE_BUTT]
{
    {do_play, do_play, NULL}, // action:do paly
    {NULL, NULL, do_pause},   // action:do pause
    {NULL, do_stop, do_stop}  // action:do stop
};

void doPlayerCmd(my_player_t& player,int cmd)
{
    doCmdFunc_t func = g_state_map[cmd][player.state];

    if (func)
    {
        func(player);
    }
}

void playerStop(my_player_t& player)
{
    doPlayerCmd(player,DO_STOP);
}

void playerPause(my_player_t& player)
{
    doPlayerCmd(player,DO_PAUSE);
}

void playerPlay(my_player_t& player)
{
    doPlayerCmd(player,DO_PLAY);
}

int main()
{
    my_player_t player;
    player.state = PLAY_PLAY;
    cout<<"the player state is:"<<player.state<<endl;
    playerPause(player);
    cout<<"the player state is:"<<player.state<<endl;
    playerStop(player);
    cout<<"the player state is:"<<player.state<<endl;
    playerPlay(player);
    cout<<"the player state is:"<<player.state<<endl;

    return 0;
}
