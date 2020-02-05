#include "AGain.hpp"
#include "editor.h"
#include <windows.h> 
void *EGAIN[8];
extern float Programms[45][64];
extern float ProgrammsContainer[45][64];
extern char progtbl[32][24];
extern void onLoadReadWavs(LPSTR flnm, int file_order, int exemplyar, int tabletype);
const float back127 =(1.f/127.f);
//-----------------------------------------------------------------------------------------
/////////// IMPORTANTO ! DESCRIBES OUR FORMAT !!!!!!
#define NPROGINCHUNK  45  ///32 actual and the rest is serving data
#define NUMREALPROG 32
#define CUR_PROG_OFFSET 33 //// NUMREALPROG +1
#define PROG_NAME_OFFSET 52 //// 64-12
#define NPARAMINCHUNK 64
//-----------------------------------------------------------------------------------------
AGain::AGain(audioMasterCallback audioMaster)
	: AudioEffectX(audioMaster, kNumerPrograms, kNumerParam)	//
{
/// prog names init
for (int le=0;le<NPROGINCHUNK;++le)
{
for (int ly=0;ly<NPARAMINCHUNK;++ly) ProgrammsContainer[le][ly]=Programms[le][ly];
}
	setNumInputs(0);		// stereo in
	setNumOutputs(2);		// stereo out
	setUniqueID('SWAS');	// identify
	///canMono();				// makes sense to feed both inputs with the same signal
	canProcessReplacing(true);	// supports both accumulating and replacing output
	hasVu ();
	hasClip (false);
	isSynth (true);
	setEditor (new Editor(this));

    programsAreChunks(true);

    ///MessageBox(0,"AGain","OK",0);
	engine=new Engine;
	engine->gimeEditor((Editor*)editor);
    EGAIN[engine->GetExemplyar()]=this;////go to global only for udtatedisplay()
	    
    ((Editor*)editor)->SetProgrammu(0);        
	/////-----------------------
	suspend ();		// flush buffer

  }
