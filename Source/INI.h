#pragma once

// Win32 profile-API replacement for the original CSimpleIniA based reader.
// The plugin only ever used a single [Settings] section with scalar values,
// so GetPrivateProfileIntA / WritePrivateProfileStringA are sufficient.

namespace INI
{
    inline bool EnsureParentDirectory(const std::string& a_path)
    {
        const auto parent = std::filesystem::path(a_path).parent_path();
        if (parent.empty()) {
            return true;
        }

        std::error_code ec;
        if (std::filesystem::exists(parent, ec)) {
            return true;
        }

        return std::filesystem::create_directories(parent, ec);
    }

    inline bool ReadBool(const char* a_key, const bool a_default, const char* a_path)
    {
        const int value = ::GetPrivateProfileIntA("Settings", a_key, a_default ? 1 : 0, a_path);
        return value != 0;
    }

    inline void WriteBool(const char* a_key, const bool a_value, const char* a_path)
    {
        ::WritePrivateProfileStringA("Settings", a_key, a_value ? "1" : "0", a_path);
    }

    void ProcessINIFile()
    {
        try {
            if (!EnsureParentDirectory(s_IniPath)) {
                logger::info("Cannot create the directory for>>{}", s_IniPath.c_str());
                return;
            }

            const bool exists = std::filesystem::exists(s_IniPath);
            const char* path  = s_IniPath.c_str();

            if (!exists) {
                WriteBool("bDebugMode", bDebugMode, path);
                WriteBool("bShowLoadedMessage", bShowLoadedMessage, path);
                WriteBool("bShowWarningsAsMessageBox", bShowWarningsAsMessageBox, path);
                WriteBool("bShowWarningsIfFormNotBuilt", bShowWarningsIfFormNotBuilt, path);
                logger::info("Created default INI file>>{}", path);
                return;
            }

            bDebugMode                  = ReadBool("bDebugMode", bDebugMode, path);
            bShowLoadedMessage          = ReadBool("bShowLoadedMessage", bShowLoadedMessage, path);
            bShowWarningsAsMessageBox   = ReadBool("bShowWarningsAsMessageBox", bShowWarningsAsMessageBox, path);
            bShowWarningsIfFormNotBuilt = ReadBool("bShowWarningsIfFormNotBuilt", bShowWarningsIfFormNotBuilt, path);
        } catch (...) {
            logger::info("Cannot read the INI file>>{}", s_IniPath.c_str());
        }
    }
}
