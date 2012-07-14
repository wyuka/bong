/*
 * Copyright/Licensing information.
 */

#define MAX_ENTRY_NUMBER 9999

#include "translatable.h"
#include "hashvalue.h"
#include "localestring.h"
#include "filetype.h"

/* Public methods */

void translatable_read_file (Translatable *self, gchar *file_name, gchar *locale)
{
    /* look up appropriate function from vtable, and call it. */
    self->read_file (self->file_type, self, file_name, locale);
}

void translatable_read_contents (Translatable *self, gchar *input_contents, gchar *locale)
{
    self->read_contents (self->file_type, self, input_contents, locale);
}

void translatable_write_file (Translatable *self, gchar *file_name, gchar *locale)
{
    self->write_file (self->file_type, self, file_name, locale);
}

gchar* translatable_write_contents (Translatable *self, gchar *input_contents, gchar *locale)
{
    return self->write_contents (self->file_type, self, input_contents, locale);
}

void translatable_add_entry (Translatable *self, EntryIndex entry_number, gchar *uik, gchar *note, gchar *locale, gchar *string)
{
    LocaleString *locale_string;
    /* look up the UIK in hash table */
    HashValue *v = g_hash_table_lookup (self->hash_table, uik);
    /* if it does not exist */
    if (v == NULL)
    {
        /* add new entry, and set the properties */
        gchar *t_uik = g_strdup(uik);
        v = hash_value_new ();
        hash_value_set_uik (v, t_uik);
        hash_value_set_note (v, note);
        hash_value_set_entry_index (v, entry_number);
        if (entry_number >= 0 && entry_number <= MAX_ENTRY_NUMBER)
            self->entry_array[entry_number] = v;
        if (locale)
        {
            hash_value_add_localestring (v, locale, string);
        }
        g_hash_table_insert (self->hash_table, t_uik, v);
        /* increment number of entries */
        self->entries_count++;
    }
    else /* entry with given UIK already exists */
    {
        /* update necessary properties */
        if (note != NULL && hash_value_get_note (v))
            hash_value_set_note(v, note);
        if (entry_number >= 0 && entry_number <= MAX_ENTRY_NUMBER && hash_value_get_entry_index(v) == -1)
        {
            hash_value_set_entry_index (v, entry_number);
            self->entry_array[entry_number] = v;
        }
        if (locale)
        {
            hash_value_add_localestring (v, locale, string);
        }
    }
}

void translatable_set_string_for_uik (Translatable *self, gchar *uik, gchar *locale, gchar *string)
{
    LocaleString *locale_string;
    /* look up entry in hash table */
    HashValue *v = g_hash_table_lookup (self->hash_table, uik);
    if (v == NULL)
        return;
    if (locale)
    {
        /* create new localestring, add to entry (will replace older one, if exists) */
        hash_value_add_localestring (v, locale, string);
    }
}

void translatable_set_string_for_entry_index (Translatable *self, EntryIndex entry_number, gchar *locale, gchar *string)
{
    LocaleString *locale_string;

    if (entry_number < 0)
        return;

    HashValue *v = self->entry_array[entry_number];
    if (v == NULL)
    {
        return;
    }
    if (locale)
    {
        hash_value_add_localestring (v, locale, string);
    }
}

void translatable_set_note_for_uik (Translatable *self, gchar *uik, gchar *note)
{
    HashValue *v = g_hash_table_lookup (self->hash_table, uik);
    if (v == NULL)
        return;
    hash_value_set_note (v, note);
}

void translatable_set_note_for_entry_index (Translatable *self, EntryIndex entry_number, gchar *note)
{
    if (entry_number < 0)
        return;
    
    HashValue *v = self->entry_array[entry_number];
    if (v == NULL)
    {
        return;
    }
    hash_value_set_note (v, note);
}

void translatable_set_entry_index_for_uik (Translatable *self, gchar *uik, EntryIndex entry_number)
{
    /* look up hash table */
    HashValue *v = g_hash_table_lookup (self->hash_table, uik);
    if (v == NULL)
        return;
    /* set entry index for the entry, and also update in the array for O(1) lookups by entry index */
    hash_value_set_entry_index (v, entry_number);
    if (entry_number >= 0 && entry_number <= MAX_ENTRY_NUMBER)
        self->entry_array[entry_number] = v;
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

EntryIndex translatable_get_entry_index_for_uik (Translatable *self, gchar *uik)
{
    HashValue *v = g_hash_table_lookup (self->hash_table, uik);
    if (v == NULL)
    {
        return -1;
    }

    return hash_value_get_entry_index (v);
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

gchar* translatable_get_string_for_entry_index (Translatable *self, EntryIndex entry_number, gchar *locale)
{
    if (entry_number < 0)
        return NULL;

    HashValue *v = self->entry_array[entry_number];
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

gchar* translatable_get_uik_for_entry_index (Translatable *self, EntryIndex entry_number)
{
    if (entry_number < 0)
        return NULL;

    HashValue *v = self->entry_array[entry_number];
    if (v == NULL)
    {
        return NULL;
    }

    return hash_value_get_uik (v);
}

gchar* translatable_get_note_for_entry_index (Translatable *self, EntryIndex entry_number)
{
    if (entry_number < 0)
        return NULL;

    HashValue *v = self->entry_array[entry_number];
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
    /* update vtable, according to the file type being used */
    self->read_file = FILE_TYPE_GET_CLASS (file_type)->read_file;
    self->read_contents = FILE_TYPE_GET_CLASS (file_type)->read_contents;
    self->write_file = FILE_TYPE_GET_CLASS (file_type)->write_file;
    self->write_contents = FILE_TYPE_GET_CLASS (file_type)->write_contents;

    self->file_type = file_type;

    /* initialize hash table, containing hash values
     * when it is destroyed, all keys are free'd with g_free, and all hashvalues are free'd
     * with hash_value_destroy
     */
    self->hash_table = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, hash_value_destroy);
    /* initialize entry array which allows O(1) access by entry index */
    self->entry_array = g_malloc0 (sizeof(HashValue*) * MAX_ENTRY_NUMBER + 1);
    /* initialize entry count */
    self->entries_count = 0;
}

int translatable_get_entries_count (Translatable *self)
{
    return self->entries_count;
}

Translatable* translatable_new (void)
{
    return g_object_new(TYPE_TRANSLATABLE, NULL);
}

void translatable_destroy (gpointer data)
{
    Translatable *self = TRANSLATABLE (data);
    /* free the hash table */
    g_hash_table_destroy(self->hash_table);
    /* free the allocated entry array */
    g_free(self->entry_array);
    /* free the FileType object */
    file_type_destroy(self->file_type);
    /* free self */
    g_object_unref(self);
}

/* boilerplate code */
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