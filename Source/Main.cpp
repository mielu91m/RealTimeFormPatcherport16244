#include <filesystem>
#include <format>
#include <iterator>
#include <map>
#include <vector>

constexpr std::uint32_t iVersion     = 123;
constexpr std::uint32_t iVersionBeta = 0;

//#define TestingPlugin

#ifdef TestingPlugin
#include "NanoTimer.h"
//#include "ctre-unicode.hpp"
#endif //  TestingPlugin

SFSE_PLUGIN_VERSION = []() noexcept {
    SFSE::PluginVersionData v{};
    v.PluginVersion({ 1, 24, 0, 0 });
    v.PluginName("RealTimeFormPatcher");
    v.AuthorName("TommInfinite");
    v.UsesSigScanning(false);
    v.UsesAddressLibrary(true);
    v.HasNoStructUse(false);   // RTFP patches live game records
    v.IsLayoutDependent(true); // record layouts are version specific
    v.CompatibleVersions({ SFSE::RUNTIME_LATEST });
    return v;
}();

std::string GetPluginVersionString()
{
    if (iVersionBeta) {
        return std::format("RTFP V.{} b{}", iVersion, iVersionBeta);
    }
    else {
        return std::format("RTFP V.{}", iVersion);
    }
}

class RTFPCriticalSection
{
public:
    std::atomic_bool bInit = false;

    CRITICAL_SECTION critSection;

    void Initialize()
    {
        bInit = true;
        InitializeCriticalSection(&critSection);
    }

    bool IsInit() { return bInit; }

    void Enter() { EnterCriticalSection(&critSection); }

    void Leave() { LeaveCriticalSection(&critSection); }
};

RTFPCriticalSection CritSectionMain;

class RTFPCriticalSectionVisitor
{
public:
    RTFPCriticalSectionVisitor() { CritSectionMain.Enter(); }

    ~RTFPCriticalSectionVisitor() { CritSectionMain.Leave(); }
};

std::string s_IniPath     = "Data/SFSE/Plugins/RealTimeFormPatcher.ini";
std::string s_InputFolder = "Data/SFSE/Plugins/RealTimeFormPatcher";

bool bDebugMode                  = false;
bool bShowLoadedMessage          = true;
bool bShowWarningsAsMessageBox   = true;
bool bShowWarningsIfFormNotBuilt = false;

std::string   sFileErrors{};
int           iFilesProcessed = 0;
std::uint32_t iFileIDCount    = 0;
bool          bGameReset      = false;

bool bASIVersion = false;

#define Iter  (*it)
#define Iter2 (*it2)
#define Iter3 (*it3)

#define DConsole_Print(...)                                                                                                                                                        \
    if (bDebugMode) {                                                                                                                                                              \
        auto Console = RE::ConsoleLog::GetSingleton();                                                                                                                             \
        Console->PrintLine(__VA_ARGS__);                                                                                                                                           \
    }

#define _DMESSAGE(...)                                                                                                                                                             \
    if (bDebugMode) {                                                                                                                                                              \
        logger::info(__VA_ARGS__);                                                                                                                                                 \
    };

#define GET_VARIABLE_NAME(Variable) (#Variable)

#define _MESSAGE(...) logger::info(__VA_ARGS__);

#define MEMBER(...)      GET_VARIABLE_NAME(__VA_ARGS__), __VA_ARGS__
#define MEMBERUINT8(...) GET_VARIABLE_NAME(__VA_ARGS__), (std::uint8_t)__VA_ARGS__
#define CONSTEVAL(...)   []() consteval { return __VA_ARGS__; }()

template <typename Member>
void CheckFormForForMemberFormAndPrintOut(std::string VarName, Member MemberToCheck)
{
    if (MemberToCheck) {
        _DMESSAGE("{} exists,formID>>{:08X}", VarName, MemberToCheck->formID);
    }
    else {
        _DMESSAGE("{} doesn't exist(NULL)", VarName);
    }
}

template <typename Member>
void CheckFormForForMemberValueAndPrintOut(std::string VarName, Member MemberToCheck)
{
    _DMESSAGE("{} value>>{}", VarName, MemberToCheck);
}

bool f_Does_FolderExist(std::string& name)
{
    if (std::filesystem::is_directory(name)) {
        return true;
    }
    else {
        return false;
    }
}

void f_Create_Folders_For_Path(std::string s_FilePath)
{
    std::filesystem::create_directories(s_FilePath);
}

// #include "Events.h"

#include "GameSettings.h"
#include "INI.h"
#include "RTFPCondition.h"
#include "RTFPSDKCompat.h"
#include "InputGetter.h"
#include "MessageBox.h"

#ifdef TestingPlugin
#include "Testing.h"
#endif //  TestingPlugin

void ProcessFilesOnInitOrGameReset()
{
    RTFPCriticalSectionVisitor Visitor{};

    _MESSAGE("File processing starts.");
    // The game rebuilds form data on load, so previously stored restore data
    // points into freed memory - drop it instead of restoring.
    Input::ClearStoredEntries();
    GameSettings::Init();
    LoadedPlugins::Get();

#if defined(TestingPlugin)
    _MESSAGE("BEFORE CHANGES");
    Test();
    plf::nanotimer timer;
    timer.start();
#endif

    Input::ProcessAllFiles();

#if defined(TestingPlugin)
    _MESSAGE("Files processed - seconds elapsed>>{}", float(timer.get_elapsed_ms() / 1000));
    _DMESSAGE("AFTER CHANGES");
    Test();
#endif

    Input::Debug::ProcessFormsInArrayAfterChanges();
    _DMESSAGE("File processing ends.");
}


