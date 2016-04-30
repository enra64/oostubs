
a.out:     file format elf64-x86-64


Disassembly of section .init:

0000000000400390 <_init>:
  400390:	48 83 ec 08          	sub    $0x8,%rsp
  400394:	48 8b 05 a5 05 20 00 	mov    0x2005a5(%rip),%rax        # 600940 <_DYNAMIC+0x1d0>
  40039b:	48 85 c0             	test   %rax,%rax
  40039e:	74 05                	je     4003a5 <_init+0x15>
  4003a0:	e8 3b 00 00 00       	callq  4003e0 <__libc_start_main@plt+0x10>
  4003a5:	48 83 c4 08          	add    $0x8,%rsp
  4003a9:	c3                   	retq   

Disassembly of section .plt:

00000000004003b0 <printf@plt-0x10>:
  4003b0:	ff 35 9a 05 20 00    	pushq  0x20059a(%rip)        # 600950 <_GLOBAL_OFFSET_TABLE_+0x8>
  4003b6:	ff 25 9c 05 20 00    	jmpq   *0x20059c(%rip)        # 600958 <_GLOBAL_OFFSET_TABLE_+0x10>
  4003bc:	0f 1f 40 00          	nopl   0x0(%rax)

00000000004003c0 <printf@plt>:
  4003c0:	ff 25 9a 05 20 00    	jmpq   *0x20059a(%rip)        # 600960 <_GLOBAL_OFFSET_TABLE_+0x18>
  4003c6:	68 00 00 00 00       	pushq  $0x0
  4003cb:	e9 e0 ff ff ff       	jmpq   4003b0 <_init+0x20>

00000000004003d0 <__libc_start_main@plt>:
  4003d0:	ff 25 92 05 20 00    	jmpq   *0x200592(%rip)        # 600968 <_GLOBAL_OFFSET_TABLE_+0x20>
  4003d6:	68 01 00 00 00       	pushq  $0x1
  4003db:	e9 d0 ff ff ff       	jmpq   4003b0 <_init+0x20>

Disassembly of section .plt.got:

00000000004003e0 <.plt.got>:
  4003e0:	ff 25 5a 05 20 00    	jmpq   *0x20055a(%rip)        # 600940 <_DYNAMIC+0x1d0>
  4003e6:	66 90                	xchg   %ax,%ax

Disassembly of section .text:

00000000004003f0 <_start>:
  4003f0:	31 ed                	xor    %ebp,%ebp
  4003f2:	49 89 d1             	mov    %rdx,%r9
  4003f5:	5e                   	pop    %rsi
  4003f6:	48 89 e2             	mov    %rsp,%rdx
  4003f9:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  4003fd:	50                   	push   %rax
  4003fe:	54                   	push   %rsp
  4003ff:	49 c7 c0 e0 05 40 00 	mov    $0x4005e0,%r8
  400406:	48 c7 c1 70 05 40 00 	mov    $0x400570,%rcx
  40040d:	48 c7 c7 e6 04 40 00 	mov    $0x4004e6,%rdi
  400414:	e8 b7 ff ff ff       	callq  4003d0 <__libc_start_main@plt>
  400419:	f4                   	hlt    
  40041a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000400420 <deregister_tm_clones>:
  400420:	b8 87 09 60 00       	mov    $0x600987,%eax
  400425:	55                   	push   %rbp
  400426:	48 2d 80 09 60 00    	sub    $0x600980,%rax
  40042c:	48 83 f8 0e          	cmp    $0xe,%rax
  400430:	48 89 e5             	mov    %rsp,%rbp
  400433:	76 1b                	jbe    400450 <deregister_tm_clones+0x30>
  400435:	b8 00 00 00 00       	mov    $0x0,%eax
  40043a:	48 85 c0             	test   %rax,%rax
  40043d:	74 11                	je     400450 <deregister_tm_clones+0x30>
  40043f:	5d                   	pop    %rbp
  400440:	bf 80 09 60 00       	mov    $0x600980,%edi
  400445:	ff e0                	jmpq   *%rax
  400447:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  40044e:	00 00 
  400450:	5d                   	pop    %rbp
  400451:	c3                   	retq   
  400452:	0f 1f 40 00          	nopl   0x0(%rax)
  400456:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  40045d:	00 00 00 

