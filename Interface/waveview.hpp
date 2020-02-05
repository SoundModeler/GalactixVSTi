/*
SIMPLE ON-OFF BUTTON
ALEX K NOV-2001
*/
//-----------------------------------------------------------------------------------------
#define CONTROLCLS Waveview   ////CLASS NAME (TO EDIT)
#define LENGH 204       ////HALF OF BITMAP LENGH (TO EDIT)
#define HIGH 149             ////HIGH OF BITMAP (TO EDIT)
#define BMPHIGH 149
#define BMPLENGH 411 
#define BKGRRGB_R 171
#define BKGRRGB_G 195
#define BKGRRGB_B 255
#define CNTRLCLSNAME "Waveview_" ////CLASS NAME TO REGISTER (TO EDIT)
#define BITMAPARRAY ledbutns    ////NAME OF BITMAP ARRAY (TO EDIT)
#define BKGR RGB(0,114,190) ///(14,15,50)
#define ADSLENGH 411
#define ADSHIGH  149
#define WM_GALACTIX 123982
///#define WM_GALACTIX_BACK  123983
#include <Commctrl.h>

///#include "ads_bk.h"
//-----------------------------------------------------------------------------------------
class CONTROLCLS
{
public:
   CONTROLCLS();

   HWND add_waveview(HWND hParent, int a,int b,int id, int mn_indx);/// CREATE
   BOOL CheckLedbtns(int indx);                      /// SET METHOD
   void RemoveEffectFromScreen(int indx);             /// SET METHOD
   BOOL GetValue(int indx);                          /// GET METHOD

private:              ////   DONT EDIT BELOW
   HWND hwndEff[64];
   inline void replaseRGB(int x, int y, float x_f,float y_f);
   unsigned char *bmprr;
   COLORREF la;
   RECT rect;
   HBRUSH brsh_bap ;
   long Decode(unsigned char *inpak,unsigned char* outdata,long ENDFA);
   HWND nHns_lbs[64];
   HWND nHParent[64];
   int ang_lbs[64];
   HANDLE BMP_ads;
   int handle2index_lbs(HWND hS);
   ///void replaseRGB(int x, int y);
   HANDLE extro_lbs(HDC hDC,LPSTR bzin);
   void gaa_lbs (HWND hWin, int onoff);
   static LONG CALLBACK HandleLedbtns(HWND hWlb, UINT msg, WPARAM wParam, LPARAM lParam);

};
//-----------------------------------------------------------------------------------------
extern void* hInstance;
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
CONTROLCLS::CONTROLCLS()
{
	for (long r=0;r<64;++r)
	{
    nHns_lbs[r]=0;
	nHParent[r]=0;
    ang_lbs[r]=0;
	hwndEff[r]=0;
    }
	BMP_ads=0;


	la=RGB(171,178,255);////(114,190,0);
	brsh_bap =CreateSolidBrush(BKGR);
    rect.left=40;
	rect.top=16;
    rect.right=ADSLENGH+rect.left;
    rect.bottom=ADSHIGH+rect.top;
   
}
//-----------------------------------------------------------------------------------------
int CONTROLCLS::handle2index_lbs(HWND hS)
{
int k=0;
while (hS!=nHns_lbs[k]) ++k;
return k;
}
//-----------------------------------------------------------------------------------------
inline void CONTROLCLS::replaseRGB(int x, int y, float x_f,float y_f)
{
	BYTE * dibits = &bmprr[sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)];
	long RowByteCount = ((((BMPLENGH * 3) -1) / 4) + 1) * 4;
    dibits += (BMPHIGH - y) * RowByteCount;
    dibits += x * 3;
    dibits[0]=BKGRRGB_B;
    dibits[1]=BKGRRGB_G;
    dibits[2]=BKGRRGB_R;

    BYTE * dibits1 = &bmprr[sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)];
	long RowByteCount1 = ((((BMPLENGH * 3) -1) / 4) + 1) * 4;
    dibits1 += (BMPHIGH - y) * RowByteCount1;
    dibits1 += (x+1) * 3;

    x_f=1.f-x_f;
	dibits1[0]=0.3*(BKGRRGB_B+x_f*dibits1[0]);
    dibits1[1]=0.3*(BKGRRGB_G+x_f*dibits1[1]);
    dibits1[2]=0.3*(BKGRRGB_R+x_f*dibits1[2]);

	BYTE * dibits2 = &bmprr[sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)];
	long RowByteCount2 = ((((BMPLENGH * 3) -1) / 4) + 1) * 4;
    dibits2 += (BMPHIGH - y-1) * RowByteCount2;
    dibits2 += x  * 3;

    y_f=1.f-y_f;
	dibits2[0]=0.3*(BKGRRGB_B+y_f*dibits2[0]);
    dibits2[1]=0.3*(BKGRRGB_G+y_f*dibits2[1]);
    dibits2[2]=0.3*(BKGRRGB_R+y_f*dibits2[2]);
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
long CONTROLCLS::Decode(unsigned char *inpak,unsigned char* outdata,long ENDFA)
{
	int  i;
	int j;
	int k;
	int r;
	int c;
//	int N=4096;
	//int F=18;
//	int THRESHOLD=2;
	unsigned char text_buf[4113];	/* ring buffer of size N */

	unsigned int  flags;
	long y=0;
	long yt=0;
	long yz=0;
	for (i = 0; i < 4096 - 18; i++) text_buf[i] = ' ';

	r = 4096 - 18;  flags = 0;
	for ( ; ; ) {
		if (((flags >>= 1) & 256) == 0) {
			  if (yt++==ENDFA) break;
			  c=inpak[y++];
			  flags = c | 0xff00;
		}
		if (flags & 1)
		    {
			if (yt++==ENDFA) break;
			c=inpak[y++];
			outdata[yz++]=(unsigned char)c;///=w
		    text_buf[r++] = c;  r &= (4096 - 1);
		} else {
			  if (yt++==ENDFA) break;
			  i=inpak[y++];
			if (yt++==ENDFA) break;
			j=inpak[y++];
			i |= ((j & 0xf0) << 4);
		    j = (j & 0x0f) + 2;
			for (k = 0; k <= j; k++)
			    {
				c = text_buf[(i + k) & (4096 - 1)];
				outdata[yz++]=(unsigned char)c;///=w
			    text_buf[r++] = c;  r &= (4096 - 1);
			}
		}
	}
	return y;
}