// struct MyStruct {
//
//     SF_HEAP_REDEFINE_NEW(MyStruct);
//
//
//     ~MyStruct() {
//         DConsole_Print("struct is removed");
//     }
//
// };

void OnDefferedInit()
{
    // auto EventSource = RE::UI::GetSingleton()->GetEventSource<RE::MenuOpenCloseEvent>();
    // auto EventSink   = new MenuOpenCloseEventSink;
    // EventSource->RegisterSink(EventSink);

    // MyStruct TestStack;
    // MyStruct* TestHeap = new MyStruct[10];
    // delete[] TestHeap;

    ProcessFilesOnInitOrGameReset();

    if (sFileErrors.length()) {
        if (bShowWarningsAsMessageBox) {
            _MESSAGE("Showing messagebox error>>{}", sFileErrors);
            SFMessageBox::Init();
            SFMessageBox::SFMessageBoxEx(sFileErrors.c_str());
            _MESSAGE("Shown");
        }
        else {
            DConsole_Print(sFileErrors.c_str());
        }
    }

    if (bShowLoadedMessage) {
        auto sMessage = GetPluginVersionString() + " - " + "processed files>>" + std::to_string(iFilesProcessed);
        DConsole_Print("%s", sMessage.c_str());
    }

    #ifdef TestingPlugin

        _DMESSAGE("CHECKING SMALL FORMS AND MEDIUM FORMS")
        auto SmallForm = Input::GetFormFromStringEx("TestSmallPlugin.esm~808");

        if (SmallForm)
        {
            _DMESSAGE("Test small form exists(OKAY)");

            auto SmallMasterInfo = LoadedPlugins::GetModInfo("TestSmallPlugin.esm");

            if (SmallMasterInfo->IsFormInPlugin(SmallForm->formID))
            {
                _DMESSAGE("Test small form  is in SmallMaster(OKAY)");
            }
            else {
                _DMESSAGE("Test small form is NOT in SmallMaster(NOT OKAY)");
            }

            auto VanillaSmallMaster = LoadedPlugins::GetModInfo("SFBGS007.esm");

            if (!VanillaSmallMaster)
            {
                _DMESSAGE("Vanilla Small master doesn't exists");
            }
            else {
                if (VanillaSmallMaster->IsFormInPlugin(SmallForm->formID)) {
                    _DMESSAGE("Test small form  is in VanillaSmallMaster(NOT OKAY)");
                }
                else {
                    _DMESSAGE("Test small form is NOT in VanillaSmallMaster(OKAY)");
                }

            }

        }
        else {
            _DMESSAGE("Test small form  doesn't exist(NOT OKAY)");
        }

        SmallForm = Input::GetFormFromStringEx("TestSmallPlugin.esm~810");

        if (SmallForm) {
            _DMESSAGE("Test small 2 form exists(NOT OKAY)");
        }
        else {
            _DMESSAGE("Test small 2 form  doesn't exist(OKAY)");
        }

       auto MedForm = Input::GetFormFromStringEx("TestMediumPlugin.esm~807");

        if (MedForm) {
            _DMESSAGE("Test Med form exists(OKAY)");

            auto MedMasterInfo = LoadedPlugins::GetModInfo("TestMediumPlugin.esm");

            if (MedMasterInfo->IsFormInPlugin(MedForm->formID)) {
                _DMESSAGE("Test med form  is in medMaster(OKAY)");
            }
            else {
                _DMESSAGE("Test medform is NOT in medMaster(NOT OKAY)");
            }

            auto VanillaMedMaster = LoadedPlugins::GetModInfo("SFBGS003.esm");

            if (!VanillaMedMaster) {
                _DMESSAGE("Vanilla Med master doesn't exists");
            }
            else {
                if (VanillaMedMaster->IsFormInPlugin(MedForm->formID)) {
                    _DMESSAGE("Test Med form  is in VanillaMedMaster(NOT OKAY)");
                }
                else {
                    _DMESSAGE("Test Med form is NOT in VanillaMedMaster(OKAY)");
                }
            }


        }
        else {
            _DMESSAGE("Test Med form  doesn't exist(NOT OKAY)");
        }

        MedForm = Input::GetFormFromStringEx("TestMediumPlugin.esm~810");

        if (MedForm) {
            _DMESSAGE("Test Med 2 form exists(NOt OKAY)");
        }
        else {
            _DMESSAGE("Test Med form 2  doesn't exist(OKAY)");
        }

    #endif 





}

#include "MyHooks.h"

