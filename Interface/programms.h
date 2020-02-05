//-----------------------------------------------------------------------------------------
void PROGRAMMSET(int Exemplyar,int prognum);
//------------------------------------
#define DSF    0
#define SIN    1
#define SIN8   2
#define SAW    3
#define DSF_2  4
#define SQUAR  5
#define DrSin  6
#define Avowel 7
#define Uvowel 8
#define Noise  9
#define Alexu  10
//-----------------------------------------------------------------------------------------
#define Exponent 0
#define SlowAttack 1
#define Pluck 2
#define Pianolike 3
#define Flat 4
#define Chick 5
#define FlatLFO 6
#define AttDc 7
#define Linear 8
//-----------------------------------------------------------------------------------------
float ProgrammsContainer[45][64];///45=32+1+16+...///extern in Engine.hpp and AGain.cpp

float Programms[45][64]= {
///DEFAULT
{DSF,DSF,DSF,DSF,DSF,DSF,
                        64,62,67,66,61, -36,
					   100,100,100,100,100,60,
					   Exponent,Exponent,
					   2,4 ,
				       0.75f,0.1f, 0.1f,  0,///cut0, reso,rel,att
					   0.99f,1, 0.7f,0.3f,55,//cut,chor,sz,rev
					   0,0,0,0,0,0},///phase
///TRANCE LEAD
{DSF,DSF,DSF,DSF,DSF,DSF,
                        64,62,67,66,61, -36,
					   100,100,100,100,100,60,
					   Pluck,Chick,
					   2,4 ,
				       0.81f,0.1f, 0.47f,  0.15f,///cut0, reso,rel,att
					   0.99f,1, 0.75f,0.75f,45,//cut,chor,sz,rev
					   0,5,10,10,20,0},///phase
///Fill-the-bit
{SAW,SAW,SAW,SAW,SQUAR,DSF_2,
                        64, 66, 63, 65, -36, -35,
					   100,100,100,100,100,100,
					   Chick,Flat,
					   3,4,
				       0.6f,0.5f,0,  0,
					   1,1, 0.7f,0.3f,40,//cut,chor,sz,rev
					   0,10,20,30,70,90},///phase
////E Piano
{SIN8,SIN8,SIN8,SIN8,SIN8,SIN8,
                        64,64,66,65,63,64,
					   100,100,100,100,60,60,
					   Pianolike,Chick,
					   2,4,
				       0.8f,0.1f, 0.1f,  0,///cut0, reso,rel,att
					   0.4f,0, 0.7f,0.7f,60,//cut,chor,sz,rev
					   0,20,0,30,60,70},///phase
///Virtual Sitar
{DSF,DSF,DSF,DSF,DSF,SIN,
                        64,64,64,64,63,-36,
					   100,100,100,100,60,100,
					   Pluck,Pianolike,
					     2,4,
				       0.5f,0.1f, 0.f,  0.f,///cut0, reso,rel,att
					   0.4f,0.75f, 0.6f,0.55f,40,//cut,chor,sz,rev
					   0,0,0,0,64,40},///phase
////ANALOG Brass
{0,2,4,4,DSF_2,4,
                        64,62,67,66,61,69,
					   35,100,100,100,100,75,
					   SlowAttack,Flat,
					   2,4,
				       0.99f,0.f, 0.f,  0.2f,///cut0, reso,rel,att
					   0.99f,0.9f, 0.8f,0.6f,80,//cut,chor,sz,rev
					   0,0,0,0,29,0},///phase
////Oboe
{DSF_2,SIN8, DSF, DSF, DrSin, DSF_2 ,
                       64, -36, 65, 66, 64, 63,
					   57,16,28,17,62,15,
					   FlatLFO,Flat,
					   2,4,
				       0.8f,0.f, 0.f,  0.47f,///cut0, reso,rel,att
					   0.3f,0.1f, 0.7f,0.8f,25,//cut,chor,sz,rev
					   0,0,0,0,40,0},///phase
/////WIND FROM CHINA
{0, 2, 5, 1, 2, 0  ,
                       64, 69, 68, 66, 61, 69,
					   100,29,8,66,28,28, 
					   Pluck,FlatLFO,
					   2,4,
				       0.4f,0.f, 0.1f,  0.04f,///cut0, reso,rel,att
					   0.6f,0.9f, 0.4f,0.8f,40,//cut,chor,sz,rev
					   0,40,90,30,10,0},///phase
///STRINGS 2
{SIN,DrSin,DrSin,DrSin,DrSin,DrSin,
                       -36,62,63,66,65,64,
					   20,100,100,100,100,75,
					   Flat,SlowAttack,
					   3,4,
				       0.99f,0.f, 0.3f,  0.99f,///cut0, reso,rel,att
					   0.5f,0.99f, 0.8f,0.5f,30,//cut,chor,sz,rev
					   0,10,20,70,45,110},///phase
///Chor
{Avowel,Avowel,Avowel,Avowel,Avowel,Avowel,
                       -36,62,63,66,65,64,
					   35,100,100,100,100,75,
					   FlatLFO,SlowAttack,
					   2,4,
				       0.99f,0.f, 0.3f,  0.99f,///cut0, reso,rel,att
					   0.47f,0.99f, 0.8f,0.75f,70,//cut,chor,sz,rev
					   0,10,20,70,45,110},///phase
///Organ
{Uvowel,Uvowel,Uvowel,Uvowel,Uvowel,Uvowel,
                       -36,62,63,66,65,64,
					   100,100,100,100,100,75,
					   Exponent,Flat,
					   2,4,
				       0.99f,0.f, 0.2f,  0.05f,///cut0, reso,rel,att
					   0.99f,0.f, 0.8f,0.4f,60,//cut,chor,sz,rev
					   0,10,20,70,45,110},///phase
///Reso Bass
{SAW,DrSin,DSF,SQUAR,SIN,DSF_2,
                       64,61,-37,65,-36,-35, 
					   100,100,100,25,100,60,
					   Pluck,Pluck,
					   2,4,
				       0.2f,0.99f, 0.f,  0.f,///cut0, reso,rel,att
					   0.99f,0.f, 0.2f,0.7f,60,//cut,chor,sz,rev
					   0,10,20,70,45,50},///phase
///FatGuy
{SAW,SAW,Avowel,Avowel,SQUAR,DSF_2,
                        64, 66, 63, 65, -36, -35,
					   100,100,100,100,100,100,
					   Exponent,Flat,
					   3,4,
				       0.03f,0.5f,0,  0,
					   1,1, 0.7f,0.99f,22,//cut,chor,sz,rev
					   0,10,20,30,70,90},///phase
///Space Dust
{DSF,SQUAR,Avowel,DSF,DrSin,SQUAR,
                       -36,62,63,66,65,64,
					   20,100,100,100,100,83,
					   Flat,SlowAttack,
					   3,4,
				       0.99f,0.f,0.4f, 0.45,
					   0.6f,0.48f, 0.85f,0.5f,30,//cut,chor,sz,rev
					   0,10,20,70,45,110},///phase
///Elf's Deliverance
{SIN8,Avowel,Avowel,Noise,Noise,Noise,
                       -36,62,64,66,65,64,
					   100,22,100,100,52,43,
					   Pluck,AttDc,
					   2,4,
				       0.75f,0.7f, 0.9f,  0.25f,///cut0, reso,rel,att
					   0.99f,0.49f, 0.99f,0.45f,42,//cut,chor,sz,rev
					   0,10,20,70,45,110},///phase
					   
// Alise
{SAW,SAW,SAW,SAW,SAW,SAW,
                       64,62,63,66,61,68,
					   35,100,100,100,100,75,
					   Linear,Pluck,
					   2,4,
				       0.05f,0.1f, 0.5f,  0.5f,///cut0, reso,rel,att
					   0.99f,0.9f, 0.8f,0.6f,40,//cut,chor,sz,rev
					   0,0,0,0,29,0},///phase
///Melaren Pad
{Alexu,DrSin,Alexu,Noise,Alexu,DSF,
                       -36,62,63,66,65,64,
					   100,100,100,37,100,50,
					   FlatLFO,SlowAttack,
					   3,4,
				       0.99f,0.98f,0.4f, 0.f,///cut0, reso,rel,att
					   0.55f,0.35f, 0.95f,0.3f,70,//cut,chor,sz,rev
					   0,10,20,70,45,110},///phase	

///Chor 2
{Uvowel,Alexu,Alexu,Alexu,Avowel,Avowel,
                       -36,62,63,66,65,64,
					   35,100,100,100,100,75,
					   FlatLFO,SlowAttack,
					   2,4,
				       0.99f,0.f, 0.3f,  0.99f,///cut0, reso,rel,att
					   0.99f,0.99f, 0.8f,0.75f,55,//cut,chor,sz,rev
					   0,10,20,70,45,110},///phase
///New Age
{DSF,DrSin,Alexu,Noise,Alexu,SQUAR,
                       -36,62,63,66,65,64,
					   100,0,0,0,100,16,
					   Pluck,Exponent,
					   3,4,
				       0.65f,0.f,0.4f, 0.f,///cut0, reso,rel,att
					   0.99f,0.35f, 0.95f,0.3f,70,//cut,chor,sz,rev
					   0,10,20,70,45,110},///phase				   
////rgc 1
{0,3,3,0,0,0,
64,62,67,66,61,-36,
100,100,100,100,100,60,2,5,2,5,
0.01,0.04,0.00,0.14,
0.52,0.00,0.75,0.09,85.0 ,
10.0 ,10.0 ,20.0 ,20.0 ,30.0 ,10.0  },
////rgc 2
{3,3,3,4,9,3,64,66,63,65,-36,-35,100,100,100,100,100,100,0,1,7,4,
0.7 ,0.37,0.00,0.00,1.0 ,0.29,1.0 ,0.57,40.0 ,0.00,10.0 ,20.0 ,30.0 ,70.0 ,90.0  },
////rgc 3
 {2,2,2,2,2,2,64,64,66,65,63,64,100,100,100,100,60,
60,3,5,2,4,0.77,0.08,0.08,0.00,0.37,0.00,0.69,0.18,60.0 ,0.00,20.0 ,0.00,30.0 ,60.0 ,70.0  },
////rgc 4
{0,0,0,0,4,4,64,64,64,64,63,-36,
100,100,100,100,60,100,7,3,2,4,0.49,0.43,0.00,0.00,1.0 ,0.48,0.74,0.18,40.0 ,0.00,0.00,0.00,
0.00,64.0 ,40.0  },
////rgc 5
{0,2,4,4,4,4,64,
62,67,66,61,69,35,100,100,100,100,75,1,4,2,4,0.98,0.00,0.00,0.18,0.98,0.88,0.8 ,0.6 ,
80.0 ,0.00,0.00,0.00,0.00,29.0 ,0.00 },
////rgc 6
 {5,5,
0,5,6,4,64,-36,65,66,64,63,57,16,28,17,62,15,2,4,2,4,0.02,0.03,0.00,0.45,1.0 ,0.00,0.29,
0.25,25.0 ,0.00,0.00,0.00,
0.00,40.0 ,0.00 },
////rgc 7
{5,2,4,1,9,0,64,69,68,66,61,69,100,29,8,66,100,28,2,6,2,4,0.03,0.00,0.08,0.03,0.88,0.72,0.4 ,
0.00,86.0 ,0.00,40.0 ,90.0 ,30.0 ,10.0 ,0.00 },
////rgc 8
{1,6,6,3,5,5,-36,164,63,66,65,64,20,100,100,100,100,75,4,1,4,4,0.29,0.01,
1.0 ,0.98,1.0 ,0.98,0.8 ,0.5 ,30.0 ,0.00,10.0 ,20.0 ,70.0 ,45.0 ,110.0  },
////rgc 9
{8,7,1,6,6,2,-36,62,63,66,65,64,35,100,100,100,100,75,2,
2,2,4,1.0 ,0.00,0.29,0.98,1.0 ,0.98,0.18,0.33,100.0 ,0.00,10.0 ,20.0 ,70.0 ,45.0 ,110.0  },
////rgc 10 - organ
{1,8,8,8,8,7,-36,65,66,66,65,165,100,100,
100,100,100,75,0,4,2,4,1.0 ,0.00,0.19,0.04,0.74,1.0 ,0.00,0.00,60.0 ,0.00,10.0 ,
20.0 ,70.0 ,45.0 ,110.0  }

};
//-----------------------------------------------------------------------------------------















