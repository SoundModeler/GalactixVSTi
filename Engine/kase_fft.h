//////KaseLab FFT January 2001
////int isProcess;
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define  DDC_PI  (3.14159265358979323846)
#define BITS_PER_WORD   (sizeof(unsigned) * 8)
///////////////=============================================////////////
////////////==============================================////////////////
///////////////=============================================////////////
int IsPowerOfTwo (long x );
int IsPowerOfTwo (long x )
{
    if ( x < 2 )
        return FALSE;

    if ( x & (x-1) )        // Thanks to 'byang' for this cute trick!
        return FALSE;

    return TRUE;
}
////////////==============================================////////////////
unsigned NumberOfBitsNeeded ( unsigned PowerOfTwo );
unsigned NumberOfBitsNeeded ( unsigned PowerOfTwo )
{
    unsigned i;

    if ( PowerOfTwo < 2 )
    {
        fprintf (
            stderr,
            ">>> Error in fftmisc.c: argument %d to NumberOfBitsNeeded is too small.\n",
            PowerOfTwo );
        ///MessageBox(0,stderr,"Error",0);
        exit(1);
    }

    for ( i=0; ; i++ )
    {
        if ( PowerOfTwo & (1 << i) )
            return i;
    }
}
///////////////==============================================//////////////
inline unsigned ReverseBits ( unsigned index, unsigned NumBits )
{
    unsigned i, rev;

    for ( i=rev=0; i < NumBits; i++ )
    {
        rev = (rev << 1) | (index & 1);
        index >>= 1;
    }

    return rev;
}
////////////=====================================================================///////////////////
void fft_float (unsigned  long NumSamples,int InverseTransform, float *RealIn, float *ImagIn, float *RealOut, float *ImagOut );
void fft_float (unsigned  long NumSamples,int InverseTransform, float *RealIn, float *ImagIn, float *RealOut, float *ImagOut )
{
    unsigned NumBits;    /* Number of bits needed to store indices */
    unsigned i, j, k, n;
    unsigned BlockSize, BlockEnd;

    double angle_numerator = 2.0 * DDC_PI;
    double tr, ti;     /* temp real, temp imaginary */

    if ( InverseTransform )
        angle_numerator = -angle_numerator;

 
    NumBits = NumberOfBitsNeeded ( NumSamples );


    for ( i=0; i < NumSamples; i++ )
    {
        j = ReverseBits ( i, NumBits );
        RealOut[j] = RealIn[i];
        ImagOut[j] = ImagIn[i];///(ImagIn == NULL) ? 0.0 : ImagIn[i];
    }

    /*
    **   Do the FFT itself...
    */

    BlockEnd = 1;
    for ( BlockSize = 2; BlockSize <= NumSamples; BlockSize <<= 1 )
    {
        double delta_angle = angle_numerator / (double)BlockSize;
        double sm2 = sin ( -2 * delta_angle );
        double sm1 = sin ( -delta_angle );
        double cm2 = cos ( -2 * delta_angle );
        double cm1 = cos ( -delta_angle );
        double w = 2 * cm1;
        double ar[3], ai[3];

    //    double temp; - needed ?

        for ( i=0; i < NumSamples; i += BlockSize )
        {
			     ///////PEASE DONT HANG UP
			  	
					///////////////////////////////////////////////////
            ar[2] = cm2;
            ar[1] = cm1;

            ai[2] = sm2;
            ai[1] = sm1;

            for ( j=i, n=0; n < BlockEnd; j++, n++ )
            {
                ar[0] = w*ar[1] - ar[2];
                ar[2] = ar[1];
                ar[1] = ar[0];

                ai[0] = w*ai[1] - ai[2];
                ai[2] = ai[1];
                ai[1] = ai[0];

                k = j + BlockEnd;
                tr = ar[0]*RealOut[k] - ai[0]*ImagOut[k];
                ti = ar[0]*ImagOut[k] + ai[0]*RealOut[k];

                RealOut[k] = RealOut[j] - tr;
                ImagOut[k] = ImagOut[j] - ti;

                RealOut[j] += tr;
                ImagOut[j] += ti;
            }
        }

        BlockEnd = BlockSize;
    }

}

////////////////////////==========================================================================/////////////////////