//-----------------------------------------------------------------------------------------
void AGain::setSampleRate (float sampleRate)
{
	char dak[32];
	ltoa((long)sampleRate,dak,10);
	MessageBox(0,"setSampleRate called",dak,0);
	AudioEffectX::setSampleRate (sampleRate);
	engine->SetSampleRate((long)sampleRate);
    /// do anything to rebuild tables
}
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
void AGain::setParameter(long index, float value)/////SET AGain MEMBERS VALUES
{
	switch (index)
	{
	        case 0: (engine)->setReverbWet(value); break; //!    
            case 1: (engine)->setReverbSize(value);break;  //!        
			case 2: (engine)->setChorus(value*127);break; //!
			case 3: (engine)->SetTuneValue(value*220-46,0);break;//!
			case 4: (engine)->SetTuneValue(value*220-46,1);break;//!
			case 5: (engine)->SetTuneValue(value*220-46,2);break;//!
			case 6: (engine)->SetTuneValue(value*220-46,3);break;//!
			case 7: (engine)->SetTuneValue(value*220-46,4);break;//!
			case 8: (engine)->SetTuneValue(value*220-46,5);break;//!
			case 9:  (engine)->setCut0(value*127); break; //!        
			case 10: (engine)->setCut(value*127); break; //!   
		    case 11: (engine)->setGain(value*100,0);break; //! 
			case 12: (engine)->setGain(value*100,1);break; //! 
			case 13: (engine)->setGain(value*100,2);break; //! 
			case 14: (engine)->setGain(value*100,3);break; //! 
			case 15: (engine)->setGain(value*100,4);break; //! 
			case 16: (engine)->setGain(value*100,5);break; //! 
			case 17: (engine)->setAttack(value*127); break; //!        
			case 18: (engine)->setRelease(value*127);break; //!          			
			case 19: (engine)->setPhase(value*127,0);break;    
			case 20: (engine)->setPhase(value*127,1);break;    
			case 21: (engine)->setPhase(value*127,2);break;    
			case 22: (engine)->setPhase(value*127,3);break;    
			case 23: (engine)->setPhase(value*127,4);break;    
			case 24: (engine)->setPhase(value*127,5);break;  

			break;	
	}
	if (editor)	((Editor*)editor)->setValue(index, value);///TO EDITOR

}
//-----------------------------------------------------------------------------------------
float AGain::getParameter(long index)
{
	long prognum=curProgram;
	float val=0.f;
	switch (index)
	{
	        case 0: val= ProgrammsContainer[prognum][29] ;    
            case 1: val= ProgrammsContainer[prognum][28] ;      
			case 2: val= ProgrammsContainer[prognum][27] ;      
			case 3: val= ProgrammsContainer[prognum][6]  *back127; 
			case 4: val= ProgrammsContainer[prognum][7]  *back127; 
			case 5: val= ProgrammsContainer[prognum][8]  *back127; 
			case 6: val= ProgrammsContainer[prognum][9]  *back127; 
			case 7: val= ProgrammsContainer[prognum][10] *back127; 
			case 8: val= ProgrammsContainer[prognum][11] *back127;   
			case 9: val= ProgrammsContainer[prognum][22] ; //!        
			case 10: val= ProgrammsContainer[prognum][26] ; //!   
            case 11: val= ProgrammsContainer[prognum][12]*0.01 ;//!  
			case 12: val= ProgrammsContainer[prognum][13]*0.01 ;//!  
			case 13: val= ProgrammsContainer[prognum][14]*0.01 ;//!  
			case 14: val= ProgrammsContainer[prognum][15]*0.01 ;//!  
			case 15: val= ProgrammsContainer[prognum][16]*0.01 ;//!  
			case 16: val= ProgrammsContainer[prognum][17]*0.01 ;//!  
        	case 17: val= ProgrammsContainer[prognum][25] ; //!       
			case 18: val= ProgrammsContainer[prognum][24] ; //!       		
			case 19: val= ProgrammsContainer[prognum][31] *back127;  
			case 20: val= ProgrammsContainer[prognum][32] *back127;  
			case 21: val= ProgrammsContainer[prognum][33] *back127;    
			case 22: val= ProgrammsContainer[prognum][34] *back127;     
			case 23: val= ProgrammsContainer[prognum][35] *back127; 
			case 24: val= ProgrammsContainer[prognum][36] *back127;    
      
	}
	return val;
}
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
long AGain::getChunk(void** data, bool isPreset)////saving
{

     for (int le=0;le<NUMREALPROG;++le)
	 memcpy((void*)&ProgrammsContainer[le][PROG_NAME_OFFSET],(void*)&progtbl[le][0],24*sizeof(char));
     
     ProgrammsContainer[CUR_PROG_OFFSET][0]=(float)engine->getCurrentProg();
              
	 *data=(void**)ProgrammsContainer;

	 isPreset=false;

	 return (NPARAMINCHUNK*NPROGINCHUNK*sizeof(float));// returns byteSize
}	
//-----------------------------------------------------------------------------------------
long AGain::setChunk(void* data, long byteSize, bool isPreset) ///reading
{
 
	if (byteSize<NPARAMINCHUNK*NPROGINCHUNK*sizeof(float)) {
	MessageBox(0,"Error in bank format","byteSize in floats",0);
    return 0;
	}

	memcpy(Programms,data,byteSize);
	for (int s=0;s<NUMREALPROG;++s)  
	{
		strcpy (progtbl[s],(char*)&Programms[s][PROG_NAME_OFFSET]);
	}
    ///--------------------------- rene 2 factory here

	for (long order=0;order<4;++order)  ///upto 4th order
	{
	long tabletype=0;
	if (Programms[34+order][32*tabletype]!=0)
	onLoadReadWavs((char*)&Programms[34+order][32*tabletype], 
		 order,engine->GetExemplyar(),tabletype);

	///MessageBox(0,(char*)&Programms[34+order][32*tabletype],"was 1",0);

    tabletype=1;
	if (Programms[34+order][32*tabletype]!=0)
	onLoadReadWavs((char*)&Programms[34+order][32*tabletype], 
		 order,engine->GetExemplyar(),tabletype);
	///MessageBox(0,(char*)&Programms[34+order][32*tabletype],"was 2",0);
    }

    ////recall active prog
	((Editor*)editor)->SetProgrammu((long)Programms[CUR_PROG_OFFSET][0]); 
    isPreset=false;
	
	return 0;
}
//-----------------------------------------------------------------------------------------
void AGain::getParameterName(long index, char *label)
{
switch (index)
	{
  	        case 0: strcpy(label, "ReverbWet"); break;  
            case 1: strcpy(label, "ReverbSize"); break;      
			case 2: strcpy(label, "Chorus");break;              
			case 3: strcpy(label, "Tune 1"); break;  
			case 4: strcpy(label, "Tune 2"); break;  
			case 5: strcpy(label, "Tune 3"); break;  
			case 6: strcpy(label, "Tune 4"); break;  
			case 7: strcpy(label, "Tune 5"); break;  
			case 8: strcpy(label, "Tune 6"); break;    
			case 9: strcpy(label, "Cut Env"); break;        
			case 10: strcpy(label, "Cut"); break;      
		    case 11: strcpy(label, "Gain 1"); break;  
			case 12: strcpy(label, "Gain 2"); break;  
			case 13: strcpy(label, "Gain 3"); break;  
			case 14: strcpy(label, "Gain 4"); break;  
			case 15: strcpy(label, "Gain 5"); break;  
			case 16: strcpy(label, "Gain 6"); break;  
			case 17: strcpy(label, "Attack"); break;      
			case 18: strcpy(label, "Release"); break;     
			case 19: strcpy(label, "Phase 1"); break;  
			case 20: strcpy(label, "Phase 2"); break;    
			case 21: strcpy(label, "Phase 3"); break;    
			case 22: strcpy(label, "Phase 4"); break;  
			case 23: strcpy(label, "Phase 5"); break;   
			case 24: strcpy(label, "Phase 6"); break;  
	}

}
//-----------------------------------------------------------------------------------------
void AGain::getParameterDisplay(long index, char *text)
{
	//Program& cp = programs[curProgram];
}

