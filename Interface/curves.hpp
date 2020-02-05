/*
SIMPLE CURVE-BUTTONS CONTROL
ALEX K NOV-2001
*/
//-----------------------------------------------------------------------------------------
#define CKRV Craftvs     ////CLASS NAME (TO EDIT)
#define BMPLENCRV 19              ////HALF OF BITMAP LENGH (TO EDIT)
#define BMPHIGHCRV 19                ////HIGH OF BITMAP (TO EDIT)
#define MXPCTRES 10          ///number of picktures in mooves
#define MXINTVLUE 10         ///max value to be passed to main window as lParam
#define WM_CURVUP 121722 
#define CNCLSNAME "rftvs_"  ////CLASS NAME TO REGISTER (TO EDIT)
#define BTMPARAY z_curvs     ////NAME OF BITMAP ARRAY (TO EDIT)
//-----------------------------------------------------------------------------------------
class CKRV
{
public:
   CKRV();

   HWND  add_curves(HWND hParent, int a,int b,int id);/// CREATE
   void  SetCurvesValue(int ind, int val);            /// SET METHOD
   int   GetCurvesValue(int indx);                      /// GET METHOD

   private:              ////   DONT EDIT BELOW
   HWND slHns[64];///ctrl handles
   float angle[64];///values (0-100)
   int changle[64];///values (0-100)
   int nachit;////////// starting params when mouse is down
   int nachan;//// starting params when mouse is down

   int isrotate[64];
   HANDLE BMPhsl;

