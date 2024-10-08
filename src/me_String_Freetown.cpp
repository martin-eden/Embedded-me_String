// Free functions for [me_String]

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

#include <stdarg.h> // va_list, va_start, va_end
#include <stdio.h> // vsnprintf()

/*
  Format string

  Implementation uses vsnprintf().
*/
TBool me_String::Freetown::FormatStr(
  me_ManagedMemory::TManagedMemory * ResultSeg,
  const TChar * FormatStr,
  va_list Args
)
{
  /*
    Implementation will use vsnprintf() from <stdio.h>.

    That fancy function accepts TUint_2 as buffer capacity.
    And returns length of formatted string in TSint_2.. Fuck you C!

    Anyway.. We don't know how long final string will be.
    We can obligate you to estimate buffer size. But we won't.
    Because you can't too.

    Instead we will do two calls to vsnprintf(). First with empty
    buffer just to get length of formatted string. Then we'll
    allocate memory and do the real call.

    And that's not all!

    Our buffer don't need trailing zero byte from so-called "string".
    So we'll do another memory allocation to copy that chunk without
    zero byte. 2*N memory consumption at runtime..

    Great API design guys!
  */

  // Return code from vsnprintf()
  TSint_2 ReturnCode = vsnprintf(0, 0, FormatStr, Args);

  // If vsnprintf() failed, return
  if (ReturnCode < 0)
    return false;

  // Assert: ReturnCode >= 0

  // Positive return code is theoretical result string length
  TUint_2 MemoryRequired = (TUint_2) ReturnCode;

  /*
    Okay, let's allocate memory and do _real_ call!
  */

  me_ManagedMemory::TManagedMemory Asciiz;

  // If no memory for ASCIIZ, return
  // ASCIIZ requires one more byte for tail
  if (!Asciiz.ResizeTo(MemoryRequired + 1))
    return false;

  /*
    We don't expect 2nd call to fail. It's same format string
    and arguments. Only buffer address and buffer size are changed.
    But we still check for error code and return if bad.
  */
  ReturnCode =
    vsnprintf(
      (TChar *) Asciiz.GetData().Start.Addr,
      Asciiz.GetSize(),
      FormatStr,
      Args
    );

  if (ReturnCode < 0)
    return false;

  // Finally! But if no memory for <Data>, return
  if (!ResultSeg->LoadFrom(&Asciiz))
    return false;

  // Assert: ResultSeg.Size >= 1

  // Trim tail zero byte from ASCIIZ
  if (!ResultSeg->ResizeTo(ResultSeg->GetSize() - 1))
    return false;

  return true;
}

/*
  All integer formatting functions represent number as fixed-length
  string with leading zeroes.

  All signed integer formatting functions represent number with
  leading sign. Sign of zero considered "+".
*/

/*
  Check that given number falls in decimal digits range [0, 9]
*/
TBool IsDigit(TUint_1 Value)
{
  return (Value <= 9);
}

/*
  Return ASCII value for digit

  For bad input returns "?" character.
*/
TChar DigToChar(TUint_1 Digit)
{
  if (!IsDigit(Digit))
    return '?';

  return ('0' + Digit); // <3 U C
}

/*
  Format TUint_4 in given length with zero padding
*/
TBool me_String::Freetown::FormatUint_4(
  me_ManagedMemory::TManagedMemory * Result,
  TUint_1 ResultLen,
  TUint_4 Value
)
{
  // No memory, return
  if (!Result->ResizeTo(ResultLen))
    return false;

  // Zero length? Job done!
  if (ResultLen == 0)
    return true;

  me_MemorySegment::TMemorySegment RawMem;

  /*
    We're getting allocated memory span for result and
    writing directly to it.
  */

  RawMem = Result->GetData();

  for (TUint_1 Offset = 0; Offset < RawMem.Size; ++Offset)
    RawMem.Bytes[Offset] = DigToChar(0);

  TUint_1 Offset = RawMem.Size - 1;
  while (Value > 0)
  {
    TUint_1 LastDigit = Value % 10;

    RawMem.Bytes[Offset] = DigToChar(LastDigit);

    if (Offset == 0)
      break;

    --Offset;
    Value = Value / 10;
  }

  return true;
}

/*
  Format TSint_4 in given length with leading sign and zero padding
*/
TBool me_String::Freetown::FormatSint_4(
  me_ManagedMemory::TManagedMemory * Result,
  TUint_1 ResultLen,
  TSint_4 Value
)
{
  if (ResultLen == 0)
    return true;

  TBool IsNegative = (Value < 0);
  if (IsNegative)
    Value = -Value;

  if (!FormatUint_4(Result, ResultLen, Value))
    return false;

  TChar SignChar;
  if (IsNegative)
    SignChar = '-';
  else
    SignChar = '+';

  Result->GetData().Bytes[0] = SignChar;

  return true;
}

/*
  2024-10-04
  2024-10-07
  2024-10-08
*/
