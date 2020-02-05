#ifndef __Engine_H
#define __Engine_H
#include "tunetables.h"

#include "..\Exe\CompileType.h"

#ifndef EXE_COMPILE
#include "..\Vst\editor.h"
#include "..\Vst\aeffectx.h"
#endif

#include <math.h>
#include <stdio.h>
#include <windows.h> 
#include "mmacroses.h"
//--------------------------------------------------------------------------------
//#ifdef CHECKPROG_VOLUME_AND_REPORT_TO_TXT
//extern float maxxa[32];
//extern long ba;
//#endif
//--------------------------------------------------------------------------------
#define MAXPOLY 16     /// MAXIMUM polifony
#define M_PI 3.14159265358979323846f
#define TWOPI 6.28318530717958647692
///static float nullarr[8]={0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f};
const float scaler127=(1.f/127.f);
extern float ProgrammsContainer[45][64];

extern HWND hPlug[8];
#define SAMPLERATE 44100
#define TABLESIZE 262144
#define TABLEMASK 262143
#define MINSTEPTUNE 0.005 /////(0.5%) =1./nstep[24]
#define NUM_OSC_TYPES 16 ///12
#define MAXWAVEFILELENGH_BYTES 32768*16

#define CHORUSLINE 32768
#define CHORUS_MSK 32767

#define CHORUS_LFO_AMP 110
#define CHORUSDLY 264
#define MAXCHORUSDELAY CHORUSDLY +CHORUS_LFO_AMP ///delayline lengh for chorus

#define WAVE_SIZE 32768   ///for reverb
#define WAVE_SIZE2 8192   ///for reverb
#define WAVE_SIZE_MASK 32767 
#define WAVE_SIZE_MASK4 8191 ///32768/4-1
#define SPEED 44100 //current samplerate for reverb
// Delay lengths are specified in seconds or
// Paper specified length/29761
///#define LENGTH_PREDELAY				0.1f
#define LENGTH_INPUTDIFFUSION1A		142.0f/SPEED
#define LENGTH_INPUTDIFFUSION1B		107.0f/SPEED
#define LENGTH_INPUTDIFFUSION2A		379.0f/SPEED
#define LENGTH_INPUTDIFFUSION2B		277.0f/SPEED
#define LENGTH_DECAYDIFFUSION1A		672.0f/SPEED
#define EXCURSION_DECAYDIFFUSION1A	8.0f/SPEED  //note paper has discrepancy - is it 8 or 16?
#define MODRATE_DECAYDIFFUSION1A	1.0f //Hz
#define LENGTH_DECAYDIFFUSION1B		908.0f/SPEED
#define EXCURSION_DECAYDIFFUSION1B	8.0f/SPEED  //note paper has discrepancy - is it 8 or 16?
#define MODRATE_DECAYDIFFUSION1B	1.0f //Hz
#define LENGTH_DECAYDIFFUSION2A		1800.0f/SPEED
#define LENGTH_DECAYDIFFUSION2B		2656.0f/SPEED
#define LENGTH_TANK1				4453.0f/SPEED
#define LENGTH_TANK2				3720.0f/SPEED
#define LENGTH_TANK3				4217.0f/SPEED
#define LENGTH_TANK4				3163.0f/SPEED
#define TAP_YL1						266.0f/SPEED
#define TAP_YL2						2974.0f/SPEED
#define TAP_YL3						1913.0f/SPEED
#define TAP_YL4						1996.0f/SPEED
#define TAP_YL5						1990.0f/SPEED
#define TAP_YL6						187.0f/SPEED
#define TAP_YL7						1066.0f/SPEED
#define TAP_YR1						353.0f/SPEED
#define TAP_YR2						3627.0f/SPEED
#define TAP_YR3						1228.0f/SPEED
#define TAP_YR4						2673.0f/SPEED
#define TAP_YR5						2111.0f/SPEED
#define TAP_YR6						335.0f/SPEED
#define TAP_YR7						121.0f/SPEED
#define samplesCheck 40
//const long ckk[2]={2,7};
#define MAXALLOWEDWAVS 16
static float *wavdata[MAXALLOWEDWAVS];
//-----------------------------------------------------------------------------------------

class Engine
{

public:
	Engine();
	~Engine();



#ifndef EXE_COMPILE
    ////void setProgram (long pgm, Editor* edt) ;
	inline long  processEvents (VstEvents* ev);
	bool gimeEditor(Editor *ed);
	Editor *edt;
#endif
	inline void process(float **inputs, float **outputs, long sampleframes);
	void render(float **outputs);
	////
    ///long framesamples;
	char GalactixDir[512];
	void initProcess();////////////
	void midiOn(long  note);
    void midiOff(long  note);
    void buildEnvelope(long  type,long  whichone);
    void buildOsc(long  type,long  oscnum);
    void buildAllOsc(long  type1,long  type2,long  type3,
					 long  type4,long  type5,long  type6);
	void setGain(long  value,long  oscnum);
	void SetVolume(long  value);
	void SetGainsValues( long  gain1,long  gain2,long  gain3,
						    long  gain4,long  gain5,long  gain6,long  gain7);
	void SetTuneValue(long  index,long  tune);
	void SetTunesValues(long  tune1,long  tune2,long  tune3,
						   long  tune4,long  tune5,long  tune6);
	void setWheel(long  value);
	void setCut(long  value );
	void setCut0(long  value );
	void setVeloSens(long  value, long  which);
	void setReso(long  value );
	void setRelease(long  value );
	void setAttack(long  value );
	void setReverbWet(float value);
	void setReverbSize(float value);
	void setChorus(long value);
	void setPhase(long  val, long  oscnum);
	void SetSampleRate(long srate); 
	long GetExemplyar() {return numInst;};
	//
	void setCurrentProg(long prognum){curProgram=prognum;};
	long getCurrentProg(){return curProgram ;};

