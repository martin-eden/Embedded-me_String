// String formatting and related functions

/*
  Author: Martin Eden
  Last mod.: 2024-10-08
*/

/*
  Actually we're using string formatting implementation from
  snprintf().

  Point of creating this module was not new functionality
  but presenting functionality in convenient and sane way.
*/

#include "me_String.h"

#include <me_BaseTypes.h>
#include <me_ManagedMemory.h>
#include <me_MemorySegment.h> // TMemorySegment
#include <stdarg.h> // va_list, va_start, va_end for Format()

using namespace me_String;

/*
  Return our data span
*/
me_MemorySegment::TMemorySegment TString::GetData()
{
  return Data.GetData();
}

// Copy from memory segment
TBool TString::CopyFrom(
  me_MemorySegment::TMemorySegment Memseg
)
{
  return Data.LoadFrom(Memseg);
}

// Copy from ASCIIZ
TBool TString::CopyFrom(
  const TChar * Asciiz
)
{
  return Data.LoadFrom(Asciiz);
}

// Copy from our specie
TBool TString::CopyFrom(
  TString String
)
{
  return Data.LoadFrom(&String.Data);
}

/*
  Format string

  Using string with printf() format specifiers.
*/
TBool TString::Format(
  const TChar * FormatStr,
  ...
)
{
  TBool Result;
  va_list Args;

  va_start(Args, FormatStr);
  Result = me_String::Freetown::Format(&Data, FormatStr, Args);
  va_end(Args);

  return Result;
}

/*
  2024-10-04
  2024-10-07
  2024-10-08
*/
