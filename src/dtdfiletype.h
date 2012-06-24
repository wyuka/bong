/*
 * Copyright/Licensing information.
 */

/* inclusion guard */
#ifndef __DTD_FILE_TYPE_H__
#define __DTD_FILE_TYPE_H__

#include "filetype.h"
struct _Translatable;
typedef struct _Translatable Translatable;

#include <glib-object.h>

/*
 * Type macros
 */

#define TYPE_DTD_FILE_TYPE              (dtd_file_type_get_type())
#define DTD_FILE_TYPE(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_DTD_FILE_TYPE, DtdFileType))
#define IS_DTD_FILE_TYPE(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_DTD_FILE_TYPE))
#define DTD_FILE_TYPE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_DTD_FILE_TYPE, DtdFileTypeClass))
#define IS_DTD_FILE_TYPE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_DTD_FILE_TYPE))
#define DTD_FILE_TYPE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_DTD_FILE_TYPE, DtdFileTypeClass))

typedef struct _DtdFileType DtdFileType;
typedef struct _DtdFileTypeClass DtdFileTypeClass;

struct _DtdFileTypeClass
{
    GTypeClass gtypeclass;
    FileTypeClass parent_class;
};

struct _DtdFileType
{
    FileType parent_instance;
    GTypeInstance gtype;
};

GType dtd_file_type_get_type (void);

void dtd_file_type_class_init (gpointer klass, gpointer klass_data);
void dtd_file_type_instance_init (GTypeInstance *instance, gpointer klass);

/* Public methods */

/* virtual public methods */
void dtd_file_type_read_file (DtdFileType *self, Translatable *tr, gchar *file_name);
void dtd_file_type_write_file (DtdFileType *self, Translatable *tr, gchar *file_name);

#endif /* __DTD_FILE_TYPE_H__ */