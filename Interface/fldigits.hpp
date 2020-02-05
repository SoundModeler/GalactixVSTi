/*
SIMPLE MENU-LIST CONTROL
ALEX K NOV-2001
*/
//-----------------------------------------------------------------------------------------
#define CONTROLCLS FLDigts     ////CLASS NAME (TO EDIT)
#define BMPWIDTH 14             ////BITMAP LENGH (TO EDIT)
#define BMPHIGH 12              ////HIGH OF BITMAP (TO EDIT)
#define WM_FLDIGITS 121917        ////MESSAGE TO PARENT (TO EDIT)
#define CNTRLCLSNAME "fldigits_" ////CLASS NAME TO REGISTER (TO EDIT)
#define MAXITEMS  16            ////MAXIMUM ITEMS IN LIST 
#define BKGR RGB(71,93,154) ///(0,30,108) //////BACKGROUND COLOR (178,199,192)
#define TXTCLR RGB(137,201,186)     ////TEXT COLOR (5,54,6)
#define BORDERCLR RGB(17,72,16) /////BORDER COLOR (5,54,6)
#define STRELKABKGR 30,155,92 ///44,189,41    /////RGB BKGR COLOR OF -> POINTER
#define DEVIDER "."
#define ZEROREPR "0.00"
#define NDIGITS 3

const long decad[4]={10,100,1000,10000};

//-----------------------------------------------------------------------------------------
class CONTROLCLS
{
public:
   CONTROLCLS();

   HWND add_fldigits(HWND hParent, int a,int b,int id,int tabletyp); /// CREATE
   void SetFLDigits(int indx,int listitem);                      /// SET METHOD
   float GetFLDigits(int indx);                      /// GET METHOD
bool ftoa(float value, char *text);
private:              ////   DONT EDIT BELOW
   
   char lpR1[64][16];
   int nachit;////////// starting params when mouse is down
   int nachan;//// starting params when mouse is down
   int isrotate[64];

