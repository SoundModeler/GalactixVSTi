
#include <windows.h>  
#include <windowsx.h>
#include <commctrl.h>
#include <math.h>
#include <string.h>
#include <stdio.h> 

#include "..\Exe\CompileType.h"
//#include "..\Exe\temp.h"
void *strea;
#include "..\Engine\Engine.hpp"
#include "..\PortAudio\portaudio.h"
#include "..\Interface\EditorVST.hpp"

#define BUFSIZE 2048
float *emptyimput[2];
void* hInstance;
float *outPA[2];
/////////////////////////////////////USING PROCESS CALLBACK FUNCTION
//------------------------------------------------------------------------
static int patestCallback(  void *inputBuffer, void *outputBuffer,
                     unsigned long framesPerBuffer,
                     PaTimestamp outTime, void *userData )
					 {
    float *out = (float*)outputBuffer;

  ((Engine*) GEFFECT[0] )->process((float**)emptyimput,(float**) outPA, framesPerBuffer);

for (int i=0;i<framesPerBuffer;i+=2) 
{
*out++=  outPA[0][i];
*out++=  outPA[1][i];
*out++=  outPA[0][i+1];
*out++=  outPA[1][i+1];
emptyimput[0][i]=0.f;
emptyimput[1][i]=0.f;
outPA[0][i]=0.f;
outPA[1][i]=0.f;
emptyimput[0][i+1]=0.f;
emptyimput[1][i+1]=0.f;
outPA[0][i+1]=0.f;
outPA[1][i+1]=0.f;
}
	return 0;
					 };
//------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)

