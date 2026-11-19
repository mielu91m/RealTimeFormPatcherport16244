#pragma once

// The 1.8.86 build called the in-game message box UI through raw vtable/REL lookups.
// That UI path is not exposed by the current CommonLibSF and its internals moved,
// so plugin diagnostics go to the SFSE log and the in-game console instead.
// This keeps plugin load non-blocking and avoids hooking unstable UI code.

namespace SFMessageBox
{
    inline void Init()
    {
    }

    inline void SFMessageBoxEx(const char* a_text)
    {
        if (!a_text) {
            return;
        }

        logger::info("{}", a_text);

        if (auto* console = RE::ConsoleLog::GetSingleton()) {
            console->PrintLine("%s", a_text);
        }
    }
}
