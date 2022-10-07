/*      An example by Guan Foo Wah
 *   
 *      Shows how to load MODs from datafile using method 1
 */

#define USE_CONSOLE

#include <stdio.h>
#include <allegro.h>
#include <jgmod.h>

JGMOD *yea;

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

    // load the file from a datafile. 
    yea = load_mod ("yea.dat#yeam");
    if (yea == NULL)
        {
        printf ("Error : Unable to load yea.dat#yeam\n");
        return 1;
        }

    play_mod (yea, TRUE);

    readkey();
    return 0;
}
END_OF_MAIN();

