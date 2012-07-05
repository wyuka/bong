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
 * The part below is some boilerplate code to make Translatable a GObject
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
    /* public*/
    GObject parent_instance;
    GTypeInstance gtype;

    /* private */
    GHashTable *hash_table;
    FileType *file_type;
    int entries_count;
    struct _HashValue **entry_array;

    /* vtable */
    void (*read_file) (FileType *file_type, Translatable *self, gchar *fileName);
    void (*read_contents) (FileType *file_type, Translatable *self, gchar *input_contents);
    void (*write_file) (FileType *file_type, Translatable *self, gchar *fileName);
    gchar* (*write_contents) (FileType *file_type, Translatable *self, gchar *input_contents);
};

/*again, some boilerplate code */
GType translatable_get_type (void);

void translatable_class_init (gpointer klass, gpointer klass_data);
void translatable_instance_init (GTypeInstance *instance, gpointer klass);

/* public functions
 * ================
 */

/* Return a newly created Translatable object.
 * Is essentially a shorthand for creating it with GObject */
Translatable* translatable_new (void);

/* Initialize a Translatable object
 * @params
 * self the Translatable object being initialized
 * file_type pointer to the FileType object which will handle the read/write
 */
void translatable_init (Translatable *self, FileType *file_type);

/* Destructor, Called when Translatable needs to be destroyed */
void translatable_destroy (gpointer data);

/* read a file into the Translatable object
 * @params
 * self Translatable object
 * file_name name of the file from which to read into the object
 */
void translatable_read_file (Translatable *self, gchar *file_name);

/* parse contents stored in a string into the Translatable object
 * @params
 * self Translatable object
 * input_contents the contents which need to be parsed
 */
void translatable_read_contents (Translatable *self, gchar *input_contents);

/* write out the Translatable object contents to a file
 * @params
 * self Translatable object
 * file_name name of the file to which to write from the object
 */
void translatable_write_file (Translatable *self, gchar *file_name);

/* parse contents stored in a string, and modify it according to contents of the Translatable object
 * @returns returns the modified string
 * @params
 * self Translatable object
 * input_contents the contents which need to be parsed
 */
gchar* translatable_write_contents (Translatable *self, gchar *input_contents);

/* add string entry to Translatable object
 * @params
 * self Translatable object
 * entry_number the index of the string in the file being read from, can be set to -1
 * uik the unique identification key, which is unique for every string
 * note the localization note for the string, can be set to NULL
 * locale the locale for which the string is being stored, can be NULL
 * string the localized string for the specific uik and locale, can be NULL
 */
void translatable_add_entry (Translatable *self, EntryIndex entry_number, gchar *uik, gchar *note, gchar *locale, gchar *string);

/* returns the number of entries in a Translatable object
 * @returns number of entries in the Translatable object
 * @params
 * self the Translatable object
 */
int translatable_get_entries_count (Translatable *self);

/* get the localized string for a specific UIK and locale
 * @returns the localized string being retrieved
 * @params
 * self the Translatable object
 * uik the key for which the localized string is to be retrieved
 * locale the locale for which the localized string is to be retrieved
 */
gchar* translatable_get_string_for_uik (Translatable *self, gchar *uik, gchar *locale);

/* set the localized string for a specific UIK and locale
 * @params
 * self the Translatable object
 * uik the key of the localized string to be stored
 * locale the locale of the localized string is to be stored
 * string the localized string to be stored
 */
void translatable_set_string_for_uik (Translatable *self, gchar *uik, gchar *locale, gchar *string);

/* get the localized string for a specific EntryIndex and locale
 * @returns the localized string being retrieved
 * @params
 * self the Translatable object
 * entry_number the entry number of the localized string to be retrieved
 * locale the locale for which the localized string is to be retrieved
 */
gchar* translatable_get_string_for_entry_index (Translatable *self, EntryIndex entry_number, gchar *locale);

/* set the localized string for a specific EntryIndex and locale
 * @params
 * self the Translatable object
 * entry_number the entry number of the localized string to be stored
 * locale the locale of the localized string is to be stored
 * string the localized string to be stored
 */
void translatable_set_string_for_entry_index (Translatable *self, EntryIndex entry_number, gchar *locale, gchar *string);

/* get the entry index for a specific UIK
 * @returns the entry index being retrieved
 * @params
 * self the Translatable object
 * uik the key for which the entry index is to be retrieved
 */
EntryIndex translatable_get_entry_index_for_uik (Translatable *self, gchar *uik);

/* set the entry index for a specific UIK
 * @params
 * self the Translatable object
 * uik the key for which the entry index is to be stored
 * entry_number the entry index to be stored
 */
void translatable_set_entry_index_for_uik (Translatable *self, gchar *uik, EntryIndex entry_number);

/* get the UIK for a specific EntryIndex
 * @returns the unique key being retrieved
 * @params
 * self the Translatable object
 * entry_number the entry index for which the UIK is to be retrieved
 */
gchar* translatable_get_uik_for_entry_index(Translatable *self, EntryIndex entry_number);

/* get the note for a specific UIK
 * @returns the note being retrieved
 * @params
 * self the Translatable object
 * uik the key for which the note is to be retrieved
 */
gchar* translatable_get_note_for_uik (Translatable *self, gchar *uik);

/* set the note for a specific UIK
 * @params
 * self the Translatable object
 * uik the key for which the note is to be stored
 * note the note being stored
 */
void translatable_set_note_for_uik (Translatable *self, gchar *uik, gchar *note);

/* get the note for a specific EntryIndex
 * @returns the note being retrieved
 * @params
 * self the Translatable object
 * entry_number the entry index of the string for which the note is to be retrieved
 */
gchar* translatable_get_note_for_entry_index(Translatable *self, EntryIndex entry_number);

/* set the note for a specific EntryIndex
 * @params
 * self the Translatable object
 * entry_number the entry index of the string for which the note is to be stored
 * note the note being stored
 */
void translatable_set_note_for_entry_index (Translatable *self, EntryIndex entry_number, gchar *note);

#endif /* __TRANSLATABLE_H__ */