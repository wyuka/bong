/*
 * Copyright/Licensing information.
 */

#include "filetype.h"
#include "translatable.h"

#include <stdio.h>

void file_type_destroy_impl (FileType *self);

/* Public methods */

void file_type_read_file (FileType *self, Translatable *tr, gchar *file_name, gchar *locale)
{
    /* look up appropriate function from vtable, and call it. */
    FILE_TYPE_GET_CLASS (self)->read_file (self, tr, file_name, locale);
}

void file_type_read_contents (FileType *self, Translatable *tr, gchar *input_contents, gchar *locale)
{
    FILE_TYPE_GET_CLASS (self)->read_contents (self, tr, input_contents, locale);
}

void file_type_write_file (FileType *self, Translatable *tr, gchar *file_name, gchar *locale)
{
    FILE_TYPE_GET_CLASS (self)->write_file (self, tr, file_name, locale);
}

gchar* file_type_write_contents (FileType *self, Translatable *tr, gchar *input_contents, gchar *locale)
{
    return (FILE_TYPE_GET_CLASS (self)->write_contents (self, tr, input_contents, locale));
}

void file_type_destroy (FileType *self)
{
    FILE_TYPE_GET_CLASS (self)->destroy (self);
}

/* This is called when the class is initialized */
void file_type_class_init (gpointer klass, gpointer klass_data)
{
    FileTypeClass *this_class = FILE_TYPE_CLASS (klass);

    /* pure virtual methods */
    this_class->read_file = 0;
    this_class->read_contents = 0;
    this_class->write_file = 0;
    this_class->write_contents = 0;

    this_class->destroy = file_type_destroy_impl;
}

/* virtual method implementation */
void file_type_destroy_impl (FileType *self)
{
    g_object_unref(self);
}

/* this is the constructor */
void file_type_instance_init (GTypeInstance *instance, gpointer klass)
{
    /* not needed atm */
}

GType file_type_get_type (void)
{
    static GType type = 0;

    if (type == 0)
    {
        static const GTypeInfo type_info =
        {
            sizeof (FileTypeClass),
            NULL,                   /* base_init */
            NULL,                   /* base_finalize */
            file_type_class_init,   /* class_init */
            NULL,                   /* class_final */
            NULL,                   /* class_data */
            sizeof (FileType),
            0,                      /* n_preallocs */
            file_type_instance_init /* instance_init */
        };

        type = g_type_register_static (G_TYPE_OBJECT, "FileType", &type_info, G_TYPE_FLAG_ABSTRACT);
    }

    return type;
}