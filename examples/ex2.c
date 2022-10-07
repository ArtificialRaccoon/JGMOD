
/*      An example by Guan Foo Wah
 *
 *      Shows how MOD and WAV can be played together. Also applicable
 *      to MIDI but not really useful.
 */

#define USE_CONSOLE

#include <stdio.h>
#include <allegro.h>
#include <jgmod.h>

JGMOD *ex;
SAMPLE *slash;
int input;

int main (void)
{
    allegro_init ();
    install_timer();            // must call this!!
    reserve_voices (16, -1);
    install_keyboard();

    if (install_sound (DIGI_AUTODETECT, MIDI_NONE, NULL) < 0)
        {
        printf ("Error initializing sound card");
        return 1;
        }

    if (install_mod (4) < 0)    // leave some for sfx. 4 voices for mod. And
        {                       // 12 for wavs. Get it ?
        printf ("Error setting digi voices");
        return 1;
        }

    ex = load_mod ("introgho.mod");    
    if (ex==NULL)
        {
        printf ("Error reading introgho.mod");
        return 1;
        }

    slash = load_wav ("slash.wav");
    if (slash == NULL)
        {
        printf ("Error reading slash.wav");
        return 1;
        }

    set_mod_volume (128);
    play_mod (ex, TRUE);

    printf ("Press space to play sfx. ESC to escape\n");

    while (1)
        {
        input = readkey() >> 8;

        if (input == KEY_ESC)
            break;

        if (input == KEY_SPACE)
            play_sample (slash, 255, 128, 1000, FALSE);

        }

    return 0;
}
END_OF_MAIN();