// SFSE message listener. In Starfield's SFSE the numeric types are
// 0 PostLoad, 1 PostPostLoad, 2 PostDataLoad, 3 PostLoadGame, 4 NewGame.
// PostDataLoad fires before TESDataHandler::formArrays is populated, so patches
// are applied on PostLoadGame/NewGame, after the game has (re)built form data.
// SFSE has no PreLoadGame message; stale stored entries are simply dropped
// because the game rebuilds the form data itself on each load.
void Listener(SFSE::MessagingInterface::Message* message) noexcept
{
    switch (message->type) {
    case SFSE::MessagingInterface::kPostLoad:
        break;
    case SFSE::MessagingInterface::kPostPostLoad:
        break;
    case SFSE::MessagingInterface::kPostDataLoad:
        break;
    case 3: // kMessage_PostLoadGame
        bGameReset = false;
        ProcessFilesOnInitOrGameReset();
        break;
    case 4: // kMessage_NewGame
        bGameReset = false;
        ProcessFilesOnInitOrGameReset();
        break;
    default:
        break;
    }
}

void InitializeLogging()
{
    try {
        auto path = SFSE::log::log_directory();
        if (!path) {
            return;
        }

        *path /= "RealTimeFormPatcher.log";

        auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);
        auto log  = std::make_shared<spdlog::logger>("rtfp", std::move(sink));
        log->set_level(spdlog::level::info);
        log->flush_on(spdlog::level::info);

        spdlog::set_default_logger(std::move(log));
        spdlog::set_pattern("%v");
    } catch (...) {
        // logging must never abort plugin load
    }
}

bool LoadPlugin(const SFSE::LoadInterface* sfse)
{
    if (!bASIVersion) {
        SFSE::Init(sfse);

        if (const auto messaging{ SFSE::GetMessagingInterface() }; !messaging->RegisterListener(Listener))
            return false;
    }

    InitializeLogging();
    logger::info("Real Time Form Patcher V.{} b{} is loading. ASI>>{}", iVersion, iVersionBeta, bASIVersion);
    // logger::info("VER>>{},beta>>{}", iVersion,iVersionBeta);

    INI::ProcessINIFile();

    if (!MyHooks::Install()) {
        _MESSAGE("Cannot instal hooks - please wait for the update. Yes, Todd borked the game again, nothing I can do. You can probably post a comment on Nexus mod page, I like to see new notifications - it makes me feel less lonely.");
        return false;
    }

    Input::Load();
    CritSectionMain.Initialize();

    _MESSAGE("RealTimeFormPatcher has finished loading.");

#ifdef TestingPlugin
    g_timer.start();
    SFSE::GetTaskInterface()->AddPermanentTask(new GameLoopTask);
    // MH_Initialize();
    // CreateFormListHook::Install();
    // CreateStarbornGameHook::Install();
    // SetIsCreatingStarborbGameHook::Install();
    // SetIsCreatingStarborbGameHookAlt::Install();
    // ScrapAllocatorHook::Install();
    // MemoryFreeHook::Install();
    // AVMDataHook::Install();
#endif //  TestingPlugin

    return true;
}

// Main SFSE plugin entry point, initialize everything here
SFSE_PLUGIN_LOAD(const SFSE::LoadInterface* sfse)
{
    return LoadPlugin(sfse);
}

extern "C" __declspec(dllexport) void InitializeASI()
{
    InitializeLogging();
    bASIVersion = true;
    LoadPlugin(NULL);
}








//
//	struct PerkRankData
//{
//    BGSPerk*    perk;        // 00
//    std::int8_t currentRank; // 08
//};
//

