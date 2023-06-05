//SETLOCO(3)   // select loco 3
//SPEED(0)
//RESERVE(1)
//SENDLOCO(3,13)
DONE


#define PULSE 100 //10 mSec
#define DUAL_SOLENOID_TURNOUT(id,pc,pt,desc) \
VIRTUAL_TURNOUT(id,desc) \
SET(pc) \
SET(pt) \
DONE \
ONCLOSE(id) \
RESET(pc) \
DELAY(PULSE) \
SET(pc) \
DONE \
ONTHROW(id) \
RESET(pt) \
DELAY(PULSE) \
SET(pt) \
DONE

// define the turnouts
DUAL_SOLENOID_TURNOUT(123, 23, 25, "Test turnout")  // Define the "Yard entrance" turnout with turnout ID 105 using pins 23/25
DUAL_SOLENOID_TURNOUT(127, 27, 29, "Test turnout")  // Define the "Yard entrance" turnout with turnout ID 105 using pins 27/29
DUAL_SOLENOID_TURNOUT(131, 31, 33, "Test turnout")  // Define the "Yard entrance" turnout with turnout ID 105 using pins 31/33
DUAL_SOLENOID_TURNOUT(122, 22, 24, "Test turnout")  // Define the "Yard entrance" turnout with turnout ID 105 using pins 24/26
DUAL_SOLENOID_TURNOUT(126, 26, 28, "Test turnout")  // Define the "Yard entrance" turnout with turnout ID 105 using pins 28/30
DUAL_SOLENOID_TURNOUT(130, 30, 32, "Test turnout")  // Define the "Yard entrance" turnout with turnout ID 105 using pins 32/34

AUTOMATION(1, "Test for V200")
  SENDLOCO(3,13)
  DONE

// define the sequences to move from one block to the next one
SEQUENCE(13) // From block 1 to block 3
   DELAYRANDOM(1000,5000) // random wait between 10 and 20 seconds
   RESERVE(3) // we wish to enter block 3… so wait for it
   PRINT("13 block 3 reserved")
   THROW(126) // Now we “own” the block, set the turnout
   PRINT("13 T126 thrown")
   IFNOT(-42)
     PRINT("13 next block is not free, wait!")
     AFTER(-42)
   ELSE
     PRINT("13 next block sensor reports free")
   ENDIF
   FWD(10) // and proceed forward
   AFTER(-39) // after we leave block 1
   PRINT("13 BLK1 free")
   FREE(1) // free the block we left
   PRINT("13 hand over to 34")
   FOLLOW(34) // follow route from block 2 to block 3

SEQUENCE(23) // From block 2 to block 3
   DELAYRANDOM(1000,5000) // random wait between 10 and 20 seconds
   RESERVE(3) // we wish to enter block 3… so wait for it
   CLOSE(126) // Now we “own” the block, set the turnout
   FWD(10) // and proceed forward
   AFTER(35) // after we leave block 2
   FREE(2) // free the block we left
   FOLLOW(34) // follow route from block 2 to block 3

SEQUENCE(34) // From block 3 to block 4
   RESERVE(4) // we wish to enter block 4… so wait for it
   PRINT("34 block 4 reserved")
   THROW(127) // Now we “own” the block, set the turnout
   PRINT("34 T127 thrown")
   FWD(10) // and proceed forward
   AFTER(-42) // after we leave block 3
   PRINT("34 BLK_3 free")
   FREE(3) // release the block we left
   PRINT("34 hand over to 45")
   FOLLOW(45) // follow route from block 4 to block 5

SEQUENCE(45)
  //AFTER(34) // after we leave block 4
  PRINT("45 now stop")
  STOP

/*
SEQUENCE(45) // From block 4 to block 5
   RESERVE(5) // we wish to enter block 5… so wait for it
   CLOSE(122) // Now we “own” the block, set the turnout
   FWD(10) // and proceed forward
   FREE(4) // release the block we left
   FOLLOW(57) // follow route from block 5 to block 7

SEQUENCE(46) // From block 4 to block 5
   RESERVE(6) // we wish to enter block 6… so wait for it
   THROW(122) // Now we “own” the block, set the turnout
   FWD(10) // and proceed forward
   FREE(4) // release the block we left
   FOLLOW(67) // follow route from block 6 to block 7

SEQUENCE(57) // From block 5 to block 7
   RESERVE(7) // we wish to enter block 7… so wait for it
   CLOSE(130) // Now we “own” the block, set the turnout
   FWD(10) // and proceed forward
   FREE(5) // release the block we left
   FOLLOW(74) // follow route from block 7 to block 8

SEQUENCE(67) // From block 6 to block 7
   RESERVE(7) // we wish to enter block 7… so wait for it
   THROW(130) // Now we “own” the block, set the turnout
   FWD(10) // and proceed forward
   FREE(6) // release the block we left
   FOLLOW(74) // follow route from block 7 to block 4

SEQUENCE(74) // From block 7 to block 4
   RESERVE(4) // we wish to enter block 5… so wait for it
   CLOSE(123) // Now we “own” the block, set the turnout
   CLOSE(127)
   FWD(10) // and proceed forward
   FREE(7) // release the block we left
   FOLLOW(45) // follow route from block 4 to block 5

*/
