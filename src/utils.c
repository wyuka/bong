#include <glib.h>

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
