/*
SIMPLE MENU-LIST CONTROL
ALEX K NOV-2001
*/
//-----------------------------------------------------------------------------------------
#define WM_HIDCTRLSWAV 121111
#include "..\Interface\waveview.hpp"
#define CONTROLCLS MenuList     ////CLASS NAME (TO EDIT)
#define BMPWIDTH 14             ////BITMAP LENGH (TO EDIT)
#define BMPHIGH 12              ////HIGH OF BITMAP (TO EDIT)
#define WM_MENULST 121017        ////MESSAGE TO PARENT (TO EDIT)
 
#define CNTRLCLSNAME "mnLst_" ////CLASS NAME TO REGISTER (TO EDIT)
#define BITMAPARRAY bz_mnlst    ////NAME OF BITMAP ARRAY (TO EDIT)
#define MAXITEMS  32            ////MAXIMUM ITEMS IN LIST 
#define BKGR RGB(155,166,250) ///(13,104,10)     ////BACKGROUND COLOR (178,199,192)
#define TXTCLR RGB(57,67,105)     ////TEXT COLOR (5,54,6)
#define BORDERCLR RGB(17,72,16) /////BORDER COLOR (5,54,6)
#define STRELKABKGR 30,155,92 ///44,189,41    /////RGB BKGR COLOR OF -> POINTER
//#define LEN_MENULST 75          /////PHISYCAL LENGH OF CONTROL
#include "..\Engine\wav32.h"
#include "..\Engine\comdo.h"

//-----------------------------------------------------------------------------------------
class CONTROLCLS
{
public:
   CONTROLCLS();
   
   HWND add_menulist(HWND hParent, int a,int b,int id,int tabletyp); /// CREATE
   void SetMenuListItem(int indx,int listitem);                      /// SET METHOD
   int  GetMenuListItem(int indx);                      /// GET METHOD
   int AddMenuListItem(int tabletype,LPSTR nwname);

   bool readWavFile2Osc(LPSTR flnm, int file_order, int exemplyar);
   bool readWavFile(LPSTR flnm, int file_order, int exemplyar);

private:              ////   DONT EDIT BELOW
   bool openNew(int ind,int tabletype);  
   bool EditWav(int ind,int tabletype);

   Waveview *wv;
   float *amp;
   float *sp;
   float *specim, *temp;

   int tabletype[64];
   int LEN_MENULST[64];
   HWND nHns_lbs[64];
   int ang_lbs[64];
   HANDLE hBMP_lbs;
   RECT RectText[64];
   RECT rect;
   HPEN hpen;
   HBRUSH brsh_bap ;
   LOGFONT cf_vw;
   HFONT font_vw;
   int handle2index_lbs(HWND hS);
   HANDLE extro_lbs(HDC hDC,LPSTR bzin);
   int gaa_lbs (HWND hWin, int ind);
   static LONG CALLBACK HandleMenuList(HWND hWlb, UINT msg, WPARAM wParam, LPARAM lParam);

};
//-----------------------------------------------------------------------------------------
extern void* hInstance;
const long MAXITMS_FACTRY[2]={11,9};
static long MAXITMS[2]={11,9};
LPSTR tblstr[2][32]=////[MAXITEMS]=
{
{
	{"DSF" },
	{"Sin" },
	{"8 sin" },
	{"Saw" } ,
	{"DSF 2" },
	{"Square" },
	{"Dr.Sin"},
	{"A-vowel"},
	{"U-vowel"},
	{"Noise"},
	{"Alex' U"}
},
{
	{"Exponent" },
	{"Slow Attack" },
	{"Pluck" },
	{"Piano-like" },
	{"Flat" },
	{"Chick" },
	{"Flat+LFO" },
	{"Att+Dc"},
	{"Linear"}
}
}
;
///  WIN32_FIND_DATA w32f[32];
//-----------------------------------------------------------------------------------------

