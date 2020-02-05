
#define TWOPI 6.28318530717958647692
/*-----------------------------------------------------------------------------------------*/
//Alex K version of DFT (slow but exact)
void DFT (long lenn,float *inflt,float *outflt,float *outim);///////
void DFT (long lenn,float *inflt,float *outflt,float *outim)
{
				//DFT TRANSFORM:
				long fq;//frequence
				float reverselen=(float) 1.0/lenn;
				long double InGral;///integral
				long double InGral2;///integral
				long i=0;//NEEDED
				InGral=0.0;//NEEDED
				for (fq=1;fq<lenn/2;++fq)
					{
						InGral=0.0;///
						InGral2=0.0;///
						i=0;
				while (i<lenn)
				{
                //InGral+=(double)inflt[i]*_fsin(TWOPI*i*fq/lenn);
                InGral+=(double)inflt[i]*sin(TWOPI*i*fq*reverselen);
				InGral2+=(double)inflt[i]*cos(TWOPI*i*fq*reverselen);
                ++i;
		        }
				i=0;
                outflt[fq]= (float)InGral*reverselen;////step;
				outim[fq] = (float)InGral2*reverselen;////step;
				//outim[fq] = (float)InGral2/lenn;////step;
			     }
				 ///////complited
 }
 /*-----------------------------------------------------------------------------------------*/
#include "kase_fft.h"
/*-----------------------------------------------------------------------------------------*/
