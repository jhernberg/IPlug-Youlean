/* note: only EEL_F_SIZE=8 is now supported (no float EEL_F's) */

void nseel_asm_1pdd(void)
{
  __asm__(
     
    "movl $0xfefefefe, %edi\n" 
#ifdef TARGET_X64
    "subl $128, %rsp\n"
    "fstpl (%rsp)\n"
    "movq (%rsp), %xmm0\n"
    #ifdef AMD64ABI
       "movl %rsi, %r15\n"
       "call *%edi\n" 
       "movl %r15, %rsi\n"
    #else
       "call *%edi\n" 
    #endif
    "movq xmm0, (%rsp)\n"
    "fldl (%rsp)\n"
    "addl $128, %rsp\n"
#else
    "subl $16, %esp\n"
    "fstpl (%esp)\n"
    "call *%edi\n" 
    "addl $16, %esp\n" 
#endif
     
  );
}
void nseel_asm_1pdd_end(void){}

void nseel_asm_2pdd(void)
{
  __asm__(
    
    "movl $0xfefefefe, %edi\n"
#ifdef TARGET_X64
    "subl $128, %rsp\n"
    "fstpl 8(%rsp)\n"
    "fstpl (%rsp)\n"
    "movq 8(%rsp), %xmm1\n"
    "movq (%rsp), %xmm0\n"
    #ifdef AMD64ABI
      "movl %rsi, %r15\n"
      "call *%edi\n"
      "movl %r15, %rsi\n"
    #else
      "call *%edi\n"
    #endif
    "movq xmm0, (%rsp)\n"
    "fldl (%rsp)\n"
    "addl $128, %rsp\n"
#else
    "subl $16, %esp\n"
    "fstpl 8(%esp)\n"
    "fstpl (%esp)\n"
    "call *%edi\n"
    "addl $16, %esp\n"
#endif
    
  );
}
void nseel_asm_2pdd_end(void){}

void nseel_asm_2pdds(void)
{
  __asm__(
    
    "movl $0xfefefefe, %eax\n"
#ifdef TARGET_X64
    "subl $128, %rsp\n"
    "fstpl (%rsp)\n"
    "movq (%rdi), %xmm0\n"
    "movq (%rsp), %xmm1\n"
    #ifdef AMD64ABI
      "movl %rsi, %r15\n"
      "movl %rdi, %r14\n"
      "call *%eax\n"
      "movl %r15, %rsi\n"
      "movq xmm0, (%r14)\n"
      "movl %r14, %rax\n" /* set return value */
    #else
      "call *%eax\n"
      "movq xmm0, (%edi)\n"
      "movl %edi, %eax\n" /* set return value */
    #endif
    "addl $128, %rsp\n"
#else
    "subl $8, %esp\n"
    "fstpl (%esp)\n"
    "pushl 4(%edi)\n" /* push parameter */
    "pushl (%edi)\n"    /* push the rest of the parameter */
    "call *%eax\n"
    "addl $16, %esp\n"
    "fstpl (%edi)\n" /* store result */
    "movl %edi, %eax\n" /* set return value */
#endif
    
  );
}
void nseel_asm_2pdds_end(void){}



//---------------------------------------------------------------------------------------------------------------


// do nothing, eh
void nseel_asm_exec2(void)
{
   __asm__(
      ""
    );
}
void nseel_asm_exec2_end(void) { }



void nseel_asm_invsqrt(void)
{
  __asm__(
    "movl $0x5f3759df, %edx\n"
    "fsts -8(%esp)\n"
#ifdef TARGET_X64
    "movl 0xfefefefe, %rax\n"
    "subl %ecx, %ecx\n"
    "fmul" EEL_F_SUFFIX " (%rax)\n"
#else
    "fmul" EEL_F_SUFFIX " (0xfefefefe)\n"
#endif
    "movl -8(%esp), %ecx\n"
    "sarl $1, %ecx\n"
    "subl %ecx, %edx\n"
    "movl %edx, -8(%esp)\n"
    "fmuls -8(%esp)\n"
    "fmuls -8(%esp)\n"
#ifdef TARGET_X64
    "movl 0xfefefefe, %rax\n"
    "fadd" EEL_F_SUFFIX " (%rax)\n"
#else
    "fadd" EEL_F_SUFFIX " (0xfefefefe)\n"
#endif
    "fmuls -8(%esp)\n"
  );
}
void nseel_asm_invsqrt_end(void) {}


//---------------------------------------------------------------------------------------------------------------
void nseel_asm_sin(void)
{
  __asm__(
    "fsin\n"
  );
}
void nseel_asm_sin_end(void) {}

//---------------------------------------------------------------------------------------------------------------
void nseel_asm_cos(void)
{
  __asm__(
    "fcos\n"
  );
}
void nseel_asm_cos_end(void) {}

//---------------------------------------------------------------------------------------------------------------
void nseel_asm_tan(void)
{
  __asm__(
    "fptan\n"
    "fstp %st(0)\n"
  );
}
void nseel_asm_tan_end(void) {}

//---------------------------------------------------------------------------------------------------------------
void nseel_asm_sqr(void)
{
  __asm__(
    "fmul %st(0), %st(0)\n"
  );
}
void nseel_asm_sqr_end(void) {}

//---------------------------------------------------------------------------------------------------------------
void nseel_asm_sqrt(void)
{
  __asm__(
    "fabs\n"
    "fsqrt\n"
  );
}
void nseel_asm_sqrt_end(void) {}


//---------------------------------------------------------------------------------------------------------------
void nseel_asm_log(void)
{
  __asm__(
    "fldln2\n"
    "fxch\n"
    "fyl2x\n"
  );
}
void nseel_asm_log_end(void) {}

//---------------------------------------------------------------------------------------------------------------
void nseel_asm_log10(void)
{
  __asm__(
    "fldlg2\n"
    "fxch\n"
    "fyl2x\n"
    
  );
}
void nseel_asm_log10_end(void) {}

//---------------------------------------------------------------------------------------------------------------
void nseel_asm_abs(void)
{
  __asm__(
    "fabs\n"
  );
}
void nseel_asm_abs_end(void) {}