//Total :582 bytes.
//-----------------------------------------------------------------------------------------
CONTROLCLS::CONTROLCLS()
{
   for (long j=0;j<64;++j) 
   {
   ang_lbs[j]=0;
   tabletype[j]=0;
   LEN_MENULST[j]=0;
   nHns_lbs[j]=0;
   hBMP_lbs;
   }
   hpen=0;
   brsh_bap=0;
   hBMP_lbs=0;
   wv=new Waveview;
}
//-----------------------------------------------------------------------------------------
int CONTROLCLS::handle2index_lbs(HWND hS)
{
int k=0;
while (hS!=nHns_lbs[k]) ++k;
return k;
}
//-----------------------------------------------------------------------------------------
HANDLE CONTROLCLS::extro_lbs(HDC hDC,LPSTR bzin)
{
	HANDLE htoBmp;
	DWORD dwSize = 0;// Holds size of info structure
    BITMAPFILEHEADER* pBfh = 0;// Bitmap File Header Structure
    BITMAPINFOHEADER* pBih = 0;// Bitmap Info Header (points to beginning of pBmi)
    BITMAPCOREHEADER* pBch = 0;// Bitmap Core Header in case of other format
    BITMAPINFO*pBmi = 0;// Bitmap Info - Header and Colour Table
    BYTE* lpBits = 0;// Will be a pointer to the bitmap bits
    HBITMAP hBitmap = 0;// Bitmap handle which will be returned
    RGBQUAD* pRgb = 0;// Used with colour table
    long nrgbs;
    //////allocating structures
	 pBfh =(BITMAPFILEHEADER*) malloc(sizeof(BITMAPFILEHEADER));
	 pBih =(BITMAPINFOHEADER*) malloc(sizeof(BITMAPINFOHEADER));
	 pBmi =(BITMAPINFO*) malloc(sizeof(BITMAPINFO));

	 ///get BITMAPFILEHEADER - 14 bytes
	    memcpy(pBfh,&bzin[0],sizeof(BITMAPFILEHEADER));
	    if(pBfh->bfType!=0x4d42) // it isn't, free the file header
	    {
       MessageBox(0,"BMP header error","uups",0);
       return 0;
       }

	 ///get BITMAPINFOHEADER    - 40 bytes
	  memcpy(pBih, &bzin[sizeof(BITMAPFILEHEADER)],sizeof(BITMAPINFOHEADER));

	 ///get RGBQUAD
	  nrgbs = (36+pBfh->bfOffBits+sizeof(BITMAPINFOHEADER))/sizeof(RGBQUAD);
	  pRgb = (RGBQUAD*) malloc(nrgbs*sizeof(RGBQUAD));
	  memcpy(pRgb,&bzin[sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)],nrgbs*sizeof(RGBQUAD));

	 ////get BITMAPINFO
	 pBmi->bmiHeader =*pBih;
	 pBmi->bmiColors[0] =*pRgb;

	 htoBmp = CreateDIBitmap(hDC,pBih,CBM_INIT,&bzin[sizeof(BITMAPFILEHEADER)+pBfh->bfOffBits-14],pBmi,DIB_RGB_COLORS);

	 free(pBfh);
	 free(pBih);
	 free(pBmi);
	 return htoBmp;
}
//-----------------------------------------------------------------------------------------
int CONTROLCLS::gaa_lbs(HWND hWin, int ind)
{

    HDC hdc;
    hdc = GetDC((HWND)hWin);
 
    SelectObject(hdc,font_vw);
    SetBkColor(hdc,BKGR);			
	SetTextColor( hdc, TXTCLR);
	DrawText( hdc, tblstr[tabletype[ind]][ang_lbs[ind]], lstrlen(tblstr[tabletype[ind]][ang_lbs[ind]] ), 
				&RectText[ind],DT_LEFT | DT_VCENTER | DT_SINGLELINE );
    /////////////////
    ReleaseDC(hWin, hdc);
return TRUE;
}
//-----------------------------------------------------------------------------------------
LONG CALLBACK CONTROLCLS::HandleMenuList (HWND hWlb, UINT msg, WPARAM wParam, LPARAM lParam)
{
int value=0;
PAINTSTRUCT ps; 
HDC hdc; 
int ind=0;
	switch (msg) {
            case WM_PAINT:
			{
			//BITMAP bm;
			//HDC hdcMemory;
			CONTROLCLS * a = (CONTROLCLS*)GetWindowLong(hWlb, GWL_USERDATA);
            if (a) ind = a->handle2index_lbs(hWlb);
		    hdc = BeginPaint(hWlb, &ps);            
            //GetObject(a->hBMP_lbs, sizeof(bm), &bm);
            //hdcMemory = CreateCompatibleDC(hdc);
            //SelectObject(hdcMemory, a->hBMP_lbs);
			FillRect( hdc,&a->rect ,	// pointer to structure with rectangle
            (HBRUSH) a->brsh_bap // handle to brush
             );

            /*int wdt=a->LEN_MENULST[ind]-1;
            BitBlt( hdc,wdt-BMPWIDTH-1,2,BMPWIDTH,BMPHIGH,hdcMemory,	
            0,0,SRCCOPY);

			SelectObject(hdc,a->hpen);
            //Rectangle
			MoveToEx(hdc, 0  ,0, NULL);
            LineTo(hdc, wdt,0);
            MoveToEx(hdc, wdt  ,0, NULL);
            LineTo(hdc, wdt,BMPHIGH+3);
			MoveToEx(hdc, wdt ,BMPHIGH+3, NULL);
            LineTo(hdc, 0,BMPHIGH+3);
			MoveToEx(hdc, 0,BMPHIGH+3, NULL);
            LineTo(hdc, 0,0);*/

	SelectObject(hdc,a->font_vw);
    SetBkColor(hdc,BKGR);			
	SetTextColor( hdc, TXTCLR);
	DrawText( hdc, tblstr[a->tabletype[ind]][a->ang_lbs[ind]], lstrlen(tblstr[a->tabletype[ind]][a->ang_lbs[ind]] ), 
				&a->RectText[ind],DT_LEFT | DT_VCENTER | DT_SINGLELINE );
            ///DeleteDC(hdcMemory);
            ReleaseDC(hWlb, hdc);
	        EndPaint(hWlb, &ps);
			}
			return 0L; 
            case WM_RBUTTONDOWN:
				{
            CONTROLCLS * a = (CONTROLCLS*)GetWindowLong(hWlb, GWL_USERDATA);
            if (a) ind = a->handle2index_lbs(hWlb);
			if (LOWORD(lParam)>a->LEN_MENULST[ind])///-2-BMPWIDTH)
			{            
            HMENU hMenu;
	        POINT pt;
            hMenu = CreatePopupMenu();             
            if( hMenu )
            {        
			int r=0;
            while (r<MAXITMS[a->tabletype[ind]])///MAXITEMS) 
			{
			AppendMenu( hMenu, MF_STRING | MF_ENABLED, r, tblstr[a->tabletype[ind]][r]);           
			if (tblstr[r]==NULL) break;
			++r;
			}
			AppendMenu( hMenu, MF_SEPARATOR, (UINT)-1, NULL ); 
            AppendMenu( hMenu, MF_STRING | MF_ENABLED, r, "Cancel" );
            GetCursorPos( &pt );           
            TrackPopupMenu( hMenu, TPM_LEFTALIGN | TPM_RIGHTBUTTON,
                               pt.x, pt.y, 0, hWlb, NULL ); 
            DestroyMenu( hMenu );               
            }
			return 0L;
			} else
				{
            
            if (a->ang_lbs[ind]<MAXITMS[a->tabletype[ind]]-1) ++a->ang_lbs[ind];
			if (lstrlen(tblstr[a->tabletype[ind]][a->ang_lbs[ind]] )==0) a->ang_lbs[ind]=0;
			InvalidateRect(hWlb, &a->RectText[ind],TRUE);
			a->gaa_lbs(hWlb,ind);	
			value=a->ang_lbs[ind];
			msg=WM_MENULST;    ///send message
				}
				}
            //return 0L;
			break;

            case WM_LBUTTONDOWN:
				{
            CONTROLCLS * a = (CONTROLCLS*)GetWindowLong(hWlb, GWL_USERDATA);
            if (a) ind = a->handle2index_lbs(hWlb);
			if (LOWORD(lParam)>a->LEN_MENULST[ind]-2-BMPWIDTH)
			{
            HMENU hMenu;
	        POINT pt;
            hMenu = CreatePopupMenu();    
			
            if( hMenu )
            {        
			int r=0;
            while (r<MAXITMS[a->tabletype[ind]]) 
			{
			AppendMenu( hMenu, MF_STRING | MF_ENABLED, r, tblstr[a->tabletype[ind]][r]);           
			if (tblstr[r]==NULL) break;
			++r;
			}
			if (a->tabletype[ind]==0)
			{
            AppendMenu( hMenu, MF_SEPARATOR, (UINT)-1, NULL ); 
            AppendMenu( hMenu, MF_STRING | MF_ENABLED, 254, "View" );
			}
			AppendMenu( hMenu, MF_SEPARATOR, (UINT)-1, NULL ); 
            AppendMenu( hMenu, MF_STRING | MF_ENABLED, 255, "Open new" );
			//}
			AppendMenu( hMenu, MF_SEPARATOR, (UINT)-1, NULL ); 
            AppendMenu( hMenu, MF_STRING | MF_ENABLED, 256, "Cancel" );
            GetCursorPos( &pt );           
            TrackPopupMenu( hMenu, TPM_LEFTALIGN | TPM_RIGHTBUTTON,
                               pt.x, pt.y, 0, hWlb, NULL ); 
            DestroyMenu( hMenu );               
            }
			} else
			{
            if (a->ang_lbs[ind]>0) --a->ang_lbs[ind];
			if (lstrlen(tblstr[a->tabletype[ind]][a->ang_lbs[ind]] )==0) a->ang_lbs[ind]=0;///!!!!!!
			InvalidateRect(hWlb, &a->RectText[ind],TRUE);
			a->gaa_lbs(hWlb,ind);
			value=a->ang_lbs[ind];
			msg=WM_MENULST;    ///send message
			}
            }			
			break;

            case WM_COMMAND:
				{
			if (LOWORD(wParam)==256) return 0;//cancel
			
            CONTROLCLS * a = (CONTROLCLS*)GetWindowLong(hWlb, GWL_USERDATA);         
			if (a) ind = a->handle2index_lbs(hWlb);
			if (LOWORD(wParam)==255) {a->openNew(ind,a->tabletype[ind]); return 0;}//open new
			if (LOWORD(wParam)==254) {a->EditWav(ind,a->tabletype[ind]); 
			msg=WM_HIDCTRLSWAV;    ///send message
			wParam=ind/16;
            lParam=0;
			
			break;}//open new
            
			a->ang_lbs[ind]=LOWORD(wParam);   
			value=LOWORD(wParam);
    hdc =GetDC(hWlb);
	InvalidateRect(hWlb, &a->RectText[ind],TRUE);
	SelectObject(hdc,a->font_vw);
    SetBkColor(hdc,BKGR);			
	SetTextColor( hdc, TXTCLR);
	DrawText( hdc, tblstr[a->tabletype[ind]][a->ang_lbs[ind]], 
		lstrlen(tblstr[a->tabletype[ind]][a->ang_lbs[ind]] ), 
			&a->RectText[ind],DT_LEFT | DT_VCENTER | DT_SINGLELINE );
            ReleaseDC(hWlb, hdc);
			msg=WM_MENULST;    ///send message
				}
            break;

            case WM_ERASEBKGND:   //////Compulsary
            return 0;

          case WM_DESTROY:
		  {
	      char tclnm[30];
	      GetClassName(hWlb,&tclnm[0], 30);
          UnregisterClass(&tclnm[0], (HINSTANCE) GetWindowLong(hWlb, GWL_HINSTANCE));
		  }
	      return FALSE;
	}

   /////// message parameters
   if (msg==WM_MENULST)
   {
   wParam=ind;
   lParam=value;
   ///if (value>MAXITMS[tabletype[ind]]) value=0; ////additional check
   }
   ///// back to windows procedure of parent window
	return CallWindowProc((WNDPROC)  GetWindowLong((HWND)GetParent(hWlb), GWL_WNDPROC),	
    hWlb,msg,wParam,lParam );
}
//-----------------------------------------------------------------------------------------
BOOL CONTROLCLS::AddMenuListItem(int tabletype,LPSTR nwname)
{
    int r=0;
	///tblstr[1][r]
    while((lstrlen((LPSTR)&tblstr[tabletype][r][0])!=0)&&(r< MAXITEMS))
	{
		if (!strcmp((LPSTR)&tblstr[tabletype][r][0],nwname)) return FALSE;
		else ++r;
	}

    if (tblstr[tabletype][r]==NULL) tblstr[tabletype][r]=(char*)malloc(strlen(nwname)+4);
	else {free(tblstr[tabletype][r]) ;tblstr[tabletype][r]=(char*)malloc(strlen(nwname)+4);}
	strcpy((LPSTR)&tblstr[tabletype][r][0],nwname);

	MAXITMS[tabletype]=r+1;

	////remember loaded files
	long order=r-MAXITMS_FACTRY[tabletype];
	long namalen=strlen(nwname);

	memcpy(&ProgrammsContainer[34+order][32*tabletype],nwname,namalen);

    ///MessageBox(0,(char*)&ProgrammsContainer[34+order][32*tabletype],"will  ",0);
    ///if (order==0) MessageBox(0,"right","will  ",0);
	return 1;
}   ///
//-----------------------------------------------------------------------------------------
bool CONTROLCLS::openNew(int index,int tabletype)
{
	      int exemplyar=index/16;

          OPENFILENAME ofn2;       // complicated common dialog box structure
          ZeroMemory(&ofn2, sizeof(OPENFILENAME));
          ofn2.lStructSize = sizeof(OPENFILENAME);
          ofn2.hwndOwner = NULL;
          ofn2.lpstrFile = (char*) calloc(260,sizeof(char));//frees last file name
          ofn2.nMaxFile = 260*sizeof(char);
          ofn2.lpstrFilter ="Wave 32-bit float (*.wav)\0*.*\0"; 
          ///"Wave 16-bit (*.wav)\0*.*\0Wave 24-bit (*.wav)\0*.*\0
          ///Wave 32-bit(*.wav)\0*.*\0Wave 32-bit float (*.wav)\0*.*\0";
          ofn2.lpstrCustomFilter =NULL;///".wav";////
          ofn2.nFilterIndex = 1;
          ofn2.lpstrFileTitle =  NULL;
          ofn2.nMaxFileTitle = 0;
          ofn2.lpstrDefExt = "wav";
          ofn2.lpstrInitialDir = ((Engine*) GEFFECT[exemplyar])->GalactixDir;///NULL;///ReadIniBlock(1);///NULL;
          ofn2.lpstrTitle = "Open wav file:";
          ofn2.Flags = OFN_HIDEREADONLY | OFN_NOCHANGEDIR | OFN_NOTESTFILECREATE | OFN_EXPLORER  | OFN_FILEMUSTEXIST;
          GetOpenFileName(&ofn2);
          ///WriteLastDir(ofn2.lpstrFile,1);///// write directory path used

		   if (strlen(ofn2.lpstrFile)==0) return 0;
 
           if (tabletype==1)		   ////// read wav to envelope
		   {
		   long file_order=MAXITMS[1]-MAXITMS_FACTRY[1];
           readWavFile(ofn2.lpstrFile, file_order,exemplyar);
		   }

		   if (tabletype==0)		   ////// read wav to oscillator
		   {
		   long file_order=MAXITMS[0]-MAXITMS_FACTRY[0];
           readWavFile2Osc(ofn2.lpstrFile, file_order,exemplyar); 
		   }
	 
	return 1;
}
//-----------------------------------------------------------------------------------------

