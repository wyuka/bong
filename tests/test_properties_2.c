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
    gchar *input_contents = NULL, *output_contents = NULL;
    GError *read_error = NULL;
    gsize length = -1;

    if (argc < 2)
        return 0;

    g_type_init();

    ty = properties_file_type_new();
    tr = translatable_new();

    translatable_init (tr, ty);
    g_file_get_contents(argv[1], &input_contents, &length, &read_error);
    translatable_read_contents (tr, input_contents);

    translatable_set_string_for_uik(tr, "contextMenuSearchText", "en", "haha");
    output_contents = translatable_write_contents (tr, input_contents);
    g_printf("%s", output_contents);
    g_free (output_contents);
    g_free (input_contents);
    translatable_destroy (tr);

    return 0;
}