   float* wavdata_ptr[16];
   long silenceCount;
   long lstart[MAXALLOWEDWAVS];
   long lend[MAXALLOWEDWAVS];
   long loop_start;
   long loop_end;
   long loop_start_filter;
   long loop_end_filter;
   //long llen[MAXALLOWEDWAVS];
   long  curent_osc_type[16];///[NUM_OSC_TYPES];
   float prebuild_tbl[16][TABLESIZE];///[NUM_OSC_TYPES][TABLESIZE];

private:
	long curProgram;
	void buildFilterEnvelope(long  type);
	void findLocation(char *outdir);
	void fDirWalk(char *_current);
	bool  checkDir();
	char DirName[512];

	
	long  numInst;
	long  srate_type;
	void initTables();

	long chorus;///value
	long chorus_desired;

	long phase[6][128];///osc - tone

	float GAINS[8];
	long normvol;
	long normvol_desired;

	long samplesToNextCheck; 
	///long samplesCheck;

	long  TUNE[8];	
	long STEPS[6][128];
	//long WHL_STEPS[128];

	//long  curent_osc_type[NUM_OSC_TYPES];
	long  curent_filt_env_type;
	float cut0;///cut1
	long cut;///cut2
	long cut_desired;
	
	float Q;///reso
	float pe1[128][128] ;//b1
    float pe2[128][128] ;//b1
    float pe3[128][128] ;//b1
    float pe4[128][128] ;//b1
    float pe5[128][128] ;//b1

	long  ispress[128];//// 1 - pressed , 0 - released
    long nton[16]; // global tone [1,2,...MAXPOLY] of each voice
    long velo[16];// global velocity [1,2,...MAXPOLY] of each voice
	long veloprev[16];///velocity of released note

    float prev_pan; ///to smother pan changes 
	float prev_vol; ///to smother volume changes 
	long index[16][8];/////runing index [0....LENSAMPLES]
	long startrel[16][8];/////index when released 

	long real_index[16];////index (time) for looped sound
	long rundx_rel[16];/// real_index handed to release
    long real_j[16];
	long real_jp[16];
	long real_j_rel[16];
	long real_jp_rel[16];

	long  isreleased[16];///// define if note relised BOOL
    long Delta[16];///note-on time
   // long DeltaRel[16];///release time
    long tonereleased[16];/////note's tone released
    long relgone[16];/////run index from startrel[]
	float *envelope[22];///[32768];///0-1 volume; 2-11 filter
 
    //Formant filter
	float borf1[4],borf2[4];
	float af1,af2,af3,af4,af5;
   //------------------------------------
   ///float out[8][TABLESIZE];/////[oscnum][index]
   
   float bo[16][8];
   float borel[16][8];// at release

   float midiScaler[256];
   float filterScaler[256];
   long RELEASE_lng;///[256];///release and 1/release
   float RELEASE_flt;///[256];///release and 1/release

   long RELEASE_2_lng;///[256];///release to hande over and 1/release
   float RELEASE_2_flt;///[256];///release to hande over and 1/release

   long ATTACK_lng;///[256];///release and 1/release
   float ATTACK_flt;///[256];///release and 1/release

   long ATTACK_2_lng;///[256];///release to hande over and 1/release
   float ATTACK_2_flt;///[256];///release to hande over and 1/release

   //------------------------------------///REVERB
   	float	Roomsize;
    float	wet,wet1,wet2;
	void initReverb();
	void initDefProg();
	long reverb_decay_smpls;//300000*decay
	///variables
   	long  tapyl1;
	long  tapyl2;
	long  tapyl3;
	long  tapyl4;
	long  tapyl5;
	long  tapyl6;
	long  tapyl7;
	long  tapyr1;
	long  tapyr2;
	long  tapyr3;
	long  tapyr4;
	long  tapyr5;
	long  tapyr6;
	long  tapyr7;
	float mix;
	float decay;
	float* sinetable;
	float* sinetable2;
   //long *sinel ;
   //long *sinel2 ;
   //float *sinef;
   //float *sinef2;
	//float damping;
#define damping 0.0005f
#define idamping 0.9995f
	///float idamping;
	float dampingay1;

	float dampingby1;

	long  tank1tap;
	long  tank1length;
	float* tank1line;
	long  tank2tap;
	long  tank2length;
	float* tank2line;
	long  tank3tap;
	long  tank3length;
	float* tank3line;
	long  tank4tap;
	long  tank4length;
	float* tank4line;

	//float decaydiffusion1coeff;
	//float decaydiffusion2coeff;
#define decaydiffusion2coeff 0.50f
#define decaydiffusion1coeff 0.70f

