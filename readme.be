BEOS specific information


-----------
BEOS Notes
-----------
Thanks to Angelo Mottola for porting JGMOD to BEOS 5.


---------------
Compiling JGMOD
---------------
Err.... I don't really know how since I do not have a BEOS. If anyone 
knows how, please write one and send it to me. Your name would be displayed 
here as a contributor :)



Using JGMOD
-----------
Include jgmod.h after including allegro.h. For example,

#include <allegro.h>
#include <jgmod.h>


Make sure you include jgmod.h after allegro.h. Otherwise you will get a
error message when compiling.

                                           
If you upgrade or downgrade your Allegro or JGMOD to newer or older wips or
something, then you need to recompile JGMOD. Just type "make veryclean" to
delete all those objects and executable files. Then type "make" to recompile.
