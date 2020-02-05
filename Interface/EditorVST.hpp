/// EditorVST.hpp
/// HERE WE COMPOSE THE MAIN PROGRAM INTERFACE (EDITOR)
/// THE FILE COULD BE COMPILED AS VST AND AS EXE
//-----------------------------------------------------------------------------------------
#include "..\Exe\CompileType.h"

#define WINSTYLE WS_CHILD|WS_VISIBLE
#define TOOLHIGH 0
#define TOOLWDTH 0
///#define CHECKPROG_VOLUME_AND_REPORT_TO_TXT
#ifdef EXE_COMPILE 
#undef WINSTYLE
#undef TOOLHIGH
#undef TOOLWDTH 
#define WINSTYLE WS_VISIBLE|WS_SYSMENU
#define TOOLHIGH 2*GetSystemMetrics( SM_CYBORDER )+2*GetSystemMetrics( SM_CYEDGE)+GetSystemMetrics(SM_CYCAPTION	)
#define TOOLWDTH 2*GetSystemMetrics( SM_CXBORDER )+2*GetSystemMetrics( SM_CXEDGE)
#endif 
//-----------------------------------------------------------------------------------------
#ifndef EXE_COMPILE
#define GOOUT 
#endif
#ifdef EXE_COMPILE 
#define GOOUT case WM_DESTROY:\
			  exit(0);\
			  PostQuitMessage (0);\
			  Pa_StopStream( strea );\
			  Pa_CloseStream( strea );\
			  Pa_Terminate();\
		      return FALSE;
/*<---------------------------------------------------------------------->*/
char ispress[128];
extern void *strea;
HWND hCPU;
void CALLBACK MyTimer (HWND hwnd, UINT uMsg,UINT idEvent,DWORD dwTime );
extern int Pa_StopStream(void *stream);
extern int Pa_CloseStream(void *stream);
extern int Pa_Terminate();
///--------------------
#include "stdlib.h"
#define PERF_DECLARE         \
  __int64 MSRB, MSRE;        \
  void *mrsb = &MSRB;    \
  void *mrse = &MSRE;    \
  char perfmtrbuf[100];    

#define PERF_START          \
  {_asm mov eax, 0          \
  _asm cpuid                \
  _asm rdtsc                \
  _asm mov ebx, mrsb        \
  _asm mov dword ptr [ebx], eax    \
  _asm mov dword ptr [ebx+4], edx  \
  _asm mov eax, 0           \
  _asm cpuid}

#define PERF_STOP           \
  {_asm mov eax, 0          \
  _asm cpuid                \
  _asm rdtsc                \
  _asm mov ebx, mrse        \
  _asm mov dword ptr [ebx], eax   \
  _asm mov dword ptr [ebx+4], edx \
  _asm mov eax, 0           \
  _asm cpuid}

#define PERF_REPORT          \
  {_ui64toa(MSRE-MSRB, perfmtrbuf, 10);    \
  MessageBox(0,perfmtrbuf,"Cycles needed: ", 0);}
/*<---------------------------------------------------------------------->*/
#ifdef CHECKPROG_VOLUME_AND_REPORT_TO_TXT
long cou=0;
float maxxa[32];
long ba;
HFILE hndF2; 
#endif

#endif 
extern void *GEFFECT[32];
//-----------------------------------------------------------------------------------------
#include "..\Interface\digits.hpp"
#include "..\Interface\fldigits.hpp"
#include "..\Interface\knob.hpp"
#include "..\Interface\wheel.hpp"
#include "..\Interface\keyboard.hpp"
#include "..\Interface\ledbtn.hpp"
#include "..\Interface\menulist.hpp"
#include "..\Interface\curves.hpp"
#include "..\Interface\runtext.hpp"
#include "..\Interface\knobSmall.hpp"
//#include "..\Interface\ledbtn.hpp"
#include "..\Interface\logopak.h"
#include "..\Interface\programms.h"
#include "..\Interface\handles.h"
//-----------------------------------------------------------------------------------------

#ifndef EXE_COMPILE
extern void *EGAIN[8];
#endif
HWND hPlug[8];
//-----------------------------------------------------------------------------------------
LONG WINAPI MakeApp (HWND hW, UINT msg, WPARAM wParam, LPARAM lParam);

extern void* hInstance;

