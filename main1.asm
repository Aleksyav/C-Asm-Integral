section .data
	const2 dd 2.0
	const1 dd -1.0
	const3 dd 1.0
	;const4 dd 2.815424
	const5 dd 3.0
	;control dw 0x077f

section .text

	global f1
	f1:
	push ebp
	mov ebp , esp
	and esp , 0xfffffff0
	;____________
	finit
	;fldcw word[control] ;pos
	fldl2e
	fmul dword[ebp + 8]
	fld st0
	frndint
	fld dword[const3]
	fscale
  fxch st2
	fsub st1
	f2xm1
	fadd dword[const3]
	fmul st2
	fld1
	fxch
	fdivp
	fadd dword[const5]
	;____________
	mov esp , ebp
	pop ebp
	ret

	global f2
	f2:
	push ebp
	mov ebp , esp
	and esp , 0xfffffff0
	;____________
	finit
	fld dword[ebp + 8]
	fadd dword[const1]
	fmul dword[const2]
	;____________
	mov esp , ebp
	pop ebp
	ret

	global f3
	f3:
	push ebp
	mov ebp , esp
	and esp , 0xfffffff0
	;____________
	finit
	fld dword[const3]
	fdiv dword[ebp + 8]
	;fstp eax
	;____________
	mov esp , ebp
	pop ebp
	ret