   int LEN_MENULST[64];
   HWND nHns_lbs[64];
   float ang_lbs[64];
   float MAXVAL[64];
   float MINVAL[64];
   HANDLE hBMP_lbs;
   RECT RectText[64];
   RECT rect;
   HPEN hpen;
   HBRUSH brsh_bap ;
   LOGFONT cf_vw;
   HFONT font_vw;
   int handle2index_lbs(HWND hS);
   int gaa_lbs (HWND hWin, int ind);
   static LONG CALLBACK HandleMenuList(HWND hWlb, UINT msg, WPARAM wParam, LPARAM lParam);

};
//-----------------------------------------------------------------------------------------
extern void* hInstance;
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
CONTROLCLS::CONTROLCLS()
{
nachit=0; 
nachan=0;
hBMP_lbs=0;
rect.left=0;
rect.right=0;
rect.bottom=0;
rect.top=0;
hpen=0;
brsh_bap =0;
///cf_vw=0;
font_vw=0;
for (long j=0;j<64;++j) 
{
ang_lbs[j]=0.f;
nHns_lbs[j]=0;
LEN_MENULST[j]=0;
isrotate[j]=0;
MAXVAL[j]=0;
MINVAL[j]=0;
RectText[j].left=0;
RectText[j].right=0;
RectText[j].bottom=0;
RectText[j].top=0;
memset(lpR1[j],0,16);
}
 
}
//-----------------------------------------------------------------------------------------
int CONTROLCLS::handle2index_lbs(HWND hS)
{
int k=0;
while (hS!=nHns_lbs[k]) ++k;
return k;
}
//-----------------------------------------------------------------------------------------
bool CONTROLCLS::ftoa(float flval, char *text)
{
int a;////total number of digits with only 2 after RADIX
int minu='-';///
char lpRT1[8]={0,0,0,0,0,0,0,0};;
long 	nb[8]={0,0,0,0,0,0,0,0};
long 	nbk[8]={0,0,0,0,0,0,0,0};
	int e;//index
	float miniml= pow(10,-NDIGITS+1);

	         if (fabs(flval)<miniml)
			 {
                         strcpy(text,ZEROREPR);////"0,0";
                         return 1;
		         }

                  for (e=1;e<NDIGITS;++e)
                  {
                  nb[e] = (long) fabs(fmod(flval,(double)1.0)*decad[e-1]);
                  nbk[e]=nb[e]-(10*nb[e-1]);
                  itoa(nbk[e],&lpRT1[e-1],10);
                  }
			for (e=NDIGITS-1;e>1;--e)
			{
		        if (nbk[e]==0) lpRT1[e-1]=' ';
		        if (nbk[e]!=0) break;
		        }
	  if (flval<(-miniml))
	  {
	  text[0]='-';///minus
	  itoa((long) fabs(flval),&text[1],10);
	  }
	  else
        {
		  ///strcat(text,(char*)&bksp);////backspace instead of minus --optional
		  itoa((long) fabs(flval),text,10);
		}

		  strcat(text,DEVIDER);
          strcat(text,lpRT1);

return 0;
}
//-----------------------------------------------------------------------------------------
int CONTROLCLS::gaa_lbs(HWND hWin, int ind)
{
 
    HDC   hdc = GetDC((HWND)hWin);
   
    FillRect( hdc,&rect ,	// pointer to structure with rectangle
            (HBRUSH) brsh_bap // handle to brush
             );        
    SelectObject(hdc,font_vw);
    SetBkColor(hdc,BKGR);			
	SetTextColor( hdc, TXTCLR);
    ftoa(ang_lbs[ind],(char*)lpR1[ind]);
	DrawText( hdc, (char*)lpR1[ind], lstrlen((char*)lpR1[ind]), 
				&RectText[ind],DT_LEFT | DT_VCENTER | DT_SINGLELINE );
////if (ind==8) MessageBox(0,"okokok","OKOK",0);
  
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
			BITMAP bm;
			HDC hdcMemory;
			CONTROLCLS * a = (CONTROLCLS*)GetWindowLong(hWlb, GWL_USERDATA);
            if (a) ind = a->handle2index_lbs(hWlb);
		    hdc = BeginPaint(hWlb, &ps);            
 
			FillRect( hdc,&a->rect ,	// pointer to structure with rectangle
            (HBRUSH) a->brsh_bap // handle to brush
             );

	SelectObject(hdc,a->font_vw);
    SetBkColor(hdc,BKGR);			
	SetTextColor( hdc, TXTCLR);
	a->ftoa(a->ang_lbs[ind],(char*)a->lpR1[ind]);
	DrawText( hdc, (char*)a->lpR1[ind], lstrlen((char*)a->lpR1[ind]), 
				&a->RectText[ind],DT_LEFT | DT_VCENTER | DT_SINGLELINE );
            
            ReleaseDC(hWlb, hdc);
	        EndPaint(hWlb, &ps);
			}
			return 0L; 
      case WM_LBUTTONDOWN:
			 {
		 SetCursor(LoadCursor(NULL,0));
         SetCapture(hWlb);
		 	CONTROLCLS * a = (CONTROLCLS*)GetWindowLong(hWlb, GWL_USERDATA);
            if (a) ind = a->handle2index_lbs(hWlb);
		 a->isrotate[ind]=1;
		 a->nachit=(short int)HIWORD(lParam);
		 a->nachan=a->ang_lbs[ind];
         a->gaa_lbs(hWlb,ind);/////a->angle_hsl[ind]);
			 }
         return 0;

         case WM_LBUTTONUP:
			 {
		 SetCursor(LoadCursor(NULL, IDC_ARROW));
	     	CONTROLCLS * a = (CONTROLCLS*)GetWindowLong(hWlb, GWL_USERDATA);
            if (a) ind = a->handle2index_lbs(hWlb);
		 a->isrotate[ind]=0;
	     ReleaseCapture();
          a->gaa_lbs(hWlb,ind);
		 
			 }
         break;

            case WM_MOUSEMOVE:
            if (wParam==MK_LBUTTON	)
            {
			CONTROLCLS * a = (CONTROLCLS*)GetWindowLong(hWlb, GWL_USERDATA);
            if (a) ind = a->handle2index_lbs(hWlb);
				/////////////
				a->ang_lbs[ind]=0.5f*(short int) (0.4f*(a->nachit-(short int)HIWORD(lParam))) + a->nachan ;

				if (a->ang_lbs[ind]>a->MAXVAL[ind]) 
					a->ang_lbs[ind]=a->MAXVAL[ind];
				if (a->ang_lbs[ind]<a->MINVAL[ind]) a->ang_lbs[ind]=a->MINVAL[ind];

				//////////////
				a->gaa_lbs(hWlb,ind);
			msg=WM_FLDIGITS;
			lParam=(int)(64.f+a->ang_lbs[ind]*2);
			wParam=ind;
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
 
   ///// back to windows procedure of parent window
	return CallWindowProc((WNDPROC)  GetWindowLong((HWND)GetParent(hWlb), GWL_WNDPROC),	
    hWlb,msg,wParam,lParam );
}
//-----------------------------------------------------------------------------------------
float CONTROLCLS::GetFLDigits(int indx)
{
   return ang_lbs[indx];
} 
//-----------------------------------------------------------------------------------------
void CONTROLCLS::SetFLDigits(int ind,int val)
{
 if (nHns_lbs[ind]!=NULL)
	{
	 ///val -46---174
     //ang_lbs[ind]=(float)(MAXVAL[ind]-MINVAL[ind])*(64-val)*0.005f;
     ang_lbs[ind]=0.5f*(val-64);///--- to chto vidno na displaye
	 //-55=0.5*(x-64)

	 /////ang_lbs[ind]/(0.005f*(MAXVAL[ind]-MINVAL[ind])
	 ///MINSTEPTUNE*(64-tune1)

	 InvalidateRect(nHns_lbs[ind], &RectText[ind],TRUE);
	//if (ind==8) MessageBox(0,"gaa now","OK",0);
    gaa_lbs(nHns_lbs[ind],ind);
 }

} ///
//-----------------------------------------------------------------------------------------
HWND CONTROLCLS::add_fldigits(HWND hParent, int a,int b,int id,int tabletyp)
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

	MAXVAL[id]=55;
    MINVAL[id]=-55;
    
    memset(&wc_id,0,sizeof(wc_id));
	wc_id.lpfnWndProc       =      HandleMenuList;
	wc_id.style             =      0;
	wc_id.lpszMenuName      =      NULL;
	wc_id.hInstance         =      (HINSTANCE) hInstance;
	wc_id.cbWndExtra        =      0;
	wc_id.hCursor           =      NULL;///LoadCursor(NULL, IDC_ARROW);
	wc_id.hbrBackground     =  NULL;//(HBRUSH) CreateSolidBrush(BKGR);
	wc_id.lpszClassName     = (LPSTR) cl_nm;///
   
   LEN_MENULST[id]= 31;
   ///if (tabletyp==2) LEN_MENULST[id]= 50;

   RegisterClass(&wc_id);

   hwnD = CreateWindow  (///WS_EX_CLIENTEDGE,
   (LPSTR) cl_nm, (LPSTR) NULL,
   WS_CHILD | WS_VISIBLE,///| WS_CLIPSIBLINGS,
   a,b,LEN_MENULST[id],BMPHIGH+4,
   (HWND)hParent,(HMENU) (int) id+770,
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
			
		     ////hBMP_lbs = extro_lbs(hhDC,(char*)BITMAPARRAY);
		     SetMapMode(hhDC,MM_TEXT );
            // ReleaseDC(hwnD, hhDC);

             COLORREF cpix;
			 cpix=BORDERCLR;
			 hpen= CreatePen(0,1,cpix);//////  

RectText[id].left=4;
RectText[id].right=LEN_MENULST[id];///-BMPWIDTH-3;
RectText[id].bottom=BMPHIGH-1;
RectText[id].top=0;

rect.left=0;
rect.right=LEN_MENULST[id];
rect.bottom=BMPHIGH-1;
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
 
             ///ang_lbs[id]=0;
	         //gaa_lbs(hwnD,id);
    nHns_lbs[id]=hwnD;
    ///if (nHns_lbs[id]==NULL) MessageBox(0,"REALYWEARD","ERR",0);

return hwnD;
}
//-----------------------------------------------------------------------------------------
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
#undef  DEVIDER  
#undef  ZEROREPR  
#undef  NDIGITS 
//-----------------------------------------------------------------------------------------
