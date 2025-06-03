# Parallel Optimization Report

## Goal
Speed up Gaussian blur filter using OpenMP to demonstrate performance improvement with multithreading.

## Method
- Original code: sequential applyGaussianBlurInPlace().
- Modified: added #pragma omp parallel for collapse(2) to outer loops.
- Tested on Ubuntu using time ./ImageProcessing.

## Time Comparison

| Version          | Time (s)       |
|------------------|----------------|
| Without OpenMP   | 1.47           |
| With OpenMP      | 0.52           |

~2.8x speedup

## Conclusion
The OpenMP version significantly reduced execution time. CI confirms code compiles. 
Repository follows lab formatting: main.cpp, Makefile, .github, report.
