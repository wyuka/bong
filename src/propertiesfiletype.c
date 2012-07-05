/*
 * Copyright/Licensing information.
 */

#include "propertiesfiletype.h"
#include "translatable.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>

/* Public methods */

void properties_file_type_read_file (PropertiesFileType *self, Translatable *tr, gchar *file_name)
{
    gchar *input_contents = NULL;
    GError *read_error = NULL;
    gsize length = -1;
    g_file_get_contents(file_name, &input_contents, &length, &read_error);
    properties_file_type_read_contents (self, tr, input_contents);
    g_free (input_contents);
}

void properties_file_type_write_file (PropertiesFileType *self, Translatable *tr, gchar *file_name)
{
    gchar *input_contents = NULL;
    gchar *output_contents = NULL;
    GError *read_error = NULL;
    gsize length = -1;
    g_file_get_contents(file_name, &input_contents, &length, &read_error);
    output_contents = properties_file_type_write_contents (self, tr, input_contents);
    g_free (input_contents);
    g_printf("%s", output_contents);
    g_free(output_contents);
}

/* This is called when the class is initialized */
void properties_file_type_class_init (gpointer klass, gpointer klass_data)
{
    FileTypeClass *parent_class = FILE_TYPE_CLASS (klass);

    /* virtual methods */
    parent_class->read_file = (void *)(properties_file_type_read_file);
    parent_class->read_contents = (void *)(properties_file_type_read_contents);
    parent_class->write_file = (void *)(properties_file_type_write_file);
    parent_class->write_contents = (void *)(properties_file_type_write_contents);
}

/* this is the constructor */
void properties_file_type_instance_init (GTypeInstance *instance, gpointer klass)
{
    /* not needed atm */
}

GType properties_file_type_get_type (void)
{
    static GType type = 0;

    if (type == 0)
    {
        static const GTypeInfo type_info =
        {
            sizeof (PropertiesFileTypeClass),
            NULL,                   /* base_init */
            NULL,                   /* base_finalize */
            properties_file_type_class_init,   /* class_init */
            NULL,                   /* class_final */
            NULL,                   /* class_data */
            sizeof (PropertiesFileType),
            0,                      /* n_preallocs */
            properties_file_type_instance_init /* instance_init */
        };

        type = g_type_register_static (TYPE_FILE_TYPE, "PropertiesFileType", &type_info, 0);
    }

    return type;
}

/* Private methods */

void properties_file_type_read_contents (PropertiesFileType *self, Translatable *tr, gchar *input_contents)
{
    gchar *equalpos, *key, *value, *stripped_line, *note = NULL;
    GList *key_list = NULL, *key_list_for_note = NULL, *note_list_for_keys = NULL, *note_list = NULL;
    gchar *end, *line = input_contents;
    gboolean note_on = FALSE;
    int entry_number = -1;
    while (1)
    {
        end = g_strstr_len(line, -1, "\n");
        if (end)
        {
            *end = '\0';

            stripped_line = g_strdup(line);
            g_strstrip(stripped_line);
            if (*stripped_line == '#')
            {
                if (g_str_has_prefix(stripped_line, "# LOCALIZATION NOTE (") || g_str_has_prefix(stripped_line, "# LOCALIZATION NOTE ("))
                {
                    if (note_on)
                    {
                        GList *notekey = key_list_for_note;
                        if (notekey != NULL && note != NULL)
                        {
                            note_list = g_list_prepend(note_list, note);
                        }
                        while (notekey != NULL)
                        {
                            note_list_for_keys = g_list_prepend(note_list_for_keys, note);
                            key_list = g_list_prepend(key_list, notekey->data);
                            notekey = notekey->next;
                        }
                    }

                    note = NULL;
                    if (key_list_for_note)
                        g_list_free(key_list_for_note);
                    key_list_for_note = NULL;

                    gchar *keystart = g_strstr_len(stripped_line, -1, "(");
                    gchar *keyend = g_strstr_len(keystart, -1, ")");

                    if (keystart && keyend)
                    {
                        note_on = TRUE;
                        key_list_for_note = find_elements_for_note(keystart + 1, keyend - keystart - 1);
                        gchar *notestart = g_strstr_len(keyend, -1, ":");
                        if (notestart && notestart[1] != '\0')
                        {
                            note = g_strdup(notestart+1);
                            g_strstrip(note);
                        }
                    }
                }
                else if (note_on == TRUE)
                {
                    gchar *noteline = g_strstrip(g_strdup(stripped_line+1));
                    if (note)
                    {
                        gchar *tmp = note;
                        note = g_strjoin("\n", note, noteline, NULL);
                        g_free(tmp);
                        g_free(noteline);
                    }
                    else
                    {
                        note = noteline;
                    }
                }
            }
            else
            {
                if (note_on == TRUE)
                {
                    GList *notekey = key_list_for_note;
                    if (notekey != NULL && note != NULL)
                    {
                        note_list = g_list_prepend(note_list, note);
                    }
                    while (notekey != NULL)
                    {
                        note_list_for_keys = g_list_prepend(note_list_for_keys, note);
                        key_list = g_list_prepend(key_list, notekey->data);
                        notekey = notekey->next;
                    }
                }
                note_on = FALSE;
                if (equalpos = g_strstr_len(stripped_line, -1, "="))
                {
                    entry_number++;
                    key = g_strstrip(g_strndup(stripped_line, equalpos - stripped_line));
                    value = g_strstrip(g_strdup(equalpos+1));
                    translatable_add_entry (tr, entry_number, key, NULL, "en", value);
                    g_free(key);
                    g_free(value);
                }
            }
            g_free(stripped_line);

            *end = '\n';
            line = end + 1;
        }
        else
            break;
    }
    GList *note_item = note_list_for_keys, *key_item = key_list;
    while (key_item != NULL)
    {
        translatable_set_note_for_uik (tr, key_item->data, note_item->data);
        key_item = key_item->next;
        note_item = note_item->next;
    }

    g_list_free(note_list_for_keys);
    g_list_free_full(note_list, g_free);
    g_list_free_full(key_list, g_free);
}

gchar* properties_file_type_write_contents(PropertiesFileType *self, Translatable *tr, gchar *input_contents)
{
    gchar *equalpos, *key, *value, *stripped_line, *output_contents = g_strdup(""), *tmp;
    gchar *end, *line = input_contents;

    while (1)
    {
        end = g_strstr_len(line, -1, "\n");
        if (end)
        {
            *end = '\0';

            stripped_line = g_strdup(line);
            g_strstrip(stripped_line);
            if (*stripped_line != '#' && (equalpos = g_strstr_len(stripped_line, -1, "=")))
            {
                key = g_strstrip(g_strndup(stripped_line, equalpos - stripped_line));
                value = translatable_get_string_for_uik(tr, key, "en");
                tmp = output_contents;
                output_contents = g_strjoin("", output_contents, key, "=", value, "\n", NULL);
                g_free(tmp);
                g_free(key);
            }
            else
            {
                tmp = output_contents;
                output_contents = g_strjoin("", output_contents, line, "\n", NULL);
                g_free(tmp);
            }
            g_free(stripped_line);
            
            *end = '\n';
            line = end + 1;
        }
        else
            break;
    }
    return output_contents;
}