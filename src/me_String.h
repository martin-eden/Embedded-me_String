// String and integers formatting

/*
  Author: Martin Eden
  Last mod.: 2024-10-08
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
      // Format TUint_1
      TBool Format(TUint_1 Value);
      // Format TUint_2
      TBool Format(TUint_2 Value);
      // Format TUint_4
      TBool Format(TUint_4 Value);
      // Format TSint_1
      TBool Format(TSint_1 Value);
      // Format TSint_2
      TBool Format(TSint_2 Value);
      // Format TSint_4
      TBool Format(TSint_4 Value);


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
    TBool FormatUint_4(
      me_ManagedMemory::TManagedMemory * Result,
      TUint_1 ResultLen,
      TUint_4 Value
    );

    // Format TUint_4 in given length with sign and zero padding
    TBool FormatSint_4(
      me_ManagedMemory::TManagedMemory * Result,
      TUint_1 ResultLen,
      TSint_4 Value
    );
  }
}

/*
  2024-10-04
  2024-10-07
  2024-10-08
*/
