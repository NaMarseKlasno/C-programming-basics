#define _DEFAULT_SOURCE
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <signal.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>


WINDOW *menuWin;
WINDOW *lvl_1;
WINDOW *lvl_2;
WINDOW *lvl_3;
WINDOW *dashboard;
WINDOW *TimerPanel;

// em


struct{
    char map[24][81];
    char map1[24][81];
    bool presX1;
}level1;
struct{
    char map_2[24][81];
    char map2[24][81];
    bool presX2;
}level2;

struct{
    char map_3[24][81];
    char map3[24][81];
    bool presX3;
    bool presX3_2;
    bool presX3_3;
    bool presX3_4;
    bool presX3_5;
    bool presX3_6;
}level3;

struct{
    int x, y;
    int kx, ky;
}player;

struct{
    int bx, by;
    int YgravSt;
}ball;

struct{
    char argument1[20];
    char argument2[20];
}args;

struct{
    bool RestartPlayPick;
    bool FastQuit;
}log_menu;

struct{
    unsigned long repetitions;
    int seconds;
    int minutes;
    int sec;
}timex;



struct{
    int coins;
    int bombs;
    short nlvl;
    short lives;
}dashpanel;

void *timer(void *data){
    timex.sec = 59;
    int interval = *(int *)data;
    for (;;) {
        if (timex.repetitions > 0) {
            timex.sec--;
            if (timex.sec == -1 && timex.minutes > 0){
                timex.minutes--;
                timex.sec = 59;
            }
            usleep(interval);
            if(timex.sec >= 0)
                timex.seconds = timex.sec;
            
                
        }
    }
}

bool Kill_p_Collision(short numLvl){
    if (numLvl == 1) {
        if (level1.map1[player.y][player.x] == '*' ||
            level1.map1[player.y][player.x+1] == '*' ||
            level1.map1[player.y][player.x+2] == '*' ||
            level1.map1[player.y+1][player.x] == '*' ||
            level1.map1[player.y+1][player.x+1] == '*' ||
            level1.map1[player.y+1][player.x+2] == '*' ) {
            return true;
        }
        else{
            return false;
        }
    }
    else if (numLvl == 2){
        if (level2.map2[player.y][player.x] == '*' ||
            level2.map2[player.y][player.x+1] == '*' ||
            level2.map2[player.y][player.x+2] == '*' ||
            level2.map2[player.y+1][player.x] == '*' ||
            level2.map2[player.y+1][player.x+1] == '*' ||
            level2.map2[player.y+1][player.x+2] == '*' ) {
            return true;
        }
        else{
            return false;
        }
    }
    else if (numLvl == 3){
        if (level3.map3[player.y][player.x] == '*' ||
            level3.map3[player.y][player.x+1] == '*' ||
            level3.map3[player.y][player.x+2] == '*' ||
            level3.map3[player.y+1][player.x] == '*' ||
            level3.map3[player.y+1][player.x+1] == '*' ||
            level3.map3[player.y+1][player.x+2] == '*' ) {
            return true;
        }
        else{
            return false;
        }
    }
    return false;
}
int is_pressed_button(int numLvl);
void PutEnemies_lvl_1(void);
void PutEnemies_lvl_2(void);
void PutEnemies_lvl_3(void);

bool winCol(int lvl);
int pick_coin(short numLvl);

void CheckAndPut(int rx, int ry, short numLvl);

void about_the_game(){
    wclear(menuWin);
    wrefresh(menuWin);
    keypad(menuWin, false);
    
    WINDOW *aboutGame = newwin(15, 80, 9, 0);
    keypad(aboutGame, true);
    //box(aboutGame, 0, 0);
    wrefresh(aboutGame);
    start_color();
    init_pair(15, COLOR_RED, -1);
    mvwaddstr(aboutGame, 14, 1, "Press ESC to return to the menu");
    
    wattron(aboutGame, COLOR_PAIR(15) | A_BOLD);
    
    mvwaddstr(aboutGame, 1, 1, "Prehistory:");
    mvwaddstr(aboutGame, 1, 41, "Basic Rules:");
    mvwaddstr(aboutGame, 9, 1, "GAME PROMISSES TO BE CHALLENGING!");
    mvwaddstr(aboutGame, 11, 41, "GOOD LUCK!");

    
    mvwaddstr(aboutGame, 14, 51, "Lad Coder:");
    wattroff(aboutGame, COLOR_PAIR(15) | A_BOLD);
    mvwaddstr(aboutGame, 3, 1, "The player got to the Death Factory,");
    mvwaddstr(aboutGame, 4, 1, "where he has to defend himself from");
    mvwaddstr(aboutGame, 5, 1, "the moving murder weapon.");
    mvwaddstr(aboutGame, 6, 1, "In parallel passing different");
    mvwaddstr(aboutGame, 7, 1, "locations of the plant."  );

    mvwaddstr(aboutGame, 3, 41, "1. The player must not touch '*'.");
    mvwaddstr(aboutGame, 4, 41, "2. The player has three minutes");
    mvwaddstr(aboutGame, 5, 41, "for each level.");
    mvwaddstr(aboutGame, 6, 41, "3. To go to the next level, the player");
    mvwaddstr(aboutGame, 7, 41, "collect a certain number of coins.");
    mvwaddstr(aboutGame, 8, 41, "and to switch the level you need");
    mvwaddstr(aboutGame, 9, 41, "to stand on the button (WIN)");


    mvwaddstr(aboutGame, 14, 62, "Stanislav Voloshyn");

    
    while (wgetch(aboutGame) != 27) {
    }
    keypad(menuWin, true);
    keypad(aboutGame, false);
    wclear(aboutGame);
    wrefresh(aboutGame);
}

void GAME_WON_MENU(){
    wclear(lvl_1);
    wclear(lvl_2);
    wclear(lvl_3);
    wclear(dashboard);
    wrefresh(lvl_2);
    wrefresh(lvl_1);
    wrefresh(lvl_3);
    wrefresh(dashboard);

    char Won[8][71];
    WINDOW *GameWon = newwin(9, 71, 2, 8);
    wmove(GameWon, 0, 0);
    FILE *gameWonfp = fopen(args.argument1, "r");
    
    for (int i = 0; i < 8; i++) {
        fgets(Won[i], 70, gameWonfp);
    }
    init_pair(14, COLOR_RED, -1 );
    wattron(GameWon, 14 | COLOR_PAIR(14) | A_BOLD);
    for (int i = 0; i < 8; i++) {
        wprintw(GameWon, Won[i]);
    }
    wattroff(GameWon, 14 | COLOR_PAIR(14) | A_BOLD);
    //box(GameWon, 0, 0);
    wrefresh(GameWon);
    fclose(gameWonfp);
    
    WINDOW *titlWon = newwin(12, 80, 12, 0);
    init_pair(15, COLOR_RED, -1);
    mvwaddstr(titlWon, 11, 1, "Press ESC to return to the menu");

    wattron(titlWon, COLOR_PAIR(15));
    mvwaddstr(titlWon, 2, 31, "Executive Director");

    mvwaddstr(titlWon, 5, 28, "Executive Vice President");
    mvwaddstr(titlWon, 8, 35, "Lad Coder");
    wattroff(titlWon, COLOR_PAIR(15));
    
    mvwaddstr(titlWon, 3, 31, "Stanislav Voloshyn");
    mvwaddstr(titlWon, 6, 31, "Stanislav Voloshyn");
    mvwaddstr(titlWon, 9, 31, "Stanislav Voloshyn");

    wrefresh(titlWon);
    keypad(titlWon, true);
    while (wgetch(titlWon) != 27) {
    }

}

void GAME_OVER_MENU(){
    wclear(lvl_1);
    wclear(lvl_2);
    wclear(lvl_3);
    wclear(dashboard);
    wrefresh(lvl_2);
    wrefresh(lvl_1);
    wrefresh(lvl_3);
    wrefresh(dashboard);

    WINDOW *GameOver = newwin(6, 100, 3, 8);

    
    wmove(GameOver, 0, 0);
    FILE *gameOverfp = fopen(args.argument2, "r");
    char arr2[8][63];

    for (int i = 0; i < 8; i++) {
        fgets(arr2[i], 62, gameOverfp);
    }
    init_pair(14, COLOR_RED, -1 );
    wattron(GameOver, 14 | COLOR_PAIR(14) | A_BOLD);
    for (int i = 0; i < 8; i++) {
        wprintw(GameOver, arr2[i]);
    }
    wattroff(GameOver, 14 | COLOR_PAIR(14) | A_BOLD);
    fclose(gameOverfp);
    //box(GameOver, 0, 0);
    wrefresh(GameOver);
    
    WINDOW *restWin = newwin(5, 40, 14, 18);
    //box(restWin, 0, 0);
    wrefresh(restWin);
    char restartMenu[3][11] = {
        {"PLAY AGAIN"},
        {"MENU"},
        {"QUIT GAME"}
    };
    init_pair(10,  COLOR_BLACK,   COLOR_RED); //CYAN was

    int pressedButton3;
    int pick2 = 0;
    int shineLine2 = 0;
    
    log_menu.RestartPlayPick = false;
    log_menu.FastQuit = false;
    wmove(restWin, 0, 0);
    keypad(restWin, true);
    while (1) {
        for (int i = 0; i < 3; i++) {
            if (i == shineLine2){
                //color_set(i, NULL);
                wattron(restWin, COLOR_PAIR(10) | A_BOLD | A_STANDOUT);
            }
            mvwprintw(restWin, i+1, 16, restartMenu[i]);
            pick2 = shineLine2+1;
            wrefresh(restWin);
            wattroff(restWin, COLOR_PAIR(10) | A_BOLD | A_STANDOUT);
        }
        pressedButton3 = wgetch(restWin);
        switch (pressedButton3) {
            case KEY_DOWN:
                shineLine2++;
                if (shineLine2 == 3)
                    shineLine2 = 2;
                break;
            case KEY_UP:
                shineLine2--;
                if (shineLine2 == -1)
                    shineLine2 = 0;
                break;
            default:
                break;
        }
        if (pressedButton3 == 10 && pick2 == 1) {
            log_menu.RestartPlayPick = true;
            dashpanel.lives = 3;
            break;
        }
        else if (pressedButton3 == 10 && pick2 == 2){
            break;
        }
        else if (pressedButton3 == 10 && pick2 == 3){
            log_menu.FastQuit = true;
            break;
        }
    }
    keypad(restWin, false);
   
}



