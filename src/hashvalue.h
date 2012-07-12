/*
 * Copyright/Licensing information.
 */

/* inclusion guard */
#ifndef __HASH_VALUE_H__
#define __HASH_VALUE_H__

#include "localestring.h"
#include <glib-object.h>

/*
 * Type macros
 */

#define TYPE_HASH_VALUE               (hash_value_get_type())
#define HASH_VALUE(obj)               (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_HASH_VALUE, HashValue))
#define IS_HASH_VALUE(obj)            (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_HASH_VALUE))
#define HASH_VALUE_CLASS(klass)       (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_HASH_VALUE, HashValueClass))
#define IS_HASH_VALUE_CLASS(klass)    (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_HASH_VALUE))
#define HASH_VALUE_GET_CLASS(obj)     (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_HASH_VALUE, HashValueClass))

typedef struct _HashValue HashValue;
typedef struct _HashValueClass HashValueClass;

typedef int EntryIndex;

struct _HashValueClass
{
    GObjectClass parent_class;
    GTypeClass gtypeclass;
};

/* this class encapsulates a UIK, a note, an entry index, and a list of
 * "LocaleString"s, which are in essence, pairs of locale and string.
 * Always, only one string is stored for a specific locale.
 */
struct _HashValue
{
    GObject parent_instance;
    GTypeInstance gtype;

    /* private */
    gchar *uik;
    gchar *note;
    EntryIndex entry_number;
    GList *list;
};

GType hash_value_get_type (void);

void hash_value_class_init (gpointer klass, gpointer klass_data);
void hash_value_instance_init (GTypeInstance *instance, gpointer klass);

/* public functions */

/* convenience function for creating HashValue using GObject mechanism */
HashValue* hash_value_new (void);
/* destructor for HashValue object */
void hash_value_destroy (gpointer data);

/* add the LocaleString to the hashvalue, will replace any existing entry
 * with same locale
 */
void hash_value_add_localestring (HashValue *self, gchar *locale, gchar *string);

/* returns a LocaleString for a specified locale */
LocaleString* hash_value_find_localestring (HashValue *self, gchar *locale);

/* sets UIK for a HashValue
 * creates a local copy of UIK, so argument may be free'd
 */
void hash_value_set_uik (HashValue *self, gchar *uik);

/* sets note for a HashValue
 * creates a local copy of note, so argument may be free'd
 */
void hash_value_set_note (HashValue *self, gchar *note);

/* sets entry index for a HashValue */
void hash_value_set_entry_index (HashValue *self, EntryIndex entry_number);

/* returns the UIK for a HashValue */
gchar* hash_value_get_uik (HashValue *self);

/* returns the note for a HashValue */
gchar* hash_value_get_note (HashValue *self);

/* returns the EntryIndex for a HashValue */
EntryIndex hash_value_get_entry_index (HashValue *self);

#endif /* __HASH_VALUE_H__ */