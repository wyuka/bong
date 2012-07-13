/*
 * Copyright/Licensing information.
 */

#include <translatableqt.hpp>
#include <propertiesfiletypeqt.hpp>

int main(int argc, char* argv[])
{
    TranslatableQt::init();

    FileTypeQt *ty = new PropertiesFileTypeQt();
    TranslatableQt tr(ty);

    if (argc < 2)
        return 0;

    tr.readFile(argv[1], "en");

    tr.setStringForUik("contextMenuSearchText", "en", "haha");
    tr.writeFile(argv[1], "en");

    return 0;
}
