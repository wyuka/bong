
#ifndef __TRANSLATABLE_QT_H__
#define __TRANSLATABLE_QT_H__

#include "bongqt_export.hpp"

#include <QtCore/QtCore>

class FileTypeQt;

struct _Translatable;
typedef int EntryIndex;

class BONGQT_EXPORT TranslatableQt
{
public:
    TranslatableQt(FileTypeQt *fileType);
    ~TranslatableQt();

    static void init();

    void readFile(QString fileName, QString locale);
    void writeFile(QString fileName, QString locale);

    void readContents(QString contents, QString locale);
    QString writeContents(QString contents, QString locale);

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
    _Translatable* getPointer() { return m_translatable; }

    _Translatable *m_translatable;
    FileTypeQt *m_fileType;
};

#endif // __TRANSLATABLE_QT_H__