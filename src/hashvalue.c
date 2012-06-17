/*
 * Copyright/Licensing information.
 */

#include "hashvalue.h"
#include "localestring.h"

/* Public methods */

void hash_value_add_localestring (HashValue *self, LocaleString *string)
{
    GList *current = self->list;
    gchar *locale = locale_string_get_locale(string);
    while (current != NULL)
    {
        if (g_strcmp0 (locale_string_get_locale(current->data), locale) == 0)
        {
            locale_string_destroy(current->data);
            self->list = g_list_remove_link(self->list, current);
            break;
        }
        current = current->next;
    }
    self->list = g_list_prepend (self->list, string);
}

LocaleString* hash_value_find_localestring (HashValue *self, gchar *locale)
{
    GList *current = self->list;
    while (current != NULL)
    {
        if (g_strcmp0 (locale_string_get_locale(current->data), locale) == 0)
            return current->data;
        current = current->next;
    }
    return NULL;
}

void hash_value_set_uik (HashValue *self, gchar *uik)
{
    self->uik = g_strdup(uik);
}

void hash_value_set_note (HashValue *self, gchar *note)
{
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
    HashValue *self = HASH_VALUE (data);
    g_free (self->uik);
    g_free (self->note);
    g_list_free_full (self->list, locale_string_destroy);
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
    hv->list = NULL;
    hv->uik = NULL;
    hv->note = NULL;
    hv->entry_number = -1;
}

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