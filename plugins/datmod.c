#include <stdio.h>


#include <allegro.h>
#include "../datedit.h"
#include <jgmod.h>


void *jgmod_calloc (int size);
void *save_jgm (PACKFILE *f, JGMOD* j);
int plugin_stop_mod (void);
int plugin_toggle_mod (void);

/* creates a new mod object */
static void *makenew_mod(long *size)
{
    return jgmod_calloc (sizeof (JGMOD));
}


/* displays a mod in the grabber object view window */
static void plot_mod(DATAFILE *dat, int x, int y)
{
    JGMOD *the_mod = (JGMOD *)dat->dat;

    if ((the_mod->bpm!=null) && (the_mod->no_pat!=null) && (the_mod->no_trk!=null) )
        {
        textprintf (screen, font, x,y+32, gui_fg_color, "Song name   : %s  ", the_mod->name);
        textprintf (screen, font, x,y+44, gui_fg_color, "No Channels : %2d ", the_mod->no_chn);
        textprintf (screen, font, x,y+56, gui_fg_color, "Period Type : %s  ", (the_mod->flag & LINEAR_MODE) ? "Linear" : "Amiga");
        textprintf (screen, font, x,y+68, gui_fg_color, "No Inst     : %2d ", the_mod->no_instrument);
        textprintf (screen, font, x,y+80, gui_fg_color, "No Tracks   : %2d ", the_mod->no_trk);
        textprintf (screen, font, x,y+92, gui_fg_color, "No Patterns : %2d ", the_mod->no_pat);
        textprintf (screen, font, x,y+104, gui_fg_color, "No Sample   : %2d ", the_mod->no_sample);
        }
}


/* handles double-clicking on a mod in the grabber */
static int dclick_mod(DATAFILE *dat)
{
    int no_chn;

    JGMOD *j = (JGMOD *)dat->dat;

    if ((j->bpm!=null) && (j->no_pat!=null) && (j->no_trk!=null) )
        {
        no_chn = j->no_chn;
        if (no_chn > 64)
            no_chn = 64;

        remove_mod();
        remove_sound();
        reserve_voices (no_chn, -1);
        if (install_sound (DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0)
            {
            reserve_voices (-1, -1);
            install_sound (DIGI_NONE, MIDI_NONE, NULL);
            }

        install_mod(no_chn);
        play_mod(j, FALSE);
        }
    return D_O_K;
}


/* returns an information string describing a mod object */
static void get_mod_desc(DATAFILE *dat, char *s)
{
    JGMOD *the_mod = (JGMOD *)dat->dat;

    if ((the_mod->bpm!=null) && (the_mod->no_pat!=null) && (the_mod->no_trk!=null) )
        sprintf (s, "Double click to play");
    else
        sprintf (s, "Empty. Grab a Mod, please :-)");
}


/* exports a mod into an external file */
static int export_mod(DATAFILE *dat, char *filename)
{
    JGMOD *j;
    PACKFILE *f;

    j = (JGMOD *)dat->dat;

    if ((j->bpm!=null) && (j->no_pat!=null) && (j->no_trk!=null) )
        {
        f = pack_fopen(filename, F_WRITE);

        if (f)
            {
            save_jgm (f, dat->dat);
            pack_fclose(f);
            }
        }

    return (errno == 0);
}


/* imports a mod from an external file */
static void *grab_mod(char *filename, long *size, int x, int y, int w, int h, int depth)
{
    fast_loading = FALSE;
    enable_m15 = TRUE;

    return load_mod(filename);
}


/* saves a mod into the datafile format */
static void save_mod(DATAFILE *dat, int packed, int packkids, int strip, int verbose, int extra, PACKFILE *f)
{
    save_jgm (f ,dat->dat);
}


int plugin_stop_mod (void)
{
    stop_mod();
    return D_O_K;
}

int plugin_toggle_mod (void)
{
    toggle_pause_mode();
    return D_O_K;
}


/* plugin interface header */
DATEDIT_OBJECT_INFO datmod_info =
{
   JGM_ID, 
   "MOD", 
   get_mod_desc,
   makenew_mod,
   save_mod,
   plot_mod,
   dclick_mod,
   NULL
};


DATEDIT_GRABBER_INFO datmod_grabber =
{
   JGM_ID, 
   "mod;s3m;xm;jgm;umx",
   "jgm",
   grab_mod,
   export_mod
};


/* hook ourselves into the grabber menu system */
MENU stop_mod_menu =
{
   "Stop Mod",
   plugin_stop_mod,
   NULL,
   0,
   NULL
};

DATEDIT_MENU_INFO stop_mod_info =
{
   &stop_mod_menu,
   NULL,
   DATEDIT_MENU_OBJECT,
   0
};

MENU toggle_mod_menu =
{
   "Pause/Resume Mod",
   plugin_toggle_mod,
   NULL,
   0,
   NULL
};

DATEDIT_MENU_INFO toggle_mod_info =
{
   &toggle_mod_menu,
   NULL,
   DATEDIT_MENU_OBJECT,
   0
};
