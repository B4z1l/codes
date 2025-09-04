
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

 struct pos {
  int x;
  int y;
 };
typedef struct pos pos;

int rb(){
    return (rand() / ( (double) RAND_MAX)) < 0.5;
}

pos av (pos point) {
  pos new;
  new.x = 0;
  new.y = 0;
  if (rb()) {
    new.x = point.x + (rb() ? 1 : -1);
    new.y = point.y;
  } else {
    new.x = point.x;
    new.y = point.y + (rb() ? 1 : -1);
  }
  return new;
}

pos av1d(pos point) {
  pos new;
  new.x = point.x + (rb() ? 1 : -1);
  new.y = point.y;
  return new;
}

double d2(pos point){
    return point.x*point.x + point.y*point.y;
}


