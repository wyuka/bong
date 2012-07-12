/*
 * Copyright/Licensing information.
 */

#include "propertiesfiletype.h"
#include <translatable.h>
#include <utils.h>

#include <stdio.h>
#include <string.h>

/* Public methods */

FileType* properties_file_type_new (void)
{
    return FILE_TYPE(g_object_new(TYPE_PROPERTIES_FILE_TYPE, NULL));
}

void properties_file_type_read_file (PropertiesFileType *self, Translatable *tr, gchar *file_name)
{
    gchar *input_contents = NULL;
    GError *read_error = NULL;
    gsize length = -1;
    /* read file contents into an allocated string */
    g_file_get_contents(file_name, &input_contents, &length, &read_error);
    /* parse the contents */
    properties_file_type_read_contents (self, tr, input_contents);
    /* free the string containing the file contents */
    g_free (input_contents);
}

void properties_file_type_write_file (PropertiesFileType *self, Translatable *tr, gchar *file_name)
{
    gchar *input_contents = NULL;
    gchar *output_contents = NULL;
    GError *read_error = NULL;
    gsize length = -1;
    /* read the input file contents into an allocated string */
    g_file_get_contents(file_name, &input_contents, &length, &read_error);

    /* fetch the modified file contents into another allocated string.
     * This string is created by modifying the input contents according
     * to entries in the Translatable object
     */
    output_contents = properties_file_type_write_contents (self, tr, input_contents);

    /* FIXME: for now, just printing the output contents.
     * Should write it to a new file
     */
    g_printf("%s", output_contents);

    /* free allocated strings after usage */
    g_free (input_contents);
    g_free(output_contents);
}

/* This is called when the class is initialized */
void properties_file_type_class_init (gpointer klass, gpointer klass_data)
{
    FileTypeClass *parent_class = FILE_TYPE_CLASS (klass);

    /* setup the vtable, override parent functions */
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

/* boilerplate code */
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
    gchar *equalpos, *key, *value, *stripped_line;
    GString *note_string = NULL;
    GList *key_list = NULL, *key_list_for_note = NULL, *note_list_for_keys = NULL, *note_list = NULL;
    gchar *end, *line = input_contents;
    gboolean note_on = FALSE, to_break = FALSE;
    int entry_number = -1;

    /* loop until asked to break */
    while (to_break == FALSE)
    {
        /* find the first occurence of a newline from current position */
        end = g_strstr_len(line, -1, "\n");
        if (end)
        {
            /* temporarily terminate the string at newline, to create a new line */
            *end = '\0';
        }
        else
        {
            /* this is the last line, need to break after this */
            to_break = TRUE;
        }

        /* strip current line of trailing and leading whitespaces */
        stripped_line = g_strdup(line);
        g_strstrip(stripped_line);

        /* if line is a comment */
        if (*stripped_line == '#')
        {
            /* if it starts off a localization note */
            if (g_str_has_prefix(stripped_line, "# LOCALIZATION NOTE (") || g_str_has_prefix(stripped_line, "# LOCALIZATION NOTE ("))
            {
                /* if last line was also part of a note */
                if (note_on)
                {
                    /* append the previous note to the global note list */
                    GList *notekey = key_list_for_note;
                    if (notekey != NULL && note_string != NULL)
                    {
                        note_list = g_list_prepend(note_list, note_string->str);
                    }
                    /* for every UIK for the note, add a copy of the note once
                     * to the list called note_list_for_keys, and a copy of the key
                     * to the list called key_list
                     */
                    while (notekey != NULL)
                    {
                        note_list_for_keys = g_list_prepend(note_list_for_keys, note_string->str);
                        key_list = g_list_prepend(key_list, notekey->data);
                        notekey = notekey->next;
                    }
                }

                /* clear all variables, need to store new note */
                if (note_string)
                    g_string_free(note_string, FALSE);
                note_string = NULL;
                if (key_list_for_note)
                    g_list_free(key_list_for_note);
                key_list_for_note = NULL;

                gchar *keystart = g_strstr_len(stripped_line, -1, "(");
                gchar *keyend = g_strstr_len(keystart, -1, ")");

                /* if UIK specified */
                if (keystart && keyend)
                {
                    note_on = TRUE;
                    /* tokenize comma-separated list of UIKs, store in list called key_list_for_note */
                    key_list_for_note = find_elements_for_note(keystart + 1, keyend - keystart - 1);

                    /* locate the start position of note */
                    gchar *notestart = g_strstr_len(keyend, -1, ":");

                    /* if some portion of the note exists in this line */
                    if (notestart && notestart[1] != '\0')
                    {
                        /* store the note and strip it of leading and trailing whitespaces */
                        gchar *temp = g_strstrip(g_strdup(notestart+1));
                        note_string = g_string_new(temp);
                        g_free(temp);
                    }
                }
            }
            /* else, if the line continues a localization note */
            else if (note_on == TRUE)
            {
                gchar *noteline = g_strstrip(g_strdup(stripped_line+1));
                /* if note was not empty previously */
                if (note_string)
                {
                    /* add the current line to the note */
                    g_string_append_printf(note_string, "\n%s", noteline);
                    g_free (noteline);
                }
                else
                {
                    /* copy this line as the note */
                    note_string = g_string_new(noteline);
                    g_free(noteline);
                }
            }
        }
        /* else, if it is not a comment line */
        else
        {
            /* if a note just finished */
            if (note_on == TRUE)
            {
                /* append the just finished note to the global note list */
                GList *notekey = key_list_for_note;
                if (notekey != NULL && note_string != NULL)
                {
                    note_list = g_list_prepend(note_list, note_string->str);
                }
                /* for every UIK for the note, add a copy of the note once
                 * to the list called note_list_for_keys, and a copy of the key
                 * to the list called key_list
                 */
                while (notekey != NULL)
                {
                    note_list_for_keys = g_list_prepend(note_list_for_keys, note_string->str);
                    key_list = g_list_prepend(key_list, notekey->data);
                    notekey = notekey->next;
                }
            }

            /* now we exit the note mode */
            note_on = FALSE;
            /* if line contains a localization string along with UIK, */
            if (equalpos = g_strstr_len(stripped_line, -1, "="))
            {
                entry_number++;
                key = g_strstrip(g_strndup(stripped_line, equalpos - stripped_line));
                value = g_strstrip(g_strdup(equalpos+1));
                /* add the localization string to the Translatable object for
                 * the retrieved UIK
                 */
                translatable_add_entry (tr, entry_number, key, NULL, "en", value);
                g_free(key);
                g_free(value);
            }
        }

        g_free(stripped_line);

        /* if this is not the last line, we had temporarily terminated the
         * input string at a newline. Restore the input string.
         */
        if (to_break != TRUE)
            *end = '\n';

        /* change the current position to just after the newline */
        line = end + 1;
    }

    /* traverse the key_list and note_list_for_keys
     * for correspoding key-value pairs for notes
     */
    GList *note_item = note_list_for_keys, *key_item = key_list;
    while (key_item != NULL)
    {
        /* store the notes for appropriate UIK in Translatable object */
        translatable_set_note_for_uik (tr, key_item->data, note_item->data);
        key_item = key_item->next;
        note_item = note_item->next;
    }

    /* free all allocated lists */
    g_list_free(note_list_for_keys);
    g_list_free_full(note_list, g_free);
    g_list_free_full(key_list, g_free);
}