//#pragma once
//
//#include "RE/B/BGSAttachParentArray.h"
//#include "RE/B/BGSBlockBashData.h"
//#include "RE/B/BGSDestructibleObjectForm.h"
//#include "RE/B/BGSEditorID.h"
//#include "RE/B/BGSEquipType.h"
//#include "RE/B/BGSInstanceNamingRulesForm.h"
//#include "RE/B/BGSKeywordForm.h"
//#include "RE/B/BGSModelMaterialSwap.h"
//#include "RE/B/BGSPickupPutdownSounds.h"
//#include "RE/B/BGSPreloadable.h"
//#include "RE/B/BSTSmartPointer.h"
//#include "RE/T/TESAmmo.h"
//#include "RE/T/TESBoundObject.h"
//#include "RE/T/TESDescription.h"
//#include "RE/T/TESEnchantableForm.h"
//#include "RE/T/TESFullName.h"
//
//namespace RE
//{
//
//    class TESObjectWEAPInstanceData;
//
//    class WeaponAmmoData
//    {
//    public:
//        char         pad_0000[32];  // 0x0000
//        RE::TESAmmo* ammo;          // 0x0020
//        char         pad_0028[8];   // 0x0028
//        uint32_t     ammoCapacity;  // 0x0030
//        char         pad_0034[336]; // 0x0034
//    };                              // Size: 0x0184
//
//    static_assert(offsetof(WeaponAmmoData, ammo) == 0x20);
//
//    class WeaponDamageData
//    {
//    public:
//        char                                                                                                pad_0000[16];         // 0x0000 // a pointer?
//        float                                                                                               attackDamage;         // 0x0010
//        float                                                                                               rangeMin;             // 0x0014
//        float                                                                                               rangeMax;             // 0x0018
//        float                                                                                               Unk1;                 // 0x001C
//        float                                                                                               Unk2;                 // 0x0020
//        float                                                                                               Unk3;                 // 0x0024
//        float                                                                                               Unk4;                 // 0x0028
//        float                                                                                               Unk5;                 // 0x002C
//        float                                                                                               Unk6;                 // 0x0030
//        float                                                                                               outOfRangeDamageMult; // 0x0034
//        float                                                                                               critDamageMult;       // 0x0038
//        float                                                                                               N000001A5;            // 0x003C
//        RE::SpellItem*                                                                                      critEffect;           // 0x0040
//        float                                                                                               N00000175;            // 0x0048
//        float                                                                                               critChanceIncMult;    // 0x004C
//        RE::BSTArray<RE::BSTTuple3<RE::TESForm*, RE::BGSCurveForm*, RE::BGSTypedFormValuePair::SharedVal>>* damageTypes;          // 0x0050
//    };                                                                                                                            // Size: 0x0140
//
//    static_assert(offsetof(WeaponDamageData, critChanceIncMult) == 0x4C);
//    static_assert(offsetof(WeaponDamageData, damageTypes) == 0x50);
//
//    class WeaponFiringData
//    {
//    public:
//        void* unk;
//        void* instanceData;
//        void* FiringType;
//        char  pad_0000[0x4];             // 0x18
//        float burstDelaySeconds;         // 1C
//        float attackSeconds;             // 0x0020
//        float fireSeconds;               // 0x0024
//        float attackDelaySec;            // 0x0028
//        float boltChargeSec;             // 0x002C
//        float pad30;                     // 0x0030
//        float shotsPerSecond;            // 34 FIX
//        bool  overrideRateOfFire;        // 38
//        float unknown;                   // 3C
//        float triggerThresholdPrimary;   // 40
//        float unk44;                     // 44
//        float triggerThresholdSecondary; // 48 FIX
//        bool  DualTriggerSet;            // 50
//    };
//
//    // static_assert(offsetof(WeaponFiringData, shotsPerSecond) == 0x34);
//    static_assert(offsetof(WeaponFiringData, pad30) == 0x30);
//    static_assert(offsetof(WeaponFiringData, triggerThresholdPrimary) == 0x40);
//    static_assert(offsetof(WeaponFiringData, triggerThresholdSecondary) == 0x48);
//    static_assert(offsetof(WeaponFiringData, burstDelaySeconds) == 0x1C);
//    static_assert(offsetof(WeaponFiringData, overrideRateOfFire) == 0x38);
//    static_assert(offsetof(WeaponFiringData, boltChargeSec) == 0x2C);
//    static_assert(offsetof(WeaponFiringData, attackDelaySec) == 0x28);
//    static_assert(offsetof(WeaponFiringData, unknown) == 0x3C);
//
//    class WeaponDataFlags
//    {
//    public:
//        TESObjectWEAPInstanceData* pad1; // 0x0000
//        TESObjectWEAPInstanceData* pad2;
//        uint8_t                    NonPlayable;
//        uint8_t                    PlayerOnly;
//        uint8_t                    flag3;
//        uint8_t                    flag4;
//        uint8_t                    CantDrop;
//        uint8_t                    MinorCrime;
//        uint8_t                    NonHostile;
//        uint8_t                    flag8;
//        uint8_t                    flag9;
//        uint8_t                    flag10;
//        uint8_t                    flag11;
//        uint8_t                    flag12;
//    };
//
//    class WeaponDataGeneral
//    {
//    public:
//        char         pad_0000[16];     // 0x0000
//        void*        equipSlot;        // 0x0010
//        char         pad_0018[24];     // 0x0018
//        void*        barrelData;       // 0x0030
//        uint32_t     Type;             // 0x0038
//        float        baseWeight;       // 0x003C
//        std::int32_t baseValue;        // 0x0040
//        float        baseSpeed;        // 0x0044
//        float        attackOxygenCost; // 0x0048
//        char         pad_004C[1];      // 0x004C
//    };                                 // Size: 0x004D
//
//    class WeapDataMelee
//    {
//    public:
//        char    pad_0000[16];  // 0x0000
//        float   N000001E6;     // 0x0010
//        float   bashDamage;    // 0x0014
//        float   reach;         // 0x0018
//        uint8_t Stagger;       // 0x001C
//        char    pad_001D[291]; // 0x001D
//    };                         // Size: 0x0140
//
//    class WeaponDataPower
//    {
//    public:
//        char pad_0000[64]; // 0x0000
//    };                     // Size: 0x0040
//
//    class WeapDataReload
//    {
//    public:
//        char  pad_0000[8]; // 0x0000
//        void* N000001F9;   // 0x0008
//        float Unknown;     // 0x0010
//        float Reloadspeed; // 0x0014
//        bool  Charging;    // 0x0018
//        bool  Single;      // 0x0019
//    };                     // Size: 0x001A
//
//    class WeapDataTurret
//    {
//    public:
//        char pad_0000[1088]; // 0x0000
//    };                       // Size: 0x0440
//
//    class WeapDataVariableRange
//    {
//    public:
//        char pad_0000[64]; // 0x0000
//    };                     // Size: 0x0040
//
//    class WeapDataVisuals
//    {
//    public:
//        char pad_0000[64]; // 0x0000
//    };                     // Size: 0x0040
//
//    class WeapDataShipWeapon
//    {
//    public:
//        char  pad_0000[32]; // 0x0000
//        float Unknown;      // 0x0020
//        char  pad_0024[4];  // 0x0024
//        float Unknown1;     // 0x0028
//        float Unknown2;     // 0x002C
//        float Unknown3;     // 0x0030
//        char  pad_0034[12]; // 0x0034
//    };                      // Size: 0x0040
//
//    class WeaponDataAudio
//    {
//    public:
//        char pad_0000[64]; // 0x0000
//    };                     // Size: 0x0040
//
//    class WeaponDataCharge
//    {
//    public:
//        char pad_0000[64]; // 0x0000
//    };                     // Size: 0x0040
//
//    class WeaponDataAim
//    {
//    public:
//        void* pad0;
//        void* pa8;
//        float sightedTransitionSeconds; // 10
//        // float pad;
//        void*         aimDownSightTemplate; // 18
//        void*         pad;                  // 20 AimDownSightData
//        void*         aimModel;             // 28
//        void*         pad30;                // 30 AimModelData
//        std::uint64_t pad38;                // 38
//        std::uint64_t pad40;                // 40
//        std::uint64_t pad48;                // 48
//        std::uint64_t pad50;                // 50
//        std::uint8_t  accuracyBonus;        // 58 Confirm later
//    };
//
//    static_assert(offsetof(WeaponDataAim, sightedTransitionSeconds) == 0x10);
//    static_assert(offsetof(WeaponDataAim, aimDownSightTemplate) == 0x18);
//    static_assert(offsetof(WeaponDataAim, aimModel) == 0x28);
//    static_assert(offsetof(WeaponDataAim, accuracyBonus) == 0x58);
//
//    class TESObjectWEAPInstanceData
//    {
//    public:
//        char                   pad_0000[24];          // 0x0000
//        WeaponDataAim*         WeaponDataAim;         // 0x0018
//        WeaponAmmoData*        WeaponAmmoData;        // 0x0020
//        WeaponDataAudio*       WeaponDataAudio;       // 0x0028
//        WeaponDataCharge*      WeaponDataCharge;      // 0x0030
//        WeaponDamageData*      WeaponDamage;          // 0x0038
//        WeaponFiringData*      WeaponFiringData;      // 0x0040
//        WeaponDataFlags*       WeaponFlags;           // 0x0048
//        WeaponDataGeneral*     WeapDataGeneral;       // 0x0050
//        WeapDataMelee*         WeapDataMelee;         // 0x0058
//        WeaponDataPower*       WeapDataPower;         // 0x0060
//        WeapDataReload*        WeapDataReload;        // 0x0068
//        WeapDataTurret*        WeapDataTurret;        // 0x0070
//        WeapDataVariableRange* WeapDataVariableRange; // 0x0078
//        WeapDataVisuals*       WeapDataVisuals;       // 0x0080
//        WeapDataShipWeapon*    WeapDataShipWeapon;    // 0x0088
//    };
//
//    static_assert(offsetof(TESObjectWEAPInstanceData, WeaponAmmoData) == 0x20);
//    static_assert(offsetof(TESObjectWEAPInstanceData, WeaponDamage) == 0x38);
//
//    namespace BGSMod::Attachment
//    {
//        class Mod;
//    }
//
//    class TESObjectWEAP : public TESBoundObject,            // 000
//                          public TESFullName,               // 0E0
//                          public BGSModelMaterialSwap,      // 0F0
//                          public TESEnchantableForm,        // 118
//                          public BGSDestructibleObjectForm, // 130
//                          public BGSEquipType,              // 140
//                          public BGSPreloadable,            // 150
//                          public BGSPickupPutdownSounds,    // 158
//                          public BGSBlockBashData,          // 1C0
//                          public BGSKeywordForm,            // 1D8
//                          public TESDescription,            // 208
//                          public BGSInstanceNamingRulesForm // 220
//    {
//    public:
//        SF_RTTI_VTABLE(TESObjectWEAP);
//        SF_FORMTYPE(WEAP);
//
//        ~TESObjectWEAP() override; // 00
//
//        // members
//        BGSEditorID                                formEditorID;      // 230
//        BSTSmartPointer<TESObjectWEAPInstanceData> weaponData;        // 240
//        BGSAttachParentArray                       attachParents;     // 248
//        BGSMod::Attachment::Mod*                   embeddedWeaponMod; // 268
//        std::uint8_t                               unk270;            // 270
//    };
//
//    static_assert(sizeof(TESObjectWEAP) == 0x278);
//}


