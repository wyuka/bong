/*
 * Copyright/Licensing information.
 */

/* inclusion guard */
#ifndef __LOCALE_STRING_H__
#define __LOCALE_STRING_H__

#include <glib-object.h>

/*
 * Type macros
 */

#define TYPE_LOCALE_STRING              (locale_string_get_type())
#define LOCALE_STRING(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_LOCALE_STRING, LocaleString))
#define IS_LOCALE_STRING(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_LOCALE_STRING))
#define LOCALE_STRING_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_LOCALE_STRING, LocaleStringClass))
#define IS_LOCALE_STRING_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_LOCALE_STRING))
#define LOCALE_STRING_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_LOCALE_STRING, LocaleStringClass))

typedef struct _LocaleString LocaleString;
typedef struct _LocaleStringClass LocaleStringClass;

struct _LocaleStringClass
{
    GObjectClass parent_class;
    GTypeClass gtypeclass;
};

struct _LocaleString
{
    GObject parent_instance;
    GTypeInstance gtype;

    /* private */
    gchar *locale;
    gchar *string;
};

GType locale_string_get_type (void);

void locale_string_class_init (gpointer klass, gpointer klass_data);
void locale_string_instance_init (GTypeInstance *instance, gpointer klass);

/* public functions */
LocaleString* locale_string_new (gchar *locale, gchar *string);
void locale_string_destroy (gpointer data);
void locale_string_set_locale (LocaleString *self, gchar *locale);
void locale_string_set_string (LocaleString *self, gchar *string);
gchar* locale_string_get_locale (LocaleString *self);
gchar* locale_string_get_string (LocaleString *self);

#endif /* __LOCALE_STRING_H__ */