// Free functions for [me_String]

/*
  Author: Martin Eden
  Last mod.: 2024-10-23
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
      (TChar *) Asciiz.GetData().Addr,
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
  TUint_4 to ASCII

  Zeroes padding.

  Arguments

    TMemorySegment Result

      We will write characters here. Segment should describe
      valid memory to which we can write.

    TUint_4 Value

      Value we're representing
*/
void me_String::Freetown::FormatUint_4(
  me_MemorySegment::TMemorySegment Result,
  TUint_4 Value
)
{
  // Zero length? Job done!
  if (Result.Size == 0)
    return;

  // Initially fill Result with "0" characters
  for (TUint_1 Offset = 0; Offset < Result.Size; ++Offset)
    Result.Bytes[Offset] = DigToChar(0);

  // Write digits from least to most significant
  TUint_1 Offset = Result.Size - 1;
  while (Value > 0)
  {
    TUint_1 LastDigit = Value % 10;

    Result.Bytes[Offset] = DigToChar(LastDigit);

    Value = Value / 10;

    // No more space to write, break
    if (Offset == 0)
      break;

    --Offset;
  }
}

/*
  TSint_4 to ASCII

  Zeroes padding, "+"/"-" sign. Zero has sign "+".
*/
void me_String::Freetown::FormatSint_4(
  me_MemorySegment::TMemorySegment Result,
  TSint_4 Value
)
{
  if (Result.Size == 0)
    return;

  TBool IsNegative = (Value < 0);

  TUint_4 Uint_4_Value;

  if (IsNegative)
    Uint_4_Value = -Value;
  else
    Uint_4_Value = Value;

  FormatUint_4(Result, Uint_4_Value);

  TChar SignChar;
  if (IsNegative)
    SignChar = '-';
  else
    SignChar = '+';

  Result.Bytes[0] = SignChar;
}

/*
  2024-10-04
  2024-10-07
  2024-10-08
  2024-10-17 Simplification
*/
