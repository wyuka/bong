/*
 * Copyright/Licensing information.
 */

#include <translatableqt.hpp>
#include <propertiesfiletypeqt.hpp>
#include <globalsqt.hpp>

extern "C"
{
    #include <glib-object.h>
}

int main(int argc, char* argv[])
{
    //initBongQt();
    g_type_init();

    FileTypeQt *ty = new PropertiesFileTypeQt();
    TranslatableQt tr(ty);

    if (argc < 2)
        return 0;

    tr.readFile(argv[1]);

    tr.setStringForUik("contextMenuSearchText", "en", "haha");
    tr.writeFile(argv[1]);

    return 0;
}