int CONTROLCLS::GetMenuListItem(int indx)
{
   return ang_lbs[indx];
} 
//-----------------------------------------------------------------------------------------
void CONTROLCLS::SetMenuListItem(int ind,int listitem)
{
 if (nHns_lbs[ind]!=NULL)
	{
    ang_lbs[ind]=listitem;
    InvalidateRect(nHns_lbs[ind], &RectText[ind],TRUE);
	//if (ind==8) MessageBox(0,"gaa now","OK",0);
    gaa_lbs(nHns_lbs[ind],ind);
 }

} ///
//-----------------------------------------------------------------------------------------
     ///////// READ WAV FILES FUNCTION UTILS ---------------- Alex K
//-----------------------------------------------------------------------------------------
bool CONTROLCLS::readWavFile(LPSTR flnm, int file_order, int exemplyar)
{

HFILE hndFl1 = _lopen(flnm,0);///
if ((hndFl1==0)|((HANDLE)hndFl1==INVALID_HANDLE_VALUE))  
{MessageBox(0,flnm,"Problem to open file:",0); return FALSE;}
else {

_llseek(hndFl1,0,FILE_BEGIN);//go to start
long flsz= _llseek(hndFl1,0,FILE_END);//go to start
_llseek(hndFl1,0,FILE_BEGIN);//go to start

_lread(hndFl1,&tw,sizeof(tw));///filling out TitleWave struc
long datastart=sizeof(tw);
///////////////////possible errors in format:
     if ((tw.id_riff[0]!=82)|(tw.id_riff[1]!= 73)|(tw.id_riff[2]!= 70)|(tw.id_riff[3]!= 70))
     {
	 MessageBox(0,"This is not RIFF format file.","Format error.",0);
	 return FALSE;
	 }
     if (tw.type[0] != 3)
     {
	 MessageBox(0,"This is not PCM float format.","Format error",0);
	 return FALSE;
	 }

	 if ((tw.id_chuck[0]!=87)|(tw.id_chuck[1]!=65)|(tw.id_chuck[2]!=86)|(tw.id_chuck[3]!=69))
     {
	 MessageBox(0,"This is not WAVE file.","Format error.",0);
	 return FALSE;
	 }

     if (tw.bits[0]!=32)
	 {
	 MessageBox(0,"Program opens only 32-bit float rate audio files","Error",0);
	 return FALSE;
	 }
     if (tw.channels[0]==2) 
     {
	 MessageBox(0,"Program opens only mono files","Error",0);
	 return FALSE;
	 }

	 if ((tw.id_data[0]!=100)|(tw.id_data[1]!=97) |(tw.id_data[2]!=116)|(tw.id_data[3] !=97))
     {
	 //// if data chunk is not following , thanks Bram for finding the bug
	 long toread=32768;
	 if (flsz<toread) toread=flsz;
	 char *bbg;
	 bbg=(char*)malloc(toread);
	 _llseek(hndFl1,0,FILE_BEGIN);//go to start
     _lread(hndFl1,(void*) bbg,toread);
	 for (long j=0;j<toread;++j) 
			 { if ((bbg[j]=='d')&&(bbg[j+1]=='a')&&(bbg[j+2]=='t')&&
				   (bbg[j+3]=='a'))
			 datastart=j+8;
			 }
     memcpy(&tw.len_data,&bbg[datastart-4],sizeof(long));
     free(bbg);	 
	 }

	 if (tw.len_data==0) 
     {
	 MessageBox(0,"Data lengh is zero.","File Format Error",0);
	 return FALSE;
	 }

//////////////////////////////////////////////
	 long read_len=tw.len_data;

     if (tw.len_data>MAXWAVEFILELENGH_BYTES) 
	 {
	 read_len=MAXWAVEFILELENGH_BYTES;
     MessageBox(0,"File is too long and will be truncated.",flnm,0);
	 } 
		 
		     _llseek(hndFl1,datastart,SEEK_SET);//go to start data
              if (NULL!=wavdata[file_order]) free(wavdata[file_order]);
              if (NULL==wavdata[file_order]) wavdata[file_order]=(float*)malloc(read_len+32);
              if (NULL==wavdata[file_order]) 
				  MessageBox(0,"Memory error at readWavFile","Error",0);
			  _lread(hndFl1,(void*) wavdata[file_order],read_len);
				 
			 /////loading loop points
			 long curr=_llseek(hndFl1,0,SEEK_CUR);
			 long rest=flsz-curr;//endfile chunk size			                    
			 char *restpo;
			
             if (rest>sizeof(smpl)) {
			 restpo=(char*) malloc(rest);
             _lread(hndFl1,(void*) restpo,rest);
  
             long smpl_chnk_offset=0;
			 for (long j=0;j<rest;++j) 
			 { if ((restpo[j]=='s')&&(restpo[j+1]=='m')&&(restpo[j+2]=='p')&&
				   (restpo[j+3]=='l'))
			 smpl_chnk_offset=j;
			 }
			 memcpy((void*)&smpl,&restpo[smpl_chnk_offset],sizeof(smpl));
			 ((Engine*) GEFFECT[exemplyar] )->lstart[file_order]=smpl.dwStart;
			 ((Engine*) GEFFECT[exemplyar] )->lend[file_order]=smpl.dwEnd;		
			 free(restpo);

			 } else
			 {
				 MessageBox(0,"Envelope file. No loop points found.",flnm,0);
                 ((Engine*) GEFFECT[exemplyar] )->lstart[file_order]=0;
				 ((Engine*) GEFFECT[exemplyar] )->lend[file_order]=read_len/4;
				 
             
			 }
					 ///end of loading loop points

	       CloseHandle(&hndFl1);///
          /////MAKE SHORT NAME & INSERT TO MENU
	       char vy = 92;// symbol "\"
           char *szStr;
           szStr = strrchr(flnm,(int)vy)+1;//short file name RIGHT WAY
           int ll=strlen(szStr);

           memset((char*)&szStr[ll-4],0,4*sizeof(char));/// remove ".zxc"

		   AddMenuListItem(1,szStr); 
		   ((Engine*) GEFFECT[exemplyar])->wavdata_ptr[file_order]=wavdata[file_order];
		   return TRUE;
		}
 
}
//----------------------------------------------------------------------------------------
bool CONTROLCLS::readWavFile2Osc(LPSTR flnm, int file_order, int exemplyar)
{

HFILE hndFl1 = _lopen(flnm,0);///
if ((hndFl1==0)|((HANDLE)hndFl1==INVALID_HANDLE_VALUE))  
{MessageBox(0,flnm,"Problem to open file:",0); return FALSE;}
else {

_llseek(hndFl1,0,FILE_BEGIN);//go to start
long flsz= _llseek(hndFl1,0,FILE_END);//go to start
_llseek(hndFl1,0,FILE_BEGIN);//go to start

_lread(hndFl1,&tw,sizeof(tw));///filling out TitleWave struc   4920  824

long datastart=sizeof(tw);
///////////////////possible errors in format:
     if ((tw.id_riff[0]!=82)|(tw.id_riff[1]!= 73)|(tw.id_riff[2]!= 70)|(tw.id_riff[3]!= 70))
     {
	 MessageBox(0,"This is not RIFF format file.","Format error.",0);
	 return FALSE;
	 }
     if (tw.type[0] != 3)
     {
	 MessageBox(0,"This is not PCM float format.","Format error",0);
	 return FALSE;
	 }
    
     if (tw.bits[0]!=32)
	 {
	 MessageBox(0,"Program opens only 32-bit float rate audio files","Error",0);
	 return FALSE;
	 }
     if (tw.channels[0]==2) 
     {
	 MessageBox(0,"Program opens only mono files","Error",0);
	 return FALSE;
	 }
	 
	 if ((tw.id_data[0]!=100)|(tw.id_data[1]!=97) |(tw.id_data[2]!=116)|(tw.id_data[3] !=97))
     {
	 //// if data chunk is not following, thanks Bram for finding the bug
 
	 long toread=32768;
	 if (flsz<toread) toread=flsz;
	 char *bbg;
	 bbg=(char*)malloc(toread);
	 _llseek(hndFl1,0,FILE_BEGIN);//go to start
     _lread(hndFl1,(void*) bbg,toread);
	 for (long j=0;j<toread;++j) 
			 { if ((bbg[j]=='d')&&(bbg[j+1]=='a')&&(bbg[j+2]=='t')&&
				   (bbg[j+3]=='a'))
			 datastart=j+8;
			 }
     memcpy(&tw.len_data,&bbg[datastart-4],sizeof(long));
     free(bbg);
	 
	 }
	 if (tw.len_data==0) 
     {
	 MessageBox(0,"Data lengh is zero.","File Format Error",0);
	 return FALSE;
	 }
//////////////////////////////////////////////
	 long read_len=tw.len_data;

     if (tw.len_data>3000) 
	 {
	 read_len=3000;
     MessageBox(0,"File is too long and will be truncated.",flnm,0);
	 } 
		 
		     _llseek(hndFl1,datastart,SEEK_SET);//go to start data
			 
			 //if (amp==NULL)
			 //{
			 sp=(float*)malloc(TABLESIZE*sizeof(float));
			 amp=(float*)malloc(TABLESIZE*sizeof(float));
			 specim=(float*)malloc(TABLESIZE*sizeof(float));
			 temp=(float*)malloc(TABLESIZE*sizeof(float));
             memset(sp,0,TABLESIZE*sizeof(float));
             memset(amp,0,TABLESIZE*sizeof(float));
			 memset(specim,0,TABLESIZE*sizeof(float));
    ///memset(((Engine*) GEFFECT[exemplyar])->prebuild_tbl[11+file_order],0,TABLESIZE*sizeof(float));

			 _lread(hndFl1,(void*) amp,read_len);

		   
			 DFT (read_len/4,amp,sp,specim);

             fft_float(TABLESIZE,1,sp,specim,
				 temp, ((Engine*) GEFFECT[exemplyar])->prebuild_tbl[11+file_order]  
				 );
			 free(sp);
             free(amp);
			 free(specim);
			 free(temp);
			 //}
	         CloseHandle(&hndFl1);///
		    /////MAKE SHORT NAME & INSERT TO MENU
           char vy = 92;// symbol "\"	
           char *szStr;
           szStr = strrchr(flnm,(int)vy)+1;//short file name RIGHT WAY
           int ll=strlen(szStr);

           memset((char*)&szStr[ll-4],0,4*sizeof(char));/// remove ".zxc"

		   AddMenuListItem(0,szStr); 
		   return TRUE;
			 }
			 
    return TRUE;
}
//----------------------------------------------------------------------------------------
//extern HandlesToHide *ht;
//extern void hideCtrls(HandlesToHide* hdh, int ind, int hide_or_show);
    