//	class TESConditionItem
//{
// public:
//    TESForm*          unk0;
//    TESConditionItem* next;
//
//    union
//    {
//        TESGlobal* global;
//        float      value;
//    };
//
//    std::uint64_t pad;
//    std::uint64_t pad2;
//    std::uint64_t pad3;
//    std::uint64_t pad4;
//    std::uint64_t pad5;
//};
//
// static_assert(sizeof(TESConditionItem) == 0x40);



//#pragma once
//
//#include "RE/B/BGSKeyword.h"
//
//namespace RE
//{
//    enum class KeywordType
//    {
//        kNone,
//        kComponentTechLevel,
//        kAttachPoint,
//        kComponentProperty,
//        kInstantiationFilter,
//        kModAssociation,
//        kSound,
//        kAnimArchetype,
//        kFunctionCall,
//        kRecipeFilter,
//        kAttractionType,
//        kDialogueSubtype,
//        kQuestTarget,
//        kAnimFlavor,
//        kAnimGender,
//        kAnimFaceArchetype,
//        kQuestGroup,
//        kAnimInjured,
//        kDispelEffect,
//
//        kTotal
//    };
//
//    template <KeywordType TYPE>
//    class BGSTypedKeywordValue
//    {
//    public:
//        // members
//        std::uint16_t   keywordIndex; // 0
//        RE::BGSKeyword* keyword;
//    };
//
//    namespace detail
//    {
//        [[nodiscard]] BGSKeyword* BGSKeywordGetTypedKeywordByIndex(KeywordType a_type, std::uint16_t a_index);
//    }
//
//    template <KeywordType TYPE>
//    class BGSTypedKeywordValueArray
//    {
//    public:
//        [[nodiscard]] bool HasKeyword(BGSKeyword* a_keyword)
//        {
//            // for (std::uint32_t i = 0; i < size; ++i) {
//            //	const auto kywd = detail::BGSKeywordGetTypedKeywordByIndex(TYPE, array[i].keywordIndex);
//            //	if (kywd == a_keyword) {
//            //		return true;
//            //	}
//            // }
//            return false;
//        }
//
//        // members
//        BGSKeyword** firstEntry;
//        BGSKeyword** lastEntry;
//        BGSKeyword** lastEntry2;
//        // BGSTypedKeywordValue<TYPE>* array;  // 00
//        // std::uint32_t               size;   // 08
//        // std::uint64_t               unk10;  // 10
//    };
//
//    // static_assert(sizeof(BGSTypedKeywordValueArray<KeywordType::kNone>) == 0x18);
//} // namespace RE



