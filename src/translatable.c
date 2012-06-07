/*
 * Copyright/Licensing information.
 */

#include "translatable.h"
#include "hashvalue.h"
#include "localestring.h"
#include "type.h"

/* Public methods */

void translatable_read_file (Translatable *self, gchar *file_name)
{
    self->read_file (self->file_type, self, file_name);
}

void translatable_add_entry (Translatable *self, EntryIndex entry_number, gchar *uik, gchar *note, gchar *locale, gchar *string)
{
    LocaleString *locale_string = locale_string_new (locale, string);
    HashValue *v = g_hash_table_lookup (self->hash_table, uik);
    if (v == NULL)
    {
        gchar *t_uik = g_strdup(uik);
        v = hash_value_new ();
        hash_value_set_uik (v, t_uik);
        hash_value_set_note (v, note);
        hash_value_set_entry_index (v, entry_number);
        hash_value_add_localestring (v, locale_string);
        g_hash_table_insert (self->hash_table, t_uik, v);
    }
    else
    {
        hash_value_add_localestring (v, locale_string);
    }
}

gchar* translatable_get_string_for_uik (Translatable *self, gchar *uik, gchar *locale)
{
    HashValue *v = g_hash_table_lookup (self->hash_table, uik);
    if (v == NULL)
    {
        return NULL;
    }

    LocaleString *ls = hash_value_find_localestring (v, locale);
    if (ls != NULL)
    {
        return locale_string_get_string (ls);
    }
}

gchar* translatable_get_note_for_uik (Translatable *self, gchar *uik)
{
    HashValue *v = g_hash_table_lookup (self->hash_table, uik);
    if (v == NULL)
    {
        return NULL;
    }

    return hash_value_get_note (v);
}

/* This is called when the class is initialized */
void translatable_class_init (gpointer klass, gpointer klass_data)
{
    /* not needed atm */
}

/* this is the constructor */
void translatable_instance_init (GTypeInstance *instance, gpointer klass)
{
    /* not needed atm */
}

/* initializes Translatable object by specifying the file type */
void translatable_init (Translatable *self, FileType *file_type)
{
    self->read_file = (void *)(FILE_TYPE_GET_CLASS (file_type)->read_file);
    self->file_type = file_type;
    self->hash_table = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, hash_value_destroy);
}

Translatable* translatable_new (void)
{
    return g_object_new(TYPE_TRANSLATABLE, NULL);
}

void translatable_destroy (gpointer data)
{
    Translatable *self = TRANSLATABLE (data);
    g_hash_table_destroy(self->hash_table);
}

GType translatable_get_type (void)
{
    static GType type = 0;

    if (type == 0)
    {
        static const GTypeInfo type_info =
        {
            sizeof (TranslatableClass),
            NULL,                       /* base_init */
            NULL,                       /* base_finalize */
            translatable_class_init,    /* class_init */
            NULL,                       /* class_final */
            NULL,                       /* class_data */
            sizeof (Translatable),
            0,                          /* n_preallocs */
            translatable_instance_init  /* instance_init */
        };

        type = g_type_register_static (G_TYPE_OBJECT, "Translatable", &type_info, 0);
    }

    return type;
}