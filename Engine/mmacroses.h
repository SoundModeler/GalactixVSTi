
//-----------------------------------------------------------------------------------------

#define IS_LESS_THANZERO(val) (*((long*)&val)>>31)
//#define IS_LESS_THANZERO2(val) ((*((long*)&val)&2147483648)==2147483648)

//#define IS_LESS_THANZERO(val,num) #define IS_LESS_THANZEROt(val)  {_asm mov  eax,val  _asm and eax,80000000H _asm jz IsPos }
//IsNeg##num:
//-----------------------------------------------------------------------------------------
//if(--ind==0) ind=FRAME;////  ASM EQUIVALENT

#define WRAP(ind_num,FRAME)  \
{_asm mov  eax,ind##ind_num  \
 _asm jnz label##ind_num     \
 _asm mov eax,FRAME          \
 _asm label##ind_num:        \
 _asm dec eax                \
 _asm mov ind##ind_num,eax   }

//-----------------------------------------------------------------------------------------
//pos=tanka-STEP;
 ///if(pos<0) pos+=FRAME;
#define WRAP2(tanka,pos,ind_nm,frm,steppa) {_asm   mov eax,tanka _asm  sub eax,steppa _asm  cmp eax,80000000H _asm  jna     IsPositive##ind_nm \
_asm add eax,frm _asm IsPositive##ind_nm: _asm  mov     pos,eax	 }
//-----------------------------------------------------------------------------------------
#define TRUNCATE(pos_float,pos_int,fract,half)  \
{_asm fld pos_float                             \
_asm  fsub half                                 \
_asm  fistp pos_int                             \
_asm  fild pos_int                              \
_asm  fsubr pos_float                           \
_asm  fstp fract                                \
}
//-----------------------------------------------------------------------------------------
