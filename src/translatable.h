/*
 * Copyright/Licensing information.
 */

/* inclusion guard */
#ifndef __TRANSLATABLE_H__
#define __TRANSLATABLE_H__

#include "filetype.h"

#include <glib-object.h>

/*
 * Type macros
 */

#define TYPE_TRANSLATABLE               (translatable_get_type())
#define TRANSLATABLE(obj)               (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_TRANSLATABLE, Translatable))
#define IS_TRANSLATABLE(obj)            (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_TRANSLATABLE))
#define TRANSLATABLE_CLASS(klass)       (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_TRANSLATABLE, TranslatableClass))
#define IS_TRANSLATABLE_CLASS(klass)    (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_TRANSLATABLE))
#define TRANSLATABLE_GET_CLASS(obj)     (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_TRANSLATABLE, TranslatableClass))

typedef struct _Translatable Translatable;
typedef struct _TranslatableClass TranslatableClass;

struct _HashValue;

typedef int EntryIndex;

struct _TranslatableClass
{
    GObjectClass parent_class;
    GTypeClass gtypeclass;
};

struct _Translatable
{
    GObject parent_instance;
    GTypeInstance gtype;

    /* private */
    GHashTable *hash_table;
    FileType *file_type;
    int entries_count;
    struct _HashValue **entry_array;
    void (*read_file) (FileType *file_type, Translatable *self, gchar *fileName);
    void (*write_file) (FileType *file_type, Translatable *self, gchar *fileName);
};

GType translatable_get_type (void);

void translatable_class_init (gpointer klass, gpointer klass_data);
void translatable_instance_init (GTypeInstance *instance, gpointer klass);

/* public functions */
Translatable* translatable_new (void);
void translatable_init (Translatable *self, FileType *file_type);
void translatable_destroy (gpointer data);

void translatable_read_file (Translatable *self, gchar *file_name);
void translatable_write_file (Translatable *self, gchar *file_name);

/* to insert empty, set locale and string = NULL
 * if you want, you can set entry_number = -1 (to replace later)
 */
void translatable_add_entry (Translatable *self, EntryIndex entry_number, gchar *uik, gchar *note, gchar *locale, gchar *string);
void translatable_set_note (Translatable *self, gchar *uik, gchar *note);
void translatable_set_entry_index (Translatable *self, gchar *uik, EntryIndex entry_number);
//void translatable_set_string_for_uik (Translatable *self, gchar *uik, gchar *locale, gchar *string);

gchar* translatable_get_string_for_uik (Translatable *self, gchar *uik, gchar *locale);
EntryIndex translatable_get_entry_index_for_uik (Translatable *self, gchar *uik);
gchar* translatable_get_note_for_uik (Translatable *self, gchar *uik);

gchar* translatable_get_string_for_entry_index(Translatable *self, EntryIndex entry_number, gchar *locale);
gchar* translatable_get_uik_for_entry_index(Translatable *self, EntryIndex entry_number);
gchar* translatable_get_note_for_entry_index(Translatable *self, EntryIndex entry_number);

int translatable_get_entries_count (Translatable *self);

#endif /* __TRANSLATABLE_H__ */