bool CONTROLCLS::EditWav(int index,int tabletype)
{
    int exemplyar=index/16;
    ///hideCtrls2(hth,exemplyar,0); 
    wv->add_waveview(hPlug[exemplyar], 44,17,exemplyar, index&15);

    return 1;
}
//-----------------------------------------------------------------------------------------
HWND CONTROLCLS::add_menulist(HWND hParent, int a,int b,int id,int tabletyp)
{
	HWND hwnD;
    HDC hhDC;
	WNDCLASS wc_id;
	char *cl_nm;
	char bbuf[8];
	cl_nm = (char*) malloc(32);
	memset(cl_nm,0,32);
	itoa(id,&bbuf[0],10);
	strcat(cl_nm,CNTRLCLSNAME);
	strcat(cl_nm,&bbuf[0]);
    
    memset(&wc_id,0,sizeof(wc_id));
	wc_id.lpfnWndProc       =      HandleMenuList;
	wc_id.style             =      0;
	wc_id.lpszMenuName      =      NULL;
	wc_id.hInstance         =      (HINSTANCE) hInstance;
	wc_id.cbWndExtra        =      0;
	wc_id.hCursor           =      NULL;///LoadCursor(NULL, IDC_ARROW);
	wc_id.hbrBackground     =  NULL;//(HBRUSH) CreateSolidBrush(BKGR);
	wc_id.lpszClassName     = (LPSTR) cl_nm;///
   
   tabletype[id]=tabletyp;
   LEN_MENULST[id]= 63;//75;
   //if (tabletyp==2) LEN_MENULST[id]= 50;

   RegisterClass(&wc_id);

   hwnD = CreateWindow  (///WS_EX_CLIENTEDGE,
   (LPSTR) cl_nm, (LPSTR) NULL,
   WS_CHILD | WS_VISIBLE,///| WS_CLIPSIBLINGS,
   a,b,LEN_MENULST[id]+BMPWIDTH+2,BMPHIGH+4,
   (HWND)hParent,(HMENU) (int) id+200,
   (HINSTANCE)hInstance, NULL);
    if (cl_nm!=NULL) free(cl_nm);
    if(!hwnD)
    {
      MessageBox(0, "Window Creation Failed!", "Error!",
                 MB_ICONEXCLAMATION | MB_OK | MB_SYSTEMMODAL);
      return FALSE;
    }
	         SetWindowLong(hwnD, GWL_USERDATA, (long) this);
             hhDC = GetDC(hwnD);

		     SetMapMode(hhDC,MM_TEXT );

             COLORREF cpix;
			 cpix=BORDERCLR;
			 hpen= CreatePen(0,1,cpix);//////  

RectText[id].left=5;
RectText[id].right=LEN_MENULST[id]-6;
RectText[id].bottom=BMPHIGH;//BMPHIGH+1
RectText[id].top=0;

rect.left=4;
rect.right=LEN_MENULST[id]-4;
rect.bottom=BMPHIGH;
rect.top=0;

cf_vw.lfHeight =(long)(-0.01389f*(BMPHIGH-3) *GetDeviceCaps(hhDC, LOGPIXELSY));///MulDiv(BMPHIGH-3, GetDeviceCaps(hhDC, LOGPIXELSY), 72);
cf_vw.lfWidth= (long) (-0.041667*GetDeviceCaps(hhDC, LOGPIXELSX));//MulDiv(3, GetDeviceCaps(hhDC, LOGPIXELSY), 72);
cf_vw.lfEscapement=0;
cf_vw.lfOrientation= 0;
cf_vw.lfWeight=FW_NORMAL ;
cf_vw.lfItalic=FALSE;
cf_vw.lfUnderline=FALSE;
cf_vw.lfStrikeOut=FALSE;
cf_vw.lfPitchAndFamily= 0	;
strcat(cf_vw.lfFaceName,(char*)"Arial");

	font_vw = CreateFontIndirect(&cf_vw);
    ReleaseDC(hwnD, hhDC);
	brsh_bap =CreateSolidBrush(BKGR);
    nHns_lbs[id]=hwnD;
    ///if (nHns_lbs[id]==NULL) MessageBox(0,"REALYWEARD","ERR",0);


	///if (tabletyp==1) for (int y=0;y<16;++y) MessageBox(0,(LPSTR)&tblstr[1][y][0],"OK",0);
return hwnD;
}
//----------------------------------------------------------------------------------------
#undef CONTROLCLS 
#undef BMPWIDTH 
#undef BMPHIGH  
#undef  CNTRLCLSNAME  
#undef  BITMAPARRAY  
#undef  MAXITEMS   
#undef  BKGR  
#undef  TXTCLR  
#undef  BORDERCLR  
#undef  STRELKABKGR  
#undef  LEN_MENULST 