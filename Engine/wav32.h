
///SamplerChunk Structure
typedef struct {
  long           chunkID;////1819307379   "smpl"
  long           chunkSize;////60
  long           dwManufacturer;//0
  long           dwProduct;///0
  long           dwSamplePeriod;///
  long           dwMIDIUnityNote;///loop lengh
  long           dwMIDIPitchFraction;///60
  long           dwSMPTEFormat;///0
  long           dwSMPTEOffset;///0
  long           cSampleLoops;///1
  long           cbSamplerData;///0
                 ///struct SampleLoop Loops[];
  long  dwIdentifier;///0
  long  dwType;///0
  long  dwStart;////start smpl
  long  dwEnd;////end smpl
  long  dwFraction;//0
  long  dwPlayCount;//0
} SamplerChunk;

/*SampleLoop Structure
typedef struct {
  long  dwIdentifier;///0
  long  dwType;///0
  long  dwStart;////start smpl
  long  dwEnd;////end smpl
  long  dwFraction;//0
  long  dwPlayCount;//0
} SampleLoop;*/

SamplerChunk smpl;

/*<------------------------------------------------------------------------------>*/

typedef struct {
	char id_riff[4];//Contains the letters "RIFF" in ASCII form
                         //      (0x52494646 big-endian form).
    long len_riff;//36 + SubChunk2Size, or more precisely:
                    //           4 + (8 + SubChunk1Size) + (8 + SubChunk2Size)
                      //         This is the size of the rest of the chunk
                        //       following this number.  This is the size of the
                          //     entire file in bytes minus 8 bytes for the
                            //   two fields not included in this count:
                              // ChunkID and ChunkSize.
	char id_chuck[4];//Contains the letters "WAVE"
                      //         (0x57415645 big-endian form).
	char fmt[4];//Contains the letters "fmt "
                         //      (0x666d7420 big-endian form).
	long len_chuck;//16 for PCM.  This is the size of the
                           //    rest of the Subchunk which follows this
                           //    number.
    char type[2];//PCM = 1 (i.e. Linear quantization)
                            //   Values other than 1 indicate some
                             //  form of compression.
	char channels[2];//Mono = 1, Stereo = 2, etc.
	long freq;//8000, 44100, etc.
	long bytes;//== SampleRate * NumChannels * BitsPerSample/8
	char  align[2];//== NumChannels * BitsPerSample/8
                              // The number of bytes for one sample including
                            //   all channels. I wonder what happens when
                             //  this number isn't an integer?
	char  bits[2];//8 bits = 8, 16 bits = 16, etc.
	char id_data[4];//Contains the letters "data"
                           //    (0x64617461 big-endian form).
	long len_data;//Subchunk2Size    == NumSamples * NumChannels * BitsPerSample/8
                        //       This is the number of bytes in the data.
                          //     You can also think of this as the size
                            //   of the read of the subchunk following this
                             //  number.
} TitleWave;

TitleWave tw;

