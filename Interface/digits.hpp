/*
SIMPLE DIGITS DISPLAY CONTROL
ALEX K NOV-2001
*/
//-----------------------------------------------------------------------------------------
#define CONTROLCLS Digits     ////CLASS NAME (TO EDIT)
#define BMPLENGH 9              ////HALF OF BITMAP LENGH (TO EDIT)
#define BMPHIGH 12                ////HIGH OF BITMAP (TO EDIT)
#define WM_DIGITSUP 121319           ////MESSAGE TO PARENT (TO EDIT)
#define WM_DIGITSRUN 151319
#define CNTRLCLSNAME "digits_"  ////CLASS NAME TO REGISTER (TO EDIT)
#define BITMAPARRAY bz_digits     ////NAME OF BITMAP ARRAY (TO EDIT)
//#define MAXNUMBER 100
//-----------------------------------------------------------------------------------------
class CONTROLCLS
{
public:
   CONTROLCLS();

   HWND  add_digits(HWND hParent, int a,int b,int numd, int id, int maxnum,int minnum);/// CREATE
   void  SetDigitsValue(int ind, long val);                  /// SET METHOD
   int GetDigitsValue(int indx);                           /// GET METHOD
   HANDLE extro_lbs(HDC hDC,LPSTR bzin);
   long Decode(unsigned char *inpak,unsigned char* outdata,long ENDFA);

   private:              ////   DONT EDIT BELOW
   HWND slHns[64];///ctrl handles
   int changle_hsl[64];///values (MINNUMBER-MAXNUMBER)
   int numdigits[64];
   ////void* hInstance;
   HANDLE BMPhsl;
   int nachit;////////// starting params when mouse is down
   int nachan;//// starting params when mouse is down