{
    hInstance=hinst;
    PortAudioStream *stream;

 if (0==curv) curv =new Craftvs;
 if (0==dg)   dg   =new Digits;
 if (0==kn)   kn   =new Knob ;
 if (0==kbrd) kbrd =new Keyboard() ;
 if (0==mnl)   mnl =new MenuList ;
 if (0==fldg) fldg =new FLDigts;
 if (0==whl)    whl=new Wheel;
 if (0==rtx)  rtx=new RunTxt;
 if (0==knsm) knsm=new KnobSm;
 if (0==ldbtn) ldbtn=new LedButton;

 GEFFECT[0]=new Engine;
 emptyimput[0]=(float*) malloc(BUFSIZE*sizeof(float));
 memset(emptyimput[0],0,BUFSIZE*sizeof(float));
 emptyimput[1]=(float*) malloc(BUFSIZE*sizeof(float));
 memset(emptyimput[1],0,BUFSIZE*sizeof(float));

 outPA[0]=(float*) malloc(BUFSIZE*sizeof(float));
 memset(outPA[0],0,BUFSIZE*sizeof(float));
 outPA[1]=(float*) malloc(BUFSIZE*sizeof(float));
 memset(outPA[1],0,BUFSIZE*sizeof(float));
 
	int err=Pa_Initialize();  
	//MessageBox(0,Pa_GetErrorText( err ) ,"Error",0);
	err=Pa_OpenStream(
				&stream,
				paNoDevice,/* default input device */
				0,              /* no input */
				paFloat32,		/* 32 bit floating point input */
				NULL,
				Pa_GetDefaultOutputDeviceID(), /* default output device */
				2,          /* stereo output */
				paFloat32,      /* 32 bit floating point output */
				NULL,
				44100,///SAMPLE_RATE,
				BUFSIZE, ///FRAMES_PER_BUFFER,            /* frames per buffer */
				0,              /* number of buffers, if zero then use default minimum */
				paClipOff,      /* we won't output out of range samples so don't bother clipping them */
				patestCallback,
				NULL);///&data );
	//MessageBox(0,Pa_GetErrorText( err ) ,"Error",0);
    err=Pa_StartStream( stream );
	///while( Pa_StreamTime( stream ) < (1024*32*128) ) Pa_Sleep(10);
	strea=stream;
	///MessageBox(0,Pa_GetErrorText( err ) ,"Error",0);

    CreateEditor((HWND)NULL,(long) 0);
	///HWND hPlug[8];
 //HMIDIIN lphmo;///////midi-in
 //int rot = midiInOpen(&lphmo,0,(unsigned long) GetActiveWindow(),0,CALLBACK_WINDOW);//open MIDI IN.
 //if (rot != 0) MessageBox(0,"Can not open device ! It could be busy.","ERR",0);///warning
 //midiInStart(lphmo);//start receiveing the messages
//float a=-0.5;
//float b=4.7;
//#define FLOATCOPY(to,from) *((long*)&to)=*((long*)&from)   //3355
/*	
#define LIMIT 999
long limit =333;
//Starta();
long pos=59 ;
long a= 100;
long b=60;

_asm {
		mov     ecx,b
		sub     ecx,70
		cmp     ecx,80000000H 
		jna     IsPositive
		add     ecx,limit // add to registers togther 		
		IsPositive: 
		mov     pos,ecx	// Move value in register back to x 
		}
char dak[16];
ltoa(pos,dak,10);

MessageBox(0,dak,"OK",0);*/

//while(x < LIMIT)

//if (a==6) MessageBox(0,"6","OK",0);
 
  //...code

  //...code to time
 /* 
#define DEFINE_ALIGNED_DOUBLES(n)	\
char __array_fastdouble[((n)*sizeof(double))+8];	\
double*	__pFastDouble = (double *) ((((long)&__array_fastdouble[0]) +8)& -8)

#define ALIGNED_DOUBLE(i)		__pFastDouble[i]


DEFINE_ALIGNED_DOUBLES(3);	
#define	a0		ALIGNED_DOUBLE(0)
#define	b0		ALIGNED_DOUBLE(1)	
#define	c0		ALIGNED_DOUBLE(2)	

#define IS_LESS_THANZEROt(val)  {_asm mov  eax,val  _asm and eax,80000000H _asm jz IsPos }
#define IS_LESS_THANZEROd(val) (*((long*)&val)>>31)
float a0,b0,c0;
a0=12.;
b0=12.3;
*/ /*
long gain[2] = {0, -578}; 
PERF_DECLARE;
PERF_START;
#define FRAME 578
long c=578;
long *ind0=&c;
for (long r=0;r<10000000;++r) {
//WRAP(0,578);

_asm {	///MAGNUS
mov eax,c
dec eax
sar eax,1Fh
and eax,FRAME
add eax,c
mov c,eax
	}
c=1/(c-c);
	_asm{ ///BRAM
mov         edx,c
sar         edx,1Fh
mov         eax,c
sub         eax,gain[edx]
mov         c,eax
	}
//c--;
//c+=(c>>31)&578;
//
//c -= gain[(*(long *)&c)>>31];
//if(--c==0) c=578;
///if (c>578) MessageBox(0,"error","ED",0);break;
//IsPos:
//;
}
PERF_STOP;
PERF_REPORT;
*/

//}
//Enda();
	/*
HFILE hndFl1 = _lopen("C:/knob/0.bmp",0);///

BYTE *bmprr;
char fromfile[64];
///strcat(fromfile,"C:/images/Knob");
BYTE *duk;
duk=(BYTE*) malloc(75654*2);
bmprr=(BYTE*) malloc(1254*2);
_lread(hndFl1,bmprr,1254);///filling out TitleWave struc
memcpy(duk,ma19,sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER));
#define KNOBSZ 20
#define KNOBSQTTY 63
#define STICKLENGH 8
#define STICKCENTER 3
for (int b=0;b<KNOBSQTTY;++b)
{
	//wsprintf(fromfile, "C:/images/Knob%d", b+1);
	//strcat(fromfile,".bmp");
    //HFILE hndFl1 = _lopen(fromfile,0);///
    ////if (b==34) MessageBox(0,fromfile,"Error opening",0); 
	//_lread(hndFl1,bmprr,1902);
float angle=(45.f-((float)b/KNOBSQTTY*150.f))	/180.f*TWOPI;
long x_palki[STICKLENGH];
long y_palki[STICKLENGH];
float x_palki_shadow[STICKLENGH];
float y_palki_shadow[STICKLENGH];
for (long h=STICKCENTER;h<STICKLENGH;++h) ///39 49 67
{
x_palki[h]=(long)((float)KNOBSZ/2-(float)h*cos((float)angle));
y_palki[h]=(long)((float)KNOBSZ/2-(float)h*sin(-(float)angle));
x_palki_shadow[h]=1.f+((float)KNOBSZ/2-(float)h*cos((float)angle))-(float)x_palki[h];
y_palki_shadow[h]=1.f+((float)KNOBSZ/2-(float)h*cos((float)angle))-(float)y_palki[h];
}

for (long x=0;x<KNOBSZ;++x) 
{
	for (long y=0;y<KNOBSZ;++y) {

	long count =sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+
		((KNOBSZ-1 - y) * ((((KNOBSZ * 3) -1) / 4) + 1) * 4) + x * 3;

	long count2 =sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+
		((KNOBSZ-1 - y) * ((((KNOBSZ*KNOBSQTTY * 3) -1) / 4) + 1) * 4) + (b*KNOBSZ +x) * 3 ;

	memcpy(&duk[count2],&bmprr[count],3);
      for (long h=STICKCENTER;h<STICKLENGH;++h)
	  {
	  
      if ((x==x_palki[h])&&(y==y_palki[h])) 
	  {duk[count2]=0;//4+39.f*(h-STICKCENTER)/STICKLENGH;
	  duk[count2+1]=0;//12+37.f*(h-STICKCENTER)/STICKLENGH;
	  duk[count2+2]=0;}//4+35.f*(h-STICKCENTER)/STICKLENGH;}

if ((x==x_palki[h]+1)&&(y==y_palki[h])) 
	  {duk[count2]/=x_palki_shadow[h];
	  duk[count2+1]/=x_palki_shadow[h];
	  duk[count2+2]/=x_palki_shadow[h];}
if ((x==x_palki[h])&&(y==y_palki[h]+1)) 
	  {duk[count2]/=y_palki_shadow[h];
	  duk[count2+1]/=y_palki_shadow[h];
	  duk[count2+2]/=y_palki_shadow[h];}

	  }
	}
	}
 CloseHandle(&hndFl1);///////////
}
HFILE hndF2 = _lcreat("Knob_out.bmp",0);
_llseek(hndF2,0,SEEK_SET);///
_lwrite (hndF2,(char*)duk, 75654);///////
*/
    MSG Msg;
    ///////////////////////////////////////////////////////////

    while(GetMessage(&Msg, NULL, 0, 0))
   {
      TranslateMessage(&Msg);
      DispatchMessage(&Msg);
   }
   return Msg.wParam;

}
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