//---------------------------------------------------------------------------------------------------------------
void nseel_asm_assign(void)
{
#ifdef TARGET_X64

  __asm__(
    "movll (%rax), %rdx\n"
    "movll %rdx, %rcx\n"
    "shrl $32, %rdx\n"
    "andl $0x7FF00000, %edx\n"
    "jz 1f\n"
    "cmpl $0x7FF00000, %edx\n"
    "je 1f\n"
    "jmp 0f\n"
    "1:\n"
    "subl %rcx, %rcx\n"
    "0:\n"
    "movll %rcx, (%edi)\n"
    "movll %rdi, %rax\n"
    );

#else

  __asm__(
    "movl 4(%eax), %edx\n"
    "movl (%eax), %ecx\n"
    "andl  $0x7ff00000, %edx\n"
    "jz 1f\n"   // if exponent=zero, zero
    "cmpl  $0x7ff00000, %edx\n"
    "je 1f\n" // if exponent=all 1s, zero
    "movl 4(%eax), %edx\n" // reread
    "jmp 0f\n"
    "1:\n"
    "subl %ecx, %ecx\n"
    "subl %edx, %edx\n"
    "0:\n"
    "movl %ecx, (%edi)\n"
    "movl %edx, 4(%edi)\n"
    "movl %edi, %eax\n"
  );

#endif
}
void nseel_asm_assign_end(void) {}

//---------------------------------------------------------------------------------------------------------------
void nseel_asm_assign_fromfp(void)
{
#ifdef TARGET_X64

  __asm__(
    "fstpl (%rdi)\n"
    "movll (%rdi), %rdx\n"
    "movll $0x7FF0000000000000, %r15\n"
    "andll %r15, %rdx\n"
    "jz 1f\n"
    "cmpll %r15, %rdx\n"
    "jne 0f\n"
    "1:"
    "subll %rcx, %rcx\n"
    "movll %rcx, (%rdi)\n"
    "0:\n"
    "movll %rdi, %rax\n"
    );

#else

  __asm__(
    "fstpl (%edi)\n"
    "movl 4(%edi), %edx\n"
    "andl $0x7ff00000, %edx\n"
    "jz 1f\n"
    "cmpl $0x7ff00000, %edx\n"
    "jne 0f\n"
    "1:\n"
      "fldz\n"
      "fstpl (%edi)\n"
    "0:\n"
    "movl %edi, %eax\n"
  );

#endif
}
void nseel_asm_assign_fromfp_end(void) {}


//---------------------------------------------------------------------------------------------------------------
void nseel_asm_assign_fast(void)
{
#ifdef TARGET_X64

  __asm__(
    "movll (%rax), %rdx\n"
    "movll %rdx, (%edi)\n"
    "movll %rdi, %rax\n"
    );

#else

  __asm__(
    "movl 4(%eax), %edx\n"
    "movl (%eax), %ecx\n"
    "movl %ecx, (%edi)\n"
    "movl %edx, 4(%edi)\n"
    "movl %edi, %eax\n"
  );

#endif
}
void nseel_asm_assign_fast_end(void) {}

//---------------------------------------------------------------------------------------------------------------
void nseel_asm_add(void)
{
  __asm__(
    "fadd\n"
  );
}
void nseel_asm_add_end(void) {}

void nseel_asm_add_op(void)
{
  __asm__(
    "fadd" EEL_F_SUFFIX " (%edi)\n"
    "movl %edi, %eax\n"
    "fstp" EEL_F_SUFFIX " (%edi)\n"
  );
}
void nseel_asm_add_op_end(void) {}


//---------------------------------------------------------------------------------------------------------------
void nseel_asm_sub(void)
{
  __asm__(
#ifdef __GNUC__
    "fsubr\n" // gnuc has fsub/fsubr backwards, ack
#else
    "fsub\n"
#endif
  );
}
void nseel_asm_sub_end(void) {}

void nseel_asm_sub_op(void)
{
  __asm__(
    "fsubr" EEL_F_SUFFIX " (%edi)\n"
    "movl %edi, %eax\n"
    "fstp" EEL_F_SUFFIX " (%edi)\n"
  );
}
void nseel_asm_sub_op_end(void) {}

//---------------------------------------------------------------------------------------------------------------
void nseel_asm_mul(void)
{
  __asm__(
    "fmul\n"
  );
}
void nseel_asm_mul_end(void) {}

void nseel_asm_mul_op(void)
{
  __asm__(
    "fmul" EEL_F_SUFFIX " (%edi)\n"
    "movl %edi, %eax\n"
    "fstp" EEL_F_SUFFIX " (%edi)\n"
  );
}
void nseel_asm_mul_op_end(void) {}

//---------------------------------------------------------------------------------------------------------------
void nseel_asm_div(void)
{
  __asm__(
#ifdef __GNUC__
    "fdivr\n" // gcc inline asm seems to have fdiv/fdivr backwards
#else
    "fdiv\n"
#endif
  );
}
void nseel_asm_div_end(void) {}

void nseel_asm_div_op(void)
{
  __asm__(
    "fld" EEL_F_SUFFIX " (%edi)\n"
#ifndef __GNUC__
    "fxch\n" // gcc inline asm seems to have fdiv/fdivr backwards
#endif
    "fdiv\n" 
    "movl %edi, %eax\n"
    "fstp" EEL_F_SUFFIX " (%edi)\n"
  );
}
void nseel_asm_div_op_end(void) {}

//---------------------------------------------------------------------------------------------------------------
void nseel_asm_mod(void)
{
  __asm__(
    "fabs\n"
    "fistpl -8(%esp)\n"
    "fabs\n"
    "fistpl -4(%esp)\n"
    "xorl %edx, %edx\n"
#ifdef TARGET_X64
    "subl %eax, %eax\n"
#endif
    "cmpl $0, -8(%esp)\n"
    "je 0f\n" // skip devide, set return to 0
    "movl -4(%esp), %eax\n"
    "divl -8(%esp)\n"
    "0:\n"
    "movl %edx, -8(%esp)\n"
    "fildl -8(%esp)\n"
  );
}
void nseel_asm_mod_end(void) {}

void nseel_asm_shl(void)
{
  __asm__(
    "fistpl -8(%esp)\n"
    "fistpl -4(%esp)\n"
    "movl -8(%esp), %ecx\n"
    "movl -4(%esp), %eax\n"
    "shll %cl, %eax\n"
    "movl %eax, -8(%esp)\n"
    "fildl -8(%esp)\n"
  );
}
void nseel_asm_shl_end(void) {}

void nseel_asm_shr(void)
{
  __asm__(
    "fistpl -8(%esp)\n"
    "fistpl -4(%esp)\n"
    "movl -8(%esp), %ecx\n"
    "movl -4(%esp), %eax\n"
    "sarl %cl, %eax\n"
    "movl %eax, -8(%esp)\n"
    "fildl -8(%esp)\n"
  );
}
void nseel_asm_shr_end(void) {}