static short kEditorHeight=289;
static short kEditorWidth =650;
static HANDLE HBlogo=0;
static unsigned char *logoarr;
//--------------------------------
#include "..\Interface\dialogN.h"
//--------------------------------
static Craftvs *curv=0;
static Digits *dg=0;
static Knob *kn=0;
static Keyboard* kbrd=0;
static MenuList *mnl=0;
static FLDigts *fldg=0;
static Wheel *whl=0;
static RunTxt *rtx=0;
static KnobSm *knsm=0;
static LedButton *ldbtn=0; 
static HandlesToHide hth[8];
//-----------------------------------------------------------------------------------------
bool CreateEditor(HWND systemWindow ,long n_instanse)
{
    char *cl_nm;
	char bbuf[10];
	cl_nm = (char*) malloc(32);
	memset(cl_nm ,0,32);
	itoa(n_instanse,&bbuf[0],10);
	strcat(cl_nm,"Editor");
	strcat(cl_nm,&bbuf[0]);  
	
	///MessageBox(0,cl_nm,"Class Name",0); 
      
      WNDCLASS wc;
      memset(&wc,0,sizeof(wc));
	  wc.lpfnWndProc       =      MakeApp;
	  wc.style             =      0;
	  wc.lpszMenuName      =      NULL;
	  wc.cbWndExtra        =      0; 
	  wc.hInstance         =      (HINSTANCE) hInstance;
	  wc.hCursor           =      0;
	  wc.hbrBackground     =      NULL;
	  wc.lpszClassName     =      cl_nm;
	  wc.hIcon             =      0;///
	
//	  MessageBox(0,"2","Class Name",0); 
	 
	  RegisterClass(&wc);
	
      HWND hW = CreateWindow(  ///
	  wc.lpszClassName,
	  "VST SYNTH.",WINSTYLE,
      0,0,kEditorWidth+TOOLWDTH,kEditorHeight+TOOLHIGH,
      (HWND) systemWindow, NULL, (HINSTANCE)hInstance, (LPVOID)MakeApp);///this);
      ///SetWindowLong((HWND)hW,GWL_USERDATA,(long)this);
      if (0==hW) {
		  MessageBox(0, "Window Creation Failed!", "Error!",0);  
      return 0;
	  }
if (HBlogo==0)
{
logoarr=(unsigned char*)malloc(589824);
dg->Decode(logopak,logoarr,86243);//
HBlogo=dg->extro_lbs(GetDC(systemWindow),(char*)logoarr);
free(logoarr);
/////
}
if (hW!=NULL)
{
kbrd->add_keyboard(hW, 151-115+15,187, n_instanse);

hth[n_instanse].gains[0]=dg->add_digits(hW, 308-115+16,37,3, 8*n_instanse,100,0);
hth[n_instanse].gains[1]=dg->add_digits(hW, 308-115+16,57,3, 8*n_instanse+1,100,0);
hth[n_instanse].gains[2]=dg->add_digits(hW, 308-115+16,77,3, 8*n_instanse+2,100,0);
hth[n_instanse].gains[3]=dg->add_digits(hW, 308-115+16,97,3, 8*n_instanse+3,100,0);
hth[n_instanse].gains[4]=dg->add_digits(hW, 308-115+16,117,3, 8*n_instanse+4,100,0);
hth[n_instanse].gains[5]=dg->add_digits(hW, 308-115+16,137,3, 8*n_instanse+5,100,0);

hth[n_instanse].gains[6]=dg->add_digits(hW, 390+18,130,3, 8*n_instanse+6,100,0);

/////
hth[n_instanse].menus[0]=mnl->add_menulist(hW,55,37,16*n_instanse,  0);
hth[n_instanse].menus[1]=mnl->add_menulist(hW,55,57,16*n_instanse+1,0);
hth[n_instanse].menus[2]=mnl->add_menulist(hW,55,77,16*n_instanse+2,0);
hth[n_instanse].menus[3]=mnl->add_menulist(hW,55,97,16*n_instanse+3,0);
hth[n_instanse].menus[4]=mnl->add_menulist(hW,55,117,16*n_instanse+4,0);
hth[n_instanse].menus[5]=mnl->add_menulist(hW,55,137,16*n_instanse+5,0);

hth[n_instanse].menus[6]=mnl->add_menulist(hW,362-115+15,40,16*n_instanse+6,1);
hth[n_instanse].menus[7]=mnl->add_menulist(hW,459-115+15,40,16*n_instanse+7,1);

 ///short
hth[n_instanse].tunes[0]=fldg->add_fldigits(hW,171,37,8*n_instanse, 2);
hth[n_instanse].tunes[1]=fldg->add_fldigits(hW,171,57,8*n_instanse+1,2);
hth[n_instanse].tunes[2]=fldg->add_fldigits(hW,171,77,8*n_instanse+2,2);
hth[n_instanse].tunes[3]=fldg->add_fldigits(hW,171,97,8*n_instanse+3,2);
hth[n_instanse].tunes[4]=fldg->add_fldigits(hW,171,117,8*n_instanse+4,2);
hth[n_instanse].tunes[5]=fldg->add_fldigits(hW,171,137,8*n_instanse+5,2);

hth[n_instanse].phases[0]=knsm->add_knobsm(hW,143,37,8*n_instanse);
hth[n_instanse].phases[1]=knsm->add_knobsm(hW,143,57,8*n_instanse+1);
hth[n_instanse].phases[2]=knsm->add_knobsm(hW,143,77,8*n_instanse+2);
hth[n_instanse].phases[3]=knsm->add_knobsm(hW,143,97,8*n_instanse+3);
hth[n_instanse].phases[4]=knsm->add_knobsm(hW,143,117,8*n_instanse+4);
hth[n_instanse].phases[5]=knsm->add_knobsm(hW,143,137,8*n_instanse+5);


hth[n_instanse].knobs[0]=kn->add_knob(hW,267,83, 8*n_instanse);//cut 
hth[n_instanse].knobs[1]=kn->add_knob(hW,309,129, 8*n_instanse+1);//reso-Programms[prognum][23] 

hth[n_instanse].knobs[2]=kn->add_knob(hW,368,82, 8*n_instanse+2);///rel//Programms[prognum][24]
hth[n_instanse].knobs[3]=kn->add_knob(hW,368,129,8*n_instanse+3);//attck-Programms[prognum][25]

kn->add_knob(hW,464,59, 8*n_instanse+4);//cut 2
kn->add_knob(hW,502,59,8*n_instanse+5);//chorus
kn->add_knob(hW,540,59, 8*n_instanse+6);//size
kn->add_knob(hW,578,59,8*n_instanse+7);//reverb

hth[n_instanse].curves[0]=curv->add_curves(hW,311,80,2*n_instanse);
hth[n_instanse].curves[1]=curv->add_curves(hW,410,80,2*n_instanse+1);

whl->add_wheel(hW,16,202,2*n_instanse);

rtx->add_runtxt(hW,462,20,n_instanse);
ldbtn->add_ledbtn(hW,492,130,n_instanse);

}
hPlug[n_instanse]=hW;

#ifdef EXE_COMPILE
SetTimer(hPlug[0],1,1000,(TIMERPROC) MyTimer);////CPU LOAD FOR EXE

#ifdef CHECKPROG_VOLUME_AND_REPORT_TO_TXT
for (int w=0;w<32;++w) maxxa[w]=0.f;
hndF2 = _lcreat("to.txt",0);
#endif

#endif
return true;
}
//-----------------------------------------------------------------------------------------

