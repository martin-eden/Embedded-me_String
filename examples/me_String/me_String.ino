// [me_String] test/demo

/*
  Author: Martin Eden
  Last mod.: 2024-10-0
*/

#include <me_String.h>
#include <me_MemorySegment.h> // for Print

#include <me_BaseTypes.h>
#include <me_InstallStandardStreams.h>
#include <me_UartSpeeds.h>

void setup()
{
  Serial.begin(me_UartSpeeds::Arduino_Normal_Bps);
  InstallStandardStreams();

  printf("[me_String] Okay, we are here.\n");
  RunTest();
  printf("[me_String] Done.\n");
}

void loop()
{
}

// --

void RunTest()
{
  using
    me_String::TString,
    me_MemorySegment::Freetown::Print;

  TString String;

  String.Format("Test [%02u.%u%u].\n", 3, 14, 15);
  // String.PrintWrappings();
  Print(String.GetData());

  String.Format("123\n");
  // String.PrintWrappings();
  Print(String.GetData());
}

/*
  2024-10-04
  2024-10-07
*/
