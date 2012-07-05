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
    int k;

    if (argc < 2)
        return 0;

    g_type_init();

    ty = g_object_new(TYPE_PROPERTIES_FILE_TYPE, NULL);
    tr = translatable_new();

    translatable_init (tr, FILE_TYPE(ty));
    translatable_read_file (tr, argv[1]);

    translatable_set_string_for_uik(tr, "contextMenuSearchText", "en", "haha");
    translatable_write_file (tr, argv[1]);
    translatable_destroy (tr);

    return 0;
}
