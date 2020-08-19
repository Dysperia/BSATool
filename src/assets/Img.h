#ifndef BSATOOL_IMG_H
#define BSATOOL_IMG_H

#include <QImage>
#include "Palette.h"

/**
 * @brief Describe the IMG image format
 *
 * If the image has an header it follows the next structure
 * - Offset X : 2 bytes
 * - Offset Y : 2 bytes
 * - Width : 2 bytes
 * - Height : 2 bytes
 * - Compression flags : 1 byte
 * - Palette flags : 1 byte
 * - Image data size : 2 bytes
 * Then follows the image data and after the palette data if any
 */
class Img
{
public:
    //**************************************************************************
    // Constructors
    //**************************************************************************
    /**
     * @brief constructor of IMG with parsing of the header. The well
     * initialization can be checked with the potentially Null status of the
     * QImage
     * @param imgData data of the IMG file
     */
    explicit Img(const QVector<char> &imgData, const Palette &palette = Palette());
    /**
     * @brief constructor of IMG without parsing of the header. The well
     * initialization can be checked with the potentially Null status of the
     * QImage
     */
    Img(QVector<char> imgData, quint16 width, quint16 height, Palette palette = Palette());

    //**************************************************************************
    // Getters/setters
    //**************************************************************************
    [[nodiscard]] quint16 offsetX() const;
    void setOffsetX(const quint16 &offsetX);

    [[nodiscard]] quint16 offsetY() const;
    void setOffsetY(const quint16 &offsetY);

    [[nodiscard]] quint16 width() const;
    void setWidth(const quint16 &width);

    [[nodiscard]] quint16 height() const;
    void setHeight(const quint16 &height);

    [[nodiscard]] quint8 compressionFlag() const;
    void setCompressionFlag(const quint8 &compressionFlag);

    [[nodiscard]] quint8 paletteFlag() const;
    void setPaletteFlag(const quint8 &paletteFlag);

    [[nodiscard]] quint16 dataSize() const;
    void setDataSize(const quint16 &dataSize);

    [[nodiscard]] Palette palette() const;
    void setPalette(const Palette &palette);

    [[nodiscard]] QImage qImage() const;

private:
    //**************************************************************************
    // Attributes
    //**************************************************************************
    /**
     * @brief offset X used to draw the image at the correct position on screen
     */
    quint16 mOffsetX = 0;
    /**
     * @brief offset Y used to draw the image at the correct position on screen
     */
    quint16 mOffsetY = 0;
    /**
     * @brief width of the image
     */
    quint16 mWidth = 0;
    /**
     * @brief height of the image
     */
    quint16 mHeight = 0;
    /**
     * @brief compression flag
     */
    quint8 mCompressionFlag = 0;
    /**
     * @brief palette flag
     */
    quint8 mPaletteFlag = 0;
    /**
     * @brief size of the image data
     */
    quint16 mDataSize = 0;
    /**
     * @brief color palette
     */
    Palette mPalette;
    /**
     * @brief image data
     */
    QVector<char> mImageData;
    /**
     * @brief QImage version of this img, mainly used for display
     */
    QImage mQImage;

    //******************************************************************************
    // Methods
    //******************************************************************************
    /**
     * Validate image data by comparing pixel number and image size (height * width). If validation passed, a non null
     * QImage is created
     */
    void validatePixelDataAndCreateImage();
};

#endif // BSATOOL_IMG_H
