/*      An example by Guan Foo Wah
 *   
 *      Shows how to use get_mod_info() function to get some information
 *      about MODs.
 */

#define USE_CONSOLE

#include <stdio.h>
#include <allegro.h>
#include <jgmod.h>

int main (int argc, char **argv)
{
    JGMOD_INFO ji;

    allegro_init();

    if (argc != 2)
        {
        printf ("Syntax : ex7 <filename>\n");
        return 1;
        }

    enable_m15 = TRUE;
    if (get_mod_info (argv[1], &ji) > 0)
        {
        printf ("Name      : %s\n", ji.name);
        printf ("Type Name : %s\n", ji.type_name);
        printf ("Type No   : %d\n", ji.type);
        }
    else
        printf ("%s\n", jgmod_error);

    return 1;
}
END_OF_MAIN();