int main(int argc, char * argv[], char * argv2[]){
    stpcpy(args.argument1, argv[1]);
    stpcpy(args.argument2, argv[2]);
  
    if(argc != 3){
        printf("Wrong numbers of paremeters\n");
    exit(EXIT_FAILURE);
    }
    initscr();
    curs_set(0);
    cbreak();
    noecho();
    pthread_t thread;
    int interval = 1000000;

    pthread_create(&thread, NULL, timer, &interval);
    
    int winY = 0, winX = 0;
    bool StartPlayPick = false;
    bool Level_1 = false;
    bool Level_2 = false;
    bool Level_3 = false;
    
    timex.repetitions = 0;
    
    
    FILE *fp = fopen("banner.txt", "r");
    
    // max xy
    getmaxyx(stdscr, winY, winX);

   
    refresh();

    // INIT BANNER CyberPunk
    
    WINDOW *banner = newwin(9, 85, winY-22, 2);
    char arr[9][85];
    for (int i = 0; i < 9; i++) {
        fgets(arr[i], 85, fp);
    }
    fclose(fp);
    use_default_colors ();
    start_color();
    init_pair(13, COLOR_RED, -1 );
    wattron(banner, COLOR_PAIR(13)  | A_BOLD );
    for (int i = 0; i < 9; i++) {
        wprintw(banner, arr[i]);
    }
    wattroff(banner, COLOR_PAIR(13)  | A_BOLD );
    wrefresh(banner);
    menuWin = newwin(6, winX-12, winY-10, 5);
    use_default_colors();
    wrefresh(menuWin);
    
    refresh();
    char menuList[3][14] = {
        {"START PLAY"},
        {"DEATH FACTORY"},
        {"QUIT GAME"}
    };
    
    int pressedButton;

    wrefresh(menuWin);

    short shineLine = 0;
    int pick = 0;
    
    start_color();
    init_pair(1,  COLOR_BLACK,   COLOR_RED); //CYAN was
    int q=0;
    keypad(menuWin, true);
    while (1) {
        if (log_menu.FastQuit) break;
        if (log_menu.RestartPlayPick == false) {
            for (int i = 0; i < 3; i++) {
                if (i == shineLine){
                    wattron(menuWin, COLOR_PAIR(1) | A_BOLD | A_STANDOUT);
                }
                if(i == 1) q = 2;
                
                else q = 0;
                mvwprintw(menuWin, i+1, 30-q, menuList[i]);
                pick = shineLine+1;
                
                wattroff(menuWin, COLOR_PAIR(1) | A_BOLD | A_STANDOUT);
            }
            
            pressedButton = wgetch(menuWin);
            //keypad(menuWin,TRUE);
            
            switch (pressedButton) {
                case KEY_DOWN:
                    shineLine++;
                    if (shineLine == 3)
                        shineLine = 2;
                    break;
                case KEY_UP:
                    shineLine--;
                    if (shineLine == -1)
                        shineLine = 0;
                    break;
                default:
                    break;
            }
            if (pressedButton == 10 && pick == 1) {
                StartPlayPick = true;
                //delwin(menuWin);
            }
            else if (pressedButton == 10 && pick == 2){
                about_the_game();
                continue;
            }
            else if (pressedButton == 10 && pick == 3){
                break;
            }
            else if (pressedButton == 27) break;
        }
        //keypad(menuWin, false);
        
        // put start play
        if (StartPlayPick || log_menu.RestartPlayPick == true) {
            wclear(menuWin);
            //wmove(menuWin, 2, 2);
            wrefresh(menuWin);
            
            char startList[4][11] = {
                {"LEVEL 1"},
                {"LEVEL 2"},
                {"LEVEL 3"},
                {"COME BACK"}
            };
            int pressedButton2 = 0;
            int shineStr = 0;
            int pickStart = 0;
            keypad(menuWin, true);
            while(log_menu.RestartPlayPick == false){
                for (int i = 0; i < 4; i++) {
                    if (i == shineStr){
                        //color_set(i, NULL);
                        wattron(menuWin, COLOR_PAIR(1) | A_BOLD | A_STANDOUT);
                    }
                    mvwprintw(menuWin, i+1, 29, startList[i]);
    
                    pickStart = shineStr+1;
                
                    wattroff(menuWin, COLOR_PAIR(1) | A_BOLD | A_STANDOUT);
                }
                pressedButton2 = wgetch(menuWin);
                //keypad(menuWin,TRUE);
                
                switch (pressedButton2) {
                    case KEY_DOWN:
                        shineStr++;
                        if (shineStr == 4)
                            shineStr = 3;
                        break;
                    case KEY_UP:
                        shineStr--;
                        if (shineStr == -1)
                            shineStr = 0;
                        break;
                    default:
                        break;
                }
                if (pressedButton2 == 10 && pickStart == 6) break;
                else if (pressedButton2 == 10 && pickStart == 1){
                    Level_1 = true;
                    break;
                }
                else if (pressedButton2 == 10 && pickStart == 2){
                    Level_2 = true;
                    break;
                }
                else if (pressedButton2 == 10 && pickStart == 3){
                    Level_3 = true;
                    break;
                }
                else if (pressedButton2 == 10 && pickStart == 4){
                    break;
                }
            }
            if (Level_2) Level_1 = false;
            if(Level_3) Level_2 = false;
            log_menu.RestartPlayPick = false;
            
            StartPlayPick = false;
            wclear(menuWin);
            wrefresh(menuWin);
            
            int kost1 = 0;
            int kost2 = 0;
            
            if (Level_1) {
                wclear(banner);
                wrefresh(banner);
                
                lvl_1 = newwin(20, 80, 4, 0);
                dashboard = newwin(4, 80, 0, 0);
                dashpanel.nlvl = 1;
                
                
                wrefresh(menuWin);
                wrefresh(lvl_1);
                
                int lettter2;
                
                memset(&level1.map, ' ', sizeof(level1));
                for (int i = 0; i < 24; i++)
                    level1.map[i][80] = '\0';
                
                FILE *fpM1 = fopen("map1.txt", "r");
                
                for (int i = 0; i < 24; i++) {
                    for (int j = 0; j < 80; j++) {
                        lettter2 = fgetc(fpM1);
                        
                        if (lettter2 == '-')
                            level1.map[i][j] = ' ';
                        else{
                            level1.map[i][j] = lettter2;
                        }
                    }
                }
                level1.map[23][80] = '\0';
                //memcpy(map1, level1.map, sizeof(map1));
                fclose(fpM1);
                
                player.x = 2;
                player.y = 2;
                player.kx = player.x;
                player.ky = player.y;
                bool presX = false;
                
                int rx = 0, ry = 0;
                dashpanel.lives = 3;
                int pressedKey;
                dashpanel.coins = 0;
                timex.minutes = 2;
                timex.seconds = 59;
                timex.sec = 59;
                
                keypad(lvl_1, true);
                start_color();
                init_pair(2, COLOR_RED , COLOR_BLACK);
                init_pair(3, COLOR_WHITE , COLOR_WHITE);
                init_pair(4, COLOR_BLUE , COLOR_YELLOW);
                init_pair(5, COLOR_BLACK, COLOR_WHITE);
                init_pair(6, COLOR_BLACK, COLOR_YELLOW);
                init_pair(7, COLOR_WHITE , COLOR_RED);
                init_pair(8, COLOR_BLACK , COLOR_CYAN);
                init_pair(9, COLOR_WHITE, COLOR_GREEN);
                init_pair(10, COLOR_RED, COLOR_RED);
                init_pair(11, COLOR_RED, COLOR_BLACK);
                init_pair(16, COLOR_RED, -1);

                
                while(1){

                    dashpanel.coins += pick_coin(1);

                    //Clear Map
                    memcpy(level1.map1, level1.map, sizeof(level1.map1));
                    
                    if (is_pressed_button(1) == 1)presX = true;
                    CheckAndPut(rx, ry, 1);
                    PutEnemies_lvl_1();
                    
                    if (Kill_p_Collision(1)) {
                        dashpanel.lives--;
                        player.x = player.kx;
                        player.y = player.ky;
                    }
                    if (dashpanel.lives == 0){
                        GAME_OVER_MENU();
                        break;;
                    }
                    wattron(dashboard, A_BOLD);
                    mvwprintw(dashboard,1 ,2, "LEVEL: ");
                    
                    mvwaddch(dashboard, 1, 9, '1' | A_BOLD | A_STANDOUT);
                    
                    mvwaddstr(dashboard, 1, 59, "Number of Coins:");
                    wattroff(dashboard, A_BOLD | A_STANDOUT);
                    wattron(dashboard, COLOR_PAIR(8) | A_BOLD);
                    mvwprintw(dashboard, 1, 76, "%d", dashpanel.coins);
                    wattroff(dashboard, COLOR_PAIR(8) | A_BOLD | A_STANDOUT);

                    mvwaddstr(dashboard, 2, 40, "to complete the level you need 12 coins");
                    mvwaddstr(dashboard, 2, 2, "ESC - quit |");
                    mvwaddstr(dashboard, 2, 14, " R - restart");
                    
                    wattron(dashboard, A_BOLD);
                    mvwaddstr(dashboard, 1, 16, "LIVES: ");
                    wattroff(dashboard, A_BOLD);
                    
                    
                    wattron(dashboard, COLOR_PAIR(16) | A_BOLD);
                    if (timex.seconds < 10) mvwprintw(dashboard, 1, 37, "0%d:0%d", timex.minutes, timex.seconds);
                    else mvwprintw(dashboard, 1, 37, "0%d:%d", timex.minutes, timex.seconds);
                    wattroff(dashboard, COLOR_PAIR(16) | A_BOLD);
                    

                    wattron(dashboard, COLOR_PAIR(11) | A_BOLD | A_STANDOUT);
                    mvwprintw(dashboard, 1, 23, "%d", dashpanel.lives);
                    wattroff(dashboard, COLOR_PAIR(11) | A_BOLD | A_STANDOUT);

                    wrefresh(dashboard);
                    
                    timex.repetitions++;
                    
                    // Show Map
                    wmove(lvl_1, 0, 0);
                    for (int i = 0; i < 24; i++) {
                        for (int j = 0; j < 80; j++) {
                            if (level1.map1[i][j] == '#' )
                                waddch(lvl_1, level1.map1[i][j] | COLOR_PAIR(3) );
                            else if(level1.map1[i][j] == '~')
                                waddch(lvl_1, level1.map1[i][j] | COLOR_PAIR(3));
                            else if (level1.map1[i][j] == '@')
                                waddch(lvl_1, level1.map1[i][j] | COLOR_PAIR(4));
                            else if (level1.map1[i][j] == '_')
                                waddch(lvl_1, level1.map1[i][j] | COLOR_PAIR(5));
                            else if (level1.map1[i][j] == '$')
                                waddch(lvl_1, level1.map1[i][j] | COLOR_PAIR(6));
                            else if (level1.map1[i][j] == '%')
                                waddch(lvl_1, level1.map1[i][j] | COLOR_PAIR(10));
                            else if (level1.map1[i][j] == '<' || level1.map1[i][j] == '>' || level1.map1[i][j] == '-')
                                waddch(lvl_1, level1.map1[i][j] | COLOR_PAIR(8));
                            else if (level1.map1[i][j] == '*' )
                                waddch(lvl_1, level1.map1[i][j] | COLOR_PAIR(7));
                            
                            else if (level1.map1[i][j] == 'W' || level1.map1[i][j] == 'I' || level1.map1[i][j] == 'N')
                                waddch(lvl_1, level1.map1[i][j] | COLOR_PAIR(9));
                            
                            else if (level1.map1[i][j] == 'X' && presX == false)
                                waddch(lvl_1, level1.map1[i][j] | COLOR_PAIR(7));
                            else if ( (is_pressed_button(1) == 1 && level1.map1[i][j] == 'X') || (presX == true && level1.map1[i][j] == 'X') ){
                                waddch(lvl_1, level1.map1[i][j] | COLOR_PAIR(9));
                                presX = true;
                            }
                            
                            else{
                                waddch(lvl_1, level1.map1[i][j]);
                            }
                        }
                        
                        
                    }
                    box(lvl_1, 0, 0);
                    box(dashboard, 0, 0);
                    wrefresh(dashboard);
                    wrefresh(lvl_1);
                    
                    if (presX == true){
                        level1.map[16][36] = ' ';
                        level1.map[16][37] = ' ';
                        level1.map[17][36] = ' ';
                        level1.map[17][37] = ' ';
                    }
                    if(dashpanel.coins >= 12){
                        level1.map[13][66] = ' ';
                        level1.map[13][67] = ' ';
                        level1.map[14][66] = ' ';
                        level1.map[14][67] = ' ';
                    }
                    if (timex.sec < 0) {
                        GAME_OVER_MENU();
                        break;
                    }
                    rx = player.x;
                    ry = player.y;
                    nodelay(lvl_1, true);
                    wtimeout(lvl_1, 100);
                    pressedKey = wgetch(lvl_1);
                   
                    if ( (pressedKey ) != EOF ){
                        switch (pressedKey) {
                            case KEY_UP:
                                player.y--;
                                break;
                            case KEY_DOWN:
                                player.y++;
                                break;
                            case KEY_LEFT:
                                player.x--;
                                break;
                            case KEY_RIGHT:
                                player.x++;
                                break;
                            default:
                                break;
                        }
                        if (pressedKey == 27) {
                            log_menu.RestartPlayPick = false;
                            break;
                        }
                        if (pressedKey == 'r' || pressedKey == 'R'){
                            log_menu.RestartPlayPick = true;
                            
                            break;
                        }
                        if ( winCol(1) ) {
                            Level_2 = true;
                            Level_1 = false;
                            break;
                        }
                    }
                }
                timex.sec = 59;
                timex.seconds = 59;
                kost1 = 1;
                Level_1 = false;
                wclear(lvl_1);
                wclear(dashboard);
                wrefresh(dashboard);
                wrefresh(lvl_1);
                if (log_menu.RestartPlayPick) {
                    Level_1 = true;
                    continue;
                }
            }
            if (Level_2) {
                Level_1 = false;
                wclear(banner);
                wrefresh(banner);
                
                lvl_2 = newwin(20, 80, 4, 0);
                dashboard = newwin(4, 80, 0, 0);
                dashpanel.nlvl = 1;
                
                //WINDOW *resWin = newwin(3, 5, 21, 75);
                
                wrefresh(menuWin);
                wrefresh(lvl_2);
                
                int lettter2;
                
                memset(&level2.map_2, ' ', sizeof(level2));
                for (int i = 0; i < 24; i++)
                    level2.map_2[i][80] = '\0';
                
                FILE *fpM2 = fopen("map2.txt", "r");
                
                for (int i = 0; i < 24; i++) {
                    for (int j = 0; j < 80; j++) {
                        lettter2 = fgetc(fpM2);
                        
                        if (lettter2 == '-') level2.map_2[i][j] = ' ';
                        else level2.map_2[i][j] = lettter2;
                    }
                }
                level2.map_2[23][80] = '\0';
                //memcpy(map1, level1.map, sizeof(map1));
                fclose(fpM2);
                
                player.x = 2;
                player.y = 16;
                player.kx = player.x;
                player.ky = player.y;
                level2.presX2 = false;
                
                int rx = 0, ry = 0;
                dashpanel.lives = 3;
                int pressedKey2;
                dashpanel.coins = 0;
                timex.minutes = 2;
                timex.seconds = 59;
                timex.sec = 59;
                
                
                keypad(lvl_2, true);
                start_color();
                init_pair(2, COLOR_RED , COLOR_BLACK);
                init_pair(3, COLOR_WHITE , COLOR_WHITE);
                init_pair(4, COLOR_BLUE , COLOR_YELLOW);
                init_pair(5, COLOR_BLACK, COLOR_WHITE);
                init_pair(6, COLOR_BLACK, COLOR_YELLOW);
                init_pair(7, COLOR_WHITE , COLOR_RED);
                init_pair(8, COLOR_BLACK , COLOR_CYAN);
                init_pair(9, COLOR_WHITE, COLOR_GREEN);
                init_pair(10, COLOR_RED, COLOR_RED);
                init_pair(11, COLOR_BLACK, COLOR_RED);
                init_pair(16, COLOR_RED, -1);

                
                //init_color(51, 600, 200, 300);

                while(1){
                    dashpanel.coins += pick_coin(2);

                    //Clear Map
                    memcpy(level2.map2, level2.map_2, sizeof(level2.map2));
                    
                    if (is_pressed_button(2) == 2) level2.presX2 = true;
                    CheckAndPut(rx, ry, 2);
                    PutEnemies_lvl_2();
                    
                    if (Kill_p_Collision(2)) {
                        dashpanel.lives--;
                        player.x = player.kx;
                        player.y = player.ky;
                    }
                    if (dashpanel.lives == 0){
                        GAME_OVER_MENU();
                        break;;
                    }
                    wattron(dashboard, A_BOLD);
                    mvwprintw(dashboard,1 ,2, "LEVEL: ");
                    mvwaddch(dashboard, 1, 9, '2' | A_BOLD | A_STANDOUT);
                    mvwaddstr(dashboard, 1, 59, "Number of Coins:");
                    wattroff(dashboard, A_BOLD | A_STANDOUT);
                    wattron(dashboard, COLOR_PAIR(8) | A_BOLD);
                    mvwprintw(dashboard, 1, 76, "%d", dashpanel.coins);
                    wattroff(dashboard, COLOR_PAIR(8) | A_BOLD | A_STANDOUT);
                    mvwaddstr(dashboard, 2, 40, "to complete the level you need 20 coins");
                    mvwaddstr(dashboard, 2, 2, "ESC - quit |");
                    mvwaddstr(dashboard, 2, 14, " R - restart");
                    wattron(dashboard, A_BOLD);
                    mvwaddstr(dashboard, 1, 16, "LIVES: ");
                    wattroff(dashboard, A_BOLD);
                    wattron(dashboard, COLOR_PAIR(11) | A_BOLD);
                    mvwprintw(dashboard, 1, 23, "%d", dashpanel.lives);
                    wattroff(dashboard, COLOR_PAIR(11) | A_BOLD | A_STANDOUT);
                    
                    wattron(dashboard, COLOR_PAIR(16) | A_BOLD);
                    if (timex.seconds < 10) mvwprintw(dashboard, 1, 37, "0%d:0%d", timex.minutes, timex.seconds);
                    else mvwprintw(dashboard, 1, 37, "0%d:%d", timex.minutes, timex.seconds);
                    wattroff(dashboard, COLOR_PAIR(16) | A_BOLD);
                    
                    wrefresh(dashboard);
                    
                    timex.repetitions ++;
                    
                    // Show Map
                    wmove(lvl_2, 0, 0);
                    for (int i = 0; i < 24; i++) {
                        for (int j = 0; j < 80; j++) {
                            if (level2.map2[i][j] == '#' )
                                waddch(lvl_2, level2.map2[i][j] | COLOR_PAIR(3) );
                            else if(level2.map2[i][j] == '~')
                                waddch(lvl_2, level2.map2[i][j] | COLOR_PAIR(3));
                            else if (level2.map2[i][j] == '@')
                                waddch(lvl_2, level2.map2[i][j] | COLOR_PAIR(4));
                            else if (level2.map2[i][j] == '_')
                                waddch(lvl_2, level2.map2[i][j] | COLOR_PAIR(5));
                            else if (level2.map2[i][j] == '$')
                                waddch(lvl_2, level2.map2[i][j] | COLOR_PAIR(6));
                            else if (level2.map2[i][j] == '%')
                                waddch(lvl_2, level2.map2[i][j] | COLOR_PAIR(10));
                            else if (level2.map2[i][j] == '<' || level2.map2[i][j] == '>' || level2.map2[i][j] == '-')
                                waddch(lvl_2, level2.map2[i][j] | COLOR_PAIR(8));
                            else if (level2.map2[i][j] == '*' )
                                waddch(lvl_2, level2.map2[i][j] | COLOR_PAIR(7));
                            
                            else if (level2.map2[i][j] == 'W' || level2.map2[i][j] == 'I' || level2.map2[i][j] == 'N')
                                waddch(lvl_2, level2.map2[i][j] | COLOR_PAIR(9));
                            
                            else if (level2.map2[i][j] == 'X')
                                if(level2.presX2) waddch(lvl_2, level2.map2[i][j] | COLOR_PAIR(9));
                                else waddch(lvl_2, level2.map2[i][j] | COLOR_PAIR(7));
                            else if ( (is_pressed_button(2) == 2 && level2.map2[i][j] == 'X') || (level2.presX2 == true && level2.map2[i][j] == 'X') ){
                                waddch(lvl_2, level2.map2[i][j] | COLOR_PAIR(9));
                                level2.presX2 = true;
                            }

                            else{
                                waddch(lvl_2, level2.map2[i][j]);
                            }
                        }
                        
                        
                    }
                    box(lvl_2, 0, 0);
                    box(dashboard, 0, 0);
                    //wrefresh(dashboard);
                    wrefresh(lvl_2);
                    
                    if (level2.presX2 == true){
                        level2.map_2[3][43] = ' ';
                        level2.map_2[3][44] = ' ';
                        level2.map_2[4][43] = ' ';
                        level2.map_2[4][44] = ' ';
                    }
                    if(dashpanel.coins >= 20){
                        level2.map_2[15][19] = ' ';
                        level2.map_2[15][20] = ' ';
                        level2.map_2[16][19] = ' ';
                        level2.map_2[16][20] = ' ';
                        level2.map_2[17][19] = ' ';
                        level2.map_2[17][20] = ' ';
                    }
                    if (timex.sec < 0) {
                        GAME_OVER_MENU();
                        break;
                    }
                    
                    rx = player.x;
                    ry = player.y;
                    nodelay(lvl_2, true);
                    wtimeout(lvl_2, 50);
                    pressedKey2 = wgetch(lvl_2);
                    if ( (pressedKey2 ) != EOF ){
                        switch (pressedKey2) {
                            case KEY_UP:
                                player.y--;
                                break;
                            case KEY_DOWN:
                                player.y++;
                                break;
                            case KEY_LEFT:
                                player.x--;
                                break;
                            case KEY_RIGHT:
                                player.x++;
                                break;
                            default:
                                break;
                        }
                        if (pressedKey2 == 27) {
                            log_menu.RestartPlayPick = false;
                            break;
                        }
                        if (pressedKey2 == 'r' || pressedKey2 == 'R'){
                            log_menu.RestartPlayPick = true;
                            break;
                        }
                        if ( winCol(2) ) {
                            Level_3 = true;
                            Level_2 = false;
                            Level_1 = false;
                            break;
                        }
                    }
                }
                //keypad(lvl_1, false);
                // end lvl_1
                kost2 = 1;
                Level_2 = false;
                wclear(lvl_2);
                wclear(dashboard);
                wrefresh(dashboard);
                wrefresh(lvl_2);
                if (log_menu.RestartPlayPick) {
                    Level_1 = false;
                    Level_2 = true;
                    continue;
                }
                
            }
            
            
            if (Level_3) {
                Level_1 = false;
                Level_2 = false;
                wrefresh(lvl_2);
                wclear(banner);
                wrefresh(banner);
                
                
                lvl_3 = newwin(20, 80, 4, 0);
                dashboard = newwin(4, 80, 0, 0);
                dashpanel.nlvl = 3;
                dashpanel.coins = 0;
                dashpanel.lives = 3;
                                
                wrefresh(menuWin);
                wrefresh(lvl_3);
                
                int lettter3;
                
                memset(&level3.map_3, ' ', sizeof(level3));
                for (int i = 0; i < 24; i++)
                    level3.map_3[i][80] = '\0';
                
                FILE *fpM3 = fopen("map3.txt", "r");
                
                for (int i = 0; i < 24; i++) {
                    for (int j = 0; j < 80; j++) {
                        lettter3 = fgetc(fpM3);
                        if (lettter3 == '-') level3.map_3[i][j] = ' ';
                        else level3.map_3[i][j] = lettter3;
                    }
                }
                level3.map_3[23][80] = '\0';

                fclose(fpM3);
                
                player.x = 2;
                player.y = 2;
                player.kx = player.x;
                player.ky = player.y;
                level3.presX3 = false;
                
                int rx = 0, ry = 0;
                dashpanel.lives = 3;
                int pressedKey3;
                dashpanel.coins = 0;
                
                timex.minutes = 2;
                timex.seconds = 59;
                timex.sec = 59;
                
                start_color();
                init_pair(2, COLOR_RED , COLOR_BLACK);
                init_pair(3, COLOR_WHITE , COLOR_WHITE);
                init_pair(4, COLOR_BLUE , COLOR_YELLOW);
                init_pair(5, COLOR_BLACK, COLOR_WHITE);
                init_pair(6, COLOR_BLACK, COLOR_YELLOW);
                init_pair(7, COLOR_WHITE , COLOR_RED);
                init_pair(8, COLOR_BLACK , COLOR_CYAN);
                init_pair(9, COLOR_WHITE, COLOR_GREEN);
                init_pair(10, COLOR_RED, COLOR_RED);
                init_pair(11, COLOR_BLACK, COLOR_RED);
                init_pair(16, COLOR_RED, -1);

                keypad(lvl_3, true);

                while(1){
                    dashpanel.coins += pick_coin(3);
                    
                    //Clear Map
                    memcpy(level3.map3, level3.map_3, sizeof(level3.map3));
                    if (is_pressed_button(3) == 3) level3.presX3 = true;
                    if (is_pressed_button(3) == 4) level3.presX3_2 = true;
                    if (is_pressed_button(3) == 5) level3.presX3_3 = true;
                    if (is_pressed_button(3) == 6) level3.presX3_4 = true;
                    if (is_pressed_button(3) == 7) level3.presX3_5 = true;
                    if (is_pressed_button(3) == 8) level3.presX3_6 = true;

                    CheckAndPut(rx, ry, 3);
                    PutEnemies_lvl_3();
                    
                    if (Kill_p_Collision(3)) {
                        dashpanel.lives--;
                        player.x = player.kx;
                        player.y = player.ky;
                    }
                    if (dashpanel.lives == 0){
                        GAME_OVER_MENU();
                        break;;
                    }
                    wattron(dashboard, A_BOLD);
                    mvwprintw(dashboard,1 ,2, "LEVEL: ");
                    mvwaddch(dashboard, 1, 9, '3' | A_BOLD | A_STANDOUT);
                    mvwaddstr(dashboard, 1, 59, "Number of Coins:");
                    wattroff(dashboard, A_BOLD );
                    wattron(dashboard, COLOR_PAIR(8) | A_BOLD );
                    mvwprintw(dashboard, 1, 76, "%d", dashpanel.coins);
                    wattroff(dashboard, COLOR_PAIR(8) | A_BOLD );
                    mvwaddstr(dashboard, 2, 40, "to complete the level you need 24 coins");
                    mvwaddstr(dashboard, 2, 2, "ESC - quit |");
                    mvwaddstr(dashboard, 2, 14, " R - restart");
                    wattron(dashboard, A_BOLD);
                    mvwaddstr(dashboard, 1, 16, "LIVES: ");
                    wattroff(dashboard, A_BOLD);
                    wattron(dashboard, COLOR_PAIR(11) | A_BOLD);
                    mvwprintw(dashboard, 1, 23, "%d", dashpanel.lives);
                    wattroff(dashboard, COLOR_PAIR(11) | A_BOLD);
                    
                    //  timer
                    wattron(dashboard, COLOR_PAIR(16) | A_BOLD);
                    if (timex.seconds < 10) mvwprintw(dashboard, 1, 37, "0%d:0%d", timex.minutes, timex.seconds);
                    else mvwprintw(dashboard, 1, 37, "0%d:%d", timex.minutes, timex.seconds);
                    wattroff(dashboard, COLOR_PAIR(16) | A_BOLD);
                    
                    wrefresh(dashboard);
                    
                    
                    timex.repetitions ++;
                    
                    
                    // Show Map
                    wmove(lvl_3, 0, 0);
                    for (int i = 0; i < 24; i++) {
                        for (int j = 0; j < 80; j++) {
                            if (level3.map3[i][j] == '#' )
                                waddch(lvl_3, level3.map3[i][j] | COLOR_PAIR(3) );
                            else if(level3.map3[i][j] == '~')
                                waddch(lvl_3, level3.map3[i][j] | COLOR_PAIR(3));
                            else if (level3.map3[i][j] == '@')
                                waddch(lvl_3, level3.map3[i][j] | COLOR_PAIR(4));
                            else if (level3.map3[i][j] == '_')
                                waddch(lvl_3, level3.map3[i][j] | COLOR_PAIR(5));
                            else if (level3.map3[i][j] == '$')
                                waddch(lvl_3, level3.map3[i][j] | COLOR_PAIR(6));
                            else if (level3.map3[i][j] == '%')
                                waddch(lvl_3, level3.map3[i][j] | COLOR_PAIR(10));
                            else if (level3.map3[i][j] == '<' || level3.map3[i][j] == '>' || level3.map3[i][j] == '-')
                                waddch(lvl_3, level3.map3[i][j] | COLOR_PAIR(8));
                            else if (level3.map3[i][j] == '*' )
                                waddch(lvl_3, level3.map3[i][j] | COLOR_PAIR(7));
                            
                            else if (level3.map3[i][j] == 'W' || level3.map3[i][j] == 'I' || level3.map3[i][j] == 'N')
                                waddch(lvl_3, level3.map3[i][j] | COLOR_PAIR(9));
                            
                            else if (level3.map3[i][j] == 'X' && level3.presX3 == false && ((i == 6 || i == 7) && j == 23))
                                waddch(lvl_3, level3.map3[i][j] | COLOR_PAIR(7));
                            else if (level3.map3[i][j] == 'X' && level3.presX3_2 == false && ((i == 2 || i == 3) && j == 24))
                                waddch(lvl_3, level3.map3[i][j] | COLOR_PAIR(7));
                            else if (level3.map3[i][j] == 'X' && level3.presX3_3== false && ((i == 4 || i == 5) && j == 65))
                                waddch(lvl_3, level3.map3[i][j] | COLOR_PAIR(7));
                            else if (level3.map3[i][j] == 'X' && level3.presX3_4 == false && ((i == 4 || i == 5) && j == 71))
                                waddch(lvl_3, level3.map3[i][j] | COLOR_PAIR(7));
                            else if (level3.map3[i][j] == 'X' && level3.presX3_5 == false && ((i == 16 || i == 17) && j == 77))
                                waddch(lvl_3, level3.map3[i][j] | COLOR_PAIR(7));
                            else if (level3.map3[i][j] == 'X' && level3.presX3_6 == false && ((i == 16 || i == 17) && j == 2))
                                waddch(lvl_3, level3.map3[i][j] | COLOR_PAIR(7));
                            
                            
                            else if ( (level3.map3[i][j] == 'X' && is_pressed_button(3) == 3) || (level3.presX3 == true && level3.map3[i][j] == 'X')){
                                waddch(lvl_3, level3.map3[i][j] | COLOR_PAIR(9));
                                level3.presX3 = true;
                            }
                            else if ( (is_pressed_button(3) == 4 && level3.map3[i][j] == 'X') || (level3.presX3_2 == true && level3.map3[i][j] == 'X') ){
                                waddch(lvl_3, level3.map3[i][j] | COLOR_PAIR(9));
                                level3.presX3_2 = true;
                            }
                            else if ( (is_pressed_button(3) == 5 && level3.map3[i][j] == 'X') || (level3.presX3_3 == true && level3.map3[i][j] == 'X') ){
                                waddch(lvl_3, level3.map3[i][j] | COLOR_PAIR(9));
                                level3.presX3_3 = true;
                            }
                            else if ( (is_pressed_button(3) == 6 && level3.map3[i][j] == 'X') || (level3.presX3_4 == true && level3.map3[i][j] == 'X') ){
                                waddch(lvl_3, level3.map3[i][j] | COLOR_PAIR(9));
                                level3.presX3_4 = true;
                            }
                            else if ( (is_pressed_button(3) == 7 && level3.map3[i][j] == 'X') || (level3.presX3_5 == true && level3.map3[i][j] == 'X') ){
                                waddch(lvl_3, level3.map3[i][j] | COLOR_PAIR(9));
                                level3.presX3_5 = true;
                            }
                            else if ( (is_pressed_button(3) == 8 && level3.map3[i][j] == 'X') || (level3.presX3_6 == true && level3.map3[i][j] == 'X') ){
                                waddch(lvl_3, level3.map3[i][j] | COLOR_PAIR(9));
                                level3.presX3_6 = true;
                            }
                           

                            else{
                                waddch(lvl_3, level3.map3[i][j]);
                            }
                        }
                        
                        
                    }
                    box(lvl_3, 0, 0);
                    box(dashboard, 0, 0);
                    wrefresh(dashboard);
                    wrefresh(lvl_3);
                    
                    if (level3.presX3 == true){
                        level3.map_3[8][2] = ' ';
                        level3.map_3[8][3] = ' ';
                        level3.map_3[8][4] = ' ';
                    }if (level3.presX3_2 == true){
                        level3.map_3[2][15] = ' ';
                        level3.map_3[2][16] = ' ';
                        level3.map_3[3][15] = ' ';
                        level3.map_3[3][16] = ' ';
                    }if (level3.presX3_3 == true){
                        level3.map_3[7][64] = ' ';
                        level3.map_3[7][65] = ' ';
                        level3.map_3[8][64] = ' ';
                        level3.map_3[8][65] = ' ';
                    }if (level3.presX3_4 == true){
                        level3.map_3[9][74] = ' ';
                        level3.map_3[9][75] = ' ';
                        level3.map_3[9][76] = ' ';
                    }if (level3.presX3_5 == true){
                        level3.map_3[16][38] = ' ';
                        level3.map_3[16][39] = ' ';
                        level3.map_3[17][38] = ' ';
                        level3.map_3[17][39] = ' ';
                    }if (level3.presX3_6 == true){
                        level3.map_3[15][12] = ' ';
                        level3.map_3[15][13] = ' ';
                        level3.map_3[15][14] = ' ';
                        level3.map_3[15][15] = ' ';
                    }
                    
                    if(dashpanel.coins >= 24){
                        level3.map_3[12][7] = ' ';
                        level3.map_3[12][8] = ' ';
                        level3.map_3[13][7] = ' ';
                        level3.map_3[13][8] = ' ';
                        level3.map_3[14][7] = ' ';
                        level3.map_3[14][8] = ' ';
                    }
                    if (timex.sec < 0) {
                        GAME_OVER_MENU();
                        break;
                    }
                    
                    rx = player.x;
                    ry = player.y;
                    nodelay(lvl_3, true);
                    wtimeout(lvl_3, 50);
                    pressedKey3 = wgetch(lvl_3);
                    if ( (pressedKey3 ) != EOF ){
                        switch (pressedKey3) {
                            case KEY_UP:
                                player.y--;
                                break;
                            case KEY_DOWN:
                                player.y++;
                                break;
                            case KEY_LEFT:
                                player.x--;
                                break;
                            case KEY_RIGHT:
                                player.x++;
                                break;
                            default:
                                break;
                        }
                        if (pressedKey3 == 27) {
                            log_menu.RestartPlayPick = false;
                            break;
                        }
                        if (pressedKey3 == 'r' || pressedKey3 == 'R'){
                            log_menu.RestartPlayPick = true;
                            
                            break;
                        }
                        if ( winCol(3) ) {
                            Level_3 = false;
                            Level_2 = false;
                            Level_1 = false;
                            GAME_WON_MENU();
                            break;
                        }
                    }
                }
                //keypad(lvl_1, false);
                // end lvl_1
                kost2 = 1;
                Level_3 = false;
                wclear(lvl_3);
                wclear(dashboard);
                wrefresh(dashboard);
                wrefresh(lvl_3);
                if (log_menu.RestartPlayPick) {
                    Level_1 = false;
                    Level_2 = false;
                    Level_3 = true;
                    continue;
                }
                
            }
            
            
            
            cbreak();
            if (kost1 == 1 || kost2 == 1) {
                wattron(banner, COLOR_PAIR(13)  | A_BOLD );
                for (int i = 0; i < 9; i++) {
                    wprintw(banner, arr[i]);
                }
                wattroff(banner, COLOR_PAIR(13)  | A_BOLD );
                wrefresh(banner);
            }
            
            
            wrefresh(banner);
        }
    }
    endwin();
    return 0;
}
int is_pressed_button(int numLvl){
    //lvl 1
    if (player.x == 33 && player.y == 11 && numLvl == 1) return 1;
    //if (player.x == 29 && player.y == 12 && numLvl == 1) return 9;

    //lvl2
    if (player.x == 15 && player.y == 2 && numLvl == 2) return 2;

    //lvl3
    if (player.x == 21 && player.y == 6 && numLvl == 3) return 3;
    if (player.x == 24 && player.y == 2 && numLvl == 3) return 4;
    if (player.x == 65 && player.y == 4 && numLvl == 3) return 5;
    if (player.x == 69 && player.y == 4 && numLvl == 3) return 6;
    if (player.x == 75 && player.y == 16 && numLvl == 3) return 7;
    if (player.x == 2 && player.y == 16 && numLvl == 3) return 8;

    return -1;
}