gchar* properties_file_type_write_contents(PropertiesFileType *self, Translatable *tr, gchar *input_contents)
{
    gchar *equalpos, *key, *value, *stripped_line;
    GString *output_contents = g_string_new(NULL);
    gchar *end, *line = input_contents;
    gboolean to_break = FALSE;

    /* loop until asked to break */
    while (to_break == FALSE)
    {
        /* find the first occurence of a newline from current position */
        end = g_strstr_len(line, -1, "\n");
        if (end)
        {
            /* temporarily terminate the string at newline, to create a new line */
            *end = '\0';
        }
        else
        {
            /* this is the last line, we need to break after this */
            to_break = TRUE;
        }

        /* strip current line of trailing and leading whitespaces */
        stripped_line = g_strdup(line);
        g_strstrip(stripped_line);

        /* if line is not a comment, and contains a UIK and localization string, */
        if (*stripped_line != '#' && (equalpos = g_strstr_len(stripped_line, -1, "=")))
        {
            /* extract key from line */
            key = g_strstrip(g_strndup(stripped_line, equalpos - stripped_line));
            /* retrieve value of localized string for UIK from Translatable object */
            value = translatable_get_string_for_uik(tr, key, "en");
            /* append the key-value pair to the output */
            g_string_append_printf(output_contents, "%s=%s\n", key, value);
            g_free(key);
        }
        /* if the line does not have a UIK and localization string */
        else
        {
            /* simply append the line to the output */
            if (to_break == FALSE)
                g_string_append_printf(output_contents, "%s\n", line);
            else
                g_string_append(output_contents, line);
        }
        g_free(stripped_line);

        /* if this is not the last line, we had temporarily terminated the
         * input string at a newline. Restore the input string.
         */
        if (to_break != TRUE)
            *end = '\n';

        /* change the current position to just after newline */
        line = end + 1;
    }
    if (output_contents)
        return g_string_free(output_contents, FALSE);
    else
        return NULL;
}