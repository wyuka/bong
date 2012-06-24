/*
 * Copyright/Licensing information.
 */

#include "dtdfiletype.h"
#include "translatable.h"

#include <stdio.h>
#include <glib.h>
#include <string.h>

void process_lines_for_read(gchar *input_contents, Translatable *tr);
gchar* process_lines_for_write(gchar *input_contents, Translatable *tr);

/* Public methods */

void dtd_file_type_read_file (DtdFileType *self, Translatable *tr, gchar *file_name)
{
    gchar *input_contents = NULL;
    GError *read_error = NULL;
    gsize length = -1;
    g_file_get_contents(file_name, &input_contents, &length, &read_error);
    process_lines_for_read (input_contents, tr);
    g_free (input_contents);
}

void dtd_file_type_write_file (DtdFileType *self, Translatable *tr, gchar *file_name)
{
    gchar *input_contents = NULL;
    gchar *output_contents = NULL;
    GError *read_error = NULL;
    gsize length = -1;
    g_file_get_contents(file_name, &input_contents, &length, &read_error);
    output_contents = process_lines_for_write (input_contents, tr);
    g_free (input_contents);
    g_printf("%s", output_contents);
    g_free(output_contents);
}

/* This is called when the class is initialized */
void dtd_file_type_class_init (gpointer klass, gpointer klass_data)
{
    FileTypeClass *parent_class = FILE_TYPE_CLASS (klass);

    /* virtual methods */
    parent_class->read_file = (void *)(dtd_file_type_read_file);
    parent_class->write_file = (void *)(dtd_file_type_write_file);
}

/* this is the constructor */
void dtd_file_type_instance_init (GTypeInstance *instance, gpointer klass)
{
    //dtd_file_type_read_file(instance, "yow");
    /* not needed atm */
}

GType dtd_file_type_get_type (void)
{
    static GType type = 0;

    if (type == 0)
    {
        static const GTypeInfo type_info =
        {
            sizeof (DtdFileTypeClass),
            NULL,                   /* base_init */
            NULL,                   /* base_finalize */
            dtd_file_type_class_init,   /* class_init */
            NULL,                   /* class_final */
            NULL,                   /* class_data */
            sizeof (DtdFileType),
            0,                      /* n_preallocs */
            dtd_file_type_instance_init /* instance_init */
        };

        type = g_type_register_static (TYPE_FILE_TYPE, "DtdFileType", &type_info, 0);
    }

    return type;
}

GList* find_elements_for_note(gchar *start, int length)
{
    gchar *comma = NULL, *keystr = start;
    GList *next = NULL;
    int lengthleft = length;
    while(comma = g_strstr_len(keystr, lengthleft, ","))
    {
        *comma = '\0';
        next = g_list_prepend(next, g_strdup(keystr));
        *comma = ',';
        lengthleft -= comma - keystr + 1;
        keystr = comma + 1;
        if (keystr >= start + length)
            return;
    }
    start[length] = '\0';
    next = g_list_prepend(next, g_strdup(keystr));
    start[length] = ')';
    return next;
}

void process_lines_for_read(gchar *input_contents, Translatable *tr)
{
    int entry_number = -1;
    GError *error = 0;
    GMatchInfo *match_info;
    GRegex *string_regex = NULL, *note_regex = NULL;

    string_regex = g_regex_new("<!ENTITY\\s+?(.*)\\s*?\"(.*)\">", G_REGEX_UNGREEDY|G_REGEX_DOTALL, 0, &error);
    g_regex_match(string_regex, input_contents, 0, &match_info);
    while (g_match_info_matches (match_info))
    {
        gchar *key = g_match_info_fetch(match_info, 1);
        gchar *value = g_match_info_fetch(match_info, 2);
        //g_printf("%s = %s\n", key, value);
        entry_number++;
        translatable_add_entry (tr, entry_number, key, NULL, "en", value);
        g_match_info_next(match_info, NULL);
        g_free(key);
        g_free(value);
    }
    g_match_info_free(match_info);
    g_regex_unref(string_regex);

    note_regex = g_regex_new("<!--\\s*LOCALIZATION NOTE\\s*?\\((.*)\\)\\s*:\\s*?(.*)\\s*?-->", G_REGEX_UNGREEDY|G_REGEX_DOTALL, 0, &error);
    g_regex_match(note_regex, input_contents, 0, &match_info);
    while (g_match_info_matches (match_info))
    {
        gchar *key = g_match_info_fetch(match_info, 1);
        GList *key_list = find_elements_for_note(key, strlen(key));
        gchar *value = g_match_info_fetch(match_info, 2);
        //g_printf("%s = %s\n", key, value);
        GList *key_item = key_list;
        while (key_item != NULL)
        {
            translatable_set_note (tr, key_item->data, value);
            key_item = key_item->next;
        }
        g_list_free_full(key_list, g_free);
        g_free(key);
        g_free(value);
        g_match_info_next(match_info, NULL);
    }
    g_match_info_free(match_info);
    g_regex_unref(string_regex);
}

gchar* process_lines_for_write(gchar *input_contents, Translatable *tr)
{
    GError *error = 0;
    GMatchInfo *match_info;
    GRegex *string_regex = NULL;
    int lastpos = 0;
    gchar *output_contents = g_strdup(""), *line, *tmp;
    
    string_regex = g_regex_new("<!ENTITY\\s+?(.*)\\s*?\"(.*)\">", G_REGEX_UNGREEDY|G_REGEX_DOTALL, 0, &error);
    g_regex_match(string_regex, input_contents, 0, &match_info);
    while (g_match_info_matches (match_info))
    {
        int startpos, endpos;
        g_match_info_fetch_pos (match_info, 0, &startpos, &endpos);
        input_contents[startpos] = '\0';
        tmp = output_contents;
        output_contents = g_strjoin ("", output_contents, input_contents + lastpos, NULL);
        g_free (tmp);
        input_contents[startpos] = '<';
        lastpos = endpos;

        gchar *key = g_match_info_fetch(match_info, 1);
        gchar *value = translatable_get_string_for_uik(tr, key, "en");
        line = g_strdup_printf("<!ENTITY %s \"%s\">", key, value);
        tmp = output_contents;
        output_contents = g_strjoin ("", output_contents, line, NULL);
        g_free (tmp);
        g_free (line);
        g_match_info_next (match_info, NULL);
        g_free (key);
    }
    g_match_info_free(match_info);
    g_regex_unref(string_regex);

    return output_contents;
}