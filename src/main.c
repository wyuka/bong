#include "translatable.h"
#include "dtdfile.h"

#include <glib-object.h>

int main()
{
    Translatable *tr = NULL;
    DtdFileType *ty = NULL;
    g_type_init();

    ty = g_object_new(TYPE_DTD_FILE_TYPE, NULL);
    tr = translatable_new();

    translatable_init (tr, FILE_TYPE(ty));
    translatable_read_file (tr, "translatable.c");

    return 0;
}