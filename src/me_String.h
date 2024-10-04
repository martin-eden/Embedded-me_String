// String formatting and related functions

/*
  Author: Martin Eden
  Status: sketching
  Last mod.: 2024-10-04
*/

#include <me_BaseTypes.h>
#include <me_ManagedMemory.h>

namespace me_String
{
  class TString
  {
    public:
      // Copy from memory segment
      TBool CopyFrom(me_MemorySegment::TMemorySegment Memseg);
      // Copy from ASCIIZ
      TBool CopyFrom(const TChar * Asciiz);
      // Copy from our specie
      TBool CopyFrom(TString String);

      // Copy our string to memory segment
      TBool CopyTo(me_ManagedMemory::TManagedMemory * Memseg);

      // Format string
      void Format(const TChar * FormatStr, ...);

    protected:
      me_ManagedMemory::TManagedMemory Data;

    private:
  };

  // Public Print() for stdout
  void Print(TString * String);
}

/*
  2024-10-04
*/
