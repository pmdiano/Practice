/**
 * Copied from: https://github.com/dotnet/coreclr/blob/master/src/jit/hashbv.cpp
 * @param  bits [description]
 * @return      [description]
 */
int countBitsInWord(unsigned int bits)
{
    // In-place adder tree: perform 16 1-bit adds, 8 2-bit adds,
    // 4 4-bit adds, 2 8=bit adds, and 1 16-bit add.
    bits = ((bits >> 1) & 0x55555555) + (bits & 0x55555555);
    bits = ((bits >> 2) & 0x33333333) + (bits & 0x33333333);
    bits = ((bits >> 4) & 0x0F0F0F0F) + (bits & 0x0F0F0F0F);
    bits = ((bits >> 8) & 0x00FF00FF) + (bits & 0x00FF00FF);
    bits = ((bits >>16) & 0x0000FFFF) + (bits & 0x0000FFFF);
    return (int) bits;
}

/**
 * Copied from: https://github.com/dotnet/coreclr/blob/master/src/jit/hashbv.cpp
 * @param  bits [description]
 * @return      [description]
 */
int countBitsInWord(unsigned __int64 bits)
{
    bits = ((bits >> 1) & 0x5555555555555555) + (bits & 0x5555555555555555);
    bits = ((bits >> 2) & 0x3333333333333333) + (bits & 0x3333333333333333);
    bits = ((bits >> 4) & 0x0F0F0F0F0F0F0F0F) + (bits & 0x0F0F0F0F0F0F0F0F);
    bits = ((bits >> 8) & 0x00FF00FF00FF00FF) + (bits & 0x00FF00FF00FF00FF);
    bits = ((bits >>16) & 0x0000FFFF0000FFFF) + (bits & 0x0000FFFF0000FFFF);
    bits = ((bits >>32) & 0x00000000FFFFFFFF) + (bits & 0x00000000FFFFFFFF);
    return (int) bits;
}