int pick_coin(short numLvl){
    int k1 = 0, k2 = 0, k3 = 0, k4 = 0, k5 = 0, k6 = 0;
    if (numLvl == 1) {
        if (level1.map1[player.y][player.x] == '$' && k1 == 0) {
            k1 = 1;
            level1.map[player.y][player.x] = ' ';
        }if (level1.map1[player.y+1][player.x] == '$' && k4 == 0){
            level1.map[player.y+1][player.x] = ' ';
            k4 = 1;
        }if (level1.map1[player.y][player.x+2] == '$' && k3 == 0){
            level1.map[player.y][player.x+2] = ' ';
            k3 = 1;
        }if (level1.map1[player.y+1][player.x+2] == '$' && k6 == 0){
            level1.map[player.y+1][player.x+2] = ' ';
            k6 = 1;
        }if (level1.map1[player.y][player.x+1] == '$' && k2 ==0){
            k2 = 1;
            level1.map[player.y][player.x+1] = ' ';
        }if (level1.map1[player.y+1][player.x+1] == '$' && k5 == 0){
            k5 = 1;
            level1.map[player.y+1][player.x+1] = ' ';
        }
    }
    else if (numLvl == 2){
        if (level2.map2[player.y][player.x] == '$' && k1 == 0) {
            k1 = 1;
            level2.map_2[player.y][player.x] = ' ';
        }if (level2.map2[player.y+1][player.x] == '$' && k4 == 0){
            level2.map_2[player.y+1][player.x] = ' ';
            k4 = 1;
        }if (level2.map2[player.y][player.x+2] == '$' && k3 == 0){
            level2.map_2[player.y][player.x+2] = ' ';
            k3 = 1;
        }if (level2.map2[player.y+1][player.x+2] == '$' && k6 == 0){
            level2.map_2[player.y+1][player.x+2] = ' ';
            k6 = 1;
        }if (level2.map2[player.y][player.x+1] == '$' && k2 ==0){
            k2 = 1;
            level2.map_2[player.y][player.x+1] = ' ';
        }if (level2.map2[player.y+1][player.x+1] == '$' && k5 == 0){
            k5 = 1;
            level2.map_2[player.y+1][player.x+1] = ' ';
        }
    }else if (numLvl == 3){
        if (level3.map3[player.y][player.x] == '$' && k1 == 0) {
            k1 = 1;
            level3.map_3[player.y][player.x] = ' ';
        }if (level3.map3[player.y+1][player.x] == '$' && k4 == 0){
            level3.map_3[player.y+1][player.x] = ' ';
            k4 = 1;
        }if (level3.map3[player.y][player.x+2] == '$' && k3 == 0){
            level3.map_3[player.y][player.x+2] = ' ';
            k3 = 1;
        }if (level3.map3[player.y+1][player.x+2] == '$' && k6 == 0){
            level3.map_3[player.y+1][player.x+2] = ' ';
            k6 = 1;
        }if (level3.map3[player.y][player.x+1] == '$' && k2 ==0){
            k2 = 1;
            level3.map_3[player.y][player.x+1] = ' ';
        }if (level3.map3[player.y+1][player.x+1] == '$' && k5 == 0){
            k5 = 1;
            level3.map_3[player.y+1][player.x+1] = ' ';
        }
    }
    
    return k1+k2+k3+k4+k5+k6;
}



