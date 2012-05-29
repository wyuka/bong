#include "translatable.h"
#include "type.h"

#include <glib-object.h>

int main()
{
    Translatable *tr = NULL;
    FileType *ty = NULL;
    g_type_init();
    ty = FILE_TYPE (g_type_create_instance(file_type_get_type()));
    tr = TRANSLATABLE (g_type_create_instance(translatable_get_type()));

    translatable_init (tr, ty);
    translatable_read_file (tr, "translatable.c");

    return 0;
}