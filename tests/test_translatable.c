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
    g_type_init();

    ty = properties_file_type_new();
    tr = translatable_new();

    translatable_init (tr, ty);

    translatable_add_entry (tr, 0, "I love you", NULL, "en", "I love you");
    translatable_add_entry (tr, 1, "I like you", NULL, "bn", "আমার তোমাকে ভালো লাগে");
    translatable_add_entry (tr, 0, "I love you", NULL, "bn", "আমি তোমায় ভালোবাসি");
    translatable_add_entry (tr, 0, "I love you", NULL, "hi", "मैं तुमसे प्यार करता हूँ");
    translatable_add_entry (tr, 1, "I like you", NULL, "en", "I like you");
    translatable_add_entry (tr, 1, "I like you", NULL, "hi", "मैं तुम्हें पसंद करता हूँ");

    g_printf("%s\n", translatable_get_string_for_uik (tr, "I love you", "en"));

    g_printf("%s\n", translatable_get_string_for_uik (tr, "I love you", "bn"));
    g_printf("%s\n", translatable_get_string_for_uik (tr, "I love you", "hi"));

    g_printf("%s\n", translatable_get_string_for_entry_index (tr, 0, "en"));
    g_printf("%s\n", translatable_get_string_for_entry_index (tr, 0, "bn"));
    g_printf("%s\n", translatable_get_string_for_entry_index (tr, 0, "hi"));

    g_printf("%s\n", translatable_get_string_for_uik (tr, "I like you", "en"));
    g_printf("%s\n", translatable_get_string_for_uik (tr, "I like you", "bn"));
    g_printf("%s\n", translatable_get_string_for_uik (tr, "I like you", "hi"));

    g_printf("%s\n", translatable_get_uik_for_entry_index (tr, 0));
    g_printf("%d\n", translatable_get_entry_index_for_uik (tr, "I love you"));
    g_printf("%s\n", translatable_get_uik_for_entry_index (tr, 1));
    g_printf("%d\n", translatable_get_entry_index_for_uik (tr, "I like you"));

    translatable_destroy (tr);

    return 0;
}