#include	<stdio.h>
int	main(){
  char	a;
  a=5;
// get pointer to a
  char	*p	=	&a;
// give value of p and value of address pointed to by p
  printf("p	address	%p\n",	p);
  printf("p	content	%d\n",	*p);
// overwrite p with garbage
  *p=22;
// a still exists
  printf("a	address	%p\n",	&a);
  printf("a	content	%d\n",	a);
}
