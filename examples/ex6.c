/*      An example by Guan Foo Wah
 *   
 *      Shows how to load MODs from datafile using method 2 before calling
 *      install_mod().
 */

#define USE_CONSOLE

#include <stdio.h>
#include <allegro.h>
#include <jgmod.h>
#include "yea.h"

DATAFILE *dat;

int main(void)
{
    allegro_init();
    install_timer();
    install_keyboard();

    // if you want to load a datafile which contains JGM before calling
    // install_mod(), you have to register_datafile_object just like the
    // line below.

    //register_datafile_object (JGM_ID, load_jgm_datafile, destroy_mod_datafile);
    register_datafile_jgmod();

    dat = load_datafile ("yea.dat");
    if (dat == NULL)
        {
        printf ("Error : Unable to load yea.dat\n");
        return 1;
        }

    if (install_sound (DIGI_AUTODETECT, MIDI_NONE, NULL) < 0)
        {
        printf ("Error : Unable to initialize sound card\n");
        return 1;
        }

    if (install_mod (4) < 0)
        {
        printf ("Error : Unable to set up voices\n");
        return 1;
        }

    play_mod (dat[YEAM].dat, TRUE);

    readkey();
    return 0;
}
END_OF_MAIN();

