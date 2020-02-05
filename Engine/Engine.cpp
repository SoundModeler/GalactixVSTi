
#include "..\Exe\CompileType.h"
#include "Engine.hpp"
#include "..\Engine\fasttrig.h"
#include "..\Engine\pink.h"

//extern void Starta();
//extern float Enda ();
//------------------------------------
void *GEFFECT[32];
static long numInitialized=0;
extern bool checkCustomEnvelopes  (LPSTR indir, int numinst);
extern bool checkCustomOscillators(LPSTR indir, int numinst);
//-----------------------------------------------------------------------------------------
Engine::Engine()
{
	////MessageBox(0,"Engine::Engine()","yuyg",0);
    
    cut=127;
	cut0=1.f;
	//isFXOff=1;
	silenceCount= 400000;
    reverb_decay_smpls=150000;///(long) (decay*300000.f);
	Q=1.f;
	long  e;
	for (long  g=0;g<128;++g)
	{
		phase[0][g]=0;
		phase[1][g]=0;
		phase[2][g]=0;
		phase[3][g]=0;
		phase[4][g]=0;
		phase[5][g]=0;
        ispress[g]=0;
		GalactixDir[g]=0;
        GalactixDir[g+128]=0;
		GalactixDir[g+256]=0;
		GalactixDir[g+384]=0;
	}
	for (int d=0;d<12;++d) envelope[d]=(float*) malloc(MAXWAVEFILELENGH_BYTES);

	loop_start=32768;
	loop_end=65536;
	loop_start_filter=32768;
    loop_end_filter=65536;

for (e=0;e<MAXPOLY;++e)
{
nton[e]=0;  
velo[e]=0;  
veloprev[e]=0;  
memset(&index[e],0,8*sizeof(long)); 
memset(&startrel[e],0,8*sizeof(long));
real_index[e]=0;  
rundx_rel[e]=0;  
isreleased[e]=0;  
Delta[e]=0;  
tonereleased[e]=0;  
relgone[e]=0;  
real_j_rel[e]=real_j[e]=0;
real_jp_rel[e]=real_jp[e]=0;
}
	srate_type=0;///default srate
	RELEASE_lng=RELEASE_2_lng= 600;  
	RELEASE_flt=RELEASE_2_flt= 0.01f;  
	ATTACK_lng=ATTACK_2_lng= 100;  
	ATTACK_flt=ATTACK_2_flt= 0.01f;  
    for (e=0;e<NUM_OSC_TYPES;++e) curent_osc_type[e]=0;
	curProgram=0;
    SetTunesValues(64,64,64,64,64,64);
    normvol_desired=normvol=0.f;
	chorus_desired=chorus=0.f;
    samplesToNextCheck=samplesCheck;///40; 
	//samplesCheck=40;
//--------------
numInst=numInitialized;///to AGain
GEFFECT[numInst]=this;//to global
++numInitialized; //to global
//--------------
	initProcess ();
	initReverb();
    initTables();
	
#ifdef EXE_COMPILE
	initDefProg();
#endif
     findLocation(GalactixDir);
     //checkCustomEnvelopes(GalactixDir,numInst);///envelopes
	 //checkCustomOscillators(GalactixDir,numInst);///Oscillators
///	
///
}
//-----------------------------------------------------------------------------------------
#ifndef EXE_COMPILE
//-----------------------------------------------------------------------------------------
////-----------------------------------------------------------------------------------------
bool Engine::gimeEditor(Editor *ed)
{
//--------------
if (ed)  ed ->SetExemplyar(numInst);/// to Editor
//--------------
	edt=ed; 
	return true;
}
#endif
//-----------------------------------------------------------------------------------------
void Engine::findLocation(char *outdir)
{
#ifdef VST_COMPILE
HMODULE hg =GetModuleHandle("GalactiX.dll");
#endif

#ifdef EXE_COMPILE
HMODULE hg =GetModuleHandle("CPP.exe");
#endif

if ((hg==INVALID_HANDLE_VALUE)||(hg==NULL) ) {
  fDirWalk("C:\\");
}
else 
{
char buk[512];
GetModuleFileName(hg,buk,512);
char vy='\\';

long dh=strlen(buk);
long d=dh;
while ((buk[d]!=vy)&&(d>0)) --d;
////szStr = strrchr(ofn2.lpstrFile,(int)vy)+1;//short file name RIGHT WAY
memset(&buk[d],0,dh-d);
strcpy(GalactixDir,buk);
}

///MessageBox(0,GalactixDir,"FOUND !!!!",0);
}
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
bool Engine::checkDir()   ////check current director & ask to insert
{
 WIN32_FIND_DATA WFD;            
#ifdef EXE_COMPILE
             HANDLE fF = FindFirstFile("CPP.exe",&WFD);
#endif
#ifdef VST_COMPILE
             HANDLE fF = FindFirstFile("GalactiX.dll",&WFD);
#endif
			 if (fF==INVALID_HANDLE_VALUE) return FALSE; /// no txt files found
             GetCurrentDirectory( MAX_PATH, GalactixDir);			 
//
			 return TRUE;
}
//-----------------------------------------------------------------------------------------
void Engine::fDirWalk(char *_current)
{
    HANDLE          Hnd;
    WIN32_FIND_DATA WFD;
    static int _dlevel = 0;
    if (FALSE==SetCurrentDirectory( _current )) return  ;
    if (TRUE==checkDir())  return ;		 
    Hnd = FindFirstFile( "*.*", &WFD );
    while ( FindNextFile( Hnd, &WFD ) )
    {
      if (( WFD.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) &&
           ( strcmp(WFD.cFileName, "..") && strcmp(WFD.cFileName, ".") ))
      {
         GetCurrentDirectory( MAX_PATH, DirName );
         if ( strncmp( &DirName[strlen(DirName)-1], "\\", 1 ) )
           (void) strcat( DirName, "\\" );
           (void) strcat( DirName, WFD.cFileName );
         _dlevel++;
         fDirWalk( DirName );
         SetCurrentDirectory( ".." );
         _dlevel--;
      }
    } 
   (void) FindClose( Hnd );
   return ;
}
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
void Engine::initProcess ()
{
/////DLY
//dlysmpls=10050;
//dlyval=0.6f;
/////CHORUS INIT 
l=0;
long k;
for (k=0;k<CHORUSLINE;++k) 
{
  membmory[k]=0.f;
  chorus_tbl[k]=45*sinf(2*M_PI*k/32768)+264;//  
  chorus_tbl2[k]=66*sinf(2*M_PI*(32768-k)/32768)+100;//  
}   
for (k=0;k<CHORUSLINE;++k) 
{
	  float oet=k-chorus_tbl[k];///left
	  float oet2=k-chorus_tbl2[k];///right
        if (oet<0) oet+=CHORUSLINE;
        if (oet2<0) oet2+=CHORUSLINE;
		/////linear long erpolation	
  ol[k]=(long)(oet-0.5);
  ol2[k]=(long)(oet2-0.5);
  fa[k]=oet - (float)ol[k] ;
  fa2[k]=oet2 - (float)ol2[k] ;
  olz[k]=(ol[k]+1)&CHORUS_MSK;
  olz2[k]=(ol2[k]+1)&CHORUS_MSK;

}

///------------- FILTER  1115,	1282  1138,	1305
 /*
	borf1[0]=borf1[1]=borf1[2]=borf1[3]=0.f;
	borf2[0]=borf2[1]=borf2[2]=borf2[3]=0.f;

  float csf    = cosf(M_PI*6000./44100.);
  float alphaf = sinf(M_PI*6000./44100.)*0.5;
 

///LOW PASS FILTER
 af2=(1 - csf)/(1 + alphaf);//b1 
 af1=0.5*af2;//b0
 af3=af1;
 af4=-2*csf/(1 + alphaf);
 af5=(1 - alphaf)/(1 + alphaf);
 */
 
 //--------------

//-------------- RBJ FILTER START
for (long  p=0;p<16;++p)
{
	memset(&bo[p],0,32);
	memset(&borel[p],0,32);
}
//-------------- RBJ FILTER-2 (KEY FOLLOW) START
for (long  n=0;n<128;++n)////note
{
for (long  p=0;p<128;++p)//cut value
{ /////tone_fr[n] =440*POWER(2;(T2-69)/12)/22050 * 2 ^ x =1

  float cs    = cosf(M_PI*tone_fr[n] * powf(2.f ,tone_log_fr[n]*p ));
  float alpha = sinf(M_PI*tone_fr[n] * powf(2.f ,tone_log_fr[n]*p  ))/(2*Q);
  pe2[n][p]=(1 - cs)/(1 + alpha);//b1
  pe1[n][p]=0.5*pe2[n][p];//b0 
  pe3[n][p]=pe1[n][p];
  pe4[n][p]=-2*cs/(1 + alpha);
  pe5[n][p]= (1 - alpha)/(1 + alpha);
}
}
setVeloSens(0,0);
setVeloSens(0,1);
    
}

