/*
 * Copyright/Licensing information.
 */

#include "dtdfiletype.h"
#include "translatable.h"

#include <stdio.h>

/* Public methods */

void dtd_file_type_read_file (DtdFileType *self, Translatable *tr, gchar *file_name)
{
    // nothing for now
}

/* This is called when the class is initialized */
void dtd_file_type_class_init (gpointer klass, gpointer klass_data)
{
    FileTypeClass *parent_class = FILE_TYPE_CLASS (klass);

    /* virtual methods */
    parent_class->read_file = (void *)(dtd_file_type_read_file);
}

/* this is the constructor */
void dtd_file_type_instance_init (GTypeInstance *instance, gpointer klass)
{
    //dtd_file_type_read_file(instance, "yow");
    /* not needed atm */
}

GType dtd_file_type_get_type (void)
{
    static GType type = 0;

    if (type == 0)
    {
        static const GTypeInfo type_info =
        {
            sizeof (DtdFileTypeClass),
            NULL,                   /* base_init */
            NULL,                   /* base_finalize */
            dtd_file_type_class_init,   /* class_init */
            NULL,                   /* class_final */
            NULL,                   /* class_data */
            sizeof (DtdFileType),
            0,                      /* n_preallocs */
            dtd_file_type_instance_init /* instance_init */
        };

        type = g_type_register_static (TYPE_FILE_TYPE, "DtdFileType", &type_info, 0);
    }

    return type;
}