//ball 1
int ballMuve(void){
    static int k = 0;
    static int Ygrav = 5;
    if (Ygrav == 10 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 5) k=0;

    }
    else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
} // ball 2
int ballMuve2(void){
    static int k = 0;
    static int Ygrav = 1;
    if (Ygrav == 8 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 1) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
} // ball 3
int ballMuve3(void){
    static int k = 0;
    static int Ygrav = 1;
    if (Ygrav == 8 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 1) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
} // ball 4
int ballMuve4(void){
    static int k = 0;
    static int Ygrav = 5;
    if (Ygrav == 17 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 5) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
} // ball 5
int ballMuve5(void){
    static int k = 0;
    static int Ygrav = 5;
    if (Ygrav == 8 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 5) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
} // ball 6
int ballMuve6(void){
    static int k = 0;
    static int Ygrav = 5;
    if (Ygrav == 8 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 5) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
}
int ballMuve7(void){
    static int k = 0;
    static int Ygrav = 10;
    if (Ygrav == 13 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 10) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
} // ball 8
int ballMuve8(void){
    static int k = 0;
    static int Ygrav = 13;
    if (Ygrav == 10 || k==1) {
        Ygrav++;
        k=1;
        if (Ygrav == 13) k=0;
    }else {
        Ygrav--;
        k=0;
    }
    return Ygrav;
} // ball 9
int ballMuve9(void){
    static int k = 0;
    static int Ygrav = 2;
    if (Ygrav == 14 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 2) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
} // ball 10
int ballMuve10(void){
    static int k = 0;
    static int Ygrav = 2;
    if (Ygrav == 17 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 2) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
}// ball 11
int ballMuve11(void){
    static int k = 0;
    static int Ygrav = 2;
    if (Ygrav == 5 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 2) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
}
int ballMuve12(void){
    static int k = 0;
    static int Ygrav = 11;
    if (Ygrav == 14 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 11) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
}
int ballMuve13(void){
    static int k = 0;
    static int Ygrav = 15;
    if (Ygrav == 17 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 15) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
}