//-----------------------------------------------------------------------------------------
Engine::~Engine()
{
	// nothing to do here
}
//-----------------------------------------------------------------------------------------
void Engine::midiOn(long  note)
{            			    
			    long  jj=1;
		        if (ispress[note]!=0) jj=ispress[note];					
                else while((velo[jj]!=0)&&(jj<MAXPOLY)) ++jj;//define which note was pressed
                ispress[note]=jj;////remember note's line

				nton[jj]=note;
	            velo[jj]=127;
                RELEASE_lng = RELEASE_2_lng;
                RELEASE_flt = RELEASE_2_flt;
				ATTACK_lng = ATTACK_2_lng;
                ATTACK_flt = ATTACK_2_flt;

				index[jj][0]=phase[0][note];/////
				index[jj][1]=phase[1][note];/////
                index[jj][2]=phase[2][note];/////
				index[jj][3]=phase[3][note];/////
				index[jj][4]=phase[4][note];/////
				index[jj][5]=phase[5][note];/////
				
				real_index[jj]=0;	
				real_j[jj]=0;
				real_jp[jj]=0;
				//j_loop[jj]=0;
                //jp_loop[jj]=0;
}
//-----------------------------------------------------------------------------------------
void Engine::midiOff(long  note)
{
			long jj=ispress[note];//define note play line
			ispress[note]=0;
            long kk=1;
            while((isreleased[kk]!=0)&&(kk<MAXPOLY)) ++kk;//define which note was released
           
                rundx_rel[kk]=real_index[jj];
			    real_j_rel[kk]=real_j[jj];
				real_jp_rel[kk]=real_jp[jj];
		
				veloprev[kk]=velo[jj];	
				isreleased[kk]=1;
			    tonereleased[kk]=note;
			    relgone[kk]=0;
			    velo[jj]=0;	

			    startrel[kk][0]=index[jj][0];///TRANSLATE LOOP POSITION
                startrel[kk][1]=index[jj][1];//////
			    startrel[kk][2]=index[jj][2];
 			    startrel[kk][3]=index[jj][3];
				startrel[kk][4]=index[jj][4]; 
                startrel[kk][5]=index[jj][5]; 
 				
 
				  borel[kk][0]=bo[jj][0]; 
				  borel[kk][1]=bo[jj][1]; 
				  borel[kk][2]=bo[jj][2]; 
				  borel[kk][3]=bo[jj][3];
				  borel[kk][4]=bo[jj][4]; 
				  borel[kk][5]=bo[jj][5]; 
				  borel[kk][6]=bo[jj][6]; 
				  borel[kk][7]=bo[jj][7];
 
                  bo[jj][0]=0.f; 
				  bo[jj][1]=0.f; 
				  bo[jj][2]=0.f; 
				  bo[jj][3]=0.f; 
                  bo[jj][4]=0.f; 
				  bo[jj][5]=0.f; 
				  bo[jj][6]=0.f; 
				  bo[jj][7]=0.f;  
}
//-----------------------------------------------------------------------------------------
void Engine::buildFilterEnvelope(long  type)
{
long a=1; 
long r=0;
ProgrammsContainer[curProgram][18]=(float)type;//
/////////////////////////// 
     if (type>8)///e.g. MAXENVELOPESTYPES
	 {
     int wavnum=type-9;
	 if (wavdata_ptr[wavnum]==NULL) 
	 { 
	 MessageBox(0,"Empty wavedata array","Error",0);
	 type=1;
	 goto errflt;
	 }
	 loop_start_filter=lstart[wavnum];
	 loop_end_filter=lend[wavnum];

	 if (wavnum<16)
        for (r=0;r<loop_end_filter;++r) envelope[a][r]=fabsf(wavdata_ptr[wavnum][r]) ;

	 }////if type>8 end

	 else {
errflt:;
	   loop_start_filter=32768;///default
       loop_end_filter=32768*2;
	 
	 switch (type)
	 {
	 case 0://///////////////////////// EXPONENT     
	 {
       for (r=0;r<loop_start_filter;++r) envelope[a][r]=exp(-r/20000.) ;
       for (r=loop_start_filter;r<loop_end_filter;++r) envelope[a][r]=envelope[a][loop_start_filter-1] ;
	 }   
	 break;///////////////////
     
	 case 1://///////////////////////// SLOW ATTACK     
	 {
       for (r=0;r<150;++r) envelope[a][r]=150.f/(float)loop_start_filter ;
       for (r=150;r<loop_start_filter;++r) envelope[a][r]=(float)r/(float)loop_start_filter ;
       for (r=loop_start_filter;r<loop_end_filter;++r) envelope[a][r]=envelope[a][loop_start_filter-1] ;
	 }  
	 break;///////////////////
     
	 case 2://///////////////////////// PLUCK	 
	 {
       for (r=0;r<loop_start_filter;++r) envelope[a][r]=0.96*exp(-r/5000.) +0.03f;
       for (r=loop_start_filter;r<loop_end_filter;++r) envelope[a][r]=envelope[a][loop_start_filter-1] ;
	 }
	 break;///////////////////

     
	 case 3://///////////////////////// PIANO-LIKE	 
	 {
       for (r=0;r<loop_start_filter;++r) envelope[a][r]=4.4*(0.191561839 +(-3.4761E-05 *r) +\
		 (1.37683E-07 *r*sqrt(r))+(-1.5861E-10*r*r  )+(0.001846424 *sqrt(r)) )   ;
       for (r=loop_start_filter;r<loop_end_filter;++r) envelope[a][r]=envelope[a][loop_start_filter-1] ;
	 }  
	 break;///////////////////
     
	 case 4://///////////////////////// FLAT	 
	 {
       for (r=0;r<loop_end_filter;++r) envelope[a][r]=1.f ;	  	
       }  
       break;///////////////////
     
	 case 5://///////////////////////// CHICK	 
	 {
       for (r=0;r<loop_start_filter;++r) 
             {
             if (r<16000) envelope[a][r]= 1.f;
	       else envelope[a][r]=  ((float)loop_start_filter-r+5000.)/((float)loop_start_filter-16000.+5000.);
             }
       for (r=loop_start_filter;r<loop_end_filter;++r) envelope[a][r]=envelope[a][loop_start_filter-1] ;
	 }
	 break;///////////////////
	 
	 case 6://///////////////////////// FLAT + LFO	 
	 {
       for (r=0;r<loop_start_filter;++r) envelope[a][r]=0.80f+0.16f*sinf(TWOPI*r/(float)loop_start_filter)*r/ (float)loop_start_filter;
       for ( r=loop_start_filter;r<loop_end_filter;++r) envelope[a][r]=envelope[a][loop_start_filter-1] ;   
	 }
	 break;///////////////////
	 
	 case 7://///////////////////////// Attack+Dcy	 
	 {     
       #define FASTDECAY 15500
       #define SHOULDER 300.f
     for (r=0;r<loop_start_filter;++r)
     {
     if (r<FASTDECAY) envelope[a][r]= 1.f-r/(FASTDECAY+SHOULDER);
     else  envelope[a][r]= (1.f-FASTDECAY/(FASTDECAY+SHOULDER))+\
		              (r-FASTDECAY)/192768.f;// 
     }
     for (r=loop_start;r<loop_end_filter;++r) envelope[a][r]=envelope[a][loop_start_filter-1] ;     
     #undef FASTDECAY 
     #undef SHOULDER 	 
	 }
	 break;///////////////////

	 
	 case 8://///////////////////////// Linear Dwn 
	 {
     #define FASTDECAY 19500
     #define SHOULDER 200.f
     for (r=0;r<loop_start_filter;++r)
     {
       if (r<FASTDECAY) envelope[a][r]= 1.f-r/(FASTDECAY+SHOULDER);
       else  envelope[a][r]= (1.f-FASTDECAY/(FASTDECAY+SHOULDER));// 
     }
     for (r=loop_start_filter;r<loop_end_filter;++r) envelope[a][r]=envelope[a][loop_start_filter-1] ;     
     #undef FASTDECAY 
     #undef SHOULDER 
	 }///////////////////
	 break;

}////switch end
}/////else end

/////////////// TRANSLATE FILTER ENVELOPE TO COEFFICIENTS
 
  curent_filt_env_type=type;
  float cs, alpha;
  float cs1, alpha1;///FOR LOW VELO CUT


  for (long t=0;t<loop_end_filter;++t)
  {
  cs    = cos(M_PI*envelope[1][t]*0.9);
  alpha = sin(M_PI*envelope[1][t]*0.9)/(2.*Q);
  cs1    = cos(M_PI*envelope[1][t]*0.03);
  alpha1 = sin(M_PI*envelope[1][t]*0.03)/(2.*Q);

  ///high cut
  envelope[3][t]=(1. - cs)/(1. + alpha);//b1
  envelope[2][t]=0.5*envelope[3][t];//b0 
  envelope[4][t]=envelope[2][t];
  envelope[5][t]=-2.*cs/(1 + alpha);
  envelope[6][t]= (1. - alpha)/(1. + alpha);
  ///low cut
  envelope[7][t]=(1. - cs1)/(1. + alpha1);//b1
  envelope[8][t]=0.5*envelope[7][t];//b0 
  envelope[9][t]=envelope[8][t];
  envelope[10][t]=-2.*cs1/(1 + alpha1);
  envelope[11][t]= (1. - alpha1)/(1. + alpha1);

  /////
 
  }/////////////////////

}/////
//-----------------------------------------------------------------------------------------
void Engine::buildEnvelope(long  type,long  whichone)
{
     long a=0;
     long r=0;
	 if (whichone==0) buildFilterEnvelope(type);//filter 
     else {      ///gain
    
     ProgrammsContainer[curProgram][19]=(float)type;//gain
     /////////////////////////// 
     if (type>8)///e.g. WAVFILE
	 {
     int wavnum=type-9;
	 if (wavdata_ptr[wavnum]==NULL) ///wav not loaded
	 { 
	 MessageBox(0,"Empty wavedata array","Error",0);
	 type=1;
	 goto errgn;
	 }
	 loop_start=lstart[wavnum];
	 loop_end=lend[wavnum];
	 if (wavnum<16)
        for (r=0;r<loop_end;++r) envelope[a][r]=fabsf(wavdata_ptr[wavnum][r]) ;

	 }////if type>8 end

	 else {
       errgn:;
	  loop_start=32768;///default
      loop_end  =65536;

	 switch (type)
	 {
	 case 0://///////////////////////// EXPONENT     
	 {
       for (r=0;r<loop_start;++r) envelope[a][r]=exp(-r/20000.) ;
       for (r=loop_start;r<loop_end;++r) envelope[a][r]=envelope[a][loop_start-1] ;
	 }   
	 break;///////////////////
     
	 case 1://///////////////////////// SLOW ATTACK     
	 {
       for (r=0;r<150;++r) envelope[a][r]=150.f/(float)loop_start ;
       for (r=150;r<loop_start;++r) envelope[a][r]=(float)r/(float)loop_start ;
       for (r=loop_start;r<loop_end;++r) envelope[a][r]=envelope[a][loop_start-1] ;
	 }  
	 break;///////////////////
     
	 case 2://///////////////////////// PLUCK	 
	 {
       for (r=0;r<loop_start;++r) envelope[a][r]=0.96*exp(-r/5000.) +0.03f;
       for (r=loop_start;r<loop_end;++r) envelope[a][r]=envelope[a][loop_start-1] ;
	 }
	 break;///////////////////

     
	 case 3://///////////////////////// PIANO-LIKE	 
	 {
       for (r=0;r<loop_start;++r) envelope[a][r]=4.4*(0.191561839 +(-3.4761E-05 *r) +\
		 (1.37683E-07 *r*sqrt(r))+(-1.5861E-10*r*r  )+(0.001846424 *sqrt(r)) )   ;
       for (r=loop_start;r<loop_end;++r) envelope[a][r]=envelope[a][loop_start-1] ;
	 }  
	 break;///////////////////
     
	 case 4://///////////////////////// FLAT	 
	 {
       for (r=0;r<loop_end;++r) envelope[a][r]=1.f ;	  	
       }  
       break;///////////////////
     
	 case 5://///////////////////////// CHICK	 
	 {
       for (r=0;r<loop_start;++r) 
             {
             if (r<16000) envelope[a][r]= 1.f;
	       else envelope[a][r]=  ((float)loop_start-r+5000.)/((float)loop_start-16000.+5000.);
             }
       for (r=loop_start;r<loop_end;++r) envelope[a][r]=envelope[a][loop_start-1] ;
	 }
	 break;///////////////////
	 
	 case 6://///////////////////////// FLAT + LFO	 
	 {
       for (r=0;r<loop_start;++r) envelope[a][r]=0.80f+0.16f*sinf(TWOPI*r/(float)loop_start)*r/ (float)loop_start;
       for ( r=loop_start;r<loop_end;++r) envelope[a][r]=envelope[a][loop_start-1] ;   
	 }
	 break;///////////////////
	 
	 case 7://///////////////////////// Attack+Dcy	 
	 {     
       #define FASTDECAY 15500
       #define SHOULDER 300.f
     for (r=0;r<loop_start;++r)
     {
     if (r<FASTDECAY) envelope[a][r]= 1.f-r/(FASTDECAY+SHOULDER);
     else  envelope[a][r]= (1.f-FASTDECAY/(FASTDECAY+SHOULDER))+\
		              (r-FASTDECAY)/192768.f;// 
     }
     for (r=loop_start;r<loop_end;++r) envelope[a][r]=envelope[a][loop_start-1] ;     
     #undef FASTDECAY 
     #undef SHOULDER 	 
	 }
	 break;///////////////////

	 
	 case 8://///////////////////////// Linear Dwn 
	 {
     #define FASTDECAY 19500
     #define SHOULDER 200.f
     for (r=0;r<loop_start;++r)
     {
       if (r<FASTDECAY) envelope[a][r]= 1.f-r/(FASTDECAY+SHOULDER);
       else  envelope[a][r]= (1.f-FASTDECAY/(FASTDECAY+SHOULDER));// 
     }
     for (r=loop_start;r<loop_end;++r) envelope[a][r]=envelope[a][loop_start-1] ;     
     #undef FASTDECAY 
     #undef SHOULDER 
	 }///////////////////
	 break;

}////switch end
}/////else end

  }///////////////////// end else
}
///-----------------------------------------------------------------------------------------
/*
envelope[0][r]- gain envelope
envelope[1][r]- filter envelope (not used in process)
envelope[2][r]-envelope[6][r]- filter coeff high cut
envelope[7][r]-envelope[11][r] filter coeff low cut
*/
///-----------------------------------------------------------------------------------------

