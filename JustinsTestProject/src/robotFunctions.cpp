#include "vex.h"
 
void countUpTask() {
  printf("start\n");
  int count = 0;

  repeat(50) {
    printf("Up %d\n", count++);
    
    // don't hog the cpu :)
    task::sleep( 20 );
  }

  // return 0;
}

// void countUpTaskStop() 
// {
//   if (subroutine.function == countUpTask) {
//     subroutine.isRunning = false;
//   }
// }

void countDownTask() {
  printf("start\n");
  int count = 0;

  repeat(50) {
    printf("Down %d\n", count--);
    
    // don't hog the cpu :)
    task::sleep( 20 );
  }

  // return 0;
}


void singleUseButton() 
{
  printf("singleUseButton\n");
  // return 0;
}