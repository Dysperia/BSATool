#ifndef ARCHIVE_H
#define ARCHIVE_H

#include "BsaFile.h"
#include "../error/Status.h"
#include "memory"
#include <QVector>
#include <QDataStream>
#include <QFile>

/**
 * @brief Describe a BSA archive
 *
 * The archive is built on the following pattern:
 * - File number: 2 bytes
 * - Files data put directly one after an other
 * - File table: 18 bytes for each
 *   - 14 bytes for the name
 *   - 4 bytes for the file size
 *
 * All data are written in little endian
 */
class BsaArchive
{
public:
    //**************************************************************************
    // Constructors
    //**************************************************************************
    /**
     * @brief Archive constructor
     */
    BsaArchive();
    /**
     * @brief Archive destructor
     */
    ~BsaArchive();

    //**************************************************************************
    // Getters/setters
    //**************************************************************************
    QString getArchiveFilePath() const;
    quint16 getFileNumber() const;
    qint64 getSize() const;
    qint64 getModifiedSize() const;
    QVector<BsaFile> getFiles() const;
    bool isOpened() const;
    bool isModified() const;

    //**************************************************************************
    // Methods
    //**************************************************************************
    /**
     * @brief open the given archive
     * @param filePath the filepath to the archive
     * @return the status of the operation : -1 if failure, 0 if success
     */
    Status openArchive(const QString &filePath);
    /**
     * @brief close this archive and restore state to a not opened archive
     */
    void closeArchive();
    /**
     * @brief retourne the archive data for the file
     * @param file the file to read, It should have at least the index set
     * @return the file data. If an error occured and the data can not be read
     * an empty vector is returned. The same happens if the archive is not
     * opened or the file is new
     */
    QVector<char> getFileData(const BsaFile &file);
    /**
     * @brief extract a file
     * @param destinationFolder destination folder of the file
     * @param file file to extract. It should have at least the index set
     * @return the status of the operation : -1 if failure, 0 if success
     */
    Status extractFile(const QString &destinationFolder,
                      const BsaFile &file);
    /**
     * @brief update a file by a new one
     * @param updateFilePath path the new file
     * @param file file to update. It should have at least the index set
     * @return the file with its state updated
     */
    BsaFile updateFile(const QString &updateFilePath,
                    const BsaFile &file);
    /**
     * @brief delete a file
     * @param file file to delete. It should have at least the index set
     * @return the file with its state updated
     */
    BsaFile deleteFile(const BsaFile &file);
    /**
     * @brief addFile add a new file to the archive
     * @param filePath path the new file
     * @return the file created
     */
    BsaFile addFile(const QString &filePath);
    /**
     * @brief cancel the delete operation pending on a file
     * @param file the file for which the operation has to be cancel
     * @return the file with its state updated
     */
    BsaFile cancelDeleteFile(const BsaFile &file);
    /**
     * @brief cancel the update operation pending on a file
     * @param file the file for which the operation has to be cancel
     * @return the file with its state updated
     */
    BsaFile cancelUpdateFile(const BsaFile &file);
    /**
     * @brief create a new empty archive
     */
    void createNewArchive();
    /**
     * @brief save the archive to the given file path
     * @param filePath path to the save file
     * @return the status of the operation : -1 if failure, 0 if success
     */
    Status saveArchive(const QString &filePath);

private:
    //**************************************************************************
    // Attributes
    //**************************************************************************
    /**
     * @brief complete archive path with filename
     */
    QFile mArchiveFile{};
    /**
     * @brief fileNumber (bytes 1 to 2 of the archive)
     */
    quint16 mFileNumber{0};
    /**
     * @brief archive total size
     */
    qint64 mSize{0};
    /**
     * @brief archive total size including all current modifications
     */
    qint64 mModifiedSize{0};
    /**
     * @brief List of the archive files
     */
    QVector<BsaFile> mFiles{};
    /**
     * @brief file stream reading the archive file
     */
    QDataStream mReadingStream{};
    /**
     * @brief true if an archive is opened
     */
    bool mOpened{false};
    /**
     * @brief true if the opened archive has been modified
     */
    bool mModified{false};
};

#endif // ARCHIVE_H
