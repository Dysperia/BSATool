#include <QtTest/QtTest>
#include "CompressionTest.h"
#include "../../src/utils/Compression.h"
#include "CompressionTestNativeDeflate.cpp"

void CompressionTest::testLZSSUncompression() {
    QWARN("Should uncompress the file and get the original data");
    QVector<char> uncompressedDataFromFile = readFile(QStringLiteral("ressources/uncompressedLZSS.data"));
    QVERIFY(!uncompressedDataFromFile.isEmpty());
    QVector<char> compressedDataFromFile = readFile(QStringLiteral("ressources/compressedLZSS.data"));
    QVERIFY(!compressedDataFromFile.isEmpty());
    QVector<char> uncompressedDataFromAlgorithm = Compression::uncompressLZSS(compressedDataFromFile);
    QVERIFY(!uncompressedDataFromAlgorithm.isEmpty());
    QCOMPARE(uncompressedDataFromAlgorithm == uncompressedDataFromFile, true);
}

void CompressionTest::testLZSSCompression() {
    QWARN("Should compress then uncompress the file and get the original data");
    QVector<char> uncompressedDataFromFile = readFile(QStringLiteral("ressources/uncompressedLZSS.data"));
    QVERIFY(!uncompressedDataFromFile.isEmpty());

    QVector<char> compressedThenUncompressedDataFromAlgorithm = Compression::uncompressLZSS(Compression::compressLZSS(uncompressedDataFromFile));
    QVERIFY(!compressedThenUncompressedDataFromAlgorithm.isEmpty());
    QCOMPARE(compressedThenUncompressedDataFromAlgorithm == uncompressedDataFromFile, true);
}

void CompressionTest::testDeflateUncompression() {
    QWARN("Should uncompress the file and get the original data");
    QVector<char> uncompressedDataFromFile = readFile(QStringLiteral("ressources/uncompressedDeflate.data"));
    QVERIFY(!uncompressedDataFromFile.isEmpty());
    QVector<char> compressedDataFromFile = readFile(QStringLiteral("ressources/compressedDeflate.data"));
    QVERIFY(!compressedDataFromFile.isEmpty());
    QVector<char> uncompressedDataFromAlgorithm = Compression::uncompressDeflate(compressedDataFromFile);
    QVERIFY(!uncompressedDataFromAlgorithm.isEmpty());
    QCOMPARE(uncompressedDataFromAlgorithm == uncompressedDataFromFile, true);
}

void CompressionTest::testNativeDeflateUncompression() {
    QWARN("Should uncompress natively the file and get the original data");
    QVector<char> uncompressedDataFromFile = readFile(QStringLiteral("ressources/uncompressedDeflate.data"));
    QVERIFY(!uncompressedDataFromFile.isEmpty());
    QVector<char> compressedDataFromFile = readFile(QStringLiteral("ressources/compressedDeflate.data"));
    QVERIFY(!compressedDataFromFile.isEmpty());
    QVector<char> uncompressedDataFromAlgorithm = nativeDeflateUncompression(compressedDataFromFile, uncompressedDataFromFile.size());
    QVERIFY(!uncompressedDataFromAlgorithm.isEmpty());
    QCOMPARE(uncompressedDataFromAlgorithm == uncompressedDataFromFile, true);
}

void CompressionTest::testDeflateCompression() {

}

void CompressionTest::testEncryptionDecryption() {
    QWARN("Should decrypt the file and get the original data");
    QVector<char> decryptedDataFromFile = readFile(QStringLiteral("ressources/decryptedINF.data"));
    QVERIFY(!decryptedDataFromFile.isEmpty());
    QVector<char> encryptedDataFromFile = readFile(QStringLiteral("ressources/encryptedINF.data"));
    QVERIFY(!encryptedDataFromFile.isEmpty());
    QVector<char> decryptedDataFromAlgorithm = Compression::encryptDecrypt(encryptedDataFromFile);
    QVERIFY(!decryptedDataFromAlgorithm.isEmpty());
    QCOMPARE(decryptedDataFromAlgorithm == decryptedDataFromFile, true);

    QWARN("Should encrypt then decrypt the file and get the original data");
    QVector<char> encryptedThenDecryptedDataFromAlgorithm = Compression::encryptDecrypt(Compression::encryptDecrypt(decryptedDataFromFile));
    QVERIFY(!encryptedThenDecryptedDataFromAlgorithm.isEmpty());
    QCOMPARE(encryptedThenDecryptedDataFromAlgorithm == decryptedDataFromFile, true);
}

QVector<char> CompressionTest::readFile(const QString &fileName) const {
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QDataStream stream(&file);
    stream.setByteOrder(QDataStream::LittleEndian);
    QVector<char> data(file.size());
    stream.readRawData(data.data(), file.size());
    file.close();
    return data;
}
