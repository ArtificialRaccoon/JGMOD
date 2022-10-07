
/*      An example by Guan Foo Wah
 *
 *      set_volume() will affect the volume of SFX and MOD. This shows
 *      how to change SFX volume without affecting MOD volume.
 */

#define USE_CONSOLE

#include <stdio.h>
#include <allegro.h>
#include <jgmod.h>

JGMOD *ex;
SAMPLE *slash;
int input;
int sfx_volume = 255;

int adjust_sfx_volume (int volume);

int main (void)
{
    allegro_init ();
    install_timer();            // must call this!!
    reserve_voices (16, -1);
    install_keyboard();

    if (install_sound (DIGI_AUTODETECT, MIDI_NONE, NULL) < 0)
        {
        printf ("Error Initializing sound card");
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

    set_mod_volume (125);
    play_mod (ex, TRUE);
    play_sample (slash, sfx_volume, 128, 1000, TRUE);

    printf (" reduce/increase SFX volume\n");
    printf (" reduce/increase MOD volume\n\n");

    while (1)
        {
        printf ("SFX volume : %3d    MOD volume : %3d\r", sfx_volume, get_mod_volume());
	fflush (stdout);

        input = readkey() >> 8;

        if (input == KEY_ESC)
            break;
        else if (input == KEY_DOWN)
            set_mod_volume (get_mod_volume() - 5);
        else if (input == KEY_UP)
            set_mod_volume (get_mod_volume() + 5);
        else if (input == KEY_LEFT)
            {
            sfx_volume = adjust_sfx_volume (sfx_volume - 5);
            adjust_sample (slash, sfx_volume , 128, 1000, TRUE);
            }
        else if (input == KEY_RIGHT)
            {
            sfx_volume = adjust_sfx_volume (sfx_volume + 5);
            adjust_sample (slash, sfx_volume , 128, 1000, TRUE);
            }
        }

    printf ("\n");
    return 0;
}
END_OF_MAIN();

int adjust_sfx_volume (int volume)
{
    if (volume < 0)
        return 0;
    else if (volume > 255)
        return 255;

    return volume;
}