0000000000400460 <register_tm_clones>:
  400460:	be 80 09 60 00       	mov    $0x600980,%esi
  400465:	55                   	push   %rbp
  400466:	48 81 ee 80 09 60 00 	sub    $0x600980,%rsi
  40046d:	48 c1 fe 03          	sar    $0x3,%rsi
  400471:	48 89 e5             	mov    %rsp,%rbp
  400474:	48 89 f0             	mov    %rsi,%rax
  400477:	48 c1 e8 3f          	shr    $0x3f,%rax
  40047b:	48 01 c6             	add    %rax,%rsi
  40047e:	48 d1 fe             	sar    %rsi
  400481:	74 15                	je     400498 <register_tm_clones+0x38>
  400483:	b8 00 00 00 00       	mov    $0x0,%eax
  400488:	48 85 c0             	test   %rax,%rax
  40048b:	74 0b                	je     400498 <register_tm_clones+0x38>
  40048d:	5d                   	pop    %rbp
  40048e:	bf 80 09 60 00       	mov    $0x600980,%edi
  400493:	ff e0                	jmpq   *%rax
  400495:	0f 1f 00             	nopl   (%rax)
  400498:	5d                   	pop    %rbp
  400499:	c3                   	retq   
  40049a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

00000000004004a0 <__do_global_dtors_aux>:
  4004a0:	80 3d d9 04 20 00 00 	cmpb   $0x0,0x2004d9(%rip)        # 600980 <__TMC_END__>
  4004a7:	75 11                	jne    4004ba <__do_global_dtors_aux+0x1a>
  4004a9:	55                   	push   %rbp
  4004aa:	48 89 e5             	mov    %rsp,%rbp
  4004ad:	e8 6e ff ff ff       	callq  400420 <deregister_tm_clones>
  4004b2:	5d                   	pop    %rbp
  4004b3:	c6 05 c6 04 20 00 01 	movb   $0x1,0x2004c6(%rip)        # 600980 <__TMC_END__>
  4004ba:	f3 c3                	repz retq 
  4004bc:	0f 1f 40 00          	nopl   0x0(%rax)

00000000004004c0 <frame_dummy>:
  4004c0:	bf 68 07 60 00       	mov    $0x600768,%edi
  4004c5:	48 83 3f 00          	cmpq   $0x0,(%rdi)
  4004c9:	75 05                	jne    4004d0 <frame_dummy+0x10>
  4004cb:	eb 93                	jmp    400460 <register_tm_clones>
  4004cd:	0f 1f 00             	nopl   (%rax)
  4004d0:	b8 00 00 00 00       	mov    $0x0,%eax
  4004d5:	48 85 c0             	test   %rax,%rax
  4004d8:	74 f1                	je     4004cb <frame_dummy+0xb>
  4004da:	55                   	push   %rbp
  4004db:	48 89 e5             	mov    %rsp,%rbp
  4004de:	ff d0                	callq  *%rax
  4004e0:	5d                   	pop    %rbp
  4004e1:	e9 7a ff ff ff       	jmpq   400460 <register_tm_clones>

