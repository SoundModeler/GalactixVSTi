/*
SIMPLE MENU-LIST CONTROL
ALEX K NOV-2001
*/
//-----------------------------------------------------------------------------------------
#define CONTROLCLS RunTxt     ////CLASS NAME (TO EDIT)
#define BMPWIDTH 14             ////BITMAP LENGH (TO EDIT)
#define BMPHIGH 12              ////HIGH OF BITMAP (TO EDIT)
#define WM_RUNTXT 126617        ////MESSAGE TO PARENT (TO EDIT)
#define WM_EXPORTWAV 146617        ////MESSAGE TO PARENT (TO EDIT)
#define CNTRLCLSNAME "RunTxt_" ////CLASS NAME TO REGISTER (TO EDIT)
#define MAXITEMS  32            ////MAXIMUM ITEMS IN LIST 
#define BKGR RGB(71,91,154) ///(13,104,10)     ////BACKGROUND COLOR (178,199,192)
#define TXTCLR RGB(171,178,255) ////(232,0,81)     ////TEXT COLOR (5,54,6)
//-----------------------------------------------------------------------------------------
#define shft 60
class CONTROLCLS
{
public:
   CONTROLCLS();

   HWND add_runtxt(HWND hParent, int a,int b,int id); /// CREATE
   void SetRuntxtItem(int indx,int listitem);                      /// SET METHOD
   int  GetRuntxtItem(int indx);                      /// GET METHOD

private:              ////   DONT EDIT BELOW
   int LEN_MENULST[64];
   HWND nHns_lbs[64];
   int ang_lbs[64];
   HANDLE hBMP_lbs;
   RECT RectText[64];
   ///RECT RectTextShifted[64];
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
char progtbl[32][24]=
{
	{"Default " },
	{"Trance Lead " },
	{"Fill-the-bit" },
	{"Electro Piano" },
	{"Virtual Sitar" } ,
	{"Analog Brass" },
	{"Oboe Synth" },
	{"Wind from China"},
    {"Magic Strings"},
    {"Chor"},
	{"Organ"},
    {"Reso Bass"},
	{"Fat Guy"},
	{"Space Dust"},
	{"Elv's Land"},
	{"Cute Alise"},
	{"Melaren Pad"},
    {"Chor 2"},
    {"New Age"},
	{"RGC Audio 1"},
	{"RGC Audio 2"},
	{"RGC Audio 3"},
	{"RGC Audio 4"},
	{"RGC Audio 5"},
	{"RGC Audio 6"},
	{"RGC Audio 7"},
	{"RGC Audio 8"},
	{"RGC Audio 9"},
	{"RGC Audio Organ"},
    {"Empty"},
	{"Empty"}
}
;
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
CONTROLCLS::CONTROLCLS()
{
  for (long j=0;j<64;++j) 
   {
   ang_lbs[j]=0;
   LEN_MENULST[j]=0;
   nHns_lbs[j]=0;
   hBMP_lbs;
   }
   hpen=0;
   brsh_bap=0;
   hBMP_lbs=0;
}
//-----------------------------------------------------------------------------------------
int CONTROLCLS::handle2index_lbs(HWND hS)
{
int k=0;
while (hS!=nHns_lbs[k]) ++k;
return k;
}
//-----------------------------------------------------------------------------------------
int CONTROLCLS::gaa_lbs(HWND hWin, int ind)
{
 
    HDC hdc = GetDC((HWND)hWin);
            
    SelectObject(hdc,font_vw);
    SetBkColor(hdc,BKGR);			
	SetTextColor( hdc, TXTCLR);
	DrawText( hdc, progtbl[ang_lbs[ind]], lstrlen(progtbl[ang_lbs[ind]] ), 
				&RectText[ind],DT_LEFT | DT_VCENTER | DT_SINGLELINE );

  
    /////////////////
    ReleaseDC(hWin, hdc);
return TRUE;
}
//-----------------------------------------------------------------------------------------
LONG CALLBACK CONTROLCLS::HandleMenuList (HWND hWlb, UINT msg, WPARAM wParam, LPARAM lParam)
{
int value=0;
///PAINTSTRUCT ps; 
HDC hdc; 
int ind=0;
	switch (msg) {
	case WM_TIMER:
		{
			CONTROLCLS * a = (CONTROLCLS*)GetWindowLong(hWlb, GWL_USERDATA);
            if (a) ind = a->handle2index_lbs(hWlb);
		    hdc = GetDC(hWlb);////BeginPaint(hWlb, &ps);            
           	++a->RectText[ind].left;
		    //a->RectText[ind].left+=30;
			a->RectText[ind].left&=127;
            //a->RectText[ind].left-=30;
			FillRect( hdc,&a->rect ,	// pointer to structure with rectangle
            (HBRUSH) a->brsh_bap // handle to brush
             );

	SelectObject(hdc,a->font_vw);
    SetBkColor(hdc,BKGR);			
	SetTextColor( hdc, TXTCLR);
	DrawText( hdc, progtbl[a->ang_lbs[ind]], lstrlen(progtbl[a->ang_lbs[ind]] ), 
				&a->RectText[ind],DT_LEFT | DT_VCENTER | DT_SINGLELINE );
    //a->RectTextShifted[ind].left=a->RectText[ind].left-3*lstrlen(progtbl[a->ang_lbs[ind]] );

     //DrawText( hdc, progtbl[a->ang_lbs[ind]], lstrlen(progtbl[a->ang_lbs[ind]] ), 
			//	&a->RectTextShifted[ind],DT_LEFT | DT_VCENTER | DT_SINGLELINE );
            ReleaseDC(hWlb, hdc);
	        ///EndPaint(hWlb, &ps);
			}
			return 0L; 
            case WM_RBUTTONDOWN:
				{
            CONTROLCLS * a = (CONTROLCLS*)GetWindowLong(hWlb, GWL_USERDATA);
            if (a) ind = a->handle2index_lbs(hWlb);
		//	if (LOWORD(lParam)>a->LEN_MENULST[ind]-2-BMPWIDTH)
		//	{            
            HMENU hMenu;
	        POINT pt;
            hMenu = CreatePopupMenu();             
            if( hMenu )
            {        
			int r=0;
            while (strlen(progtbl[r])!=0)
			{
			AppendMenu( hMenu, MF_STRING | MF_ENABLED, r, progtbl[r]);           
			if (progtbl[r]==NULL) break;
			++r;
			}
			AppendMenu( hMenu, MF_SEPARATOR, (UINT)-1, NULL ); 
            AppendMenu( hMenu, MF_STRING | MF_ENABLED, 255, "Edit preset name" );
			AppendMenu( hMenu, MF_SEPARATOR, (UINT)-1, NULL ); 
            AppendMenu( hMenu, MF_STRING | MF_ENABLED, 256, "Cancel" );
            GetCursorPos( &pt );           
            TrackPopupMenu( hMenu, TPM_LEFTALIGN | TPM_RIGHTBUTTON,
                               pt.x, pt.y, 0, hWlb, NULL ); 
            DestroyMenu( hMenu );               
         //   }
			return 0L;
			}
				}
            //return 0L;
			break;

            case WM_COMMAND:
				{
			if (LOWORD(wParam)==256) return 0;//cancel
			
            CONTROLCLS * a = (CONTROLCLS*)GetWindowLong(hWlb, GWL_USERDATA);
            if (a) ind = a->handle2index_lbs(hWlb);
            if (LOWORD(wParam)==255) {msg=WM_EXPORTWAV; wParam=ind; break;}
            a->ang_lbs[ind]=LOWORD(wParam);   
			value=LOWORD(wParam);
    hdc =GetDC(hWlb);
	InvalidateRect(hWlb, &a->RectText[ind],TRUE);
	SelectObject(hdc,a->font_vw);
    SetBkColor(hdc,BKGR);			
	SetTextColor( hdc, TXTCLR);
	DrawText( hdc, progtbl[a->ang_lbs[ind]], 
		lstrlen(progtbl[a->ang_lbs[ind]] ), 
			&a->RectText[ind],DT_LEFT | DT_VCENTER | DT_SINGLELINE );
            ReleaseDC(hWlb, hdc);
			msg=WM_RUNTXT;    ///send message
				}
            break;

            case WM_ERASEBKGND:   //////Compulsary
            return 0;

          case WM_DESTROY:
		  {
	      char tclnm[30];
	      GetClassName(hWlb,&tclnm[0], 30);
          UnregisterClass(&tclnm[0], (HINSTANCE) GetWindowLong(hWlb, GWL_HINSTANCE));
		  KillTimer(hWlb,1);
		  }
	      return FALSE;
	}

   /////// message parameters
   if (msg==WM_RUNTXT)
   {
   wParam=ind;
   lParam=value;
   }
   ///// back to windows procedure of parent window
	return CallWindowProc((WNDPROC)  GetWindowLong((HWND)GetParent(hWlb), GWL_WNDPROC),	
    hWlb,msg,wParam,lParam );
}
//-----------------------------------------------------------------------------------------
int CONTROLCLS::GetRuntxtItem(int indx)
{
   return ang_lbs[indx];
} 
//-----------------------------------------------------------------------------------------
void CONTROLCLS::SetRuntxtItem(int ind,int listitem)
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
HWND CONTROLCLS::add_runtxt(HWND hParent, int a,int b,int id)
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
   