void editPresetName(int exemplyar)
{

translate_exemplar=exemplyar;
NewF(hPlug[exemplyar]);

}

//-----------------------------------------------------------------------------------------
LONG WINAPI MakeApp (HWND hW, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {

	case WM_ERASEBKGND:  //// DRAW BACKGROUND
				{
                BITMAP bm;
                HDC hdcMemory;
                GetObject(HBlogo, sizeof(bm), &bm);
                hdcMemory = CreateCompatibleDC((HDC) wParam);
                SelectObject(hdcMemory, HBlogo);
                BitBlt((HDC) wParam,0,	0,kEditorWidth, kEditorHeight,hdcMemory,0,0,SRCCOPY);
                DeleteDC(hdcMemory);
                ReleaseDC(hW, (HDC) wParam);
				}
                return 1L;
//--------------------------------PC-KEY PIANO
#ifdef EXE_COMPILE
	case WM_KEYDOWN:
		{
long nnot=1;
switch (wParam) {
case 90: nnot=1 ; break; 
case 83: nnot=2 ; break; 
case 88: nnot=3 ; break; 
case 68: nnot=4 ; break; 
case 67: nnot=5 ; break; 
case 86: nnot=6 ; break; 
case 71: nnot=7 ; break; 
case 66: nnot=8 ; break; 
case 72: nnot=9 ; break; 
case 78: nnot=10 ; break; 
case 74: nnot=11 ; break; 
case 76: nnot=14 ; break; 
case 77: nnot=12 ; break; 
case 81: nnot=13 ; break; 
case 50: nnot=14 ; break; 
case 87: nnot=15 ; break; 
case 51: nnot=16 ; break; 
case 69: nnot=17 ; break; 
case 82: nnot=18 ; break; 
case 53: nnot=19 ; break; 
case 84: nnot=20 ; break; 
case 54: nnot=21 ; break; 
case 89: nnot=22 ; break; 
case 55: nnot=23 ; break; 
case 85: nnot=24 ; break; 
case 73: nnot=25 ; break; 
case 57: nnot=26 ; break; 
case 79: nnot=27 ; break; 
case 48: nnot=28 ; break; 
case 80: nnot=29 ; break; 
case 186: nnot=32 ; break; 
case 188: nnot=13 ; break; 
case 189: nnot=17 ; break; 
case 190: nnot=15 ; break; 
case 192: nnot=16 ; break; 
case 221: nnot=30 ; break; 
case 219: nnot=31 ; break; 
break;
}
if (ispress[nnot+47]!=1)
{
((Engine*) GEFFECT[0] )->midiOn(nnot+47);
ispress[nnot+47]=1;
kbrd->SetNoteOn(0,nnot+47);
}
		}
break;
	case WM_KEYUP:
		{
long nnot=1;
switch (wParam) {
case 90: nnot=1 ; break; 
case 83: nnot=2 ; break; 
case 88: nnot=3 ; break; 
case 68: nnot=4 ; break; 
case 67: nnot=5 ; break; 
case 86: nnot=6 ; break; 
case 71: nnot=7 ; break; 
case 66: nnot=8 ; break; 
case 72: nnot=9 ; break; 
case 78: nnot=10 ; break; 
case 74: nnot=11 ; break; 
case 76: nnot=14 ; break; 
case 77: nnot=12 ; break; 
case 81: nnot=13 ; break; 
case 50: nnot=14 ; break; 
case 87: nnot=15 ; break; 
case 51: nnot=16 ; break; 
case 69: nnot=17 ; break; 
case 82: nnot=18 ; break; 
case 53: nnot=19 ; break; 
case 84: nnot=20 ; break; 
case 54: nnot=21 ; break; 
case 89: nnot=22 ; break; 
case 55: nnot=23 ; break; 
case 85: nnot=24 ; break; 
case 73: nnot=25 ; break; 
case 57: nnot=26 ; break; 
case 79: nnot=27 ; break; 
case 48: nnot=28 ; break; 
case 80: nnot=29 ; break; 
case 186: nnot=32 ; break; 
case 188: nnot=13 ; break; 
case 189: nnot=17 ; break; 
case 190: nnot=15 ; break; 
case 192: nnot=16 ; break; 
case 221: nnot=30 ; break; 
case 219: nnot=31 ; break; 
break;
}
((Engine*) GEFFECT[0] )->midiOff(nnot+47);
ispress[nnot+47]=0;
kbrd->SetNoteOff(0,nnot+47);
		}
break;
//--------------------------------PC-KEY PIANO
 case MM_MIM_DATA:
	 {
		 int MIDIchan=0;
                     ///// PLAY NOTE
					 if ((LOBYTE(lParam)==144 + MIDIchan)&(ispress[HIBYTE(lParam)]==0)&(HIWORD(lParam)!=0)) {
				     ((Engine*) GEFFECT[0] )->midiOn(HIBYTE(lParam));
                     ispress[HIBYTE(lParam)]=1;
					 }
				     if ((LOBYTE(lParam)==128+MIDIchan)|(HIWORD(lParam)!=0)) { //keyup
				     ((Engine*) GEFFECT[0] )->midiOff(HIBYTE(lParam));
                     ispress[HIBYTE(lParam)]=0;
					 }
     break;
	 }
#endif
//--------------------------------MIDI PIANO

  case WM_MIDIKEYPRESSED:((Engine*) GEFFECT[wParam] )->midiOn(lParam+48);	break;
  case WM_MIDIKEYUP:     ((Engine*) GEFFECT[wParam] )->midiOff(lParam+48);	break;
  case WM_MENULST:       
	  {
      switch (wParam&15)
	  {
	  case 0: ((Engine*) GEFFECT[wParam/16] )->buildOsc(lParam,0);break;
	  case 1: ((Engine*) GEFFECT[wParam/16] )->buildOsc(lParam,1);break;
      case 2: ((Engine*) GEFFECT[wParam/16] )->buildOsc(lParam,2);break;
	  case 3: ((Engine*) GEFFECT[wParam/16] )->buildOsc(lParam,3);break;
	  case 4: ((Engine*) GEFFECT[wParam/16] )->buildOsc(lParam,4);break;
	  case 5: ((Engine*) GEFFECT[wParam/16] )->buildOsc(lParam,5);break;
      case 6: ((Engine*) GEFFECT[wParam/16] )->buildEnvelope(lParam,0);break;
      case 7: ((Engine*) GEFFECT[wParam/16] )->buildEnvelope(lParam,1);break;

  }
	  break;
	  }
  case WM_FLDIGITS: ((Engine*) GEFFECT[wParam/8] )->SetTuneValue(lParam,wParam&0x07);break;

  case WM_DIGITSRUN: ///WM_DIGITSUP:
	  {
	  if ((wParam&0x07)!=6) 
	  {
	  ((Engine*) GEFFECT[wParam/8] )->setGain(lParam,wParam&0x07);break;
	  }
	  else
	  {
	  ((Engine*) GEFFECT[wParam/8] )->SetVolume(lParam);
	  }
	  }
	  break;

  case WM_PTCHWHEEL:((Engine*) GEFFECT[wParam/2] )->setWheel(lParam);break;

  case WM_PTCHWHEELUP: ((Engine*) GEFFECT[wParam/2] )->setWheel(64);break;

  case WM_GALACTIX: hideCtrls(hth,wParam,lParam);break;//// 
  case WM_HIDCTRLSWAV: hideCtrls2(hth,wParam,lParam);break;//// 

  case WM_EXPORTWAV: editPresetName(wParam);/////
	  break;

  case WM_KNOB:
	  {
    switch (wParam&0x07)
	{
    case 0: ((Engine*) GEFFECT[wParam/8] )->setCut0(lParam );break;
    case 2: ((Engine*) GEFFECT[wParam/8] )->setRelease(lParam );break;
    case 3: ((Engine*) GEFFECT[wParam/8] )->setAttack(lParam );break;
	case 4: ((Engine*) GEFFECT[wParam/8] )->setCut(lParam );break;
    case 5: ((Engine*) GEFFECT[wParam/8] )->setChorus(lParam);break;
    case 6: ((Engine*) GEFFECT[wParam/8] )->setReverbSize((float) lParam/127. );break;
	case 7: ((Engine*) GEFFECT[wParam/8] )->setReverbWet((float) lParam/127. );break;
	}
	  }
      break;
  case WM_KNOBUP:	 if ((wParam&0x07)==1) 
						 ((Engine*) GEFFECT[wParam/8] )->setReso(lParam );break;
  
  case WM_CURVUP: ((Engine*) GEFFECT[wParam/8] )->setVeloSens(lParam,wParam&0x01);break;///prelimenary
  case WM_RUNTXT: 	  PROGRAMMSET(wParam,lParam ); break;///
  case WM_KNOBSMUP: ((Engine*) GEFFECT[wParam/8] )->setPhase(lParam,wParam&0x07);break;///
     GOOUT
      }

return DefWindowProc (hW,msg,wParam,lParam);
}
//----------------------------------------------------------------------------------------
#ifdef EXE_COMPILE