   long Decode(unsigned char *inpak,unsigned char* outdata,long ENDFA);
   HANDLE extro_lbs(HDC hDC,LPSTR bzin);
   void gaa(HWND hWin, int high_pos);
   int handle2index_sl(HWND hS);
   static LONG CALLBACK HandleKnob(HWND hWlb, UINT msg, WPARAM wParam, LPARAM lParam);

};
//-----------------------------------------------------------------------------------------
extern void* hInstance;   ///BKGRGB
//-----------------------------------------------------------------------------------------
unsigned char BTMPARAY[]  = { 95,
66,77,170,42,0,242,242,54,242,240,213,40,242,240,190,242,240,19,242,240,1,0,53,24,242,242,116,241,240,196,14,18,3,26,6,31,129,44,
0,111,19,39,15,57,15,72,10,3,156,69,36,15,108,15,126,15,90,15,162,15,180,15,0,144,15,216,15,234,15,198,15,14,31,32,31,252,
15,68,31,0,86,31,50,31,101,31,140,31,104,31,122,31,194,31,212,31,128,176,31,248,31,10,47,230,31,46,47,64,47,28,39,0,63,0,
136,49,0,180,94,99,47,117,47,6,132,42,116,24,96,47,168,47,186,47,150,47,222,47,0,240,47,204,47,20,63,38,63,2,63,74,63,92,
63,56,63,0,128,63,146,63,110,63,161,63,200,63,164,63,182,63,254,63,0,16,79,236,63,52,79,70,79,34,79,106,79,124,79,88,71,0,
95,47,170,79,188,79,93,79,224,79,242,79,206,79,22,95,0,40,95,4,95,76,95,94,95,58,95,106,95,148,95,112,95,48,130,95,202,95,
166,95,184,85,124,41,221,95,10,111,0,230,95,46,111,64,111,28,111,79,111,118,111,82,111,100,111,24,172,111,190,111,151,67,134,51,193,103,
249,95,244,111,0,149,102,217,99,229,111,39,127,3,127,21,115,81,118,54,127,0,108,127,15,118,21,127,153,127,117,127,168,127,207,127,171,127,
0,189,127,5,143,23,143,129,127,59,143,77,143,69,127,83,143,0,131,143,95,143,167,140,140,143,146,143,53,143,236,143,200,143,127,0,0,144,
59,0,181,96,49,143,0,41,159,142,109,21,147,33,159,99,159,63,159,24,150,107,143,0,162,159,126,159,153,159,216,159,180,159,138,153,8,175,
26,175,0,132,159,62,175,80,175,44,175,201,159,134,175,98,175,147,159,0,188,175,152,175,200,175,176,175,206,175,252,147,248,175,46,191,254,143,
75,147,63,0,190,107,0,187,15,104,0,186,101,30,177,252,159,111,191,152,99,24,81,179,31,176,90,176,184,100,95,191,167,191,131,186,0,87,
179,150,179,31,191,228,191,192,188,93,191,23,207,243,191,0,147,191,77,207,41,207,59,207,131,207,95,207,198,185,8,195,0,146,207,149,207,110,
207,213,191,1,223,221,207,125,204,245,175,224,16,223,58,208,37,223,109,223,70,185,66,0,194,127,114,0,194,111,0,193,109,143,191,32,167,223,
128,184,142,210,58,208,150,208,189,32,223,226,223,0,190,219,147,211,210,211,173,131,222,223,240,223,144,223,219,223,0,38,239,255,223,74,239,146,
239,110,239,128,239,200,239,164,239,0,11,230,191,239,209,239,227,239,179,195,58,223,13,255,31,255,192,248,233,49,255,79,255,68,239,169,255,146,
72,150,69,255,0,199,120,0,199,116,0,196,252,202,213,255,177,103,0,184,104,0,183,7,99,0,181,176,255,150,101,201,246,121,240,148,243,0,
219,255,35,15,255,249,210,240,14,6,91,209,27,15,45,15,0,63,8,121,240,20,15,149,15,113,15,17,15,152,15,167,15,0,185,15,203,15,
221,15,68,15,1,31,19,31,236,15,55,16,0,245,225,65,31,80,31,240,15,59,21,121,255,142,28,213,255,252,118,31,146,72,153,71,0,203,
126,0,35,201,121,204,17,11,1,146,243,110,1,193,230,199,50,239,31,24,4,39,181,16,196,116,19,47,37,47,0,55,45,205,16,74,38,173,
131,89,47,107,47,125,41,204,209,0,84,47,159,47,6,34,181,16,128,41,197,47,215,47,176,47,0,251,47,13,63,31,63,49,54,143,47,76,
63,94,63,55,54,0,91,212,128,63,146,63,50,63,182,50,181,28,202,63,11,4,248,56,63,242,31,4,33,214,140,0,211,137,183,0,209,134,
16,33,203,129,10,36,197,129,117,219,55,255,176,166,252,59,35,68,67,181,16,206,1,130,79,79,97,79,115,77,74,64,134,73,173,131,152,79,
0,170,79,188,73,181,16,146,79,221,79,68,64,173,131,134,79,0,10,95,28,95,100,95,206,79,82,95,185,79,61,80,121,95,0,139,95,157,
95,61,86,131,3,190,95,208,95,55,95,244,83,192,181,25,6,111,24,96,106,95,20,239,0,37,220,149,63,0,219,146,0,214,141,16,33,74,
64,99,207,131,23,97,8,32,30,99,196,113,147,241,0,157,246,253,57,128,111,146,111,164,111,182,105,71,67,200,102,0,1,83,215,111,233,111,
251,105,239,35,13,127,31,127,181,16,0,251,108,67,127,85,127,46,127,121,115,71,33,131,127,149,127,0,167,127,185,127,203,127,221,127,125,117,
154,249,3,143,21,143,128,124,124,102,105,66,143,84,143,244,115,91,214,250,27,224,15,156,0,223,153,184,97,181,16,135,137,21,97,0,122,117,
227,204,59,35,188,134,103,124,212,143,230,143,248,134,0,135,137,109,83,19,159,37,159,55,159,16,159,91,159,109,83,0,200,143,133,159,94,159,
132,140,184,147,1,83,196,159,214,159,0,232,159,250,159,12,175,30,175,172,86,57,175,75,175,93,175,192,141,188,126,175,144,175,105,175,180,163,
3,34,233,166,199,0,230,159,187,129,181,16,185,102,213,139,199,0,211,136,152,167,244,112,184,83,190,103,54,241,225,119,27,244,170,221,151,16,
33,7,191,0,25,191,43,191,4,188,46,84,83,191,101,191,119,190,127,147,0,142,191,245,172,61,191,136,191,211,191,172,191,153,163,241,115,0,
3,207,21,207,39,207,57,207,75,207,93,207,253,179,131,3,0,123,207,141,207,244,191,131,1,181,207,199,207,160,207,178,200,254,3,34,243,179,
0,239,176,0,237,61,171,16,33,230,164,0,227,252,162,192,169,108,14,208,208,60,130,39,48,218,234,169,63,209,0,109,83,73,223,91,223,109,
220,67,217,109,83,142,223,160,223,0,64,223,191,99,202,223,220,220,109,86,130,223,6,239,223,223,0,70,223,181,16,63,239,81,239,99,239,117,
239,135,239,153,239,0,57,227,239,41,189,239,207,239,54,233,71,38,246,239,8,255,248,26,255,44,243,3,34,247,186,0,243,181,48,51,209,87,
111,136,255,11,35,131,41,108,250,112,214,24,248,160,39,230,58,176,219,147,187,77,163,255,181,246,3,230,163,159,154,46,92,220,255,238,255,199,
243,190,180,0,13,15,173,251,36,233,199,255,75,15,36,15,111,9,66,15,0,141,15,159,15,177,15,195,15,213,15,117,6,154,255,2,31,192,
20,31,38,31,56,31,74,31,92,31,3,34,253,193,55,0,248,190,112,29,237,170,64,241,247,240,99,226,157,190,129,68,70,144,131,140,49,168,
31,0,186,26,139,255,217,31,235,31,196,25,109,89,21,47,39,47,0,199,28,72,47,90,47,108,32,0,47,15,47,147,47,108,47,0,128,67,
189,47,207,47,225,47,243,47,5,63,23,63,41,63,0,59,63,77,63,95,63,113,63,131,63,205,25,132,38,123,98,223,254,201,0,254,196,172,
61,240,177,12,124,26,195,172,144,54,228,63,246,63,8,79,26,79,0,44,79,62,79,80,79,98,79,116,79,134,79,152,79,170,79,0,188,79,
206,79,224,79,242,79,4,95,22,95,40,95,58,95,0,76,95,94,95,112,95,130,95,148,95,166,95,184,95,202,95,236,220,87,123,101,217,144,
208,50,134,0,211,158,182,144,126,0,203,119,126,116,244,112,189,255,104,0,184,104,0,173,91,0,255,171,83,0,169,77,0,166,73,63,0,156,
66,0,151,60,32,111,50,111,0,68,111,86,111,104,111,122,111,140,111,158,111,176,111,194,111,0,212,111,230,111,248,111,10,127,28,127,46,127,
64,127,82,127,0,100,127,118,127,136,127,154,127,172,127,190,127,208,127,226,127,176,244,127,6,143,24,135,31,98,134,51,95,132,129,189,46,104,
133,44,0,126,43,170,42,123,13,37,131,138,150,69,92,143,110,143,128,143,146,143,0,164,143,182,143,200,143,218,143,236,143,254,143,16,159,34,
159,0,52,159,70,159,88,159,106,159,124,159,142,159,160,159,178,159,0,196,159,214,159,232,159,250,159,12,175,30,175,48,175,66,175,2,84,167,
0,0 }; 
//Total :1826 bytes.
//-----------------------------------------------------------------------------------------
CKRV::CKRV()
{
   BMPhsl=0;
   nachit=0; 
   nachan=0; 
   for (long j=0;j<64;++j) 
   {
   angle[j]=0;
   changle[j]=0;
   slHns[j]=0;
   isrotate[j]=0;
   }
}
//-----------------------------------------------------------------------------------------
long CKRV::Decode(unsigned char *inpak,unsigned char* outdata,long ENDFA)
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
int CKRV::handle2index_sl(HWND hS)
{
int k=0;
while (hS!=slHns[k]) ++k;
return k;
}
//-----------------------------------------------------------------------------------------
HANDLE CKRV::extro_lbs(HDC hDC,LPSTR bzin)
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
void CKRV::gaa(HWND hWin, int number)
{
BITMAP bm;
HDC hdc;
HDC hdcMemory;
GetObject(BMPhsl, sizeof(bm), &bm);
hdc = GetDC(hWin);
hdcMemory = CreateCompatibleDC(hdc);
SelectObject(hdcMemory, BMPhsl);

BitBlt(hdc,0,0,BMPLENCRV,BMPHIGHCRV, hdcMemory, BMPLENCRV*number, 0,SRCCOPY);/////MASK ROUND KNOB

DeleteDC(hdcMemory);
/////////////////
ReleaseDC(hWin, hdc);
}
//-----------------------------------------------------------------------------------------
LONG CALLBACK CKRV::HandleKnob(HWND hW, UINT msg, WPARAM wParam, LPARAM lParam)
{
 long ind=0;
 PAINTSTRUCT ps;
 HDC hdc;

	switch (msg) {
            case WM_PAINT:
			{
			CKRV * a = (CKRV*)GetWindowLong(hW, GWL_USERDATA);
            if (a) ind = a->handle2index_sl(hW);
		    hdc = BeginPaint(hW, &ps);
            BITMAP bm;
            HDC hdcMemory;
            GetObject(a->BMPhsl, sizeof(bm), &bm);
            hdcMemory = CreateCompatibleDC(hdc);
		    SelectObject(hdcMemory, a->BMPhsl);
			
			BitBlt(hdc,0,0,BMPLENCRV,BMPHIGHCRV, hdcMemory, BMPLENCRV*(a->changle[ind]), 
				0,SRCCOPY);/////MASK ROUND KNOB

          
            DeleteDC(hdcMemory);
            ReleaseDC(hW, hdc);
			EndPaint(hW, &ps);
			}
			return 0L;
         case WM_LBUTTONDOWN:
			 {
		 	 CKRV * a = (CKRV*)GetWindowLong(hW, GWL_USERDATA);
             if (a) ind = a->handle2index_sl(hW);
		     if(a->changle[ind]<MXPCTRES)++a->changle[ind];
             a->gaa(hW,a->changle[ind]);
			 lParam=a->changle[ind];
             msg=WM_CURVUP ;    
		     wParam=ind; 
			 }
         break;

         case WM_RBUTTONDOWN:
			 {
		     CKRV * a = (CKRV*)GetWindowLong(hW, GWL_USERDATA);
             if (a) ind = a->handle2index_sl(hW);
		     if(a->changle[ind]>0) --a->changle[ind];
             a->gaa(hW,a->changle[ind]);
		     lParam=a->changle[ind];
             msg=WM_CURVUP ;    
		     wParam=ind; 
			 }
         break;

            case WM_ERASEBKGND:   //////Compulsary
            return 0;
		
          case WM_DESTROY:
		  {
	      char tclnm[30];
	      GetClassName(hW,&tclnm[0], 30);
          UnregisterClass(&tclnm[0], (HINSTANCE) GetWindowLong(hW, GWL_HINSTANCE));
		  }
	      return FALSE;
	}
  ///// back to windows procedure of parent window
	return CallWindowProc((WNDPROC)  GetWindowLong((HWND)GetParent(hW), GWL_WNDPROC),	
    hW,msg,wParam,lParam );
}
//-----------------------------------------------------------------------------------------
int CKRV::GetCurvesValue(int indx)
{
   return (int)(MXINTVLUE*changle[indx]/MXPCTRES);
} 
//-----------------------------------------------------------------------------------------
void CKRV::SetCurvesValue(int ind, int val)
{
	if (slHns[ind]!=NULL)
	{
		
		changle[ind]=val;
		gaa(slHns[ind],changle[ind]);

	}
} ///
//-----------------------------------------------------------------------------------------
HWND CKRV::add_curves(HWND hParent, int a,int b,int id)
{
	HWND hwnD;
    HDC hhDC; 
	char *cl_nm;
	char bbuf[10];
	cl_nm = (char*) malloc(32);
	memset(cl_nm ,0,32);
	itoa(id,&bbuf[0],10);
	strcat(cl_nm,CNCLSNAME);
	strcat(cl_nm,&bbuf[0]);

    WNDCLASS wc_id;
    memset(&wc_id,0,sizeof(wc_id));
	wc_id.lpfnWndProc       =      HandleKnob;
	wc_id.style             =      0;
	wc_id.lpszMenuName      =      NULL;
	wc_id.hInstance         =      (HINSTANCE)  hInstance;
	wc_id.cbWndExtra        =      0;
	wc_id.hCursor           =      0;
	wc_id.hbrBackground     =      NULL;
	wc_id.lpszClassName     =      (LPSTR) cl_nm;///

  RegisterClass(&wc_id);

   hwnD = CreateWindow(
   (LPSTR) cl_nm, (LPSTR) NULL,
    WS_CHILD | WS_VISIBLE,
    a,b,BMPLENCRV,BMPHIGHCRV,
    (HWND)hParent,(HMENU) (int) id+600,
    (HINSTANCE)hInstance, NULL);
	if (cl_nm!=NULL) free(cl_nm);
    SetWindowLong(hwnD, GWL_USERDATA, (long) this);

		     /////// --------- EXCLUDE BACKGROUND PIXELS
	         if (BMPhsl==0)
			 {
                /////// ---------
			    hhDC = GetDC(hwnD);
			    unsigned char *bmparr;
			    bmparr=(unsigned char*)malloc(12003);
			    Decode(BTMPARAY,bmparr,1826);
                BMPhsl=extro_lbs(hhDC,(char*)bmparr);
	            ReleaseDC(hwnD, hhDC);
                free(bmparr);				
			 }

slHns[id]=hwnD;
return hwnD;

}
//-----------------------------------------------------------------------------------------
#undef  CKRV  
#undef  BMPLENCRV  
#undef  BMPHIGHCRV  
#undef  MXPCTRES  
#undef  MXINTVLUE  
#undef  CNCLSNAME  
#undef  BTMPARAY  
//-----------------------------------------------------------------------------------------
