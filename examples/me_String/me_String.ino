// [me_String] test/demo

/*
  Author: Martin Eden
  Last mod.: 2024-10-08
*/

#include <me_String.h>

#include <me_BaseTypes.h>
#include <me_UartSpeeds.h>
#include <me_Console.h>

#include <me_ManagedMemory.h>

void setup()
{
  Console.Init(me_UartSpeeds::Arduino_Normal_Bps);

  Console.Print("[me_String] Okay, we are here.");
  RunTest();
  Console.Print("[me_String] Done.");
}

void loop()
{
}

// --

void RunTest()
{
  me_String::TString String;

  String.Format("Test [%02u.%02u %02u].", 3, 14, 15);
  Console.Print(String.GetData());

  String.Format(123);
  Console.Print(String.GetData());

  String.Format("ABCDEF");
  Console.Print(String.GetData());
}

/*
  2024-10-04
  2024-10-07
  2024-10-08
*/