void nseel_asm_mod_op(void)
{
  __asm__(
    "fld" EEL_F_SUFFIX " (%edi)\n"
    "fxch\n"
    "fabs\n"
    "fistpl (%edi)\n"
    "fabs\n"
    "fistpl -8(%esp)\n"
#ifdef TARGET_X64
    "subl %eax, %eax\n"
#endif
    "xorl %edx, %edx\n"
    "cmpl $0, (%edi)\n"
    "je 0f\n" // skip devide, set return to 0
    "movl -8(%esp), %eax\n"
    "divl (%edi)\n"
    "0:\n"
    "movl %edx, (%edi)\n"
    "fildl (%edi)\n"
    "movl %edi, %eax\n"
    "fstp" EEL_F_SUFFIX " (%edi)\n"
    );
}
void nseel_asm_mod_op_end(void) {}

//---------------------------------------------------------------------------------------------------------------
void nseel_asm_or(void)
{
  __asm__(
    "fistpll -8(%esp)\n"
    "fistpll -16(%esp)\n"
#ifdef TARGET_X64
    "movll -16(%rsp), %rdi\n"
    "orll %rdi, -8(%rsp)\n"
#else
    "movl -16(%esp), %edi\n"
    "movl -12(%esp), %ecx\n"
    "orl %edi, -8(%esp)\n"
    "orl %ecx, -4(%esp)\n"
#endif
    "fildll -8(%esp)\n"
  );
}
void nseel_asm_or_end(void) {}

void nseel_asm_or0(void)
{
  __asm__(
    "frndint\n"
  );
}
void nseel_asm_or0_end(void) {}

void nseel_asm_or_op(void)
{
  __asm__(
    "fld" EEL_F_SUFFIX " (%edi)\n"
    "fxch\n"
    "fistpll (%edi)\n"
    "fistpll -8(%esp)\n"
#ifdef TARGET_X64
    "movll -8(%rsp), %rax\n"
    "orll %rax, (%rdi)\n"
#else
    "movl -8(%esp), %eax\n"
    "movl -4(%esp), %ecx\n"
    "orl %eax, (%edi)\n"
    "orl %ecx, 4(%edi)\n"
#endif
    "fildll (%edi)\n"
    "movl %edi, %eax\n"
    "fstp" EEL_F_SUFFIX " (%edi)\n"
  );
}
void nseel_asm_or_op_end(void) {}


void nseel_asm_xor(void)
{
  __asm__(
    "fistpll -8(%esp)\n"
    "fistpll -16(%esp)\n"
#ifdef TARGET_X64
    "movll -16(%rsp), %rdi\n"
    "xorll %rdi, -8(%rsp)\n"
#else
    "movl -16(%esp), %edi\n"
    "movl -12(%esp), %ecx\n"
    "xorl %edi, -8(%esp)\n"
    "xorl %ecx, -4(%esp)\n"
#endif
    "fildll -8(%esp)\n"
  );
}
void nseel_asm_xor_end(void) {}

void nseel_asm_xor_op(void)
{
  __asm__(
    "fld" EEL_F_SUFFIX " (%edi)\n"
    "fxch\n"
    "fistpll (%edi)\n"
    "fistpll -8(%esp)\n"
#ifdef TARGET_X64
    "movll -8(%rsp), %rax\n"
    "xorll %rax, (%rdi)\n"
#else
    "movl -8(%esp), %eax\n"
    "movl -4(%esp), %ecx\n"
    "xorl %eax, (%edi)\n"
    "xorl %ecx, 4(%edi)\n"
#endif
    "fildll (%edi)\n"
    "movl %edi, %eax\n"
    "fstp" EEL_F_SUFFIX " (%edi)\n"
  );
}
void nseel_asm_xor_op_end(void) {}


//---------------------------------------------------------------------------------------------------------------
void nseel_asm_and(void)
{
  __asm__(
    "fistpll -8(%esp)\n"
    "fistpll -16(%esp)\n"
#ifdef TARGET_X64
    "movll -16(%rsp), %rdi\n"
    "andll %rdi, -8(%rsp)\n"
#else
    "movl -16(%esp), %edi\n"
    "movl -12(%esp), %ecx\n"
    "andl %edi, -8(%esp)\n"
    "andl %ecx, -4(%esp)\n"
#endif
    "fildll -8(%esp)\n"
  );
}
void nseel_asm_and_end(void) {}

void nseel_asm_and_op(void)
{
  __asm__(
    "fld" EEL_F_SUFFIX " (%edi)\n"
    "fxch\n"
    "fistpll (%edi)\n"
    "fistpll -8(%esp)\n"
#ifdef TARGET_X64
    "movll -8(%rsp), %rax\n"
    "andll %rax, (%rdi)\n"
#else
    "movl -8(%esp), %eax\n"
    "movl -4(%esp), %ecx\n"
    "andl %eax, (%edi)\n"
    "andl %ecx, 4(%edi)\n"
#endif
    "fildll (%edi)\n"
    "movl %edi, %eax\n"
    "fstp" EEL_F_SUFFIX " (%edi)\n"
  );
}
void nseel_asm_and_op_end(void) {}


//---------------------------------------------------------------------------------------------------------------
void nseel_asm_uplus(void) // this is the same as doing nothing, it seems
{
   __asm__(
      ""
    );
}
void nseel_asm_uplus_end(void) {}

//---------------------------------------------------------------------------------------------------------------
void nseel_asm_uminus(void)
{
  __asm__(
    "fchs\n"
  );
}
void nseel_asm_uminus_end(void) {}



//---------------------------------------------------------------------------------------------------------------
void nseel_asm_sign(void)
{
  __asm__(

#ifdef TARGET_X64


    "fst" EEL_F_SUFFIX " -8(%rsp)\n"
    "mov" EEL_F_SUFFIX " -8(%rsp), %rdx\n"
    "movll $0x7FFFFFFFFFFFFFFF, %rcx\n"
    "testll %rcx, %rdx\n"
    "jz 0f\n" // zero zero, return the value passed directly
      // calculate sign
      "incll %rcx\n" // rcx becomes 0x80000...
      "fstp %st(0)\n"
      "fld1\n"
      "testl %rcx, %rdx\n"
      "jz 0f\n"
      "fchs\n"      
  	"0:\n"

#else

    "fsts -4(%esp)\n"
    "movl -4(%esp), %ecx\n"
    "movl $0x7FFFFFFF, %edx\n"
    "testl %edx, %ecx\n"
    "jz 0f\n" // zero zero, return the value passed directly
      // calculate sign
      "incl %edx\n" // edx becomes 0x8000...
      "fstp %st(0)\n"
      "fld1\n"
      "testl %edx, %ecx\n"
      "jz 0f\n"
      "fchs\n"      
  	"0:\n"
   
#endif
);
}
void nseel_asm_sign_end(void) {}



