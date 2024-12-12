/* Belan Artem Vladislavovich
./Labwork1 st135609@student.spbu.ru*/
#ifndef BMP_H
#define BMP_H

#include <cstdint>

#pragma pack(push, 1)
struct BitmapHeader
{
    uint16_t fileType;        // Тип файла (должен быть 0x4D42 для BMP)
    uint32_t fileSize;        // Размер файла
    uint16_t reserved1;       // Зарезервировано
    uint16_t reserved2;       // Зарезервировано
    uint32_t offsetData;      // Смещение данных изображения
};

struct DIBitmapHeader
{
    uint32_t size;            // Размер DIB-заголовка
    int32_t width;            // Ширина изображения
    int32_t height;           // Высота изображения
    uint16_t planes;          // Число плоскостей цвета (1)
    uint16_t bitCount;        // Количество бит на пиксель (например, 24 для RGB)
    uint32_t compression;     // Тип сжатия (0 для несжатого изображения)
    uint32_t sizeImage;       // Размер изображения (может быть 0 для несжатого BMP)
    int32_t xPixelsPerMeter;  // Горизонтальное разрешение (пикселей на метр)
    int32_t yPixelsPerMeter;  // Вертикальное разрешение (пикселей на метр)
    uint32_t colorsUsed;      // Количество используемых цветов (0 для всех)
    uint32_t colorsImportant; // Количество важных цветов (0 для всех)
};

struct BitmapColorHeader
{
    uint32_t redMask;         // Маска красного канала
    uint32_t greenMask;       // Маска зелёного канала
    uint32_t blueMask;        // Маска синего канала
    uint32_t alphaMask;       // Маска альфа-канала
    uint32_t colorSpaceType;  // Тип цветового пространства
    uint32_t unused[16];      // Зарезервированные данные для sRGB
};
#pragma pack(pop)

#endif
