#pragma once

// Game setting access built on the current CommonLibSF RE::Setting / GameSettingCollection.
// The 1.8.86 code used a hand-rolled qqSetting mirror; the layout is the same
// (value @0x08, default @0x10, name @0x18), so only the accessors changed.

namespace GameSettings
{
    using qqSetting = RE::Setting;

    inline RE::GameSettingCollection* GetCollection()
    {
        return RE::GameSettingCollection::GetSingleton();
    }

    inline RE::Setting* GetSettingByName(const std::string& a_name)
    {
        auto* collection = GetCollection();
        if (!collection) {
            return nullptr;
        }

        return collection->GetSetting(a_name.c_str());
    }

    inline bool IsSettingANumber(const RE::Setting::Type a_type)
    {
        switch (a_type) {
        case RE::Setting::Type::kBool:
        case RE::Setting::Type::kChar:
        case RE::Setting::Type::kUChar:
        case RE::Setting::Type::kInt:
        case RE::Setting::Type::kUInt:
        case RE::Setting::Type::kFloat:
            return true;
        default:
            return false;
        }
    }

    inline bool IsSettingABool(const RE::Setting::Type a_type)
    {
        return a_type == RE::Setting::Type::kBool;
    }

    inline bool IsSettingAString(const RE::Setting::Type a_type)
    {
        return a_type == RE::Setting::Type::kString;
    }

    // The game keeps cached copies of some settings; the original mod notified it
    // through the function at REL::ID(198258) after changing a value.
    inline void NotifySettingUpdated(RE::Setting* a_setting)
    {
        if (!a_setting) {
            return;
        }

        using func_t = void (*)(RE::Setting*);
        static REL::Relocation<func_t> func{ REL::ID(198258) };
        func(a_setting);
    }

    inline void Init()
    {
        if (!GetCollection()) {
            logger::info("Game settings collection is not available yet.");
        }
    }
}