//---------------------------------------------------------------------------------------------------------------
void nseel_asm_bnot(void)
{
  __asm__(
    "testl %eax, %eax\n"
    "setz %al\n"   
    "andl $0xff, %eax\n"
  );
}
void nseel_asm_bnot_end(void) {}

//---------------------------------------------------------------------------------------------------------------
void nseel_asm_if(void) // not currently used on x86/x86-64
{
  __asm__(
#ifdef TARGET_X64
    "subl $8, %rsp\n"
    "testl %eax, %eax\n"
    "jz 0f\n"
    "movll $0xfefefefe, %rax\n"
    "call *%eax\n"
    "jmp 1f\n"
    "0:\n"
    "movll $0xfefefefe, %rax\n"
    "call *%eax\n"
    "1:\n"
    "addl $8, %rsp\n"
#else
    "subl $12, %esp\n"
    "testl %eax, %eax\n"
    "jz 0f\n"
    "movl $0xfefefefe, %eax\n"
    "call *%eax\n"
    "jmp 1f\n"
    "0:\n"
    "movl $0xfefefefe, %eax\n"
    "call *%eax\n"
    "1:\n"
    "addl $12, %esp\n"
#endif

  );
}
void nseel_asm_if_end(void) {}

//---------------------------------------------------------------------------------------------------------------
void nseel_asm_repeat(void)
{
  __asm__(
#ifdef TARGET_X64
    "fistpll -8(%esp)\n"
    "movll -8(%rsp), %rcx\n"
#else
    "fistpl -8(%esp)\n"
    "movl -8(%esp), %ecx\n"
#endif 
    "cmpl $1, %ecx\n"
    "jl 1f\n"
    "cmpl $" NSEEL_LOOPFUNC_SUPPORT_MAXLEN_STR ", %ecx\n"
    "jl 0f\n"
    "movl $" NSEEL_LOOPFUNC_SUPPORT_MAXLEN_STR ", %ecx\n"
"0:\n"
      "movl $0xfefefefe, %edx\n"
#ifdef TARGET_X64
      "subl $8, %esp\n" /* keep stack aligned to 16 byte */
#else
      "subl $4, %esp\n" /* keep stack aligned to 16 byte */
#endif
      "pushl %esi\n" // revert back to last temp workspace
      "pushl %ecx\n"
      
      "call *%edx\n"

      "popl %ecx\n"
      "popl %esi\n"
#ifdef TARGET_X64
      "addl $8, %esp\n" /* keep stack aligned to 16 byte */
#else
      "addl $4, %esp\n" /* keep stack aligned to 16 byte */
#endif
    "decl %ecx\n"
    "jnz 0b\n"
"1:\n"
  );
}
void nseel_asm_repeat_end(void) {}

//---------------------------------------------------------------------------------------------------------------
void nseel_asm_fcall(void)
{
  __asm__(
     "movl $0xfefefefe, %edx\n"
#ifdef TARGET_X64
     "subl $8, %esp\n" 
     "call *%edx\n"
     "addl $8, %esp\n"
#else
     "subl $12, %esp\n" /* keep stack 16 byte aligned, 4 bytes for return address */
     "call *%edx\n"
     "addl $12, %esp\n"
#endif
  );
}
void nseel_asm_fcall_end(void) {}

void nseel_asm_repeatwhile(void)
{
  __asm__(
    "movl $" NSEEL_LOOPFUNC_SUPPORT_MAXLEN_STR ", %ecx\n"
"0:\n"
      "movl $0xfefefefe, %edx\n"

#ifdef TARGET_X64
      "subl $8, %esp\n" /* keep stack aligned -- required on x86 and x64*/ 
#else
      "subl $4, %esp\n" /* keep stack aligned -- required on x86 and x64*/ 
#endif
      "pushl %esi\n" // revert back to last temp workspace
      "pushl %ecx\n"
      "call *%edx\n"
      "popl %ecx\n"
      "popl %esi\n"
#ifdef TARGET_X64
      "addl $8, %esp\n" /* keep stack aligned -- required on x86 and x64 */ 
#else
      "addl $4, %esp\n" /* keep stack aligned -- required on x86 and x64 */ 
#endif
	  "testl %eax, %eax\n"
	  "jz 0f\n"
    "decl %ecx\n"
    "jnz 0b\n"
	"0:\n"
  );
}
void nseel_asm_repeatwhile_end(void) {}


void nseel_asm_band(void)
{
  __asm__(
    "testl %eax, %eax\n"
    "jz 0f\n"

     "movl $0xfefefefe, %ecx\n"
#ifdef TARGET_X64
        "subl $8, %rsp\n"
#else
        "subl $12, %esp\n"
#endif
        "call *%ecx\n"
#ifdef TARGET_X64
        "addl $8, %rsp\n"
#else
        "addl $12, %esp\n"
#endif
    "0:\n"
  );
}
void nseel_asm_band_end(void) {}

void nseel_asm_bor(void)
{
  __asm__(
    "testl %eax, %eax\n"
    "jnz 0f\n"

    "movl $0xfefefefe, %ecx\n"
#ifdef TARGET_X64
    "subl $8, %rsp\n"
#else
    "subl $12, %esp\n"
#endif
    "call *%ecx\n"
#ifdef TARGET_X64
    "addl $8, %rsp\n"
#else
    "addl $12, %esp\n"
#endif
    "0:\n"
  );
}
void nseel_asm_bor_end(void) {}

