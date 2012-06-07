/*
 * Copyright/Licensing information.
 */

#include "hashvalue.h"
#include "localestring.h"

/* Public methods */

void hash_value_add_localestring (HashValue *self, LocaleString *string)
{
    self->list = g_list_append (self->list, string);
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

void hash_value_destroy (gpointer data)
{
    HashValue *self = HASH_VALUE (data);
    g_free (self->uik);
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