	long decaydiffusion1atap;
	//long decaydiffusion1ailength;
#define decaydiffusion1ailength	681
#define decaydiffusion1aflength	681.f
	//float decaydiffusion1aflength;
#define decaydiffusion1bilength 917
#define decaydiffusion1bflength 917.f

	float decaydiffusion1acentre;
	float decaydiffusion1arange;
	float decaydiffusion1amodpos;
	float decaydiffusion1amodrate;
	float* decaydiffusion1aline;
	long  decaydiffusion1btap;
//long  decaydiffusion1bilength;
//float decaydiffusion1bflength;
	float decaydiffusion1bcentre;
	float decaydiffusion1brange;
	float decaydiffusion1bmodpos;
	float decaydiffusion1bmodrate;
	float* decaydiffusion1bline;
	long  decaydiffusion2atap;
	//long  decaydiffusion2alength;
#define decaydiffusion2alength 1800

	float* decaydiffusion2aline;
	long  decaydiffusion2btap;
	//long  decaydiffusion2blength;
#define decaydiffusion2blength 2656
	float* decaydiffusion2bline;

	long  inputdiffusion1atap;
	long  inputdiffusion1alength;

	float* inputdiffusion1aline;
	long  inputdiffusion1btap;
	long  inputdiffusion1blength;
	float* inputdiffusion1bline;
	//float inputdiffusion1coeff;
#define inputdiffusion1coeff 0.750f 
#define inputdiffusion2coeff 0.625f
	long  inputdiffusion2atap;
	long  inputdiffusion2alength;
	float* inputdiffusion2aline;
	long  inputdiffusion2btap;
	long  inputdiffusion2blength;
	float* inputdiffusion2bline;
	//float inputdiffusion2coeff;

	//float ibandwidth;
	float bandwidthy1;
	//float bandwidth;
#define bandwidth 0.9995f 
#define ibandwidth 0.0005f ///1.0f-bandwidth; 

	//long  predelaytap;
	///void cleanup();
	//long  predelaylength;
	//float* predelayline;
	//bool notsafe;
	///float echo_gulyaet[32768];

	//long result;///the same as l for chorus e.g. index wrapped
	
	//------------------------------------
    long  l;
	float membmory[CHORUSLINE];///memory line
    float chorus_tbl[CHORUSLINE];
	float chorus_tbl2[CHORUSLINE];
  long  ol[CHORUSLINE];
  long  ol2[CHORUSLINE];
  long  olz[CHORUSLINE];
  long  olz2[CHORUSLINE];
  float fa[CHORUSLINE];
  float fa2[CHORUSLINE];

 
	//------------------------------------
	//long dlysmpls; 
	//float dlyval;
   //long isFXOff;

};
//-----------------------------------------------------------------------------------------

#define ap1 (volf*ann_0_0[j]+backvolv*ann_1_0[j])
#define ap2 (volf*ann_0_1[j]+backvolv*ann_1_1[j])
#define ap3 (volf*ann_0_2[j]+backvolv*ann_1_2[j])
#define ap4 (volf*ann_0_3[j]+backvolv*ann_1_3[j])
#define ap5 (volf*ann_0_4[j]+backvolv*ann_1_4[j])