00000000004004e6 <main>:
  4004e6:	55                   	push   %rbp
  4004e7:	48 89 e5             	mov    %rsp,%rbp
  4004ea:	48 83 ec 10          	sub    $0x10,%rsp
  4004ee:	c6 45 f7 05          	movb   $0x5,-0x9(%rbp)
  4004f2:	48 8d 45 f7          	lea    -0x9(%rbp),%rax
  4004f6:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  4004fa:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  4004fe:	48 89 c6             	mov    %rax,%rsi
  400501:	bf f4 05 40 00       	mov    $0x4005f4,%edi
  400506:	b8 00 00 00 00       	mov    $0x0,%eax
  40050b:	e8 b0 fe ff ff       	callq  4003c0 <printf@plt>
  400510:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  400514:	0f b6 00             	movzbl (%rax),%eax
  400517:	0f be c0             	movsbl %al,%eax
  40051a:	89 c6                	mov    %eax,%esi
  40051c:	bf 02 06 40 00       	mov    $0x400602,%edi
  400521:	b8 00 00 00 00       	mov    $0x0,%eax
  400526:	e8 95 fe ff ff       	callq  4003c0 <printf@plt>
  40052b:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  40052f:	c6 00 16             	movb   $0x16,(%rax)
  400532:	48 8d 45 f7          	lea    -0x9(%rbp),%rax
  400536:	48 89 c6             	mov    %rax,%rsi
  400539:	bf 10 06 40 00       	mov    $0x400610,%edi
  40053e:	b8 00 00 00 00       	mov    $0x0,%eax
  400543:	e8 78 fe ff ff       	callq  4003c0 <printf@plt>
  400548:	0f b6 45 f7          	movzbl -0x9(%rbp),%eax
  40054c:	0f be c0             	movsbl %al,%eax
  40054f:	89 c6                	mov    %eax,%esi
  400551:	bf 1e 06 40 00       	mov    $0x40061e,%edi
  400556:	b8 00 00 00 00       	mov    $0x0,%eax
  40055b:	e8 60 fe ff ff       	callq  4003c0 <printf@plt>
  400560:	b8 00 00 00 00       	mov    $0x0,%eax
  400565:	c9                   	leaveq 
  400566:	c3                   	retq   
  400567:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  40056e:	00 00 

0000000000400570 <__libc_csu_init>:
  400570:	41 57                	push   %r15
  400572:	41 56                	push   %r14
  400574:	41 89 ff             	mov    %edi,%r15d
  400577:	41 55                	push   %r13
  400579:	41 54                	push   %r12
  40057b:	4c 8d 25 d6 01 20 00 	lea    0x2001d6(%rip),%r12        # 600758 <__frame_dummy_init_array_entry>
  400582:	55                   	push   %rbp
  400583:	48 8d 2d d6 01 20 00 	lea    0x2001d6(%rip),%rbp        # 600760 <__init_array_end>
  40058a:	53                   	push   %rbx
  40058b:	49 89 f6             	mov    %rsi,%r14
  40058e:	49 89 d5             	mov    %rdx,%r13
  400591:	4c 29 e5             	sub    %r12,%rbp
  400594:	48 83 ec 08          	sub    $0x8,%rsp
  400598:	48 c1 fd 03          	sar    $0x3,%rbp
  40059c:	e8 ef fd ff ff       	callq  400390 <_init>
  4005a1:	48 85 ed             	test   %rbp,%rbp
  4005a4:	74 20                	je     4005c6 <__libc_csu_init+0x56>
  4005a6:	31 db                	xor    %ebx,%ebx
  4005a8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  4005af:	00 
  4005b0:	4c 89 ea             	mov    %r13,%rdx
  4005b3:	4c 89 f6             	mov    %r14,%rsi
  4005b6:	44 89 ff             	mov    %r15d,%edi
  4005b9:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  4005bd:	48 83 c3 01          	add    $0x1,%rbx
  4005c1:	48 39 eb             	cmp    %rbp,%rbx
  4005c4:	75 ea                	jne    4005b0 <__libc_csu_init+0x40>
  4005c6:	48 83 c4 08          	add    $0x8,%rsp
  4005ca:	5b                   	pop    %rbx
  4005cb:	5d                   	pop    %rbp
  4005cc:	41 5c                	pop    %r12
  4005ce:	41 5d                	pop    %r13
  4005d0:	41 5e                	pop    %r14
  4005d2:	41 5f                	pop    %r15
  4005d4:	c3                   	retq   
  4005d5:	90                   	nop
  4005d6:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  4005dd:	00 00 00 

00000000004005e0 <__libc_csu_fini>:
  4005e0:	f3 c3                	repz retq 

Disassembly of section .fini:

00000000004005e4 <_fini>:
  4005e4:	48 83 ec 08          	sub    $0x8,%rsp
  4005e8:	48 83 c4 08          	add    $0x8,%rsp
  4005ec:	c3                   	retq   
