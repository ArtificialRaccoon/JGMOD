/* registration code for setting up the sample object plugin */
{
   extern DATEDIT_OBJECT_INFO datmod_info;
   extern DATEDIT_GRABBER_INFO datmod_grabber;
   extern DATEDIT_MENU_INFO stop_mod_info;
   extern DATEDIT_MENU_INFO toggle_mod_info;
   extern void register_datafile_jgmod(void);

   datedit_register_object(&datmod_info);
   datedit_register_grabber(&datmod_grabber);
   datedit_register_menu(&stop_mod_info);
   datedit_register_menu(&toggle_mod_info);

   register_datafile_jgmod();
}
