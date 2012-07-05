/*
 * Copyright/Licensing information.
 */

#include "localestring.h"

/* Public methods */

/* This is called when the class is initialized */
void locale_string_class_init (gpointer klass, gpointer klass_data)
{
    /* not needed atm */
}

/* this is the constructor */
void locale_string_instance_init (GTypeInstance *instance, gpointer klass)
{
    /* not needed atm */
}

void locale_string_destroy (gpointer data)
{
    /* free the allocated strings for locale and string */
    LocaleString *self = LOCALE_STRING (data);
    g_free(self->locale);
    g_free(self->string);
}

LocaleString* locale_string_new (gchar *locale, gchar *string)
{
    /* create new LocaleString using GObject, then set the
     * locale and string
     */
    LocaleString* ls = g_object_new(TYPE_LOCALE_STRING, NULL);
    locale_string_set_locale (ls, locale);
    locale_string_set_string (ls, string);
    return ls;
}

void locale_string_set_locale (LocaleString *self, gchar *locale)
{
    g_free(self->locale);
    self->locale = g_strdup(locale);
}

void locale_string_set_string (LocaleString *self, gchar *string)
{
    g_free(self->string);
    self->string = g_strdup(string);
}

gchar* locale_string_get_locale (LocaleString *self)
{
    return self->locale;
}

gchar* locale_string_get_string (LocaleString *self)
{
    return self->string;
}

/* boilerplate code */
GType locale_string_get_type (void)
{
    static GType type = 0;

    if (type == 0)
    {
        static const GTypeInfo type_info =
        {
            sizeof (LocaleStringClass),
            NULL,                       /* base_init */
            NULL,                       /* base_finalize */
            locale_string_class_init,    /* class_init */
            NULL,                       /* class_final */
            NULL,                       /* class_data */
            sizeof (LocaleString),
            0,                          /* n_preallocs */
            locale_string_instance_init  /* instance_init */
        };

        type = g_type_register_static (G_TYPE_OBJECT, "LocaleString", &type_info, 0);
    }

    return type;
}