//---------------------------------------------------------------------------------------------------------------
void nseel_asm_equal(void)
{
  __asm__(
    "fsub\n"
    "fabs\n"
#ifdef TARGET_X64
    "fcomp" EEL_F_SUFFIX " (%r13)\n" //[g_closefact]
#else
    "fcomp" EEL_F_SUFFIX " -8(%ebx)\n" //[g_closefact]
#endif
    "fstsw %ax\n"
    "andl $256, %eax\n" // old behavior: if 256 set, true (NaN means true)
  );
}
void nseel_asm_equal_end(void) {}
//
//---------------------------------------------------------------------------------------------------------------
void nseel_asm_notequal(void)
{
  __asm__(
    "fsub\n"
    "fabs\n"
#ifdef TARGET_X64
    "fcomp" EEL_F_SUFFIX " (%r13)\n" //[g_closefact]
#else
    "fcomp" EEL_F_SUFFIX " -8(%ebx)\n" //[g_closefact]
#endif
    "fstsw %ax\n"
    "andl $256, %eax\n"
    "xorl $256, %eax\n" // old behavior: if 256 set, FALSE (NaN makes for false)
  );
}
void nseel_asm_notequal_end(void) {}


//---------------------------------------------------------------------------------------------------------------
void nseel_asm_above(void)
{
  __asm__(
    "fcompp\n"
    "fstsw %ax\n"
    "andl $1280, %eax\n" //  (1024+256) old behavior: NaN would mean 1, preserve that
  );
}
void nseel_asm_above_end(void) {}

//---------------------------------------------------------------------------------------------------------------
void nseel_asm_beloweq(void)
{
  __asm__(
    "fcompp\n"
    "fstsw %ax\n"
    "andl $256, %eax\n" // old behavior: NaN would be 0 (ugh)
    "xorl $256, %eax\n"
  );
}
void nseel_asm_beloweq_end(void) {}


void nseel_asm_booltofp(void)
{
  __asm__(
    "testl %eax, %eax\n"
    "jz 0f\n"
    "fld1\n"
    "jmp 1f\n"
    "0:\n"
    "fldz\n"
    "1:\n"
  );
}
void nseel_asm_booltofp_end(void) {}

void nseel_asm_fptobool(void)
{
  __asm__(
    "fabs\n"
#ifdef TARGET_X64
    "fcomp" EEL_F_SUFFIX " (%r13)\n" //[g_closefact]
#else
    "fcomp" EEL_F_SUFFIX " -8(%ebx)\n" //[g_closefact]
#endif
    "fstsw %ax\n"
    "andl $256, %eax\n"
    "xorl $256, %eax\n"
  );
}
void nseel_asm_fptobool_end(void) {}


void nseel_asm_min(void)
{
  __asm__(
    "fld" EEL_F_SUFFIX " (%edi)\n"
    "fcomp" EEL_F_SUFFIX " (%eax)\n"
    "movl %eax, %ecx\n"
    "fstsw %ax\n"
    "testl $256, %eax\n"
    "movl %ecx, %eax\n"
    "jz 0f\n"
    "movl %edi, %eax\n"
    "0:\n"
    );

}
void nseel_asm_min_end(void) {}

void nseel_asm_max(void)
{
  __asm__(
    "fld" EEL_F_SUFFIX " (%edi)\n"
    "fcomp" EEL_F_SUFFIX " (%eax)\n"
    "movl %eax, %ecx\n"
    "fstsw %ax\n"
    "testl $256, %eax\n"
    "movl %ecx, %eax\n"
    "jnz 0f\n"
    "movl %edi, %eax\n"
    "0:\n"
    );
}
void nseel_asm_max_end(void) {}



void nseel_asm_min_fp(void)
{
  __asm__(
    "fcom\n"
    "fstsw %ax\n"
    "testl $256, %eax\n"
    "jz 0f\n"
    "fxch\n"
    "0:\n"
    "fstp %st(0)\n"
    );

}
void nseel_asm_min_fp_end(void) {}

void nseel_asm_max_fp(void)
{
  __asm__(
    "fcom\n"
    "fstsw %ax\n"
    "testl $256, %eax\n"
    "jnz 0f\n"
    "fxch\n"
    "0:\n"
    "fstp %st(0)\n"
    );
}
void nseel_asm_max_fp_end(void) {}



// just generic functions left, yay




void _asm_generic3parm(void)
{
  __asm__(
#ifdef TARGET_X64

#ifdef AMD64ABI

    "movl %rsi, %r15\n"
    "movl %rdi, %rdx\n" // third parameter = parm
    "movl $0xfefefefe, %rdi\n" // first parameter= context

    "movl %ecx, %rsi\n" // second parameter = parm
    "movl %rax, %rcx\n" // fourth parameter = parm
    "movl $0xfefefefe, %rax\n" // call function
    "subl $128, %rsp\n"
    "call *%rax\n"

    "movl %r15, %rsi\n"
    "addl $128, %rsp\n"

#else
    "movl %ecx, %edx\n" // second parameter = parm
    "movl $0xfefefefe, %ecx\n" // first parameter= context
    "movl %rdi, %r8\n" // third parameter = parm
    "movl %rax, %r9\n" // fourth parameter = parm
    "movl $0xfefefefe, %edi\n" // call function
    "subl $128, %rsp\n"
    "call *%edi\n"
    "addl $128, %rsp\n"
#endif

#else
    
    "movl $0xfefefefe, %edx\n"
    "pushl %eax\n" // push parameter
    "pushl %edi\n" // push parameter
    "movl $0xfefefefe, %edi\n"
    "pushl %ecx\n" // push parameter
    "pushl %edx\n" // push context pointer
    "call *%edi\n"
    "addl $16, %esp\n"
    
#endif
 );
}
void _asm_generic3parm_end(void) {}


void _asm_generic3parm_retd(void)
{
  __asm__(
#ifdef TARGET_X64
#ifdef AMD64ABI
    "movl %rsi, %r15\n"
    "movl %rdi, %rdx\n" // third parameter = parm
    "movl $0xfefefefe, %rdi\n" // first parameter= context
    "movl %ecx, %rsi\n" // second parameter = parm
    "movl %rax, %rcx\n" // fourth parameter = parm
    "movl $0xfefefefe, %rax\n" // call function
    "subl $128, %rsp\n"
    "call *%rax\n"
    "movl %r15, %rsi\n"
#else
    "movl %ecx, %edx\n" // second parameter = parm
    "movl $0xfefefefe, %ecx\n" // first parameter= context
    "movl %rdi, %r8\n" // third parameter = parm
    "movl %rax, %r9\n" // fourth parameter = parm
    "movl $0xfefefefe, %edi\n" // call function
    "subl $128, %rsp\n"
    "call *%edi\n"
#endif
    "movq xmm0, (%rsp)\n"
    "fldl (%rsp)\n"
    "addl $128, %rsp\n"
#else
    
    "subl $16, %esp\n"
    "movl %edi, 8(%esp)\n"
    "movl $0xfefefefe, %edx\n"
    "movl $0xfefefefe, %edi\n"
    "movl %eax, 12(%esp)\n"
    "movl %ecx, 4(%esp)\n"
    "movl %edx, (%esp)\n"
    "call *%edi\n"
    "addl $16, %esp\n"
    
#endif
 );
}
void _asm_generic3parm_retd_end(void) {}


