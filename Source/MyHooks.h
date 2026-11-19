#pragma once

// The original 1.8.86 port hooked fixed offsets inside GameDataReset/GameDataLoaded.
// Those intra-function offsets are not stable across runtimes, so the port uses
// SFSE messaging instead:
//   kMessage_PostLoadGame (3) -> ProcessFilesOnInitOrGameReset()
//   kMessage_NewGame      (4) -> ProcessFilesOnInitOrGameReset()
// PostDataLoad (2) is too early: TESDataHandler::formArrays is still empty there.
// SFSE has no PreLoadGame message, so stale restore entries are dropped instead
// of restored - the game rebuilds form data on load anyway.

namespace MyHooks
{
    inline bool Install()
    {
        return true;
    }
}
