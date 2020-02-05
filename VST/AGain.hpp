#ifndef __AGAIN_H
#define __AGAIN_H

#include "audioeffectx.h"
#include "..\Engine\Engine.hpp"
//-----------------------------------------------------------------------------------------
// parameters...
enum
{
	kNumerPrograms = 0,///18,///
	kNumOutputs = 2,

	k1, // ?????? need it ???
	kNumerParam =25,
     
};
//---------------------------------------------------------------------------------------
class Program
{
friend class AGain;

public:
	Program();
	~Program() {}

private:
	//float pangle[8];
	char name[24];
};
//-----------------------------------------------------------------------------------------

class AGain : public AudioEffectX
{

public:
	AGain(audioMasterCallback audioMaster);
	~AGain();
    
	virtual void process(float **inputs, float **outputs, long sampleframes);
	virtual void processReplacing(float **inputs, float **outputs, long sampleframes);
	virtual long processEvents(VstEvents* events);
    
	//virtual void setProgram(long program);
	//virtual void setProgramName(char *name);
	//virtual void getProgramName(char *name);
	virtual void setParameter(long index, float value);
	virtual float getParameter(long index);
	virtual void getParameterLabel(long index, char *label);
	virtual void getParameterDisplay(long index, char *text);
	virtual void getParameterName(long index, char *text);
	virtual void setSampleRate(float sampleRate);
	virtual void setBlockSize(long blockSize);
	virtual void resume();
	virtual long getChunk(void** data, bool isPreset) ;//{return 0;}	
	// returns byteSize	
	virtual long setChunk(void* data, long byteSize, bool isPreset); 
	 

	//virtual bool getOutputProperties (long index, VstPinProperties* properties);
	//virtual bool getProgramNameIndexed (long category, long index, char* text);
	//virtual bool copyProgram (long destination);
	virtual bool getEffectName (char* name);
	virtual bool getVendorString (char* text);
	virtual bool getProductString (char* text);
	virtual long getVendorVersion () {return 1;}
	virtual long canDo (char* text);
	

	////
	Engine *engine;
	//Program* programs;

};
//-----------------------------------------------------------------------------------------
#define USELESS __asm nop

#endif