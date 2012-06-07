/*
 * Copyright/Licensing information.
 */

#include "translatable.h"
#include "dtdfile.h"
#include "localestring.h"

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

    LocaleString *l = locale_string_new ("en", "I love you");
    translatable_add_localestring (tr, "I love you", l);
    l = locale_string_new ("bn", "Amar tomake bhalo lage");
    translatable_add_localestring (tr, "I like you", l);
    l = locale_string_new ("bn", "Ami tomake bhalobashi");
    translatable_add_localestring (tr, "I love you", l);
    l = locale_string_new ("en", "I like you");
    translatable_add_localestring (tr, "I like you", l);
    l = translatable_find_localestring(tr, "I love you", "bn");
    g_debug("%s", locale_string_get_string(l));
    l = translatable_find_localestring(tr, "I love you", "en");
    g_debug("%s", locale_string_get_string(l));
    l = translatable_find_localestring(tr, "I like you", "bn");
    g_debug("%s", locale_string_get_string(l));
    l = translatable_find_localestring(tr, "I like you", "en");
    g_debug("%s", locale_string_get_string(l));

    translatable_destroy (tr);

    return 0;
}