//#pragma once
//
//#include "RE/B/BGSAttachParentArray.h"
//#include "RE/B/BSTArray.h"
//#include "RE/B/BaseFormComponent.h"
//#include "RE/T/TESDescription.h"
//#include "RE/T/TESFullName.h"
//
//namespace RE
//{
//    class BGSKeyword;
//    class BGSMorphableObject;
//    class BGSAddonNode;
//} // namespace RE
//
//namespace RE::BGSMod
//{
//    namespace Attachment
//    {
//        class Mod : public TESForm,             // 00
//                    public TESFullName,         // 30
//                    public TESDescription,      // 40
//                    public BGSModelMaterialSwap // 58
//        {
//        public:
//            SF_RTTI_VTABLE(BGSMod__Attachment__Mod);
//            SF_FORMTYPE(OMOD);
//
//            struct Data
//            {
//            public:
//                // members
//
//                enum class IncludesFlag
//                {
//                    kNone       = 0,
//                    kOptional   = 1 << 0,
//                    kDontUseAll = 1 << 1
//                };
//
//                struct Include
//                {
//                    RE::BGSMod::Attachment::Mod*                 mod;
//                    std::uint8_t                                 level;
//                    stl::enumeration<IncludesFlag, std::uint8_t> flags;
//                };
//
//                static_assert(sizeof(Include) == 0x10);
//
//                struct Property
//                {
//                    struct ValueType1Bool
//                    {
//                        bool  value1;
//                        bool  value2;
//                        void* pad;
//                    };
//
//                    struct ValueType2Float
//                    {
//                        float value1;
//                        float value2;
//                        void* pad;
//                    };
//
//                    struct ValueType3Int
//                    {
//                        std::int32_t value1;
//                        std::int32_t value2;
//                        void*        pad;
//                    };
//
//                    struct ValueType4FormFloat
//                    {
//                        RE::TESForm* value1;
//                        float        value2;
//                    };
//
//                    union // 0
//                    {
//                        ValueType1Bool      type1Val;
//                        ValueType2Float     type2Val;
//                        ValueType3Int       type3Val;
//                        ValueType4FormFloat type4Val;
//                    };
//
//                    std::uint8_t  type;       // 10
//                    std::uint8_t  pad[7];     // 11
//                    std::uint32_t propertyID; // 18
//                    std::uint32_t pad2;       // 18
//                                        // std::uint64_t pad2;
//                                        // float         pad2;
//                                        // float Value1;
//                                        // float Value2;
//                };
//
//                static_assert(sizeof(Property) == 0x20);
//                static_assert(offsetof(Property, type) == 0x10);
//
//                BSTArray<Include>  includes;   // 00
//                BSTArray<Property> properties; // 10
//            };
//
//            static_assert(sizeof(Data) == 0x20);
//
//            ~Mod() override; // 00
//
//            // members
//            Data                 data;          // 80
//            BGSAttachParentArray attachParents; // A0
//            std::uint64_t        unkC0;         // C0 - std::vector<BGSKeyword*>?
//            std::uint64_t        unkC8;         // C8
//            std::uint64_t        unkD0;         // D0
//            BGSKeyword*          attachPoint;   // D8
//            BGSMorphableObject*  unkE0;         // E0
//            BGSMorphableObject*  unkE8;         // E8
//            BSFixedString        name;          // F0
//            std::uint8_t         unkF8;         // F8
//            std::uint8_t         unkF9;         // F9
//            std::uint8_t         priority;      // FA
//            std::uint8_t         unkFB;         // FB
//            std::uint8_t         unkFC;         // FC
//        };
//
//        static_assert(sizeof(Mod) == 0x100);
//    } // namespace Attachment
//
//    namespace Template
//    {
//        class Items : public BaseFormComponent
//        {
//        public:
//            SF_RTTI_VTABLE(BGSMod__Template__Items);
//
//            ~Items() override; // 00
//
//            // override (BaseFormComponent)
//            const BSFixedString& GetFormComponentType() const override; // 01 - { return "BGSMod_Template_Component"; }
//            void                 InitializeDataComponent() override;    // 02
//
//            // add
//            virtual void Unk_0B(); // 0B
//            virtual void Unk_0C(); // 0C
//            virtual void Unk_0D(); // 0D
//
//            // members
//            BSTArray<void*> unk08; // 08
//            BSFixedString   unk18; // 18
//        };
//
//        static_assert(sizeof(Items) == 0x20);
//    } // namespace Template
//} // namespace RE::BGSMod


