//------------------------------------
typedef struct {
HWND menus[8];
HWND phases[6];
HWND tunes[6];
HWND gains[7];
HWND knobs[4];
HWND curves[2];
int status; ///hiden 0 shown 1
} HandlesToHide;
//------------------------------------
///hide ctrls if credits shown
void hideCtrls(HandlesToHide* hdh, int ind, int hide_or_show)
{
if (hide_or_show==0)
{
  for (int e=0;e<6;++e) 
  {
  ShowWindow(hdh[ind].menus[e],SW_HIDE);
  ShowWindow(hdh[ind].phases[e],SW_HIDE);
  ShowWindow(hdh[ind].tunes[e],SW_HIDE);
  ShowWindow(hdh[ind].gains[e],SW_HIDE);
  }
  ShowWindow(hdh[ind].menus[6],SW_HIDE);
  ShowWindow(hdh[ind].menus[7],SW_HIDE);
  ShowWindow(hdh[ind].gains[6],SW_HIDE);
  ShowWindow(hdh[ind].knobs[0],SW_HIDE);
  ShowWindow(hdh[ind].knobs[1],SW_HIDE);
  ShowWindow(hdh[ind].knobs[2],SW_HIDE);
  ShowWindow(hdh[ind].knobs[3],SW_HIDE);
  ShowWindow(hdh[ind].curves[0],SW_HIDE);
  ShowWindow(hdh[ind].curves[1],SW_HIDE);

} else {

	if (hdh[ind].status!=1) {  //// if we aint show wav view
for (int e=0;e<6;++e) 
{
  ShowWindow(hdh[ind].menus[e],SW_SHOWNORMAL);
  ShowWindow(hdh[ind].phases[e],SW_SHOWNORMAL);
  ShowWindow(hdh[ind].tunes[e],SW_SHOWNORMAL);
  ShowWindow(hdh[ind].gains[e],SW_SHOWNORMAL);
}
    }
ShowWindow(hdh[ind].menus[6],SW_SHOWNORMAL);
ShowWindow(hdh[ind].menus[7],SW_SHOWNORMAL);
ShowWindow(hdh[ind].gains[6],SW_SHOWNORMAL);
ShowWindow(hdh[ind].knobs[0],SW_SHOWNORMAL);
ShowWindow(hdh[ind].knobs[1],SW_SHOWNORMAL);
ShowWindow(hdh[ind].knobs[2],SW_SHOWNORMAL);
ShowWindow(hdh[ind].knobs[3],SW_SHOWNORMAL);
ShowWindow(hdh[ind].curves[0],SW_SHOWNORMAL);
ShowWindow(hdh[ind].curves[1],SW_SHOWNORMAL);
}
}
//------------------------------------
void hideCtrls2(HandlesToHide* hdh, int ind, int hide_or_show)
{
if (hide_or_show==0)
{
  for (int e=0;e<6;++e) 
  {
  ShowWindow(hdh[ind].menus[e],SW_HIDE);
  ShowWindow(hdh[ind].phases[e],SW_HIDE);
  ShowWindow(hdh[ind].tunes[e],SW_HIDE);
  ShowWindow(hdh[ind].gains[e],SW_HIDE);
  hdh[ind].status=1;
  }

} else {
for (int e=0;e<6;++e) 
{
  ShowWindow(hdh[ind].menus[e],SW_SHOWNORMAL);
  ShowWindow(hdh[ind].phases[e],SW_SHOWNORMAL);
  ShowWindow(hdh[ind].tunes[e],SW_SHOWNORMAL);
  ShowWindow(hdh[ind].gains[e],SW_SHOWNORMAL);
  hdh[ind].status=0;
}

}
}
//------------------------------------