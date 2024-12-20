/* Belan Artem Vladislavovich
./Labwork1 st135609@student.spbu.ru*/
#include <iostream>
#include <fstream>
#include <vector>
#include "bmp.h"
#include <cmath>
#include <cstdint>
#include <algorithm>

void rotateClockwiseInPlace(std::vector<uint8_t>& imagePixels, int width, int height)
{
    std::vector<uint8_t> temp = imagePixels;

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            for (int c = 0; c < 3; ++c)
            {
                imagePixels[(x * height + (height - y - 1)) * 3 + c] = temp[(y * width + x) * 3 + c];
            }
        }
    }
}

void applyGaussianBlurInPlace(std::vector<uint8_t>& imagePixels, int width, int height)
{
    double sigma = 1.0;
    int kernelSize = 5;
    std::vector<std::vector<double>> kernel(kernelSize, std::vector<double>(kernelSize));
    double sum = 0.0;
    int halfKernel = kernelSize / 2;

    for (int x = -halfKernel; x <= halfKernel; ++x)
    {
        for (int y = -halfKernel; y <= halfKernel; ++y)
        {
            kernel[x + halfKernel][y + halfKernel] = (1.0 / (2 * M_PI * sigma * sigma)) * exp(-(x * x + y * y) / (2 * sigma * sigma));
            sum += kernel[x + halfKernel][y + halfKernel];
        }
    }

    for (int i = 0; i < kernelSize; ++i)
    {
        for (int j = 0; j < kernelSize; ++j)
        {
            kernel[i][j] /= sum;
        }
    }

    std::vector<uint8_t> temp = imagePixels;

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            double blueSum = 0.0, greenSum = 0.0, redSum = 0.0;

            for (int ky = -halfKernel; ky <= halfKernel; ++ky)
            {
                for (int kx = -halfKernel; kx <= halfKernel; ++kx)
                {
                    int pixelY = std::min(std::max(y + ky, 0), height - 1);
                    int pixelX = std::min(std::max(x + kx, 0), width - 1);

                    blueSum += temp[(pixelY * width + pixelX) * 3] * kernel[ky + halfKernel][kx + halfKernel];
                    greenSum += temp[(pixelY * width + pixelX) * 3 + 1] * kernel[ky + halfKernel][kx + halfKernel];
                    redSum += temp[(pixelY * width + pixelX) * 3 + 2] * kernel[ky + halfKernel][kx + halfKernel];
                }
            }

            imagePixels[(y * width + x) * 3] = static_cast<uint8_t>(blueSum);
            imagePixels[(y * width + x) * 3 + 1] = static_cast<uint8_t>(greenSum);
            imagePixels[(y * width + x) * 3 + 2] = static_cast<uint8_t>(redSum);
        }
    }
}

int main()
{
    std::ifstream file("file.bmp", std::ios::binary);

    if (!file)
    {
        std::cerr << "Error opening file!" << std::endl;
        return -1;
    }

    BitmapHeader bmpHeader;
    DIBitmapHeader dibHeader;
    BitmapColorHeader bmpColorHeader;

    file.read(reinterpret_cast<char*>(&bmpHeader), sizeof(BitmapHeader));
    if (bmpHeader.fileType != 0x4D42)
    {
        std::cerr << "Unsupported file format!" << std::endl;
        return -1;
    }

    file.read(reinterpret_cast<char*>(&dibHeader), sizeof(DIBitmapHeader));
    file.read(reinterpret_cast<char*>(&bmpColorHeader), sizeof(BitmapColorHeader));

    int width = dibHeader.width;
    int height = dibHeader.height;
    size_t rowSize = (width * 3 + 3) & ~3;

    std::vector<uint8_t> imagePixels(height * rowSize);
    file.seekg(bmpHeader.offsetData, std::ios::beg);
    file.read(reinterpret_cast<char*>(imagePixels.data()), imagePixels.size());
    file.close();

    rotateClockwiseInPlace(imagePixels, width, height);

    std::ofstream outFile("rotated_clockwise.bmp", std::ios::binary);
    outFile.write(reinterpret_cast<char*>(&bmpHeader), sizeof(BitmapHeader));
    outFile.write(reinterpret_cast<char*>(&dibHeader), sizeof(DIBitmapHeader));
    outFile.write(reinterpret_cast<char*>(&bmpColorHeader), sizeof(BitmapColorHeader));
    outFile.write(reinterpret_cast<char*>(imagePixels.data()), imagePixels.size());
    outFile.close();

    applyGaussianBlurInPlace(imagePixels, width, height);std::ofstream blurFile("blurred_image.bmp", std::ios::binary);
    blurFile.write(reinterpret_cast<char*>(&bmpHeader), sizeof(BitmapHeader));
    blurFile.write(reinterpret_cast<char*>(&dibHeader), sizeof(DIBitmapHeader));
    blurFile.write(reinterpret_cast<char*>(&bmpColorHeader), sizeof(BitmapColorHeader));
    blurFile.write(reinterpret_cast<char*>(imagePixels.data()), imagePixels.size());
    blurFile.close();

    return 0;
}
