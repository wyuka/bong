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

/* serves as a virtual base class,
 * or an interface, for different file formats
 * which have their own r/w operations
 */
struct _FileTypeClass
{
    GTypeClass gtypeclass;
    GObjectClass parent_class;

    /* vtable */
    void (*read_file) (FileType *self, struct _Translatable *tr, gchar *fileName, gchar *locale);
    void (*write_file) (FileType *self, struct _Translatable *tr, gchar *fileName, gchar *locale);
    void (*read_contents) (FileType *self, struct _Translatable *tr, gchar *input_contents, gchar *locale);
    gchar* (*write_contents) (FileType *self, struct _Translatable *tr, gchar *input_contents, gchar *locale);

    void (*destroy) (FileType *self);
};

struct _FileType
{
    GObject parent_instance;
    GTypeInstance gtype;
};

GType file_type_get_type (void);

void file_type_class_init (gpointer klass, gpointer klass_data);
void file_type_instance_init (GTypeInstance *instance, gpointer klass);

/* Public methods */

/* virtual public methods */

/* read a file with given file name, and store entries into a Translatable object */
void file_type_read_file (FileType *self, struct _Translatable *tr, gchar *file_name, gchar *locale);

/* parse the contents given in a string, and store entries into a Translatable object */
void file_type_read_contents (FileType *self, struct _Translatable *tr, gchar *input_contents, gchar *locale);

/* read a file with given file name, modify it according to the entries
 * in Translatable object, and write to a different file */
void file_type_write_file (FileType *self, struct _Translatable *tr, gchar *file_name, gchar *locale);

/* parse the contents given in a string, modify it according to the entries
 * in Translatable object, and return as an allocated string.
 * The output must be manually free'd.
 */
gchar* file_type_write_contents (FileType *self, struct _Translatable *tr, gchar *input_contents, gchar *locale);

/* destroy the file type object, free the space allocated to it */
void file_type_destroy (FileType *self);

#endif /* __FILE_TYPE_H__ */