   int isrotate[64];
   int MAXNUMBER[64];
   int MINNUMBER[64];
   //HANDLE extro_lbs(HDC hDC,LPSTR bzin);
   void gaa_sl(HWND hWin, long high_pos);
   int handle2index_sl(HWND hS);
   static LONG CALLBACK HandleDigits(HWND hWlb, UINT msg, WPARAM wParam, LPARAM lParam);

};
//-----------------------------------------------------------------------------------------
extern void* hInstance;   ///BKGRGB
//-----------------------------------------------------------------------------------------
unsigned char BITMAPARRAY[]  = { 95,
66,77,230,13,0,242,242,54,242,240,213,40,242,240,97,242,240,12,242,240,1,0,53,24,242,242,176,241,240,196,14,18,3,26,5,255,29,223,163,
36,202,119,36,93,15,64,23,70,65,45,3,42,0,39,0,36,1,255,211,148,36,204,135,36,191,124,6,69,4,197,121,57,4,40,15,82,15,52,
15,70,15,0,112,15,154,15,124,15,142,15,184,15,226,15,196,15,214,6,134,211,0,211,148,20,31,38,22,35,2,15,16,187,15,101,33,99,90,
81,19,78,16,2,16,252,1,62,211,0,209,144,36,202,132,105,20,91,22,54,76,31,201,129,252,1,201,129,78,31,96,31,0,162,23,148,31,118,
31,160,31,178,31,220,31,190,31,232,31,12,250,22,247,16,204,135,56,47,74,38,35,1,11,19,0,252,0,117,35,2,19,252,1,36,18,117,47,
111,45,211,2,0,132,47,126,47,192,47,210,47,156,47,222,47,240,47,2,63,0,20,63,62,63,168,47,98,63,104,47,82,63,76,63,158,47,0,
112,63,158,63,224,63,242,63,188,63,254,63,16,79,34,79,0,52,79,94,79,124,63,130,79,136,63,114,79,108,79,78,79,0,144,79,190,79,0,
95,18,95,220,79,30,95,48,95,66,95,224,84,95,126,95,156,79,250,79,168,76,36,151,74,63,36,182,104,36,195,124,225,84,223,80,155,151,74,
252,1,205,138,225,87,232,89,151,177,72,5,22,5,16,47,33,182,104,240,84,151,25,74,14,105,237,84,182,104,41,32,41,111,59,111,0,11,96,
8,111,98,103,244,95,6,100,40,106,74,108,182,105,140,237,95,137,100,205,138,104,111,98,102,215,85,186,15,106,36,200,130,5,116,3,112,198,102,
6,118,6,12,121,186,106,182,111,32,102,53,127,74,124,86,127,6,41,39,186,106,224,99,122,127,20,127,14,119,120,127,0,186,127,192,108,171,121,
174,112,222,101,146,127,176,79,154,95,0,148,95,58,143,76,143,106,95,40,143,230,79,184,84,155,143,0,185,95,143,143,209,143,227,143,101,143,191,
143,25,159,31,134,1,62,1,159,203,143,89,159,107,159,125,159,251,143,161,159,0,167,143,197,159,143,159,185,152,76,159,6,175,136,159,226,159,0,
60,175,66,159,44,175,114,175,132,175,150,175,180,159,186,175,0,216,159,210,159,68,175,210,175,108,175,38,191,168,175,2,191,12,92,191,210,87,93,
60,38,47,80,47,26,47,20,47,0,194,191,8,38,173,191,11,47,141,20,8,207,142,31,208,26,192,145,191,75,207,157,191,67,47,129,207,103,37,
36,202,1,117,2,31,44,31,222,8,181,207,223,207,245,11,223,0,12,210,207,0,31,202,117,40,223,58,216,253,207,247,207,0,105,223,187,207,49,
31,43,31,61,24,0 }; 
//Total :630 bytes.LSZ PACKED
//-----------------------------------------------------------------------------------------
CONTROLCLS::CONTROLCLS()
{
for (long j=0;j<64;++j) 
{
	changle_hsl[j]=0;
    slHns[j]=0;///ctrl handles
    changle_hsl[j]=0;///values (MINNUMBER-MAXNUMBER)
    numdigits[j]=0;
   isrotate[j]=0;
   MAXNUMBER[j]=0;
   MINNUMBER[j]=0;
}
   BMPhsl=0;
   nachit=0;////////// starting params when mouse is down
   nachan=0;//// starting params when mouse is down
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
int CONTROLCLS::handle2index_sl(HWND hS)
{
int k=0;
while (hS!=slHns[k]) ++k;
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
void CONTROLCLS::gaa_sl (HWND hWin, long numbera)
{
BITMAP bm;
HDC hdc;
HDC hdcMemory;
GetObject(BMPhsl, sizeof(bm), &bm);
hdc = GetDC(hWin);
hdcMemory = CreateCompatibleDC(hdc);
SelectObject(hdcMemory, BMPhsl);
long number=fabsf(numbera);

long number1=10;
if (number==100) number1=1;
long number2=(int)(number*0.1);
if (number<10) number2=10;
if (number==100) number2=0;
long number3=number%10;
if (numbera<0) number1=11;
StretchBlt( hdc,0, 0,BMPLENGH,BMPHIGH,hdcMemory, number1*(BMPLENGH-1),0,BMPLENGH,
		   BMPHIGH,SRCCOPY );
StretchBlt( hdc,BMPLENGH, 0,BMPLENGH,BMPHIGH,hdcMemory, number2*(BMPLENGH-1),0,BMPLENGH,
		   BMPHIGH,SRCCOPY );
StretchBlt( hdc,2*BMPLENGH, 0,BMPLENGH,BMPHIGH,hdcMemory, number3*(BMPLENGH-1),0,BMPLENGH,
		   BMPHIGH,SRCCOPY );
DeleteDC(hdcMemory);
/////////////////
ReleaseDC(hWin, hdc);
}
//-----------------------------------------------------------------------------------------
LONG CALLBACK CONTROLCLS::HandleDigits(HWND hW, UINT msg, WPARAM wParam, LPARAM lParam)
{
 int ind=0;
 PAINTSTRUCT ps;
 HDC hdc;

	switch (msg) {
            case WM_PAINT:
			{
			CONTROLCLS * a = (CONTROLCLS*)GetWindowLong(hW, GWL_USERDATA);
            if (a) ind = a->handle2index_sl(hW);
		    hdc = BeginPaint(hW, &ps);
            BITMAP bm;
            HDC hdcMemory;
            GetObject(a->BMPhsl, sizeof(bm), &bm);
            hdcMemory = CreateCompatibleDC(hdc);
		    SelectObject(hdcMemory, a->BMPhsl);
			int number=fabsf(a->changle_hsl[ind]);

int number1=10;
if (number==100) number1=1;
int number2=(int)(number*0.1);
if (number<10) number2=10;
if (number==100) number2=0;
int number3=number%10;
if (a->changle_hsl[ind]<0) number1=11;

StretchBlt( hdc,0, 0,BMPLENGH,BMPHIGH,hdcMemory, number1*(BMPLENGH-1),0,BMPLENGH,
		   BMPHIGH,SRCCOPY );
StretchBlt( hdc,BMPLENGH, 0,BMPLENGH,BMPHIGH,hdcMemory, number2*(BMPLENGH-1),0,BMPLENGH,
		   BMPHIGH,SRCCOPY );
StretchBlt( hdc,2*BMPLENGH, 0,BMPLENGH,BMPHIGH,hdcMemory, number3*(BMPLENGH-1),0,BMPLENGH,
		   BMPHIGH,SRCCOPY );
          
            DeleteDC(hdcMemory);
            ReleaseDC(hW, hdc);
			EndPaint(hW, &ps);
			}
			return 0L;
         case WM_LBUTTONDOWN:
			 {
		 SetCursor(LoadCursor(NULL,0));
         SetCapture(hW);
		 	CONTROLCLS * a = (CONTROLCLS*)GetWindowLong(hW, GWL_USERDATA);
            if (a) ind = a->handle2index_sl(hW);
		 a->isrotate[ind]=1;
		 a->nachit=(short int)HIWORD(lParam);
		 a->nachan=a->changle_hsl[ind];
         a->gaa_sl(hW,a->changle_hsl[ind]);
			 }
         return 0;

         case WM_LBUTTONUP:
			 {
		 SetCursor(LoadCursor(NULL, IDC_ARROW));
	     	CONTROLCLS * a = (CONTROLCLS*)GetWindowLong(hW, GWL_USERDATA);
            if (a) ind = a->handle2index_sl(hW);
		 a->isrotate[ind]=0;
	     ReleaseCapture();
         a->gaa_sl(hW,a->changle_hsl[ind]);
		 msg=WM_DIGITSUP ;
		 wParam=ind;
		 lParam=a->changle_hsl[ind];
			 }
         break;

            case WM_MOUSEMOVE:
            if (wParam==MK_LBUTTON	)
            {
			CONTROLCLS * a = (CONTROLCLS*)GetWindowLong(hW, GWL_USERDATA);
            if (a) ind = a->handle2index_sl(hW);
				/////////////
				a->changle_hsl[ind]=(short int) (0.4f*(a->nachit-(short int)HIWORD(lParam))) + a->nachan ;

				if (a->changle_hsl[ind]>a->MAXNUMBER[ind]) 
					a->changle_hsl[ind]=a->MAXNUMBER[ind];
				if (a->changle_hsl[ind]<a->MINNUMBER[ind]) a->changle_hsl[ind]=a->MINNUMBER[ind];

				//////////////
				a->gaa_sl(hW,a->changle_hsl[ind]);
				msg=WM_DIGITSRUN;
                wParam=ind;
		        lParam=a->changle_hsl[ind];
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

   /////// message parameters

   ///// back to windows procedure of parent window
	return CallWindowProc((WNDPROC)  GetWindowLong((HWND)GetParent(hW), GWL_WNDPROC),	
    hW,msg,wParam,lParam );
}
//-----------------------------------------------------------------------------------------
int CONTROLCLS::GetDigitsValue(int indx)
{
   return changle_hsl[indx];
} 
//-----------------------------------------------------------------------------------------
void CONTROLCLS::SetDigitsValue(int ind, long val)
{
	if (slHns[ind]!=NULL)  ///&&(val<101))
	{
		
		changle_hsl[ind]=val;
		gaa_sl(slHns[ind],changle_hsl[ind]);

	}
} ///
//-----------------------------------------------------------------------------------------
HWND CONTROLCLS::add_digits(HWND hParent, int a,int b,int umdigits_a, int id, int maxnum,int minnum)
{
	HWND hwnD;
    HDC hhDC; 
	char *cl_nm;
	char bbuf[10];
	cl_nm = (char*) malloc(32);
	memset(cl_nm ,0,32);
	itoa(id,&bbuf[0],10);
	strcat(cl_nm,CNTRLCLSNAME);
	strcat(cl_nm,&bbuf[0]);
    numdigits[id]=umdigits_a;

    WNDCLASS wc_id;
    memset(&wc_id,0,sizeof(wc_id));
	wc_id.lpfnWndProc       =      HandleDigits;
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
    a,b,umdigits_a*BMPLENGH,BMPHIGH,
    (HWND)hParent,(HMENU) (int) id+400,
    (HINSTANCE)hInstance, NULL);
	if (cl_nm!=NULL) free(cl_nm);
    SetWindowLong(hwnD, GWL_USERDATA, (long) this);

		     /////// ---------  
	MAXNUMBER[id]=maxnum;
	MINNUMBER[id]=minnum;

             if (BMPhsl==0)
			 {
                /////// ---------
			    hhDC = GetDC(hwnD);
			    unsigned char *bmparr;
			    bmparr=(unsigned char*)malloc(8192);
			    Decode(BITMAPARRAY,bmparr,630);
                BMPhsl=extro_lbs(hhDC,(char*)bmparr);
	            ReleaseDC(hwnD, hhDC);
                free(bmparr);
				
			 }

slHns[id]=hwnD;
return hwnD;

}
//-----------------------------------------------------------------------------------------
#undef CONTROLCLS 
#undef BMPLENGH 
#undef BMPHIGH 
#undef WM_SLDR
#undef CNTRLCLSNAME 
#undef BITMAPARRAY 
//-----------------------------------------------------------------------------------------