inline void Engine::process(float **inputs, float **outputs, long sampleframes)
{
	
			    long b=1;
			    //long issound=0;		
				float* g0=&GAINS[0];
				float* g1=&GAINS[1];
				float* g2=&GAINS[2];
				float* g3=&GAINS[3];
				float* g4=&GAINS[4];
				float* g5=&GAINS[5];

                        float* tb0=prebuild_tbl[curent_osc_type[0]];
                        float* tb1=prebuild_tbl[curent_osc_type[1]];
				float* tb2=prebuild_tbl[curent_osc_type[2]];
				float* tb3=prebuild_tbl[curent_osc_type[3]];
				float* tb4=prebuild_tbl[curent_osc_type[4]];
				float* tb5=prebuild_tbl[curent_osc_type[5]];

				float* ann_0_0=envelope[0+2];
                float* ann_0_1=envelope[1+2];
				float* ann_0_2=envelope[2+2];
				float* ann_0_3=envelope[3+2];
				float* ann_0_4=envelope[4+2];

				float* ann_1_0=envelope[0+7];
                float* ann_1_1=envelope[1+7];
				float* ann_1_2=envelope[2+7];
				float* ann_1_3=envelope[3+7];
				float* ann_1_4=envelope[4+7];

			while (b<MAXPOLY)
			{	//------------------------------------	
				if (velo[b]!=0) //////////////PLAY
				{
				//issound=1;
				silenceCount=0;
			    float res; 
			    float* out1 = outputs[0]+Delta[b];
	            //float* out2 = outputs[1]+Delta[b];
				long startfrom = sampleframes-Delta[b];
	            Delta[b]=0;
				float volb =  midiScaler[velo[b]]*normvol; 
				float volf =  filterScaler[velo[b]]*cut0 ; 
			    float backvolv= 1.f-volf; 
				
				float bf0=  bo[b][0];
				float bf1=  bo[b][1];
				float bf2=  bo[b][2];
				float bf3=  bo[b][3];
				float bf4=  bo[b][4];
				float bf5=  bo[b][5];
				float bf6=  bo[b][6];
				float bf7=  bo[b][7];

                float *pf1=&pe1[nton[b]][cut];
                float *pf2=&pe2[nton[b]][cut];
				float *pf3=&pe3[nton[b]][cut];
				float *pf4=&pe4[nton[b]][cut];
				float *pf5=&pe5[nton[b]][cut];

			    long i0=index[b][0];
				long i1=index[b][1];
				long i2=index[b][2];
				long i3=index[b][3];
				long i4=index[b][4];
				long i5=index[b][5];

                long* st0=&STEPS[0][nton[b]] ;
                long* st1=&STEPS[1][nton[b]] ;
				long* st2=&STEPS[2][nton[b]] ;
				long* st3=&STEPS[3][nton[b]] ;
				long* st4=&STEPS[4][nton[b]] ;
				long* st5=&STEPS[5][nton[b]] ;
				long ri=real_index[b];
				long j=real_j[b];
				long jp=real_jp[b];
				  // loop 1
		          while (startfrom--)
				  {	 
		          float in=*g0*tb0[i0&TABLEMASK]+*g1*tb1[i1&TABLEMASK]+*g2*tb2[i2&TABLEMASK]
				     +*g3*tb3[i3&TABLEMASK]+*g4*tb4[i4&TABLEMASK]+*g5*tb5[i5&TABLEMASK];				 
				  //			  
				  i0+=*st0;
				  i1+=*st1;
				  i2+=*st2;
				  i3+=*st3;
				  i4+=*st4;
				  i5+=*st5;
				  /////FILTER

                  res =  ap1*in +ap2*bf0 + ap3*bf1 - ap4*bf2-ap5*bf3;
				  ////------wrap envelope loop indexes 
				  ++j;
				  if (j==loop_end_filter) j=loop_start_filter;

				  if (jp==loop_end) jp=loop_start;
				  ///--------------------------------------------------				  
				  
				  
                  bf3=bf2;////will be y[n-2]
				  bf1=bf0;///will be x[n-2]
				  bf0=in;///will be x[n-1]
				  bf2=res;////will be y[n-1]			   
				  res= *pf1*res+*pf2*bf4+*pf3*bf5-*pf4*bf6-*pf5*bf7;
                          bf7=bf6;////will be y[n-2]
				  bf6=bf4;///will be x[n-2]
				  bf4=bf2;///will be x[n-1]
				  bf6=res;////will be y[n-1]
				  if (ri++<ATTACK_lng) res*=ATTACK_flt*ri;//fade-in				   				 
				  
				  (*out1++) += res*volb*envelope[0][jp++]; 

				  }/////END OF WHILE - loop 1
				index[b][0]=i0;
				index[b][1]=i1;
				index[b][2]=i2;
				index[b][3]=i3;
				index[b][4]=i4;
				index[b][5]=i5;
				bo[b][0]=bf0;
				bo[b][1]=bf1;
				bo[b][2]=bf2;
				bo[b][3]=bf3;
				bo[b][4]=bf4;
				bo[b][5]=bf5;
				bo[b][6]=bf6;
				bo[b][7]=bf7;
				real_index[b]=ri;
				real_j[b]=j;
				real_jp[b]=jp;

				}////END OF PLAY
				//------------------------------------
				if (isreleased[b]==1) ///////RELEASE
				{
                //issound=1;
				silenceCount=0;
				float res; //backvolv,
	            float* out1 = outputs[0];///
	            //float* out2 = outputs[1];///
			    long startfrom = sampleframes;///
		        float volv = midiScaler[veloprev[b]]*normvol;
			
				float volf =filterScaler[veloprev[b]]*cut0;
				float backvolv=1.f-volf;

	            float bf0=  borel[b][0];
				float bf1=  borel[b][1];
				float bf2=  borel[b][2];
				float bf3=  borel[b][3];
				float bf4=  borel[b][4];
				float bf5=  borel[b][5];
				float bf6=  borel[b][6];
				float bf7=  borel[b][7];

                float *pf1=&pe1[tonereleased[b]][cut];
                float *pf2=&pe2[tonereleased[b]][cut];
				float *pf3=&pe3[tonereleased[b]][cut];
				float *pf4=&pe4[tonereleased[b]][cut];
				float *pf5=&pe5[tonereleased[b]][cut];

			    long i0=startrel[b][0];
				long i1=startrel[b][1];
				long i2=startrel[b][2];
				long i3=startrel[b][3];
				long i4=startrel[b][4];
				long i5=startrel[b][5];

                long* st0=&STEPS[0][tonereleased[b]] ;
                long* st1=&STEPS[1][tonereleased[b]] ;
				long* st2=&STEPS[2][tonereleased[b]] ;
				long* st3=&STEPS[3][tonereleased[b]] ;
				long* st4=&STEPS[4][tonereleased[b]] ;
				long* st5=&STEPS[5][tonereleased[b]] ;

				long ri=rundx_rel[b];
				long rg=relgone[b];
				long j=real_j_rel[b];
				long jp=real_jp_rel[b];

					  /////loop 2 - release
                  while (startfrom--)  
				  {               
			      //long ck= (ri>32767)? 1:0; 		          
		           float in=*g0*tb0[i0&TABLEMASK]+*g1*tb1[i1&TABLEMASK]+*g2*tb2[i2&TABLEMASK]
				     +*g3*tb3[i3&TABLEMASK]+*g4*tb4[i4&TABLEMASK]+*g5*tb5[i5&TABLEMASK];
				   
				  i0+=*st0;
                  i1+=*st1;
				  i2+=*st2;
                  i3+=*st3;
                  i4+=*st4;
                  i5+=*st5;

				  res =  ap1*in +ap2*bf0 + ap3*bf1 - ap4*bf2-ap5*bf3;

				  ////------wrap envelope loop indexes 
				  ++j;
				  if (j==loop_end_filter) j=loop_start_filter;

				  if (jp==loop_end) jp=loop_start;
				  ///--------------------------------------------------				  
                  bf3=bf2;////will be y[n-2]
				  bf1=bf0;///will be x[n-2]
				  bf0=in;///will be x[n-1]
				  bf2=res;////will be y[n-1]				   
				  res= *pf1*res+*pf2*bf4+*pf3*bf5-*pf4*bf6-*pf5*bf7;
                  bf7=bf6;////will be y[n-2]
				  bf6=bf4;///will be x[n-2]
				  bf4=bf2;///will be x[n-1]
				  bf6=res;////will be y[n-1]
                  if (ri++<ATTACK_lng) res*=ATTACK_flt*ri;//fade-in (for short sounds)					 
				  res*=volv*RELEASE_flt*(RELEASE_lng-rg++)*envelope[0][jp++];//fade-out;                  
                  (*out1++) += res ;
                   //   ++(*ri);
					  //++(*rg);			 
                         ////RELEASE END -> BREAK LOOP
						 if (rg>RELEASE_lng) { 
					         volv=0;
				             isreleased[b]=0;	
						 }
					  }///loop 2 release end
				startrel[b][0]=i0;
				startrel[b][1]=i1;
				startrel[b][2]=i2;
				startrel[b][3]=i3;
				startrel[b][4]=i4;
				startrel[b][5]=i5;
				borel[b][0]=bf0;
				borel[b][1]=bf1;
				borel[b][2]=bf2;
				borel[b][3]=bf3;
				borel[b][4]=bf4;
				borel[b][5]=bf5;
				borel[b][6]=bf6;
				borel[b][7]=bf7;
				rundx_rel[b]=ri;
				relgone[b]=rg;
				real_j_rel[b]=j;
				real_jp_rel[b]=jp;
                }	////end is released	
				//------------------------------------
            ++b;
			}

	float *outputL=outputs[0]; 
    float *outputR=outputs[1];
    float chorusloc;//,chorusloce;
	long bukka;///,oetl,oetl2;

    ///////////	
   if (silenceCount<reverb_decay_smpls)//300000*decay
   {
    float half=0.5;
    float value1,value2,tankinput;
	float yl,yr;
	float delaytap;
	long pos,posp1;
	float fract,a,b_rev,c;
 
    /////// INDEXES ADRS
    long* ind1= &inputdiffusion1atap;
	long* ind2= &inputdiffusion1btap;
    long* ind3= &inputdiffusion2atap;
	long* ind4= &inputdiffusion2btap;

	while(sampleframes--)
	{
        //float in =(*outputL); 
        /////-------------------------------------------------  CHORUS & DELAY       
            bukka= (l++)&CHORUS_MSK;
		membmory[bukka]=*outputL;////write to memory
            //memdmory[l]=*outputL;

		chorusloc=chorus*0.001;
		*outputL*=(1.f-chorusloc);////adjust dry signal
		*outputL=*outputL+chorusloc*(membmory[ol[bukka]]  
		+fa[bukka]*(membmory[olz[bukka]] -membmory[ol[bukka]])) +1e-20;
        *outputR=*outputL+chorusloc*(membmory[ol2[bukka]]
		+fa2[bukka]*(membmory[olz2[bukka]]-membmory[ol2[bukka]]))+1e-20;

	  /////-------------------------------------------------  REVERB

        //value2=0.5f* (*outputL + *outputR)*bandwidth+ibandwidth*bandwidthy1;

		bandwidthy1=0.5f* (*outputL + *outputR)*bandwidth+ibandwidth*bandwidthy1;//value2;

		value1=inputdiffusion1aline[inputdiffusion1atap];
	
		inputdiffusion1aline[inputdiffusion1atap]=bandwidthy1;//value2;

		//if(--inputdiffusion1atap==0) inputdiffusion1atap=141;////inputdiffusion1alength;
		WRAP(1,142);

	    value1+=bandwidthy1*inputdiffusion1coeff;

		value2=inputdiffusion1bline[inputdiffusion1btap];
		value1-=value2*inputdiffusion1coeff;
		inputdiffusion1bline[inputdiffusion1btap]=value1;

		////if(inputdiffusion1btap<0) inputdiffusion1btap=inputdiffusion1blength;
		WRAP(2,107);

		value2+=value1*inputdiffusion1coeff;

		value1=inputdiffusion2aline[inputdiffusion2atap];
		value2-=value1*inputdiffusion2coeff;
		inputdiffusion2aline[inputdiffusion2atap]=value2;

		//if(inputdiffusion2atap<0) inputdiffusion2atap=inputdiffusion2alength;
		WRAP(3,379);

		value1+=value2*inputdiffusion2coeff;

		tankinput=inputdiffusion2bline[inputdiffusion2btap];
		value1-=tankinput*inputdiffusion2coeff;
		inputdiffusion2bline[inputdiffusion2btap]=value1;

		//if(inputdiffusion2btap<0) inputdiffusion2btap=inputdiffusion2blength;
		WRAP(4,277);

		tankinput+=value1*inputdiffusion2coeff;
//b=1/(b-b);
		// tankinput is now sent into two points of the tank
		// for those with the original paper, I'm going left first

		value2=tankinput+decay*tank4line[tank4tap];

		//left hand side

		delaytap=(float) decaydiffusion1atap-sinetable[bukka];

		//if IS_LESS_THANZERO(delaytap) delaytap+=decaydiffusion1aflength;
		if(delaytap<0.0f) delaytap+=decaydiffusion1aflength;

        TRUNCATE( delaytap,pos,fract,half);
        ///////

		posp1=pos+1;
if(posp1>680) posp1=0;

        value1=decaydiffusion1aline[pos]+fract*(decaydiffusion1aline[posp1]-decaydiffusion1aline[pos]);
		//end interpolation


		value2+=value1*decaydiffusion1coeff; //note sign
		decaydiffusion1aline[decaydiffusion1atap++]=value2;

if(decaydiffusion1atap==decaydiffusion1ailength) decaydiffusion1atap=0;


		value1-=value2*decaydiffusion1coeff;

		// output from last section: value1
		// tank 1 delay line

		value2=tank1line[tank1tap];
		tank1line[tank1tap++]=value1;
		if(tank1tap==tank1length) tank1tap=0;

		// output from last section: value2
		// damping a:  y(n)=(1-damping)*x(n) + damping*y(n-1)

		//value2*=idamping;
		value2=value2*idamping+damping*dampingay1;
		dampingay1=value2;

		// output from last section: value2
		// decay

		//value2*=decay;

		// output from last section: value2
		// decay diffusion 2a

		value1=decaydiffusion2aline[decaydiffusion2atap];
		value2=value2*decay-value1*decaydiffusion2coeff;
		decaydiffusion2aline[decaydiffusion2atap++]=value2;

if(decaydiffusion2atap==decaydiffusion2alength)	decaydiffusion2atap=0;

// b=1/(b-b);

		value1+=value2*decaydiffusion2coeff;

		// output from last section: value1
		// tank 2 delay line

		value2=tank2line[tank2tap];
		tank2line[tank2tap++]=value1;
		if(tank2tap==tank2length) tank2tap=0;

		// output from last section: value2
		// decay and sum with tankinput

		//value2*=decay;
		value2=value2*decay+tankinput;

	//right hand side
    	delaytap=decaydiffusion1btap - sinetable2[bukka];

		if(delaytap<0.0f)	delaytap+=decaydiffusion1bflength;
        TRUNCATE( delaytap,pos,fract,half);

		posp1=pos+1;
		if(posp1>916) posp1=0;///decaydiffusion1bilength;
	
        value1=decaydiffusion1bline[pos]+fract*(decaydiffusion1bline[posp1]-decaydiffusion1bline[pos]);

		//end interpolation

		value2+=value1*decaydiffusion1coeff; //note sign
		decaydiffusion1bline[decaydiffusion1btap++]=value2;

if(decaydiffusion1btap==decaydiffusion1bilength) decaydiffusion1btap=0;

		value1-=value2*decaydiffusion1coeff;

		// output from last section: value1
		// tank 3 delay line

		value2=tank3line[tank3tap]*idamping+damping*dampingby1;
		dampingby1=value2;

		tank3line[tank3tap++]=value1;
		if(tank3tap==tank3length) tank3tap=0;

		// output from last section: value2

		value2*=decay;

		// output from last section: value2
		// decay diffusion 2b

		value1=decaydiffusion2bline[decaydiffusion2btap];
		value2-=value1*decaydiffusion2coeff;
		decaydiffusion2bline[decaydiffusion2btap++]=value2;
if(decaydiffusion2btap==decaydiffusion2blength) decaydiffusion2btap=0;
		value1+=value2*decaydiffusion2coeff;

		// output from last section: value1
		// tank 4 delay line

		//value2=tank4line[tank4tap]; note tank4 output has already been cycled in left hand side so we don't want to do it agin
		tank4line[tank4tap++]=value1;
        if(tank4tap==tank4length) tank4tap=0;
		//output
		//left
		long tanka1= tank1tap;
	    long tanka3=	tank3tap;
		long tanka2=	tank2tap;
		long tanka4=tank4tap;
		long suma = decaydiffusion2btap;
		long suma2 = decaydiffusion2atap;

		//pos=tank3tap-tapyl1;
	    ///if(pos<0) pos+=tank3length;
		WRAP2(tanka3,pos,1,4217,266); 
		yl=0.6f*tank3line[pos];

		//pos=tank3tap-tapyl2;
		//if(pos<0) pos+=tank3length;
        WRAP2(tanka3,pos,2,4217,2974); 
		yl+=0.6f*tank3line[pos];

		///pos=decaydiffusion2btap-tapyl3;
		//if(pos<0) pos+=decaydiffusion2blength;
		WRAP2(suma,pos,3,2656,1913);
		yl-=0.6f*decaydiffusion2bline[pos];

		//pos=tank4tap-tapyl4;
		//if(pos<0) pos+=tank4length;
		WRAP2(tanka4,pos,4,3163,1996);
		yl+=0.6f*tank4line[pos];

		//pos=tank1tap-tapyl5;
		//if(pos<0) pos+=tank1length;
		WRAP2(tanka1,pos,5,4453,1990);
		yl-=0.6f*tank1line[pos];

		//pos=decaydiffusion2atap-tapyl6;
		//if(pos<0) pos+=decaydiffusion2alength;
        WRAP2(suma2,pos,6,1800,187);
		yl-=0.6f*decaydiffusion2aline[pos];

		//pos=tank2tap-tapyl6;
		//if(pos<0) pos+=tank2length;
		WRAP2(tanka2,pos,7,3720,187);
        float wetL=yl-0.6f*tank2line[pos];

        //////right
		//pos=tank1tap-tapyr1;
		//if(pos<0) pos+=tank1length;
        WRAP2(tanka1,pos,8,4453,266);
		yr=0.6f*tank1line[pos];

		//pos=tank1tap-tapyr2;
		//if(pos<0) pos+=tank1length;
        WRAP2(tanka1,pos,9,4453,2974);
		yr+=0.6f*tank1line[pos];

		//pos=decaydiffusion2atap-tapyr3;
		//if(pos<0) pos+=decaydiffusion2alength;
        WRAP2(suma2,pos,10,1800,1228);
		yr-=0.6f*decaydiffusion2aline[pos];

		//pos=tank2tap-tapyr4;
		//if(pos<0) pos+=tank2length;
        WRAP2(tanka2,pos,11,3720,2673);
		yr+=0.6f*tank2line[pos];

		//pos=tank3tap-tapyr5;
		//if(pos<0) pos+=tank3length;
        WRAP2(tanka3,pos,12,4217,1990);
		yr-=0.6f*tank3line[pos];

		//pos=decaydiffusion2btap-tapyr6;
		//if(pos<0) pos+=decaydiffusion2blength;
        WRAP2(suma,pos,13,2656,335);
		yr-=0.6f*decaydiffusion2bline[pos];

		//pos=tank1tap-tapyr7;
		//if(pos<0) pos+=tank1length;
        WRAP2(tanka1,pos,14,4453,4453);
		float wetR= yr-0.6f*tank1line[pos] ;

		//////// stereo out
		float erat=*outputL++ += mix*wetL ;
    	*outputR++ += mix*wetR ;
//#ifdef CHECKPROG_VOLUME_AND_REPORT_TO_TXT
//if (fabs(erat)>maxxa[ba]) maxxa[ba]=fabs(erat);
//#endif	
      /////-------------------------------------------------  END REVERB


		/////---------------------------Smoothing
        // do it every 40th sample
		if (!--samplesToNextCheck)
		{			
			samplesToNextCheck = samplesCheck;
            ////smooth main volume
			if (normvol_desired!=normvol )
			{
				if (normvol  > normvol_desired)	--normvol;
				else ++normvol;
			}
			////smooth main cut
            if (cut_desired!=cut)
			{
				if (cut  > cut_desired)--cut;
				else ++cut;
			}
			////smooth chorus
            if (chorus_desired!=chorus)
			{
				if (chorus  > chorus_desired) --chorus;
				else ++chorus;
			}
		}//////IF END Smothing 
		// 
		++silenceCount;
	}/////////////WHILE END
   }///// silenceCount end

   /////-------------------------------------------------
   //////SILENCE
   else
   {
	   while(sampleframes--)
	   {
	   /////---------------------------CHORUS & DELAY       
        bukka= (l++)&CHORUS_MSK;

		float in=membmory[bukka]=*outputL;////write to memory
		chorusloc=chorus*0.001;
		in*=(1.f-chorusloc);////adjust dry signal

		*outputL++=in+chorusloc*(membmory[ol[bukka]]  
		+fa[bukka]*(membmory[olz[bukka]] -membmory[ol[bukka]])) +1e-20;

        *outputR++=in+chorusloc*(membmory[ol2[bukka]]
		+fa2[bukka]*(membmory[olz2[bukka]]-membmory[ol2[bukka]]))+1e-20;

		/////---------------------------Silence smoothing
        // do it every 40th sample
		if (!--samplesToNextCheck)
		{			
			samplesToNextCheck = samplesCheck;
            ////smooth main volume
			if (normvol_desired!=normvol )
			{
				if (normvol  > normvol_desired)	--normvol;
				else ++normvol;
			}
			////smooth main cut
            if (cut_desired!=cut)
			{
				if (cut  > cut_desired)--cut;
				else ++cut;
			}
			////smooth chorus
            if (chorus_desired!=chorus)
			{
				if (chorus  > chorus_desired) --chorus;
				else ++chorus;
			}
		}//////IF END
	   }////END WHILE
   }////// END SILENCE
   
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
#ifndef EXE_COMPILE
inline long Engine::processEvents (VstEvents* ev)
{	
for (long i = 0; i < ev->numEvents; i++)
	{
		if ((ev->events[i])->type != kVstMidiType)
			continue;
		VstMidiEvent* event = (VstMidiEvent*)ev->events[i];
		char* midiData = event->midiData;

		long status = midiData[0] & 0xf0;		// ignoring channel
        long note = midiData[1] & 0x7f;
        long velocity = midiData[2] & 0x7f;		

		 switch (status) {
		 case 0x90: //// PLAY NOTE	
		 {	 
			    if (velocity!=0) {
			    long  jj=1;
		        if (ispress[note]!=0) jj=ispress[note];					
                else while((velo[jj]!=0)&&(jj<MAXPOLY)) ++jj;//define which note was pressed
                ispress[note]=jj;////remember note's line

				nton[jj]=note;
	            velo[jj]=velocity;
				Delta[jj]=event->deltaFrames;
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
				if (edt) ((Editor*)edt)->SetNoteOn( note);

				}///end if ((velocity==0)
			    else
			    {
			    //PROCESSING AS noteoff
                long jj=ispress[note];//define note play line
			    ispress[note]=0;
                long kk=1;
                while((isreleased[kk]!=0)&&(kk<MAXPOLY)) ++kk;//define which note was released
           
                rundx_rel[kk]=real_index[jj];	
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
			 if (edt) ((Editor*)edt)->SetNoteOff( note);      
			 }
		 } 
		break; 

///////////

		case 0x80: //////// STOP NOTE
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
			if (edt) ((Editor*)edt)->SetNoteOff( note);           
			}
			break;	

		case 0xB0://////// CONTROLL
			{
         long cytlnumber = note;///midiData[1] & 0x7f;/// 
		 switch(cytlnumber) {		
		        case 1:  
			    cut_desired=velocity;
			    if (edt) ((Editor*) edt)->SetKnob(4,velocity);
				//if ((ev->events[i])->type != kVstMidiType) 
				//	MessageBox(0,"Modulation","OK",0);break;				
				break;
		 case 7:  
			 normvol_desired=(midiData[2] & 0x7f)<<3;
			 if (edt) ((Editor*) edt)->SetVolume(normvol_desired*0.0984252f);
			 break;    
         case 91: 
			 chorus_desired=(midiData[2] & 0x7f)<<3;
			 if (edt) ((Editor*) edt)->SetKnob(5,midiData[2] & 0x7f);
			 break;    
		 case 72: 
			 setRelease(midiData[2] & 0x7f);
			 if (edt) ((Editor*) edt)->SetKnob(2,midiData[2] & 0x7f);
			 break;    
		 case 73: 
			 setAttack(midiData[2] & 0x7f);
			 if (edt) ((Editor*) edt)->SetKnob(3,midiData[2] & 0x7f);
			 break;    		 
		/*  case 64: 
			  //pedal
			  RELEASE_2_lng=(velocity<64)?0:10000;
			  //100+(30000.f*scaler127*(midiData[2] & 0x7f));
              RELEASE_2_flt=1.f/RELEASE_2_lng;
			  //MessageBox(0,"Sustain","OK",0);
			  break;*/
          case 120: ///All Sound Off
			  {
			  for (int e=0;e<MAXPOLY;++e) {isreleased[e]=1;velo[e]=0;}
              for (int t=0;t<127;++t) ispress[t]=0;	
			  if (edt) ((Editor*) edt)->SetAllNoteOff() ;  
			  ///MessageBox(0,"ALL NOTE OFF 120","OK",0);
			  }
		  break; 
		  
		  case 121: ////All Controllers Off
			  {
			  ////RESTORE MOD CONTROLL
			  if (edt) ((Editor*) edt)->SetKnob(4,ProgrammsContainer[curProgram][26]*127);
              cut_desired=ProgrammsContainer[curProgram][26]*127;
			  ///MessageBox(0,"ALL NOTE OFF 121","OK",0);
			  }
		  break;

          case 123: ///All Notes Off
			  {
			  ////RESTORE MOD CONTROLL
              if (edt) 
			  {
			  ((Editor*) edt)->SetKnob(4,ProgrammsContainer[curProgram][26]*127);
			  ((Editor*) edt)->SetAllNoteOff() ; 
			  }
              cut_desired=ProgrammsContainer[curProgram][26]*127;
			  for (int e2=0;e2<MAXPOLY;++e2) {isreleased[e2]=1;velo[e2]=0;}
              for (int t2=0;t2<127;++t2) ispress[t2]=0;	 
			 
			  //MessageBox(0,"ALL NOTE OFF 123","OK",0);
			  }
		  break;
		


          break;
		 }///END CTRL SWITCH
		 break;
		} ///END CONTROLL

		 case 0xE0://////// WHEEL
			{
         unsigned short _14bit = (unsigned short)midiData[2];
         _14bit <<= 7;
         _14bit |= (unsigned short)midiData[1];
         _14bit >>= 7;////reduce to get it in range of 0-127
         setWheel(_14bit );
	     if (edt) ((Editor*) edt)->SetWheel(0,_14bit );
	     break;
			}

        break;
        }/////////end switch status
		event++;

	}
	return 1;	// want more

}
#endif
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
#endif