//#pragma once
//
//#include "RE/A/AVMData.h"
//#include "RE/B/BGSAttachParentArray.h"
//#include "RE/B/BGSForcedLocRefType.h"
//#include "RE/B/BGSNativeTerminalForm.h"
//#include "RE/B/BGSOverridePackCollection.h"
//#include "RE/B/BSLock.h"
//#include "RE/B/BSTArray.h"
//#include "RE/B/BSTEvent.h"
//#include "RE/N/NiPoint3.h"
//#include "RE/S/Sexes.h"
//#include "RE/T/TESActorBase.h"
//#include "RE/T/TESRaceForm.h"
//
//namespace RE
//{
//    class BGSHeadPart;
//    class BGSListForm;
//    class BGSOutfit;
//    class BGSRelationship;
//    class MenuOpenCloseEvent;
//    class TESClass;
//    class TESCombatStyle;
//    class TESFaction;
//    class TESFurniture;
//
//    class TESNPC : public TESActorBase,                    // 000
//                   public TESRaceForm,                     // 260
//                   public BGSOverridePackCollection,       // 270
//                   public BGSForcedLocRefType,             // 2B8
//                   public BGSNativeTerminalForm,           // 2D0
//                   public BSTEventSink<MenuOpenCloseEvent> // 2E0
//    {
//    public:
//        SF_RTTI_VTABLE(TESNPC);
//        SF_FORMTYPE(NPC_);
//
//        enum class PRONOUN_TYPE
//        {
//            kUnselected,
//            kHeHim,
//            kSheHer,
//            kTheyThem
//        };
//
//        ~TESNPC() override; // 00
//
//        [[nodiscard]] TESRace* GetRace() const { return formRace; }
//
//        [[nodiscard]] SEX  GetSex() const;
//        [[nodiscard]] bool ContainsKeyword(std::string_view a_editorID);
//        [[nodiscard]] bool HasKeyword(std::string_view a_editorID);
//        [[nodiscard]] bool IsInFaction(TESFaction* a_faction) const;
//
//        struct MorphWeight
//        {
//            float thin;
//            float muscular;
//            float fat;
//        };
//
//        // members
//        BGSAttachParentArray                         attachParents;   // 2E8
//        std::uint32_t                                unk308;          // 308
//        std::uint32_t                                unk30C;          // 30C
//        TESClass*                                    npcClass;        // 310
//        std::uint64_t                                unk318;          // 318
//        BGSListForm*                                 giftFilter;      // 320
//        TESCombatStyle*                              combatStyle;     // 328
//        std::uint32_t                                fileOffset;      // 330
//        std::uint32_t                                unk334;          // 334
//        TESRace*                                     originalRace;    // 338
//        TESNPC*                                      faceNPC;         // 340
//        MorphWeight                                  morphWeight;     // 348
//        float                                        height;          // 354
//        float                                        heightMax;       // 358
//        std::uint32_t                                unk35C;          // 35C
//        TESNPC*                                      unk360;          // 360
//        std::uint64_t                                unk368;          // 368
//        std::uint64_t                                unk370;          // 370
//        BGSLocalizedString                           shortName;       // 378
//        TESObjectARMO*                               farSkin;         // 380
//        TESFurniture*                                powerArmorFurn;  // 388
//        BGSOutfit*                                   defaultOutfit;   // 390
//        BGSOutfit*                                   sleepOutfit;     // 398
//        BGSListForm*                                 defaultPackList; // 3A0
//        TESFaction*                                  crimeFaction;    // 3A8
//        TESFaction*                                  unk3B0;          // 3B0
//        BSTArray<BGSHeadPart*>                       headparts;       // 3B8
//        std::uint64_t                                pad;
//        BSTArray<float>*                             unk3D0;        // 3D0
//        std::uint64_t                                unk3D8;        // 3D8
//        std::uint64_t                                unk3E0;        // 3E0
//        BSTArray<AVMData>                            tintAVMData;   // 3E8
//        std::uint32_t                                skinToneIndex; // 3F8
//        std::uint32_t                                unk3FC;        // 3FC
//        BSFixedString                                teeth;         // 400
//        BSFixedString                                jewelryColor;  // 408
//        BSFixedString                                eyeColor;      // 410
//        BSFixedString                                hairColor;     // 418
//        BSFixedString                                facialColor;   // 420
//        BSFixedString                                eyebrowColor;  // 428
//        BSTArray<BGSRelationship*>*                  relationships; // 430
//        BGSLocalizedString                           organization;  // 438 - faction?
//        std::uint64_t                                unk440;        // 440
//        stl::enumeration<PRONOUN_TYPE, std::uint8_t> pronoun;       // 448
//    };
//
//    static_assert(sizeof(TESNPC) == 0x450);
//} // namespace RE


