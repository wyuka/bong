/*
 * Copyright/Licensing information.
 */

#include "translatable.h"
#include "dtdfile.h"

#include <glib-object.h>

int main()
{
    Translatable *tr = NULL;
    DtdFileType *ty = NULL;
    g_type_init();

    ty = g_object_new(TYPE_DTD_FILE_TYPE, NULL);
    tr = translatable_new();

    translatable_init (tr, FILE_TYPE(ty));
    translatable_read_file (tr, "translatable.c");

    translatable_add_entry (tr, 0, "I love you", NULL, "en", "I love you");
    translatable_add_entry (tr, 3, "I like you", NULL, "bn", "Amar tomake bhalo lage");
    translatable_add_entry (tr, 2, "I love you", NULL, "bn", "Ami tomake bhalobasi");
    translatable_add_entry (tr, 1, "I like you", NULL, "en", "I like you");

    g_debug("%s", translatable_get_string_for_uik (tr, "I love you", "en"));
    g_debug("%s", translatable_get_string_for_uik (tr, "I love you", "bn"));
    g_debug("%s", translatable_get_string_for_uik (tr, "I like you", "en"));
    g_debug("%s", translatable_get_string_for_uik (tr, "I like you", "bn"));

    translatable_destroy (tr);

    return 0;
}