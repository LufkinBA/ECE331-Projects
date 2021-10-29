//test all the functions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gps.h"

int main(){
const char filename[]="umhab99-armtrack";
//test highlight
highlight("notthis,notthis,notthis,notthis,notthis\n",6);
highlight("notthis,notthis,notthis,notthis,this\n",5);
highlight("notthis,notthis,notthis,this,notthis\n",4);
highlight("notthis,notthis,this,notthis,notthis\n",3);
highlight("notthis,this,notthis,notthis,notthis\n",2);
highlight("this,notthis,notthis,notthis,notthis\n",1);
//test parsedata
parsedata(filename,1);
return 0;
}
