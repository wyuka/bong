/*
 * Copyright/Licensing information.
 */

#include "translatable.h"
#include "propertiesfiletype.h"

#include <glib-object.h>

int main(int argc, char* argv[])
{
    Translatable *tr = NULL;
    PropertiesFileType *ty = NULL;

    if (argc < 2)
        return 0;

    g_type_init();

    ty = g_object_new(TYPE_PROPERTIES_FILE_TYPE, NULL);
    tr = translatable_new();

    translatable_init (tr, FILE_TYPE(ty));
    translatable_read_file (tr, argv[1]);
    
    g_printf("%s\n", translatable_get_string_for_uik (tr, "cmd_clearHistory", "en"));
    g_printf("%d\n", translatable_get_entry_index_for_uik (tr, "cmd_clearHistory"));
    g_printf("%s\n", translatable_get_string_for_entry_index (tr, 1, "en"));

    translatable_destroy (tr);

    return 0;
}
