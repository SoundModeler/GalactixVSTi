#include "editor.h"
#include "again.hpp"
#include <windows.h>
//-----------------------------------------------------------------------------------------
#include "..\Interface\EditorVST.hpp"
//-----------------------------------------------------------------------------------------
/// 

//-----------------------------------------------------------------------------------------
Editor::Editor (AudioEffect* fx) : AEffEditor(fx)
{
 ///MessageBox(0,"Editor::Editor","Editor::Editor",0);
 if (0==curv) curv =new Craftvs;
 if (0==dg)   dg   =new Digits;
 if (0==kn)   kn   =new Knob ;
 if (0==kbrd) kbrd =new Keyboard ;
 if (0==mnl)  mnl =new MenuList ;
 if (0==fldg) fldg =new FLDigts;
 if (0==whl)  whl=new Wheel;
 if (0==rtx)  rtx=new RunTxt;
 if (0==knsm) knsm=new KnobSm;
 if (0==ldbtn) ldbtn=new LedButton;

 fx ->setEditor(this);
}
//-----------------------------------------------------------------------------------------
long Editor::getRect (ERect **erect)
{
    static ERect r={0,0,kEditorHeight,kEditorWidth};
    *erect = &r;
    return true;
}
//-----------------------------------------------------------------------------------------
Editor::~Editor ()
{
//////////////
}
//-----------------------------------------------------------------------------------------
void Editor::close ()
{
//////////////
}
//-----------------------------------------------------------------------------------------
long Editor::open (void* ptr)
{
     systemWindow = ptr;
	 CreateEditor((HWND)systemWindow,Exemplyar);
	 ////SetProgrammu(
	 ///((Engine*) GEFFECT[Exemplyar] )->getCurrentProg());///BUG !!!!!!
	 
	 Updatef(Exemplyar);
	 return true;

}
//-----------------------------------------------------------------------------------------
void Editor::setParameter (long index, float value)
{	
//////////////////
	setValue( index,  value);
}
//-----------------------------------------------------------------------------------------
void Editor::setValue(long index, float value)
{				
  ///long Exemplyar=0;
  switch (index)
  {

  case 0:kn->SetKnobValue( 8*Exemplyar+7,(long)(value*127));break;//rev wet
  case 1:kn->SetKnobValue( 8*Exemplyar+6,(long)(value*127));break;//rev sz
  case 2:kn->SetKnobValue( 8*Exemplyar+5,(long)(value*127));break;//chor

  case 3:fldg->SetFLDigits( 8*Exemplyar,  (long)(value*220-46));break;///tune
  case 4:fldg->SetFLDigits( 8*Exemplyar+1,(long)(value*220-46));break;
  case 5:fldg->SetFLDigits( 8*Exemplyar+2,(long)(value*220-46));break;
  case 6:fldg->SetFLDigits( 8*Exemplyar+3,(long)(value*220-46));break;
  case 7:fldg->SetFLDigits( 8*Exemplyar+4,(long)(value*220-46));break;
  case 8:fldg->SetFLDigits( 8*Exemplyar+5,(long)(value*220-46));break;

  case 9: kn->SetKnobValue( 8*Exemplyar  ,(long)(value*127));break;//cut0
  case 10:kn->SetKnobValue( 8*Exemplyar+4,(long)(value*127));break;//cut
		    
  case 11:dg->SetDigitsValue ( 8*Exemplyar,   (long)(value*100));break;///GAINS
  case 12:dg->SetDigitsValue ( 8*Exemplyar+1, (long)(value*100));break;
  case 13:dg->SetDigitsValue ( 8*Exemplyar+2, (long)(value*100));break;
  case 14:dg->SetDigitsValue ( 8*Exemplyar+3, (long)(value*100));break;
  case 15:dg->SetDigitsValue ( 8*Exemplyar+4, (long)(value*100));break;
  case 16:dg->SetDigitsValue ( 8*Exemplyar+5, (long)(value*100));break;

  case 17:kn->SetKnobValue( 8*Exemplyar+3,value*127);break;///ATTACK
  case 18:kn->SetKnobValue( 8*Exemplyar+2,value*127);break;///RELEASE 

  case 19:knsm->SetKnobSmValue( 8*Exemplyar  ,(long)(value*127));break;///phase
  case 20:knsm->SetKnobSmValue( 8*Exemplyar+1,(long)(value*127));break;
  case 21:knsm->SetKnobSmValue( 8*Exemplyar+2,(long)(value*127));break;
  case 22:knsm->SetKnobSmValue( 8*Exemplyar+3,(long)(value*127));break;
  case 23:knsm->SetKnobSmValue( 8*Exemplyar+4,(long)(value*127));break;
  case 24:knsm->SetKnobSmValue( 8*Exemplyar+5,(long)(value*127));break;

  }
}
//-----------------------------------------------------------------------------------------
void Editor::update( )
{	
//////////////////
}
//-----------------------------------------------------------------------------------------
void Editor::SetExemplyar(int index )
{	
Exemplyar=index;
//////////////////
}
//-----------------------------------------------------------------------------------------
void Editor::SetNoteOn(int note)  
{	
if (kbrd!=0) kbrd->SetNoteOn(Exemplyar,note);   
//////////////////
}
//-----------------------------------------------------------------------------------------
void Editor::SetNoteOff(int note)  
{	
if (kbrd!=0) kbrd->SetNoteOff(Exemplyar,note);   
//////////////////
}
//-----------------------------------------------------------------------------------------
void Editor::SetAllNoteOff()  
{	
if (kbrd!=0) kbrd->SetAllOff(Exemplyar);   
//////////////////
}
//-----------------------------------------------------------------------------------------
void Editor::SetProgrammu(int pgnum)
{
PROGRAMMSET(Exemplyar,pgnum);
///rtx->SetRuntxtItem(Exemplyar,pgnum);
}
//-----------------------------------------------------------------------------------------
void Editor::SetKnob(int index, int val)
{
if (kn!=0) kn->SetKnobValue( 8*Exemplyar+index,val);
}
//-----------------------------------------------------------------------------------------
void Editor::SetWheel(int index, int val)
{
if (whl!=0) whl->SetWheel( 2*Exemplyar+index,val);
}
//-----------------------------------------------------------------------------------------
void Editor::SetVolume(int volm)
{
if (dg!=0) dg->SetDigitsValue (8*Exemplyar+6, volm);//// 100/127
}
//-----------------------------------------------------------------------------------------