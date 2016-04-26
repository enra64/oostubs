#include	<stdio.h>
int	main(){
  char	a;
  a=5;
  char	*p	=	&a;
  printf("p	address	%p\n",	p);
  printf("p	content	%d\n",	*p);
  *p=22;
  printf("a	address	%p\n",	&a);
  printf("a	content	%d\n",	a);
}
