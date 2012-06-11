/*
 * Copyright/Licensing information.
 */

#include "propertiesfiletype.h"
#include "translatable.h"

#include <stdio.h>
#include <string.h>

void process_lines(gchar *contents, Translatable *tr);
void process_line(gchar *line, Translatable *tr);

/* Public methods */

void properties_file_type_read_file (PropertiesFileType *self, Translatable *tr, gchar *file_name)
{
    gchar *contents = 0;
    GError *read_error = 0;
    gsize length = -1;
    g_file_get_contents(file_name, &contents, &length, &read_error);
    process_lines (contents, tr);
    g_free (contents);
}

/* This is called when the class is initialized */
void properties_file_type_class_init (gpointer klass, gpointer klass_data)
{
    FileTypeClass *parent_class = FILE_TYPE_CLASS (klass);

    /* virtual methods */
    parent_class->read_file = (void *)(properties_file_type_read_file);
}

/* this is the constructor */
void properties_file_type_instance_init (GTypeInstance *instance, gpointer klass)
{
    //properties_file_type_read_file(instance, "yow");
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

void process_lines(gchar *contents, Translatable *tr)
{
    gchar *end, *cur = contents;
    while (1)
    {
        end = g_strstr_len(cur, -1, "\n");
        if (end)
        {
            *end = 0;
            //printf("%s\n", cur);
            process_line(cur, tr);
            *end = '\n';
            cur = end+1;
        }
        else
            break;
    }
}

void process_line(gchar *line, Translatable *tr)
{
    gchar *equalpos, *key, *value, *stripped_line, *comment = NULL;
    static gboolean note_on = FALSE;
    static int entry_index = -1;
    stripped_line = g_strdup(line);
    if (*stripped_line == '#')
    {
        if (g_str_has_prefix(stripped_line, "# LOCALIZATION NOTE ("))
        {
            note_on = TRUE;
            gchar *note = stripped_line + strlen("# LOCALIZATION NOTE (");
            //GList *list = NULL;
            //find_elements_for_note(note, list);
            //g_list_free_full(list, g_free);
        }
        else if (note_on == TRUE)
        {
            gchar *tmp = comment;
            comment = g_strjoin(NULL, comment, stripped_line, NULL);
            if (tmp != NULL)
                g_free(tmp);
        }
    }
    else
    {
        note_on = FALSE;
        if (equalpos = g_strstr_len(stripped_line, -1, "="))
        {
            entry_index++;
            *equalpos = 0;
            key = g_strdup(stripped_line);
            *equalpos = '=';
            value = g_strdup(equalpos+1);
            //g_printf("--- key = %s, value = %s\n", key, value);
            translatable_add_entry (tr, entry_index, key, NULL, "en", value);
            g_free(value);
        }
    }
    g_free(stripped_line);
}