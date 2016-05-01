/*
1	movl	$0x0	,	0	x18	(%esp)
2	jmp	pos2

3	pos1	:
4	mov	0x18(%esp), %eax    # save a to eax
5	mov	%eax,	(%esp)        # write 0 to the position the stack top pointer points to
6	call	func
7	addl	$0x1	,	0x18	(%esp)  # add 1 to a

8	pos2	:
9	cmpl	$0x9	,	0x18	(%esp)
10 jle	pos1
*/

int32_t a = 0;
goto pos2;

pos1:
func();
a++;

pos2:
if(a <= 0x9)
  goto pos1;

/*
1	cmpl	$0x5	,	0	x18	(%esp)
2	jne	pos3
3	call doSomething
4	pos3	:
*/

if(a != 0x5)
  goto pos3;
else
  doSomething();
