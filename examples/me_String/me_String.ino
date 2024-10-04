// [me_String] test/demo

/*
  Author: Martin Eden
  Last mod.: 2024-10-04
*/

#include <me_String.h>

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
    me_String::Print;

  TString String;

  String.Format("Test [%2u.%u%u].\n", 3, 14, 15);
  Print(&String);

  String.Format("123\n");
  Print(&String);
}

/*
  2024-10-04
*/
