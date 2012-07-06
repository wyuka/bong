#include "bongqt_export.hpp"

#include <translatable.h>
#include <QtCore/QtCore>

class FileTypeQt;

static gchar* qstringToGchar(QString &text)
{
    gchar *output = NULL;
    if (text.isEmpty())
        return NULL;
    QByteArray arr = text.toUtf8();
    output = g_strdup(arr.constData());
}

typedef int EntryIndex;

class BONGQT_EXPORT TranslatableQt
{
public:
    TranslatableQt(FileTypeQt *fileType);
    ~TranslatableQt();

    void readFile(QString fileName);
    void writeFile(QString fileName);

    void readContents(QString contents);
    QString writeContents(QString contents);

    void addEntry(QString uik, EntryIndex entryNumber, QString note, QString locale, QString string);

    QString getNoteForUik(QString uik);
    void setNoteForUik(QString uik, QString note);

    QString getNoteForEntryIndex(EntryIndex entryNumber);
    void setNoteForEntryIndex(EntryIndex entryNumber, QString note);

    QString getUikForEntryIndex(EntryIndex entryNumber);
    EntryIndex getEntryIndexForUik(QString uik);
    void setEntryIndexForUik(QString uik, EntryIndex entryNumber);

    QString getStringForUik(QString uik, QString locale);
    void setStringForUik(QString uik, QString locale, QString string);

    QString getStringForEntryIndex(EntryIndex entryNumber, QString locale);
    void setStringForEntryIndex(EntryIndex entryNumber, QString locale, QString string);

    int entryCount();

private:
    Translatable* getPointer() { return m_translatable; }

    Translatable *m_translatable;
    FileTypeQt *m_fileType;
};