int ballMuve14(void){
    static int k = 0;
    static int Ygrav = 15;
    if (Ygrav == 17 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 15) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
}

int ballMuve15(void){
    static int k = 0;
    static int Ygrav = 15;
    if (Ygrav == 17 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 15) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
}
int ballMuve16(void){
    static int k = 0;
    static int Ygrav = 2;
    if (Ygrav == 10 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 2) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
}
int ballMuve17(void){
    static int k = 0;
    static int Ygrav = 10;
    if (Ygrav == 2 || k==1) {
        Ygrav++;
        k=1;
        if (Ygrav == 10) k=0;
    }else {
        Ygrav--;
        k=0;
    }
    return Ygrav;
}
int ballMuveW1(void){
    static int k = 0;
    static int Ygrav = 1;
    if (Ygrav == 14 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 1) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
}
int ballMuveW2(void){
    static int k = 0;
    static int Ygrav = 14;
    if (Ygrav == 1 || k==1) {
        Ygrav++;
        k=1;
        if (Ygrav == 14) k=0;
    }else {
        Ygrav--;
        k=0;
    }
    return Ygrav;
}
int ballMuveW3(void){
    static int k = 0;
    static int Xgrav = 1;
    if (Xgrav == 13 || k==1) {
        Xgrav--;
        k=1;
        if (Xgrav == 1) k=0;
    }else {
        Xgrav++;
        k=0;
    }
    return Xgrav;
}
int ballMuveW4(void){
    static int k = 0;
    static int Xgrav = 13;
    if (Xgrav == 1 || k==1) {
        Xgrav++;
        k=1;
        if (Xgrav == 13) k=0;
    }else {
        Xgrav--;
        k=0;
    }
    return Xgrav;
}
int ballMuveW5(void){
    static int k = 0;
    static int Ygrav = 1;
    if (Ygrav == 4 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 1) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
}
int ballMuveW6(void){
    static int k = 0;
    static int Ygrav = 1;
    if (Ygrav == 4 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 1) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
}
int ballMuveW7(void){
    static int k = 0;
    static int Ygrav = 1;
    if (Ygrav == 4 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 1) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
}
int ballMuveW8(void){
    static int k = 0;
    static int Ygrav = 1;
    if (Ygrav == 4 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 1) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
}
int ballMuveW9(void){
    static int k = 0;
    static int Ygrav = 6;
    if (Ygrav == 9 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 6) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
}
int ballMuveW10(void){
    static int k = 0;
    static int Ygrav = 6;
    if (Ygrav == 9 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 6) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
}
int ballMuveW11(void){
    static int k = 0;
    static int Ygrav = 6;
    if (Ygrav == 9 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 6) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
}
int ballMuveW12(void){
    static int k = 0;
    static int Ygrav = 2;
    if (Ygrav == 17 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 2) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
}
int ballMuveW13(void){
    static int k = 0;
    static int Ygrav = 2;
    if (Ygrav == 17 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 2) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
}
int ballMuveW14(void){
    static int k = 0;
    static int Ygrav = 17;
    if (Ygrav == 2 || k==1) {
        Ygrav++;
        k=1;
        if (Ygrav == 17) k=0;
    }else {
        Ygrav--;
        k=0;
    }
    return Ygrav;
}
int ballMuveW15(void){
    static int k = 0;
    static int Ygrav = 17;
    if (Ygrav == 2 || k==1) {
        Ygrav++;
        k=1;
        if (Ygrav == 17) k=0;
    }else {
        Ygrav--;
        k=0;
    }
    return Ygrav;
}
int ballMuveW16(void){
    static int k = 0;
    static int Ygrav = 56;
    if (Ygrav == 77 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 56) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
}
int ballMuveW17(void){
    static int k = 0;
    static int Ygrav = 77;
    if (Ygrav == 56 || k==1) {
        Ygrav++;
        k=1;
        if (Ygrav == 77) k=0;
    }else {
        Ygrav--;
        k=0;
    }
    return Ygrav;
}
int ballMuveW18(void){
    static int k = 0;
    static int Ygrav = 51;
    if (Ygrav == 77 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 51) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
}
int ballMuveW19(void){
    static int k = 0;
    static int Ygrav = 77;
    if (Ygrav == 51 || k==1) {
        Ygrav++;
        k=1;
        if (Ygrav == 77) k=0;
    }else {
        Ygrav--;
        k=0;
    }
    return Ygrav;
}
int ballMuveW20(void){
    static int k = 0;
    static int Ygrav = 14;
    if (Ygrav == 48 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 14) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
}
int ballMuveW21(void){
    static int k = 0;
    static int Ygrav = 15;
    if (Ygrav == 48 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 15) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
}
int ballMuveW22(void){
    static int k = 0;
    static int Ygrav = 14;
    if (Ygrav == 17 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 14) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
}
int ballMuveW23(void){
    static int k = 0;
    static int Ygrav = 14;
    if (Ygrav == 17 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 14) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
}
int ballMuveW24(void){
    static int k = 0;
    static int Ygrav = 14;
    if (Ygrav == 17 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 14) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
}
int ballMuveQ1(void){
    static int k = 0;
    static int Ygrav = 5;
    if (Ygrav == 7 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 5) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
}
int ballMuveQ2(void){
    static int k = 0;
    static int Ygrav = 1;
    if (Ygrav == 5 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 1) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
}
int ballMuveQ3(void){
    static int k = 0;
    static int Ygrav = 1;
    if (Ygrav == 5 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 1) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
}
int ballMuveQ4(void){
    static int k = 0;
    static int Ygrav = 1;
    if (Ygrav == 5 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 1) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
}
int ballMuveQ5(void){
    static int k = 0;
    static int Ygrav = 1;
    if (Ygrav == 5 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 1) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
}
int ballMuveQ6(void){
    static int k = 0;
    static int Ygrav = 58;
    if (Ygrav == 78 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 58) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
}
int ballMuveQ7(void){
    static int k = 0, Ygrav = 47;
    if (Ygrav == 77 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 47) k=0;
    }else {
        Ygrav++;
        k=0;
    }
    return Ygrav;
}int ballMuveQ8(void){
    static int k = 0, Ygrav = 48;
    if (Ygrav == 77 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 47) k=0;
    }else {
        Ygrav++;
        k=0;
    }return Ygrav;
}int ballMuveQ9(void){
    static int k = 0, Ygrav = 49;
    if (Ygrav == 77 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 47) k=0;
    }else {
        Ygrav++;
        k=0;
    }return Ygrav;
}int ballMuveQ10(void){
    static int k = 0, Ygrav = 50;
    if (Ygrav == 77 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 47) k=0;
    }else {
        Ygrav++;
        k=0;
    }return Ygrav;
}int ballMuveQ11(void){
    static int k = 0, Ygrav = 51;
    if (Ygrav == 77 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 47) k=0;
    }else {
        Ygrav++;
        k=0;
    }return Ygrav;
}int ballMuveQ12(void){
    static int k = 0, Ygrav = 52;
    if (Ygrav == 77 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 47) k=0;
    }else {
        Ygrav++;
        k=0;
    }return Ygrav;
}int ballMuveQ13(void){
    static int k = 0, Ygrav = 45;
    if (Ygrav == 33 || k==1) {
        Ygrav++;
        k=1;
        if (Ygrav == 45) k=0;
    }else {
        Ygrav--;
        k=0;
    }return Ygrav;
}int ballMuveQ14(void){
    static int k = 0, Ygrav = 14;
    if (Ygrav == 10 || k==1) {
        Ygrav++;
        k=1;
        if (Ygrav == 14) k=0;
    }else {
        Ygrav--;
        k=0;
    }return Ygrav;
}int ballMuveQ15(void){
    static int k = 0, Ygrav = 12;
    if (Ygrav == 17 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 12) k=0;
    }else {
        Ygrav++;
        k=0;
    }return Ygrav;
}int ballMuveQ16(void){
    static int k = 0, Ygrav = 12;
    if (Ygrav == 17 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 12) k=0;
    }else {
        Ygrav++;
        k=0;
    }return Ygrav;
}int ballMuveQ17(void){
    static int k = 0, Ygrav = 12;
    if (Ygrav == 17 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 12) k=0;
    }else {
        Ygrav++;
        k=0;
    }return Ygrav;
}int ballMuveQ18(void){
    static int k = 0, Ygrav = 12;
    if (Ygrav == 17 || k==1) {
        Ygrav--;
        k=1;
        if (Ygrav == 12) k=0;
    }else {
        Ygrav++;
        k=0;
    }return Ygrav;
}



