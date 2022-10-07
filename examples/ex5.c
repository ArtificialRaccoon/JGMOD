/*      An example by Guan Foo Wah
 *   
 *      Shows how to load MODs from datafile using method after calling
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

    // should load datafile after install_mod (only if it contains JGM)
    // If you want to load datafile before install_mod, refer to ex6.c
    dat = load_datafile ("yea.dat");
    if (dat == NULL)
        {
        printf ("Error : Unable to load yea.dat\n");
        return 1;
        }

    play_mod (dat[YEAM].dat, TRUE);

    readkey();
    return 0;
}
END_OF_MAIN();