/*<------------------------------------------------------------------------------>*/
LPSTR saveWavMultiBits(HWND hwndDlg,float *res1,float *res2, long nsamples, long samplerate,int chnls)
{

    OPENFILENAME ofn2;       // complicated common dialog box structure
    HFILE hndF2;
    long u;
    long norma;
    long ger1,ger2;
    float iee1,iee2;
    TitleWave tw1;
          ZeroMemory(&ofn2, sizeof(OPENFILENAME));
          ofn2.lStructSize = sizeof(OPENFILENAME);
          ofn2.hwndOwner = hwndDlg;
          ofn2.lpstrFile = (char*) calloc(260,sizeof(char));//frees last file name
          ofn2.nMaxFile = 260*sizeof(char);
ofn2.lpstrFilter = "Wave 16-bit (*.wav)\0*.*\0Wave 24-bit (*.wav)\0*.*\0Wave 32-bit(*.wav)\0*.*\0Wave 32-bit float (*.wav)\0*.*\0";
          ofn2.lpstrCustomFilter =NULL;///".wav";////
          ofn2.nFilterIndex = 1;
          ofn2.lpstrFileTitle = NULL;//NULL;
          ofn2.nMaxFileTitle = 0;
          ofn2.lpstrDefExt = "wav";
          ofn2.lpstrInitialDir = NULL;///ReadIniBlock(1);///NULL;
          ofn2.lpstrTitle = "Render calculated sound as:";
          ofn2.Flags = OFN_HIDEREADONLY | OFN_NOCHANGEDIR | OFN_NOTESTFILECREATE | OFN_EXPLORER  | OFN_FILEMUSTEXIST;
          GetSaveFileName(&ofn2);
          ////WriteLastDir(ofn2.lpstrFile,1);///// write directory path used

    /*<------------------------*/
	if (ofn2.lpstrFile[0] == 0)
        {
	    /////MessageBox(0,"No file selected.","",0);
	    return FALSE;
	    }

    if (res1==NULL)
		{
	    MessageBox(0,"There is no data to save.","Developer error",0);
		return FALSE;
	    }

///////////////////////
tw1.id_riff[0]=82;//"RIFF"
tw1.id_riff[1] = 73;
tw1.id_riff[2] = 70;
tw1.id_riff[3] = 70;
tw1.len_riff = (nsamples*chnls*(ofn2.nFilterIndex+1))-8+256;//
if (ofn2.nFilterIndex==4) tw1.len_riff = (nsamples*chnls*ofn2.nFilterIndex)-8+256;//
tw1.id_chuck[0]=87;//"WAVE"
tw1.id_chuck[1]=65;
tw1.id_chuck[2]=86;
tw1.id_chuck[3]=69;
tw1.fmt[0]=102;//"fmt"
tw1.fmt[1]=109;
tw1.fmt[2]=116;
tw1.fmt[3]=32;
tw1.len_chuck= 16;
tw1.type[0]=1;//PCM
if (ofn2.nFilterIndex==4) tw1.type[0]=3;///WAVE_FORMAT_IEEE_FLOAT;

tw1.type[1]=0;
tw1.channels[0]=chnls;/////channels (stereo or mono)
tw1.channels[1]=0;
tw1.freq= samplerate;//////sample rate
tw1.bytes = samplerate*(ofn2.nFilterIndex+1)*chnls;
if (ofn2.nFilterIndex==4) tw1.bytes = samplerate*(ofn2.nFilterIndex)*chnls;
tw1.align[0] = (ofn2.nFilterIndex+1)*chnls;
if (ofn2.nFilterIndex==4) tw1.align[0] = (ofn2.nFilterIndex)*chnls;
tw1.align[1] = 0;
tw1.bits[0] = (ofn2.nFilterIndex+1)*8;///bits per sample
if (ofn2.nFilterIndex==4) tw1.bits[0] = (ofn2.nFilterIndex)*8;
tw1.bits[1] = 0;
tw1.id_data[0] =100 ;//"data"
tw1.id_data[1] =97 ;
tw1.id_data[2] =116 ;
tw1.id_data[3] =97 ;
tw1.len_data =nsamples*chnls*(ofn2.nFilterIndex+1);////lenght of data
if (ofn2.nFilterIndex==4) tw1.len_data =nsamples*chnls*ofn2.nFilterIndex;////lenght of data

                norma=pow(256,ofn2.nFilterIndex-1)*32768.f;

                hndF2 = _lcreat(ofn2.lpstrFile,0);

                _llseek(hndF2,0,FILE_BEGIN);//

                _lwrite(hndF2,(LPSTR) &tw1,sizeof(tw1));//

				_llseek(hndF2,sizeof(tw1),SEEK_SET);///
if (ofn2.nFilterIndex!=4)   ///TYPE 1 INTEGER
	{
				for (u=0;u<nsamples;++u)
				{
				 ger1=(long) (norma*res1[u]);
				 ger2=(long) (norma*res2[u]);
				 _lwrite (hndF2,(char*) &ger1,ofn2.nFilterIndex+1);// in casse of mono
				if (chnls==2) _lwrite (hndF2,(char*)&ger2,ofn2.nFilterIndex+1);// in casse of stereo
			    }
    }
if (ofn2.nFilterIndex==4)   ///TYPE 3 FLOAT
	{
				for (u=0;u<nsamples;++u)
				{
				iee1=(float) res1[u];
				iee2=(float) res2[u];
				char df1[8],df2[8];
		        memcpy(df1,(void*)&iee1,sizeof(float));
				memcpy(df2,(void*)&iee2,sizeof(float));
				_lwrite (hndF2,(char*)&df1,sizeof(float));// in casse of mono
				if (chnls==2) _lwrite (hndF2,(char*)&df2,sizeof(float));// in casse of stereo
			    }
    }
				CloseHandle((HANDLE)hndF2);////////////////////close file

return ofn2.lpstrFile;//////returns directory of the saved file
}
//*<------------------------------------------------------------------------------------------------------->*/