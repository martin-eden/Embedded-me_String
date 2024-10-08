#!/bin/bash

# Uninstall library
arduino-cli lib uninstall me_String

# Uninstall dependencies
arduino-cli lib uninstall \
  me_ManagedMemory \
  me_MemorySegment \
  me_BaseTypes