//-----------------------------------------------------------------------------------------
void AGain::getParameterLabel(long index, char *label)
{
	strcpy(label, "   NA   ");
}
//-----------------------------------------------------------------------------------------
void AGain::process(float **inputs, float **outputs, long sampleframes)
{
engine->process(inputs,outputs,sampleframes);	
}
//-----------------------------------------------------------------------------------------
void AGain::processReplacing(float **inputs, float **outputs, long sampleframes)
{
engine->process(inputs,outputs,sampleframes);      
}
//-----------------------------------------------------------------------------------------
long AGain::processEvents (VstEvents* ev)
{	
return engine->processEvents (ev);
}
//-----------------------------------------------------------------------------------------
void AGain::setBlockSize (long blockSize)
{
	AudioEffectX::setBlockSize (blockSize);
	// you may need to have to do something here...
}
//-----------------------------------------------------------------------------------------
void AGain::resume ()     /////----------VST SYNTH
{
wantEvents();
}
//-----------------------------------------------------------------------------------------
AGain::~AGain()
{
	// nothing to do here
}
//-----------------------------------------------------------------------------------------
bool AGain::getEffectName (char* name)
{
	strcpy (name, "GalactiX");
	return true;
}

//-----------------------------------------------------------------------------------------
bool AGain::getVendorString (char* text)
{
	strcpy (text, "alex@smartelectronix");
	return true;
}

//-----------------------------------------------------------------------------------------
bool AGain::getProductString (char* text)
{
	strcpy (text, "GalactiX");
	return true;
}
//-----------------------------------------------------------------------------------------
long AGain::canDo (char* text)
{
	if (!strcmp (text, "receiveVstEvents"))
		return 1;
	if (!strcmp (text, "receiveVstMidiEvent"))
		return 1;
//	if (!strcmp (text, "plugAsChannelInsert"))
//		return 1;
	return -1;	// explicitly can't do; 0 => don't know
}
//-----------------------------------------------------------------------------------------