   LEN_MENULST[id]= 140;

   RegisterClass(&wc_id);

   hwnD = CreateWindow  (///WS_EX_CLIENTEDGE,
   (LPSTR) cl_nm, (LPSTR) NULL,
   WS_CHILD | WS_VISIBLE,///| WS_CLIPSIBLINGS,
   a,b,LEN_MENULST[id],BMPHIGH+4,
   (HWND)hParent,(HMENU) (int) id+3200,
   (HINSTANCE)hInstance, NULL);
  

    if (cl_nm!=NULL) free(cl_nm);
    if(!hwnD)
    {
      MessageBox(0, "Window Creation Failed!", "Error!",
                 MB_ICONEXCLAMATION | MB_OK | MB_SYSTEMMODAL);
      return FALSE;
    }
	SetTimer(hwnD,1,100,NULL);
	         SetWindowLong(hwnD, GWL_USERDATA, (long) this);
             hhDC = GetDC(hwnD);
			
		     ////hBMP_lbs = extro_lbs(hhDC,(char*)BITMAPARRAY);
		     SetMapMode(hhDC,MM_TEXT );
            // ReleaseDC(hwnD, hhDC);

             ///COLORREF cpix;
 
			 ///hpen= CreatePen(0,1,cpix);//////  

RectText[id].left=4;
RectText[id].right=LEN_MENULST[id]-BMPWIDTH-3;
RectText[id].bottom=BMPHIGH+1;
RectText[id].top=3;
/*
RectTextShifted[id].left=4;
RectTextShifted[id].right=shft;///LEN_MENULST[id]-BMPWIDTH-3;
RectTextShifted[id].bottom=BMPHIGH+1;
RectTextShifted[id].top=3;
*/
rect.left=0;
rect.right=LEN_MENULST[id];
rect.bottom=BMPHIGH+4;
rect.top=0;

cf_vw.lfHeight =(long)(-0.01389f*(BMPHIGH-4) *GetDeviceCaps(hhDC, LOGPIXELSY));///MulDiv(BMPHIGH-3, GetDeviceCaps(hhDC, LOGPIXELSY), 72);
cf_vw.lfWidth= (long) (-0.041667*GetDeviceCaps(hhDC, LOGPIXELSX));//MulDiv(3, GetDeviceCaps(hhDC, LOGPIXELSY), 72);
cf_vw.lfEscapement=0;
cf_vw.lfOrientation= 0;
cf_vw.lfWeight=FW_NORMAL ;
cf_vw.lfItalic=TRUE;
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
//-----------------------------------------------------------------------------------------
