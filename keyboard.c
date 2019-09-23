#include "keyboard.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <fcntl.h>
#include <pthread.h>

int keysDown[NUM_KEYS] = {0};

void init_kb(void){
  int kbdev = open("/dev/input/event0",O_RDONLY);
  T_ARGS args = {kbdev};
  pthread_t kbThread;
  if(pthread_create(&kbThread, NULL, proc_kb_event, (void *)&args)){
    fprintf(stderr,"Error creating thread.\n");
    exit(1);
  }
}

void *proc_kb_event(void *t_args){
  int fd = ((T_ARGS *)t_args)->fd;
  input_event *event = (input_event *)malloc(sizeof(input_event));
  while(1){
    if(read(fd, event, sizeof(input_event)) && event->type == EV_KEY){
      keysDown[event->code] = event->value;
    }
  }
}


