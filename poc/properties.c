#include <glib.h>
#include <stdio.h>
#include <string.h>
//#include "dtd.h"

GHashTable *dtd_hash_table;

gchar* read_source_file(gchar **contents, gsize *length, const gchar *filename)
{
    GError *error;
    g_file_get_contents(filename, contents, length, &error);
}

void find_elements_for_note(gchar *start, GList *list)
{
    //g_strstr_len();
    //list = g_list_append(list, );
    gchar *com = NULL, *paren = NULL;
    paren = strchr(start, ')');
    *paren = '\0';
    while ((com = strchr(start, ',')) != NULL)
    {
        *com = '\0';
        //printf("%s\n", start);
        *com = ',';
        start = com + 1;
    }
    //printf("%s\n", start);
    *paren = ')';
    //printf("%s\n", paren + 2);
}

void process_line(const gchar *line, GHashTable *dtd_hash_table)
{
    gchar *equalpos, *key, *value, *stripped_line, *comment = NULL;
    static gboolean note_on = FALSE;
    stripped_line = g_strdup(line);
    if (*stripped_line == '#')
    {
        if (g_str_has_prefix(stripped_line, "# LOCALIZATION NOTE ("))
        {
            note_on = TRUE;
            gchar *note = stripped_line + strlen("# LOCALIZATION NOTE (");
            GList *list = NULL;
            //find_elements_for_note(note, list);
            g_list_free_full(list, g_free);
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
            *equalpos = 0;
            key = g_strdup(stripped_line);
            *equalpos = '=';
            value = g_strdup(equalpos+1);
            g_hash_table_insert(dtd_hash_table, key, value);
        }
    }
    g_free(stripped_line);
}

void process_lines(const gchar *contents, const gsize length, GHashTable *dtd_hash_table)
{
    gchar *end, *cur = contents;
    while (1)
    {
        end = g_strstr_len(cur, -1, "\n");
        if (end)
        {
            *end = 0;
            //printf("%s\n", cur);
            process_line(cur, dtd_hash_table);
            *end = '\n';
            cur = end+1;
        }
        else
            break;
    }
    //g_hash_table_insert(dtd_hash_table, "a", "b");
}

void print_entry(gchar *key, gchar *value)
{
    printf("key = %s\nvalue = %s\n\n", key, value);
}

int main(int argc, char **argv)
{
    gchar *contents;
    gsize length;
    if(argc < 2)
        return 1;
    read_source_file(&contents, &length, argv[1]);
    dtd_hash_table = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
    process_lines(contents, length, dtd_hash_table);
    //printf("%s", contents);
    g_hash_table_foreach(dtd_hash_table, print_entry, NULL);
    g_hash_table_unref(dtd_hash_table);
    g_free(contents);
}