/*
 * Copyright/Licensing information.
 */

#include <translatable.h>
#include <propertiesfiletype.h>

#include <glib-object.h>

int main(int argc, char* argv[])
{
    Translatable *tr = NULL;
    FileType *ty = NULL;
    int k;

    if (argc < 2)
        return 0;

    g_type_init();

    ty = properties_file_type_new();
    tr = translatable_new();

    translatable_init (tr, ty);
    translatable_read_file (tr, argv[1], "en");

    translatable_set_string_for_uik(tr, "contextMenuSearchText", "en", "haha");
    translatable_write_file (tr, argv[1], "en");
    translatable_destroy (tr);

    return 0;
}
