#include "translatable.h"
#include "type.h"

/* Public methods */

void translatable_read_file (Translatable *self, gchar *file_name)
{
    self->read_file (self->file_type, self, file_name);
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
}

Translatable* translatable_new (void)
{
    return g_object_new(TYPE_TRANSLATABLE, NULL);
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