#ifndef __inc_editor__
#define __inc_editor__

#ifndef __AEffEditor__
#include "AEffEditor.hpp"
#
#endif

//-----------------------------------------------------------------------------------------
class Editor : public AEffEditor 
{
	public:
		Editor (AudioEffect* effect);
		~Editor ();
	void SetExemplyar(int);
	void SetNoteOn( int note); 
    void SetNoteOff( int note);
	void SetAllNoteOff();
	void SetVolume(int volm);
	void SetKnob(int index, int val);
    void SetWheel(int index, int val);
	void SetProgrammu(int pgnum);
	   
		virtual void update();
		virtual void setValue (long index, float value);
		virtual long open (void* ptr);		
		virtual void close ();
		virtual void setParameter (long index, float value);
        virtual long getRect (ERect **erect);

	private:
		int Exemplyar;///// important guy
	
};
//-----------------------------------------------------------------------------------------
#
#endif