//-----------------------------------------------------------------------------------------
void CONTROLCLS::gaa_lbs (HWND hWin, int onoff)
{
   BITMAP bm;
   HDC hdc;
   HDC hdcMemory;
   GetObject(BMP_ads, sizeof(bm), &bm);
   hdc = GetDC((HWND)hWin);
   hdcMemory = CreateCompatibleDC(hdc);
   SelectObject(hdcMemory, BMP_ads);

    BitBlt(hdc,0,0,LENGH,HIGH,hdcMemory,205,0,SRCCOPY);
    DeleteDC(hdcMemory);
    /////////////////
    ReleaseDC(hWin, hdc);
}
//-----------------------------------------------------------------------------------------
LONG CALLBACK CONTROLCLS::HandleLedbtns (HWND hWlb, UINT msg, WPARAM wParam, LPARAM lParam)
{
PAINTSTRUCT ps; 
HDC hdc; 
long ind=0;
long value=0;
TRACKMOUSEEVENT tme;
	switch (msg) {

            case WM_PAINT:
			{
			CONTROLCLS * a = (CONTROLCLS*)GetWindowLong(hWlb, GWL_USERDATA);
            if (a) ind = a->handle2index_lbs(hWlb);
		    hdc = BeginPaint(hWlb, &ps);            
            BITMAP bm;
			HDC hdcMemory;
			GetObject(a->BMP_ads, sizeof(bm), &bm);
            hdcMemory = CreateCompatibleDC(hdc);
            SelectObject(hdcMemory, a->BMP_ads);
			BitBlt(hdc,0,0,LENGH,149,hdcMemory,205,0,SRCCOPY);
            ////int r=5/(a->ang_lbs[ind]-1);
			DeleteDC(hdcMemory);
            ReleaseDC(hWlb, hdc);
	        EndPaint(hWlb, &ps);
			}
			return 0L;
			
            case WM_MOUSELEAVE:
				{
 	        CONTROLCLS * a = (CONTROLCLS*)GetWindowLong(hWlb, GWL_USERDATA);
            if (a) ind = a->handle2index_lbs(hWlb);
			a->ang_lbs[ind]=0;
	        a->gaa_lbs(hWlb ,a->ang_lbs[ind]);
				}
			return 0;

            case WM_MOUSEMOVE:
			{
            tme.cbSize = sizeof(TRACKMOUSEEVENT);
            tme.dwFlags = TME_LEAVE;
            tme.hwndTrack = hWlb;
            _TrackMouseEvent(&tme);

			CONTROLCLS * a = (CONTROLCLS*)GetWindowLong(hWlb, GWL_USERDATA);
            if (a) ind = a->handle2index_lbs(hWlb);
			a->ang_lbs[ind]=1;
	        a->gaa_lbs(hWlb ,a->ang_lbs[ind]);
            }
			break;

            case WM_LBUTTONDOWN:
			{
			CONTROLCLS * a = (CONTROLCLS*)GetWindowLong(hWlb, GWL_USERDATA);
			if (a) ind = a->handle2index_lbs(hWlb);
		    //msg=WM_HIDCTRLSWAV;    ///send message
		    //wParam=ind;
            //lParam=0;
			SendMessage(hWlb,WM_HIDCTRLSWAV,ind,1);///show ctrls again
			DestroyWindow(hWlb);
			}
			return 1;

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

   ///// back to windows procedure of parent window
	return CallWindowProc((WNDPROC)  GetWindowLong((HWND)GetParent(hWlb), GWL_WNDPROC),	
    hWlb,msg,wParam,lParam );
}
//-----------------------------------------------------------------------------------------
BOOL CONTROLCLS::GetValue(int indx)
{
   return ang_lbs[indx];
} 
//-----------------------------------------------------------------------------------------
void CONTROLCLS::RemoveEffectFromScreen(int indx)
{
 
} ///
//-----------------------------------------------------------------------------------------
BOOL CONTROLCLS::CheckLedbtns(int indx)
{

BOOL val;
++ang_lbs[indx];
ang_lbs[indx]&=0x01;
val = ang_lbs[indx];
gaa_lbs(nHns_lbs[indx] ,ang_lbs[indx]);

return val;
} ///
//-----------------------------------------------------------------------------------------
HWND CONTROLCLS::add_waveview(HWND hParent, int a,int b,int id, int mn_indx)
{
	if (hParent==0) MessageBox(0, "hParen==0", "Error!", 0);
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
	wc_id.lpfnWndProc       =      HandleLedbtns;//DefWindowProc;//HandleLedbtns;//
	wc_id.style             =      0;
	wc_id.lpszMenuName      =      NULL;
	wc_id.hInstance         =      (HINSTANCE) hInstance;
	wc_id.cbWndExtra        =      0;
	wc_id.hCursor           =      0;///LoadCursor(NULL, IDC_ARROW);
	wc_id.hbrBackground     =  NULL;///(HBRUSH) CreateSolidBrush(RGB(12,12,12));
	wc_id.lpszClassName     = (LPSTR) cl_nm;///
   
   RegisterClass(&wc_id);
   hwnD = CreateWindow  (///WS_EX_CLIENTEDGE,
   (LPSTR) cl_nm, (LPSTR) NULL,
   WS_CHILD | WS_VISIBLE,///| WS_CLIPSIBLINGS,
   a,b,LENGH,HIGH,
   (HWND)hParent,(HMENU) (int) id+1690,
   (HINSTANCE)hInstance, NULL);



    if(!hwnD)
    {
      MessageBox(0, "Window Creation Failed!", "Error!",
                 MB_ICONEXCLAMATION | MB_OK | MB_SYSTEMMODAL);
      return FALSE;
    }
	
/*SendMessage(CreateWindow ("BUTTON", (LPSTR) "OK",\
                          WS_CHILD | WS_VISIBLE | WS_BORDER|BS_FLAT ,\
						  135,15,45,20,\
                          (HWND) hwnD,(HMENU) (int) 888,\
						  (HINSTANCE) GetWindowLong((HWND)hwnD, GWL_HINSTANCE),(WNDPROC) HandleLedbtns)\
,WM_SETFONT,(WPARAM) (HANDLE) GetStockObject(ANSI_VAR_FONT),TRUE);
*/	
	
	
	         SetWindowLong(hwnD, GWL_USERDATA, (long) this);
	         if (cl_nm!=NULL) free(cl_nm);             
			 /////// --------- EXCLUDE BACKGROUND PIXELS

             /////// ---------

             hhDC = GetDC(hwnD);
	         bmprr=(unsigned char*)malloc(196608);
			 Decode(ads_bk,bmprr,34056);
			 long exemplyar=id;
			 long osctype=((Engine*) GEFFECT[exemplyar])->curent_osc_type[mn_indx];
			  		               
             long RowByteCount = ((((BMPLENGH * 3) -1) / 4) + 1) * 4;

for (long r=0;r<TABLESIZE;++r) 
{
	//replaseRGB(r+205,0.5f*HIGH*(1.f-((Engine*) GEFFECT[exemplyar])->prebuild_tbl[osctype][r*TABLESIZE/LENGH]));
	float x_f=(float)LENGH*r/TABLESIZE+205;
	float y_f=(float)HIGH*(0.5f-0.4f*((Engine*) GEFFECT[exemplyar])->prebuild_tbl[osctype][r]);
	long x=(long) x_f;
	long y=(long) y_f;
    x_f-=x;
    y_f-=y;
	//replaseRGB(x,y,xf,yf);	
	BYTE * dibits = &bmprr[sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)];  
	BYTE * dibits1 =&bmprr[sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)];  
	BYTE * dibits2 =&bmprr[sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)];  
	
    dibits +=  (BMPHIGH - y) * RowByteCount;
    dibits += x * 3;
    dibits[0]=BKGRRGB_B;
    dibits[1]=BKGRRGB_G;
    dibits[2]=BKGRRGB_R;

    dibits1 += (BMPHIGH - y) * RowByteCount;
    dibits1 += (x+1) * 3;

    x_f=1.f-x_f;
	dibits1[0]=0.3*(BKGRRGB_B+x_f*dibits1[0]);
    dibits1[1]=0.3*(BKGRRGB_G+x_f*dibits1[1]);
    dibits1[2]=0.3*(BKGRRGB_R+x_f*dibits1[2]);

    dibits2 += (BMPHIGH - y-1) * RowByteCount;
    dibits2 += x  * 3;

    y_f=1.f-y_f;
	dibits2[0]=0.3*(BKGRRGB_B+y_f*dibits2[0]);
    dibits2[1]=0.3*(BKGRRGB_G+y_f*dibits2[1]);
    dibits2[2]=0.3*(BKGRRGB_R+y_f*dibits2[2]);
}    
			

			    BMP_ads=extro_lbs(hhDC,(char*)bmprr);
	            ReleaseDC(hwnD, hhDC);
                free(bmprr);

             //ang_lbs[id]=0;
	         //gaa_lbs(hBMP_lbs, hwnD,0);
             nHns_lbs[id]=hwnD;
			 nHParent[id]=hParent;

return hwnD;
}
//-----------------------------------------------------------------------------------------
#undef CONTROLCLS 
#undef LENGH  
#undef HIGH  
#undef BMPHIGH  
#undef BMPLENGH  
#undef BKGRRGB_R  
#undef BKGRRGB_G  
#undef BKGRRGB_B  
#undef CNTRLCLSNAME  
#undef BITMAPARRAY 
#undef BKGR  
#undef ADSLENGH  
#undef ADSHIGH 

//-----------------------------------------------------------------------------------------