void PutEnemies_lvl_1(void){
    static int yw;
    if (timex.repetitions%2 == 0) {
        yw = ballMuve();
        level1.map1[ yw ][5] = '*';
    }else level1.map1[ yw ][5] = '*';
    // bool 2
    static int yw2;
    if (timex.repetitions%2 == 0) {
        yw2 = ballMuve2();
        level1.map1[ yw2 ][29] = '*';
    } else level1.map1[ yw2 ][29] = '*';
    // ball 3
    static int yw3;
    if (timex.repetitions%2 == 0) {
        yw3 = ballMuve3();
        level1.map1[ yw3 ][33] = '*';
    } else level1.map1[ yw3 ][33] = '*';
    // ball 4
    static int yw4;
    if (timex.repetitions%2 == 0) {
        yw4 = ballMuve4();
        level1.map1[ yw4 ][9] = '*';
    } else level1.map1[ yw4 ][9] = '*';
    // ball 5
    static int yw5;
    if (timex.repetitions%3 == 0) {
        yw5 = ballMuve5();
        level1.map1[ yw5 ][13] = '*';
    } else level1.map1[ yw5 ][13] = '*';
    // ball 6
    static int yw6;
    if (timex.repetitions%3 == 0) {
        yw6 = ballMuve6();
        level1.map1[ yw6 ][17] = '*';
    } else level1.map1[ yw6 ][17] = '*';
    static int yw7;
    if (timex.repetitions%12 == 0) {
        yw7 = ballMuve7();
        level1.map1[ yw7 ][24] = '*';
    } else level1.map1[ yw7 ][24] = '*';
    static int yw8;
    if (timex.repetitions%12 == 0) {
        yw8 = ballMuve8();
        level1.map1[ yw8 ][25] = '*';
    } else level1.map1[ yw8 ][25] = '*';
    static int yw9;
    if (timex.repetitions%2 == 0) {
        yw9 = ballMuve9();
        level1.map1[ yw9 ][39] = '*';
    } else level1.map1[ yw9 ][39] = '*';
    static int yw10;
    if (timex.repetitions%2 == 0) {
        yw10 = ballMuve10();                            //10
        level1.map1[ yw10 ][53] = '*';
    } else level1.map1[ yw10 ][53] = '*';
    static int yw11;
    if (timex.repetitions%10 == 0) {
        yw11 = ballMuve11();                    //11
        level1.map1[ yw11 ][57] = '*';
    } else level1.map1[ yw11 ][57] = '*';
    static int yw12;
    if (timex.repetitions%6 == 0) {
        yw12 = ballMuve12();                    //11
        level1.map1[ yw12 ][64] = '*';
    } else level1.map1[ yw12 ][64] = '*';
    
    static int yw13;
    if (timex.repetitions%12 == 0) {
        yw13 = ballMuve13();                    //11
        level1.map1[ yw13 ][19] = '*';
    } else level1.map1[ yw13 ][19] = '*';
    
    static int yw14;
    if (timex.repetitions%11 == 0) {
        yw14 = ballMuve14();                    //11
        level1.map1[ yw14 ][23] = '*';
    } else level1.map1[ yw14 ][23] = '*';
    static int yw15;
    if (timex.repetitions%12 == 0) {
        yw15 = ballMuve15();                    //11
        level1.map1[ yw15 ][27] = '*';
    } else level1.map1[ yw15 ][27] = '*';
    static int yw16;
    if (timex.repetitions%4 == 0) {
        yw16 = ballMuve16();                    //16
        level1.map1[ yw16 ][71] = '*';
    } else level1.map1[ yw16 ][71] = '*';
    static int yw17;
    if (timex.repetitions%4 == 0) {
        yw17 = ballMuve17();                    //17
        level1.map1[ yw17 ][71] = '*';
    } else level1.map1[ yw17 ][71] = '*';
}

