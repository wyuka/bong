/*
 * Copyright/Licensing information.
 */

/* inclusion guard */
#ifndef __PROPERTIES_FILE_TYPE_H__
#define __PROPERTIES_FILE_TYPE_H__

#include "filetype.h"
struct _Translatable;
typedef struct _Translatable Translatable;

#include <glib-object.h>

/*
 * Type macros
 */

#define TYPE_PROPERTIES_FILE_TYPE              (properties_file_type_get_type())
#define PROPERTIES_FILE_TYPE(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_PROPERTIES_FILE_TYPE, PropertiesFileType))
#define IS_PROPERTIES_FILE_TYPE(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_PROPERTIES_FILE_TYPE))
#define PROPERTIES_FILE_TYPE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_PROPERTIES_FILE_TYPE, PropertiesFileTypeClass))
#define IS_PROPERTIES_FILE_TYPE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_PROPERTIES_FILE_TYPE))
#define PROPERTIES_FILE_TYPE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_PROPERTIES_FILE_TYPE, PropertiesFileTypeClass))

typedef struct _PropertiesFileType PropertiesFileType;
typedef struct _PropertiesFileTypeClass PropertiesFileTypeClass;

struct _PropertiesFileTypeClass
{
    GTypeClass gtypeclass;
    FileTypeClass parent_class;
};

/* this class implements the FileType interface.
 * This backend is for reading/writing Mozilla properties files.
 */
struct _PropertiesFileType
{
    FileType parent_instance;
    GTypeInstance gtype;
};

GType properties_file_type_get_type (void);

void properties_file_type_class_init (gpointer klass, gpointer klass_data);
void properties_file_type_instance_init (GTypeInstance *instance, gpointer klass);

/* Public methods */

/* virtual public methods */

/* reimplements file_type_read_file */
void properties_file_type_read_file (PropertiesFileType *self, Translatable *tr, gchar *file_name);

/* reimplements file_type_read_contents */
void properties_file_type_read_contents (PropertiesFileType *self, Translatable *tr, gchar *input_contents);

/* reimplements file_type_write_file */
void properties_file_type_write_file (PropertiesFileType *self, Translatable *tr, gchar *file_name);

/* reimplements file_type_write_contents */
gchar* properties_file_type_write_contents (PropertiesFileType *self, Translatable *tr, gchar *input_contents);

#endif /* __PROPERTIES_FILE_TYPE_H__ */