void _asm_generic2parm(void) // this prob neds to be fixed for ppc
{
  __asm__(
#ifdef TARGET_X64

#ifdef AMD64ABI
    "movl %rsi, %r15\n"
    "movl %edi, %esi\n" // second parameter = parm
    "movl $0xfefefefe, %edi\n" // first parameter= context
    "movl %rax, %rdx\n" // third parameter = parm
    "movl $0xfefefefe, %rcx\n" // call function
    "subl $128, %rsp\n"
    "call *%rcx\n"
    "movl %r15, %rsi\n"
    "addl $128, %rsp\n"
#else
    "movl $0xfefefefe, %ecx\n" // first parameter= context
    "movl %edi, %edx\n" // second parameter = parm
    "movl %rax, %r8\n" // third parameter = parm
    "movl $0xfefefefe, %edi\n" // call function
    "subl $128, %rsp\n"
    "call *%edi\n"
    "addl $128, %rsp\n"
#endif
#else
    
    "movl $0xfefefefe, %edx\n"
    "movl $0xfefefefe, %ecx\n"
    "subl $4, %esp\n" // keep stack aligned
    "pushl %eax\n" // push parameter
    "pushl %edi\n" // push parameter
    "pushl %edx\n" // push context pointer
    "call *%ecx\n"
    "addl $16, %esp\n"
    
#endif
 );
}
void _asm_generic2parm_end(void) {}


void _asm_generic2parm_retd(void)
{
  __asm__(
#ifdef TARGET_X64
#ifdef AMD64ABI
    "movl %rsi, %r15\n"
    "movl %rdi, %rsi\n" // second parameter = parm
    "movl $0xfefefefe, %rdi\n" // first parameter= context
    "movl $0xfefefefe, %rcx\n" // call function
    "movl %rax, %rdx\n" // third parameter = parm
    "subl $128, %rsp\n"
    "call *%rcx\n"
    "movl %r15, %rsi\n"
#else
    "movl %rdi, %rdx\n" // second parameter = parm
    "movl $0xfefefefe, %rcx\n" // first parameter= context
    "movl $0xfefefefe, %rdi\n" // call function
    "movl %rax, %r8\n" // third parameter = parm
    "subl $128, %rsp\n"
    "call *%edi\n"
#endif
    "movq xmm0, (%rsp)\n"
    "fldl (%rsp)\n"
    "addl $128, %rsp\n"
#else
    
    "subl $16, %esp\n"
    "movl $0xfefefefe, %edx\n"
    "movl $0xfefefefe, %ecx\n"
    "movl %edx, (%esp)\n"
    "movl %edi, 4(%esp)\n"
    "movl %eax, 8(%esp)\n"
    "call *%ecx\n"
    "addl $16, %esp\n"
    
#endif
 );
}
void _asm_generic2parm_retd_end(void) {}





void _asm_generic1parm(void) 
{
  __asm__(
#ifdef TARGET_X64
#ifdef AMD64ABI
    "movl $0xfefefefe, %rdi\n" // first parameter= context
    "movl %rsi, %r15\n"
    "movl %eax, %rsi\n" // second parameter = parm
    "subl $128, %rsp\n"
    "movl $0xfefefefe, %rcx\n" // call function
    "call *%rcx\n"
    "movl %r15, %rsi\n"
    "addl $128, %rsp\n"
#else
    "movl $0xfefefefe, %ecx\n" // first parameter= context
    "movl %eax, %edx\n" // second parameter = parm
    "movl $0xfefefefe, %edi\n" // call function
    "subl $128, %rsp\n"
    "call *%edi\n"
    "addl $128, %rsp\n"
#endif
#else
    
    "movl $0xfefefefe, %edx\n"
    "subl $8, %esp\n" // keep stack aligned
    "movl $0xfefefefe, %ecx\n"
    "pushl %eax\n" // push parameter
    "pushl %edx\n" // push context pointer
    "call *%ecx\n"
    "addl $16, %esp\n"
    
#endif

 );
}
void _asm_generic1parm_end(void) {}


void _asm_generic1parm_retd(void) // 1 parameter returning double
{
  __asm__(
#ifdef TARGET_X64
    "subl $128, %rsp\n"
#ifdef AMD64ABI
    "movl $0xfefefefe, %rdi\n" // first parameter = context pointer
    "movl $0xfefefefe, %rcx\n" // function address
    "movl %rsi, %r15\n" // save rsi
    "movl %rax, %rsi\n" // second parameter = parameter

    "call *%rcx\n"
    
    "movl %r15, %rsi\n"
#else
    "movl $0xfefefefe, %ecx\n" // first parameter= context
    "movl $0xfefefefe, %edi\n" // call function

    "movl %rax, %rdx\n" // second parameter = parm

    "call *%edi\n"
#endif
    "movq xmm0, (%rsp)\n"
    "fldl (%rsp)\n"
    "addl $128, %rsp\n"
#else
    
    "movl $0xfefefefe, %edx\n" // context pointer
    "movl $0xfefefefe, %ecx\n" // func-addr
    "subl $16, %esp\n"
    "movl %eax, 4(%esp)\n" // push parameter
    "movl %edx, (%esp)\n" // push context pointer
    "call *%ecx\n"
    "addl $16, %esp\n"
    
#endif
 );
}
void _asm_generic1parm_retd_end(void) {}





// this gets its own stub because it's pretty crucial for performance :/

