/*
 * Copyright/Licensing information.
 */

#include "hashvalue.h"
#include "localestring.h"

/* Public methods */

void hash_value_add_localestring (HashValue *self, gchar *locale, gchar *string)
{
    /* check if LocaleString with same locale exists */
    LocaleString *exists = hash_value_find_localestring (self, locale);
    /* if it exists, */
    if (exists != NULL)
    {
        /* free and remove the LocaleString from the list */
        locale_string_set_string (exists, string);
    }
    else
    {
        /* add the LocaleString to the list of LocaleStrings */
        LocaleString *localestring = locale_string_new (locale, string);
        self->list = g_list_prepend (self->list, localestring);
    }
}

LocaleString* hash_value_find_localestring (HashValue *self, gchar *locale)
{
    /* traverse the list and look for LocaleString matching given locale */
    GList *current = self->list;
    while (current != NULL)
    {
        /* if match is found */
        if (g_strcmp0 (locale_string_get_locale(current->data), locale) == 0)
            /*return the LocaleString */
            return current->data;
        current = current->next;
    }
    /* search failed, return NULL */
    return NULL;
}

void hash_value_set_uik (HashValue *self, gchar *uik)
{
    /* create a copy of the uik supplied, and store it */
    self->uik = g_strdup(uik);
}

void hash_value_set_note (HashValue *self, gchar *note)
{
    /* create a copy of the note supplied, and store it */
    self->note = g_strdup(note);
}

void hash_value_set_entry_index (HashValue *self, EntryIndex entry_number)
{
    self->entry_number = entry_number;
}

gchar* hash_value_get_uik (HashValue *self)
{
    return self->uik;
}

gchar* hash_value_get_note (HashValue *self)
{
    return self->note;
}

EntryIndex hash_value_get_entry_index (HashValue *self)
{
    return self->entry_number;
}

void hash_value_destroy (gpointer data)
{
    /* free the properties individually, and the
     * list containing all "LocaleString"s. Uses locale_string_destroy
     * to destroy every element in the list
     */
    HashValue *self = HASH_VALUE (data);
    g_free (self->uik);
    g_free (self->note);
    g_list_free_full (self->list, locale_string_destroy);
    g_object_unref(self);
}

/* This is called when the class is initialized */
void hash_value_class_init (gpointer klass, gpointer klass_data)
{
    /* not needed atm */
}

/* this is the constructor */
void hash_value_instance_init (GTypeInstance *instance, gpointer klass)
{
    /* not needed atm */
}

HashValue* hash_value_new (void)
{
    HashValue *hv = g_object_new(TYPE_HASH_VALUE, NULL);
    /* mark all properties as empty */
    hv->list = NULL;
    hv->uik = NULL;
    hv->note = NULL;
    hv->entry_number = -1;
}

/* boilerplate code */
GType hash_value_get_type (void)
{
    static GType type = 0;

    if (type == 0)
    {
        static const GTypeInfo type_info =
        {
            sizeof (HashValueClass),
            NULL,                       /* base_init */
            NULL,                       /* base_finalize */
            hash_value_class_init,    /* class_init */
            NULL,                       /* class_final */
            NULL,                       /* class_data */
            sizeof (HashValue),
            0,                          /* n_preallocs */
            hash_value_instance_init  /* instance_init */
        };

        type = g_type_register_static (G_TYPE_OBJECT, "HashValue", &type_info, 0);
    }

    return type;
}