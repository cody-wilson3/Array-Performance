#include "sortutils.hpp"

#include <algorithm>
#include <array>

SourceArray getStartArray();

int main()
{
    // Random
    SourceArray random = getStartArray();

    // Sorted
    SourceArray sorted = random;
    std::sort(sorted.begin(), sorted.end());

    // Reversed
    SourceArray reversed = sorted;
    std::reverse(reversed.begin(), reversed.end());

    // OrganPipe
    SourceArray organPipe = sorted;
    organPipeStdArray(organPipe);

    // Rotated
    SourceArray rotated = sorted;
    uint8_t pivot = 1;
    std::rotate(rotated.begin(), rotated.begin() + pivot, rotated.end());

    //--------- Raw Array ------------
    evaluateRawArray(random, sorted, reversed, organPipe, rotated);

    //--------- std::array -----------
    evaluateStdArray(random, sorted, reversed, organPipe, rotated);

    //--------- std::vector ----------
    evaluateStdVector(random, sorted, reversed, organPipe, rotated);
}