void PutEnemies_lvl_2(void){
    static int yW1;
    if (timex.repetitions%3 == 0) {
        yW1 = ballMuveW1();
        level2.map2[ yW1 ][9] = '*';
    } else level2.map2[ yW1 ][9] = '*';
    static int yW2;
    if (timex.repetitions%3 == 0) {
        yW2 = ballMuveW2();
        level2.map2[ yW2 ][9] = '*';
    } else level2.map2[ yW2 ][9] = '*';
    
    static int xW3;
    if (timex.repetitions%2 == 0) {
        xW3 = ballMuveW3();
        level2.map2[ 11 ][xW3] = '*';
    } else level2.map2[ 11 ][xW3] = '*';
    static int xW4;
    if (timex.repetitions%2 == 0) {
        xW4 = ballMuveW4();
        level2.map2[ 4 ][xW4] = '*';
    } else level2.map2[ 4 ][xW4] = '*';
    
    static int yW5;
    if (timex.repetitions%5 == 0) {
        yW5 = ballMuveW5();
        level2.map2[ yW5 ][23] = '*';
    } else level2.map2[ yW5 ][23] = '*';
    static int yW6;
    if (timex.repetitions%5 == 0) {
        yW6 = ballMuveW6();
        level2.map2[ yW6 ][28] = '*';
    } else level2.map2[ yW6 ][28] = '*';
    static int yW7;
    if (timex.repetitions%5 == 0) {
        yW7 = ballMuveW7();
        level2.map2[ yW7 ][33] = '*';
    } else level2.map2[ yW7 ][33] = '*';
    static int yW8;
    if (timex.repetitions%5 == 0) {
        yW8 = ballMuveW8();
        level2.map2[ yW8 ][38] = '*';
    } else level2.map2[ yW8 ][38] = '*';
    
    static int yW9;
    if (timex.repetitions%18 == 0) {
        yW9 = ballMuveW9();
        level2.map2[ yW9 ][28] = '*';
    } else level2.map2[ yW9 ][28] = '*';
    static int yW10;
    if (timex.repetitions%18 == 0) {
        yW10 = ballMuveW10();
        level2.map2[ yW10 ][35] = '*';
    } else level2.map2[ yW10 ][35] = '*';
    static int yW11;
    if (timex.repetitions%18 == 0) {
        yW11 = ballMuveW11();
        level2.map2[ yW11 ][42] = '*';
    } else level2.map2[ yW11 ][42] = '*';
    static int yW12;
    if (timex.repetitions%5 == 0) {
        yW12 = ballMuveW12();
        level2.map2[ yW12 ][64] = '*';
    } else level2.map2[ yW12 ][64] = '*';
    static int yW13;
    if (timex.repetitions%3 == 0) {
        yW13 = ballMuveW13();
        level2.map2[ yW13 ][69] = '*';
    } else level2.map2[ yW13 ][69] = '*';

    static int yW14;
    if (timex.repetitions%3 == 0) {
        yW14 = ballMuveW14();
        level2.map2[ yW14 ][65] = '*';
    } else level2.map2[ yW14 ][65] = '*';
    static int yW15;
    if (timex.repetitions%3 == 0) {
        yW15 = ballMuveW15();
        level2.map2[ yW15 ][70] = '*';
    } else level2.map2[ yW15 ][70] = '*';
    
    static int xW16;
    if (timex.repetitions%3 == 0) {
        xW16 = ballMuveW16();
        level2.map2[ 5 ][xW16] = '*';
    } else level2.map2[ 5 ][xW16] = '*';
    static int xW17;
    if (timex.repetitions%3 == 0) {
        xW17 = ballMuveW17();
        level2.map2[ 6 ][xW17] = '*';
    } else level2.map2[ 6 ][xW17] = '*';
    
    static int xW18;
    if (timex.repetitions%3 == 0) {
        xW18 = ballMuveW18();
        level2.map2[ 11 ][xW18] = '*';
    } else level2.map2[11 ][xW18] = '*';
    static int xW19;
    if (timex.repetitions%3 == 0) {
        xW19 = ballMuveW19();
        level2.map2[ 12 ][xW19] = '*';
    } else level2.map2[ 12 ][xW19] = '*';
    static int xW20;
    if (timex.repetitions%2 == 0) {
        xW20 = ballMuveW20();
        level2.map2[ 9 ][xW20] = '*';
    } else level2.map2[9 ][xW20] = '*';
    static int xW21;
    if (timex.repetitions%3 == 0) {
        xW21 = ballMuveW21();
        level2.map2[ 11 ][xW21] = '*';
    } else level2.map2[ 11 ][xW21] = '*';
    static int yW22, yW23, yW24;
    if (timex.repetitions%6 == 0) {
        yW22 = ballMuveW22();
        yW23 = ballMuveW23();
        yW24 = ballMuveW24();
        level2.map2[ yW22 ][25] = '*';
        level2.map2[ yW23 ][31] = '*';
        level2.map2[ yW24 ][37] = '*';
    } else {
        level2.map2[ yW22 ][25] = '*';
        level2.map2[ yW23 ][31] = '*';
        level2.map2[ yW24 ][37] = '*';
    }
}

