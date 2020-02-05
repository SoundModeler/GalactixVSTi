/*
Create small cool get-name window
*/

/*<------------------------------------------------------------------------------------------------------------------------------------------------------>*/
HBMP BMP_ads;
long translate_exemplar=0;
long iSWshown=0;
short int deltax=0;
short int deltay=0;
///====================================================================================///////////
/*-----------------------------------------------------------------------------------------*/
long CALLBACK MakeWpp (HWND hW, UINT msg, WPARAM wParam, LPARAM lParam);
long CALLBACK MakeWpp (HWND hW, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	            case WM_ERASEBKGND:  //// DRAW BACKGROUND
				{
                BITMAP bm;
                HDC hdcMemory;
                GetObject(HBlogo, sizeof(bm), &bm);
                hdcMemory = CreateCompatibleDC((HDC) wParam);
                SelectObject(hdcMemory, HBlogo);
                BitBlt((HDC) wParam,0,	0,187, 57,hdcMemory,458,108,SRCCOPY);
                DeleteDC(hdcMemory);
                ReleaseDC(hW, (HDC) wParam);
				}
                return 1L;
		  case WM_DESTROY:
	      iSWshown=0;  
	      return FALSE;

		   case WM_LBUTTONDOWN:
			   {
			   	POINT p;
            GetCursorPos(&p);///hwndDlg,&wplc);
            deltax=p.x;///(short int)LOWORD(lParam);
			deltay=p.y;///(short int)HIWORD(lParam);
			   }
			return 0;

		  case WM_MOUSEMOVE:
            if (wParam==MK_LBUTTON	)
            {
            RECT rcwn;
            GetWindowRect(hW,&rcwn); //
			POINT p;
            GetCursorPos(&p);///hwndDlg,&wplc);
			deltax-=p.x;///(short int)LOWORD(lParam);
			deltay-=p.y;///(short int)HIWORD(lParam);
			MoveWindow(hW, rcwn.left-deltax
				,rcwn.top-deltay,187, 57,TRUE);//
			deltax=p.x;///(short int)LOWORD(lParam);
            deltay=p.y;///(short int)HIWORD(lParam);
			}
			break;

	             case WM_COMMAND:
				 switch (LOWORD(wParam)) {

	        case 888:////
				{
                char szStr[ 64 ];
                int i;
	            GetDlgItemText(hW,5486,szStr,20);
				if (strlen(szStr)!=0) 
				{
				for (long r=0;r<24;++r) progtbl[((Engine*) GEFFECT[translate_exemplar])->curProgram][r]=0;
				strcat(progtbl[((Engine*) GEFFECT[translate_exemplar] )->curProgram],szStr);
				}
				iSDialogshown=0;
				DestroyWindow(hW);
				UnregisterClass("GettingNV", (HINSTANCE) GetWindowLong (hW, GWL_HINSTANCE));
		}
			return TRUE;

		                      }
					   			////default:
			return DefWindowProc (hW,msg,wParam,lParam);
				}
			return DefWindowProc (hW,msg,wParam,lParam);
}
/*-----------------------------------------------------------------------------------------*/
HWND NewW(HWND hwndDlg );///parent window handle
HWND NewW(HWND hwndDlg )
{
	if (iSWshown==0)
	{

unsigned char *bmprr;
bmprr=(unsigned char*)malloc(196608);
			 dg->Decode(ads_bk,bmprr,34056);
			 
                BMP_ads=extro_lbs(hhDC,(char*)bmprr);
	            ReleaseDC(hwnD, hhDC);
                free(bmprr);

    WNDCLASS wr;
    memset(&wr,0,sizeof(wr));
	wr.lpfnWndProc = MakeWpp;////DefWindowProc ;
    //	wr.hInstance = (HINSTANCE) GetWindowLong(hwndDlg, GWL_HINSTANCE);
   // (HINSTANCE) GetWindowLong(hwndW, GWL_HINSTANCE);
	wr.hCursor = LoadCursor(NULL, IDC_ARROW);
	wr.hbrBackground = (HBRUSH) CreateSolidBrush(RGB(51,64,109));//(COLOR_WINDOW + 1);
	wr.lpszClassName = "GettingNV";

 if(!RegisterClass(&wr))
    {
      return 0;
    }
  RECT rcwn;
  GetWindowRect(hwndDlg,&rcwn); //
  HWND hwndW = CreateWindowEx (WS_EX_CLIENTEDGE	,  "GettingNV", "Enter new preset name:",
       WS_POPUP,///WS_VISIBLE | WS_EX_TOPMOST,// | WS_SYSMENU,// |WS_MINIMIZEBOX | WS_SYSMENU,//
	      rcwn.left+450,rcwn.top+45,187, 57,///240,90,
	//    (wplc.right-wplc.left)/2, (wplc.bottom-wplc.top)/2, 240, 90,
       hwndDlg, (HMENU) 0, wr.hInstance, (WNDPROC) MakeWpp);///NULL);//main window

SendMessage(CreateWindowEx (WS_EX_CLIENTEDGE	, "EDIT", (LPSTR) NULL,
                           WS_CHILD | WS_VISIBLE| WS_BORDER|  ES_AUTOVSCROLL | ES_MULTILINE,
						  5, 15, 120,21,
                          (HWND) hwndW, (HMENU) (int) 5486,////GetActiveWindow(),(HANDLE) (int) 486,
						  (HINSTANCE) GetWindowLong ((HWND) hwndW, GWL_HINSTANCE),
						  (WNDPROC) MakeWpp),WM_SETFONT, (WPARAM) (HANDLE) GetStockObject(ANSI_VAR_FONT),TRUE);
SendMessage(CreateWindow ("BUTTON", (LPSTR) "OK",\
                          WS_CHILD | WS_VISIBLE | WS_BORDER|BS_FLAT ,\
						  135,15,45,20,\
                          (HWND) hwndW,(HMENU) (int) 888,\
						  (HINSTANCE) GetWindowLong((HWND)hwndDlg, GWL_HINSTANCE),(WNDPROC) MakeWpp)\
,WM_SETFONT,(WPARAM) (HANDLE) GetStockObject(ANSI_VAR_FONT),TRUE);

	   if(hwndW == NULL)
   {
      MessageBox(0, "Window Creation Failed!", "Error!",
         MB_ICONEXCLAMATION | MB_OK | MB_SYSTEMMODAL);
      return NULL;
   }


  ShowWindow(hwndW,5);
  UpdateWindow(hwndW);
  
  iSWshown=1;				
   return hwndW;///
	} 
	else return 0;
}
//////////=============================================================================////
