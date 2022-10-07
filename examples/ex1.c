
/*      An example by Guan Foo Wah
 *   
 *      This code shows how JGMOD can be initialized and play mod
 */

#define USE_CONSOLE

#include <stdio.h>
#include <allegro.h>
#include <jgmod.h>

JGMOD *ex;

int main ()
{
    allegro_init ();
    install_timer();            // must call this!!
    install_keyboard();
    reserve_voices (8, -1);     // call this before install_sound if needed
    if (install_sound (DIGI_AUTODETECT, MIDI_NONE, NULL) < 0)
        {
        printf ("Error initializing sound card");
        return 1;
        }

    if (install_mod (8) < 0)    // call install_mod only after install_sound
        {
        printf ("Error setting digi voices");
        return 1;
        }

    ex = load_mod ("introgho.mod");    
    if (ex == NULL)
        {
        printf ("Error reading introgho.mod");
        return 1;
        }

    play_mod (ex, TRUE);

    readkey();
    stop_mod();
    destroy_mod (ex);
    return 0;
}
END_OF_MAIN();