void PutEnemies_lvl_3(void){
    static int yQ1;
    if (timex.repetitions%16 == 0) {
        yQ1 = ballMuveQ1();
        level3.map3[ yQ1 ][20] = '*';
    } else level3.map3[ yQ1 ][20] = '*';
    static int yQ2, yQ3;
    if (timex.repetitions%7 == 0) {
        yQ2 = ballMuveQ2();
        yQ3 = ballMuveQ3();
        level3.map3[ yQ2 ][29] = '*';
        level3.map3[ yQ3 ][33] = '*';
    } else{
        level3.map3[ yQ2 ][29] = '*';
        level3.map3[ yQ3 ][33] = '*';
    }static int yQ4, yQ5;
    if (timex.repetitions%7 == 0) {
        yQ4 = ballMuveQ4();
        yQ5 = ballMuveQ5();
        level3.map3[ yQ4 ][45] = '*';
        level3.map3[ yQ5 ][49] = '*';
    } else {
        level3.map3[ yQ4 ][45] = '*';
        level3.map3[ yQ5 ][49] = '*';
    }static int xQ6;
    if (timex.repetitions%2 == 0) {
        xQ6 = ballMuveQ6();
        level3.map3[ 3 ][xQ6] = '*';
    } else level3.map3[ 3 ][xQ6] = '*';
    
    static int xQ7;
    if (timex.repetitions%2 == 0) {
        xQ7 = ballMuveQ7();
        level3.map3[ 10 ][xQ7] = '*';
    } else level3.map3[ 10 ][xQ7] = '*';
    static int xQ8;
    if (timex.repetitions%2 == 0) {
        xQ8 = ballMuveQ8();
        level3.map3[ 11 ][xQ8] = '*';
    } else level3.map3[ 11 ][xQ8] = '*';
    static int xQ9;
    if (timex.repetitions%2 == 0) {
        xQ9 = ballMuveQ9();
        level3.map3[ 12 ][xQ9] = '*';
    } else level3.map3[ 12 ][xQ9] = '*';
    static int xQ10;
    if (timex.repetitions%2 == 0) {
        xQ10 = ballMuveQ10();
        level3.map3[ 13 ][xQ10] = '*';
    } else level3.map3[ 13 ][xQ10] = '*';
    static int xQ11;
    if (timex.repetitions%2 == 0) {
        xQ11 = ballMuveQ11();
        level3.map3[ 14 ][xQ11] = '*';
    } else level3.map3[ 14 ][xQ11] = '*';
    static int xQ12;
    if (timex.repetitions%2 == 0) {
        xQ12 = ballMuveQ12();
        level3.map3[ 15 ][xQ12] = '*';
    } else level3.map3[ 15 ][xQ12] = '*';
    static int yQ14, xQ13;
    if (timex.repetitions%4 == 0) {
        xQ13 = ballMuveQ13();
        yQ14 = ballMuveQ14();
        level3.map3[ 12 ][xQ13] = '*';
        level3.map3[ yQ14 ][40] = '*';
    } else{
        level3.map3[ 12 ][xQ13] = '*';
        level3.map3[ yQ14 ][40] = '*';
    }static int yQ15, yQ16, yQ17, yQ18;
    if (timex.repetitions%4 == 0) {
        yQ15 = ballMuveQ15();
        yQ16 = ballMuveQ16();
        yQ17 = ballMuveQ17();
        yQ18 = ballMuveQ18();
        level3.map3[ yQ15 ][25] = '*';
        level3.map3[ yQ16 ][26] = '*';
        level3.map3[ yQ17 ][27] = '*';
        level3.map3[ yQ18 ][28] = '*';
    } else{
        level3.map3[ yQ15 ][25] = '*';
        level3.map3[ yQ16 ][26] = '*';
        level3.map3[ yQ17 ][27] = '*';
        level3.map3[ yQ18 ][28] = '*';
    }
}


bool winCol(int lvl){
    if ( ( lvl == 1 )&&(level1.map1[player.y][player.x] == 'I' ||
        level1.map1[player.y][player.x+1] == 'I' ||
        level1.map1[player.y][player.x+2] == 'I' ||
        level1.map1[player.y+1][player.x] == 'I' ||
        level1.map1[player.y+1][player.x+1] == 'I' ||
        level1.map1[player.y+1][player.x+2] == 'I' ) ){
        return true;
    }else if ( ( lvl == 2 )&&(level2.map2[player.y][player.x] == 'I' ||
        level2.map2[player.y][player.x+1] == 'I' ||
        level2.map2[player.y][player.x+2] == 'I' ||
        level2.map2[player.y+1][player.x] == 'I' ||
        level2.map2[player.y+1][player.x+1] == 'I' ||
        level2.map2[player.y+1][player.x+2] == 'I' ) ){
        return true;
    }else if ( ( lvl == 3 )&&(level3.map3[player.y][player.x] == 'I' ||
        level3.map3[player.y][player.x+1] == 'I' ||
        level3.map3[player.y][player.x+2] == 'I' ||
        level3.map3[player.y+1][player.x] == 'I' ||
        level3.map3[player.y+1][player.x+1] == 'I' ||
        level3.map3[player.y+1][player.x+2] == 'I' ) ){
        return true;
    }
    else{
        return false;
    }
}

void CheckAndPut(int rx, int ry, short numLvl){
    if (player.x == 0 ) player.x++;
    if (player.y-1 == 0) player.y++;
    if (player.x+2 == 79) player.x--;
    if (player.y == 23) player.y--;
    
    
    if (numLvl==1) {
        if ( (level1.map1[player.y+1][player.x] == '#') || (level1.map1[player.y][player.x+ 1] == '#') || (level1.map1[player.y+1][player.x+2] == '#') || (level1.map1[player.y][player.x] == '#') || (level1.map1[player.y][player.x+2] == '#'))
            player.y = ry;
        if ( (level1.map1[player.y+1][player.x+2] == '#') || (level1.map1[player.y+1][player.x] == '#') || (level1.map1[player.y][player.x] == '#') || (level1.map1[player.y][player.x+2] == '#') ) player.x = rx;
        if ( (level1.map1[player.y+1][player.x] == '%') || (level1.map1[player.y][player.x+ 1] == '%') || (level1.map1[player.y+1][player.x+2] == '%') || (level1.map1[player.y][player.x] == '%') || (level1.map1[player.y][player.x+2] == '%'))
            player.y = ry;
        if ( (level1.map1[player.y+1][player.x+2] == '%') || (level1.map1[player.y+1][player.x] == '%') || (level1.map1[player.y][player.x] == '%') || (level1.map1[player.y][player.x+2] == '%') )
            player.x = rx;
        level1.map1[player.y][player.x] = '<';
        level1.map1[player.y][player.x+1] = '-';
        level1.map1[player.y][player.x+2] = '>';   // <@>
        level1.map1[player.y+1][player.x] = '<';   // <@>
        level1.map1[player.y+1][player.x+1] = '-'; //
        level1.map1[player.y+1][player.x+2] = '>';
    }else if (numLvl == 2) {
        if ( (level2.map2[player.y+1][player.x] == '#') || (level2.map2[player.y][player.x+ 1] == '#') || (level2.map2[player.y+1][player.x+2] == '#') || (level2.map2[player.y][player.x] == '#') || (level2.map2[player.y][player.x+2] == '#'))
            player.y = ry;
        if ( (level2.map2[player.y+1][player.x+2] == '#') || (level2.map2[player.y+1][player.x] == '#') || (level2.map2[player.y][player.x] == '#') || (level2.map2[player.y][player.x+2] == '#')) player.x = rx;
        if ( (level2.map2[player.y+1][player.x] == '%') || (level2.map2[player.y][player.x+ 1] == '%') || (level2.map2[player.y+1][player.x+2] == '%') || (level2.map2[player.y][player.x] == '%') || (level2.map2[player.y][player.x+2] == '%') || level2.map2[player.y+1][player.x+1] == '#')
            player.y = ry;
        if ( (level2.map2[player.y+1][player.x+2] == '%') || (level2.map2[player.y+1][player.x] == '%') || (level2.map2[player.y][player.x] == '%') || (level2.map2[player.y][player.x+2] == '%') )
            player.x = rx;
        
        level2.map2[player.y][player.x] = '<';
        level2.map2[player.y][player.x+1] = '-';
        level2.map2[player.y][player.x+2] = '>';   // <@>
        level2.map2[player.y+1][player.x] = '<';   // <@>
        level2.map2[player.y+1][player.x+1] = '-'; //
        level2.map2[player.y+1][player.x+2] = '>';
    }else if (numLvl == 3) {
        if ( (level3.map3[player.y+1][player.x] == '#') || (level3.map3[player.y][player.x+ 1] == '#') || (level3.map3[player.y+1][player.x+2] == '#') || (level3.map3[player.y][player.x] == '#') || (level3.map3[player.y][player.x+2] == '#'))
            player.y = ry;
        if ( (level3.map3[player.y+1][player.x+2] == '#') || (level3.map3[player.y+1][player.x] == '#') || (level3.map3[player.y][player.x] == '#') || (level3.map3[player.y][player.x+2] == '#')) player.x = rx;
        if ( (level3.map3[player.y+1][player.x] == '%') || (level3.map3[player.y][player.x+ 1] == '%') || (level3.map3[player.y+1][player.x+2] == '%') || (level3.map3[player.y][player.x] == '%') || (level3.map3[player.y][player.x+2] == '%') || level3.map3[player.y+1][player.x+1] == '#')
            player.y = ry;
        if ( (level3.map3[player.y+1][player.x+2] == '%') || (level3.map3[player.y+1][player.x] == '%') || (level3.map3[player.y][player.x] == '%') || (level3.map3[player.y][player.x+2] == '%') )
            player.x = rx;
        
        level3.map3[player.y][player.x] = '<';
        level3.map3[player.y][player.x+1] = '-';
        level3.map3[player.y][player.x+2] = '>';   // <@>
        level3.map3[player.y+1][player.x] = '<';   // <@>
        level3.map3[player.y+1][player.x+1] = '-'; //
        level3.map3[player.y+1][player.x+2] = '>';
    }
}
