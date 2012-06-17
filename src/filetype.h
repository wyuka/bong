/*
 * Copyright/Licensing information.
 */

/* inclusion guard */
#ifndef __FILE_TYPE_H__
#define __FILE_TYPE_H__

struct _Translatable;

#include <glib-object.h>

/*
 * Type macros
 */

#define TYPE_FILE_TYPE              (file_type_get_type())
#define FILE_TYPE(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_FILE_TYPE, FileType))
#define IS_FILE_TYPE(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_FILE_TYPE))
#define FILE_TYPE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_FILE_TYPE, FileTypeClass))
#define IS_FILE_TYPE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_FILE_TYPE))
#define FILE_TYPE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_FILE_TYPE, FileTypeClass))

typedef struct _FileType FileType;
typedef struct _FileTypeClass FileTypeClass;

struct _FileTypeClass
{
    GTypeClass gtypeclass;
    GObjectClass parent_class;

    void (*read_file) (FileType *self, struct _Translatable *tr, gchar *fileName);
    void (*write_file) (FileType *self, struct _Translatable *tr, gchar *fileName);
};

struct _FileType
{
    GObject parent_instance;
    GTypeInstance gtype;

    /* private */
    gchar* m_fileTypeName;
};

GType file_type_get_type (void);

void file_type_class_init (gpointer klass, gpointer klass_data);
void file_type_instance_init (GTypeInstance *instance, gpointer klass);

/* Public methods */

/* virtual public methods */
void file_type_read_file (FileType *self, struct _Translatable *tr, gchar *file_name);
void file_type_write_file (FileType *self, struct _Translatable *tr, gchar *file_name);

#endif /* __FILE_TYPE_H__ */