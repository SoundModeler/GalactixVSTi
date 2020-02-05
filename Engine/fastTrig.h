//------------------------------------------------------/////
/* 

  Fast sinus and cos calc in loop with size of TABLESIZE
  This macroses writen by Alex K. on February 2002 

  USAGE: 
  INIT_FASTSIN(1.0,2);
  loop: 
     double s=FASTSIN(2);  //// we get sin(1.0*TWOPI/TABLESIZE*index);
*/
//------------------------------------------------------/////

#define INIT_FASTSIN(N,id) double wrek##id=N*TWOPI/TABLESIZE; double brek##id=2.0\
*cos(wrek##id);double ygo##id=0; double ygn##id=-sin(wrek##id); double ygd##id=\
-sin(2.0*wrek##id)

#define FASTSIN(id) ygo##id = brek##id*ygn##id - ygd##id; ygd##id\
= ygn##id ; ygn##id = ygo##id 

#define INIT_FASTCOS(N,id) double wreck##id= N*TWOPI/TABLESIZE; double breck##id = 2.0\
* cos(wreck##id); double ygco##id=0; double icp##id= M_PI*0.5; double ygcn##id=\
sin(icp##id-wreck##id); double ygcd##id=sin(icp##id-2.0*wreck##id)

#define FASTCOS(id) ygco##id = breck##id*ygcn##id - ygcd##id; ygcd##id =\
ygcn##id ; ygcn##id = ygco##id 


//------------------------------------------------------/////