#include "keyboard.h"

#include <ncurses.h>
#include <linux/input.h>
#include <stdio.h>
#include <string.h>

char *keyStr[NUM_KEYS] = {"RES","ESC","1","2","3","4","5","6","7","8","9","0","-","=","BKSP",
  "TAB","Q","W","E","R","T","Y","U","I","O","P","{","}","RET",
  "L_CTRL","A","S","D","F","G","H","J","K","L",";","\'","`",
  "L_SHIFT","\\","Z","X","C","V","B","N","M",",",".","/","R_SHIFT","KP_*",
  "L_ALT","SPACE","CAPS","F1","F2","F3","F4","F5","F6","F7","F8","F9","F10",
  "NUMLCK","SCRLLCK","KP_7","KP_8","KP_9","KP_-","KP_4","KP_5","KP_6","KP_+","KP_1","KP_2","KP_3","KP_0","KP_.",
  [87] = "F11","F12",[96] = "KP_RET","R_CTRL","KP_/","SYSRQ","R_ALT","LINEFEED","HOME","UP","PG_UP","LEFT","RIGHT",
  "END","DOWN","PG_DOWN","INSERT","DEL"};

int main(int argc, char *argv[]){
  // keyboard demo
  initscr();
  init_kb(); // start keyboard thread
  char sbuff[2048];
  int print = 0;
  while(1){
    for(int i = 0; i < NUM_KEYS; i++){
      if(keysDown[i]){
        if(sbuff[0]) strcat(sbuff,", ");
        strcat(sbuff,keyStr[i]);
        print = 1;
      }
    }
    if(print){
      erase();
      printw("Keys held: %s\n", sbuff);
      refresh();
      print = 0;
      memset(sbuff,0,strlen(sbuff));
    }
  }
  return 0;
}
