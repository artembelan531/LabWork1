/* Belan Artem Vladislavovich
./Labwork1 st135609@student.spbu.ru*/
#ifndef BMP_H
#define BMP_H

#include <cstdint>

#pragma pack(push, 1)
struct BitmapHeader
{
    uint16_t fileType;        
    uint32_t fileSize;        
    uint16_t reserved1;       
    uint16_t reserved2;       
    uint32_t offsetData;        
};

struct DIBitmapHeader
{
    uint32_t size;            
    int32_t width;            
    int32_t height;           
    uint16_t planes;          
    uint16_t bitCount;        
    uint32_t compression;     
    uint32_t sizeImage;       
    int32_t xPixelsPerMeter;  
    int32_t yPixelsPerMeter;  
    uint32_t colorsUsed;      
    uint32_t colorsImportant; 
};

struct BitmapColorHeader
{
    uint32_t redMask;         
    uint32_t greenMask;       
    uint32_t blueMask;        
    uint32_t alphaMask;       
    uint32_t colorSpaceType;  
    uint32_t unused[16];      
};
#pragma pack(pop)

#endif
