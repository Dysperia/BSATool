#ifndef BSATOOL_COMPRESSIONTEST_H
#define BSATOOL_COMPRESSIONTEST_H

#include <QObject>

class CompressionTest  : public QObject
{
    Q_OBJECT

private slots:
    /**
     * @brief test LZSS uncompression
     */
    void testLZSSUncompression();
    /**
     * @brief test LZSS compression
     */
    void testLZSSCompression();
    /**
     * @brief test deflate uncompression
     */
    void testDeflateUncompression();
    /**
     * @brief test deflate native uncompression
     */
    void testNativeDeflateUncompression();
    /**
     * @brief test deflate compression
     */
    void testDeflateCompression();
    /**
     * @brief test encryption decryption
     */
    void testEncryptionDecryption();

private:
    [[nodiscard]] QVector<char> readFile(const QString &fileName) const;
};


#endif //BSATOOL_COMPRESSIONTEST_H
