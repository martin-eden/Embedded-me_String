// String and integers formatting

/*
  Author: Martin Eden
  Last mod.: 2024-10-23
*/

#include <me_BaseTypes.h>
#include <me_MemorySegment.h>
#include <me_ManagedMemory.h>

#include <stdarg.h> // "va_list" for free free function Format()

namespace me_String
{
  class TString
  {
    public:
      // Return our data span
      me_MemorySegment::TMemorySegment GetData();

      // Copy from memory segment
      TBool CopyFrom(me_MemorySegment::TMemorySegment Memseg);
      // Copy from ASCIIZ
      TBool CopyFrom(const TChar * Asciiz);
      // Copy from our specie
      TBool CopyFrom(TString String);

      // Format string
      TBool Format(const TChar * FormatStr, ...);

    private:
      me_ManagedMemory::TManagedMemory Data;
  };

  namespace Freetown
  {
    // Format string
    TBool FormatStr(
      me_ManagedMemory::TManagedMemory * Result,
      const TChar * FormatStr,
      va_list Args
    );

    // Format TUint_4 in given length with zero padding
    void FormatUint_4(
      me_MemorySegment::TMemorySegment Result,
      TUint_4 Value
    );

    // Format TSint_4 in given length with sign and zero padding
    void FormatSint_4(
      me_MemorySegment::TMemorySegment Result,
      TSint_4 Value
    );
  }
}

/*
  2024-10-04
  2024-10-07
  2024-10-08
  2024-10-17
*/