//#pragma once
//
//#include "RE/B/BSTArray.h"
//#include "RE/T/TESDescription.h"
//#include "RE/T/TESForm.h"
//#include "RE/T/TESFullName.h"
//
//namespace RE
//{
//    class BGSKeyword;
//
//    struct BGSPerkRank
//    {
//        std::uint64_t   pad0;    // 0
//        std::uint64_t   pad8;    // 8
//        std::uint64_t   pad10;   // 10 pointer to smth
//        BSTArray<void*> Effects; // 18
//        TESDescription  pad28;   // 28
//        std::uint64_t   pad40;   // 40
//        std::uint64_t   pad48;   // 48
//        std::uint64_t   pad50;   // 50
//        std::uint64_t   pad60;   // 60 WRONG
//    };
//
//    static_assert(sizeof(BGSPerkRank) == 0x60);
//
//    class BGSPerk : public TESForm,       // 00
//                    public TESFullName,   // 30
//                    public TESDescription // 40
//    {
//    public:
//        SF_RTTI_VTABLE(BGSPerk);
//        SF_FORMTYPE(PERK);
//
//        ~BGSPerk() override; // 00
//
//        enum class Flag
//        {
//            kNone         = 0,
//            kPCTrait      = 1 << 0,
//            kPlayable     = 1 << 1,
//            kShowInCrewUI = 1 << 3,
//            kPCBackground = 1 << 4,
//        };
//
//        // members
//        std::uint16_t                        unk58;        // 58
//        std::uint8_t                         unk5A;        // 5A
//        stl::enumeration<Flag, std::uint8_t> flags;        // 5B
//        std::uint8_t                         unk5C;        // 5C
//        BGSPerk*                             trainingPerk; // 60
//        BSFixedStringCS                      unk68;        // 68
//        BSFixedString                        perkIcon;     // 70 - GNAM
//        BGSKeyword*                          restriction;  // 78
//        std::uint64_t                        unk80;        // 80 // perk rank
//        std::uint64_t                        unk88;        // 88 // perk rank last p
//        std::uint64_t                        unk90;        // 90 // perk rank last p 2
//    };
//
//    static_assert(sizeof(BGSPerk) == 0x98);
//} // namespace RE



//Starfiled V10 update


//// members
//BGSAttachParentArray                         attachParents; // 2F0
//std::uint8_t                                 pad[0x38];
//MorphWeight                                  morphWeight;     // confirmed.
//float                                        height;          // confirmed.
//float                                        heightMax;       // confirmed.
//std::uint32_t                                unk35C;          // 35C
//TESNPC*                                      unk360;          // 360
//std::uint64_t                                unk368;          // 368
//std::uint64_t                                unk370;          // 370
//BGSLocalizedString                           shortName;       // 378
//TESObjectARMO*                               farSkin;         // 380
//TESFurniture*                                powerArmorFurn;  // 388
//BGSOutfit*                                   defaultOutfit;   // 390
//BGSOutfit*                                   sleepOutfit;     // 398 // confirmed. That' not sleep outfit - that's space outdit lol
//BGSListForm*                                 defaultPackList; // 3A0
//TESFaction*                                  crimeFaction;    // 3A8 // confirmed.
//TESFaction*                                  unk3B0;          // 3B0
//BSTArray<BGSHeadPart*>                       headparts;       // 3B8 // confirmed.
//std::uint64_t                                pad2;            // LOCK
//BSTArray<float>*                             unk3D0;          // 3D0
//std::uint64_t                                unk3D8;          // 3D8
//std::uint64_t                                unk3E0;          // 3E0
//BSTArray<AVMData>                            tintAVMData;     // 3E8
//std::uint32_t                                skinToneIndex;   // 3F8
//std::uint32_t                                unk3FC;          // 3FC
//BSFixedString                                teeth;           // 400
//BSFixedString                                jewelryColor;    // 408
//BSFixedString                                eyeColor;        // 410
//BSFixedString                                hairColor;       // 418
//BSFixedString                                facialColor;     // 420
//BSFixedString                                eyebrowColor;    // 428
//BSTArray<BGSRelationship*>*                  relationships;   // 430
//BGSLocalizedString                           organization;    // 438 - faction?
//std::uint64_t                                unk440;          // 440
//stl::enumeration<PRONOUN_TYPE, std::uint8_t> pronoun;         // 448


//// members
//
//ACTOR_BASE_DATA        actorData;   // 08
//std::int32_t           changeFlags; // 1C
//BSTArray<FACTION_RANK> factions;    // 20 // confirmed
//std::uint64_t          pad;
//TESForm**              templateForms;    // 30
//TESForm**              unk38;            // 38
//TESForm*               baseTemplateForm; // 40 //confirmed
//TESLevItem*            deathItem;        // 48
//TESGlobal*             legendChance;     // 50
//TESForm*               legendTemplate;   // 58
//BGSVoiceType*          voiceType;        // 60
//std::uint32_t          unk68;            // 68
//std::uint32_t          unk6C;            // 6C
