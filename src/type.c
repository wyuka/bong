/*
 * Copyright/Licensing information.
 */

#include "type.h"
#include "translatable.h"

#include <stdio.h>

/* Public methods */

void file_type_read_file (FileType *self, Translatable *tr, gchar *file_name)
{
    FILE_TYPE_GET_CLASS (self)->read_file (self, tr, file_name);
}

/* This is called when the class is initialized */
void file_type_class_init (gpointer klass, gpointer klass_data)
{
    FileTypeClass *this_class = FILE_TYPE_CLASS (klass);

    /* pure virtual methods */
    this_class->read_file = 0;
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