void Engine::buildAllOsc(long  type1,long  type2,long  type3,
						long  type4,long  type5,long  type6)
{
buildOsc(type1,0);
buildOsc(type2,1);
buildOsc(type3,2);
buildOsc(type4,3);
buildOsc(type5,4);
buildOsc(type6,5);
}
///-----------------------------------------------------------------------------------------
void Engine::buildOsc(long  type,long  oscnum)
{
	curent_osc_type[oscnum]=type;
    ProgrammsContainer[curProgram][oscnum]=(float)type;
    ////memcpy(out[oscnum],prebuild_tbl[type],TABLESIZE*sizeof(float));
}
//-----------------------------------------------------------------------------------------
void Engine::SetTuneValue(long  tune,long  oscnum)
{
TUNE[oscnum]=tune;
for (long r=24;r<108;++r)  
    STEPS[oscnum][r]=nstep[srate_type][r] *(1.+MINSTEPTUNE*(tune-64));
    ProgrammsContainer[curProgram][oscnum+6]=(float)tune;
}
//-----------------------------------------------------------------------------------------
void Engine::SetSampleRate(long srate)
{
	switch(srate) {
	case 44100: srate_type=0; break;
	case 48000: srate_type=1; break;
		/// add more types
	}
}
//-----------------------------------------------------------------------------------------
void Engine::SetTunesValues(long  tune1,long  tune2,long  tune3,
						   long  tune4,long  tune5,long  tune6)
{
TUNE[0]=tune1;
TUNE[1]=tune2;
TUNE[2]=tune3;
TUNE[3]=tune4;
TUNE[4]=tune5;
TUNE[5]=tune6;
for (long  r=24;r<108;++r) ///64 --- no tune
{	
   STEPS[0][r]=nstep[srate_type][r] *(1.+MINSTEPTUNE*(tune1-64));
   STEPS[1][r]=nstep[srate_type][r] *(1.+MINSTEPTUNE*(tune2-64));
   STEPS[2][r]=nstep[srate_type][r] *(1.+MINSTEPTUNE*(tune3-64));
   STEPS[3][r]=nstep[srate_type][r] *(1.+MINSTEPTUNE*(tune4-64));
   STEPS[4][r]=nstep[srate_type][r] *(1.+MINSTEPTUNE*(tune5-64));
   STEPS[5][r]=nstep[srate_type][r] *(1.+MINSTEPTUNE*(tune6-64));
}
ProgrammsContainer[curProgram][0+6]=(float)tune1;
ProgrammsContainer[curProgram][1+6]=(float)tune2;
ProgrammsContainer[curProgram][2+6]=(float)tune3;
ProgrammsContainer[curProgram][3+6]=(float)tune4;
ProgrammsContainer[curProgram][4+6]=(float)tune5;
ProgrammsContainer[curProgram][5+6]=(float)tune6;
}
//-----------------------------------------------------------------------------------------
void Engine::setWheel(long  wheeltune)
{
for (long  r=24;r<108;++r) ///64 --- no tune
{	
   STEPS[0][r]=nstep[srate_type][r] *(1.+MINSTEPTUNE*(TUNE[0]+wheeltune-128));
   STEPS[1][r]=nstep[srate_type][r] *(1.+MINSTEPTUNE*(TUNE[1]+wheeltune-128));
   STEPS[2][r]=nstep[srate_type][r] *(1.+MINSTEPTUNE*(TUNE[2]+wheeltune-128));
   STEPS[3][r]=nstep[srate_type][r] *(1.+MINSTEPTUNE*(TUNE[3]+wheeltune-128));
   STEPS[4][r]=nstep[srate_type][r] *(1.+MINSTEPTUNE*(TUNE[4]+wheeltune-128));
   STEPS[5][r]=nstep[srate_type][r] *(1.+MINSTEPTUNE*(TUNE[5]+wheeltune-128));
}

}
//-----------------------------------------------------------------------------------------
void Engine::setGain(long  value,long  oscnum)
{
  GAINS[oscnum]=0.00166f*value;/// e.g. 0.01/6
  ProgrammsContainer[curProgram][oscnum+12]=(float)value;
} 
//-----------------------------------------------------------------------------------------
void Engine::SetVolume(long  value)
{
ProgrammsContainer[curProgram][30]=(float)value;
normvol_desired=value<<3;///step scaled to 0:889
}        
//-----------------------------------------------------------------------------------------
void Engine::SetGainsValues( long  gain1,long  gain2,long  gain3,
						    long  gain4,long  gain5,long  gain6,long  gain7)
{
 
  setGain(gain1,0);
  setGain(gain2,1);
  setGain(gain3,2);
  setGain(gain4,3);
  setGain(gain5,4);
  setGain(gain6,5);
  SetVolume(gain7);
  
}
//-----------------------------------------------------------------------------------------
void Engine::setCut(long  value )
{
cut_desired= value; ///0-127
ProgrammsContainer[curProgram][26]=scaler127*(float)value;
}
//-----------------------------------------------------------------------------------------
void Engine::setCut0(long  value )
{
cut0= scaler127*value;///cut0: 0-1
ProgrammsContainer[curProgram][22]=scaler127*(float)value;
}
//-----------------------------------------------------------------------------------------
void Engine::setPhase(long  val, long  oscnum)
{
	for (long  g=24;g<108;++g) phase[oscnum][g]=TABLESIZE/127*val;
    ProgrammsContainer[curProgram][oscnum+31]=(float)val;
}
//-----------------------------------------------------------------------------------------
void Engine::setVeloSens(long  value,long  which )
{
	if (value<10&&value>0)
	{
	switch (which)
	{
	case 0: 
		{
		for (long  g=0;g<128;++g) filterScaler[g]=veloArrs[value][g];
        ProgrammsContainer[curProgram][20]=(float)value;
		break;
		}	
    case 1: 
		{
		for (long  g=0;g<128;++g) midiScaler[g]=veloArrs[value][g]*9.842519685e-4; 
		ProgrammsContainer[curProgram][21]=(float)value;
		break;
		}	
	}
	}
}
//-----------------------------------------------------------------------------------------
void Engine::setReso(long  value )
{
Q=1.f+4*scaler127*value;
buildEnvelope(curent_filt_env_type,0);
ProgrammsContainer[curProgram][23]=scaler127*(float)value;
}
//-----------------------------------------------------------------------------------------
void Engine::setRelease(long  value )
{
RELEASE_2_lng=100+(30000.f*scaler127*value);
RELEASE_2_flt=1.f/RELEASE_2_lng;
ProgrammsContainer[curProgram][24]=scaler127*(float)value;
}
//-----------------------------------------------------------------------------------------
void Engine::setAttack(long  value )
{
ATTACK_2_lng=100+(3000.f*scaler127*value);
ATTACK_2_flt=1.f/ATTACK_2_lng;
ProgrammsContainer[curProgram][25]=scaler127*(float)value;
}
//-----------------------------------------------------------------------------------------
void Engine::setReverbWet(float value)
{
/*	float width=0.5f;
	wet =  value;//*0.5f;
	wet1 = wet*(width/2 + 0.5f);
	wet2 = wet*((1-width)/2);

		decay=0.5f;*/
		mix=value;
ProgrammsContainer[curProgram][29]=(float)value;
}
//-----------------------------------------------------------------------------------------
void Engine::setReverbSize(float value)
{
    decay=value*0.8;
	reverb_decay_smpls=(long) (decay*300000.f);
	//Roomsize=value*0.28f+0.7f;
ProgrammsContainer[curProgram][28]=(float)value;	 
}
//-----------------------------------------------------------------------------------------
void Engine::setChorus(long value)
{
ProgrammsContainer[curProgram][27]=scaler127*(float)value;	
chorus_desired=value<<3;///step scaled to 0:889
 
}
//-----------------------------------------------------------------------------------------
void Engine::initReverb()
{
 //------------------------------------///REVERB
 
   	Roomsize =0;
    wet=0;
	wet1=0;
	wet2=0;
	///result=0;
	//------------------------------------
	
	//cleanup of used resources
/*
	if(predelayline!=0)
	{
		delete predelayline;
		predelayline=0;
	}

	if(inputdiffusion1aline!=0)
	{
		delete inputdiffusion1aline;
		inputdiffusion1aline=0;
	}
	if(inputdiffusion1bline!=0)
	{
		delete inputdiffusion1bline;
		inputdiffusion1bline=0;
	}
	if(inputdiffusion2aline!=0)
	{
		delete inputdiffusion2aline;
		inputdiffusion2aline=0;
	}
	if(inputdiffusion2bline!=0)
	{
		delete inputdiffusion2bline;
		inputdiffusion2bline=0;
	}
	if(decaydiffusion1aline!=0)
	{
		delete decaydiffusion1aline;
		decaydiffusion1aline=0;
	}
	if(decaydiffusion1bline!=0)
	{
		delete decaydiffusion1bline;
		decaydiffusion1bline=0;
	}
	if(decaydiffusion2aline!=0)
	{
		delete decaydiffusion2aline;
		decaydiffusion2aline=0;
	}
	if(decaydiffusion2bline!=0)
	{
		delete decaydiffusion2bline;
		decaydiffusion2bline=0;
	}
	if(tank1line!=0)
	{
		delete tank1line;
		tank1line=0;
	}
	if(tank2line!=0)
	{
		delete tank2line;
		tank2line=0;
	}
	if(tank3line!=0)
	{
		delete tank3line;
		tank3line=0;
	}
	if(tank4line!=0)
	{
		delete tank4line;
		tank4line=0;
	}  */
	///--------------------------- init reverb main
	long a;
	mix=0.5f; // even dry/wet mix

	///predelaylength=(long )(SPEED*LENGTH_PREDELAY+0.5f); //0 < predelay << inf
	///predelaytap=0;
	/*if(predelaylength!=0)
	{
		predelayline=new float[predelaylength];
		for(a=0;a<predelaylength;a++)
			predelayline[a]=0.0f;
	}*/

	//bandwidth=0.9995f; //This should probably be adjusted to samplerate
					   //How?
	//ibandwidth=1.0f-bandwidth; //Pre-calculation
	bandwidthy1=0;

	//inputdiffusion1coeff=0.750f; //Should be altered to samplerate?

	inputdiffusion1alength=(long )(SPEED*LENGTH_INPUTDIFFUSION1A+0.5f);
	inputdiffusion1atap=0;
	inputdiffusion1aline=new float[inputdiffusion1alength];
	for(a=0;a<inputdiffusion1alength;a++)
		inputdiffusion1aline[a]=0.0f;

	inputdiffusion1blength=(long )(SPEED*LENGTH_INPUTDIFFUSION1B+0.5f);
	inputdiffusion1btap=0;
	inputdiffusion1bline=new float[inputdiffusion1blength];
	for(a=0;a<inputdiffusion1blength;a++)
		inputdiffusion1bline[a]=0.0f;

	//inputdiffusion2coeff=0.625f; //Should be altered to samplerate?

	inputdiffusion2alength=(long )(SPEED*LENGTH_INPUTDIFFUSION2A+0.5f);
	inputdiffusion2atap=0;
	inputdiffusion2aline=new float[inputdiffusion2alength];
	for(a=0;a<inputdiffusion2alength;a++)
		inputdiffusion2aline[a]=0.0f;

	inputdiffusion2blength=(long )(SPEED*LENGTH_INPUTDIFFUSION2B+0.5f);
	inputdiffusion2btap=0;
	inputdiffusion2bline=new float[inputdiffusion2blength];
	for(a=0;a<inputdiffusion2blength;a++)
		inputdiffusion2bline[a]=0.0f;

	tank1length=(long )(SPEED*LENGTH_TANK1+0.5f);
	tank1tap=0;
	tank1line=new float[tank1length];
	for(a=0;a<tank1length;a++)
		tank1line[a]=0.0f;

	tank2length=(long )(SPEED*LENGTH_TANK2+0.5f);
	tank2tap=0;
	tank2line=new float[tank2length];
	for(a=0;a<tank2length;a++)
		tank2line[a]=0.0f;

	tank3length=(long )(SPEED*LENGTH_TANK3+0.5f);
	tank3tap=0;
	tank3line=new float[tank3length];
	for(a=0;a<tank3length;a++)
		tank3line[a]=0.0f;

	tank4length=(long )(SPEED*LENGTH_TANK4+0.5f);
	tank4tap=0;
	tank4line=new float[tank4length];
	for(a=0;a<tank4length;a++)
		tank4line[a]=0.0f;

	//decaydiffusion1coeff=0.70f;
///681  
	//decaydiffusion1ailength=(long )(SPEED*(LENGTH_DECAYDIFFUSION1A+EXCURSION_DECAYDIFFUSION1A))+1; //fit fractional length delay within long erger samples
	//decaydiffusion1aflength=(float) decaydiffusion1ailength;
	decaydiffusion1acentre=SPEED*LENGTH_DECAYDIFFUSION1A;
	decaydiffusion1arange=SPEED*EXCURSION_DECAYDIFFUSION1A;
	decaydiffusion1amodrate=MODRATE_DECAYDIFFUSION1A*WAVE_SIZE/SPEED;
	decaydiffusion1aline=new float[decaydiffusion1ailength];
	decaydiffusion1amodpos=0.0f;
	decaydiffusion1atap=0;
	for(a=0;a<decaydiffusion1ailength;a++)
		decaydiffusion1aline[a]=0.0f;
///917
	//decaydiffusion1bilength=(long )(SPEED*(LENGTH_DECAYDIFFUSION1B+EXCURSION_DECAYDIFFUSION1B))+1; //fit fractional length delay within long erger samples
	//decaydiffusion1bflength=(float) decaydiffusion1bilength;
	decaydiffusion1bcentre=SPEED*LENGTH_DECAYDIFFUSION1B;
	decaydiffusion1brange=SPEED*EXCURSION_DECAYDIFFUSION1B;
	decaydiffusion1bmodrate=MODRATE_DECAYDIFFUSION1B*WAVE_SIZE/SPEED;
	decaydiffusion1bline=new float[decaydiffusion1bilength];
	decaydiffusion1bmodpos=(float)WAVE_SIZE/4.0f; //out of phase with other modulator
	decaydiffusion1btap=0;
	for(a=0;a<decaydiffusion1bilength;a++)
		decaydiffusion1bline[a]=0.0f;

	//decaydiffusion2coeff=0.50f;
//1800
	//decaydiffusion2alength=(long )(SPEED*LENGTH_DECAYDIFFUSION2A+0.5f);
	decaydiffusion2atap=0;
	decaydiffusion2aline=new float[decaydiffusion2alength];
	decaydiffusion2atap=0;
	for(a=0;a<decaydiffusion2alength;a++)
		decaydiffusion2aline[a]=0.0f;
// 2656
	//decaydiffusion2blength=(long )(SPEED*LENGTH_DECAYDIFFUSION2B+0.5f);
	decaydiffusion2btap=0;
	decaydiffusion2bline=new float[decaydiffusion2blength];
	decaydiffusion2btap=0;
	for(a=0;a<decaydiffusion2blength;a++)
		decaydiffusion2bline[a]=0.0f;

	//damping=0.0005f; //This should probably be adjusted to samplerate
					   //How?
	////idamping=1.0f-damping; //Pre-calculation
	dampingay1=0.0f;
	dampingby1=0.0f;

	decay=0.5f;

	tapyl1=(long )(SPEED*TAP_YL1+0.5f);
	tapyl2=(long )(SPEED*TAP_YL2+0.5f);
	tapyl3=(long )(SPEED*TAP_YL3+0.5f);
	tapyl4=(long )(SPEED*TAP_YL4+0.5f);
	tapyl5=(long )(SPEED*TAP_YL5+0.5f);
	tapyl6=(long )(SPEED*TAP_YL6+0.5f);
	tapyl7=(long )(SPEED*TAP_YL7+0.5f);
	tapyr1=(long )(SPEED*TAP_YR1+0.5f);
	tapyr2=(long )(SPEED*TAP_YR2+0.5f);
	tapyr3=(long )(SPEED*TAP_YR3+0.5f);
	tapyr4=(long )(SPEED*TAP_YR4+0.5f);
	tapyr5=(long )(SPEED*TAP_YR5+0.5f);
	tapyr6=(long )(SPEED*TAP_YR6+0.5f);
	tapyr7=(long )(SPEED*TAP_YR7+0.5f);

	
//    sinel=new long[WAVE_SIZE];
//    sinel2=new long[WAVE_SIZE];
//    sinef=new  float[WAVE_SIZE];
//    sinef2=new float[WAVE_SIZE];

inputdiffusion1alength-=1;
inputdiffusion1atap=inputdiffusion1alength;
inputdiffusion1blength-=1;
inputdiffusion1btap=inputdiffusion1blength;
inputdiffusion2alength-=1;
inputdiffusion2atap=inputdiffusion2alength;
inputdiffusion2blength-=1;
inputdiffusion2btap=inputdiffusion2blength;

/*
#define LENGTH_INPUTDIFFUSION1A		142.0f/SPEED
#define LENGTH_INPUTDIFFUSION1B		107.0f/SPEED
#define LENGTH_INPUTDIFFUSION2A		379.0f/SPEED
#define LENGTH_INPUTDIFFUSION2B		277.0f/SPEED*/
/*
decaydiffusion1ailength-=1;
decaydiffusion1atap=decaydiffusion1ailength;

decaydiffusion1bilength-=1;
decaydiffusion1btap=decaydiffusion1bilength;

decaydiffusion1aflength-=1.f;
decaydiffusion1bflength-=1.f;

decaydiffusion2blength=-1;
decaydiffusion2btap=decaydiffusion2blength;
//tank4length-=1;
//tank4tap=tank4length;
//tank3length-=1;
//tank3tap=tank3length;*/
//tank1length-=1;
//tank1tap=tank1length;
//decaydiffusion2alength-=1;
//decaydiffusion2atap=decaydiffusion2alength;
//tank2length-=1;
//tank2tap=tank2length;

    sinetable=new float[WAVE_SIZE];
	sinetable2=new float[WAVE_SIZE];
	for(a=0;a<WAVE_SIZE;a++)
	{
		sinetable[a]= decaydiffusion1acentre+decaydiffusion1arange*sin((float)a*TWOPI/WAVE_SIZE);
		sinetable2[a]=decaydiffusion1bcentre+decaydiffusion1brange*sin((float)a*TWOPI/WAVE_SIZE);
	
		
		
		/*

		sinetable2[a]=(float)decaydiffusion1brange
			*sin((float)a*TWOPI/WAVE_SIZE)+decaydiffusion1bcentre;
		sinel2[a]=(long) (sinetable2[a]);////tselaya chast'
	 
			sinef2[a]=1.f-fabs(sinetable2[a]-(float) sinel2[a]);///drobnaya chast
			sinel2[a]+=1;
 
///681  ///916

		sinetable[a]=(float) decaydiffusion1arange*
		sin((float)a*TWOPI/WAVE_SIZE)+decaydiffusion1acentre;
		 		
      	sinel[a]=(long) (sinetable[a]);////tselaya chast'
			

		sinef[a]=1.f-fabs(sinetable[a]-(float) sinel[a]);///drobnaya chast
	    sinel[a]+=1;

	  
	   }*/
		   //	else sinef[a]=sinetable[a]-(float) sinel[a];
	}
}
//-----------------------------------------------------------------------------------------
void Engine::initTables()
{
	///Starta();
	float a=0.8;
	float a12=0.4f;
	float N= 500;
	float an=2*powf(a,N+2.f);
    float an12=2*powf(a12,N+2.f);
    float w1= TWOPI/TABLESIZE;
	float a_sqare=a*a;
	float a12_square=a12*a12;

    INIT_FASTSIN(1.0,0);/////main sinus
    INIT_FASTSIN(N,  1);
	INIT_FASTSIN((N+1),  2);
	INIT_FASTSIN(2.0,  3);
	INIT_FASTSIN(3.0,  4);
	INIT_FASTSIN(4.0,  5);
	INIT_FASTSIN(5.0,  6);
	INIT_FASTSIN(6.0,  7);
	INIT_FASTSIN(7.0,  8);
	INIT_FASTSIN(8.0,  9);/////

INIT_FASTSIN(1.99487181460799,  10); 

INIT_FASTSIN(1.94358973206068,  11); 
INIT_FASTSIN(2.02051281777711,  12); 
INIT_FASTSIN(1.98974359111145,  13); 
INIT_FASTSIN(0.487179479363171, 14); 
INIT_FASTSIN(3.01025640888856,  15); 
INIT_FASTSIN(2.00512822349655,  16); 
INIT_FASTSIN(2.48205129397116,  17); 
INIT_FASTSIN(1.50769229714028,  18); 
INIT_FASTSIN(1.97948718222289,  19); 
INIT_FASTSIN(0.497435888251726, 20); 
INIT_FASTSIN(2.47179488508261,  21); 
INIT_FASTSIN(2.96923077333434,  22); 
INIT_FASTSIN(2.01025640888856,  23); 
INIT_FASTSIN(1.90256409650646,  24); 


  INIT_FASTSIN(9.0,  25);
  INIT_FASTSIN(10.0, 26);/////
INIT_FASTSIN(11,  27); 
INIT_FASTSIN(17,  28); 
INIT_FASTSIN(19,  29); 

    INIT_FASTCOS(1.0,0);/////main cos
INIT_FASTCOS(1.97948718222289,1);
INIT_FASTCOS(1.96410254983779,2);
INIT_FASTCOS(2.51282052063683,3);
INIT_FASTCOS(0.492307664755178,4 );
INIT_FASTCOS(1.48717947936317,5);
INIT_FASTCOS(1.94358973206068,6);
INIT_FASTCOS(1.96923077333434,7);
INIT_FASTCOS(2.00512822349655,8);
INIT_FASTCOS(1.95384614094923,9);
INIT_FASTCOS(1.93846154666867,10);
INIT_FASTCOS(1.47692307047462,11);
INIT_FASTCOS(1.98974359111145,12);
INIT_FASTCOS(2.50256411174827,13);
INIT_FASTCOS(1.99487181460799,14);
INIT_FASTCOS(2.0153846323851,15);
INIT_FASTCOS(1.98461540571944,16);

    ////A-vowel
  

 
	INIT_FASTCOS(2.0, 17);
    INIT_FASTCOS(3.0,  18);
	INIT_FASTCOS(4.0, 19);
	INIT_FASTCOS(7.0,  20);
	INIT_FASTCOS(8.0, 21);
    INIT_FASTCOS(11.0,  22);
	INIT_FASTCOS(12.0, 23);
	INIT_FASTCOS(5.0, 24);
    INIT_FASTCOS(6.0, 25);
	INIT_FASTCOS(9.0, 26);

	INIT_FASTCOS(10.0, 27);
	INIT_FASTCOS(15.0, 28);
    INIT_FASTCOS(16.0, 29);
	INIT_FASTCOS(19.0, 30);

    PinkNumber pn;

/*	float maxres[16];
	for (int x=0;x<16;++x) maxres[x]=0.f;
	HFILE hndF2 = _lcreat("to.txt",0);
	int rj = 2573;///next row

#define ch(i) if (fabs(prebuild_tbl[i][r])>maxres[i]) maxres[i]=fabs(prebuild_tbl[i][r])
*/
	for (long r=0;r<TABLESIZE;++r) 
	{
    /// 
      FASTSIN(0); ///ygo0
      FASTSIN(1);
	  FASTSIN(2);
	  FASTSIN(3);
	  FASTSIN(4);
	  FASTSIN(5);
	  FASTSIN(6);
	  FASTSIN(7);
	  FASTSIN(8);
	  FASTSIN(9);

      FASTCOS(0);///ygco0

     FASTSIN(11); 
     FASTSIN(12); 
     FASTSIN(13); 
     FASTSIN(14); 
     FASTSIN(15); 
     FASTSIN(16); 
     FASTSIN(17); 
     FASTSIN(18); 
     FASTSIN(19); 
     FASTSIN(20); 
     FASTSIN(21); 
     FASTSIN(22); 
     FASTSIN(23); 
     FASTSIN(24); 

	 FASTSIN(25); 
     FASTSIN(26); 
	 FASTSIN(27); 
     FASTSIN(28); 
	 FASTSIN(29); 

     FASTCOS(1);
     FASTCOS(2);
     FASTCOS(3);
     FASTCOS(4);
     FASTCOS(5);
     FASTCOS(6);
     FASTCOS(7);
     FASTCOS(8);
     FASTCOS(9);
     FASTCOS(10);
     FASTCOS(11);
     FASTCOS(12);
     FASTCOS(13);
     FASTCOS(14);
     FASTCOS(15);
     FASTCOS(16);

///// for A-vowel
	  //FASTSIN(17);
	  //FASTSIN(18);/////
	 FASTCOS(17);
     FASTCOS(18);
	 FASTCOS(19);
	 FASTCOS(20);
	 FASTCOS(21);
     FASTCOS(22);
	 FASTCOS(23);

    FASTCOS(24);
    FASTCOS(25);
	FASTCOS(26);
	FASTCOS(27);
    FASTCOS(28);
	FASTCOS(29);
	FASTCOS(30);
	  
     /////DSF
	prebuild_tbl[0][r]=1.060720008*2.1*((a*ygo0-a_sqare*ygo0+a*an*ygo1-an*ygo2)
		/(1-2*a*ygco0+a_sqare));
//ch(0);

    /////SIN
	prebuild_tbl[1][r]= ygo0*0.990020447;
//	ch(1);

	//// 8 sin
	prebuild_tbl[2][r]= 1.6*1.473005494*(0.3046*ygo0+0.2093*ygo3+ 0.052 *ygo4+   0.03*ygo5+
					          0.04 *ygo6+0.0193*ygo7+ 0.013 *ygo8+0.00591*ygo9);
//ch(2);
	/////SAW
	prebuild_tbl[3][r]= 0.99*(2.f*fmodf(w1*r/TWOPI, 1.f)-1.f);
//ch(3);
    //////DSF 2
	prebuild_tbl[4][r]= 2.1*1.650050865*((a12*ygo0-a12_square*ygo0+
		a12*an12*ygo1-an12*ygo2)/(1-2*a12*ygco0+a12_square));
//ch(4);
    ////SQUARE
	if (fmodf(w1*r/TWOPI, 1.f)>0.5) prebuild_tbl[5][r]= 0.99f;
    else prebuild_tbl[5][r]=-0.99f;	
//ch(5);		
	////drunk sinus 1 
    prebuild_tbl[6][r]= 0.2*1.15819915*(
 1.0    *ygo10 
-0.63853*ygo0 
-0.62999*ygo11 
-0.54566*ygo12 
-0.49686*ygo13 +
 0.48263*ygo14 +
 0.45504*ygo15 +
 0.44522*ygo16 
-0.43239*ygo17 +
 0.42108*ygo18 +
 0.41898*ygo19 
-0.39516*ygo20 
-0.37183*ygo21 +
 0.35016*ygo22 
-0.33997*ygo23 
-0.32836*ygo24 +

 0.87283*ygco1 
-0.662  *ygco2 
-0.66066*ygco3 
-0.59648*ygco4 
+0.52948*ygco5 
-0.52731*ygco6 +
 0.52642*ygco7 +
 0.51019*ygco8 +
 0.47068*ygco9 +
 0.45485*ygco10 
-0.40984*ygco11 
-0.40947*ygco12 
-0.40873*ygco13 +
 0.39393*ygco14 +
 0.36987*ygco15 +
 0.36931*ygco16 );
//	ch(6);
     ////A-vowel
     prebuild_tbl[7][r]= 0.1*2.851116189*(
 0.72101*ygo0 //// 1
-0.15914*ygo3 +/////2
 1.0    *ygo4 ////// 3
-0.19741*ygo5 +/////// 4
 0.06269*ygo6 //////5
-0.06535*ygo9 +/////8
-0.06758*ygo25 +/////9
 0.07361*ygo26 ////10

-0.41987*ygco0 +//// 1
 1.7238 *ygco17 /////2
-0.37558*ygco18 ////// 3
-0.43095*ygco19 +/////// 4
 0.08017*ygco20 ///// 7
-0.12514*ygco21 ////// 8
-0.11745*ygco22   ////11
-0.0767 *ygco23 );///12
//	 ch(7);
    ////U-vowel
prebuild_tbl[8][r]=0.2*2.739864865*(
( 1.0    *ygo0) +//// 1
( 0.10043*ygo3) +//// 2
( 0.15442*ygo4) +////3
( 0.05075*ygo5) +////4
(-0.11964*ygo6) +////5
(-0.53762*ygo7) +////6
( 0.10547*ygo9) +////7
(-0.03283*ygo26) +////10

(-0.73929*ygco0) +//// 1
( 0.20373*ygco17) +//// 2
(-0.17566*ygco19) +////4
(-0.19581*ygco24) +////5
(-0.07128*ygco25) +////6
( 0.08751*ygco21) +//////8
(-0.27237*ygco26) +////9
(-0.05965*ygco23) );////12
//ch(8);
prebuild_tbl[9][r]=(0.000030517578125f*1.029285782*pn.GetNextValue());//*ygo0);///noise


     ////MADE FROM MY U , sounds sherokhovato as you like
prebuild_tbl[10][r]=0.35*(
( 1.0    *ygo0) +
( 0.44523*ygo3) +
( 0.42237*ygo4) +
( 0.02018*ygo5) +
( 0.02427*ygo6) +
(-0.02448*ygo27) +
( 0.03741*ygo28) +
( 0.01979*ygo29) +
( 0.15886*ygco0) +
(-0.31527*ygco17) +
( 0.30318*ygco18) +
(-0.07245*ygco19) +
(-0.02168*ygco27) +
( 0.01471*ygco28) +
( 0.02061*ygco29) +
( 0.01284*ygco30) );/**/
/*

10
15
16
19

*/
//(0.000030517578125f*1.029285782*pn.GetNextValue());//*ygo0);///noise
//ch(9);
	}
	//Enda();
/*	for (int e=0;e<10;++e)
	{
	_lwrite (hndF2, (LPSTR) &rj, 2);///////
	  
	  char buk[16];
	  ltoa(maxres[e]*32768,buk,10);
     _lwrite (hndF2, (LPSTR) buk,strlen(buk));///////
	}
	///MessageBox(0,"Tables ready","yuyg",0);
*/
}
//-----------------------------------------------------------------------------------------
void Engine::initDefProg()
{
			setReverbWet(0.6);///REVERB
            setReverbSize(0.8);///REVERB
			setChorus(114);
			SetTunesValues(64,62,67,66,61,69);
			Q=1.5f;///setReso(0.5f);
			cut0=0.8f;///cut 1
			setCut(40);///cut 2
			buildEnvelope(6,0);//flat + LFO
            buildEnvelope(4,1);
		    SetGainsValues(35,100,100,100,100,75,40);
		    buildAllOsc(0,2,4,4,1,4);
			setAttack(60);
			setRelease(0);
		    setVeloSens(2,0);
            setVeloSens(4,1);
}
//-----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------