void _asm_megabuf(void)
{
  __asm__(


#ifdef TARGET_X64


#ifdef AMD64ABI

    "fadd" EEL_F_SUFFIX " -8(%r12)\n"
    "subll %rdx, %rdx\n"

    "fistpl -8(%rsp)\n"

    // check if -8(%rsp) is in range, and buffer available, otherwise call function
    "movl -8(%rsp), %edx\n"
    "testl $0xff800000, %rdx\n" // 0xFFFFFFFF - (NSEEL_RAM_BLOCKS*NSEEL_RAM_ITEMSPERBLOCK - 1)
    "jnz 1f\n"
    "movll %rdx, %rax\n"
    "shrll $13, %rax\n"     // log2(NSEEL_RAM_ITEMSPERBLOCK) - log2(sizeof(void*))
    "andll $0x3F8, %rax\n"  // (NSEEL_RAM_BLOCKS-1)*sizeof(void*)
    "movll (%r12, %rax), %rax\n"
    "testl %rax, %rax\n"
    "jz 1f\n"
    "andll $0xFFFF, %rdx\n" // (NSEEL_RAM_ITEMSPERBLOCK-1)
    "shlll $3, %rdx\n"      // log2(sizeof(EEL_F))
    "addll %rdx, %rax\n"
    "jmp 0f\n"

    
    "1:\n"
    "movl $0xfefefefe, %rax\n"
    "movl %r12, %rdi\n" // set first parm to ctx
    "movl %rsi, %r15\n" // save rsi
    "movl %rdx, %esi\n" // esi becomes second parameter (edi is first, context pointer)
    "subl $128, %rsp\n"
    "call *%rax\n"
    "movl %r15, %rsi\n" // restore rsi
    "addl $128, %rsp\n"
    "0:\n"

#else

    "fadd" EEL_F_SUFFIX " -8(%r12)\n"
    "subll %rdi, %rdi\n"

    "fistpl -8(%esp)\n"

    // check if -8(%esp) is in range...
    "movl -8(%rsp), %edi\n"
    "testl $0xff800000, %edi\n"   // 0xFFFFFFFF - (NSEEL_RAM_BLOCKS*NSEEL_RAM_ITEMSPERBLOCK - 1)
    "jnz 1f\n"
    "movll %rdi, %rax\n"
    "shrll $13, %rax\n"           // log2(NSEEL_RAM_ITEMSPERBLOCK) - log2(sizeof(void*))
    "andll $0x3F8, %rax\n"        // (NSEEL_RAM_BLOCKS-1)*sizeof(void*)
    "movll (%r12, %rax), %rax\n"
    "testl %rax, %rax\n"
    "jz 1f\n"
    "andll $0xFFFF, %rdi\n"   // (NSEEL_RAM_ITEMSPERBLOCK-1)
    "shlll $3, %rdi\n"        // log2(sizeof(EEL_F))
    "addll %rdi, %rax\n"
    "jmp 0f\n"

    "1:\n"
    "movl $0xfefefefe, %rax\n" // function ptr
    "movl %r12, %rcx\n" // set first parm to ctx
    "movl %rdi, %rdx\n" // rdx is second parameter (rcx is first)
    "subl $128, %rsp\n"
    "call *%rax\n"
    "addl $128, %rsp\n"
    "0:"
#endif


#else
    "fadd" EEL_F_SUFFIX " -8(%ebx)\n"
    "fistpl -8(%esp)\n"

    // check if -8(%esp) is in range, and buffer available, otherwise call function
    "movl -8(%esp), %edi\n"
    "testl $0xff800000, %edi\n"  // 0xFFFFFFFF - (NSEEL_RAM_BLOCKS*NSEEL_RAM_ITEMSPERBLOCK - 1)
    "jnz 1f\n"

    "movl %edi, %eax\n"
    "shrl $14, %eax\n"            // log2(NSEEL_RAM_ITEMSPERBLOCK) - log2(sizeof(void *))
    "andl $0x1FC, %eax\n"    // (NSEEL_RAM_BLOCKS-1)*sizeof(void*)
    "movl (%ebx, %eax), %eax\n"
    "testl %eax, %eax\n"
    "jz 1f\n"
    "andl $0xFFFF, %edi\n"  // (NSEEL_RAM_ITEMSPERBLOCK-1)
    "shll $3, %edi\n"       // log2(sizeof(EEL_F))
    "addl %edi, %eax\n"
    "jmp 0f\n"


    "1:\n"
    "subl $8, %esp\n" // keep stack aligned
    "movl $0xfefefefe, %ecx\n"
    "pushl %edi\n" // parameter
    "pushl %ebx\n" // push context pointer
    "call *%ecx\n"
    "addl $16, %esp\n"

    "0:"


#endif



 );
}

void _asm_megabuf_end(void) {}


void _asm_gmegabuf(void)
{
  __asm__(


#ifdef TARGET_X64


#ifdef AMD64ABI

    "movl %rsi, %r15\n"
    "fadd" EEL_F_SUFFIX " (%r13)\n"
    "movl $0xfefefefe, %rdi\n" // first parameter = context pointer
    "xorl %rsi, %rsi\n"
    "fistpl -8(%rsp)\n"
    "movl -8(%rsp), %esi\n" 
    "movl $0xfefefefe, %edx\n"
    "subl $128, %rsp\n"
    "call *%edx\n"
    "movl %r15, %rsi\n"
    "addl $128, %rsp\n"

#else
    "movl $0xfefefefe, %ecx\n" // first parameter = context pointer
    "fadd" EEL_F_SUFFIX " (%r13)\n"
    "fistpl -8(%esp)\n"
    "xorl %rdx, %rdx\n"
    "movl -8(%esp), %edx\n"
    "movl $0xfefefefe, %edi\n"
    "subl $128, %rsp\n"
    "call *%edi\n"
    "addl $128, %rsp\n"
#endif


#else
    "movl $0xfefefefe, -16(%esp)\n"
    "fadd" EEL_F_SUFFIX " -8(%ebx)\n"
    "movl $0xfefefefe, %edi\n"
    "fistpl -12(%esp)\n"
    "subl $16, %esp\n" // keep stack aligned
    "call *%edi\n"
    "addl $16, %esp\n"

#endif



 );
}

void _asm_gmegabuf_end(void) {}

void nseel_asm_stack_push(void)
{
#ifdef TARGET_X64
  __asm__(
    "movl $0xfefefefe, %rdi\n"
    "movll (%rax), %rcx\n"
    "movll (%rdi), %rax\n"
    "addll $8, %rax\n"
    "movl $0xFEFEFEFE, %rdx\n"
    "andll %rdx, %rax\n"
    "movl $0xFEFEFEFE, %rdx\n"
    "orll %rdx, %rax\n"
    "movll %rcx, (%rax)\n"
    "movll %rax, (%rdi)\n"
    );
#else

  __asm__(
    "movl $0xfefefefe, %edi\n"
    
    "movl (%eax), %ecx\n"
    "movl 4(%eax), %edx\n"

    "movl (%edi), %eax\n"

    "addl $8, %eax\n"
    "andl $0xfefefefe, %eax\n"
    "orl $0xfefefefe, %eax\n"
    
    "movl %ecx, (%eax)\n"
    "movl %edx, 4(%eax)\n"

    "movl %eax, (%edi)\n"
  );

#endif

}
void nseel_asm_stack_push_end(void) {}