void CALLBACK MyTimer (HWND hwnd, UINT uMsg,UINT idEvent,DWORD dwTime )
{
	if (uMsg==WM_TIMER)
	{
    int per= (int)(Pa_GetCPULoad(strea)*100);
	char dak[64];
	strcpy(dak,"VST SYNTH- CPU: ");
	itoa(per,&dak[16],10);
	strcat(dak,"%");
	SetWindowText(hwnd,dak);

#ifdef CHECKPROG_VOLUME_AND_REPORT_TO_TXT
++cou;
if (cou%10==0)
{   
	++ba;
	PROGRAMMSET(0,ba);	
}
if (cou%10==3)
{
((Engine*) GEFFECT[0] )->midiOn(20+48);
}
if (cou%10==9)
{
((Engine*) GEFFECT[0] )->midiOff(20+48);
  int rj = 2573;///next row
  _lwrite (hndF2, (LPSTR) &rj, 2);///////	  
	char buk[16];
	ltoa(maxxa[ba]*32768,buk,10);
    _lwrite (hndF2, (LPSTR) buk,strlen(buk));///////
	
}
#endif //CHECKPROG_VOLUME_AND_REPORT_TO_TXT


	}
}

#endif //EXE_COMPILE
//----------------------------------------------------------------------------------------
void PROGRAMMSET(int Exemplyar,int prognum)
{
	((Engine*) GEFFECT[Exemplyar] )->setCurrentProg(prognum);
	///Programms[prognum][32]
	ldbtn->RemoveEffectFromScreen(Exemplyar);
            ((Engine*) GEFFECT[Exemplyar] )->setReverbWet(Programms[prognum][29]);      
            ((Engine*) GEFFECT[Exemplyar] )->setReverbSize(Programms[prognum][28]);      
			((Engine*) GEFFECT[Exemplyar] )->setChorus(Programms[prognum][27]*127);      
			((Engine*) GEFFECT[Exemplyar] )->SetTunesValues(Programms[prognum][6],Programms[prognum][7],Programms[prognum][8],Programms[prognum][9],Programms[prognum][10],Programms[prognum][11]);      
			((Engine*) GEFFECT[Exemplyar] )->setReso(Programms[prognum][23]*127);     
			((Engine*) GEFFECT[Exemplyar] )->setCut0(Programms[prognum][22]*127);      
			((Engine*) GEFFECT[Exemplyar] )->setCut(Programms[prognum][26]*127); 
			
			((Engine*) GEFFECT[Exemplyar] )->buildEnvelope(Programms[prognum][18],0);      
            ((Engine*) GEFFECT[Exemplyar] )->buildEnvelope(Programms[prognum][19]  ,1);      
		    ((Engine*) GEFFECT[Exemplyar] )->SetGainsValues(Programms[prognum][12],Programms[prognum][13],Programms[prognum][14],Programms[prognum][15],Programms[prognum][16],Programms[prognum][17],Programms[prognum][30]);      
		    ((Engine*) GEFFECT[Exemplyar] )->buildAllOsc(Programms[prognum][0],Programms[prognum][1],Programms[prognum][2],Programms[prognum][3],Programms[prognum][4],Programms[prognum][5]);      
			((Engine*) GEFFECT[Exemplyar] )->setAttack(Programms[prognum][25]*127);      
			((Engine*) GEFFECT[Exemplyar] )->setRelease(Programms[prognum][24]*127);      
		    ((Engine*) GEFFECT[Exemplyar] )->setVeloSens(Programms[prognum][20],0);      
            ((Engine*) GEFFECT[Exemplyar] )->setVeloSens(Programms[prognum][21],1); 
			
			((Engine*) GEFFECT[Exemplyar] )->setPhase(Programms[prognum][31],0);
			((Engine*) GEFFECT[Exemplyar] )->setPhase(Programms[prognum][32],1);
			((Engine*) GEFFECT[Exemplyar] )->setPhase(Programms[prognum][33],2);
			((Engine*) GEFFECT[Exemplyar] )->setPhase(Programms[prognum][34],3);
			((Engine*) GEFFECT[Exemplyar] )->setPhase(Programms[prognum][35],4);
			((Engine*) GEFFECT[Exemplyar] )->setPhase(Programms[prognum][36],5);
 //  ((Engine*) GEFFECT[Exemplyar] )->cut=((Engine*) GEFFECT[Exemplyar] )->cut_desired;
 //  ((Engine*) GEFFECT[Exemplyar] )->chorus=((Engine*) GEFFECT[Exemplyar] )->chorus_desired;
			
rtx->SetRuntxtItem(Exemplyar,prognum);
curv->SetCurvesValue(2*Exemplyar,Programms[prognum][20]);
curv->SetCurvesValue(2*Exemplyar+1,Programms[prognum][21]);
     
mnl->SetMenuListItem( 16*Exemplyar,    Programms[prognum][0]);
mnl->SetMenuListItem( 16*Exemplyar+1,  Programms[prognum][1]);
mnl->SetMenuListItem( 16*Exemplyar+2,  Programms[prognum][2]);
mnl->SetMenuListItem( 16*Exemplyar+3,  Programms[prognum][3]);
mnl->SetMenuListItem( 16*Exemplyar+4,  Programms[prognum][4]);
mnl->SetMenuListItem( 16*Exemplyar+5,  Programms[prognum][5]);			
          	       
fldg->SetFLDigits( 8*Exemplyar, Programms[prognum][6]);
fldg->SetFLDigits( 8*Exemplyar+1,Programms[prognum][7]);
fldg->SetFLDigits( 8*Exemplyar+2, Programms[prognum][8]);
fldg->SetFLDigits( 8*Exemplyar+3, Programms[prognum][9]);
fldg->SetFLDigits( 8*Exemplyar+4, Programms[prognum][10]);
fldg->SetFLDigits( 8*Exemplyar+5, Programms[prognum][11]);
		    
mnl->SetMenuListItem( 16*Exemplyar+6, Programms[prognum][18]);
mnl->SetMenuListItem( 16*Exemplyar+7, Programms[prognum][19]);
	   
dg->SetDigitsValue ( 8*Exemplyar,    Programms[prognum][12]);
dg->SetDigitsValue ( 8*Exemplyar+1,  Programms[prognum][13]);
dg->SetDigitsValue ( 8*Exemplyar+2,  Programms[prognum][14]);
dg->SetDigitsValue ( 8*Exemplyar+3,  Programms[prognum][15]);
dg->SetDigitsValue ( 8*Exemplyar+4,  Programms[prognum][16]);
dg->SetDigitsValue ( 8*Exemplyar+5,  Programms[prognum][17]);
dg->SetDigitsValue ( 8*Exemplyar+6,  Programms[prognum][30]);		

kn->SetKnobValue( 8*Exemplyar+2,Programms[prognum][24]*127);
kn->SetKnobValue( 8*Exemplyar  ,Programms[prognum][22]*127);
kn->SetKnobValue( 8*Exemplyar+4,Programms[prognum][26]*127);
kn->SetKnobValue( 8*Exemplyar+3,Programms[prognum][25]*127);
kn->SetKnobValue( 8*Exemplyar+1,Programms[prognum][23]*127);
kn->SetKnobValue( 8*Exemplyar+5,Programms[prognum][27]*127);	
kn->SetKnobValue( 8*Exemplyar+7,Programms[prognum][29]*127);
kn->SetKnobValue( 8*Exemplyar+6,Programms[prognum][28]*127);

knsm->SetKnobSmValue( 8*Exemplyar  ,Programms[prognum][31]);
knsm->SetKnobSmValue( 8*Exemplyar+1,Programms[prognum][32]);
knsm->SetKnobSmValue( 8*Exemplyar+2,Programms[prognum][33]);
knsm->SetKnobSmValue( 8*Exemplyar+3,Programms[prognum][34]);
knsm->SetKnobSmValue( 8*Exemplyar+4,Programms[prognum][35]);
knsm->SetKnobSmValue( 8*Exemplyar+5,Programms[prognum][36]);
}
//----------------------------------------------------------------------------------------
void Updatef(long Exemplyar)
{
long prognum=((Engine*) GEFFECT[Exemplyar] )->getCurrentProg();
///ldbtn->RemoveEffectFromScreen(Exemplyar);
rtx->SetRuntxtItem(Exemplyar,prognum);
curv->SetCurvesValue(2*Exemplyar,Programms[prognum][20]);
curv->SetCurvesValue(2*Exemplyar+1,Programms[prognum][21]);
     
mnl->SetMenuListItem( 16*Exemplyar,    Programms[prognum][0]);
mnl->SetMenuListItem( 16*Exemplyar+1,  Programms[prognum][1]);
mnl->SetMenuListItem( 16*Exemplyar+2,  Programms[prognum][2]);
mnl->SetMenuListItem( 16*Exemplyar+3,  Programms[prognum][3]);
mnl->SetMenuListItem( 16*Exemplyar+4,  Programms[prognum][4]);
mnl->SetMenuListItem( 16*Exemplyar+5,  Programms[prognum][5]);			
          	       
fldg->SetFLDigits( 8*Exemplyar, Programms[prognum][6]);
fldg->SetFLDigits( 8*Exemplyar+1,Programms[prognum][7]);
fldg->SetFLDigits( 8*Exemplyar+2, Programms[prognum][8]);
fldg->SetFLDigits( 8*Exemplyar+3, Programms[prognum][9]);
fldg->SetFLDigits( 8*Exemplyar+4, Programms[prognum][10]);
fldg->SetFLDigits( 8*Exemplyar+5, Programms[prognum][11]);
		    
mnl->SetMenuListItem( 16*Exemplyar+6, Programms[prognum][18]);
mnl->SetMenuListItem( 16*Exemplyar+7, Programms[prognum][19]);
	   
dg->SetDigitsValue ( 8*Exemplyar,    Programms[prognum][12]);
dg->SetDigitsValue ( 8*Exemplyar+1,  Programms[prognum][13]);
dg->SetDigitsValue ( 8*Exemplyar+2,  Programms[prognum][14]);
dg->SetDigitsValue ( 8*Exemplyar+3,  Programms[prognum][15]);
dg->SetDigitsValue ( 8*Exemplyar+4,  Programms[prognum][16]);
dg->SetDigitsValue ( 8*Exemplyar+5,  Programms[prognum][17]);
dg->SetDigitsValue ( 8*Exemplyar+6,  Programms[prognum][30]);		

kn->SetKnobValue( 8*Exemplyar+2,Programms[prognum][24]*127);
kn->SetKnobValue( 8*Exemplyar  ,Programms[prognum][22]*127);
kn->SetKnobValue( 8*Exemplyar+4,Programms[prognum][26]*127);
kn->SetKnobValue( 8*Exemplyar+3,Programms[prognum][25]*127);
kn->SetKnobValue( 8*Exemplyar+1,Programms[prognum][23]*127);
kn->SetKnobValue( 8*Exemplyar+5,Programms[prognum][27]*127);	
kn->SetKnobValue( 8*Exemplyar+7,Programms[prognum][29]*127);
kn->SetKnobValue( 8*Exemplyar+6,Programms[prognum][28]*127);

knsm->SetKnobSmValue( 8*Exemplyar  ,Programms[prognum][31]);
knsm->SetKnobSmValue( 8*Exemplyar+1,Programms[prognum][32]);
knsm->SetKnobSmValue( 8*Exemplyar+2,Programms[prognum][33]);
knsm->SetKnobSmValue( 8*Exemplyar+3,Programms[prognum][34]);
knsm->SetKnobSmValue( 8*Exemplyar+4,Programms[prognum][35]);
knsm->SetKnobSmValue( 8*Exemplyar+5,Programms[prognum][36]);
}
//------------------------------------------------------------------///called from AGain
void onLoadReadWavs(LPSTR flnm, int file_order, int exemplyar, int tabletype) 
{
char nak[512];
strcpy(nak,((Engine*) GEFFECT[exemplyar] )->GalactixDir);
if ( strncmp( &nak[strlen(nak)-1], "\\", 1 ) )
           (void) strcat( nak,"\\" );
strcat(nak,flnm);
strcat(nak,".wav");

///MessageBox(0,nak,"Gonna open:",0);
if (tabletype==1) mnl->readWavFile(nak, file_order, exemplyar);
else mnl->readWavFile2Osc(nak, file_order, exemplyar);
}
//----------------------------------------------------------------------------------------

