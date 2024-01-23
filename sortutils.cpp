#pragma once
#include "sortutils.hpp"

#include <algorithm>
#include <array>
#include <chrono>
#include <execution>
#include <iostream>
#include <random>

SourceArray getStartArray()
{
    std::random_device rd;
    std::default_random_engine engine{ rd() };
    std::uniform_int_distribution<int> myDistribution(-10000000, 10000000);

    // Initialize a std::array with values from the distribution
    SourceArray myArray{};

    for (auto& element : myArray)
    {
        element = myDistribution(engine);
    }

    return myArray;
}

void organPipeStdArray(SourceArray& data)
{
    // For even-sized array
    if (data.size() % 2 == 0)
    {
        for (std::uint32_t j = 0; j < data.size() / 2; j++)
        {
            data[j + data.size() / 2] = data[data.size() / 2 - 1 - j];
        }
    }

    // For odd-sized array
    else
    {
        for (std::uint32_t j = 0; j < data.size() / 2; j++)
        {
            data[j + data.size() / 2 + 1] = data[data.size() / 2 - 1 - j];
        }
    }
}

void initializeRawArrayFromStdArray(const SourceArray& source, int dest[])
{
    for (std::uint32_t i = 0; i < source.size(); i++)
    {
        dest[i] = source[i];
    }
}

void performStdSortOperation(const SourceArray& data, std::string operation, bool parallel)
{
    std::chrono::milliseconds totalTime(0);
    std::chrono::microseconds totalTimeMicro(0);

    for (uint32_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        SourceArray tempData = data;
        if (parallel)
        {
            auto start = std::chrono::steady_clock::now();
            std::sort(std::execution::par, tempData.begin(), tempData.end());
            auto end = std::chrono::steady_clock::now();
            auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            auto diffMicro = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            totalTime += diff;
            totalTimeMicro += diffMicro;
        }
        else
        {
            auto start = std::chrono::steady_clock::now();
            std::sort(tempData.begin(), tempData.end());
            auto end = std::chrono::steady_clock::now();
            auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            auto diffMicro = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            totalTimeMicro += diffMicro;
            totalTime += diff;
        }
    }
    if (totalTime.count() == 0)
    {
        std::cout << std::format("{:24}: {} us\n", operation, totalTimeMicro.count());
    }
    else
    {
        std::cout << std::format("{:24}: {} ms\n", operation, totalTime.count());
    }
}

void performRawSortOperation(const SourceArray& data, std::string operation, bool parallel)
{
    std::chrono::milliseconds totalTime(0);
    std::chrono::microseconds totalTimeMicro(0);

    for (uint32_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        int tempData[HOW_MANY_ELEMENTS];
        initializeRawArrayFromStdArray(data, tempData);
        if (parallel)
        {
            auto start = std::chrono::steady_clock::now();
            std::sort(std::execution::par, std::begin(tempData), std::end(tempData));
            auto end = std::chrono::steady_clock::now();
            auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            auto diffMicro = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            totalTime += diff;
            totalTimeMicro += diffMicro;
        }
        else
        {
            auto start = std::chrono::steady_clock::now();
            std::sort(std::begin(tempData), std::end(tempData));
            auto end = std::chrono::steady_clock::now();
            auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            auto diffMicro = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            totalTime += diff;
            totalTimeMicro += diffMicro;
        }
        initializeRawArrayFromStdArray(data, tempData);
    }
    if (totalTime.count() == 0)
    {
        std::cout << std::format("{:24}: {} us\n", operation, totalTimeMicro.count());
    }
    else
    {
        std::cout << std::format("{:24}: {} ms\n", operation, totalTime.count());
    }
}

void performVectorSortOperation(const SourceArray& data, std::string operation, bool parallel)
{
    std::chrono::milliseconds totalTime(0);
    std::chrono::microseconds totalTimeMicro(0);

    for (uint32_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        std::vector<int> tempData(data.begin(), data.end());
        if (parallel)
        {
            auto start = std::chrono::steady_clock::now();
            std::sort(std::execution::par, tempData.begin(), tempData.end());
            auto end = std::chrono::steady_clock::now();
            auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            auto diffMicro = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            totalTimeMicro += diffMicro;

            totalTime += diff;
        }
        else
        {
            auto start = std::chrono::steady_clock::now();
            std::sort(tempData.begin(), tempData.end());
            auto end = std::chrono::steady_clock::now();
            auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            totalTime += diff;
            auto diffMicro = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            totalTimeMicro += diffMicro;
        }
    }
    if (totalTime.count() == 0)
    {
        std::cout << std::format("{:24}: {} us\n", operation, totalTimeMicro.count());
    }
    else
    {
        std::cout << std::format("{:24}: {} ms\n", operation, totalTime.count());
    }
}

void evaluateStdArray(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated)
{

    // Sequential random array
    std::cout << "  --- std::array Performance ---\n\n";
    std::cout << "Sequential" << std::endl;
    performStdSortOperation(random, "        Random Time ", false);
    performStdSortOperation(sorted, "        Sorted Time ", false);
    performStdSortOperation(reversed, "        Reversed Time ", false);
    performStdSortOperation(organPipe, "        Organ Pipe Time ", false);
    performStdSortOperation(rotated, "        Rotated Time ", false);

    std::cout << "\nParallel" << std::endl;

    performStdSortOperation(random, "        Random Time ", true);
    performStdSortOperation(sorted, "        Sorted Time ", true);
    performStdSortOperation(reversed, "        Reversed Time ", true);
    performStdSortOperation(organPipe, "        Organ Pipe Time ", true);
    performStdSortOperation(rotated, "        Rotated Time ", true);
    std::cout << "\n";
}

void evaluateRawArray(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated)
{
    // Sequential
    std::cout << "  --- Raw Array Performance ---\n\n";
    std::cout << "Sequential" << std::endl;
    performRawSortOperation(random, "        Random Time ", false);
    performRawSortOperation(sorted, "        Sorted Time ", false);
    performRawSortOperation(reversed, "        Reversed Time ", false);
    performRawSortOperation(organPipe, "        Organ Pipe Time ", false);
    performRawSortOperation(rotated, "        Rotated Time ", false);

    std::cout << "\nParallel" << std::endl;

    // Parallel
    performRawSortOperation(random, "        Random Time ", true);
    performRawSortOperation(sorted, "        Sorted Time ", true);
    performRawSortOperation(reversed, "        Reversed Time ", true);
    performRawSortOperation(organPipe, "        Organ Pipe Time ", true);
    performRawSortOperation(rotated, "        Rotated Time ", true);
    std::cout << "\n";
}

void evaluateStdVector(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated)
{
    // Sequential random array
    std::cout << "  --- std::vector Performance ---\n\n";
    std::cout << "Sequential" << std::endl;
    performVectorSortOperation(random, "        Random Time ", false);
    performVectorSortOperation(sorted, "        Sorted Time ", false);
    performVectorSortOperation(reversed, "        Reversed Time ", false);
    performVectorSortOperation(organPipe, "        Organ Pipe Time ", false);
    performVectorSortOperation(rotated, "        Rotated Time ", false);

    std::cout << "\nParallel" << std::endl;

    performVectorSortOperation(random, "        Random Time ", true);
    performVectorSortOperation(sorted, "        Sorted Time ", true);
    performVectorSortOperation(reversed, "        Reversed Time ", true);
    performVectorSortOperation(organPipe, "        Organ Pipe Time ", true);
    performVectorSortOperation(rotated, "        Rotated Time ", true);
    std::cout << "\n";
}