void nseel_asm_stack_pop(void)
{
#ifdef TARGET_X64

  __asm__(
      "movl $0xfefefefe, %rdi\n"
      "movll (%rdi), %rcx\n"
      "movq (%rcx), %xmm0\n"
      "subll $8, %rcx\n"
      "movl $0xFEFEFEFE, %rdx\n"
      "andll %rdx, %rcx\n"
      "movl $0xFEFEFEFE, %rdx\n"
      "orll %rdx, %rcx\n"
      "movll %rcx, (%rdi)\n"
      "movq %xmm0, (%eax)\n"
    );

#else

  __asm__(
    "movl $0xfefefefe, %edi\n"
    "movl (%edi), %ecx\n"
    "fld" EEL_F_SUFFIX  " (%ecx)\n"
    "subl $8, %ecx\n"
    "andl $0xfefefefe, %ecx\n"
    "orl $0xfefefefe, %ecx\n"
    "movl %ecx, (%edi)\n"
    "fstp" EEL_F_SUFFIX " (%eax)\n"
  );

#endif
}
void nseel_asm_stack_pop_end(void) {}


void nseel_asm_stack_pop_fast(void)
{
#ifdef TARGET_X64

  __asm__(
      "movl $0xfefefefe, %rdi\n"
      "movll (%rdi), %rcx\n"
      "movll %rcx, %rax\n"
      "subll $8, %rcx\n"
      "movl $0xFEFEFEFE, %rdx\n"
      "andll %rdx, %rcx\n"
      "movl $0xFEFEFEFE, %rdx\n"
      "orll %rdx, %rcx\n"
      "movll %rcx, (%rdi)\n"
    );

#else

  __asm__(
    "movl $0xfefefefe, %edi\n"
    "movl (%edi), %ecx\n"
    "movl %ecx, %eax\n"
    "subl $8, %ecx\n"
    "andl $0xfefefefe, %ecx\n"
    "orl $0xfefefefe, %ecx\n"
    "movl %ecx, (%edi)\n"        
  );

#endif
}
void nseel_asm_stack_pop_fast_end(void) {}

void nseel_asm_stack_peek_int(void)
{
#ifdef TARGET_X64

  __asm__(
    "movll $0xfefefefe, %rdi\n"
    "movll (%rdi), %rax\n"   
    "movl $0xfefefefe, %rdx\n"
    "subll %rdx, %rax\n"
    "movl $0xFEFEFEFE, %rdx\n"
    "andll %rdx, %rax\n"
    "movl $0xFEFEFEFE, %rdx\n"
    "orll %rdx, %rax\n"
  );

#else

  __asm__(
    "movl $0xfefefefe, %edi\n"
    "movl (%edi), %eax\n"   
    "movl $0xfefefefe, %edx\n"
    "subl %edx, %eax\n"
    "andl $0xfefefefe, %eax\n"
    "orl $0xfefefefe, %eax\n"
  );

#endif

}
void nseel_asm_stack_peek_int_end(void) {}



void nseel_asm_stack_peek(void)
{
#ifdef TARGET_X64

  __asm__(
    "movll $0xfefefefe, %rdi\n"
    "fistpl -8(%rsp)\n"
    "movll (%rdi), %rax\n"   
    "movll -8(%rsp), %rdx\n"
    "shll $3, %rdx\n" // log2(sizeof(EEL_F))
    "subl %rdx, %rax\n"
    "movl $0xFEFEFEFE, %rdx\n"
    "andll %rdx, %rax\n"
    "movl $0xFEFEFEFE, %rdx\n"
    "orll %rdx, %rax\n"
  );

#else

  __asm__(
    "movl $0xfefefefe, %edi\n"
    "fistpl -8(%esp)\n"
    "movl (%edi), %eax\n"   
    "movl -8(%esp), %edx\n"
    "shll $3, %edx\n" // log2(sizeof(EEL_F))
    "subl %edx, %eax\n"
    "andl $0xfefefefe, %eax\n"
    "orl $0xfefefefe, %eax\n"
  );

#endif

}
void nseel_asm_stack_peek_end(void) {}


void nseel_asm_stack_peek_top(void)
{
#ifdef TARGET_X64

  __asm__(
    "movll $0xfefefefe, %rdi\n"
    "movll (%rdi), %rax\n"   
  );

#else

  __asm__(
    "movl $0xfefefefe, %edi\n"
    "movl (%edi), %eax\n"   
  );

#endif

}
void nseel_asm_stack_peek_top_end(void) {}

void nseel_asm_stack_exch(void)
{
#ifdef TARGET_X64

  __asm__(
    "movll $0xfefefefe, %rdi\n"
    "movll (%rdi), %rcx\n"   
    "movq (%rcx), %xmm0\n"
    "movq (%rax), %xmm1\n"
    "movq %xmm0, (%rax)\n"
    "movq %xmm1, (%rcx)\n"
  );

#else

  __asm__(
    "movl $0xfefefefe, %edi\n"
    "movl (%edi), %ecx\n"   
    "fld" EEL_F_SUFFIX  " (%ecx)\n"
    "fld" EEL_F_SUFFIX  " (%eax)\n"
    "fstp" EEL_F_SUFFIX  " (%ecx)\n"
    "fstp" EEL_F_SUFFIX " (%eax)\n"
  );

#endif

}
void nseel_asm_stack_exch_end(void) {}

#ifdef TARGET_X64
void win64_callcode() 
{
	__asm__(
		"push %rbx\n"
		"push %rbp\n"
		"push %r12\n"
		"push %r13\n"
		"push %r14\n"
		"push %r15\n"

#ifdef AMD64ABI
    "movll %rsi, %r12\n" // second parameter is ram-blocks pointer
    "movll %rdx, %r13\n" // third parameter is ptr to g_closefact
		"call %rdi\n"
#else
		"push %rdi\n"
		"push %rsi\n"
    "movll %rdx, %r12\n" // second parameter is ram-blocks pointer
    "movll %r8, %r13\n" // third parameter is ptr to g_closefact
		"call %rcx\n"
		"pop %rsi\n"
		"pop %rdi\n"
#endif

		"fclex\n"

		"pop %r15\n"
		"pop %r14\n"
		"pop %r13\n"
		"pop %r12\n"
		"pop %rbp\n"
		"pop %rbx\n"
		"ret\n"
	);
}

#endif