/*static WIN32_FIND_DATA w32f[32];
///
bool checkCustomEnvelopes(LPSTR indir,int exemplyar)
{
	   char temp[512];
	   strcpy(temp,indir);
	   if ( strncmp( &temp[strlen(temp)-1], "\\", 1 ) )
           (void) strcat( temp, "\\" );
             
	       strcat( temp, "Envelopes");
		  
	        ///MessageBox(0,temp,"gona chk",0);

             char szStr[ 64 ];
			 SetCurrentDirectory(temp);/// "C:/");
             HANDLE fF = FindFirstFile("*.wav",&w32f[0]);
			 if (fF==INVALID_HANDLE_VALUE) 
			 {
			 MessageBox(0,"No envelope files are found. OK?",indir,0); /// no txt files found				 
			 } else {
             /// GetCurrentDirectory( MAX_PATH, DirNamePresets );
             ///MessageBox(0,DirName,"Get it!!!",0);
             wsprintf( szStr, w32f[0].cFileName, 1 );// 
			 int katems=0;
             if (TRUE==readWavFile(w32f[0].cFileName,0))
			 {
             ((Engine*) GEFFECT[exemplyar] )->wavdata_ptr[0]=wavdata[0];

			 int ll=strlen(szStr);
             memset((char*)&szStr[ll-4],0,4*sizeof(char));/// remove ".zxc"
             katems=1;	
			 
			 mnl->AddMenuListItem(1,szStr); ///tabletype =1 //envelope
			 }		     
			 ///wavdata[0][5]=0.f;

			 //kitems =1;
             while ((FindNextFile(fF,&w32f[katems])!=0)&&(katems<16))///
	         {
             wsprintf( szStr, w32f[katems].cFileName, 1);////// remove ".zxc"
			 if (TRUE==readWavFile(w32f[katems].cFileName,katems))
			 {

			 ((Engine*) GEFFECT[exemplyar])->wavdata_ptr[katems]=wavdata[katems];

             int ll=strlen(szStr);
			 memset((char*)&szStr[ll-4],0,4*sizeof(char));
             mnl->AddMenuListItem(1,szStr); ///tabletype =1 //envelope         
			 ++katems;
			 }
			 }
             }///end else
return TRUE;
}*/
//----------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------
/*bool checkCustomOscillators(LPSTR indir,int exemplyar)
{
	   char temp[512];
	   strcpy(temp,indir);
	   if ( strncmp( &temp[strlen(temp)-1], "\\", 1 ) )
           (void) strcat( temp, "\\" );

        strcat( temp, "Oscillators");

	 ///MessageBox(0,temp,"gona chk",0);

             char szStr[ 64 ];
			 SetCurrentDirectory(temp);/// "C:/");
             HANDLE fF = FindFirstFile("*.wav",&w32f[0]);
			 if (fF==INVALID_HANDLE_VALUE) 
			 {
			 MessageBox(0,"No envelope files are found. OK?",indir,0); /// no txt files found				 
			 } else {
             /// GetCurrentDirectory( MAX_PATH, DirNamePresets );
             ///MessageBox(0,DirName,"Get it!!!",0);
             wsprintf( szStr, w32f[0].cFileName, 1 );// 
			 int katems=0;
             if (TRUE==readWavFile2Osc(w32f[0].cFileName,0,exemplyar))
			 {
			 int ll=strlen(szStr);
             memset((char*)&szStr[ll-4],0,4*sizeof(char));/// remove ".zxc"
             katems=1;				 
			 mnl->AddMenuListItem(0,szStr);/// tabletype 0 osc
			 }		     
			 ///wavdata[0][5]=0.f;

			 //kitems =1;
             while ((FindNextFile(fF,&w32f[katems])!=0)&&(katems<16))///
	         {
             wsprintf( szStr, w32f[katems].cFileName, 1);////// remove ".zxc"
			 if (TRUE==readWavFile2Osc(w32f[katems].cFileName,katems,exemplyar))
			 {
             int ll=strlen(szStr);
			 memset((char*)&szStr[ll-4],0,4*sizeof(char));
             mnl->AddMenuListItem(0,szStr);/// tabletype 0 osc        
			 ++katems;
			 }
			 }
             }///end else
return TRUE;
}*/
//----------------------------------------------------------------------------------------