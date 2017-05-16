#include "NTools.h"

namespace Nully
{
  bool NTools::IsBitSet(const uint32_t a_bytes, const uint8_t a_bitsToShift)
  {
    // IsBitSet must be implemented for LittleEndian and BigEndian (to support AMD and Intel)

    // example: a_bytes = 0xF0000000
    // binary: 1111 0000 0000 0000 0000 0000 0000 0000
    //         #
    // you are looking for the 32th bit (#)

    // so in order to get the bit you need, you bitshift 0x1 (binary: 0001) by 31 to the left (assuming you have 4 bytes...)
    // before shift:                      0000 0000 0000 0000 0000 0000 0000 0001  (hex: 0x1, or 1 decimal)
    // after shifting by 31 to the left:  1000 0000 0000 0000 0000 0000 0000 0000

    // now simply & operator between a_bytes and the shifted 1
    // a_bytes    1111 0000 0000 0000 0000 0000 0000 0000 (0xF0000000 in hex)
    // & a_shift  1000 0000 0000 0000 0000 0000 0000 0000
    // resultA    1000 0000 0000 0000 0000 0000 0000 0000

    // so in order to check if the bit is set
    // simply if (a_bytes & a_shift == a_shift)
    // in binary it looks like this:
    // resultA    1000 0000 0000 0000 0000 0000 0000 0000
    // == a_shift 1000 0000 0000 0000 0000 0000 0000 0000
    // bit is set
    uint32_t firstBit = 0x1;
    uint32_t shifted = firstBit << (a_bitsToShift - 1);

    if ((a_bytes & shifted) == shifted)
    {
      return true;
    }

    return false;
  }
}
