/*
 * Copyright/Licensing information.
 */

#include <glib.h>

GList* find_elements_for_note(gchar *start, int length)
{
    gchar *comma = NULL, *keystr = start;
    GList *next = NULL;
    int lengthleft = length;
    /* for every comma encountered */
    while(comma = g_strstr_len(keystr, lengthleft, ","))
    {
        /* temporarily terminate the string at comma
         * thus creating a token
         */
        *comma = '\0';
        /* prepend token to list */
        next = g_list_prepend(next, g_strdup(keystr));
        /* restore the string by putting the comma back */
        *comma = ',';
        lengthleft -= comma - keystr + 1;
        keystr = comma + 1;
        if (keystr >= start + length)
            return next;
    }
    /* retrieve element after last comma, prepend it to the list */
    start[length] = '\0';
    next = g_list_prepend(next, g_strdup(keystr));
    start[length] = ')';
    return next;
}
