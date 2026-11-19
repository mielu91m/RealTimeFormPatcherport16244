#pragma once


//<Requires Editor ID> file mofidier
//Conditions to end the line early.
//Look into GS Strings CTD
//Script - properties
//Properties for other forms.
//Description!!!!!!!!!!!!!!!!!!!
//Cell records.
//Terminal menu entries TNAM-SUBMENU
//Aim model - edit values.
//Add properties support to OMOD
//Flora
//Weapon sound level and firing type
//More filters byworkbench keyword.
// Planet records.
// Bone modifier
//
// Object templates
//Add / remove / replace includes, combinations,
//    and properties
//
//        Set the min and max levels
//
//            I'm trying to change the uniques so they have unique stats and edit the rest of the templates so weapons drop with mods that I make 

//Location - name


//EffectSetting - Magic Effect




//if constexpr (std::is_same<FormType, RE::TESObjectARMO*>::value)
//if constexpr (std::is_same<T, Input::TempModifierAlt::Value>::value) {
//    ArrayNonForm::AddRemove(CurrentForm->listOfEffects, CurrentModifierValue.CurrentModifierValue, EffectItem::RemoveFromArray, EffectItem::GetFromString);
//}
//else {
//    ArrayNonForm::AddRemove(CurrentForm->listOfEffects, CurrentModifierValue, EffectItem::RemoveFromArray, EffectItem::GetFromString);
//}


#define TUPLE3 RE::BSTTuple3<RE::TESForm*, RE::BGSCurveForm*, RE::BGSTypedFormValuePair::SharedVal>
#define PROPERTY RE::BSTTuple3<RE::TESForm*, RE::TESForm*, RE::BGSTypedFormValuePair::SharedVal>



class TommPlanetContentManagerContentNode : public RE::TESForm // 00
{
public:
};

class TommPlanetContentManagerBranchNode : public RE::TESForm // 00
{
public:
    std::uint8_t                                       pad38[0x30];
    RE::BSTArray<TommPlanetContentManagerContentNode*> nodes;
};

static_assert(offsetof(TommPlanetContentManagerBranchNode, pad38) == 0x38);
static_assert(offsetof(TommPlanetContentManagerBranchNode, nodes) == 0x68);



namespace Ext
{
    const std::uint8_t InterfaceVer = 1;

    enum RTFPErrors
    {
        kSuccess             = 1,
        kRTFPNotInitalized   = -1, //Initialization happens on SFSEPluginLoad. If you want to add files before OnDefferedInit you should add it on kPostPostDataLoad
        kFileNotLoaded       = -2, //Returns if file is not loaded(it might be in the folder but for instance, it it requires a higher version of RTFP it will not be loaded)
        kStringLengthZero    = -3, //Returns if you passed an empty string instead of lines to run.
        kCurrentlyUnavaiable = -4, // During GameReset.
        kFileNotValid        = -5           // File is rejected during processing modifiers(if they are present).
    };


    enum RTFPFlags
    {
        kExecuteImmediately = 1 << 0,
    };


} // namespace Ext

namespace StoredEntries {


    struct Entry
    {
        RE::TESForm* formIn     = NULL;
        uintptr_t    firstEntry = NULL;
        uintptr_t    lastEntry  = NULL;
        uintptr_t    lastEntry2 = NULL;

        uintptr_t NewFirstEntryAddress = NULL;
    };


    std::vector<Entry> v_Stored{};

    Entry* GetEntryFromArray(std::uint32_t formID)
    {
        for (auto it = v_Stored.begin(); it != v_Stored.end(); it++) {
            if (Iter.formIn->formID == formID)
            {
                return &Iter;
            }
        }
        return NULL;
    }



}



class TESQuestTomm : public RE::TESForm
{
public:
};

class BGSStoryManagerQuestNode : public RE::TESForm // there are other classes in it
{
public:

    struct QuestEntry
    {
        TESQuestTomm* quest;
        float         HoursUntilReset;
        std::uint64_t unk;
    };
    static_assert(sizeof(QuestEntry) == 0x18);

    std::uint8_t         pad38[0x18]; // 38
    BGSStoryManagerQuestNode* prevSibl;
    std::uint8_t         pad58[0x8];
    std::uint32_t        maxConcurringQuests; // 60
    std::uint16_t        nodeFlags;
    std::uint16_t        questFlags;
    RE::BSTArray<QuestEntry>  Quests;
    float                hoursUntillreset; // 78
    std::uint32_t        numQuestsToRun;   // 7C
};

static_assert(offsetof(BGSStoryManagerQuestNode, pad38) == 0x38);
static_assert(offsetof(BGSStoryManagerQuestNode, maxConcurringQuests) == 0x60);
static_assert(offsetof(BGSStoryManagerQuestNode, hoursUntillreset) == 0x78);
static_assert(offsetof(BGSStoryManagerQuestNode, numQuestsToRun) == 0x7C);
static_assert(offsetof(BGSStoryManagerQuestNode, prevSibl) == 0x50);


class BGSAVMData : public RE::TESForm // 141337B60 in 1-9-6-7
{
public:

    enum class TYPE
    {
        kNone,
        kSimpleGroup,
        kComplexGroup,
        kModulation
    };

    RE::BGSEditorID     formEditorID; // 38
    std::uint32_t       type;         // 48
    std::uint32_t       pad;          // 4C
    RE::BSFixedString   category;     // 50
    RE::BSFixedString   category2;    // 58 Same as first category?
    RE::AVMData::Entry* firstEntry;   // 60 // Pointer to first entry
    RE::AVMData::Entry* lastEntry;    // 68 // Pointe to last entry
    RE::AVMData::Entry* lastEntry2;   // 70 Same as pointer previous one.
};
static_assert(offsetof(BGSAVMData, firstEntry) == 0x60);
static_assert(sizeof(BGSAVMData) == 0x78);



class BGSAVMDataAlt : public RE::TESForm // 00
{
public:
    enum class TYPE
    {
        kNone,
        kSimpleGroup,
        kComplexGroup,
        kModulation
    };

    RE::BGSEditorID     formEditorID; // 38
    std::uint32_t       type;         // 48
    std::uint32_t       pad;          // 4C
    RE::BSFixedString   category;     // 50
    RE::BSFixedString   category2;    // 58 Same as first category?
    std::vector<RE::AVMData::Entry> Entries;
};
static_assert(sizeof(BGSAVMDataAlt) == 0x78);



//template <typename Assertion>
//struct AssertValue : AssertionChecker<Assertion::value, Assertion>
//{
//    static_assert(AssertionValue, "Assertion failed <see below for more information>");
//    static const bool value = Assertion::value;
//};


//
//        if (typeid(T) == typeid(int))
//static_assert(false, "Hey user! You suck!");  if (typeid(CurrentValue) == typeid(float)) {
// /

// Constructible object
//Filter by values with >> <<
// Add activators and some values to them?
// Edit item values - weapon, armor,misc item, spell duration, base effect duration.

//Weapon flags


#include "Defines.h"

template<class T, class M>
bool IsFlagSet(T&Flags, M Bit)
{
    return Flags & Bit;
}


void __forceinline FillCharFromModifierString(std::string_view sFrom, char* in)
{
    strncpy(in, sFrom.data(), sFrom.length());
    in[sFrom.length()] = '\0';
}

void __forceinline FillCharFromModifierStringExceptFirstAndLastSymbol(std::string_view sFrom, char* in)
{
    strncpy(in, sFrom.data() + 1, sFrom.length() -1);
    in[sFrom.length() - 2] = '\0';
}



namespace LoadedPlugins
{
    enum PluginType
    {
        k_None  = 0,
        k_Full    = 1,
        k_Medium = 2,
        k_Small = 3,
    };

    std::string GetPluginTypeByID(int iType)
    {
        switch (iType) {
        case PluginType::k_Full:
            return "Full";
            break;
        case PluginType::k_Medium:
            return "Medium";
            break;
        case PluginType::k_Small:
            return "Small";
            break;
        default:
            return "UNKNOWN";
        }
    }

    struct Plugin
    {
        char         Name[261];
        std::uint8_t Index;
        int          type = PluginType::k_None;

        bool IsFormInPlugin(std::uint32_t formID)
        {
            _DMESSAGE("checking if form is in {} plugin", GetPluginTypeByID(type));
            if (type == PluginType::k_Full && (formID >> 24) == Index)
            {
                return true;
            }
            else if (type == PluginType::k_Medium && ((formID >> 24) == 0xFD && ((formID & 0x00FFF000) >> 24) == Index)) {
                return true;
            }
            else if (type == PluginType::k_Small && ((formID >> 24) == 0xFE && ((formID & 0x00FFF000) >> 12) == Index)) {
                return true;
            }

            return false;
        }

    };

    std::vector<Plugin> vLoadedMods;



    Plugin* GetModInfo(std::string_view sModName)
    {
        for (auto it = vLoadedMods.begin(); it != vLoadedMods.end(); it++) {
            if (sModName == Iter.Name) {
                return &Iter;
            }
        }

        return NULL;
    }


    template <int iPluginType, class T>
    void GetPluginsFromArray(T& Array)
    {
        int iModIndex = 0;

        for (auto it = Array.begin(); it != Array.end(); it++) {

            if constexpr (iPluginType == PluginType::k_Full) {
                _DMESSAGE("Full master>>{:08X},Name>>{},ModIndex>>{}", (uintptr_t)std::addressof(Iter), (**it).fileName, iModIndex);
            }
            else if constexpr (iPluginType == PluginType::k_Medium) {
                _DMESSAGE("Medium master>>{:08X},Name>>{},ModIndex>>{}", (uintptr_t)std::addressof(Iter), (**it).fileName, iModIndex);
            }
            else if constexpr (iPluginType == PluginType::k_Small) {
                _DMESSAGE("Small master>>{:08X},Name>>{},ModIndex>>{}", (uintptr_t)std::addressof(Iter), (**it).fileName, iModIndex);
            }


            Plugin NewPlugin{};
            NewPlugin.Index = iModIndex;

            size_t iSize = sizeof((**it).fileName);
            strncpy(NewPlugin.Name, (**it).fileName, iSize);
            NewPlugin.Name[iSize] = '\0';
            NewPlugin.type        = iPluginType;

            vLoadedMods.push_back(NewPlugin);

            iModIndex++;
        }

    }





    void Get()
    {
        vLoadedMods.clear();
        auto gHandler = RE::TESDataHandler::GetSingleton();

        std::uint8_t iModIndex = 0;

        _DMESSAGE("Reserving space for plugins.");
        vLoadedMods.reserve(gHandler->compiledFileCollection.files.size() + gHandler->compiledFileCollection.smallFiles.size() + gHandler->compiledFileCollection.mediumFiles.size());
        _DMESSAGE("Reserved>>{}", vLoadedMods.size());

        _DMESSAGE("TESDataHandler>>{:08X}", (uintptr_t)gHandler);
        _DMESSAGE("FileCollectionAddress>>{:08X}", (uintptr_t)&gHandler->compiledFileCollection);
        _DMESSAGE("Loaded files count>>{}", gHandler->compiledFileCollection.files.size());

        // for (size_t i = 0; i < iSize - 1; i++)
        //    NewPlugin.Name[i] = tolower(NewPlugin.Name[i]);


        GetPluginsFromArray<PluginType::k_Full>(gHandler->compiledFileCollection.files);
        GetPluginsFromArray<PluginType::k_Medium>(gHandler->compiledFileCollection.mediumFiles);
        GetPluginsFromArray<PluginType::k_Small>(gHandler->compiledFileCollection.smallFiles);


        //for (auto it = gHandler->compiledFileCollection.files.begin(); it != gHandler->compiledFileCollection.files.end(); it++) {

        //    _DMESSAGE("FILE>>{:08X},Name>>{},ModIndex>>{}", (uintptr_t)std::addressof(Iter), (**it).fileName, iModIndex);
        //    Plugin NewPlugin{};
        //    NewPlugin.Index = iModIndex;

        //    size_t iSize = sizeof((**it).fileName);
        //    strncpy(NewPlugin.Name, (**it).fileName,iSize);
        //    NewPlugin.Name[iSize] = '\0';
        //    NewPlugin.type        = PluginType::k_Big;

        //    vLoadedMods.push_back(NewPlugin);

        //    iModIndex++;
        //}


        //for (auto it = gHandler->compiledFileCollection.smallFiles.begin(); it != gHandler->compiledFileCollection.smallFiles.end(); it++) {
        //    DConsole_Print("Light plugin>>>%s", (**it).fileName);
        //    _DMESSAGE("Light plugin>>>{},address>>{:08X}", (**it).fileName, (uintptr_t)std::addressof(Iter));
        //}

        //for (auto it = gHandler->compiledFileCollection.mediumFiles.begin(); it != gHandler->compiledFileCollection.mediumFiles.end(); it++) {
        //    DConsole_Print("Medium plugin>>>%s", (**it).fileName);
        //    _DMESSAGE("Medium  plugin>>>{},address>>{:08X}", (**it).fileName, (uintptr_t)std::addressof(Iter));
        //}

        if (bDebugMode) {
            for (auto it = vLoadedMods.begin(); it != vLoadedMods.end(); it++)
            {
                _MESSAGE("Mod Name>>{},Type>>{},ModIndex>>{}", Iter.Name, GetPluginTypeByID(Iter.type), Iter.Index);
                DConsole_Print("Mod Name>>%s,Type>>%s,ModIndex>>%d", Iter.Name, GetPluginTypeByID(Iter.type), Iter.Index);
            }
        }

    }




}

inline constexpr auto hash_djb2a(const std::string_view sv)
{
    unsigned long hash{ 5381 };
    for (unsigned char c : sv) {
        hash = ((hash << 5) + hash) ^ c;
    }
    return hash;
}

inline constexpr auto operator"" _sh(const char* str, size_t len)
{
    return hash_djb2a(std::string_view{ str, len });
}



template <class T,class _ValueToSet>
void _forceinline CheckAndSetValue(_ValueToSet& valToSet, T& ValueSource)
{


    if constexpr (typeid(_ValueToSet) == typeid(float)) {

        if (ValueSource.data > FLT_MAX) {
            ValueSource.data = FLT_MAX;
        }
        else if (ValueSource.data < -FLT_MAX) {
            ValueSource.data = -FLT_MAX;
        }
    }
    else if constexpr (typeid(_ValueToSet) == typeid(std::uint32_t)) {

        if (ValueSource.data > UINT32_MAX) {
            ValueSource.data = UINT32_MAX;
        }
        else if (ValueSource.data < 0) {
            ValueSource.data = 0;
            return;
        }
    }
    else if constexpr (typeid(_ValueToSet) == typeid(std::int32_t)) {

        if (ValueSource.data > INT_MAX) {
            ValueSource.data = INT_MAX;
        }
        else if (ValueSource.data < INT_MIN) {
            ValueSource.data = INT_MIN;
        }
    }
    else if constexpr (typeid(_ValueToSet) == typeid(std::int16_t)) {

        if (ValueSource.data > INT16_MAX) {
            ValueSource.data = INT16_MAX;
        }
        else if (ValueSource.data < INT16_MIN) {
            ValueSource.data = INT16_MIN;
        }
    }
    else if constexpr (typeid(_ValueToSet) == typeid(std::uint16_t)) {

        if (ValueSource.data > UINT16_MAX) {
            ValueSource.data = UINT16_MAX;
        }
        else if (ValueSource.data < 0) {
            ValueSource.data = 0;
        }
      
    }
    else if constexpr  (typeid(_ValueToSet) == typeid(std::int8_t)) {

        if (ValueSource.data > INT8_MAX) {
            ValueSource.data = INT8_MAX;
        }
        else if (ValueSource.data < INT8_MIN) {
            ValueSource.data = INT8_MIN;
        }
    }
    else if constexpr (typeid(_ValueToSet) == typeid(std::uint8_t)) {

        if (ValueSource.data > UINT8_MAX) {
            ValueSource.data = UINT8_MAX;
        }
        else if (ValueSource.data < 0) {
            ValueSource.data = 0;
        }
        
    }




    valToSet = ValueSource.data;
    //_DMESSAGE("VALUE SET AFTER>>{}", valToSet);
}




template <typename ValueType>
struct NumberFromString {
    bool   bSuccess = true;
    ValueType data     = 0;



    template <class _ValueToSet>
    void CheckAndSetInBoundsFor(_ValueToSet& valToSet) // Not used
    // Brings double(second param) to bounds of first param.
    {
        if constexpr (typeid(_ValueToSet) == typeid(float)) {
            _DMESSAGE("type is float>>{}, Double>>>{}", valToSet, data);
            if (data > FLT_MAX) {
                data = FLT_MAX;
                _DMESSAGE("Setting float to MAX");
            }
            else if (data < -FLT_MAX) {
                data = -FLT_MAX;
                _DMESSAGE("Setting float to MIN");
            }
        }
        else if constexpr (typeid(_ValueToSet) == typeid(std::uint32_t)) {
            if (data > UINT32_MAX) {
                data = UINT32_MAX;
            }
            else if (data < 0) {
                data = 0;
                return;
            }
        }
        else if constexpr (typeid(_ValueToSet) == typeid(std::int32_t)) {
            if (data > INT_MAX) {
                data = INT_MAX;
            }
            else if (data < INT_MIN) {
                data = INT_MIN;
            }
        }
        else if constexpr (typeid(_ValueToSet) == typeid(std::int16_t)) {
            if (data > INT16_MAX) {
                data = INT16_MAX;
            }
            else if (data < INT16_MIN) {
                data = INT16_MIN;
            }
        }
        else if constexpr (typeid(_ValueToSet) == typeid(std::uint16_t)) {
            if (data > UINT16_MAX) {
                data = UINT16_MAX;
            }
            else if (data < 0) {
                data = 0;
            }
        }
        else if constexpr (typeid(_ValueToSet) == typeid(std::int8_t)) {
            if (data > INT8_MAX) {
                data = INT8_MAX;
            }
            else if (data < INT8_MIN) {
                data = INT8_MIN;
            }
        }
        else if constexpr (typeid(_ValueToSet) == typeid(std::uint8_t)) {
            if (data > UINT8_MAX) {
                data = UINT8_MAX;
            }
            else if (data < 0) {
                data = 0;
            }
        }
        else {
            throw "Add types to CheckAndSetSelf function";
        }
    }


};

template <typename ValueType>
NumberFromString<ValueType> GetNumberFromString(std::string_view in)
{
    NumberFromString<ValueType> result;
    auto [ptr, err] = std::from_chars(in.data(), in.data() + in.size(), result.data);

    if (err == std::errc{} && ptr == in.data() + in.size()) {
        return result;
    }
    else {
        _DMESSAGE("Converstion NOT successful>>{}, error>> {}", in, (int)err);
        result.bSuccess = false;
        return result;
    }
}


template <class Value>
NumberFromString<Value> GetNumberFromString(Value value,std::string_view in)
{
    NumberFromString<Value> result;
    auto [ptr, err] = std::from_chars(in.data(), in.data() + in.size(), result.data);

    if (err == std::errc{} && ptr == in.data() + in.size()) {
        return result;
    }
    else {
        _DMESSAGE("Converstion NOT successful>>{}, error>> {}", in, (int)err);
        result.bSuccess = false;
        return result;
    }
}




uint32_t GetDECFromHEX(std::string_view s_FormIDs)
{

    uint32_t result;
    auto [ptr, err] = std::from_chars(s_FormIDs.data(), s_FormIDs.data() + s_FormIDs.size(), result, 16);

    if (err == std::errc{} && ptr == s_FormIDs.data() + s_FormIDs.size()) {
        //DConsole_Print("Converstion successful>>%x", result);
        return result;
    }
    else {
        _DMESSAGE("Converstion FormID NOT successful>>{} {}", s_FormIDs, (int)err);
        return 0;
    }
}



template <bool bSet,class T, class Fl>
void _forceinline SetOrRemoveFlagAlt(T& Flags, Fl RequestedFlag)
{
    if constexpr(bSet) {
        Flags |= RequestedFlag;
    }
    else {
        Flags &= ~RequestedFlag;
    }
}


#include <spdlog/fmt/fmt.h>
namespace Input
{
    template <class T>
    void ProcessModifiersForLeveledList(T* CurrentForm, std::string_view& ModifierSection);
    std::vector<RE::TESForm*> GetAllLoadedTypeFormsFromLineAndProcessFilters(int& iCurrentSection, std::string_view FormIDValue);

    std::vector<RE::TESForm*> GetMultipleFormsFromLine(int& iCurrentSection, std::string_view FormIDValue);

    struct File
    {

        struct Modifier {
            ~Modifier()
            {
                if (type == FileModifierType::k_RequiresPluginLoaded) {
                    delete (RequiresPluginLoadedMod*)value;
                }
                else if (type == FileModifierType::k_RequiresPluginNotLoaded) {
                    delete (RequiresPluginNotLoadedMod*)value;
                }
            };

            enum FileModifierType
            {
                k_None = 0,
                k_RequiresPluginLoaded = 1,
                k_RequiresPluginNotLoaded = 1,
            };

            struct RequiresPluginLoadedMod
            {
                std::string RequiresPluginLoaded{};
                bool        bWarning = false;
            };

            struct RequiresPluginNotLoadedMod
            {
                std::string RequiresPluginLoaded{};
                bool        bWarning = false;
            };


            int type = FileModifierType::k_None;
            void* value= NULL;
        };


        bool CheckForModifiersShouldContinue() {

            //if (!modifiers.size()) {
            //    return true;
            //}

            //for (auto& modifier : modifiers) {

            //    if (modifier.type == Modifier::FileModifierType::k_RequiresPluginLoaded) {

            //    }
            //    else if (modifier.type == Modifier::FileModifierType::k_RequiresPluginNotLoaded) {

            //    }

            //}

        }


        std::uint32_t     ID = 0;
        std::string name{};
        std::string content{};
        std::int32_t      Priority       = 0;
        std::uint32_t TimesProcessed = 0;
        //std::vector<Modifier> modifiers{}; 

        std::string RequiresPluginLoaded{};
        bool              RequiresPluginLoadedWarning = false;
        bool              firstLineRemoved = false;

    };

    File* currentFile = NULL;
    std::uint32_t currentLine = 0;








    //auto s = std::format("Hi {}", 1);

    //template <class... Args>
    //void PrintRTFPError(Args... args)
    //{
    //    auto s = std::format(std::forward<Args>(args)...);
    //    //_DMESSAGE(s);
    //}

    //template <typename... Args>
    //std::string my_print(spdlog::fmt_lib::fmt::format_string<Args...> s, Args&&... args)
    //{
    //    return spdlog::fmt_lib::format(s, std::forward<Args>(args)...);
    //}




    std::vector<File> files{};

    enum Calculation
    {
        k_CalcNone = 0,
        k_Add,
        k_Sub,
        k_Mult,
        k_Div
    };

    union CachedValue
    {
        RE::TESForm* Form = NULL;
        double       dNumber;
    };

    struct TempModifierAlt
    {
        enum Flags
        {
            kValid    = 1 << 0,
            kNeedsToBeValid    = 1 << 1,
            kCalcSet = 1 << 2,
            kCalcAdd  = 1 << 3,
            kCalcSub  = 1 << 4,
            kCalcDiv  = 1 << 5,
            kCalcMult = 1 << 6
        };

        

        struct Value
        {
            std::string_view CurrentModifierValue{};
            CachedValue  cached;
            std::uint8_t flags;


            operator std::string_view &()
            {
                return CurrentModifierValue;
            }
            //friend std::ostream& operator<<(std::ostream& os, const MyString& rhs) { return os << rhs.str; }




        };

        unsigned long CurrentModifierName = 0;
        Value         value{};
    };

    #define _DRTFPError(...)                                                                                                                                                           \
    if (bDebugMode) {                                                                                                                                                              \
        std::string sErrorString = std::format(__VA_ARGS__);                                                                                                                       \
        Errors::PrintConsoleError(sErrorString);                                                                                                                                           \
        logger::info("{}", sErrorString);                                                                                                                                          \
    }

    #define _DRTFPFormBuiltError(...)                                                                                                                                                           \
    if (bShowWarningsIfFormNotBuilt) {                                                                                                                                                              \
        std::string sErrorString = std::format(__VA_ARGS__);                                                                                                                       \
        Errors::PrintConsoleError(sErrorString);                                                                                                                                   \
        if (bDebugMode){logger::info("{}", sErrorString);}                                                                                                                                          \
    }



    namespace Errors
    {

        void PrintConsoleError(std::string& err)
        {
            if (err.length() > 3000)
            {
                if (currentFile) {
                    DConsole_Print("ERROR in file %s, line %d - %s", currentFile->name.c_str(), currentLine, err.substr(0,3000).c_str());
                }
                else {
                    DConsole_Print("ERROR - %s", err.substr(0, 3000).c_str());
                }
            }
            else {
                if (currentFile) {
                    DConsole_Print("ERROR in file %s, line %d - %s", currentFile->name.c_str(), currentLine, err.c_str());
                }
                else {
                    DConsole_Print("ERROR - %s", err.c_str());
                }
            }
        }

        void PrintFormError(std::string& err)
        {
            if (currentFile) {
                DConsole_Print("ERROR in file %s, line %d - %s", currentFile->name.c_str(), currentLine, err.c_str());
            }
            else {
                DConsole_Print("ERROR - %s", err.c_str());
            }
        }

                                                                                                                   
    }







    template <bool bSet,class T, typename F>
    void ProcessFlagModifierAlt(T& Flags, std::string_view CurrentModifierValue, F func)
    {

        size_t CurrentPos     = 0;
        size_t NewModifierPos = 0;

        _DMESSAGE("ProcessFlagModifier starts");

        while (NewModifierPos != NONPOS) {
            NewModifierPos = CurrentModifierValue.find(sArrDelimeter, CurrentPos);
            _DMESSAGE("Flag>>{},Set>>{}", CurrentModifierValue.substr(CurrentPos, NewModifierPos - CurrentPos), bSet);
            func(Flags, hash_djb2a(CurrentModifierValue.substr(CurrentPos, NewModifierPos - CurrentPos)));
            CurrentPos = NewModifierPos + 1;
        }
    }




    enum Sections
    {
        k_None,
        k_Weapons              = RE::FormType::kWEAP,
        k_Armors               = RE::FormType::kARMO,
        k_Ammo                 = RE::FormType::kAMMO,
        k_NPC                  = RE::FormType::kNPC_,
        k_FormList             = RE::FormType::kFLST,
        k_Global               = RE::FormType::kGLOB,
        k_Projectile           = RE::FormType::kPROJ,
        k_Misc                 = RE::FormType::kMISC,
        k_Constructible        = RE::FormType::kCOBJ,
        k_Perk                 = RE::FormType::kPERK,
        k_Spell                = RE::FormType::kSPEL,
        k_Activator            = RE::FormType::kACTI,
        k_LeveledList_BaseForm = RE::FormType::kLVLB,
        k_LeveledList_NPC      = RE::FormType::kLVLN,
        k_LeveledList_Item     = RE::FormType::kLVLI,
        k_LeveledList_PackIn   = RE::FormType::kLVLP,
        k_Keyword              = RE::FormType::kKYWD,
        k_AVMData              = RE::FormType::kAVMD,
        k_Static               = RE::FormType::kSTAT,
        k_CELL                 = RE::FormType::kCELL,
        k_Book                 = RE::FormType::kBOOK,
        k_Location                                                                    = RE::FormType::kLCTN,
        k_MagicEffect                                                               = RE::FormType::kMGEF,
        k_Race                                                                    = RE::FormType::kRACE,
        k_Ingestible                                    = RE::FormType::kALCH,
        k_ConditionForm                 = RE::FormType::kCNDF,
        k_VoiceType            = RE::FormType::kVTYP,
        k_Message                     = RE::FormType::kMESG,
        k_Outfit                                       = RE::FormType::kOTFT,
        k_StoryManagerQuestNode                    = RE::FormType::kSMQN,
        k_Container                         = RE::FormType::kCONT,
        k_PlanetContentManagerBranchNode                                          = RE::FormType::kPCBN,
        k_ObjectModification                                          = RE::FormType::kOMOD,
        k_Terminal                                                                = RE::FormType::kTERM,
        k_Reference                                          = RE::FormType::kREFR,
        kLoadScreen                                                               = RE::FormType::kLSCR,

        k_Condition        = 254,
        k_Debug                         = 255,
        k_Filters      = 299,
        k_Gamesettings = 300

    };



    //template <class T, typename F>
    //auto consteval const_GetFlagFromFlagName(T FlagName, F Func)
    //{
    //    return Func(FlagName);
    //}


    template <typename T>
    consteval std::uint8_t const_GetTypeFromFormType()
    {
        int iResult = Sections::k_None;
        if constexpr (std::is_same<T, RE::BGSKeyword*>::value) {
            iResult = Input::Sections::k_Keyword;
        }
        else if constexpr (std::is_same<T, RE::TESGlobal*>::value)
        {
            iResult = Input::Sections::k_Global;
        }
        else if constexpr (std::is_same<T, RE::BGSPerk*>::value) {
            iResult = Input::Sections::k_Perk;
        }
        else if constexpr (std::is_same<T, RE::BGSProjectile*>::value) {
            iResult = Input::Sections::k_Projectile;
        }
        else if constexpr (std::is_same<T, RE::TESAmmo*>::value) {
            iResult = Input::Sections::k_Ammo;
        }
        else if constexpr (std::is_same<T, RE::TESAmmo*>::value) {
            iResult = Input::Sections::k_Ammo;
        }
        else if constexpr (std::is_same<T, RE::BGSOutfit*>::value) {
            iResult = (std::uint8_t)RE::FormType::kOTFT;
        }
        else if constexpr (std::is_same<T, RE::TESFaction*>::value) {
            iResult = (std::uint8_t)RE::FormType::kFACT;
        }
        else if constexpr (std::is_same<T, RE::TESWaterForm*>::value) {
            iResult = (std::uint8_t)RE::FormType::kWATR;
        }
        else if constexpr (std::is_same<T, RE::TESLevItem*>::value) {
            iResult = (std::uint8_t)RE::FormType::kLVLI;
        }
        else if constexpr (std::is_same<T, BGSStoryManagerQuestNode*>::value) {
            iResult = (std::uint8_t)RE::FormType::kSMQN;
        }
        else if constexpr (std::is_same<T, RE::TESQuest*>::value) {
            iResult = (std::uint8_t)RE::FormType::kQUST;
        }
        else if constexpr (std::is_same<T, RE::SpellItem*>::value) {
            iResult = (std::uint8_t)RE::FormType::kSPEL;
        }
        else if constexpr (std::is_same<T, RE::TESRace*>::value) {
            iResult = (std::uint8_t)RE::FormType::kRACE;
        }
        else if constexpr (std::is_same<T, TommPlanetContentManagerBranchNode*>::value) {
            iResult = (std::uint8_t)RE::FormType::kPCBN;
        }
        else if constexpr (std::is_same<T, TommPlanetContentManagerContentNode*>::value) {
            iResult = (std::uint8_t)RE::FormType::kPCCN;
        }
        else if constexpr (std::is_same<T, RE::BGSHeadPart*>::value) {
            iResult = (std::uint8_t)RE::FormType::kHDPT;
        }
        else if constexpr (std::is_same<T, RE::TESObjectREFR*>::value) {
            iResult = (std::uint8_t)RE::FormType::kREFR;
        }
        else if constexpr (std::is_same<T, RE::TESObjectCELL*>::value) {
            iResult = (std::uint8_t)RE::FormType::kCELL;
        }
        else if constexpr (std::is_same<T, RE::BGSMod::Attachment::Mod*>::value) {
            iResult = (std::uint8_t)RE::FormType::kOMOD;
        }
        else if constexpr (std::is_same<T, RE::BGSTerminal*>::value) {
            iResult = (std::uint8_t)RE::FormType::kTERM;
        }
        else if constexpr (std::is_same<T, RE::BGSTerminalMenu*>::value) {
            iResult = (std::uint8_t)RE::FormType::kTMLM;
        }
        else if constexpr (std::is_same<T, RE::BGSListForm*>::value) {
            iResult = (std::uint8_t)RE::FormType::kFLST;
        }
        else if constexpr (std::is_same<T, RE::TESLoadScreen*>::value) {
            iResult = (std::uint8_t)RE::FormType::kLSCR;
        }
        else if constexpr (std::is_same<T, RE::BGSConditionForm*>::value) {
            iResult = (std::uint8_t)RE::FormType::kCNDF;
        }
        else if constexpr (std::is_same<T, RE::TESObjectWEAP*>::value) {
            iResult = (std::uint8_t)RE::FormType::kWEAP;
        }
        else if constexpr (std::is_same<T, RE::EffectSetting*>::value) {
            iResult = (std::uint8_t)RE::FormType::MGEF;
        }
        else if constexpr (std::is_same<T, RE::BGSLocation*>::value) {
            iResult = (std::uint8_t)RE::FormType::kLCTN;
        }
        else {
            throw "Add types to GetTypeFromFormType function";
        }

        //static_assert(iResult != Sections::k_None);

        return iResult;
    }

    

    struct Section
    {
        enum Flags
        {
            k_None = 0,
            k_SupportsKeywords = 1 << 0,
            k_SupportsValue    = 1 << 1,
            k_SupportsWeight   = 1 << 2,
        };

        const unsigned long SectionName       = 0;
        const int            SectionID         = 0;
        const int           iFlags = 0;
        static int GetFlags(int& iCurrentSection);

    };

    constexpr std::array<Section, 39> v_Sections = {
        Section{ "Weapon"_sh, Sections::k_Weapons, Section::Flags::k_SupportsKeywords | Section::Flags::k_SupportsWeight | Section::Flags::k_SupportsValue },
        Section{ "Armor"_sh, Sections::k_Armors, Section::Flags::k_SupportsKeywords | Section::Flags::k_SupportsWeight | Section::Flags::k_SupportsValue },
        Section{ "Book"_sh, Sections::k_Book, Section::Flags::k_SupportsKeywords | Section::Flags::k_SupportsWeight | Section::Flags::k_SupportsValue },
        Section{         "NPC"_sh,                  Sections::k_NPC,                                                                      Section::Flags::k_SupportsKeywords},
        Section{  "Ammo"_sh,     Sections::k_Ammo, Section::Flags::k_SupportsKeywords | Section::Flags::k_SupportsValue | Section::Flags::k_SupportsWeight},
        Section{  "Misc"_sh, Sections::k_Misc, Section::Flags::k_SupportsKeywords | Section::Flags::k_SupportsValue | Section::Flags::k_SupportsWeight},
        Section{ "Ingestible"_sh, Sections::k_Ingestible, Section::Flags::k_SupportsKeywords | Section::Flags::k_SupportsWeight },
        Section{         "Spell"_sh,                 Sections::k_Spell, Section::Flags::k_SupportsKeywords},
        Section{  "Activator"_sh,            Sections::k_Activator, Section::Flags::k_SupportsKeywords},
        Section{    "Static"_sh,            Sections::k_Static,                                                                     },
        Section{ "Constructible"_sh, Sections::k_Constructible, Section::Flags::k_None },
        Section{ "Perk"_sh, Sections::k_Perk, Section::Flags::k_None },
        Section{  "Global"_sh,   Sections::k_Global,             Section::Flags::k_None},
        Section{ "FormList"_sh, Sections::k_FormList, Section::Flags::k_None },
        Section{"Projectile"_sh, Sections::k_Projectile,k_None},
        Section{"LVLLBaseForm"_sh, Sections::k_LeveledList_BaseForm,k_None},
        Section{ "LVLLNPC"_sh, Sections::k_LeveledList_NPC, Section::Flags::k_None },
        Section{ "LVLLItem"_sh, Sections::k_LeveledList_Item, Section::Flags::k_None },
        Section{ "LVLLPackIn"_sh, Sections::k_LeveledList_PackIn, Section::Flags::k_None },
        Section{ "AVMData"_sh, Sections::k_AVMData, k_None },
        Section{ "Cell"_sh, Sections::k_CELL, k_None },
        Section{ "Location"_sh, Sections::k_Location, Section::Flags::k_SupportsKeywords },
        Section{ "VoiceType"_sh, Sections::k_VoiceType, k_None },
        Section{ "ConditionForm"_sh, Sections::k_ConditionForm, k_None },
        Section{ "MagicEffect"_sh, Sections::k_MagicEffect, Section::Flags::k_SupportsKeywords },
        Section{ "StoryManagerQuestNode"_sh, Sections::k_StoryManagerQuestNode, k_None },
        Section{ "Message"_sh, Sections::k_Message, k_None },
        Section{ "Outfit"_sh, Sections::k_Outfit, k_None },
        Section{ "Container"_sh, Sections::k_Container, Section::Flags::k_SupportsKeywords },
        Section{ "PCBN"_sh, Sections::k_PlanetContentManagerBranchNode, k_None },
        Section{ "Race"_sh, Sections::k_Race, Section::Flags::k_SupportsKeywords },
        Section{ "Reference"_sh, Sections::k_Reference, k_None },
        Section{ "ObjectModification"_sh, Sections::k_ObjectModification, k_None },
        Section{ "LoadScreen"_sh, Sections::kLoadScreen, k_None },
        Section{ "Terminal"_sh, Sections::k_Terminal, Section::Flags::k_SupportsKeywords },
        Section{"Filters"_sh,              Sections::k_Filters,k_None},
        Section{ "GameSettings"_sh, Sections::k_Gamesettings, Section::Flags::k_None },
        Section{ "Debug"_sh, Sections::k_Debug, Section::Flags::k_None },
        Section{ "Condition"_sh, Sections::k_Condition, Section::Flags::k_None },
    };

    //std::string_view GetSectionNameByID(int ID)
    //{
    //    for (auto& sect : v_Sections) {

    //        if (ID == sect.SectionID) {
    //            return sect.SectionName;
    //        }

    //    }


    //}


    int Section::GetFlags(int& iCurrentSection)
    {
        for (auto it = v_Sections.begin(); it != v_Sections.end(); it++) {
            if (Iter.SectionID == iCurrentSection) {
                return Iter.iFlags;
            }
        }

        return 0;
    }




    const Section* GetSectionByName(std::string_view sSection)
    {
        auto CurrentSection = hash_djb2a(sSection);

        for (auto it = v_Sections.begin(); it != v_Sections.end(); it++) {
            if (Iter.SectionName == CurrentSection) {
                return &(*it);
            }
        }

        return NULL;
    }



    namespace CustomFilters
    {
        struct Filter
        {
            std::string               Name{};
            std::vector<RE::TESForm*> forms{};
            int                       iSection = 0;
        };

        std::vector<Filter> v_filters;


        Filter* GetFilterByName(std::string_view sName)
        {
            for (auto it = v_filters.begin(); it != v_filters.end(); it++) {
                if ((*it).Name == sName) {
                    return &Iter;
                }
            }

            return NULL;
        }

        template <typename... Args>
        Filter* GetFilterByNameAndCheckForSection(std::string_view sName, Args... args)
        {

            if constexpr (sizeof...(args) > 1) {

                for (auto it = v_filters.begin(); it != v_filters.end(); it++) {
                    if ((*it).Name == sName) {

                        for (const auto formType : { args... }) {
                            if (Iter.iSection == formType) {
                                return &Iter;
                            }

                        }
                    }
                }
                _DRTFPError("Cannot accept filter forms for current section. No filters with allowed sections.");
                return NULL;

            }
            else {

                std::uint8_t FormType = *std::get<0>(std::make_tuple(&args...));
                for (auto it = v_filters.begin(); it != v_filters.end(); it++) {
                    if ((*it).Name == sName) {
                       if (Iter.iSection != FormType) {
                            _DRTFPError("Cannot accept filter forms for current section {}. Section in filters>>{}", FormType, Iter.iSection);
                            return NULL;
                        }
                        return &Iter;
                    }
                }
            }


            return NULL;
        }




        bool CreateFilterFromLine(std::string_view CategoryName, std::string_view ModifierSection)
        {
            //Ammo|*plugin_incl(MyTestPlugin.esm,MyTestPlugin2.esm)

            auto Section = GetSectionByName(CategoryName);

            if (!Section)
            {
                _DRTFPError("No filter section with that name found>>{}.", CategoryName);
                return false;
            }

            int iSectionID = Section->SectionID;

            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;

            NewModifierPos = ModifierSection.find(sSectionDelimeter, CurrentPos);

            if (NewModifierPos == NONPOS) {
                _DRTFPError("Custom filter:::No delimeter between forms and filter name>>{}", ModifierSection);
                return false;
            }
            else if (NewModifierPos == CurrentPos) {
                _DRTFPError("Custom filter::between forms and filter name is empty>>{}", ModifierSection);
                return false;
            }
   
           Filter NewFilter;

           if (ModifierSection.at(0) == sSearchForAllFormsSymbol) {
                NewFilter.forms = GetAllLoadedTypeFormsFromLineAndProcessFilters(iSectionID, ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos));
           }
           else if (ModifierSection.at(0) == sSearchForMultipleForms) {
                NewFilter.forms = GetMultipleFormsFromLine(iSectionID, ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos));
           }
           else {

                _DRTFPError("First symbol is not specified(can be * for filters or + for multiple forms),cannot find any forms>>{}",ModifierSection);
           }


           if (!NewFilter.forms.size()) {
                _DMESSAGE("No forms found for filters.");
                return false;
           }

           CurrentPos = NewModifierPos + 1;

           std::string_view sFilterName = ModifierSection.substr(CurrentPos, ModifierSection.length() - CurrentPos);

           if (GetFilterByName(sFilterName))
           {
                _DRTFPError("Cannot add another filter with the same name>>{}", sFilterName);
                return false;
           }

           NewFilter.Name = sFilterName;
           NewFilter.iSection = iSectionID;
           v_filters.push_back(NewFilter);

           _DMESSAGE("Added new filter>>{}, forms>>{}", sFilterName, NewFilter.forms.size());

           return true;
        }

    }






    RE::TESForm* GetFormFromStringEx(std::string_view FormIDValue)
    {
        auto DelimeterPos = FormIDValue.find(sFormIDDelimeter);

        if (DelimeterPos == NONPOS) {
           std::string CurrentFormID = std::string(FormIDValue);
           _DMESSAGE("Looking by Editor ID>>{}", FormIDValue);
           return RE::TESForm::LookupByEditorID(CurrentFormID);
        }
        else {
           std::string_view sModName = FormIDValue.substr(0, DelimeterPos);
           _DMESSAGE("Mod name>>{}", sModName);

           auto ModInfo = LoadedPlugins::GetModInfo(sModName);

           if (ModInfo == NULL) {
                _DMESSAGE("Plugin <{}> is not loaded", sModName);
                return NULL;
           }

           std::string_view sFormID = FormIDValue.substr(DelimeterPos + 1, FormIDValue.length() - 1);

           auto DEC = GetDECFromHEX(sFormID);
           if (!DEC) {
                return NULL;
           }
           std::uint32_t FormIDToLook = 0;

           if (ModInfo->type == LoadedPlugins::PluginType::k_Full)
           {
                FormIDToLook = ((ModInfo->Index & 0xFF) << 24) | (DEC & 0x00FFFFFF);
                _DMESSAGE("BuiltFormID for {} is {:08X}", FormIDValue, FormIDToLook);
           }
           else if (ModInfo->type == LoadedPlugins::PluginType::k_Medium) {
                FormIDToLook = 0xFD << 24 | ((ModInfo->Index) << 24) | (DEC & 0x0000FFFF);
           }
           else if (ModInfo->type == LoadedPlugins::PluginType::k_Small) {
                FormIDToLook = 0xFE << 24 | ((ModInfo->Index) << 12) | (DEC & 0x00000FFF);
           }
           else {
                _DMESSAGE("Type of plugin is not supported.");
           }


           return RE::TESForm::LookupByID(FormIDToLook);
        }
    }


    std::uint32_t GetFormIDFromStringEx(std::string_view FormIDValue)
    {
        auto DelimeterPos = FormIDValue.find(sFormIDDelimeter);

        if (DelimeterPos == NONPOS) {
           std::string CurrentFormID = std::string(FormIDValue);
           _DMESSAGE("Looking by Editor ID>>{}", FormIDValue);
           return NULL;
        }
        else {
           std::string_view sModName = FormIDValue.substr(0, DelimeterPos);
           _DMESSAGE("Mod name>>{}", sModName);

           auto ModInfo = LoadedPlugins::GetModInfo(sModName);

           if (ModInfo == NULL) {
                _DMESSAGE("Plugin <{}> is not loaded", sModName);
                return NULL;
           }

           std::string_view sFormID = FormIDValue.substr(DelimeterPos + 1, FormIDValue.length() - 1);

           auto DEC = GetDECFromHEX(sFormID);
           if (!DEC) {
                return NULL;
           }
           std::uint32_t FormIDToLook = 0;

           if (ModInfo->type == LoadedPlugins::PluginType::k_Full) {
                FormIDToLook = ((ModInfo->Index & 0xFF) << 24) | (DEC & 0x00FFFFFF);
           }
           else if (ModInfo->type == LoadedPlugins::PluginType::k_Medium) {
                FormIDToLook = 0xFD << 24 | ((ModInfo->Index) << 24) | (DEC & 0x0000FFFF);
           }
           else if (ModInfo->type == LoadedPlugins::PluginType::k_Small) {
                FormIDToLook = 0xFE << 24 | ((ModInfo->Index) << 12) | (DEC & 0x00000FFF);
           }
           else {
                _DMESSAGE("Type of plugin is not supported.");
           }
           _DMESSAGE("BuiltFormID for {} is {:08X}", FormIDValue, FormIDToLook);
           return FormIDToLook;
        }
    }





    //RE::TESForm* GetFormFromString(std::string_view FormIDValue)
    //{
    //    //_MESSAGE("TEXT>>{},LENGTH>>{},SIZE>>{}", FormIDValue.data(), FormIDValue.length(), FormIDValue.size());
    //    auto DelimeterPos = FormIDValue.find(sFormIDDelimeter);

    //    if (DelimeterPos == NONPOS) {
    //        std::string CurrentFormID = std::string(FormIDValue); // because it doesn't work with string_view. Prolly need to create a char on stack.
    //        // char        TempChar[257];
    //        // FormIDValue.copy(TempChar,FormIDValue.length());

    //        _DMESSAGE("Looking by Editor ID>>{}", FormIDValue);
    //        return RE::TESForm::LookupByEditorID(CurrentFormID);
    //    }
    //    else {
    //        std::string_view sModName = FormIDValue.substr(0, DelimeterPos);
    //        _DMESSAGE("Mod name>>{}", sModName);

    //        auto ModIndex = LoadedPlugins::GetModIndex(sModName);

    //        if (ModIndex == iBadPluginindex)
    //        {
    //            _DMESSAGE("Plugin <{}> is not loaded", sModName);
    //            return NULL;
    //        }

    //        std::string_view sFormID = FormIDValue.substr(DelimeterPos + 1, FormIDValue.length() - 1);

    //        auto DEC = GetDECFromHEX(sFormID);
    //        if (!DEC) {
    //            return NULL;
    //        }

    //        std::uint32_t FormIDToLook = ((ModIndex & 0xFF) << 24) | (DEC & 0x00FFFFFF);
    //        _DMESSAGE("BuiltFormID for {} is {:08X}", FormIDValue, FormIDToLook);
    //        return RE::TESForm::LookupByID(FormIDToLook);
    //    }
    //}


    //std::uint32_t GetFormIDFromString(std::string_view FormIDValue)
    //{
    //    auto DelimeterPos = FormIDValue.find(sFormIDDelimeter);

    //    if (DelimeterPos == NONPOS) {

    //        return NULL;
    //    }
    //    else {
    //        std::string_view sModName = FormIDValue.substr(0, DelimeterPos);
    //        _DMESSAGE("Mod name>>{}", sModName);

    //        auto ModIndex = LoadedPlugins::GetModIndex(sModName);

    //        if (ModIndex == iBadPluginindex) {
    //            _DMESSAGE("Plugin <{}> is not loaded", sModName);
    //            return NULL;
    //        }

    //        std::string_view sFormID = FormIDValue.substr(DelimeterPos + 1, FormIDValue.length() - 1);

    //        auto DEC = GetDECFromHEX(sFormID);
    //        if (!DEC) {
    //            return NULL;
    //        }

    //        std::uint32_t FormIDToLook = ((ModIndex & 0xFF) << 24) | (DEC & 0x00FFFFFF);

    //        _DMESSAGE("BuiltFormID for {} is {:08X}", FormIDValue, FormIDToLook);
    //        return FormIDToLook;
    //    }
    //}


    struct TESFormResult
    {
        bool bValid = true;
        RE::TESForm* data = NULL;
    };

    //template <bool bAllowNull>
    //TESFormResult GetFormFromStringAndCheckForCategory(std::string_view FormIDValue, uint8_t iCurrentCategory)
    //{
    //    TESFormResult result;

    //    if (FormIDValue == sNULLForm) {
    //        if constexpr (bAllowNull == false) {
    //            result.bValid = false;
    //            _DRTFPError("NULL form is not allowed in this case.");
    //        }
    //        return result;
    //    }


    //    result.data = GetFormFromString(FormIDValue);

    //    if (!result.data) {
    //        _DRTFPFormBuiltError("Cannot find specified form from line>>{}", FormIDValue);
    //        result.bValid = false;
    //        return result;
    //    }

    //    if (result.data->formType.underlying() != iCurrentCategory && iCurrentCategory != Input::Sections::k_Debug) {
    //        _DRTFPError("Found form <{}> type {} is not equal to category it should be in in>>{}", FormIDValue, result.data->formType.underlying(), iCurrentCategory);
    //        result.bValid = false;
    //        return result;
    //    }

    //    return result;
    //}



    template <bool bAllowNull, typename... Args>
    TESFormResult GetFormFromStringAndCheckForCategory(std::string_view FormIDValue, Args... args)
    {
        TESFormResult result;

        if (FormIDValue == sNULLForm) {
            if constexpr (bAllowNull == false) {
                result.bValid = false;
                _DRTFPError("NULL form is not allowed in this case.");
            }
            return result;
        }

        result.data = GetFormFromStringEx(FormIDValue);

        if (!result.data) {
            _DRTFPFormBuiltError("Cannot find specified form from line>>{}", FormIDValue);
            result.bValid = false;
            return result;
        }

        if constexpr (sizeof...(args) > 1) {
            bool bFound = false;

            _DMESSAGE("ARGS COUNT > 1");
            for (const auto formType : { args... }) {
                if (result.data->formType.underlying() == formType) {
                    bFound = true;
                    break;
                }
            }

            if (!bFound) {
                _DRTFPError("Found form <{}> type {} is not equal to any categories supported for this values.", FormIDValue, result.data->formType.underlying());
                result.bValid = false;
                return result;
            }
        }
        else {
            //_DMESSAGE("ARGS COUNT = 1");
            std::uint8_t FormType = *std::get<0>(std::make_tuple(&args...)); // this actually gets optimized down to a var comparison lol
            
            if (result.data->formType.underlying() != FormType && FormType != Input::Sections::k_Debug) { 
                _DRTFPError("Found form <{}> type {} is not equal to category it should be in in>>{}", FormIDValue, result.data->formType.underlying(), FormType);
                result.bValid = false;
                return result;
            }

        }


        return result;
    }





    template<bool bAllowNull>
    TESFormResult GetFormFromStringAndDontCheckForCategory(std::string_view FormIDValue)
    {
        TESFormResult result;

        if (FormIDValue == sNULLForm){

            if constexpr (bAllowNull == false) {
                result.bValid = false;
                _DRTFPError("NULL form is not allowed in this case.");
            }

            return result;
        }

        result.data = GetFormFromStringEx(FormIDValue);

        if (!result.data) {
            result.bValid = false;
            _DRTFPFormBuiltError("Cannot find specified form from line>>{}", FormIDValue);
            return result;
        }

        return result;
    }












    void ApplyMemberNumberMofidier(TempModifierAlt::Value& value, bool& CurrentValue)
    {
        _DMESSAGE("ApplyMemberModifier ALT starts for BOOL>>{}", value.CurrentModifierValue);

        if (IsFlagSet(value.flags, TempModifierAlt::Flags::kValid)) {
            CurrentValue = (bool)value.cached.dNumber;
        }
        else {
            value.flags |= TempModifierAlt::Flags::kNeedsToBeValid;

            if (isdigit(value.CurrentModifierValue.at(0))) {
                auto DValue = GetNumberFromString<double>(value.CurrentModifierValue);
                if (!DValue.bSuccess) {
                    return;
                }

                _DMESSAGE("Value after converting>>{}. Setting cached value", DValue.data);
                value.flags |= TempModifierAlt::Flags::kValid;
                value.cached.dNumber = DValue.data;
                SetFloatMofidier(CurrentValue, DValue.data);
            }
            else {
                _DRTFPError("Cannot apply mathematical operations on bool modifier>>{}", value.CurrentModifierValue);
            }
        }
    }


    void ApplyMemberNumberMofidier(std::string_view CurrentModifierValue, bool& CurrentValue)
    {
        _DMESSAGE("ApplyMemberFloatMofidier for BOOL {}", CurrentModifierValue);

        if (isdigit(CurrentModifierValue.at(0))) {
            auto Value = GetNumberFromString<double>(CurrentModifierValue);

            if (!Value.bSuccess) {
                return;
            }

            _DMESSAGE("Bool result>>{}", Value.data);
            CurrentValue = (bool)Value.data;
        }
        else {
            _DRTFPError("Cannot apply mathematical operations on bool modifier>>{}", CurrentModifierValue);
        }
    }


    template <class T>
    void ApplyMemberNumberMofidier(TempModifierAlt::Value& value, T& CurrentValue)
    {
        _DMESSAGE("ApplyMemberModifier ALT starts>>{}", value.CurrentModifierValue);
        if (IsFlagSet(value.flags, TempModifierAlt::Flags::kValid)) {
            _DMESSAGE("Cached num valid>>{}", value.cached.dNumber);
            if (IsFlagSet(value.flags, TempModifierAlt::Flags::kCalcSet)) {
                //_DMESSAGE("Cached set");
                SetFloatMofidier(CurrentValue, value.cached.dNumber);
            }
            else if (IsFlagSet(value.flags, TempModifierAlt::Flags::kCalcAdd)) {
                //_DMESSAGE("Cached add");
                AddFloatMofidier(CurrentValue, value.cached.dNumber);
            }
            else if (IsFlagSet(value.flags, TempModifierAlt::Flags::kCalcSub)) {
                //_DMESSAGE("Cached sub");
                SubFloatMofidier(CurrentValue, value.cached.dNumber);
            }
            else if (IsFlagSet(value.flags, TempModifierAlt::Flags::kCalcMult)) {
                //_DMESSAGE("Cached mult");
                MultFloatMofidier(CurrentValue, value.cached.dNumber);
            }
            else if (IsFlagSet(value.flags, TempModifierAlt::Flags::kCalcDiv)) {
                //_DMESSAGE("Cached div");
                DivFloatMofidier(CurrentValue, value.cached.dNumber);
            }
            else {
                _DRTFPError("Could not proceed with flags in cached double value>>{}", value.flags);
            }
        }
        else {
            value.flags |= TempModifierAlt::Flags::kNeedsToBeValid;
            if (isdigit(value.CurrentModifierValue.at(0))) {
                auto DValue = GetNumberFromString(CurrentValue, value.CurrentModifierValue);
                if (!DValue.bSuccess) {
                    return;
                }

                _DMESSAGE("Value after converting>>{}. Setting cached value", DValue.data);
                value.flags |= TempModifierAlt::Flags::kValid;
                value.flags |= TempModifierAlt::Flags::kCalcSet;
                value.cached.dNumber = DValue.data;
                SetFloatMofidier(CurrentValue, DValue.data);
            }
            else {
                auto DValue = GetNumberFromString(CurrentValue, value.CurrentModifierValue.substr(1, value.CurrentModifierValue.size() - 1));

                if (!DValue.bSuccess) {
                    return;
                }

                _DMESSAGE("Value after converting>>{}. Setting cached value", DValue.data);

                switch (value.CurrentModifierValue.at(0)) {
                case sAdd:
                    value.flags |= TempModifierAlt::Flags::kValid;
                    value.cached.dNumber = DValue.data;
                    value.flags |= TempModifierAlt::Flags::kCalcAdd;
                    AddFloatMofidier(CurrentValue, DValue.data);
                    break;
                case sSub:
                    value.flags |= TempModifierAlt::Flags::kValid;
                    value.cached.dNumber = DValue.data;
                    value.flags |= TempModifierAlt::Flags::kCalcSub;
                    SubFloatMofidier(CurrentValue, DValue.data);
                    break;
                case sMult:
                    value.flags |= TempModifierAlt::Flags::kValid;
                    value.cached.dNumber = DValue.data;
                    value.flags |= TempModifierAlt::Flags::kCalcMult;
                    MultFloatMofidier(CurrentValue, DValue.data);
                    break;
                case sDiv:
                    value.flags |= TempModifierAlt::Flags::kValid;
                    value.cached.dNumber = DValue.data;
                    value.flags |= TempModifierAlt::Flags::kCalcDiv;
                    DivFloatMofidier(CurrentValue, DValue.data);
                    break;
                default:
                    _DRTFPError("Operation not supported>>{}", value.CurrentModifierValue);
                }
            }
        }
    }


    template <class T>
    void ApplyMemberNumberMofidier(std::string_view CurrentModifierValue, T& CurrentValue)
    {
        _DMESSAGE("ApplyMemberFloatMofidier {}", CurrentModifierValue);


        if (isdigit(CurrentModifierValue.at(0))) {

            auto Value = GetNumberFromString(CurrentValue, CurrentModifierValue);

            if (!Value.bSuccess)
            {
                return;
            }

            //_DMESSAGE("Value after converting>>{}", Value.data);

           CurrentValue = Value.data;
        }
        else {

            auto Value = GetNumberFromString(CurrentValue,CurrentModifierValue.substr(1, CurrentModifierValue.size() - 1));

            if (!Value.bSuccess) {
                return;
            }

            switch (CurrentModifierValue.at(0)) {
            case sAdd:
                AddFloatMofidier(CurrentValue, Value.data);
                break;
            case sSub:
                SubFloatMofidier(CurrentValue, Value.data);
                break;
            case sMult:
                MultFloatMofidier(CurrentValue, Value.data);
                break;
            case sDiv:
                DivFloatMofidier(CurrentValue, Value.data);
                break;
            default:
                _DRTFPError("Operation not supported>>{}", CurrentModifierValue);
            }
        }
    }


    

    





    namespace SFString
    {
        template<class T>
        void Set(T& modelPath, std::string_view ModifierSection)
        {
            if (ModifierSection.length() > iMaxCharCountForValues)
            {
               _DRTFPError("Maximum lenght is exceeded for model>>>>{}", ModifierSection);
                return;
            }
            else if (ModifierSection.length()< 2)
            {
                _DRTFPError("Lenght of string is less than 2(it must be enclosed in quotes)", ModifierSection);
                return;
            }

            if (ModifierSection.at(0) != '\"' || ModifierSection.at(ModifierSection.length() - 1) != '\"')
            {
                _DRTFPError("String is not put in quotes", ModifierSection);
                return;
            }

            

            _DMESSAGE("new string path>>{}", ModifierSection);
            char TempArr[iMaxCharCountForValues + 1];
            FillCharFromModifierStringExceptFirstAndLastSymbol(ModifierSection, TempArr);

            //strncpy(TempArr, ModifierSection.data(), ModifierSection.length());
            //TempArr[ModifierSection.length()] = '\0';
            modelPath = TempArr;
        }

      


    }






    namespace FormListArray
    {
        void AddFormListToArray(RE::BSTArray<RE::TESForm*>& formlist, RE::TESForm* CurrentForm)
        {
            formlist.push_back(CurrentForm);
        }

        void RemoveFormListFromArray(RE::BSTArray<RE::TESForm*>& formlist, RE::TESForm* CurrentForm)
        {
            for (auto it = formlist.begin(); it != formlist.end(); ) {
                if (Iter->formID == CurrentForm->formID) {
                    it = formlist.erase(it);
                    continue;
                }
                it++;
            }



        }

        template <typename F>
        void AddRemoveFormListInArray(RE::BSTArray<RE::TESForm*>& formlist, std::string_view ModifierSection, F func)
        {
            if (ModifierSection.at(0) == sSearchForFilters)
            {
                auto CustomFilter = Input::CustomFilters::GetFilterByName(ModifierSection.substr(1, ModifierSection.length() - 1));

                if (!CustomFilter) {
                    _DRTFPError("Cannot find a filter with name>>{}", ModifierSection.substr(1, ModifierSection.length() - 1));
                    return;
                }

                for (auto it = CustomFilter->forms.begin(); it != CustomFilter->forms.end(); it++)
                {
                    func(formlist, Iter);
                }

            }
            else {
                size_t CurrentPos     = 0;
                size_t NewModifierPos = 0;
                while (NewModifierPos != NONPOS) {
                    NewModifierPos = ModifierSection.find(sArrDelimeter, CurrentPos);

                    auto CurrentForm = GetFormFromStringAndDontCheckForCategory<false>(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos));
                    CurrentPos       = NewModifierPos + 1;

                    if (!CurrentForm.bValid) {
                        continue;
                    }

                    func(formlist, CurrentForm.data);
                }
            }
        }





        void ReplaceFormListInArray(RE::BSTArray<RE::TESForm*>& formlist, std::string_view ModifierSection)
        {
            // CurrentModifierValue = ObjectTypeAmmo,sMyFormList

            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;

            NewModifierPos = ModifierSection.find(sArrDelimeter, CurrentPos);

            if (NewModifierPos == NONPOS) {
                _DRTFPError("Replace::No comma between entries.");
                return;
            }

            auto CurrentForm = GetFormFromStringAndDontCheckForCategory<false>(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos));

            if (!CurrentForm.bValid) {
                return;
            }

            CurrentPos = NewModifierPos + 1;

            auto ReplacedForm = GetFormFromStringAndDontCheckForCategory<false>(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos));

            if (!ReplacedForm.bValid) {
                return;
            }

            for (auto it = formlist.begin(); it != formlist.end(); it++) {
                if (Iter == CurrentForm.data) {
                    formlist.erase(it);
                    formlist.push_back(ReplacedForm.data);
                    return;
                }
            }
        }

    }

    namespace AttachParentsArray // FUCK TEMPLATES. FUCK THEM.
    {

        template <class T>
        struct StoredData
        {
            bool                            bAffected           = false;
            T formIn              = NULL;
            int                             iOriginalEntryCount = 0;
            std::vector<RE::BGSKeyword*> vEntries{};

            template <class T>
            bool GetEntriesFromForm(T formIn)
            {
                auto& triplet = RTFP::Triplet(RTFP::AttachKeywords(formIn->attachParents));

                _DMESSAGE("Getting entries from form>>{:08X},First entry>>{:08X},Last entry>>{:08X},Last entry 2>>{:08X}", formIn->formID,
                          (uintptr_t)triplet.begin, (uintptr_t)triplet.end, (uintptr_t)triplet.capacityEnd);

                if (!triplet.begin) {
                    _DMESSAGE("No first entry in form>>{:08X}", formIn->formID);
                    return true;
                }

                if (!triplet.end) {
                    _DMESSAGE("No last entry in form>>{:08X}. DATA IS NOT VALID - CANNOT EDIT THIS FORM", formIn->formID);
                    return false;
                }

                uintptr_t pDifference = (uintptr_t)triplet.end - (uintptr_t)triplet.begin;

                if ((uintptr_t)triplet.end < (uintptr_t)triplet.begin) {
                    _DMESSAGE("Last entry is less than first entry - should not happen - CANNOT EDIT THIS FORM>>{:08X}. {:08X} vs {:08X}", formIn->formID,
                              (uintptr_t)triplet.end, (uintptr_t)triplet.begin);
                    return false;
                }
                float fDifference = pDifference / sizeof(RE::BGSKeyword*);
                _DMESSAGE("Difference between pointers>>{}", fDifference);

                if (!(std::trunc(fDifference) == fDifference)) {
                    _DMESSAGE("Pointers of entries are messed up - should not happen - CANNOT EDIT THIS FORM>>{:08X}. {:08X} vs {:08X}, diff>>{}", formIn->formID,
                              (uintptr_t)triplet.end, (uintptr_t)triplet.begin, fDifference);
                    return false;
                }

                int iCount = fDifference;
                vEntries.reserve(iCount + 1);
                iOriginalEntryCount = iCount;

               for (RE::BGSKeyword** entr = static_cast<RE::BGSKeyword**>(triplet.begin); entr != static_cast<RE::BGSKeyword**>(triplet.end);) {
                    _DMESSAGE("keyword formID>>{:08X}", (*entr)->formID);
                    vEntries.push_back(*entr);
                    entr++;
                }

                
                _DMESSAGE("APPR::Added {} entries from the form>>{:08X}", vEntries.size(), formIn->formID);
                return true;
            }


            void ApplyChanges()
            {
                _DMESSAGE("---------------Applying AVDM Changes for {:08X}", formIn->formID);

                auto& triplet = RTFP::Triplet(RTFP::AttachKeywords(formIn->attachParents));

                if (!vEntries.size()) {
                    RE::MemoryManager::GetSingleton()->Free(triplet.begin, 0);
                    triplet.begin       = NULL;
                    triplet.end         = NULL;
                    triplet.capacityEnd = NULL;
                    _DMESSAGE("---------------Entries are empty - clearing original array.");
                    return;
                }

                //RE::BGSKeyword** NewObject = new RE::BGSKeyword*[vEntries.size()];

                RE::BGSKeyword** NewObject = (RE::BGSKeyword**)RE::MemoryManager::GetSingleton()->Allocate(sizeof(RE::BGSKeyword*) * (vEntries.size()), 0, false);



                _DMESSAGE("NewObjectAddres>>{:08X}, LastAddress>>{:08X}", (uintptr_t)NewObject, ((uintptr_t)NewObject + sizeof(RE::AVMData::Entry) * vEntries.size()));

                int iCount = 0;
                for (auto it = vEntries.begin(); it != vEntries.end(); it++) {
                    _DMESSAGE("placing {} at {:08X}", iCount, (uintptr_t)&NewObject[iCount]);
                    NewObject[iCount] = Iter;
                    iCount++;
                }

                _DMESSAGE("Addresses - First entry>>{:08X},Last entry>>{:08X}", (uintptr_t)NewObject, (uintptr_t)&NewObject[vEntries.size() - 1]);

                //RE::MemoryManager::GetSingleton()->Free(formIn->attachParents.firstEntry, 0);
                StoredEntries::Entry NewEntry;
                NewEntry.formIn     = formIn;
                NewEntry.firstEntry = (uintptr_t)triplet.begin;
                NewEntry.lastEntry  = (uintptr_t)triplet.end;
                NewEntry.lastEntry2 = (uintptr_t)triplet.capacityEnd;


                triplet.begin       = NewObject;
                triplet.end         = &NewObject[vEntries.size()]; // yes, invalid pointer intended
                triplet.capacityEnd = triplet.end; // wtf is last entry 2


                NewEntry.NewFirstEntryAddress = (uintptr_t)NewObject;
                StoredEntries::v_Stored.push_back(NewEntry);

                _DMESSAGE("New  AVDM addresses - First entry>>{:08X},Last entry>>{:08X},Last entry 2>>{:08X}", (uintptr_t)triplet.begin,
                          (uintptr_t)triplet.end,
                          (uintptr_t)triplet.capacityEnd);
            }
        };

        std::vector<StoredData<RE::TESObjectWEAP*>> v_WeaponBGSEntries{};
        std::vector<StoredData<RE::TESObjectARMO*>> v_ArmorBGSEntries{};

        template <class T, typename TYPENAME>
        StoredData<T>* GetOrCreateStoredData(T formIn, std::vector<StoredData<TYPENAME>>& vStored)
        {
            for (auto it = vStored.begin(); it != vStored.end(); it++) {
                if (Iter.formIn->formID == formIn->formID) {
                    _DMESSAGE("Found stored data,formID>>{:08X}", Iter.formIn->formID);
                    return &Iter;
                }
            }

            StoredData<TYPENAME> NewStoredData{};
            NewStoredData.formIn = formIn;

            if (!NewStoredData.GetEntriesFromForm(formIn)) {
                _DMESSAGE("DATA NOT VALID - not creating.");
                return NULL;
            }

            vStored.push_back(NewStoredData);
            _DMESSAGE("Created new stored data for formID>>{:08X}", vStored.back().formIn->formID);

            return &vStored.back();
        }

        template <class T, typename TYPENAME, typename F>
        void AddRemoveForm(T formIn, std::string_view ModifierSection, std::vector<StoredData<TYPENAME>>& vEntries, F funcProcess)
        {
            auto pData = GetOrCreateStoredData(formIn, vEntries);

            if (!pData) {
                _DRTFPError("Critical error - cannot edit form.");
                return;
            }

            if (ModifierSection.at(0) == sSearchForFilters) {
                auto CustomFilter = Input::CustomFilters::GetFilterByNameAndCheckForSection(ModifierSection.substr(1, ModifierSection.length() - 1), Sections::k_Keyword);

                if (!CustomFilter) {
                    _DRTFPError("Cannot find a filter with name>>{}", ModifierSection.substr(1, ModifierSection.length() - 1));
                    return;
                }

                for (auto it = CustomFilter->forms.begin(); it != CustomFilter->forms.end(); it++) {
                    funcProcess(pData, (RE::BGSKeyword*)Iter);
                }
            }
            else {
                size_t CurrentPos     = 0;
                size_t NewModifierPos = 0;
                while (NewModifierPos != NONPOS) {
                    NewModifierPos = ModifierSection.find(sArrDelimeter, CurrentPos);

                    auto CurrentForm = GetFormFromStringAndCheckForCategory<false>(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos),
                                                                                   const_GetTypeFromFormType<RE::BGSKeyword*>());
                    CurrentPos       = NewModifierPos + 1;

                    if (!CurrentForm.bValid) {

                        continue;
                    }

                    funcProcess(pData, (RE::BGSKeyword*)CurrentForm.data);
                }
            }
        }

        template <typename T>
        void AddToArray(T* pData, RE::BGSKeyword* NewEntry)
        {
            _DMESSAGE("Adding entry to vector>>>{:08X}", NewEntry->formID);
            pData->vEntries.push_back(NewEntry);
            pData->bAffected = true;
        }

        template <typename T>
        void RemoveFromArray(T* pData, RE::BGSKeyword* NewEntry)
        {
            for (auto it = pData->vEntries.begin(); it != pData->vEntries.end(); it++) {
                if (Iter->formID == NewEntry->formID) {
                    pData->vEntries.erase(it);
                    pData->bAffected = true;
                    return;
                }
            }

        }

        template <class T, typename TYPENAME>
        void ClearArray(T formIn, std::vector<StoredData<TYPENAME>>& vStored)
        {
            auto pData = GetOrCreateStoredData(formIn, vStored);

            if (!pData) {
                _DRTFPError("Critical error - cannot edit form");
                return;
            }
            pData->vEntries.clear();
            pData->bAffected = true;
        }

        template <class T, typename TYPENAME>
        void ProcessReplacing(T formIn, std::string_view ModifierSection, std::vector<StoredData<TYPENAME>>& vStored)
        {
            auto pData = GetOrCreateStoredData(formIn, vStored);

            if (!pData) {
                _DRTFPError("Critical error - cannot edit form");
                return;
            }

            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;

            NewModifierPos = ModifierSection.find(sArrDelimeter, CurrentPos);

            if (NewModifierPos == NONPOS) {
                _DRTFPError("No comma in>>{}", ModifierSection);
                return;
            }

            auto CurrentForm
                = GetFormFromStringAndCheckForCategory<false>(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos), const_GetTypeFromFormType<RE::BGSKeyword*>());

            if (!CurrentForm.bValid) {
                return;
            }

            CurrentPos = NewModifierPos + 1;

            auto ReplacedForm= GetFormFromStringAndCheckForCategory<false>(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos), const_GetTypeFromFormType<RE::BGSKeyword*>());

            if (!ReplacedForm.bValid) {
                return;
            }

            RE::BGSKeyword* ReplacedFormUse = (RE::BGSKeyword*)ReplacedForm.data;

            for (auto it = pData->vEntries.begin(); it != pData->vEntries.end(); it++) {
                if (Iter->formID == CurrentForm.data->formID) {
                    pData->vEntries.erase(it);
                    pData->vEntries.push_back(ReplacedFormUse);
                    return;
                }

            }

            return;
        }

    }

    namespace ElementOperators
    {

        //Faction rank
        bool _forceinline AreEntriesEqual(RE::FACTION_RANK& left, RE::FACTION_RANK& right)
        {
            if (left.faction == right.faction && left.rank == right.rank) {
                return true;
            }
            return false;
        }

        void _forceinline ReplaceLeftWithRight(RE::FACTION_RANK& left, RE::FACTION_RANK& right)
        {
            left.faction = right.faction;
            left.rank    = right.rank;
        }


        //Story manager quest entry
        bool _forceinline AreEntriesEqual(BGSStoryManagerQuestNode::QuestEntry& left, BGSStoryManagerQuestNode::QuestEntry& right)
        {
            if (left.quest == right.quest && left.HoursUntilReset == right.HoursUntilReset) {
                return true;
            }
            return false;
        }

        void _forceinline ReplaceLeftWithRight(BGSStoryManagerQuestNode::QuestEntry& left, BGSStoryManagerQuestNode::QuestEntry& right)
        {
            left.HoursUntilReset = right.HoursUntilReset;
            left.quest           = right.quest;
        }



        //Constructible form component + Damage Type Array in weapons
        bool _forceinline AreEntriesEqual(TUPLE3& left, TUPLE3& right)
        {
            if (left.first == right.first && left.third.i == right.third.i) { // && left.second == right.second
                return true;
            }
            return false;
        }

        void _forceinline ReplaceLeftWithRight(TUPLE3& left, TUPLE3& right)
        {
            left       = right;
        }

        RE::BSTArray<TUPLE3>* CreatePointerBSTArrayIdNotExist(RE::BSTArray<TUPLE3>*& Arr)
        {
            _DMESSAGE("CREATING NEW COMP ARRAY.");

            auto NewArray = new RE::BSTArray<TUPLE3>;
            Arr           = NewArray;
            _DMESSAGE("CREATING NEW COMP ARRAY DONE.");
            return Arr;
        }


        //Perk Array perks

        bool _forceinline AreEntriesEqual(RE::PerkRankData& left, RE::PerkRankData& right)
        {
            if (left.perk->formID == right.perk->formID && left.currentRank == right.currentRank) {
                return true;
            }
            return false;
        }

        void _forceinline ReplaceLeftWithRight(RE::PerkRankData& left, RE::PerkRankData& right)
        {
            left.currentRank = right.currentRank;
            left.perk        = right.perk;
        }


        bool _forceinline AreEntriesEqual(PROPERTY& left, PROPERTY& right)
        {
            if (left.first == right.first && left.third.i == right.third.i && left.second == right.second) {
                return true;
            }
            return false;
        }

        void _forceinline ReplaceLeftWithRight(PROPERTY& left, PROPERTY& right)
        {
            left = right;
            // left.first = right.first;
            // left.third = right.third;
        }

        RE::BSTArray<PROPERTY>* CreatePointerBSTArrayIdNotExist(RE::BSTArray<PROPERTY>*& Arr)
        {
            _DMESSAGE("CREATING NEW COMP ARRAY.");

            auto NewArray = new RE::BSTArray<PROPERTY>;
            Arr           = NewArray;
            _DMESSAGE("CREATING NEW COMP ARRAY DONE.");
            return Arr;
        }

        bool _forceinline AreEntriesEqual(RE::ContainerObject& left, RE::ContainerObject& right)
        {
            if (left.obj->formID == right.obj->formID &&left.count == right.count && left.itemExtra == right.itemExtra) {
                return true;
            }
            return false;
        }

        void _forceinline ReplaceLeftWithRight(RE::ContainerObject& left, RE::ContainerObject& right)
        {
            left.obj = right.obj;
            left.itemExtra = right.itemExtra;
            left.obj       = right.obj;
        }

        bool _forceinline AreEntriesEqual(RE::BGSMod::Attachment::Mod::Data::Include& left, RE::BGSMod::Attachment::Mod::Data::Include& right)
        {
            if (left.mod == right.mod && left.level == right.level && left.flags.underlying() == right.flags.underlying()) {
                return true;
            }
            return false;
        }

        void _forceinline ReplaceLeftWithRight(RE::BGSMod::Attachment::Mod::Data::Include& left, RE::BGSMod::Attachment::Mod::Data::Include& right)
        {
            left.mod      = right.mod;
            left.level = right.level;
            left.flags      = right.flags;
        }


    }






    namespace ObjectModification
    {

        struct EntryFromString
        {
            struct Data
            {
                RE::BGSMod::Attachment::Mod::Data::Include elem;
            };

            bool bValid = false;
            Data data;

            EntryFromString()
            {
                std::uint8_t* pFlags = (std::uint8_t*)&data.elem.flags; // hate those fucking flags.
                *pFlags              = 0;
                data.elem.level = 0;
                data.elem.mod       = NULL;
                _DMESSAGE("OMOD init");
            }
        };

        //struct StoredEntryFromString
        //{
        //    unsigned long Hash;
        //    EntryFromString StoredEntry;
        //};

        //std::vector<StoredEntryFromString> v_StoredEntries{};

        


        template <bool bInsert>
        EntryFromString GetFromString(std::string_view ModifierSection)
        {
            EntryFromString result;

            //for (auto it = v_StoredEntries.begin(); it != v_StoredEntries.end(); it++)
            //{
            //    DConsole_Print("test 1");
            //    if (hash_djb2a(ModifierSection) == Iter.Hash)
            //    {
            //        _MESSAGE("returning stored entry");
            //        return Iter.StoredEntry;
            //    }
            //}
            //DConsole_Print("test 2");

            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;

            static_assert(bInsert == false, "Cannot insert this element yet");

            NewModifierPos = ModifierSection.find(sPropertiesDelimeter, CurrentPos); 

            if (NewModifierPos == NONPOS) {
                _DRTFPError("OMOD::No properties for form>>{}", ModifierSection);
                return result;
            }

            auto CurrentForm = GetFormFromStringAndCheckForCategory<false>(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos),
                                                                           const_GetTypeFromFormType<RE::BGSMod::Attachment::Mod*>());

            if (!CurrentForm.bValid) {
                return result;
            }

            CurrentPos = NewModifierPos + 1;
            NewModifierPos = ModifierSection.find(sPropertiesDelimeter, CurrentPos);
            if (NewModifierPos == NONPOS) {
                _DRTFPError("OMOD:::No properties for Level>>{}", ModifierSection);
                return result;
            }

            auto Level = GetNumberFromString<std::int8_t>(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos));

            if (!Level.bSuccess) {
                _DRTFPError("OMOD::Cannot convert level to a number>>{}", ModifierSection);
                return result;
            }

            CurrentPos = NewModifierPos + 1;
            NewModifierPos = ModifierSection.find(sPropertiesDelimeter, CurrentPos);

            if (NewModifierPos == NONPOS) {
                _DRTFPError("OMOD:::No properties for Optional>>{}", ModifierSection);
                return result;
            }

            auto FlagOptional = GetNumberFromString<std::uint8_t>(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos));

            if (!FlagOptional.bSuccess) {
                _DRTFPError("OMOD::Cannot convert optional to a number>>{}", ModifierSection);
                return result;
            }
            CurrentPos     = NewModifierPos + 1;

            auto FlagDontUseAll = GetNumberFromString<std::uint8_t>(ModifierSection.substr(CurrentPos, ModifierSection.length() - CurrentPos));

            if (!FlagDontUseAll.bSuccess) {
                _DRTFPError("OMOD::Cannot convert optional to a number>>{}", ModifierSection);
                return result;
            }


            result.data.elem.level = Level.data;
            result.data.elem.mod   = (RE::BGSMod::Attachment::Mod*)CurrentForm.data;

            if (FlagOptional.data)
            {
                result.data.elem.flags.set(RE::BGSMod::Attachment::Mod::Data::IncludesFlag::kOptional);
            }

            if (FlagDontUseAll.data) {
                result.data.elem.flags.set(RE::BGSMod::Attachment::Mod::Data::IncludesFlag::kDontUseAll);
            }

            result.bValid          = true;
            _DMESSAGE("New OMOD, Mod>>{:08X},level>>{},optional>{},DontUseAll>{}", result.data.elem.mod->formID, result.data.elem.level,
                      result.data.elem.flags.any(RE::BGSMod::Attachment::Mod::Data::IncludesFlag::kOptional),
                      result.data.elem.flags.any(RE::BGSMod::Attachment::Mod::Data::IncludesFlag::kDontUseAll));


            //StoredEntryFromString NewStoredEntry;
            //NewStoredEntry.Hash = hash_djb2a(ModifierSection);
            //NewStoredEntry.StoredEntry = result;
            //v_StoredEntries.push_back(NewStoredEntry);
            return result;
        }

    }








    namespace ContainerItem
    {

        struct EntryFromString
        {
            struct Data
            {
                RE::ContainerObject elem;
                std::uint32_t    iEntryPos = 0;
            };

            bool bValid = false;
            Data data;

            EntryFromString()
            {
                data.elem.count   = 0;
                data.elem.itemExtra = NULL;
                data.elem.obj       = NULL;
                _DMESSAGE("Cont item init");
            }
        };

        template <bool bInsert>
        EntryFromString GetFromString(std::string_view ModifierSection)
        {
            EntryFromString result;

            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;

            static_assert(bInsert == false, "Cannot insert this element yet");

            NewModifierPos = ModifierSection.find(sPropertiesDelimeter, CurrentPos);

            if (NewModifierPos == NONPOS) {
                _DRTFPError("CONT::No properties for form>>{}", ModifierSection);
                return result;
            }

            auto CurrentForm = GetFormFromStringAndDontCheckForCategory<false>(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos));

            if (!CurrentForm.bValid) {
                return result;
            }

            CurrentPos = NewModifierPos + 1;

            auto Count = GetNumberFromString<std::int32_t>(ModifierSection.substr(CurrentPos, ModifierSection.length() - CurrentPos));

            if (!Count.bSuccess) {
                _DRTFPError("CONT::Cannot convert Rank to a number>>{}", ModifierSection);
                return result;
            }

            result.data.elem.count   = Count.data;
            result.data.elem.obj   = (RE::TESBoundObject*)CurrentForm.data;
            result.bValid            = true;
            _DMESSAGE("new Container elem,formID>>{:08X},count>>{}", result.data.elem.obj->formID, result.data.elem.count);
            return result;
        }

    }


    namespace Factions
    {
        struct EntryFromString
        {
            struct Data
            {
                RE::FACTION_RANK elem;
                std::uint32_t                        iEntryPos = 0;
            };

            bool bValid = false;
            Data data;

            EntryFromString()
            {
                data.elem.faction         = NULL;
                data.elem.rank    = 0;
                data.elem.pad09 = 0;
                data.elem.pad0A =0;
                data.elem.pad0C           = 0;
                _DMESSAGE("Faction rank init");
            }
        };

        template <bool bInsert>
        EntryFromString GetFromString(std::string_view ModifierSection)
        {
            EntryFromString result;

            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;

            static_assert(bInsert == false, "Cannot insert this element yet");

            NewModifierPos = ModifierSection.find(sPropertiesDelimeter, CurrentPos);

            if (NewModifierPos == NONPOS) {
                _DRTFPError("FACT::No properties for form>>{}", ModifierSection);
                return result;
            }

            auto CurrentForm = GetFormFromStringAndCheckForCategory<false>(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos),
                                                                    const_GetTypeFromFormType<RE::TESFaction*>());

            if (!CurrentForm.bValid) {
                return result;
            }

            CurrentPos = NewModifierPos + 1;

            auto Rank = GetNumberFromString<std::uint8_t>(ModifierSection.substr(CurrentPos, ModifierSection.length() - CurrentPos));

            if (!Rank.bSuccess) {
                _DRTFPError("FACT::Cannot convert Rank to a number>>{}", ModifierSection);
                return result;
            }

            result.data.elem.rank = Rank.data;
            result.data.elem.faction = (RE::TESFaction*)CurrentForm.data;
            result.bValid           = true;
            _DMESSAGE("new Faction elem,faction>>{:08X},rank>>{}", result.data.elem.faction->formID, result.data.elem.rank);
            return result;
        }


    }


    namespace StoryManagerQuestNode
    {

        struct EntryFromString
        {
            struct Data
            {
                BGSStoryManagerQuestNode::QuestEntry elem;
                std::uint32_t         iEntryPos = 0;
            };

            bool bValid = false;
            Data data;

            EntryFromString()
            {
                data.elem.HoursUntilReset = 0;
                data.elem.unk             = 0;
                data.elem.quest           = NULL;
                _DMESSAGE("SMQN init");
            }

        };


        template <bool bInsert>
        EntryFromString GetFromString(std::string_view ModifierSection)
        {
            EntryFromString result;

            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;

            NewModifierPos = ModifierSection.find(sPropertiesDelimeter, CurrentPos);

            if (NewModifierPos == NONPOS) {
                _DRTFPError("SMQN::No properties for form>>{}", ModifierSection);
                return result;
            }

            auto CurrentForm= GetFormFromStringAndCheckForCategory<false>(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos), (std::uint8_t)RE::FormType::kQUST);

            if (!CurrentForm.bValid) {
                return result;
            }

            CurrentPos = NewModifierPos + 1;

            NumberFromString<float> Hour{};



            if constexpr (bInsert == true) {

                NewModifierPos = ModifierSection.find(sParametersDelimeter, CurrentPos);

                if (NewModifierPos == NONPOS)
                {
                    _DRTFPError("SMQN::No parameter delimeter _ to specify insert position>>{}", ModifierSection);
                    return result;
                }

                Hour = GetNumberFromString<float>(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos));
            }
            else {
                Hour = GetNumberFromString<float>(ModifierSection.substr(CurrentPos, ModifierSection.length() - CurrentPos));
            }


            if (!Hour.bSuccess) {
                _DRTFPError("SMQN::Cannot convert Hour to a number>>{}", ModifierSection);
                return result;
            }

            if constexpr (bInsert == true)
            {
                CurrentPos = NewModifierPos + 1;

                auto Position = GetNumberFromString<std::uint32_t>(ModifierSection.substr(CurrentPos, ModifierSection.length() - CurrentPos));

                if (!Position.bSuccess) {
                    _DRTFPError("SMQN::Cannot convert Position to float>>{}, Modifier>>{}", ModifierSection,
                              ModifierSection.substr(CurrentPos, ModifierSection.length() - CurrentPos));
                    return result;
                }

                if (Position.data < 0) { //redundant?
                    _DRTFPError("SMQN::Pos for insert is less than zero>>{}, Modifier>>{}", ModifierSection,
                              ModifierSection.substr(CurrentPos, ModifierSection.length() - CurrentPos));
                    return result;
                }

                result.data.iEntryPos = Position.data;
                _DMESSAGE("Setting position for insert>>{}", result.data.iEntryPos);
            }


            result.data.elem.HoursUntilReset = Hour.data;
            result.data.elem.quest = (TESQuestTomm*)CurrentForm.data;
            result.bValid         = true;
            _DMESSAGE("new SMQN entry,quest>>{:08X},hours>>{}", result.data.elem.quest->formID, result.data.elem.HoursUntilReset);
            return result;
        }

    }



    namespace MagicEffect
    {
        template <class FlagRequest>
        static bool _forceinline IsFormFlagSet(RE::EffectSetting* formIN, FlagRequest& iFlagRequest)
        {
            return (std::uint32_t&)formIN->data.flags & iFlagRequest;
        }

        constexpr std::uint32_t GetFlagFromFlagName(unsigned long FlagName)
        {
            switch (FlagName) {
            case sMagicItemFlagHostile:
                return (std::uint32_t)RE::EffectSetting::EffectSettingData::Flag::kHostile;
            case sMagicItemFlagRecover:
                return (std::uint32_t)RE::EffectSetting::EffectSettingData::Flag::kRecover;
            case sMagicItemFlagDetrimental:
                return (std::uint32_t)RE::EffectSetting::EffectSettingData::Flag::kDetrimental;
            case sMagicItemFlagSnapToNavMesh:
                return (std::uint32_t)RE::EffectSetting::EffectSettingData::Flag::kSnapToNavMesh;
            case sMagicItemFlagNoHitEvent:
                return (std::uint32_t)RE::EffectSetting::EffectSettingData::Flag::kNoHitEffect;
            case sMagicItemDispelWithKeywords:
                return (std::uint32_t)RE::EffectSetting::EffectSettingData::Flag::kDispelWithKeywords;
            case sMagicItemNoDuration:
                return (std::uint32_t)RE::EffectSetting::EffectSettingData::Flag::kNoDuration;
            case sMagicItemNoMagnitude:
                return (std::uint32_t)RE::EffectSetting::EffectSettingData::Flag::kNoMagnitude;
            case sMagicItemNoArea:
                return (std::uint32_t)RE::EffectSetting::EffectSettingData::Flag::kNoArea;
            case sMagicItemFXPersist:
                return (std::uint32_t)RE::EffectSetting::EffectSettingData::Flag::kFXPersist;
            case sMagicItemGoryVisuals:
                return (std::uint32_t)RE::EffectSetting::EffectSettingData::Flag::kGoryVisuals;
            case sMagicItemHideInUI:
                return (std::uint32_t)RE::EffectSetting::EffectSettingData::Flag::kHideInUI;
            case sMagicItemNoRecast:
                return (std::uint32_t)RE::EffectSetting::EffectSettingData::Flag::kNoRecast;
            case sMagicItemPowerAffectsMagnitude:
                return (std::uint32_t)RE::EffectSetting::EffectSettingData::Flag::kPowerAffectsMagnitude;
            case sMagicItemPowerAffectsDuration:
                return (std::uint32_t)RE::EffectSetting::EffectSettingData::Flag::kPowerAffectsDuration;
            case sMagicItemPainless:
                return (std::uint32_t)RE::EffectSetting::EffectSettingData::Flag::kPainless;
            case sMagicNoHitEffect:
                return (std::uint32_t)RE::EffectSetting::EffectSettingData::Flag::kNoHitEffect;
            case sMagicNoDeathDispel:
                return (std::uint32_t)RE::EffectSetting::EffectSettingData::Flag::kNoDeathDispel;
            default:
                if (std::is_constant_evaluated()) {
                    throw "Add types to GetFlagFromFlagName function";
                }
                else {
                    _DRTFPError("Unknown flags for Magic Item");
                }
                return 0;
            }
        }

        template <bool bSet>
        void ProcessFlags(std::uint32_t& Flags, unsigned long CurrentModifierValue)
        {
            switch (CurrentModifierValue) {
                _SetOrRemoveFlag(sMagicItemFlagHostile, MagicEffect::GetFlagFromFlagName) _SetOrRemoveFlag(sMagicItemFlagRecover, MagicEffect::GetFlagFromFlagName)
                    _SetOrRemoveFlag(sMagicItemFlagDetrimental, MagicEffect::GetFlagFromFlagName) _SetOrRemoveFlag(sMagicItemFlagSnapToNavMesh, MagicEffect::GetFlagFromFlagName)
                        _SetOrRemoveFlag(sMagicItemFlagNoHitEvent, MagicEffect::GetFlagFromFlagName) _SetOrRemoveFlag(sMagicItemDispelWithKeywords, MagicEffect::GetFlagFromFlagName)
                            _SetOrRemoveFlag(sMagicItemNoDuration, MagicEffect::GetFlagFromFlagName) _SetOrRemoveFlag(sMagicItemNoMagnitude, MagicEffect::GetFlagFromFlagName)
                                _SetOrRemoveFlag(sMagicItemNoArea, MagicEffect::GetFlagFromFlagName) _SetOrRemoveFlag(sMagicItemFXPersist, MagicEffect::GetFlagFromFlagName)
                                    _SetOrRemoveFlag(sMagicItemGoryVisuals, MagicEffect::GetFlagFromFlagName)
                                        _SetOrRemoveFlag(sMagicItemPowerAffectsMagnitude, MagicEffect::GetFlagFromFlagName)
                                            _SetOrRemoveFlag(sMagicItemPowerAffectsDuration, MagicEffect::GetFlagFromFlagName)
                                                _SetOrRemoveFlag(sMagicItemPainless, MagicEffect::GetFlagFromFlagName)
                                                    _SetOrRemoveFlag(sMagicNoHitEffect, MagicEffect::GetFlagFromFlagName)
                                                        _SetOrRemoveFlag(sMagicNoDeathDispel, MagicEffect::GetFlagFromFlagName)




                break;
            }
        }

    }




    namespace Ingestibles
    {

        template <class FlagRequest>
        static bool _forceinline IsFormFlagSet(RE::AlchemyItem* formIN, FlagRequest& iFlagRequest)
        {
            return formIN->data.flags & iFlagRequest;
        }

        constexpr std::uint32_t GetFlagFromFlagName(unsigned long FlagName)
        {
            switch (FlagName) {
            case sIngestibleFlagNoAutoCalc:
                return (std::uint32_t)RE::AlchemyItem::AlchemyFlag::kCostOverride;
            case sIngestibleFlagFoodItem:
                return (std::uint32_t)RE::AlchemyItem::AlchemyFlag::kFoodItem;
            case sIngestibleFlagMedicine:
                return (std::uint32_t)RE::AlchemyItem::AlchemyFlag::kMedicine;
            case sIngestibleFlagPoison:
                return (std::uint32_t)RE::AlchemyItem::AlchemyFlag::kPoison;
            default:
                if (std::is_constant_evaluated()) {
                    throw "Add types to GetFlagFromFlagName function";
                }
                else {
                    _DRTFPError("Unknown flags for Ingestibles");
                }
                return 0;
            }
        }



        template <bool bSet>
        void ProcessFlags(std::uint32_t& Flags, unsigned long CurrentModifierValue)
        {
            switch (CurrentModifierValue) {

                _SetOrRemoveFlag(sIngestibleFlagNoAutoCalc, Ingestibles::GetFlagFromFlagName)
                    _SetOrRemoveFlag(sIngestibleFlagFoodItem, Ingestibles::GetFlagFromFlagName)
                _SetOrRemoveFlag(sIngestibleFlagMedicine, Ingestibles::GetFlagFromFlagName)
                    _SetOrRemoveFlag(sIngestibleFlagPoison, Ingestibles::GetFlagFromFlagName)
            default:
                _DRTFPError("Invalid flag for Ingestibles.");
                break;
            }
        }
    }




    namespace AVMData
    {

        void OutputAVMEntry(RE::AVMData::Entry& entry)
        {
            _DMESSAGE("-----------------outputting entry")
            CheckFormForForMemberValueAndPrintOut(MEMBER(entry.name.c_str()));
            CheckFormForForMemberValueAndPrintOut(MEMBER(entry.texturePath.c_str()));
            CheckFormForForMemberValueAndPrintOut(MEMBER(entry.color.alpha));
            CheckFormForForMemberValueAndPrintOut(MEMBER(entry.color.red));
            CheckFormForForMemberValueAndPrintOut(MEMBER(entry.color.blue));
            CheckFormForForMemberValueAndPrintOut(MEMBER(entry.color.green));
            CheckFormForForMemberValueAndPrintOut(MEMBER(entry.intensity));
            _DMESSAGE("-----------------outputting entry END")
        }

        bool AreTwoEntriesEqualSimpleComplexType(RE::AVMData::Entry& left, RE::AVMData::Entry& right)
        {
            if (strcmp(left.name.c_str(), right.name.c_str()) == 0)
            {
                if (strcmp(left.texturePath.c_str(), right.texturePath.c_str()) == 0)
                {
                    return true;
                }
            }
            return false;
        }

        bool AreTwoEntriesEqualModulationType(RE::AVMData::Entry& left, RE::AVMData::Entry& right)
        {
            if (strcmp(left.name.c_str(), right.name.c_str()) == 0) {
                if (strcmp(left.texturePath.c_str(), right.texturePath.c_str()) == 0) {
                    if (left.color == right.color)
                    {
                        return true;
                    }
                }
            }
            return false;
        }



        struct StoredData
        {
            bool bAffected = false;
            BGSAVMData*   formIn              = NULL;
            int iOriginalEntryCount = 0;
            std::vector<RE::AVMData::Entry> vEntries{};


            void OutputData()
            {
                _DMESSAGE("Outputting for {:08X},bAffected>>{}",formIn->formID, bAffected);

                for (auto it = vEntries.begin(); it != vEntries.end(); it++) {
                    OutputAVMEntry(Iter);
                }
            }

            void ApplyChanges()
            {
                _DMESSAGE("---------------Applying AVDM Changes for {:08X}", formIn->formID);

                if (!vEntries.size())
                {
                    _DMESSAGE("---------------Entries are empty after all changes - cannot apply.")
                    return;
                }



                    auto NewObject = new RE::AVMData::Entry[vEntries.size()];

                    _DMESSAGE("NewObjectAddres>>{:08X}, LastAddress>>{:08X}", (uintptr_t)NewObject, ((uintptr_t)NewObject + sizeof(RE::AVMData::Entry) * vEntries.size()));

                    //_DMESSAGE("test3");
                    int iCount = 0;
                    for (auto it = vEntries.begin(); it != vEntries.end(); it++) {
                        _DMESSAGE("placing {} at {:08X}", iCount, (uintptr_t)&NewObject[iCount]);
                        NewObject[iCount] = Iter;
                        iCount++;
                    }

                    _DMESSAGE("Addresses - First entry>>{:08X},Last entry>>{:08X}", (uintptr_t)NewObject, (uintptr_t)&NewObject[vEntries.size() - 1]);

                    StoredEntries::Entry NewEntry;
                    NewEntry.formIn     = formIn;
                    NewEntry.firstEntry = (uintptr_t)formIn->firstEntry;
                    NewEntry.lastEntry  = (uintptr_t)formIn->lastEntry;
                    NewEntry.lastEntry2 = (uintptr_t)formIn->lastEntry2;


                    // RE::MemoryManager::GetSingleton()->Free(formIn->firstEntry, false);
                    formIn->firstEntry = NewObject;
                    formIn->lastEntry  = &NewObject[vEntries.size()]; // yes, invalid pointer intended
                    formIn->lastEntry2 = formIn->lastEntry;           // wtf is last entry 2


                    NewEntry.NewFirstEntryAddress = (uintptr_t)NewObject;
                    StoredEntries::v_Stored.push_back(NewEntry);


               // _DMESSAGE("test7");
                _DMESSAGE("New  AVDM addresses - First entry>>{:08X},Last entry>>{:08X},Last entry 2>>{:08X}",(uintptr_t)formIn->firstEntry,
                          (uintptr_t)formIn->lastEntry, (uintptr_t)formIn->lastEntry2);
            }


            bool GetEntriesFromForm(BGSAVMData* formIn) {

                _DMESSAGE("Getting entries from form>>{:08X},First entry>>{:08X},Last entry>>{:08X},Last entry 2>>{:08X}", formIn->formID, (uintptr_t)formIn->firstEntry,
                          (uintptr_t)formIn->lastEntry, (uintptr_t)formIn->lastEntry2);



                if (!formIn->firstEntry)
                {
                    _DRTFPError("No first entry in form>>{:08X}", formIn->formID);
                    return true;
                }

                if (!formIn->lastEntry) {
                    _DRTFPError("No last entry in form>>{:08X}. DATA IS NOT VALID - CANNOT EDIT THIS FORM", formIn->formID);
                    return false;
                }

                uintptr_t pDifference = (uintptr_t)formIn->lastEntry - (uintptr_t)formIn->firstEntry;

                if ((uintptr_t)formIn->lastEntry < (uintptr_t)formIn->firstEntry)
                {
                    _DMESSAGE("Last entry is less than first entry - should not happen - CANNOT EDIT THIS FORM>>{:08X}. {:08X} vs {:08X}", formIn->formID,
                              (uintptr_t)formIn->lastEntry,(uintptr_t)formIn->firstEntry);
                    return false;
                }


                float fDifference = pDifference / sizeof(RE::AVMData::Entry);
                _DMESSAGE("Difference between pointers>>{}", fDifference);

                if (!(std::trunc(fDifference) == fDifference))
                {
                    _DMESSAGE("Pointers of entries are messed up - should not happen - CANNOT EDIT THIS FORM>>{:08X}. {:08X} vs {:08X}, diff>>{}", formIn->formID, (uintptr_t)formIn->lastEntry, (uintptr_t)formIn->firstEntry, fDifference);
                    return false;
                }

                int iCount = fDifference;
                vEntries.reserve(iCount + 1);
                iOriginalEntryCount = iCount;

                for (RE::AVMData::Entry* entr = formIn->firstEntry; entr != formIn->lastEntry;) {
                    _DMESSAGE("entry address>>{:08X} ,name>>{}, path>>{}", (uintptr_t)entr, entr->name.c_str(), entr->texturePath.c_str());

                    RE::AVMData::Entry NewEntry;
                    NewEntry.color       = entr->color;
                    NewEntry.intensity   = entr->intensity;
                    NewEntry.name        = entr->name.c_str();
                    NewEntry.texturePath = entr->texturePath.c_str();

                    //RE::BSFixedString newString("Dead");

                    //_DMESSAGE("Address of new string NAME>>{:08X}", (uintptr_t)sTemp.c_str());
                    //_DMESSAGE("Address of new string BSNAME>>{:08X}", (uintptr_t)NewEntry.name.c_str());
                    //_DMESSAGE("Address of new string NEW NEW>>{:08X}", (uintptr_t)newString.c_str());

                    
                    vEntries.push_back(std::move(NewEntry));


                    //vEntries.back().name = sTemp;
                    //vEntries.back().texturePath = sTemp2;

                    entr++;
                }

                _DMESSAGE("Added {} entries from the form>>{:08X}", vEntries.size(), formIn->formID);
                return true;
            }
        };



        std::vector<StoredData> vStored{};

        struct EntryFromString
        {
            bool               bValid = false;
            RE::AVMData::Entry data;

            EntryFromString()
            {
                data.color.red = 0;
                data.color.green = 0;
                data.color.blue = 0;

                data.intensity = 64; // it's 64 in all of the entries in the game.
            }


            void Output() {
                _DMESSAGE("Outputting entry, bValid>>{}", bValid);
                OutputAVMEntry(data);
            }

        };



        EntryFromString GetFromString(std::string_view ModifierSection, std::uint32_t Type)
        {
            EntryFromString result{};

            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;

            int iCount = 0;
            _DMESSAGE("Getting AVMD entry starts from>>{}", ModifierSection);

   
            bool bSimpleOrComplexGroup = false;
            bool bComplexGroup         = false;

            while (NewModifierPos != NONPOS && iCount < 6) {

                if (iCount > 2 && (bSimpleOrComplexGroup))
                {
                    _DMESSAGE("ending loop for simple or complex group");
                    break;
                }

                NewModifierPos = ModifierSection.find(sPropertiesDelimeter, CurrentPos);


                std::string_view sCurrentPart = ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos);

                _DMESSAGE("Current part>>{}", sCurrentPart);

                if (!sCurrentPart.length()) {
                    _DRTFPError("Lenght of current part is 0,Count>>{},string>>{}", iCount, sCurrentPart);
                    return result;
                }

                if (iCount == 0) // Type
                {
                    auto floatResult = GetNumberFromString<std::uint32_t>(sCurrentPart);

                    if (!floatResult.bSuccess) {
                        _DRTFPError("Cannot convert to number from your input>>{}, part>>", ModifierSection, sCurrentPart);
                        return result;
                    }


                    if (Type != floatResult.data)
                    {
                        _DRTFPError("Type from the line {} doesn't correspond with current AVMD type {} - CANNOT ADD.Section>>{}", floatResult.data, Type, ModifierSection);
                        return result;
                    }

                    if (floatResult.data == (std::uint32_t)RE::AVMData::Type::kSimpleGroup || floatResult.data == (std::uint32_t)RE::AVMData::Type::kComplexGroup
                        || floatResult.data == (std::uint32_t)RE::AVMData::Type::kNone)
                    {
                        bSimpleOrComplexGroup = true;


                        //
                        if (floatResult.data == (std::uint32_t)RE::AVMData::Type::kComplexGroup)
                        {
                            bComplexGroup = true;
                        }



                    }
                    else if (floatResult.data == (std::uint32_t)RE::AVMData::Type::kModulation) {
                    }
                    else {
                        _DRTFPError("Type from the line {} doesn't correspond with any known current AVMD types  - CANNOT ADD.Section>>{}", floatResult.data, ModifierSection);
                        return result;
                    }

                    _DMESSAGE("type of entry>>{}", floatResult.data);
       
                }
                else if (iCount == 1) //Name
                {
                    if (sCurrentPart.length() >= iMaxCharCountForValues)
                    {
                        _DRTFPError("Maximum lenght is exceeded for name>>>>{}", ModifierSection);
                        return result;
                    }

                    char TempArr[iMaxCharCountForValues + 1];


                    if (sCurrentPart.at(0) == '\"' && sCurrentPart.at(sCurrentPart.length() -1) == '\"' && sCurrentPart.length() > 2)
                    {
                        FillCharFromModifierStringExceptFirstAndLastSymbol(sCurrentPart, TempArr);
                    }
                    else {
                        FillCharFromModifierString(sCurrentPart, TempArr);
                    }

                    result.data.name = TempArr;
                }
                else if (iCount == 2 && bSimpleOrComplexGroup) // Texture Path(Value)
                {
                    if (sCurrentPart.length() >= iMaxCharCountForValues) {
                        _DRTFPError("Maximum lenght is exceeded for value>>>>{}", ModifierSection);
                        return result;
                    }

                    char TempArr[iMaxCharCountForValues + 1];

                    if (sCurrentPart.at(0) == '\"' && sCurrentPart.at(sCurrentPart.length() - 1) == '\"' && sCurrentPart.length() > 2) {
                        FillCharFromModifierStringExceptFirstAndLastSymbol(sCurrentPart, TempArr);
                    }
                    else {
                        FillCharFromModifierString(sCurrentPart, TempArr);
                    }

                    result.data.texturePath = TempArr;
                }
                else if (iCount >= 2) 
                {
                    std::uint8_t* valToAffect = NULL;

                    auto floatResult = GetNumberFromString<std::uint8_t>(sCurrentPart);

                    if (!floatResult.bSuccess) {
                        _DRTFPError("Cannot convert to number from your input>>{}, part>>", ModifierSection, sCurrentPart);
                        return result;
                    }

                    if (iCount == 2) //R
                    {
                        valToAffect = &result.data.color.red;
                    }
                    else if (iCount == 3)//G
                    {
                        valToAffect = &result.data.color.green;
                    }
                    else if (iCount == 4) // B
                    {
                        valToAffect = &result.data.color.blue;
                    }
                    else if (iCount == 5) // Alpha
                    {
                        valToAffect = &result.data.color.alpha;
                    }

                    if (!valToAffect)
                    {
                        _DRTFPError("No value to affect -SHOULDNT HAPPEN, please report.");
                        return result;
                    }

                    *valToAffect = floatResult.data;
                }

                iCount++;
                CurrentPos = NewModifierPos + 1;
            }


            if (bComplexGroup) //Complex group has these set to 255.
            {
                result.data.color.alpha = 255;
                result.data.color.red = 255;
                result.data.color.blue = 255;
                result.data.color.green = 255;
            }

            result.bValid = true;
            result.Output();
            return result;
        }


        StoredData* GetOrCreateStoredAVMData(BGSAVMData* formIn) {

            for (auto it = vStored.begin(); it != vStored.end(); it++)
            {
                if (Iter.formIn->formID == formIn->formID)
                {
                    _DMESSAGE("Found stored data,formID>>{:08X}", Iter.formIn->formID);
                    return &Iter;
                }
            }

            StoredData NewStoredData{};
            NewStoredData.formIn = formIn;

            if (!NewStoredData.GetEntriesFromForm(formIn))
            {
                _DMESSAGE("DATA NOT VALID - not creating.");
                return NULL;
            }

            vStored.push_back(NewStoredData);
            _DMESSAGE("Created new stored data for formID>>{:08X}", vStored.back().formIn->formID);
            return &vStored.back();
        }



        void AddToArray(StoredData* pData, EntryFromString& NewEntry)
        {
            _DMESSAGE("Adding entry to vector");
            NewEntry.Output();
            pData->vEntries.push_back((std::move(NewEntry.data)));
            pData->bAffected = true;
        }

        void RemoveFromArray(StoredData* pData, EntryFromString& NewEntry)
        {
            if (pData->formIn->type == (std::uint32_t)BGSAVMData::TYPE::kModulation)
            {
                for (auto it = pData->vEntries.begin(); it != pData->vEntries.end(); it++) {
                    if (AreTwoEntriesEqualModulationType(Iter,NewEntry.data)) {
                        pData->vEntries.erase(it);
                        pData->bAffected = true;
                        return;
                    }
                }
            }
            else {
                for (auto it = pData->vEntries.begin(); it != pData->vEntries.end(); it++) {
                    if (AreTwoEntriesEqualSimpleComplexType(Iter, NewEntry.data)) {
                        pData->vEntries.erase(it);
                        pData->bAffected = true;
                        return;
                    }
                }
            }
        }



        void ReplaceInArray(StoredData* pData, EntryFromString& EntryToReplace, EntryFromString& EntryToBeReplacedWith)
        {
            if (pData->formIn->type == (std::uint32_t)BGSAVMData::TYPE::kModulation) {
                for (auto it = pData->vEntries.begin(); it != pData->vEntries.end(); it++) {
                    if (AreTwoEntriesEqualModulationType(Iter, EntryToReplace.data)) {
                        Iter.name = EntryToBeReplacedWith.data.name;
                        Iter.texturePath = EntryToBeReplacedWith.data.texturePath;
                        Iter.color       = EntryToBeReplacedWith.data.color;
                        pData->bAffected = true;
                        return;
                    }
                }
            }
            else {
                for (auto it = pData->vEntries.begin(); it != pData->vEntries.end(); it++) {
                    if (AreTwoEntriesEqualSimpleComplexType(Iter, EntryToReplace.data)) {
                        Iter.name        = EntryToBeReplacedWith.data.name;
                        Iter.texturePath = EntryToBeReplacedWith.data.texturePath;
                        pData->bAffected = true;
                        return;
                    }
                }
            }
        }




        void ProcessReplacing(BGSAVMData* formIn, std::string_view ModifierSection)
        {

            auto pData = GetOrCreateStoredAVMData(formIn);

            if (!pData) {
                _DRTFPError("Critical error - cannot edit form");
                return;
            }

            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;

            NewModifierPos = ModifierSection.find(sArrDelimeter, CurrentPos);

            if (NewModifierPos == NONPOS) {
                _DRTFPError("No comma in>>{}", ModifierSection);
                return;
            }

            auto DecodedObjectOne = GetFromString(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos), formIn->type);

            if (!DecodedObjectOne.bValid) {
                return;
            }

            CurrentPos = NewModifierPos + 1;

            auto DecodedObjectTwo = GetFromString(ModifierSection.substr(CurrentPos, ModifierSection.length() - CurrentPos), formIn->type);

            if (!DecodedObjectTwo.bValid) {
                return;
            }

            ReplaceInArray(pData, DecodedObjectOne, DecodedObjectTwo);
            return;
        }








        template < typename F>
        void AddRemoveForm(BGSAVMData* formIn, std::string_view ModifierSection, F funcProcess)
        {
            auto pData = GetOrCreateStoredAVMData(formIn);

            if (!pData)
            {
                _DRTFPError("Critical error - cannot edit form");
                return;
            }

            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;


            auto DecodedObject = GetFromString(ModifierSection, formIn->type);
            if (!DecodedObject.bValid) {
                _DRTFPError("AVMData - could not extract Decoded object");
                return;
            }
            _DMESSAGE("Decoded object found");

            funcProcess(pData, DecodedObject);

            return;


            //int iCount = 0;

            //for (auto& match : ctre::search_all<"([0-9])+:\"([^\"]*)\":\"([^\"]*)\"">(ModifierSection)) {
            //    iCount++;
            //    _DMESSAGE("Modifier1 FULL>>{}", std::string_view{ match.get<0>() });
            //    _DMESSAGE("Modifier1 type>>{}", std::string_view{ match.get<1>() });
            //    _DMESSAGE("Modifier1 name>>{}", std::string_view{ match.get<2>() });
            //    _DMESSAGE("Modifier1 path>>{}", std::string_view{ match.get<3>() });
            //}

            //_DMESSAGE("Found modifiers>>{}", iCount);

            //size_t CurrentPos     = 0;
            //size_t NewModifierPos = 0;

            //while (NewModifierPos != NONPOS) {
            //    NewModifierPos = ModifierSection.find(sArrDelimeter, CurrentPos);

            //    auto DecodedObject = GetFromString(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos),formIn->type);

            //    CurrentPos         = NewModifierPos + 1;

            //    if (!DecodedObject.bValid) {
            //        continue;
            //    }
            //    _DMESSAGE("Decoded object found");

            //    funcProcess(pData, DecodedObject);
            //}
        }

        void ClearArray(BGSAVMData* formIn)
        {
            auto pData = GetOrCreateStoredAVMData(formIn);

            if (!pData) {
                _DRTFPError("Critical error - cannot edit form");
                return;
            }
            pData->vEntries.clear();
            pData->bAffected = true;
        }

    }


    #ifdef TestingPlugin
    struct StoredParamType
        {

            std::vector<std::string> Names;
            std::uint32_t paramType;
            std::string   FunctionName{};
        };

        std::vector<StoredParamType> StoredParamTypes;
        std::string                  CurrentFunction{};
    #endif 





    namespace Condition
    {


                std::unordered_map<std::string_view, int> RunObObjectMap = {
                {        "Subject",           RTFP::CONDITIONITEMOBJECT::kSelf},
                {         "Target",         RTFP::CONDITIONITEMOBJECT::kTarget},
                {      "Reference",                            UINT8_MAX - 1},
                {   "CombatTarget",   RTFP::CONDITIONITEMOBJECT::kCombatTarget},
                {"LinkedReference",      RTFP::CONDITIONITEMOBJECT::kLinkedRef},
                {     "QuestAlias",     RTFP::CONDITIONITEMOBJECT::kQuestAlias},
                {    "PackageData",       RTFP::CONDITIONITEMOBJECT::kPackData},
                {      "EventData",      RTFP::CONDITIONITEMOBJECT::kEventData},
                {  "CommandTarget",  RTFP::CONDITIONITEMOBJECT::kCommandTarget},
                { "EventCameraRef", RTFP::CONDITIONITEMOBJECT::kEventCameraRef},
                {       "MyKiller",       RTFP::CONDITIONITEMOBJECT::kMyKiller},
                {    "Player Ship",     RTFP::CONDITIONITEMOBJECT::kPlayerShip}
            };

            std::string GetRunOnObjectAsString(std::uint8_t ID)
            {
            for (auto& object : RunObObjectMap) {
                if (object.second == ID) {
                    return (std::string)object.first;
                }
            }
            return "UNIDENTFIFIED";
            }

            std::uint8_t GetRunOnObject(std::string_view ModifierSection)
            {
            auto result = RunObObjectMap.find(ModifierSection);

            if (result == RunObObjectMap.end()) {
                _DRTFPError("Invalid operator>>{}", ModifierSection);
                return UINT8_MAX;
            }

            if (result->second == UINT8_MAX - 1) {
                _DRTFPError("References are not supported atm.");
                return UINT8_MAX;
            }

            return result->second;
            }







        enum ParamType {
            kString                      = 0,
            kCount                       = 1,
            kFloat                       = 2,
            kObjectID                    = 3,
            kObjectReferenceID           = 4,
            kActorValue                 = 5,
            kActor                       = 6,
            kSpellItem                  = 7,
            kAxis                        = 8,
            kCell                        = 9,
            kAnimationGroup             = 10,
            kMagicItem              = 11,
            kTopic                       = 13,
            kQuest                       = 14,
            kRace                        = 15,
            kClass                       = 16,
            kFaction                     = 17,
            kSex                         = 18,
            kGlobal                      = 19,
            kFurniture                   = 20,
            kObjectID2                    = 21,
            kStage                       = 23,
            kMapMarker                = 24,
            kActorBase                  = 25,
            kContainer         = 26,
            kWorldSpace                  = 27,
            kCrimeType                  = 28,
            kPackage                     = 29,
            kCombatStyle     = 30,
            kMagicEffect              = 31,
            kFormType                = 32,
            kWeatherID                  = 33,
            kOwner            = 35,
            kEffectShaderID            = 36,
            kFormList          = 37,
            kPerk                        = 39,
            kNote                        = 40,
            kMiscellaneousStat    = 41,
            kImagespaceModifierID      = 42,
            kImageSpace                  = 43,
            kEventFunction              = 46,
            kEventMember                = 47,
            kData             = 48,
            kVoiceType                   = 49,
            kIdleForm                   = 50,
            kMessage                     = 51,
            kObjectID3                    = 52,
            kAlignment                   = 53,
            kEquipType                   = 54,
            kObjectID4                    = 55,
            kMusic                       = 56,
            kCriticalStage               = 57,
            kKeyword                     = 58,
            kRefType                     = 59,
            kLocation                    = 60,
            kObjectID5                    = 61,
            kQuestAlias                  = 62,
            kPrimitive                   = 63,
            kScene                       = 66,
            kSource            = 67,
            kAssociationType             = 68,
            kWardState                  = 69,
            kPackageData  = 70,
            kPackageData2        = 71,
            kPapyrusVariableName       = 73,
            kReferenceEffect     = 74,
            kPackageData3       = 75,
            kKnowableForm               = 77,
            kRegion                      = 78,
            kAction                      = 79,
            kMovementSelectIdleFromState = 80,
            kMovementSelectIdleToState   = 81,
            kPapyrusScript              = 82,
            kDamageType                = 83,
            kAction1                      = 84,
            kKeyword2                     = 85,
            kFurnitureEntryType        = 86,
            kSpeechChallenge   = 87,
            kAcousticspace       = 88,
            kMovementType        = 89,
            kConditionForm        = 90,
            kBGSSnapNode                 = 91,
            kCelestialBody             = 92,
            kBiomeMask             = 93,
            kResearchProject          = 94,
            kPerkCategory         = 95,
            kPerkSkillGroup            = 96,
            kComparisonOperator         = 97,
            kCause                       = 98,
            kReverbForm     = 99,
            kReactionType               = 100,
            kLimbCategory           = 101,
            kPronoun                     = 102,
            kResource                    = 103,
            //kUnk                   = 3789937112,
        };


        enum ParamTypeRTFP
        {
            kParamNone = 0,
            kParamNoParams,
            kParamCantFindParam,
            kParamString,
            kFormOrRef,
            kParamInt,
            kParamFloat
        };

        std::unordered_map<std::uint32_t, int> ParamMapAr = {
            {ParamType::kString, ParamTypeRTFP::kParamString},
            {ParamType::kCount,    ParamTypeRTFP::kParamInt},
            {ParamType::kFloat,  ParamTypeRTFP::kParamFloat},
            {ParamType::kObjectID, ParamTypeRTFP::kFormOrRef},
            {ParamType::kObjectReferenceID, ParamTypeRTFP::kFormOrRef},
            {ParamType::kActorValue, ParamTypeRTFP::kFormOrRef},
            {ParamType::kActor, ParamTypeRTFP::kFormOrRef},
            {ParamType::kSpellItem, ParamTypeRTFP::kFormOrRef},
            {ParamType::kAxis, ParamTypeRTFP::kParamInt}, ///////////////////////////?
            {ParamType::kCell, ParamTypeRTFP::kFormOrRef},
            {ParamType::kAnimationGroup, ParamTypeRTFP::kFormOrRef},
            {ParamType::kMagicItem, ParamTypeRTFP::kFormOrRef},
            {ParamType::kTopic, ParamTypeRTFP::kFormOrRef},
            {ParamType::kQuest, ParamTypeRTFP::kFormOrRef},
            {ParamType::kRace, ParamTypeRTFP::kFormOrRef},
            {ParamType::kClass, ParamTypeRTFP::kFormOrRef},
            {ParamType::kFaction, ParamTypeRTFP::kFormOrRef},
            {ParamType::kSex, ParamTypeRTFP::kFormOrRef},
            {ParamType::kGlobal, ParamTypeRTFP::kFormOrRef},
            {ParamType::kFurniture, ParamTypeRTFP::kFormOrRef},
            {ParamType::kObjectID2, ParamTypeRTFP::kFormOrRef},
            {ParamType::kStage, ParamTypeRTFP::kParamInt},
            {ParamType::kMapMarker, ParamTypeRTFP::kFormOrRef},
            {ParamType::kActorBase, ParamTypeRTFP::kFormOrRef},
            {ParamType::kContainer, ParamTypeRTFP::kFormOrRef},
            {ParamType::kWorldSpace, ParamTypeRTFP::kFormOrRef},
            {ParamType::kCrimeType, ParamTypeRTFP::kParamInt},
            {ParamType::kPackage, ParamTypeRTFP::kFormOrRef},
            {ParamType::kCombatStyle, ParamTypeRTFP::kFormOrRef},
            {ParamType::kMagicEffect, ParamTypeRTFP::kFormOrRef},
            {ParamType::kFormType, ParamTypeRTFP::kParamInt},
            {ParamType::kWeatherID, ParamTypeRTFP::kFormOrRef},
            {ParamType::kOwner, ParamTypeRTFP::kFormOrRef},
            {ParamType::kEffectShaderID, ParamTypeRTFP::kFormOrRef},
            {ParamType::kFormList, ParamTypeRTFP::kFormOrRef},
            {ParamType::kPerk, ParamTypeRTFP::kFormOrRef},
            {ParamType::kNote, ParamTypeRTFP::kFormOrRef},
            {ParamType::kMiscellaneousStat, ParamTypeRTFP::kFormOrRef},
            {ParamType::kImagespaceModifierID, ParamTypeRTFP::kFormOrRef},
            {ParamType::kImageSpace, ParamTypeRTFP::kFormOrRef},
            {ParamType::kEventFunction, ParamTypeRTFP::kParamInt},
            {ParamType::kEventMember, ParamTypeRTFP::kFormOrRef},
            {ParamType::kData, ParamTypeRTFP::kFormOrRef},
            {ParamType::kVoiceType, ParamTypeRTFP::kFormOrRef},
            {ParamType::kIdleForm, ParamTypeRTFP::kFormOrRef},
            {ParamType::kMessage, ParamTypeRTFP::kFormOrRef},
            {ParamType::kObjectID3, ParamTypeRTFP::kFormOrRef},
            {ParamType::kAlignment, ParamTypeRTFP::kParamInt},
            {ParamType::kEquipType, ParamTypeRTFP::kFormOrRef},
            {ParamType::kObjectID4, ParamTypeRTFP::kFormOrRef},
            {ParamType::kMusic, ParamTypeRTFP::kFormOrRef},
            {ParamType::kCriticalStage, ParamTypeRTFP::kFormOrRef},
            {ParamType::kKeyword, ParamTypeRTFP::kFormOrRef},
            {ParamType::kRefType, ParamTypeRTFP::kFormOrRef},
            {ParamType::kLocation, ParamTypeRTFP::kFormOrRef},
            {ParamType::kObjectID, ParamTypeRTFP::kFormOrRef},
            {ParamType::kQuestAlias, ParamTypeRTFP::kParamInt},
            {ParamType::kPrimitive, ParamTypeRTFP::kFormOrRef},
            {ParamType::kScene, ParamTypeRTFP::kParamInt},
            {ParamType::kSource, ParamTypeRTFP::kFormOrRef},
            {ParamType::kAssociationType, ParamTypeRTFP::kFormOrRef},
            {ParamType::kWardState, ParamTypeRTFP::kFormOrRef},
            {ParamType::kPackageData, ParamTypeRTFP::kFormOrRef},
            {ParamType::kPackageData, ParamTypeRTFP::kFormOrRef},
            {ParamType::kPapyrusVariableName, ParamTypeRTFP::kParamString},
            {ParamType::kReferenceEffect, ParamTypeRTFP::kFormOrRef},
            {ParamType::kPackageData, ParamTypeRTFP::kFormOrRef},
            {ParamType::kKnowableForm, ParamTypeRTFP::kFormOrRef},
            {ParamType::kRegion, ParamTypeRTFP::kFormOrRef},
            {ParamType::kAction, ParamTypeRTFP::kFormOrRef},
            {ParamType::kMovementSelectIdleFromState, ParamTypeRTFP::kFormOrRef},
            {ParamType::kMovementSelectIdleToState, ParamTypeRTFP::kFormOrRef},
            {ParamType::kPapyrusScript, ParamTypeRTFP::kFormOrRef},
            {ParamType::kDamageType, ParamTypeRTFP::kFormOrRef},
            {ParamType::kAction, ParamTypeRTFP::kFormOrRef},
            {ParamType::kKeyword, ParamTypeRTFP::kFormOrRef},
            {ParamType::kFurnitureEntryType, ParamTypeRTFP::kFormOrRef},
            {ParamType::kSpeechChallenge, ParamTypeRTFP::kFormOrRef},
            {ParamType::kAcousticspace, ParamTypeRTFP::kFormOrRef},
            {ParamType::kMovementType, ParamTypeRTFP::kParamInt},
            {ParamType::kConditionForm, ParamTypeRTFP::kFormOrRef},
            {ParamType::kBGSSnapNode, ParamTypeRTFP::kFormOrRef},
            {ParamType::kCelestialBody, ParamTypeRTFP::kFormOrRef},
            {ParamType::kBiomeMask, ParamTypeRTFP::kParamInt},
            {ParamType::kResearchProject, ParamTypeRTFP::kFormOrRef},
            {ParamType::kPerkCategory, ParamTypeRTFP::kFormOrRef},
            {ParamType::kPerkSkillGroup, ParamTypeRTFP::kFormOrRef},
            {ParamType::kComparisonOperator, ParamTypeRTFP::kFormOrRef},
            {ParamType::kCause , ParamTypeRTFP::kParamInt},
            {ParamType::kReverbForm, ParamTypeRTFP::kFormOrRef},
            {ParamType::kReactionType, ParamTypeRTFP::kFormOrRef},
            {ParamType::kLimbCategory, ParamTypeRTFP::kParamInt},
            {ParamType::kPronoun, ParamTypeRTFP::kParamInt},
            {ParamType::kResource, ParamTypeRTFP::kFormOrRef},
            //{ParamType::kUnk, ParamTypeRTFP::kFormOrRef}
        };
 






        int GetParamTypeFromFunction(RE::SCRIPT_FUNCTION* func, int iParamCount)
        {

            _DMESSAGE("GetParamTypeFromFunction, Num params>>{},iParamCount>>{}", func->numParams, iParamCount);

            if (!func->numParams) {
                return ParamTypeRTFP::kParamNoParams;
            }

            if (iParamCount >= func->numParams) {
                _DMESSAGE("param exceeds NumParams of the function>>{}", func->numParams);
                return ParamTypeRTFP::kParamNoParams;
            }

            if (!func->params) {
                _DMESSAGE("Params are NULL");
                return ParamTypeRTFP::kParamNoParams;
            }

            _DMESSAGE("Param type from script>>{}", func->params[iParamCount].paramType);

            auto ParamType = ParamMapAr.find(func->params[iParamCount].paramType);

            if (ParamType == ParamMapAr.end())
            {
                _DRTFPError("CANNOT FIND PARAMETER type in the array");
                return ParamTypeRTFP::kParamCantFindParam;
            }

            _DMESSAGE("Param type is>>{}", ParamType->second);
            return ParamType->second;
        }

        struct FunctionInfo
        {
            std::uint16_t ID;
            RE::SCRIPT_FUNCTION* func;
        };

        std::map<std::string_view, FunctionInfo> funcs{};



        FunctionInfo* GetFunctionInfoByName(std::string_view name)
        {
            auto command = funcs.find(name);

            if (command == funcs.end()) {
                return NULL;
            }

            return &command->second;
        }

        FunctionInfo* GetFunctionInfoByID(std::uint16_t ID)
        {
            for (auto& command : funcs) {
                if (command.second.ID == ID) {
                    return &command.second;
                }
            }
            return NULL;
        }

        void GetScriptFunctions()
        {
            if (funcs.size()) {
                return;
            }

            std::uint16_t iCount = 0;
            for (auto& command : RE::Script::GetScriptCommands()) {
                if (command.functionName) {
                    if (strlen(command.functionName)) // One of the functions had name but with lenght of 0
                    {
                        FunctionInfo NewInfo;
                        NewInfo.ID = iCount;
                        NewInfo.func = &command;

                        funcs.emplace(command.functionName, std::move(NewInfo));
                    }

                }

                iCount++;
            }

            _DMESSAGE("Found {} script functions", funcs.size());

            if (bDebugMode) {
                _DMESSAGE("Outputting Script functions.");
                // for (auto& func : funcs) {
                //     _MESSAGE("Function>>{},Count>>{}, lenght>>{}", func.first, func.second, func.first.length());
                // }
                //_DMESSAGE("Outputting Script functions END.");
            }

            //_DMESSAGE("ID of GetDistance is {},", GetIDOfFunctionByName("GetDistance"));
            //_DMESSAGE("ID of GetDistanceNONEXIST is {},", GetIDOfFunctionByName("GetDistanceNONEXIST"));
        }



        //23 for
        bool IsFunctionParameterString(RE::SCRIPT_FUNCTION* func ,int iParamCount)
        {
            _DMESSAGE("Num params>>{},iParamCount>>{}", func->numParams, iParamCount);

            if (!func->numParams)
            {
                return false;
            }

            if (iParamCount >= func->numParams)
            {
                _DMESSAGE("param exceeds NumParams of the function>>{}", func->numParams);
                return false;
            }

            if (!func->params)
            {
                _DMESSAGE("Params are NULL");
                return false;
            }


            //if (!&func->params[iParamCount])
            //{
            //    _DMESSAGE("Params count is NULL");
            //    return false;
            //}

           #ifdef TestingPlugin
            StoredParamType* StoredParam = NULL;
            for (auto& param : StoredParamTypes) {
                if (param.paramType == func->params[iParamCount].paramType) {
                    StoredParam = &param;
                    break;
                }
            }


            if (StoredParam)
            {

                if (func->params[iParamCount].paramName)
                {
                    bool bFound = false;
                    for (auto& name : StoredParam->Names) {
                        if (name == func->params[iParamCount].paramName) {
                            bFound = true;
                            break;
                        }
                    }

                    if (!bFound)
                    {
                        StoredParam->Names.push_back(func->params[iParamCount].paramName);
                    }

                }

            }
            else {

                StoredParamType NewParam;
                NewParam.paramType    = func->params[iParamCount].paramType;
                NewParam.Names.push_back(func->params[iParamCount].paramName);
                NewParam.FunctionName = CurrentFunction;
                StoredParamTypes.push_back(NewParam);
            }



           #endif 


            _DMESSAGE("Param>>{},Type>>{}", func->params[iParamCount].paramName, func->params[iParamCount].paramType);

            if (func->params[iParamCount].paramType == 73)
            {
                return true;
            }
            else {
                return false;
            }


        }

        void OutputTESConditionItem(RTFP::TESConditionItem* Curr)
        {
            GetScriptFunctions();

            int iCount = 0;
            while (Curr) {

                _DMESSAGE("New condition,pos>>{},unk0>>{:08X},ObjectRefHandle>>{:08X},address>>{:08X}", iCount, (uintptr_t)Curr->unk0, (uintptr_t)Curr->ObjectRefHandle,
                          (uintptr_t)Curr);
                iCount++;

                std::string CompareOperator{};


                if (Curr->compareOperators == RTFP::CompareOperators::k_EqualTo) {
                    CompareOperator = "=";
                    //_DMESSAGE("Compare operator is EQUAL TO");
                }
                else if (Curr->compareOperators == RTFP::CompareOperators::k_NotEqualTo) {
                    CompareOperator = "!=";
                    //_DMESSAGE("Compare operator is NOT EQUAL TO");
                }
                else if (Curr->compareOperators == RTFP::CompareOperators::k_GreaterThan) {
                    CompareOperator = ">";
                    //_DMESSAGE("Compare operator is GREATER THAN");
                }
                else if (Curr->compareOperators == RTFP::CompareOperators::k_GreaterThanEqual) {
                    CompareOperator = ">=";
                    //_DMESSAGE("Compare operator is GREATER THAN EQUAL TO");
                }
                else if (Curr->compareOperators == RTFP::CompareOperators::kLessThan) {
                    CompareOperator = "<";
                    //_DMESSAGE("Compare operator is LESS THAN");
                }
                else if (Curr->compareOperators == RTFP::CompareOperators::kLessThanEqual) {
                    CompareOperator = "<=";
                    //_DMESSAGE("Compare operator is LESS THAN EQUAL");
                }
                else {
                    //_DMESSAGE("Compare operator is UNDEFINED >>{}", (std::uint8_t)Curr->compareOperators);
                }

                std::string sFunctionAsText = GetRunOnObjectAsString(Curr->object);


                _DMESSAGE("OR>>{},AliasParam>>{},ValueGlobal>>{},PackDataParam>>{},SwapSubjAndTarget>>{},Object>>{}({})", (std::uint8_t)Curr->compareOr,
                          (std::uint8_t)Curr->aliasParams, (std::uint8_t)Curr->valueIsGlobal, (std::uint8_t)Curr->packDataParams, (std::uint8_t)Curr->swapsSubjectAndTarget,
                          (std::uint8_t)Curr->object, sFunctionAsText);


                

                auto funcInfo = GetFunctionInfoByID(Curr->functionID);


                if (funcInfo) {
                    sFunctionAsText += "." + (std::string)funcInfo->func->functionName;

                    _DMESSAGE("Function is>>{}", funcInfo->func->functionName);

                    for (auto i = 0; i < 2; i++)
                    {
                        auto ParameterType = GetParamTypeFromFunction(funcInfo->func, i);

                        if (ParameterType == ParamTypeRTFP::kFormOrRef) {
                            _DMESSAGE("Param {} is a form.",i);
                            CheckFormForForMemberFormAndPrintOut(MEMBER(Curr->params[i].vForm));
                        }
                        else if (ParameterType == ParamTypeRTFP::kParamString) {
                            _DMESSAGE("Param {} is a string.",i);

                            if (Curr->params[i].vString)
                            {
                                _DMESSAGE("string>>{}", Curr->params[i].vString->c_str())
                            }
                            else {
                                _DMESSAGE("string is NULL. If you're reading output for just created condition from RTFP - the string is not yet created. It will be when added to any form.");
                            }

                        }
                        else if (ParameterType == ParamTypeRTFP::kParamInt) {
                            _DMESSAGE("Param {} is a int",i);
                            _DMESSAGE("int>>{}", Curr->params[i].vInt)
                        }
                        else if (ParameterType == ParamTypeRTFP::kParamNoParams) {
                            _DMESSAGE("Function doesn't have param {}",i);
                        }
                        else if (ParameterType == ParamTypeRTFP::kParamCantFindParam) {
                            _DMESSAGE("Invalid param type for {}. Please report to TommInfinite", i);
                        }
                        else if (ParameterType == ParamTypeRTFP::kParamFloat) {
                                _DMESSAGE("Param {} is a float", i);
                                _DMESSAGE("First param is float>>{}", Curr->params[i].vFloat)
                        }
                        else {
                            _DMESSAGE("PARAM 1 IS UNDEFINED>>{}", ParameterType);
                        }
                    }

                }
                else {
                    _DMESSAGE("Could not find function info by ID");
                    sFunctionAsText += "." + (std::string)"UNKFunction";
                }

                sFunctionAsText += " ";
                sFunctionAsText += CompareOperator + " ";

                if (Curr->valueIsGlobal) {


                    if (Curr->global) {
                        sFunctionAsText += std::to_string(Curr->global->value);
                        _DMESSAGE("Global formID>>{:08X}", Curr->global->formID);
                        CheckFormForForMemberValueAndPrintOut(MEMBER(Curr->global->value));
                    }
                    else {
                        sFunctionAsText += "NULL";
                        _DMESSAGE("Global Variable form is NULL.");
                    }

                    sFunctionAsText += "(GLOBAL)";
                }
                else {
                    sFunctionAsText += std::to_string(Curr->value);
                    _DMESSAGE("Value is float >>{}", Curr->value);
                }

                if (Curr->ObjectRefHandle) {
                    _DMESSAGE("ObjectRefHandle>>{:08X}", Curr->ObjectRefHandle);

                    // RE::NiPointer<RE::TESForm> FormResult;
                    // GetSmartPointer(Curr->ObjectRefHandle, FormResult);

                    // if (FormResult)
                    //{
                    //     // _DMESSAGE("form valid>>{:08X}", FormResult);
                    // }
                    // else {
                    //      _DMESSAGE("Form is not valid");
                    // }

                    // auto HandleMine = CreateHandle(FormResult);
                    //_DMESSAGE("Handle from form>>{:08X}", HandleMine);
                }

                _DMESSAGE("Function as text>>{}", sFunctionAsText);


                if (iCount > 100) {
                    _DRTFPError("No more than 100 entries can be outputted.Please report to TommInfinite.");
                    break;
                }

                if (!Curr->next) {
                    _DMESSAGE("Last entry");
                    break;
                }
                Curr = Curr->next;
            }
        }



        struct TESConditionItemFromString
        {

            struct StoredText {
                bool bTextValid = false;
                char Text[iMaxCharCountForValues + 1]{};
            };

            RTFP::TESConditionItem data;
            bool                 bValid = false;

            StoredText storedText[2];
        };

        struct TESConditionFromString {
            bool             bValid = false;
            std::string                             name{};
            RE::TESCondition data;
            std::vector<TESConditionItemFromString> tesCondItems{};

            TESConditionFromString()
            {
                data.unk0 = 0;
                data.head = NULL;
            }
        };

        std::vector<TESConditionFromString> tesConditionsFromString;

        TESConditionFromString* GetTESConditionByName(std::string_view sName)
        {
            for (auto& TESCond : tesConditionsFromString)
            {
                if (TESCond.name == sName)
                {
                    return &TESCond;
                }
            }


            return NULL;
        }


        void CleanTESConditionItem(RTFP::TESConditionItem& NewItem)
        {
            NewItem.unk0                  = 0;
            NewItem.next                  = 0;
            NewItem.value                 = 0;
            NewItem.ObjectRefHandle       = NULL;
            NewItem.ObjectRefHandlePAD    = NULL;
            NewItem.functionID            = 0;
            NewItem.params[0].vForm       = NULL;
            NewItem.params[1].vForm       = NULL;
            NewItem.compareOr             = 0;
            NewItem.aliasParams           = 0;
            NewItem.valueIsGlobal         = 0;
            NewItem.packDataParams        = 0;
            NewItem.swapsSubjectAndTarget = 0;
            NewItem.compareOperators      = RTFP::CompareOperators::k_EqualTo;
            NewItem.object                = RTFP::CONDITIONITEMOBJECT::kSelf;
        }



        std::uint8_t GetCompareOperator(std::string_view ModifierSection) {

            if (ModifierSection == "=") {

                return RTFP::CompareOperators::k_EqualTo;
            }
            else if (ModifierSection == "!")
            {
                return RTFP::CompareOperators::k_NotEqualTo;
            }
            else if (ModifierSection == ">=") {
                return RTFP::CompareOperators::k_GreaterThanEqual;
            }
            else if (ModifierSection == "<") {
                return RTFP::CompareOperators::kLessThan;
            }
            else if (ModifierSection == "<=") {
                return RTFP::CompareOperators::kLessThanEqual;
            }
            else {
                return UINT8_MAX;
            }

        }





        void ProcessAndSetFlag(TESConditionItemFromString& result, std::string_view ModifierSection)
        {
            if (ModifierSection == "or")
            {
                result.data.compareOr = true;
            }
            else if (ModifierSection == "use_pdata")
            {
                result.data.packDataParams = true;
            }
            else if (ModifierSection == "use_alias") {
                result.data.aliasParams = true;
            }
            else if (ModifierSection == "swap_subtar") {
                result.data.swapsSubjectAndTarget = true;
            }
            else {
                if (ModifierSection.length()) {
                    _DRTFPError("Current Function flag is not supported>>{}", ModifierSection);
                }
            }

        }




        //Subject:GetRandomPercent:<=:1:~:~:or:use_alias|
        TESConditionItemFromString GetTESConditionItemFromString(std::string_view ModifierSection)
        {
            TESConditionItemFromString result;
            CleanTESConditionItem(result.data);

            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;

            NewModifierPos = ModifierSection.find(sPropertiesDelimeter, CurrentPos);

            if (NewModifierPos == NONPOS) {
                _DRTFPError("COND::No properties for RunOnObject>>{}", ModifierSection);
                return result;
            }

            result.data.object = static_cast<RTFP::CONDITIONITEMOBJECT>(GetRunOnObject(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos)));

            if (result.data.object == UINT8_MAX) {
                _DRTFPError("Invalid RunOn object>>{}", ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos));
                return result;
            }
            _DMESSAGE("Run on object>>{}", (std::uint8_t)result.data.object);

            CurrentPos     = NewModifierPos + 1;
            NewModifierPos = ModifierSection.find(sPropertiesDelimeter, CurrentPos);

            if (NewModifierPos == NONPOS) {
                _DRTFPError("COND::No properties for function>>{}", ModifierSection);
                return result;
            }


            auto funcInfo = GetFunctionInfoByName(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos));

            if (!funcInfo)
            {
                _DRTFPError("Specified function doesn't exist>>{}", ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos));
                return result;
            }

            result.data.functionID = funcInfo->ID;

            CurrentPos = NewModifierPos + 1;
            NewModifierPos = ModifierSection.find(sPropertiesDelimeter, CurrentPos);

            if (NewModifierPos == NONPOS) {
                _DRTFPError("COND::No properties for Compare operator>>{}", ModifierSection);
                return result;
            }

            result.data.compareOperators = GetCompareOperator(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos));

            if (result.data.compareOperators == UINT8_MAX) {
                _DRTFPError("Invalid Compare operator>>{}", ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos));
                return result;
            }

            CurrentPos = NewModifierPos + 1;
            NewModifierPos = ModifierSection.find(sPropertiesDelimeter, CurrentPos);

            if (NewModifierPos == NONPOS) {
                _DRTFPError("COND::No properties for value>>{}", ModifierSection);
                return result;
            }

            auto ValuePart = ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos);

            if (!ValuePart.length()) {
                _DRTFPError("Value part is empty>>{}", ModifierSection);
                return result;
            }

            if (isdigit(ValuePart.at(0)))
            {
                auto floatResult = GetNumberFromString<float>(ValuePart);

                if (!floatResult.bSuccess) {
                    _DRTFPError("Cannot convert to number from your input>>{}, part>>", ModifierSection, ValuePart);
                    return result;
                }
                result.data.value = floatResult.data;

            }
            else {
                auto Global = GetFormFromStringAndCheckForCategory<false>(ValuePart, const_GetTypeFromFormType<RE::TESGlobal*>());

                if (!Global.bValid)
                {
                    _DMESSAGE("Cannot build formID from your value>>{}, part>>", ModifierSection, ValuePart);
                    return result;
                }

                result.data.global = (RE::TESGlobal*)Global.data;
                result.data.valueIsGlobal = true;
            }


            bool NoMoreProperties = false;
            for (auto i = 0; i < 2; i++)
            {
                CurrentPos = NewModifierPos + 1;
                NewModifierPos = ModifierSection.find(sPropertiesDelimeter, CurrentPos);

                auto QuotesOpenPos = ModifierSection.find(sQuotes, CurrentPos);
                _DMESSAGE("New modifier pos>>{},QuotesOpenPos>>{}", NewModifierPos, QuotesOpenPos);

                if (QuotesOpenPos != NONPOS)
                {
                   _DMESSAGE("Detected opening quotes at>>{}.", QuotesOpenPos);

                        auto QuotesClosedPos = ModifierSection.find(sQuotes, QuotesOpenPos + 1);
                        if (QuotesOpenPos != NONPOS)
                        {
                            _DMESSAGE("Detected closing quotes at>>{}. : pos is >>{}", QuotesClosedPos, NewModifierPos);
                            if (NewModifierPos > QuotesOpenPos && NewModifierPos < QuotesClosedPos)
                            {
                                _DMESSAGE("Next modifier is in quotes - looking for the next one.");
                                NewModifierPos = ModifierSection.find(sPropertiesDelimeter, QuotesClosedPos);
                                _DMESSAGE("Next : delimeter>>>{}", NewModifierPos);

                            }
                        }
                        else {
                            _DRTFPError("Quotes are not closed in >>{} param. <<{}>>", i, ModifierSection);
                            return result;
                        }
                }



                if (i == 0)
                {
                    if (NewModifierPos == NONPOS) {
                            _DRTFPError("COND::No properties for  form{} >>{}", std::to_string(i + 1), ModifierSection);
                        return result;
                    }
                }
                else {
                    if (NewModifierPos == NONPOS)
                    {
                        _DMESSAGE("no more properties.");
                        NoMoreProperties = true;
                    }
                }

                std::string_view CurrentValue = ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos);

                if (!CurrentValue.length()) {

                    _DRTFPError("nothing specified for the value>>{},>>{}", std::to_string(i + 1), ModifierSection);
                    return result;
                }


                auto ParamType = GetParamTypeFromFunction(funcInfo->func, i);

                if (ParamType == ParamTypeRTFP::kFormOrRef)
                {
                    auto CurrentForm = GetFormFromStringAndDontCheckForCategory<true>(CurrentValue);

                    if (!CurrentForm.bValid) {
                        _DMESSAGE("Cannot build form {} from>>{}", std::to_string(i), CurrentValue);
                        return result;
                    }

                    result.data.params[i].vForm = CurrentForm.data;
                    _DMESSAGE("value is a form>>{:08X}", result.data.params[i].vForm->formID);

                }
                else if (ParamType == ParamTypeRTFP::kParamString)
                {
                     if (CurrentValue.at(CurrentValue.length() - 1) != '"') {
                        _DRTFPError("Function {} requires string for parameter {}. Strings ARE NOT SUPPORTED AT THE MOMENT.", funcInfo->func->functionName, std::to_string(i + 1),
                                   ModifierSection);
                         return result;
                     }

                    //if (CurrentValue.length() > iMaxCharCountForValues) {
                    //    _DMESSAGE("Lenght of parameter >>{} is more than {}. This function requires string which should be specified in quotes>>{}", std::to_string(i + 1),
                    //              iMaxCharCountForValues, CurrentValue);
                    //    return result;
                    //}

                    //if (CurrentValue.length() < 2) {
                    //    _DMESSAGE("Lenght of parameter >>{} is less than 2. This function requires string which should be specified in quotes.", std::to_string(i + 1),
                    //              ModifierSection);
                    //    return result;
                    //}

                    //if (CurrentValue.at(0) != '"') {
                    //    _DMESSAGE("Function {} requires string as a parameter {}. Strings should be specified in quotes", funcInfo->func->functionName, std::to_string(i + 1),
                    //              ModifierSection);
                    //    return result;
                    //}

                    //if (CurrentValue.at(CurrentValue.length() - 1) != '"') {
                    //    _DMESSAGE("Function {} requires string for parameter {}. Strings should be specified in quotes", funcInfo->func->functionName, std::to_string(i + 1),
                    //              ModifierSection);
                    //    return result;
                    //}


                    //result.storedText[i].bTextValid = true;
                    //FillCharFromModifierStringExceptFirstAndLastSymbol(CurrentValue, result.storedText[i].Text);
                    //_DMESSAGE("value is a string>>{}.", result.storedText[i].Text);
                }
                else if (ParamType == ParamTypeRTFP::kParamInt) {

                    auto numResult = GetNumberFromString<int>(CurrentValue);

                    if (!numResult.bSuccess)
                    {
                         _DRTFPError("Function {} requires int as a parameter {}. Cannot convert value to a number", funcInfo->func->functionName, std::to_string(i + 1),
                                  ModifierSection);
                        return result;
                    }

                    result.data.params[i].vInt = numResult.data;
                }
                else if (ParamType == ParamTypeRTFP::kParamFloat) {
                    auto numResult = GetNumberFromString<float>(CurrentValue);

                    if (!numResult.bSuccess) {
                        _DRTFPError("Function {} requires float as a parameter {}. Cannot convert value to a number", funcInfo->func->functionName, std::to_string(i + 1),
                                  ModifierSection);
                        return result;
                    }

                    result.data.params[i].vFloat = numResult.data;
                }
                else if (ParamType == ParamTypeRTFP::kParamCantFindParam) {

                        _DRTFPError("Cannot determine type of parameter {} for function {}. Please report to TommInfinite. <<{}>>", std::to_string(i + 1), funcInfo->func->functionName, 
                              ModifierSection);
                    return result;
                }


            }

            if (NoMoreProperties)
            {
                _DMESSAGE("No more properties - returning conditon");
                result.bValid = true;
                return result;
            }


            while (NewModifierPos != NONPOS) {
                CurrentPos     = NewModifierPos + 1;
                NewModifierPos = ModifierSection.find(sPropertiesDelimeter, CurrentPos);
                ProcessAndSetFlag(result,ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos));
            }

            result.bValid = true;
            return result;

        }


        TESConditionFromString GetTESConditionFromString(std::string_view sIn)
        {
            TESConditionFromString result{};

            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;

            while (NewModifierPos != NONPOS) {
                NewModifierPos = sIn.find(sSectionDelimeter, CurrentPos);

                auto DecodedObject = GetTESConditionItemFromString(sIn.substr(CurrentPos, NewModifierPos - CurrentPos));
                CurrentPos         = NewModifierPos + 1;

                if (!DecodedObject.bValid) {
                    _DRTFPError("One of the conditions is not valid.");
                    return result;
                }

                if (bDebugMode)
                {
                    OutputTESConditionItem(&DecodedObject.data);
                }
                result.tesCondItems.push_back(DecodedObject);
            }



            result.bValid = true;
            return result;
        }







        void ProcessConditionLine(std::string_view ConditionName,std::string_view sIn)
        {

            auto Condition = GetTESConditionByName(ConditionName);

            if (Condition)
            {
                _DRTFPError("Condition with that name already exists>>{}", ConditionName);
                return;
            }

            GetScriptFunctions();

            auto result = GetTESConditionFromString(sIn);

            if (!result.bValid)
            {
                _DMESSAGE("condition non valid");
                return;
            }
            result.name = ConditionName;
            _DMESSAGE("Added new condition with name>>{}, entries count>>{}", result.name,result.tesCondItems.size());
            tesConditionsFromString.push_back(std::move(result));
        }



        void AddToTESConditionItemFromArray(RTFP::TESConditionItem*& next, RTFP::TESConditionItem* NewEntries, std::uint32_t size)
        {
            _DMESSAGE("AddToTESConditionItemFromArray starts with size>>{}", size);
            next = NewEntries;
            RTFP::TESConditionItem* CurrentCondItem = next;

            for (auto i = 1; i < size; i++)
            {
                CurrentCondItem->next = &NewEntries[i];
                CurrentCondItem       = CurrentCondItem->next;

                _DMESSAGE("Adding cond>>{}", i);
            }
            _DMESSAGE("Conditions added, count >>{}.", size);
        }

        bool AddConditionToConditionArray(RE::TESCondition& cond, std::string_view ConditionName)
        {
            auto Condition = GetTESConditionByName(ConditionName);

            if (!Condition) {
                _DMESSAGE("Condition with specified name not found>>{}", ConditionName);
                return false;
            }

            
            RTFP::TESConditionItem* NewEntries = new RTFP::TESConditionItem[Condition->tesCondItems.size()];

            std::uint32_t count = 0;
            for (auto& ConditionStored : Condition->tesCondItems)
            {
                NewEntries[count] = ConditionStored.data;

                for (auto i = 0; i < 2; i++)
                {
                    if (ConditionStored.storedText[i].bTextValid)
                    {
                        _DMESSAGE("Creating new string for param {} with text>>{}", i, ConditionStored.storedText[i].Text);
                        NewEntries[count].params[i].vString = new RE::BSFixedString(ConditionStored.storedText[i].Text); //Crashes at Unity.
                        _DMESSAGE("Created");
                    }

                }

                count++;
            }


            //RTFP::TESConditionItem* NewEntry = new RTFP::TESConditionItem(Condition->tesCondItems.at(0).data);

            if (cond.head)
            {
                RTFP::TESConditionItem* Curr = RTFP::AsRTFP(cond.head);

                while (Curr) {

                    if (!Curr->next) {
                        AddToTESConditionItemFromArray(Curr->next, NewEntries, Condition->tesCondItems.size());
                        OutputTESConditionItem(Curr->next);
                        return true;
                    }
                    Curr = Curr->next;
                }
            }
            else {
                RTFP::TESConditionItem* newHead = RTFP::AsRTFP(cond.head);
                AddToTESConditionItemFromArray(newHead, NewEntries,Condition->tesCondItems.size());
                cond.head = reinterpret_cast<RE::TESConditionItem*>(newHead);
                OutputTESConditionItem(newHead);
            }

            
            return true;
        }



        template <typename _FuncProcess>
        void AddRemove(RE::TESCondition& cond, std::string_view& ModifierSection, _FuncProcess funcProcess)
        {
            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;

            while (NewModifierPos != NONPOS) {
                NewModifierPos = ModifierSection.find(sArrDelimeter, CurrentPos);
                funcProcess(cond, ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos));
                CurrentPos = NewModifierPos + 1;
            }
        }




    }



    namespace Message
    {

        template <class FlagRequest>
        static bool _forceinline IsFormFlagSet(RE::BGSMessage* formIN, FlagRequest& iFlagRequest)
        {
            return formIN->flags.underlying() & iFlagRequest;
        }

        constexpr std::uint32_t GetFlagFromFlagName(unsigned long FlagName)
        {
            switch (FlagName) {
            case sMessageFlagMessageBox:
                return (std::uint32_t)RE::BGSMessage::MessageFlag::kMessageBox;
            case sMessageFlagDelayInitialDisplay:
                return (std::uint32_t)RE::BGSMessage::MessageFlag::kInitialDelay;
            default:
                if (std::is_constant_evaluated()) {
                    throw "Add types to GetFlagFromFlagName function";
                }
                else {
                    _DRTFPError("Unknown flags for Message");
                }
                return 0;
            }
        }




        template <bool bSet>
        void ProcessFlags( std::uint32_t& Flags, unsigned long CurrentModifierValue)
        {
            switch (CurrentModifierValue) {
                _SetOrRemoveFlag(sMessageFlagMessageBox, Message::GetFlagFromFlagName)
                _SetOrRemoveFlag(sMessageFlagDelayInitialDisplay, Message::GetFlagFromFlagName)


            default: _DRTFPError("Invalid flag for Message");
                break;
            }
        }


        struct EntryFromString
        {
            struct Data
            {
                RE::BGSMessage::MESSAGEBOX_BUTTON elem;
                std::uint32_t         iEntryPos = 0;
            };

            bool bValid = false;
            Data data;
            

            EntryFromString()
            {
                data.elem.conditions.head = NULL;
                data.elem.conditions.unk0 = 0;
                data.elem.reference       = NULL;
                data.elem.unk08           = 0;
            }


        };




        void AddToArray(RE::BSTArray<RE::BGSMessage::MESSAGEBOX_BUTTON*>& Arr, EntryFromString::Data& EntryToAdd)
        {
            _DMESSAGE("adding message button to array");
            RE::BGSMessage::MESSAGEBOX_BUTTON* NewItem = new RE::BGSMessage::MESSAGEBOX_BUTTON;
            *NewItem = std::move(EntryToAdd.elem);
            _DMESSAGE("adding message button to array 2");
            Arr.push_back(NewItem);
            _DMESSAGE("done");

        }


        EntryFromString GetFromString(std::string_view ModifierSection)
        {
            EntryFromString result;

            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;

            
            NewModifierPos = ModifierSection.find(sPropertiesDelimeter, CurrentPos);

            if (NewModifierPos == NONPOS) {
                _DRTFPError("MSGBUTT::No properties for form>>{}", ModifierSection);
                return result;
            }
            std::string_view ButtonText = ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos);


            if (ButtonText.length() >= iMaxCharCountForValues) {
                _DRTFPError("Maximum lenght is exceeded for button text>>>>{}", ModifierSection);
                return result;
            }
            else if (!ButtonText.length()) {
                _DRTFPError("MSGBUTT:No text for button>>{}", ModifierSection);
                return result;
            }
            else if (ButtonText.length() <3) {
                _DRTFPError("MSGBUTT:Text for button is less than 3>>{}, lenght>>{}", ModifierSection, ButtonText.length());
                return result;
            }
            else if (ButtonText.at(0) != '\"') {
                _DRTFPError("MSGBUTT:First symbol for text is not a quote>>{}", ModifierSection);
                return result;
            }
            else if (ButtonText.at(ButtonText.length() -1) != '\"') {
                _DRTFPError("MSGBUTT:Last symbol for text is not a quote>>{}", ModifierSection);
                return result;
            }

            char TempArr[iMaxCharCountForValues + 1];

            FillCharFromModifierStringExceptFirstAndLastSymbol(ButtonText, TempArr);

            result.data.elem.text = TempArr;

            CurrentPos = NewModifierPos + 1;

            auto CurrentForm = GetFormFromStringAndCheckForCategory<true>(ModifierSection.substr(CurrentPos, ModifierSection.length() - CurrentPos), (std::uint8_t)RE::FormType::kREFR);

            result.data.elem.reference = (RE::TESObjectREFR*)CurrentForm.data;
            result.bValid = true;


            if (result.data.elem.reference)
            {
                _DMESSAGE("New message button text>>{},ref>>{:08X}", result.data.elem.text.c_str(), result.data.elem.reference->formID);
            }
            else {
                _DMESSAGE("New message button text>>{},ref>>NULL", result.data.elem.text.c_str());
            }

            return result;
        }


    }








    namespace EffectItem
    {

        //auto        operator<=>(const EffectItemData&) const                 = default;
        //friend bool operator==(const EffectItemData&, const EffectItemData&) = default;
        //auto        operator<=>(const EffectItem&) const                     = default;
        //friend bool operator==(const EffectItem&, const EffectItem&)         = default;

        bool _forceinline IsEffectDataEqual(RE::EffectItem& d1, RE::EffectItem& d2)
        {
            return d1.effectSetting == d2.effectSetting && d1.data.magnitude == d2.data.magnitude && d1.data.area == d2.data.area && d1.data.duration == d2.data.duration
                   && d1.areaGlobal == d2.areaGlobal && d1.durationGlobal == d2.durationGlobal && d1.magGlobal == d2.magGlobal;
                //&& d1.rawCost == d2.rawCost
                //&& d1.unk30 == d2.unk30 &&
                //d1.unk34 == d2.unk34;
        }

         bool _forceinline IsEffectDataEqualJustCheckForEffect(RE::EffectItem& d1, RE::EffectItem& d2)
        {
            return d1.effectSetting == d2.effectSetting;
        }

        void OutputEffectItem(RE::EffectItem& data)
        {
            _DMESSAGE("--------------------Outputting EffectItemData start.");
            CheckFormForForMemberFormAndPrintOut(MEMBER(data.effectSetting));
            CheckFormForForMemberValueAndPrintOut(MEMBER(data.data.magnitude));
            CheckFormForForMemberValueAndPrintOut(MEMBER(data.data.area));
            CheckFormForForMemberValueAndPrintOut(MEMBER(data.data.duration));
            CheckFormForForMemberFormAndPrintOut(MEMBER(data.magGlobal));
            CheckFormForForMemberFormAndPrintOut(MEMBER(data.areaGlobal));
            CheckFormForForMemberFormAndPrintOut(MEMBER(data.durationGlobal));
            CheckFormForForMemberValueAndPrintOut(MEMBER(data.rawCost));
            _DMESSAGE("--------------------Outputting EffectItemData end.");
        }



        struct EffectItemDataTomm
        {
            bool    bValid = false;
            RE::EffectItem data;
            auto           operator<=>(const EffectItemDataTomm&) const = default;

            EffectItemDataTomm()
            {
                data.areaGlobal = NULL;
                data.durationGlobal = NULL;
                data.magGlobal      = NULL;
                data.effectSetting = 0;
                data.rawCost        = 0;
                data.unk30 = 0;
                data.unk34 = 0;
                data.data.area = 0;
                data.data.duration = 0;
                data.data.magnitude = 0;
                data.conditions.head = NULL;
               // _DMESSAGE("Effect Data Init done.");
            }

            void Output() {
                _DMESSAGE("Outputting EffectItemData start.");
                CheckFormForForMemberFormAndPrintOut(MEMBER(data.effectSetting));
                CheckFormForForMemberValueAndPrintOut(MEMBER(data.data.magnitude));
                CheckFormForForMemberValueAndPrintOut(MEMBER(data.data.area));
                CheckFormForForMemberValueAndPrintOut(MEMBER(data.data.duration));
                CheckFormForForMemberFormAndPrintOut(MEMBER(data.magGlobal));
                CheckFormForForMemberFormAndPrintOut(MEMBER(data.areaGlobal));
                CheckFormForForMemberFormAndPrintOut(MEMBER(data.durationGlobal));
                CheckFormForForMemberValueAndPrintOut(MEMBER(data.rawCost));
                _DMESSAGE("Outputting EffectItemData end.");
            }



        };

        EffectItemDataTomm GetFromString(std::string_view ModifierSection)
        {
            EffectItemDataTomm result{};

            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;


            int iCount = 0;
            _DMESSAGE("getting EffectItem starts from>>{}", ModifierSection);

            while (NewModifierPos != NONPOS && iCount <7) {
                NewModifierPos = ModifierSection.find(sPropertiesDelimeter, CurrentPos);

                std::string_view sCurrentPart = ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos);

                if (!sCurrentPart.length())
                {
                    _DRTFPError("Lenght of current part is 0,Count>>{},string>>{}", iCount, sCurrentPart);
                    return result;
                }


                if (iCount == 0) // Effect form ID
                {
                    auto CurrentForm = GetFormFromStringAndCheckForCategory<false>(sCurrentPart, (std::uint8_t)RE::FormType::kMGEF);

                    if (!CurrentForm.bValid) {
                        return result;
                    }

                    result.data.effectSetting = (RE::EffectSetting*)CurrentForm.data;

                }
                else if (iCount == 1) //Magnitude
                {
                    auto floatResult = GetNumberFromString<float>(sCurrentPart);

                        if (!floatResult.bSuccess)
                        {
                            _DRTFPError("Cannot convert to number from your input>>{}, part>>", ModifierSection, sCurrentPart);
                            return result;
                        }

                        result.data.data.magnitude = floatResult.data;

                }
                else if (iCount == 2) // Area
                {
                        auto floatResult = GetNumberFromString<float>(sCurrentPart);

                        if (!floatResult.bSuccess) {
                            _DRTFPError("Cannot convert to number from your input>>{}, part>>", ModifierSection, sCurrentPart);
                            return result;
                        }

                        result.data.data.area = floatResult.data;

                }
                else if (iCount == 3) // Duration
                {
                        auto DoubleResult = GetNumberFromString(result.data.data.duration,sCurrentPart);

                        if (!DoubleResult.bSuccess) {
                            _DRTFPError("Cannot convert to number from your input>>{}, part>>", ModifierSection, sCurrentPart);
                            return result;
                        }

                        result.data.data.duration = DoubleResult.data;
                }
                else if (iCount == 4) // Magnitude GLOB
                {
                   auto CurrentForm      = GetFormFromStringAndCheckForCategory<true>(sCurrentPart, Sections::k_Global);

                   if (!CurrentForm.bValid)
                   {
                         _DRTFPFormBuiltError("Cannot convert to Magniture global from your input>>{}, part>>", ModifierSection, sCurrentPart);
                        return result;
                   }

                    result.data.magGlobal = (RE::TESGlobal*)CurrentForm.data;
                }
                else if (iCount == 5) // Area GLOB
                {
                    auto CurrentForm       = GetFormFromStringAndCheckForCategory<true>(sCurrentPart, Sections::k_Global);

                    if (!CurrentForm.bValid) {
                        _DRTFPFormBuiltError("Cannot convert to Area global from your input>>{}, part>>", ModifierSection, sCurrentPart);
                        return result;
                    }
                    result.data.areaGlobal = (RE::TESGlobal*)CurrentForm.data;
                }
                else if (iCount == 6) // DurationGLOB
                {
                    auto CurrentForm           = GetFormFromStringAndCheckForCategory<true>(sCurrentPart, Sections::k_Global);

                    if (!CurrentForm.bValid) {
                        _DRTFPFormBuiltError("Cannot convert to Duration global from your input>>{}, part>>", ModifierSection, sCurrentPart);
                        return result;
                    }
                    result.data.durationGlobal = (RE::TESGlobal*)CurrentForm.data;
                }

                iCount++;
                CurrentPos = NewModifierPos + 1;
            }

            if (iCount <7) {
                _DRTFPError("Incorrect syntax for effect entry>>{}", ModifierSection);
                return result;
            }


            result.Output();
            result.bValid = true;
            return result;
        }

        void AddToArray(RE::BSTArray<RE::EffectItem*>& Arr, RE::EffectItem& EffectData)
        {
            auto NewItem = new RE::EffectItem;

            (*NewItem) = EffectData;
            Arr.push_back(NewItem);
        }

        void RemoveFromArray(RE::BSTArray<RE::EffectItem*>& Arr, RE::EffectItem& EffectData)
        {
            for (auto it = Arr.begin(); it != Arr.end(); it++) {

                if (IsEffectDataEqualJustCheckForEffect((**it), EffectData)) {
                    RE::MemoryManager::GetSingleton()->Free(*it, 0);
                    Arr.erase(it);
                    break;
                }
            }
        }

        void ReplaceInArray(RE::BSTArray<RE::EffectItem*>& Arr, RE::EffectItem& EffectDataToBeReplaced, RE::EffectItem& EffectDataToReplaceTo)
        {
            for (auto it = Arr.begin(); it != Arr.end(); it++) {

                if (IsEffectDataEqualJustCheckForEffect((**it), EffectDataToBeReplaced)) {
                    **it = EffectDataToReplaceTo;
                    break;
                }
            }
        }


        void ClearArray(RE::BSTArray<RE::EffectItem*>& Arr)
        {
            for (auto it = Arr.begin(); it != Arr.end(); it++) {
                RE::MemoryManager::GetSingleton()->Free(*it, 0);
                break;
            }
            Arr.clear();
        }

    }




    namespace PerkRankData
    {
        struct PerkRankDataTomm
        {
            bool bValid = false;

            struct Data
            {
                RE::PerkRankData elem;
            };

            Data data;
        };


        template <bool bInsert>
        PerkRankDataTomm GetFromString(std::string_view ModifierSection)
        {
            PerkRankDataTomm result;

            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;

            NewModifierPos = ModifierSection.find(sPropertiesDelimeter, CurrentPos);

            if (NewModifierPos == NONPOS) {
                _DRTFPError("Perk rank::No properties for form>>{}", ModifierSection);
                return result;
            }

            auto CurrentForm = GetFormFromStringAndCheckForCategory<false>(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos), Sections::k_Perk);

            if (!CurrentForm.bValid) {
                return result;
            }

            CurrentPos  = NewModifierPos + 1;


            auto PerkRank = GetNumberFromString(result.data.elem.currentRank,ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos));

            if (!PerkRank.bSuccess) {
                _DRTFPError("Perk rank::Cannot convert perk rank to a number>>{}", ModifierSection);
                return result;
            }


            result.data.elem.currentRank = PerkRank.data;
            result.data.elem.perk        = (RE::BGSPerk*)CurrentForm.data ;
            result.bValid = true;
            return result;
        }
    }

    namespace ConditionForm
    {
        struct EntryFromString
        {
            struct Data
            {
                RE::BGSConditionForm* form = NULL;
                std::uint32_t         iEntryPos = 0;
            };

            bool               bValid = false;
            Data                data;
        };



        void AddEntryFromCondForm(RE::BGSConditionForm* AddTo, EntryFromString::Data& AddFrom)
        {
            _DMESSAGE("Adding conditioned form from {:08X}, entry>>{} to {:08X}", AddFrom.form->formID, AddFrom.iEntryPos, AddTo->formID);
            std::uint32_t iCount = 0;

            RTFP::TESConditionItem* Curr = RTFP::AsRTFP(AddFrom.form->conditions.head);

            RTFP::TESConditionItem* FoundConditionedItem = NULL;

            while (Curr) {
                if (Curr->unk0)
                {
                    _DMESSAGE("New condition,iCount>>{},unk>>{:08X},address>>{:08X}", iCount, (uintptr_t)Curr->unk0, (uintptr_t)Curr);
                }
                else {
                    _DMESSAGE("New condition,iCount>>{},unk>>NULL,address>>{:08X}", iCount, (uintptr_t)Curr);
                }


                if (iCount == AddFrom.iEntryPos)
                {
                    FoundConditionedItem = Curr;
                    _DMESSAGE("Found entry - breaking.")
                    break;
                }

                if (!Curr->next) {
                    _DMESSAGE("Last entry");
                    break;
                }
                Curr = Curr->next;
                iCount++;
            }

            if (!FoundConditionedItem)
            {
                _DRTFPError("Could not find the item in source COND form");
                return;
            }

            Curr = RTFP::AsRTFP(AddTo->conditions.head);

            _DMESSAGE("Adding entry to the other form");

            iCount = 0;
             while (Curr) {
                if (Curr->unk0) {

                 _DMESSAGE("New condition,iCount>>{},unk>>{:08X},address>>{:08X}", iCount, (uintptr_t)Curr->unk0, (uintptr_t)Curr);
               }
               else {
                 _DMESSAGE("New condition,iCount>>{},unk>>NULL,address>>{:08X}", iCount, (uintptr_t)Curr);

               }


                if (!Curr->next) {
                    _DMESSAGE("Last entry! Adding.");
                    RTFP::TESConditionItem* MemoryPointer = (RTFP::TESConditionItem*)RE::MemoryManager::GetSingleton()->Allocate(sizeof(RTFP::TESConditionItem), 0, false);
                    _DMESSAGE("New memory address>>{:08X}", (uintptr_t)MemoryPointer);
                    std::memcpy(MemoryPointer, FoundConditionedItem, sizeof(RTFP::TESConditionItem));
                    Curr->next = MemoryPointer;
                    MemoryPointer->next = NULL; // Last entry must have NULL obvs.
                    break;
                }
                Curr = Curr->next;
                iCount++;
             }

             _DMESSAGE("Added at pos {}", iCount);
        }


        EntryFromString GetFromString(std::string_view ModifierSection)
        {
            EntryFromString result;

            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;

            NewModifierPos = ModifierSection.find(sPropertiesDelimeter, CurrentPos);

            if (NewModifierPos == NONPOS) {
                _DRTFPError("COND form::No properties for form>>{}", ModifierSection);
                return result;
            }

            auto CurrentForm = GetFormFromStringAndCheckForCategory<false>(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos), Sections::k_ConditionForm);

            if (!CurrentForm.bValid) {
                return result;
            }

            CurrentPos = NewModifierPos + 1;

            auto EntryPos = GetNumberFromString(result.data.iEntryPos, ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos));

            if (!EntryPos.bSuccess) {
                _DRTFPError("Perk rank::Cannot convert perk rank to a number>>{}", ModifierSection);
                return result;
            }


            result.data.iEntryPos        = EntryPos.data;
            result.data.form      = (RE::BGSConditionForm*)CurrentForm.data;
            result.bValid           = true;
            return result;
        }




    }


    namespace Properties
    {
        struct EntryFromString
        {
            bool bValid = false;

            struct Data
            {
                PROPERTY elem;
            };

            Data data;

            EntryFromString()
            {
                data.elem.first   = NULL;
                data.elem.second  = NULL;
                data.elem.third.i = 0;
                _DMESSAGE("Properties::EntryFromString init.");
            }
        };

        template <bool bInsert, typename ValueType>
        EntryFromString GetFromString(std::string_view ModifierSection)
        {
            EntryFromString result;

            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;

            NewModifierPos = ModifierSection.find(sPropertiesDelimeter, CurrentPos);

            if (NewModifierPos == NONPOS) {
                _DRTFPError("Component data::No properties for form>>{}", ModifierSection);
                return result;
            }

            auto CurrentForm = GetFormFromStringAndDontCheckForCategory<false>(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos));

            if (!CurrentForm.bValid) {
                return result;
            }

            CurrentPos     = NewModifierPos + 1;
            NewModifierPos = ModifierSection.find(sPropertiesDelimeter, CurrentPos);

            if (NewModifierPos == NONPOS) {
                _DRTFPError("Component data::No value for form>>{}", ModifierSection);
                return result;
            }

            auto Value = GetNumberFromString<ValueType>(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos));

            if (!Value.bSuccess) {
                _DRTFPError("Component data::Cannot convert cound to a number>>{}", ModifierSection);
                return result;
            }

            CurrentPos = NewModifierPos + 1;

            auto CurveForm = GetFormFromStringAndCheckForCategory<true>(ModifierSection.substr(CurrentPos, ModifierSection.length() - CurrentPos), (std::uint8_t)RE::FormType::kCURV);

            if (!CurveForm.bValid) {
                return result;
            }

            result.data.elem.first   = CurrentForm.data;
            result.data.elem.third.f = Value.data;
            result.data.elem.second  = CurveForm.data;
            result.bValid            = true;
            return result;
        }

    }



    namespace TUPLE {

        struct TupleData
        {
            bool bValid = false;

            struct Data
            {
                TUPLE3 elem;
            };

            Data data;

            TupleData()
            {
                data.elem.first   = NULL;
                data.elem.second  = NULL;
                data.elem.third.i = 0;
                _DMESSAGE("TupleData init.");
            }
        };

        template <bool bInsert>
        TupleData GetFromString(std::string_view ModifierSection)
        {
            TupleData result;

            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;

            NewModifierPos = ModifierSection.find(sPropertiesDelimeter, CurrentPos);

            if (NewModifierPos == NONPOS) {
                _DRTFPError("Component data::No properties for form>>{}", ModifierSection);
                return result;
            }

            auto CurrentForm = GetFormFromStringAndDontCheckForCategory<false>(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos));

            if (!CurrentForm.bValid) {
                return result;
            }

            CurrentPos = NewModifierPos + 1;

            auto CompCount = GetNumberFromString(result.data.elem.third.i, ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos));

            if (!CompCount.bSuccess) {
                _DRTFPError("Component data::Cannot convert cound to a number>>{}", ModifierSection);
                return result;
            }

            result.data.elem.first   = CurrentForm.data;
            result.data.elem.third.i = CompCount.data;
            result.bValid            = true;
            return result;
        }



    }










    namespace ConstructibleObjects 
    {
        void SetCategory(RE::BGSConstructibleObject* vIn, std::string_view ModifierSection)
        {

            int  CurrentCategory = Sections::k_Keyword;
            auto CurrentForm     = GetFormFromStringAndCheckForCategory<false>(ModifierSection, CurrentCategory);
            if (!CurrentForm.bValid) {
                return;
            }

            vIn->recipeFilters.clear();
            vIn->recipeFilters.push_back(static_cast<RE::BGSKeyword*>(CurrentForm.data));
            _DMESSAGE("category set");

            //if (vIn.size())
            //{
            //    _DMESSAGE("Setting new category at 0 pos");
            //    vIn.at(0) = (RE::BGSKeyword*)CurrentForm.data;
            //}
            //else {
            //    _DMESSAGE("Pushing category to an empty vector");
            //    vIn.push_back((RE::BGSKeyword*)CurrentForm.data);
            //}

            _DMESSAGE("Done");
        }


    }




    namespace Weapons // Because Beth like making it harder for us.
    {
        void ProcessFlagsForWeapons(bool bSet, RE::WeaponDataFlags* CurrentWeaponFlags, unsigned long CurrentModifierValue) 
        {
            
            switch (CurrentModifierValue) {
            case sWeaponFlagNonPlayable:
                CurrentWeaponFlags->NonPlayable = bSet;
                break;
            case sWeaponFlagPlayerOnly:
                CurrentWeaponFlags->PlayerOnly = bSet;
                break;
            case sWeaponFlagCantDrop:
                CurrentWeaponFlags->CantDrop = bSet;
                break;
            case sWeaponFlagMinorCrime:
                CurrentWeaponFlags->MinorCrime= bSet;
                break;
            case sWeaponFlagNonHostile:
                CurrentWeaponFlags->NonHostile = bSet;
                break;
            default:
                _DMESSAGE("Invalid flag for Weapons.");
                break;
            }
        }


        void ProcessFlagModifier(bool bSet, RE::TESObjectWEAP* CurrentWeapon, std::string_view CurrentModifierValue)
        {
            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;

            _DMESSAGE("ProcessFlagModifier for weapon starts");

            auto CurrentWeaponData = CurrentWeapon->weaponData.get();

            if (!CurrentWeaponData)
            {
                _DRTFPError("CurrentWeapon data is not valid???>>>{:08X}", CurrentWeapon->formID);
                return;
            }

            RE::WeaponDataFlags* CurrentWeaponFlags = CurrentWeaponData->WeaponFlags;

            if (!CurrentWeaponFlags)
            {
                _DRTFPError("CurrentWeapon  flags data is not valid???>>>{:08X}", CurrentWeapon->formID);
                return;
            }

            while (NewModifierPos != NONPOS) {
                NewModifierPos = CurrentModifierValue.find(sArrDelimeter, CurrentPos);
                _DMESSAGE("Flag>>{},Set>>{}", CurrentModifierValue.substr(CurrentPos, NewModifierPos - CurrentPos), bSet);
                ProcessFlagsForWeapons(bSet, CurrentWeaponFlags, hash_djb2a(CurrentModifierValue.substr(CurrentPos, NewModifierPos - CurrentPos)));
                CurrentPos = NewModifierPos + 1;
            }
        }
    }






    namespace ArrayNonForm
    {
        template <class Array,class Entry>
        void Add(Array& Arr, Entry& entry)
        {
            if constexpr (std::is_pointer<Array>::value) {


                if (Arr)
                {
                    Arr->push_back(std::move(entry.elem));
                    _DMESSAGE("pushing to existing arr");
                }
                else {
                    auto pNewArr = ElementOperators::CreatePointerBSTArrayIdNotExist(Arr);

                    if (pNewArr) {
                            pNewArr->push_back(std::move(entry.elem));
                            _DMESSAGE("pushing to  new arr");
                    }
                    else {
                            _DMESSAGE("Cannot create new BSTArr arr.");
                    }
                }

            }
            else {
                
                _DMESSAGE("test 1,size>>{}", Arr.size());
                Arr.push_back(std::move(entry.elem));
                _DMESSAGE("test 2");
            }

        }

       template <class Array, class Entry>
        void Remove(Array& Arr, Entry& entry)
       {

            if constexpr (std::is_pointer<Array>::value) {

               for (auto it = Arr->begin(); it != Arr->end(); it++) {
                    if (ElementOperators::AreEntriesEqual(Iter, entry.elem)) {
                            Arr->erase(it);
                            break;
                    }
                }

            }
            else {
                for (auto it = Arr.begin(); it != Arr.end(); it++) {
                    if (ElementOperators::AreEntriesEqual(Iter, entry.elem)) {
                            Arr.erase(it);
                            break;
                    }
                }
            }

       }


       template <class Array, class Entry>
       void Replace(Array& Arr, Entry& EffectDataToBeReplaced, Entry& EffectDataToReplaceTo)
       {
            _DMESSAGE("Replacing.");

            if constexpr (std::is_pointer<Array>::value) {

               for (auto it = Arr->begin(); it != Arr->end(); it++) {
                    if (ElementOperators::AreEntriesEqual((*it), EffectDataToBeReplaced.elem)) {
                            ElementOperators::ReplaceLeftWithRight(Iter, EffectDataToReplaceTo.elem);
                            _DMESSAGE("Replaced");
                            break;
                    }
                }
            }
            else {
                for (auto it = Arr.begin(); it != Arr.end(); it++) {
                    if (ElementOperators::AreEntriesEqual((*it), EffectDataToBeReplaced.elem)) {
                            ElementOperators::ReplaceLeftWithRight(Iter, EffectDataToReplaceTo.elem);
                            _DMESSAGE("Replaced");
                            break;
                    }
                }
            }
       }


      template <class Array, class Entry>
       void Insert(Array& Arr, Entry& EntryToAdd)
       {

            if constexpr (std::is_pointer<Array>::value) {
                if (EntryToAdd.iEntryPos >= Arr->size()) {
                    _DRTFPError("Cannot insert to pos>>{} because size of array is>> {}", EntryToAdd.iEntryPos, Arr.size());
                    return;
                }
                Arr->emplace(Arr.begin() + EntryToAdd.iEntryPos, std::move(EntryToAdd.elem));
                _DMESSAGE("Inserted at pos >>{}", EntryToAdd.iEntryPos);
            }
            else {
                if (EntryToAdd.iEntryPos >= Arr.size()) {
                    _DRTFPError("Cannot insert to pos>>{} because size of array is>> {}", EntryToAdd.iEntryPos, Arr.size());
                    return;
                }
                Arr.emplace(Arr.begin() + EntryToAdd.iEntryPos, std::move(EntryToAdd.elem));
                _DMESSAGE("Inserted at pos >>{}", EntryToAdd.iEntryPos);

            }

       }

       template <class Array>
       void _Clear(Array& Arr)
       {

           _DMESSAGE("Clearing");
           if constexpr (std::is_pointer<Array>::value) {

                Arr->clear();

           }
           else {
                Arr.clear();
           }

       }


        template <class T, typename _FuncProcess, typename _FuncGet>
        void _AddRemoveInsert(T& Array, std::string_view ModifierSection, _FuncProcess funcProcess, _FuncGet funcGet)
        {
            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;

            while (NewModifierPos != NONPOS) {
                NewModifierPos = ModifierSection.find(sArrDelimeter, CurrentPos);

                auto DecodedObject = funcGet(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos));
                CurrentPos         = NewModifierPos + 1;

                if (!DecodedObject.bValid) {
                    continue;
                }
                _DMESSAGE("Decoded object found");

                funcProcess(Array, DecodedObject.data);
            }
        }



       


        template <typename T, typename _FuncProcess, typename _FuncGet>
        void _ReplaceInArray(T& Arr, std::string_view ModifierSection, _FuncProcess funcProcess, _FuncGet funcGet)
        {
            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;

            NewModifierPos = ModifierSection.find(sArrDelimeter, CurrentPos);

            if (NewModifierPos == NONPOS) {
                _DRTFPError("No comma in>>{}", ModifierSection);
                return;
            }

            auto DecodedObjectOne = funcGet(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos));

            if (!DecodedObjectOne.bValid) {
                return;
            }

           CurrentPos = NewModifierPos + 1;

           auto DecodedObjectTwo = funcGet(ModifierSection.substr(CurrentPos, ModifierSection.length() - CurrentPos));

           if (!DecodedObjectTwo.bValid) {
                return;
           }

            funcProcess(Arr, DecodedObjectOne.data,DecodedObjectTwo.data);
            return;
        }

       
      


    }



    namespace Array
    {
        template <typename T,typename O>
        void InsertObject(T& Arr, O& CurrentObject, int Pos)
        {
            Arr.insert(Arr.begin() + Pos, CurrentObject);
        }

        template <typename T, typename O>
        void ReplaceNthObject(T& Arr, O& CurrentObject, int Pos)
        {
            Arr.at(Pos) = CurrentObject;
        }

        
        template <typename T>
        void AddToArray(RE::BSTArray<T>& array, T CurrentForm)
        {
            array.push_back(CurrentForm);
        }

        template <typename T>
        void RemoveFromArray(RE::BSTArray<T>& array, T CurrentForm)
        {
            for (auto it = array.begin(); it != array.end();) {
                if (Iter->formID == CurrentForm->formID) {
                    it = array.erase(it);
                    continue;
                }

                it++;
            }


        }

        template <typename T>
        void ReaplaceObject(RE::BSTArray<T>& array, T CurrentForm, T FormToReplace)
        {
            for (auto it = array.begin(); it != array.end();) {
                if (Iter->formID == CurrentForm->formID) {
                    it = array.erase(it);
                    continue;
                }
                it++;
            }
        }


        template <typename T, typename F, typename... Args>
        void AddRemoveInArray(RE::BSTArray<T>& array, std::string_view ModifierSection, F func, Args... args)
        {
            if (ModifierSection.at(0) == sSearchForFilters) {
                bool bFound = false;

                auto CustomFilter = Input::CustomFilters::GetFilterByNameAndCheckForSection(ModifierSection.substr(1, ModifierSection.length() - 1), std::forward<Args>(args)...);

                if (!CustomFilter) {
                    _DRTFPError("Cannot find a filter with name>>{}", ModifierSection.substr(1, ModifierSection.length() - 1));
                    return;
                }

                for (auto it = CustomFilter->forms.begin(); it != CustomFilter->forms.end(); it++) {
                    func(array, (T)Iter);
                }
            }
            else {
                size_t CurrentPos     = 0;
                size_t NewModifierPos = 0;
                while (NewModifierPos != NONPOS) {
                    NewModifierPos = ModifierSection.find(sArrDelimeter, CurrentPos);

                    auto CurrentForm = GetFormFromStringAndCheckForCategory<false>(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos), std::forward<Args>(args)...);
                    CurrentPos       = NewModifierPos + 1;

                    if (!CurrentForm.bValid) {
                            continue;
                    }

                    func(array, (T)CurrentForm.data);
                }
            }
        }


        template <typename T, typename F>
        void AddRemoveInArray(RE::BSTArray<T>& array, std::string_view ModifierSection, F func, std::uint8_t iArrayFormType)
        {

            if (ModifierSection.at(0) == sSearchForFilters) {
                auto CustomFilter = Input::CustomFilters::GetFilterByNameAndCheckForSection(ModifierSection.substr(1, ModifierSection.length() - 1), iArrayFormType);

                if (!CustomFilter) {
                    _DRTFPError("Cannot find a filter with name>>{}", ModifierSection.substr(1, ModifierSection.length() - 1));
                    return;
                }

                for (auto it = CustomFilter->forms.begin(); it != CustomFilter->forms.end(); it++) {
                    func(array, (T)Iter);
                }
            }
            else {
                size_t CurrentPos     = 0;
                size_t NewModifierPos = 0;
                while (NewModifierPos != NONPOS) {
                    NewModifierPos = ModifierSection.find(sArrDelimeter, CurrentPos);

                    auto CurrentForm = GetFormFromStringAndCheckForCategory<false>(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos), iArrayFormType);
                    CurrentPos       = NewModifierPos + 1;

                    if (!CurrentForm.bValid) {
                        continue;
                    }

                    func(array, (T)CurrentForm.data);

                }
            }
        }


        





        template <typename T>
        void ReplaceFormInArray(RE::BSTArray<T>& array, std::string_view ModifierSection, std::uint8_t iCurrentCategory)
        {
            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;

            NewModifierPos = ModifierSection.find(sArrDelimeter, CurrentPos);

            if (NewModifierPos == NONPOS) {
                _DRTFPError("No comma.");
                return;
            }

            auto CurrentForm = GetFormFromStringAndCheckForCategory<false>(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos), iCurrentCategory);

            if (!CurrentForm.bValid) {
                return;
            }

            CurrentPos = NewModifierPos + 1;

            auto ReplacedForm = GetFormFromStringAndCheckForCategory<false>(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos), iCurrentCategory);

            if (!ReplacedForm.bValid) {
                return;
            }

            T ReplacedFormUse = (T)ReplacedForm.data;

            for (auto it = array.begin(); it != array.end(); it++) {
                if (Iter->formID == CurrentForm.data->formID) {
                    array.erase(it);
                    array.push_back(ReplacedFormUse);
                    return;
                }
            }
        }



        template <typename T, typename... Args>
        void ReplaceFormInArray(RE::BSTArray<T>& array, std::string_view ModifierSection, Args... args)
        {
            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;

            NewModifierPos = ModifierSection.find(sArrDelimeter, CurrentPos);

            if (NewModifierPos == NONPOS) {
                _DRTFPError("No comma.");
                return;
            }

            auto CurrentForm = GetFormFromStringAndCheckForCategory<false>(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos), std::forward<Args>(args)...);

            if (!CurrentForm.bValid) {
                return;
            }

            CurrentPos = NewModifierPos + 1;

            auto ReplacedForm = GetFormFromStringAndCheckForCategory<false>(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos), std::forward<Args>(args)...);

            if (!ReplacedForm.bValid) {
                return;
            }

            T ReplacedFormUse = (T)ReplacedForm.data;

            for (auto it = array.begin(); it != array.end(); it++) {
                if (Iter->formID == CurrentForm.data->formID) {
                    array.erase(it);
                    array.push_back(ReplacedFormUse);
                    return;
                }
            }
        }





        template <typename T, typename... Args>
        void ReplaceFormInArrayAlt(RE::BSTArray<T>& array, Input::TempModifierAlt::Value& ModifierSection, Args... args)
        {
            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;

            NewModifierPos = ModifierSection.CurrentModifierValue.find(sArrDelimeter, CurrentPos);

            if (NewModifierPos == NONPOS) {
                _DRTFPError("No comma.");
                return;
            }

            if constexpr (sizeof...(args) > 0)
            {

            }



            //if (func < std::forward<Args>(args))
            //{

            //}



            for (const auto p : { args... }) {
                //std::cout << p.type().name() << std::endl;
            }



            //auto CurrentForm = GetFormFromStringAndCheckForCategory<false>(ModifierSection.CurrentModifierValue.substr(CurrentPos, NewModifierPos - CurrentPos), iCurrentCategory);

            //if (!CurrentForm.bValid) {
            //    return;
            //}

            //CurrentPos = NewModifierPos + 1;

            //auto ReplacedForm = GetFormFromStringAndCheckForCategory<false>(ModifierSection.CurrentModifierValue.substr(CurrentPos, NewModifierPos - CurrentPos), iCurrentCategory);

            //if (!ReplacedForm.bValid) {
            //    return;
            //}

            //T ReplacedFormUse = (T)ReplacedForm.data;

            //for (auto it = array.begin(); it != array.end(); it++) {
            //    if (Iter->formID == CurrentForm.data->formID) {
            //        array.erase(it);
            //        array.push_back(ReplacedFormUse);
            //        return;
            //    }
            //}
        }




    }







    namespace KeywordsArray
    {
        void AddKeywordToArray(RE::BSTArray<RE::BGSKeyword*>& keywords, RE::BGSKeyword* CurrentForm)
        {
            keywords.push_back((RE::BGSKeyword*)CurrentForm);
        }

        void RemoveKeywordFromArray(RE::BSTArray<RE::BGSKeyword*>& keywords, RE::BGSKeyword* CurrentForm)
        {

            for (auto it = keywords.begin(); it != keywords.end();) {

                if (Iter->formID == CurrentForm->formID) {
                    it = keywords.erase(it);
                    _DMESSAGE("Removing keyword>>{:08X}", CurrentForm->formID);
                    continue;
                }

                it++;
            }
        }


        template <typename F>
        void AddRemoveKeywordInArray(RE::BSTArray<RE::BGSKeyword*>& keywords, std::string_view ModifierSection, F func)
        {
            // CurrentModifierValue = ObjectTypeAmmo,sMyKeyword

            if (ModifierSection.at(0) == sSearchForFilters) {
                auto CustomFilter = Input::CustomFilters::GetFilterByNameAndCheckForSection(ModifierSection.substr(1, ModifierSection.length() - 1),
                                                                                            const_GetTypeFromFormType<RE::BGSKeyword*>());

                if (!CustomFilter) {
                    _DRTFPError("Cannot find a filter with name>>{}", ModifierSection.substr(1, ModifierSection.length() - 1));
                    return;
                }

                for (auto it = CustomFilter->forms.begin(); it != CustomFilter->forms.end(); it++) {
                    func(keywords, (RE::BGSKeyword*)Iter);
                }
            }
            else {
                size_t CurrentPos     = 0;
                size_t NewModifierPos = 0;
                while (NewModifierPos != NONPOS) {
                    NewModifierPos = ModifierSection.find(sArrDelimeter, CurrentPos);
                    // std::string CurrentFormID = std::string(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos)).c_str();

                    // std::string      sTemp         = CurrentFormID;

                    auto CurrentForm = GetFormFromStringAndCheckForCategory<false>(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos),
                                                                            const_GetTypeFromFormType<RE::BGSKeyword*>());

                    CurrentPos = NewModifierPos + 1;

                    if (!CurrentForm.bValid) {

                        continue;
                    }
                    //_DMESSAGE("Keywords before>>{}", keywords.size());
                    func(keywords, (RE::BGSKeyword*)CurrentForm.data);
                    //_DMESSAGE("Keywords after>>{}", keywords.size());
                }
            }

        }











        void ReplaceKeywordInArray(RE::BSTArray<RE::BGSKeyword*>& keywords, std::string_view ModifierSection)
        {
            // CurrentModifierValue = ObjectTypeAmmo,sMyKeyword

            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;

            NewModifierPos = ModifierSection.find(sArrDelimeter, CurrentPos);

            if (NewModifierPos == NONPOS) {
                _DRTFPError("No comma.");
                return;
            }

            auto CurrentForm
                = GetFormFromStringAndCheckForCategory<false>(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos), const_GetTypeFromFormType<RE::BGSKeyword*>());

            if (!CurrentForm.bValid) {
                return;
            }

            CurrentPos = NewModifierPos + 1;

            auto ReplacedForm = GetFormFromStringAndCheckForCategory<false>(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos), const_GetTypeFromFormType<RE::BGSKeyword*>());

            if (!ReplacedForm.bValid) {
                return;
            }

            RE::BGSKeyword* ReplacedFormUse = (RE::BGSKeyword*)ReplacedForm.data;

            for (auto it = keywords.begin(); it != keywords.end(); it++) {
                if (Iter->formID == CurrentForm.data->formID) {
                    keywords.erase(it);
                    keywords.push_back(ReplacedFormUse);
                    return;
                }
            }
        }

       



    }





    template <class T>
    void SetFormFromModifier(T& FormToSet, std::string_view ModifierSection, int CurrentCategory)
    {

        auto CurrentForm = GetFormFromStringAndCheckForCategory<true>(ModifierSection, CurrentCategory);
        if (!CurrentForm.bValid) {
            return;
        }

        FormToSet = (decltype(FormToSet))CurrentForm.data;

    }

    template <class T>
    void SetFormFromModifier(T& FormToSet, Input::TempModifierAlt::Value& value, int CurrentCategory)
    {
        //_DMESSAGE("WORKING WITH VALUE INSTEAD OF STRING");
        if (IsFlagSet(value.flags, TempModifierAlt::Flags::kValid))
        {
            _DMESSAGE("Using cached value");
            FormToSet = (decltype(FormToSet))value.cached.Form;
        }
        else {
            value.flags |= TempModifierAlt::Flags::kNeedsToBeValid;
            auto CurrentForm = GetFormFromStringAndCheckForCategory<true>(value.CurrentModifierValue, CurrentCategory);
            if (!CurrentForm.bValid) {
                return;
            }

            value.cached.Form = CurrentForm.data;
            value.flags |= TempModifierAlt::Flags::kValid;
            _DMESSAGE("Setting cached value for the first time");
            FormToSet = (decltype(FormToSet))CurrentForm.data;
        }

    }



    template <class T>
    void SetFormFromModifierDontCheckForCategory(T& FormToSet, std::string_view ModifierSection)
    {
        auto CurrentForm = GetFormFromStringAndDontCheckForCategory<true>(ModifierSection);
        if (!CurrentForm.bValid) {
            return;
        }

        FormToSet = (decltype(FormToSet))CurrentForm.data;
    }


    namespace NPC
    {

        template <class FlagRequest>
        static bool _forceinline IsActorBaseFlagSet(RE::TESNPC* formIN, FlagRequest& iFlagRequest)
        {
            return formIN->actorData.actorBaseFlags.underlying() & iFlagRequest;
        }




       constexpr std::uint32_t GetFlagFromFlagName(unsigned long FlagName)
       {
           switch (FlagName)
           {
            case sActorFlagFemale:
                return (std::uint32_t)RE::ACTOR_BASE_DATA::Flag::kFemale;
            case sActorFlagEssential:
                return (std::uint32_t)RE::ACTOR_BASE_DATA::Flag::kEssential;
            case sActorFlagIsChargenFacePreset:
                return (std::uint32_t)RE::ACTOR_BASE_DATA::Flag::kIsChargenFacePreset;
            case sActorFlagRespawn:
                return (std::uint32_t)RE::ACTOR_BASE_DATA::Flag::kRespawn;
            case sActorFlagAutoCalcStats:
                return (std::uint32_t)RE::ACTOR_BASE_DATA::Flag::kAutoCalcStats;
            case sActorFlagUnique:
                return (std::uint32_t)RE::ACTOR_BASE_DATA::Flag::kUnique;
            case sActorFlagDoesntAffectStealthMeter:
                return (std::uint32_t)RE::ACTOR_BASE_DATA::Flag::kDoesntAffectStealthMeter;
            case sActorFlagPCLevelMult:
                return (std::uint32_t)RE::ACTOR_BASE_DATA::Flag::kPCLevelMult;
            case sActorFlagProtected:
                return (std::uint32_t)RE::ACTOR_BASE_DATA::Flag::kProtected;
            case sActorFlagSummonable:
                return (std::uint32_t)RE::ACTOR_BASE_DATA::Flag::kSummonable;
            case sActorFlagDoesntBleed:
                return (std::uint32_t)RE::ACTOR_BASE_DATA::Flag::kDoesntBleed;
            case sActorFlagBleedoutOverride:
                return (std::uint32_t)RE::ACTOR_BASE_DATA::Flag::kBleedoutOverride;
            case sActorFlagOppositeGenderAnims:
                return (std::uint32_t)RE::ACTOR_BASE_DATA::Flag::kOppositeGenderanims;
            case sActorFlagSimpleActor:
                return (std::uint32_t)RE::ACTOR_BASE_DATA::Flag::kSimpleActor;
            case sActorFlagIsGhost:
                return (std::uint32_t)RE::ACTOR_BASE_DATA::Flag::kIsGhost;
            case sActorFlagInvulnerable:
                return (std::uint32_t)RE::ACTOR_BASE_DATA::Flag::kInvulnerable;
            default:
                if (std::is_constant_evaluated())
                {
                    throw "Add types to GetFlagFromFlagName function";
                }
                else {
                    _DRTFPError("Unknown flags for NPC");
                }
                return 0;
           }
       }



       template <bool bSet>
        void ProcessFlagsForActorBaseData(std::uint32_t& Flags, unsigned long CurrentModifierValue)
        {


            switch (CurrentModifierValue) {
                _SetOrRemoveFlag(sActorFlagFemale, NPC::GetFlagFromFlagName)
                    _SetOrRemoveFlag(sActorFlagEssential, NPC::GetFlagFromFlagName)
                    _SetOrRemoveFlag(sActorFlagIsChargenFacePreset, NPC::GetFlagFromFlagName)
                    _SetOrRemoveFlag(sActorFlagRespawn, NPC::GetFlagFromFlagName)
                     _SetOrRemoveFlag(sActorFlagAutoCalcStats, NPC::GetFlagFromFlagName)
                    _SetOrRemoveFlag(sActorFlagUnique, NPC::GetFlagFromFlagName)
                    _SetOrRemoveFlag(sActorFlagDoesntAffectStealthMeter, NPC::GetFlagFromFlagName)
                    _SetOrRemoveFlag(sActorFlagPCLevelMult, NPC::GetFlagFromFlagName)
                    _SetOrRemoveFlag(sActorFlagProtected, NPC::GetFlagFromFlagName)
                    _SetOrRemoveFlag(sActorFlagSummonable, NPC::GetFlagFromFlagName)
                     _SetOrRemoveFlag(sActorFlagDoesntBleed, NPC::GetFlagFromFlagName)
                    _SetOrRemoveFlag(sActorFlagBleedoutOverride, NPC::GetFlagFromFlagName)
                     _SetOrRemoveFlag(sActorFlagOppositeGenderAnims, NPC::GetFlagFromFlagName)
                    _SetOrRemoveFlag(sActorFlagSimpleActor, NPC::GetFlagFromFlagName)
                     _SetOrRemoveFlag(sActorFlagIsGhost, NPC::GetFlagFromFlagName)
                    _SetOrRemoveFlag(sActorFlagInvulnerable, NPC::GetFlagFromFlagName)
            default:
                _DMESSAGE("Invalid flag for Actor Base Data.");
                break;
            }
        }

    }


    















    namespace GameSettingsProcessing
    {





        enum GSType
        {
            k_None1 = 0,
            k_Float,
            k_Bool,
            k_Int,
            k_String,
            k_UInt
        };



       

        NumberFromString<double> ProcessModifiersForGameSetting(std::string_view CurrentModifierValue, std::uint8_t& iNeedsCalculating)
        {
            NumberFromString<double> result;

            if (isdigit(CurrentModifierValue.at(0))) {
                result = GetNumberFromString<double>(CurrentModifierValue);
            }
            else {
                switch (CurrentModifierValue.at(0)) {
                case sAdd:
                    iNeedsCalculating = Input::Calculation::k_Add;
                    result            = GetNumberFromString<double>(CurrentModifierValue.substr(1, CurrentModifierValue.size() - 1));
                    break;
                case sSub:
                    iNeedsCalculating = Input::Calculation::k_Sub;
                    result            = GetNumberFromString<double>(CurrentModifierValue.substr(1, CurrentModifierValue.size() - 1));
                    break;
                case sMult:
                    iNeedsCalculating = Input::Calculation::k_Mult;
                    result            = GetNumberFromString<double>(CurrentModifierValue.substr(1, CurrentModifierValue.size() - 1));
                    break;
                case sDiv:
                    iNeedsCalculating = Input::Calculation::k_Div;
                    result            = GetNumberFromString<double>(CurrentModifierValue.substr(1, CurrentModifierValue.size() - 1));
                    break;
                default:
                    _DMESSAGE("Operation not supported for GameSetting>>{}", CurrentModifierValue);
                }
            }

            return result;
        }




        void ProcessGameSettingForNumberedModifier(double GameSettingDouble, std::string GameSettingName, std::uint8_t& iNeedsCalculating)
        {
            using Type = RE::Setting::Type;

            auto pGameSetting = GameSettings::GetSettingByName(GameSettingName);

            if (!pGameSetting) {
                _DRTFPError("Game setting with name {} doesn't exists.", GameSettingName);
                return;
            }

            auto SettingType = pGameSetting->GetType();

            if (!GameSettings::IsSettingANumber(SettingType)) {
                _DRTFPError("Setting {} is not a number but {} - cannot set a string value.", GameSettingName, static_cast<int>(SettingType));
                return;
            }

            if (iNeedsCalculating != Calculation::k_CalcNone) {
                if (SettingType == Type::kBool) {
                    _DRTFPError("--------------------------------Cannot apply calculation to bool in GameSetting>>{}.", GameSettingName);
                    return;
                }

                if (iNeedsCalculating == Calculation::k_Add) {
                    if (SettingType == Type::kFloat) {
                        GameSettingDouble = pGameSetting->GetFloat() + GameSettingDouble;
                    }
                    else if (SettingType == Type::kUInt) {
                        GameSettingDouble = pGameSetting->GetUInt() + GameSettingDouble;
                    }
                    else if (SettingType == Type::kInt) {
                        GameSettingDouble = pGameSetting->GetInt() + GameSettingDouble;
                    }
                }
                else if (iNeedsCalculating == Calculation::k_Sub) {
                    if (SettingType == Type::kFloat) {
                        GameSettingDouble = pGameSetting->GetFloat() - GameSettingDouble;
                    }
                    else if (SettingType == Type::kUInt) {
                        GameSettingDouble = pGameSetting->GetUInt() - GameSettingDouble;
                    }
                    else if (SettingType == Type::kInt) {
                        GameSettingDouble = pGameSetting->GetInt() - GameSettingDouble;
                    }
                }
                else if (iNeedsCalculating == Calculation::k_Mult) {
                    if (SettingType == Type::kFloat) {
                        GameSettingDouble = pGameSetting->GetFloat() * GameSettingDouble;
                    }
                    else if (SettingType == Type::kUInt) {
                        GameSettingDouble = pGameSetting->GetUInt() * GameSettingDouble;
                    }
                    else if (SettingType == Type::kInt) {
                        GameSettingDouble = pGameSetting->GetInt() * GameSettingDouble;
                    }
                }
                else if (iNeedsCalculating == Calculation::k_Div) {
                    if (SettingType == Type::kFloat) {
                        GameSettingDouble = pGameSetting->GetFloat() / GameSettingDouble;
                    }
                    else if (SettingType == Type::kUInt) {
                        GameSettingDouble = pGameSetting->GetUInt() / GameSettingDouble;
                    }
                    else if (SettingType == Type::kInt) {
                        GameSettingDouble = pGameSetting->GetInt() / GameSettingDouble;
                    }
                }
            }

            if (SettingType == Type::kFloat) {

                if (GameSettingDouble > FLT_MAX)
                {
                    GameSettingDouble = FLT_MAX;
                }
                else if (GameSettingDouble < -FLT_MAX) {
                    GameSettingDouble = -FLT_MAX;
                }

                pGameSetting->SetFloat((float)GameSettingDouble);
            }
            else if (SettingType == Type::kUInt) {


                if (GameSettingDouble > UINT32_MAX) {
                    GameSettingDouble = UINT32_MAX;
                }
                else if (GameSettingDouble < 0) {
                    _DRTFPError("After calculations value has become less than zero>>{}.You cannot set negative values to this Game setting.GameSettingname>>{}", GameSettingDouble,
                                GameSettingName);
                    return;
                }

                pGameSetting->SetUInt((std::uint32_t)GameSettingDouble);
            }
            else if (SettingType == Type::kInt) {


                if (GameSettingDouble > INT_MAX) {
                    GameSettingDouble = INT_MAX;
                }
                else if (GameSettingDouble < INT_MIN) {
                    GameSettingDouble = INT_MIN;
                }

                pGameSetting->SetInt((std::int32_t)GameSettingDouble);
            }
            else if (SettingType == Type::kBool) {
                pGameSetting->SetBool((bool)GameSettingDouble);
            }

            GameSettings::NotifySettingUpdated(pGameSetting);

            _DMESSAGE("Game setting set - name>>{},Modifier>>{}", GameSettingName,GameSettingDouble)

        }



        void ProcessGameSettingForStringModifier(std::string GameSettingName, std::string_view& sSecondPart)
        {
            auto pGameSetting = GameSettings::GetSettingByName(GameSettingName);

            if (!pGameSetting) {
                _DRTFPError("Game setting with name {} doesn't exists.", GameSettingName);
                return;
            }

            auto SettingType = pGameSetting->GetType();

            if (!GameSettings::IsSettingAString(SettingType))
            {
                _DRTFPError("Setting {} is not a string but {} - cannot set a string value.", GameSettingName, static_cast<int>(SettingType));
                return;
            }


            std::string sValue{ sSecondPart };
            pGameSetting->SetString(sValue.c_str());
            GameSettings::NotifySettingUpdated(pGameSetting);

        }



        void ProcessGameSettingsLine(std::string_view GameSettingName, std::string_view ModifierSection)
        {
            _DMESSAGE("Processing gamesetting line>>{}|{}", GameSettingName, ModifierSection)


            if (ModifierSection.at(0) == '"') {

                auto ClosingQuotePos = ModifierSection.find('"', 1);

                if (ClosingQuotePos == NONPOS)
                {
                    _DRTFPError("no closing quote for modifier>>{}", ModifierSection);
                    return;
                }

                std::string_view sSecondPart = ModifierSection.substr(1, ModifierSection.length() - 2);


                size_t CurrentPos     = 0;
                size_t NewModifierPos = 0;
                while (NewModifierPos != NONPOS) {
                    NewModifierPos = GameSettingName.find(sArrDelimeter, CurrentPos);
                    ProcessGameSettingForStringModifier((std::string)GameSettingName.substr(CurrentPos, NewModifierPos - CurrentPos), sSecondPart);
                    CurrentPos = NewModifierPos + 1;
                }



            }
            else {
                std::uint8_t  iNeedsCalculating = Calculation::k_CalcNone;
                auto GameSettingDouble = ProcessModifiersForGameSetting(ModifierSection, iNeedsCalculating);

                if (!GameSettingDouble.bSuccess) {
                    _DRTFPError("Cannot extract number from modifier>>{}", ModifierSection);
                    return;
                }


                 size_t CurrentPos     = 0;
                 size_t NewModifierPos = 0;
                 while (NewModifierPos != NONPOS) {

                    NewModifierPos = GameSettingName.find(sArrDelimeter, CurrentPos);
                    ProcessGameSettingForNumberedModifier(GameSettingDouble.data, (std::string)GameSettingName.substr(CurrentPos, NewModifierPos - CurrentPos), iNeedsCalculating);
                    CurrentPos = NewModifierPos + 1;
                 }



            }
        }
    }



    struct TempModifier
    {
        unsigned long    CurrentModifierName = 0;
        std::string_view CurrentModifierValue{};
  
    };





    namespace LeveledLists
    {


        struct StoredData
        {
            bool                            bAffected           = false;
            bool                            bDontSort           = false;
            bool                            bEntriesCopied      = false;
            bool                            bEntriesNonValid    = false;
            RE::TESLevCharacter*            formIn              = NULL;
            int                             iOriginalEntryCount = 0;
            std::vector<RE::LEVELED_OBJECT> vEntries{};

            void __forceinline SetAffected()
            {
                 if (!bAffected) {
                    bAffected = true;
                 }
            }


            void ApplyChanges()
            {
                 _DMESSAGE("REPLACING -- Temp LVLList array has {} elements", vEntries.size());
                 auto NewLeveleddObjectArr = new RE::LEVELED_OBJECT[vEntries.size()];

                 // RE::LEVELED_OBJECT* NewLeveleddObjectArr = new RE::LEVELED_OBJECT[vLeveledList.size() + 1];

                 int iCount = 0;
                 for (auto it = vEntries.begin(); it != vEntries.end(); it++) {
                    _DMESSAGE("REPLACING--Form in vector array>>{:08X} at pos {}", vEntries.at(iCount).form->formID, iCount);
                    NewLeveleddObjectArr[iCount] = vEntries.at(iCount);
                    iCount++;
                 }

                 StoredEntries::Entry NewEntry;
                 NewEntry.formIn     = formIn;
                 NewEntry.firstEntry = (uintptr_t)formIn->leveledLists;
                 NewEntry.lastEntry  = formIn->baseListCount;



                 formIn->baseListCount = vEntries.size();
                // _DMESSAGE("freeing old LVL object array, new listCount>>{}", formIn->baseListCount);
                // RE::MemoryManager::GetSingleton()->Free(formIn->leveledLists, 0);
                 formIn->leveledLists = NewLeveleddObjectArr;
                 NewEntry.NewFirstEntryAddress = (uintptr_t)NewLeveleddObjectArr;

                StoredEntries::v_Stored.push_back(NewEntry);

                 _DMESSAGE("done");

            }



            bool CanAddNewItem() {

                if (vEntries.size() <= iMaxLVLListCount)
                {
                    return true;
                }
                _DRTFPError("Max entry count exceeded- cannot add.");
                return false;
            }


            bool GetEntriesFromForm(RE::TESLevCharacter* formIn)
            {
                 if (!formIn->leveledLists) {
                    _DMESSAGE("No leveled list in form>>{:08X}", formIn->formID);
                    bEntriesNonValid = true;
                    return false;
                 }

                 vEntries.reserve(formIn->baseListCount);

                 for (auto i = 0; i < formIn->baseListCount; i++) {
                    _DMESSAGE("COPYING--Form in original array>>{:08X}", formIn->leveledLists[i].form->formID);
                    vEntries.push_back(formIn->leveledLists[i]);
                 }
                 iOriginalEntryCount = vEntries.size();
                 bEntriesCopied      = true;
                 return true;
            }

            bool EntriesCopiedOrValid(RE::TESLevCharacter* formIn)
            {
                 if (bEntriesCopied) {
                    return true;
                 }
                 else if (bEntriesNonValid)
                 {
                    _DMESSAGE("Entries are not valid for >> {:08X}", formIn->formID);
                    return false;
                 }

                 return GetEntriesFromForm(formIn);
            }

        };

        std::vector<StoredData> vStored{};

        StoredData* GetOrCreateStoredItem(RE::TESLevCharacter* formIn)
        {
            for (auto it = vStored.begin(); it != vStored.end(); it++) {
                 if (Iter.formIn->formID == formIn->formID) {
                    _DMESSAGE("Found stored data,formID>>{:08X}", Iter.formIn->formID);
                    return &Iter;
                 }
            }

            StoredData NewStoredData{};
            NewStoredData.formIn = formIn;
            vStored.push_back(NewStoredData);
            _DMESSAGE("Created new stored data for formID>>{:08X}", vStored.back().formIn->formID);
            return &vStored.back();
        }



        struct DecodedLeveledObject
        {
            bool bValid = false;
            RE::LEVELED_OBJECT data;


            DecodedLeveledObject()
            {
                 data.form       = NULL;
                 data.conditions = NULL;
                 data.itemExtra  = NULL;
                 data.chanceNone = 0;
                 data.unk1D      = 0;
                _DMESSAGE("INIT leveled object.");
            }

        };


        DecodedLeveledObject GetLeveledObjectFromModifier(std::string_view ModifierSection)
        {
            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;

            DecodedLeveledObject result{};

            //Starfield~1EA1:1:1:0
            //Form:Level:Count:Chance

            NewModifierPos = ModifierSection.find(sPropertiesDelimeter, CurrentPos);

            if (NewModifierPos == NONPOS) {
                _DRTFPError("LVL Object::No properties for form>>{}", ModifierSection);
                return result;
            }

            auto CurrentForm = GetFormFromStringAndDontCheckForCategory<false>(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos));

            if (!CurrentForm.bValid) {
                return result;
            }

            CurrentPos = NewModifierPos + 1;
            NewModifierPos = ModifierSection.find(sPropertiesDelimeter, CurrentPos);

            if (NewModifierPos == NONPOS) {
                _DRTFPError("LVL Object:::No properties for level>>{}", ModifierSection);
                return result;
            }
            else if (NewModifierPos == CurrentPos)
            {
                _DRTFPError("LVL Object::Property for level is empty>>{}", ModifierSection);
                return result;
            }

            auto Level = GetNumberFromString<std::uint16_t>(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos));

            if (!Level.bSuccess)
            {
                _DRTFPError("LVL Object::Cannot convert Level to float>>{}", ModifierSection);
                return result;
            }

            CurrentPos     = NewModifierPos + 1;
            NewModifierPos = ModifierSection.find(sPropertiesDelimeter, CurrentPos);

            if (NewModifierPos == NONPOS) {
                _DRTFPError("LVL Object:::No properties for count>>{}", ModifierSection);
                return result;
            }
            else if (NewModifierPos == CurrentPos){
                _DRTFPError("LVL Object::Property for count is empty>>{}", ModifierSection);
                return result;
            }

            auto Count = GetNumberFromString<std::uint16_t>(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos));

            if (!Count.bSuccess) {
                _DRTFPError("LVL Object::Cannot convert count to float>>{}", ModifierSection);
                return result;
            }

            CurrentPos     = NewModifierPos + 1;


            //NewModifierPos = ModifierSection.find(sPropertiesDelimeter, CurrentPos);

            //if (NewModifierPos == NONPOS) {
            //    _DMESSAGE("LVL Object:::No properties for chance>>{}", ModifierSection);
            //    return result;
            //}
            //else if (NewModifierPos == CurrentPos) {
            //    _DMESSAGE("LVL Object::Property for chance is empty>>{}", ModifierSection);
            //    return result;
            //}

            auto Chance = GetNumberFromString(result.data.chanceNone, ModifierSection.substr(CurrentPos, ModifierSection.length() - CurrentPos));

            if (!Chance.bSuccess) {
                _DRTFPError("LVL Object::Cannot convert chance to float>>{}, Modifier>>{}",
                          ModifierSection,ModifierSection.substr(CurrentPos, ModifierSection.length() - CurrentPos));
                return result;
            }

            result.bValid = true;
            result.data.level      = Level.data;
            result.data.count      = Count.data;
            result.data.chanceNone = Chance.data;


            result.data.form = CurrentForm.data;
            _DMESSAGE("Extracted LeveledObject, level>>{},count>>{},form>>{:08X},chanceNone>>{}", result.data.level, result.data.count, result.data.form->formID,
                      result.data.chanceNone);
            return result;
        }




        void AddLeveledObjectToLeveledList(LeveledLists::StoredData& storedData, RE::LEVELED_OBJECT& CurrentObject)
        {
            storedData.SetAffected();
            storedData.vEntries.push_back(CurrentObject);
        }


        void RemoveLeveledObjectFromLeveledList(LeveledLists::StoredData& storedData, RE::LEVELED_OBJECT& CurrentObject)
        {
            for (auto it = storedData.vEntries.begin(); it != storedData.vEntries.end();) {

                
                if (Iter.level == CurrentObject.level && Iter.form == CurrentObject.form && Iter.count == CurrentObject.count && Iter.chanceNone == CurrentObject.chanceNone) {
                    storedData.SetAffected();
                    it = storedData.vEntries.erase(it);
                    return;
                }
                else {
                    it++;
                }
            }

        }


        bool __forceinline AreLeveledObjectsEqual(RE::LEVELED_OBJECT& left, RE::LEVELED_OBJECT& right)
        {
            if (left.level == right.level && left.form == right.form && left.count == right.count && left.chanceNone == right.chanceNone)
            {
                return true;
            }
            return false;
        }


        RE::LEVELED_OBJECT* GetLeveledObjectFromVector(std::vector<RE::LEVELED_OBJECT>& vEntries, RE::LEVELED_OBJECT& EffectDataToBeReplaced)
        {
            for (auto it = vEntries.begin(); it != vEntries.end();it++) {
                if (AreLeveledObjectsEqual(Iter, EffectDataToBeReplaced)) {
                    return &Iter;
                }
                
            }
            return NULL;
        }


        void ReplaceLeveledObjectFromLeveledList(LeveledLists::StoredData& storedData, RE::LEVELED_OBJECT& EffectDataToBeReplaced, RE::LEVELED_OBJECT& EffectDataToReplaceTo)
        {
            auto FoundLVLObject = GetLeveledObjectFromVector(storedData.vEntries, EffectDataToBeReplaced);

            if (FoundLVLObject) {
                storedData.SetAffected();
                *FoundLVLObject = EffectDataToReplaceTo;
            }

        }


        template <typename T, typename F>
        void AddRemoveForm(T& vLeveledList, std::string_view ModifierSection, F func)
        {
            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;

            while (NewModifierPos != NONPOS) {
                NewModifierPos = ModifierSection.find(sArrDelimeter, CurrentPos);

                auto DecodedObject = GetLeveledObjectFromModifier(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos));

                CurrentPos         = NewModifierPos + 1;

                if (!DecodedObject.bValid) {
                    continue;
                }
                _DMESSAGE("Decoded object found");

                func(vLeveledList, DecodedObject.data);
            }


        }

        template <typename F>
        bool ProcessInsertReplaceMoficiator(LeveledLists::StoredData& storedData, std::string_view ModifierSection, F func)
        {
            bool   bAffected      = false;
            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;

            NewModifierPos = ModifierSection.find(sParametersDelimeter, CurrentPos);

            if (NewModifierPos == NONPOS) {
                _DRTFPError("Insert LVL List::No parameters in>>{}", ModifierSection);
                return false;
            }

            auto DecodedObject = GetLeveledObjectFromModifier(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos));

            if (!DecodedObject.bValid) {
                return false;
            }

            CurrentPos = NewModifierPos + 1;

            auto Position = GetNumberFromString<float>(ModifierSection.substr(CurrentPos, ModifierSection.length() - CurrentPos));
            
            if (!Position.bSuccess) {
                _DRTFPError("Insert LVL List::Cannot convert Position to float>>{}, Modifier>>{}", ModifierSection,
                          ModifierSection.substr(CurrentPos, ModifierSection.length() - CurrentPos));
                return false;
            }

            int Pos = (int)Position.data;

            if (Pos >= storedData.vEntries.size()) {
                _DRTFPError("Insert LVL List::Cannot insert to pos>>{} because size of array is>> {}", Pos, storedData.vEntries.size());
                return false;
            }
            else if (Pos > iMaxLVLListCount -1)
            {
                _DRTFPError("Insert LVL List::Cannot insert to pos>>{} because max size of LVLed list is>> {}", Pos, iMaxLVLListCount - 1);
                return false;
            }

            storedData.SetAffected();
            func(storedData.vEntries, DecodedObject.data, Pos);
            return true;
        }
        
        template < typename F>
        void InsertReplaceForm(LeveledLists::StoredData& StoredData, std::string_view ModifierSection, F func)
        {
            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;

            while (NewModifierPos != NONPOS) {
                NewModifierPos = ModifierSection.find(sArrDelimeter, CurrentPos);
                ProcessInsertReplaceMoficiator(StoredData, ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos), func);
                CurrentPos = NewModifierPos + 1;
            }

        }





        template <typename _FuncProcess>
        void AddConditionToEntry(LeveledLists::StoredData& storedData, std::string_view ModifierSection, _FuncProcess funcProcess)
        {
            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;

            NewModifierPos = ModifierSection.find(sParametersDelimeter, CurrentPos);

            if (NewModifierPos == NONPOS) {
                _DRTFPError("No comma in>>{}", ModifierSection);
                return;
            }

            auto DecodedObjectOne = LeveledLists::GetLeveledObjectFromModifier(ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos));

            if (!DecodedObjectOne.bValid) {
                return;
            }

            CurrentPos = NewModifierPos + 1;


            auto FoundLVLObject = GetLeveledObjectFromVector(storedData.vEntries, DecodedObjectOne.data);

            if (!FoundLVLObject)
            {
                _DRTFPError("no specified LVL list object in the LVLed list.");
                return;
            }



            if (!FoundLVLObject->conditions) {

                _DMESSAGE("No TESCondition - trying to create.");
                auto Condition = Condition::GetTESConditionByName(ModifierSection.substr(CurrentPos, ModifierSection.length() - CurrentPos));

                if (!Condition) {
                    _DRTFPError("Condition with specified name not found>>{}", ModifierSection.substr(CurrentPos, ModifierSection.length() - CurrentPos));
                    return;
                }

                FoundLVLObject->conditions = new RE::TESCondition;
                FoundLVLObject->conditions->head = NULL;
                FoundLVLObject->conditions->unk0 = NULL;
                _DMESSAGE("No condition - creating.");
            }


            if (Condition::AddConditionToConditionArray((*FoundLVLObject->conditions), ModifierSection.substr(CurrentPos, ModifierSection.length() - CurrentPos)))
            {
                storedData.SetAffected();
            }
            return;
        }







        //void ReplaceLVLObject(std::vector<RE::LEVELED_OBJECT>& Arr, RE::LEVELED_OBJECT& CurrentObject, int Pos)
        //{

        //   for (auto it = vEntries.begin(); it != StoredData.vEntries.end();) {
        //        if (Iter.level == CurrentObject.level && Iter.form == CurrentObject.form && Iter.count == CurrentObject.count && Iter.chanceNone == CurrentObject.chanceNone) {
        //            if (!StoredData.bAffected) {
        //                StoredData.bAffected = true;
        //            }
        //            it = StoredData.vEntries.erase(it);
        //        }
        //        else {
        //            it++;
        //        }
        //    }


        //}



        template <class FlagRequest>
        static bool _forceinline IsFormFlagSet(RE::TESLevCharacter* formIN, FlagRequest& iFlagRequest)
        {
            return formIN->flags & iFlagRequest;
        }


        constexpr std::uint8_t GetFlagFromFlagName(unsigned long FlagName)
        {
            switch (FlagName) {
            case sLVLListFlagCalculateFromAllLevels:
                return (std::uint8_t)RE::TESLeveledList::Flag::kCalculateFromAllLevelsLTOrEqPCLevel;
            case sLVLListFlagCalculateForEachItem:
                return (std::uint8_t)RE::TESLeveledList::Flag::kCalculateForEachItemInCount;
            case sLVLListFlagCalculateAll:
                return (std::uint8_t)RE::TESLeveledList::Flag::kUseAll;
            default:
                if (std::is_constant_evaluated()) {
                    throw "Add types to GetFlagFromFlagName function";
                }
                else {
                    _DRTFPError("Unknown flags for LVLed lists");
                }
                return 0;
            }
        }



        template <bool bSet>
        void ProcessFlagsForLVLLists(std::uint8_t& Flags, unsigned long CurrentModifierValue)
        {

            switch (CurrentModifierValue) {

                _SetOrRemoveFlag(sLVLListFlagCalculateFromAllLevels, Input::LeveledLists::GetFlagFromFlagName)
                _SetOrRemoveFlag(sLVLListFlagCalculateForEachItem, Input::LeveledLists::GetFlagFromFlagName)
                _SetOrRemoveFlag(sLVLListFlagCalculateAll, Input::LeveledLists::GetFlagFromFlagName)

                   
            default:
                _DRTFPError("Invalid flag for LVLed Lists.");
                break;
            }
        }
    }


    namespace Cell
    {
        template <class FlagRequest>
        static bool _forceinline IsFormFlagSet(RE::TESObjectCELL* formIN, FlagRequest& iFlagRequest)
        {
            return formIN->cellFlags.underlying() & iFlagRequest;
        }

        constexpr std::uint32_t GetFlagFromFlagName(unsigned long FlagName)
        {
            switch (FlagName) {
            case sCellFlagCanFastTravel:
                return (std::uint32_t)RE::TESObjectCELL::Flag::kCanFastTravel;
            case sCellFlagPublic:
                return (std::uint32_t)RE::TESObjectCELL::Flag::kPublic;

            default:
                if (std::is_constant_evaluated()) {
                    throw "Add types to GetFlagFromFlagName function";
                }
                else {
                    _DRTFPError("Unknown flags for Cell");
                }
                return 0;
            }
        }

        template <bool bSet>
        void ProcessFlags(std::uint32_t& Flags, unsigned long CurrentModifierValue)
        {
            switch (CurrentModifierValue) {
                _SetOrRemoveFlag(sCellFlagCanFastTravel, Cell::GetFlagFromFlagName)
                 _SetOrRemoveFlag(sCellFlagPublic, Cell::GetFlagFromFlagName)
            default:
                _DRTFPError("Invalid flag for Cell.");
                break;
            }
        }


    }





    void ProcessModifierForLeveledList(unsigned long CurrentModifierName, std::string_view CurrentModifierValue, RE::TESLevCharacter* CurrentForm,
                                       LeveledLists::StoredData& StoredData)
    {



        bool bAffected = false;
        switch (CurrentModifierName) {
        case sLVLListArrayAdd:

            if (StoredData.EntriesCopiedOrValid(CurrentForm))
            {
                if (StoredData.CanAddNewItem()) {
                    LeveledLists::AddRemoveForm(StoredData, CurrentModifierValue, LeveledLists::AddLeveledObjectToLeveledList);
                }
                else {
                    _DRTFPError("Cannot add new item to LVLed List - max count exceeded.");
                }

            }

            break;
        case sLVLListArrayRemove:
            if (StoredData.EntriesCopiedOrValid(CurrentForm)) {
                LeveledLists::AddRemoveForm(StoredData, CurrentModifierValue, LeveledLists::RemoveLeveledObjectFromLeveledList);
            }

            break;
        case sLVLListArrayInsert:
            if (StoredData.EntriesCopiedOrValid(CurrentForm)) {

                if (StoredData.CanAddNewItem()) {
                    LeveledLists::InsertReplaceForm(StoredData, CurrentModifierValue, Array::InsertObject<std::vector<RE::LEVELED_OBJECT>, RE::LEVELED_OBJECT>);
                }
                else {
                    _DRTFPError("Cannot insert new item to LVLed List - max count exceeded.");
                }

            }
            break;

        case sLVLListArrayReplace:
            if (StoredData.EntriesCopiedOrValid(CurrentForm)) {
                ArrayNonForm::_ReplaceInArray(StoredData, CurrentModifierValue,
                                              LeveledLists::ReplaceLeveledObjectFromLeveledList,
                                              LeveledLists::GetLeveledObjectFromModifier);

                //LeveledLists::InsertReplaceForm(StoredData, CurrentModifierValue, Array::InsertObject<std::vector<RE::LEVELED_OBJECT>, RE::LEVELED_OBJECT>);
            }
            break;

        case sLVLListArrayDontSort:
            StoredData.bDontSort = true;
            break;

        case sCondidtionAddToForm:
            Condition::AddRemove(CurrentForm->conditions, CurrentModifierValue, Condition::AddConditionToConditionArray);
            break; 
        case sLVLListCondidtionAddToEntry:
            if (StoredData.EntriesCopiedOrValid(CurrentForm)) {
                LeveledLists::AddConditionToEntry(StoredData, CurrentModifierValue, LeveledLists::GetLeveledObjectFromModifier);
            }
            break;

        case sLVLListChanceGlobal:
            _SetFormFromModifier(CurrentForm->chanceGlobal);
            break;


        case sValueFlagSet:
            ProcessFlagModifierAlt<true>((std::uint8_t&)CurrentForm->flags, CurrentModifierValue, LeveledLists::ProcessFlagsForLVLLists<true>);
            break;
        case sValueFlagUnset:
            ProcessFlagModifierAlt<false>((std::uint8_t&)CurrentForm->flags, CurrentModifierValue, LeveledLists::ProcessFlagsForLVLLists<false>);
            break;
        default:
            _DRTFPError("Modifier is not valid for {}, formID>>{:08X}", RE::FormTypeToString(CurrentForm->GetFormType()), CurrentForm->formID);
        }
    }

    template <class T>
    void ProcessModifiersForLeveledList(T* CurrentForm, std::string_view& ModifierSection)
    {

        size_t CurrentPos     = 0;
        size_t NewModifierPos = 0;

        auto StoredLVlList = LeveledLists::GetOrCreateStoredItem((RE::TESLevCharacter*)CurrentForm);


        while (NewModifierPos != NONPOS) {
            NewModifierPos = ModifierSection.find(sSectionDelimeter, CurrentPos);
            _DMESSAGE("Modifier pos>>{}, CurrentPos>>{}", NewModifierPos, CurrentPos);

            std::string_view CurrentModifier = ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos);
            //_DMESSAGE("Modifier>>>{}", CurrentModifier);

            auto BracketLeftPos = CurrentModifier.find(sValueDelimeterLeft);

            if (BracketLeftPos != NONPOS) {
                std::string_view CurrentModifierName = CurrentModifier.substr(0, BracketLeftPos);

                auto BracketRightPos = CurrentModifier.find_last_of(sValueDelimeterRight);

                if (BracketRightPos != NONPOS) {
                    std::string_view CurrentModifierValue = CurrentModifier.substr(BracketLeftPos + 1, BracketRightPos - BracketLeftPos - 1);

                    _DMESSAGE("ProcessModifiersForForm Modifier>>{}, Modifier value>>{}", CurrentModifierName, CurrentModifierValue);
                    ProcessModifierForLeveledList(hash_djb2a(CurrentModifierName), CurrentModifierValue, CurrentForm,  *StoredLVlList);
                }
            }

            CurrentPos = NewModifierPos + 1;
        }


        
        if (StoredLVlList->bAffected)
        {
            if (!StoredLVlList->bDontSort) {
                _DMESSAGE("Sorting lvlList.");
                std::sort(StoredLVlList->vEntries.begin(), StoredLVlList->vEntries.end(), [](RE::LEVELED_OBJECT& a, RE::LEVELED_OBJECT& b) -> bool { return a.level < b.level; });
            }
        }
        else {
            _DMESSAGE("List was not affected.");
        }


        //if (!IsFlagSet(iTempCopyFlags, LeveledLists::k_DontSort)) {
        //    _DMESSAGE("Sorting lvlList.");

        //    std::sort(v_LeveledObjectCopy.begin(), v_LeveledObjectCopy.end(), [](RE::LEVELED_OBJECT& a, RE::LEVELED_OBJECT& b) -> bool { return a.level < b.level;
        //    });
        //}
        //else {
        //    _DMESSAGE("not sorting lvlList..");
        //}

        //if (IsFlagSet(iTempCopyFlags, LeveledLists::k_Affected))
        //{
        //    _DMESSAGE("Copy created - replacing old Leveled List");
        //    LeveledLists::ReplaceLeveledObjectsInLeveledList(CurrentForm->leveledLists, CurrentForm->baseListCount, v_LeveledObjectCopy);
        //}
    }



    namespace Filters
    {

        enum ComparisonOperators
        {
            k_None,
            kEqual,
            kNotEqual,
            kLarger,
            kLesser
        };

        struct ComparisonData
        {
            int iCurrentComparison = ComparisonOperators::k_None;
            double data = 0;
        };



        template <class T>
        bool _forceinline CompareMemberValueIsEqual(double& ComparisonData,T& Value)
        {
            return Value == ComparisonData;
        }

        template <class T>
        bool _forceinline CompareMemberValueIsLarger(double& ComparisonData, T& Value)
        {
            if (Value > ComparisonData)
            {
                //_DMESSAGE("{} is more than {}", Value, ComparisonData);
                return true;
            }
            else {
                //_DMESSAGE("{} is less than {}", Value, ComparisonData);
                return false;
            }
        }

        template <class T>
        bool _forceinline CompareMemberValueIsLesser(double& ComparisonData, T& Value)
        {
            return Value < ComparisonData;
        }


        template <class T>
        ComparisonData GetComparisonDataFromString(std::string_view CurrentModifierValue, T& CurrentValue)
        {
            _DMESSAGE("FilterByMemberValue {}", CurrentModifierValue);
            ComparisonData result;
            switch (CurrentModifierValue.at(0)) {
            case sFilterEqual:
                result.iCurrentComparison = ComparisonOperators::kEqual;
                break;
            case sFilterNotEqual:
                result.iCurrentComparison = ComparisonOperators::kNotEqual;
                break;
            case sFilterLarger:
                result.iCurrentComparison = ComparisonOperators::kLarger;
                break;
            case sFilterLesser:
                result.iCurrentComparison = ComparisonOperators::kLesser;
                break;
            default:
                _DRTFPError("Comparison with that symbol is not supported>>{}", CurrentModifierValue);
                return result;
            }
            auto ValueDouble = GetNumberFromString(CurrentValue,CurrentModifierValue.substr(1, CurrentModifierValue.size() - 1));

           if (!ValueDouble.bSuccess) {
                result.iCurrentComparison = ComparisonOperators::k_None; // so it doesn't go further.
                return result;
           }
           result.data = std::move(ValueDouble.data);
           _DMESSAGE("Comparison sign>>{},comparison double>>{}", result.iCurrentComparison, result.data);
           return result;
        }





         template <class T>
        __forceinline std::int32_t& GetMemberValueFromForm(T formIn)
        {
           return formIn->value;
        }

        template <>
        __forceinline std::int32_t& GetMemberValueFromForm(RE::TESObjectWEAP* formIn)
        {
           return formIn->weaponData.get()->WeapDataGeneral->baseValue;
        }

        template <>
        __forceinline std::int32_t& GetMemberValueFromForm(RE::TESObjectARMO* formIn)
        {
           return formIn->instanceData.value().value;
        }




        template <class T>
        __forceinline float& GetWeightFromForm(T formIn)
        {
           return formIn->weight;
        }

         template <>
        __forceinline float& GetWeightFromForm(RE::TESObjectWEAP* formIn)
        {
           return formIn->weaponData.get()->WeapDataGeneral->baseWeight;
        }

        template <>
        __forceinline float& GetWeightFromForm(RE::TESObjectARMO* formIn)
        {
           return formIn->instanceData.value().weight;
        }




        template <typename FormType, unsigned long FilterName, typename FuncToGetValue>
        void FilterFormsByValue(std::vector<RE::TESForm*>& vForms, std::vector<TempModifier>& Filters, FuncToGetValue funcToGetValue)
        {
           std::vector<FormType>& vFormsCasted = *((std::vector<FormType>*)&vForms);

           for (auto it = Filters.begin(); it != Filters.end(); it++) {
                switch (Iter.CurrentModifierName) {
                case FilterName:
                    auto ComparisonResult = Filters::GetComparisonDataFromString(Iter.CurrentModifierValue, funcToGetValue(vFormsCasted.at(0)));

                    if (ComparisonResult.iCurrentComparison == Filters::ComparisonOperators::k_None) {
                        continue;
                    }
                    else if (ComparisonResult.iCurrentComparison == Filters::ComparisonOperators::kEqual) {
                        for (auto it = vFormsCasted.begin(); it != vFormsCasted.end();) {
                            if (Filters::CompareMemberValueIsEqual(ComparisonResult.data, funcToGetValue(Iter))) {
                                it++;
                            }
                            else {
                                _DMESSAGE("Removing {:08X} from filters because of value check,Value>>{}.", Iter->formID, funcToGetValue(Iter));
                                it = vFormsCasted.erase(it);
                            }
                        }
                    }
                    else if (ComparisonResult.iCurrentComparison == Filters::ComparisonOperators::kNotEqual) {
                        for (auto it = vFormsCasted.begin(); it != vFormsCasted.end();) {
                            if (!Filters::CompareMemberValueIsEqual(ComparisonResult.data, funcToGetValue(Iter))) {
                                it++;
                            }
                            else {
                                _DMESSAGE("Removing {:08X} from filters because of value check,Value>>{}.", Iter->formID, funcToGetValue(Iter));
                                it = vFormsCasted.erase(it);
                            }
                        }
                    }
                    else if (ComparisonResult.iCurrentComparison == Filters::ComparisonOperators::kLarger) {
                        for (auto it = vFormsCasted.begin(); it != vFormsCasted.end();) {
                            if (Filters::CompareMemberValueIsLarger(ComparisonResult.data, funcToGetValue(Iter))) {
                                it++;
                            }
                            else {
                                _DMESSAGE("Removing {:08X} from filters because of value check,Value>>{}.", Iter->formID, funcToGetValue(Iter));
                                it = vFormsCasted.erase(it);
                            }
                        }
                    }
                    else if (ComparisonResult.iCurrentComparison == Filters::ComparisonOperators::kLesser) {
                        for (auto it = vFormsCasted.begin(); it != vFormsCasted.end();) {
                            if (Filters::CompareMemberValueIsLesser(ComparisonResult.data, funcToGetValue(Iter))) {
                                it++;
                            }
                            else {
                                _DMESSAGE("Removing {:08X} from filters because of value check,Value>>{}.", Iter->formID, funcToGetValue(Iter));
                                it = vFormsCasted.erase(it);
                            }
                        }
                    }
                }
           }

        }




        void FilterByIncludePlugins(std::vector<RE::TESForm*>& vForms, std::vector<LoadedPlugins::Plugin*>& vFilters)
        // Form must BE in any plugin which is in the vector. If it is not - remove.
        {

            if (!vFilters.size())
            {
                _DMESSAGE("no plugins detected in included plugins - clearing all the forms.");
                vForms.clear();
                return;
            }

            for (auto it = vForms.begin(); it != vForms.end();) {
                bool bFound = false;

                for (auto it2 = vFilters.begin(); it2 != vFilters.end(); it2++) {
                    //_DMESSAGE("Form mod Index>>{}, comparing with {}", Iter->formID >> 24,Iter2);
                    if (Iter2->IsFormInPlugin(Iter->formID)) {
                        bFound = true;
                        break;
                    }
                }

                if (!bFound) {
                    it = vForms.erase(it);
                }
                else {
                    it++;
                }
            }
        }

        void FilterByExcludePlugins(std::vector<RE::TESForm*>& vForms, std::vector<LoadedPlugins::Plugin*>& vFilters)
        // Form must NOT be in any plugin which is in the vector. If it is - remove.
        {
            if (!vFilters.size())
            {
                _DMESSAGE("no plugins detected - skipping the check");
                return;
            }


            for (auto it = vForms.begin(); it != vForms.end();) {
                bool bFound = false;

                for (auto it2 = vFilters.begin(); it2 != vFilters.end(); it2++) {
                    if (Iter2->IsFormInPlugin(Iter->formID)) {
                        bFound = true;
                        break;
                    }
                }

                if (bFound) {
                    it = vForms.erase(it);
                }
                else {
                    it++;
                }
            }
        }

        template <typename Func>
        void ProcessFiltersByPlugins(std::vector<RE::TESForm*>& vForms, std::string_view Filters, Func func)
        {
            _DMESSAGE("ProcessFiltersByPlugins starts");
            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;

            std::vector<LoadedPlugins::Plugin*> vModIndexes;

            while (NewModifierPos != NONPOS) {
                NewModifierPos = Filters.find(sArrDelimeter, CurrentPos);

                auto PluginInfo = LoadedPlugins::GetModInfo(Filters.substr(CurrentPos, NewModifierPos - CurrentPos));

                if (PluginInfo != NULL) {
                    _DMESSAGE("added mod index of <{}> to Filter array.", Filters.substr(CurrentPos, NewModifierPos - CurrentPos));
                    vModIndexes.push_back(PluginInfo);
                }
                CurrentPos = NewModifierPos + 1;
            }

            func(vForms, vModIndexes);
        }

        template <typename FormType>
        void FilterByIncludeKeyword(std::vector<FormType>& vForms, std::vector<uint32_t>& vFilters) // All must be included, otherwise remove.
        {

            for (auto it = vForms.begin(); it != vForms.end();) {
                bool bRemove = false;

                for (auto it2 = vFilters.begin(); it2 != vFilters.end(); it2++) {
                    bool bFound = false;

                    for (auto it3 = Iter->keywords.begin(); it3 != Iter->keywords.end(); it3++) {
                        if (Iter3->formID == Iter2) {
                            bFound = true;
                            break;
                        }
                    }

                    if (!bFound) {
                        bRemove = true;
                        break;
                    }
                }

                if (bRemove) {
                    it = vForms.erase(it);
                }
                else {
                    it++;
                }
            }
        }

        template <typename FormType>
        void FilterByIncludeKeywordAny(std::vector<FormType>& vForms, std::vector<uint32_t>& vFilters) // Any must be included,otherwise remove
        {

            for (auto it = vForms.begin(); it != vForms.end();) {
                //_DMESSAGE("Checking form>>{:08X}", Iter->formID);
                bool bFound = false;
                for (auto it2 = vFilters.begin(); it2 != vFilters.end(); it2++) {
                    for (auto it3 = Iter->keywords.begin(); it3 != Iter->keywords.end(); it3++) {
                        //_DMESSAGE("Checkig keyword>>{:08X}", Iter3->formID);
                        if (Iter3->formID == Iter2) {
                            bFound = true;
                            break;
                        }
                    }

                    if (bFound) {
                        break;
                    }
                }

                if (bFound) {
                    it++;
                }
                else {
                    it = vForms.erase(it);
                }
            }
        }

        template <typename FormType>
        void FilterByExcludeKeyword(std::vector<FormType>& vForms, std::vector<uint32_t>& vFilters) // All must be excluded, otherwise remove
        {

            for (auto it = vForms.begin(); it != vForms.end();) {
                bool bRemove = false;

                for (auto it2 = vFilters.begin(); it2 != vFilters.end(); it2++) {
                    bool bFound = false;

                    for (auto it3 = Iter->keywords.begin(); it3 != Iter->keywords.end(); it3++) {
                        if (Iter3->formID == Iter2) {
                            bFound = true;
                            break;
                        }
                    }

                    if (bFound) {
                        bRemove = true;
                        break;
                    }
                }

                if (bRemove) {
                    it = vForms.erase(it);
                }
                else {
                    it++;
                }
            }
        }

        template <typename FormType>
        void FilterByExcludeKeywordAny(std::vector<FormType>& vForms, std::vector<uint32_t>& vFilters) // Any must be excluded, otherwise remove
        {


            for (auto it = vForms.begin(); it != vForms.end();) {
                bool bFound = false;

                for (auto it2 = vFilters.begin(); it2 != vFilters.end(); it2++) {
                    for (auto it3 = Iter->keywords.begin(); it3 != Iter->keywords.end(); it3++) {
                        if (Iter3->formID == Iter2) {
                            bFound = true;
                            break;
                        }
                    }

                    if (bFound) {
                        break;
                    }
                }

                if (bFound) {
                    it = vForms.erase(it);
                }
                else {
                    it++;
                }
            }
        }

        template <bool bRemoveIfNoFilters,typename FormType, typename Func>
        void ProcessFiltersByFormIDs(std::vector<FormType>& vForms, std::string_view Filters, Func func)
        {
            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;

            std::vector<uint32_t> vFilters;

            if (Filters.at(0) == sSearchForFilters) {
                auto CustomFilter = Input::CustomFilters::GetFilterByNameAndCheckForSection(Filters.substr(1, Filters.length() - 1), (std::uint8_t)RE::FormType::kKYWD);

                if (!CustomFilter) {
                    _DRTFPError("Cannot find a filter with name>>{}", Filters.substr(1, Filters.length() - 1));
                    return;
                }

                vFilters.reserve(CustomFilter->forms.size());

                for (auto it = CustomFilter->forms.begin(); it != CustomFilter->forms.end(); it++) {
                    _DMESSAGE("Adding keyword to Filters from a custom filter>>{:08X}", Iter->formID);
                    vFilters.push_back(Iter->formID);
                }
            }
            else {
                vFilters.reserve(4);

                while (NewModifierPos != NONPOS) {
                    NewModifierPos = Filters.find(sArrDelimeter, CurrentPos);

                    auto CurrentForm
                        = GetFormFromStringAndCheckForCategory<false>(Filters.substr(CurrentPos, NewModifierPos - CurrentPos), const_GetTypeFromFormType<RE::BGSKeyword*>());
                    CurrentPos       = NewModifierPos + 1;

                    if (!CurrentForm.bValid) {
                        continue;
                    }
                    _DMESSAGE("Adding keyword to Filters", CurrentForm.data->formID);
                    vFilters.push_back(CurrentForm.data->formID);
                }
            }

            if (!vFilters.size()) {
                _DMESSAGE("Filters are empty");

                if constexpr (bRemoveIfNoFilters == true)
                {
                    _DMESSAGE("Cleaning forms");
                    vForms.clear();
                }

                return;
            }

            func(vForms, vFilters);
        }

        template <typename FormType>
        void FilterArrayByKeywords(std::vector<RE::TESForm*>& vForms, std::vector<TempModifier>& Filters)
        {
            std::vector<FormType>* vFormsCasted = (std::vector<FormType>*)&vForms;

            for (auto it = Filters.begin(); it != Filters.end(); it++) {
                switch (Iter.CurrentModifierName) {
                case sFiltersKeywordInclude:
                    ProcessFiltersByFormIDs<true,FormType>((*vFormsCasted), Iter.CurrentModifierValue, FilterByIncludeKeyword<FormType>);
                    break;
                case sFiltersKeywordExclude:
                    ProcessFiltersByFormIDs<false,FormType>((*vFormsCasted), Iter.CurrentModifierValue, FilterByExcludeKeyword<FormType>);
                    break;
                case sFiltersKeywordIncludeAny:
                    ProcessFiltersByFormIDs<true, FormType>((*vFormsCasted), Iter.CurrentModifierValue, FilterByIncludeKeywordAny<FormType>);
                    break;
                case sFiltersKeywordExcludeAny:
                    ProcessFiltersByFormIDs<false, FormType>((*vFormsCasted), Iter.CurrentModifierValue, FilterByExcludeKeywordAny<FormType>);
                    break;
                }
            }
        }

        bool IsFormInFormList(std::uint32_t& formID, RE::BGSListForm* FormList)
        {
            for (auto it = FormList->arrayOfForms.begin(); it != FormList->arrayOfForms.end(); it++) {
                if (Iter->formID == formID) {
                    return true;
                }
            }
            return false;
        }

        void FilterByIncludeInFormList(std::vector<RE::TESForm*>& vForms, std::vector<RE::BGSListForm*>& vFilters)
        // Form be included,otherwise remove
        {
            for (auto it = vForms.begin(); it != vForms.end();) {
                bool bFound = false;

                for (auto it2 = vFilters.begin(); it2 != vFilters.end(); it2++) {
                    if (IsFormInFormList(Iter->formID, Iter2)) {
                        bFound = true;
                        break;
                    }
                }

                if (!bFound) {
                    it = vForms.erase(it);
                }
                else {
                    it++;
                }
            }
        }

        void FilterByExcludeInFormList(std::vector<RE::TESForm*>& vForms, std::vector<RE::BGSListForm*>& vFilters)
        // Form must be excluded, otherwise remove
        {
            for (auto it = vForms.begin(); it != vForms.end();) {
                bool bFound = false;

                for (auto it2 = vFilters.begin(); it2 != vFilters.end(); it2++) {
                    if (IsFormInFormList(Iter->formID, Iter2)) {
                        bFound = true;
                        break;
                    }
                }

                if (bFound) {
                    it = vForms.erase(it);
                }
                else {
                    it++;
                }
            }
        }

        void FilterByProjInAmmo(std::vector<RE::BGSProjectile*>& vForms, std::vector<RE::TESAmmo*>& vFilters)
        {
            for (auto it = vForms.begin(); it != vForms.end();) {
                bool bFound = false;

                for (auto it2 = vFilters.begin(); it2 != vFilters.end(); it2++) {
                    if (Iter2->data.projectile == Iter) {
                        bFound = true;
                        break;
                    }
                }
                if (bFound) {
                    it++;
                }
                else {
                    it = vForms.erase(it);
                }
            }
        }

        bool _forceinline ProjectileInAmmo(RE::BGSProjectile* Form1, RE::TESAmmo* Form2)
        {
            return (Form2->data.projectile == Form1);
        }

        bool _forceinline NPCHasRace(RE::TESNPC* Form1, RE::TESRace* Form2)
        {
            return (Form1->formRace == Form2);
        }

        bool _forceinline COBJHasKeyword(RE::BGSConstructibleObject* Form1, RE::BGSKeyword* Form2)
        {
            return (Form1->benchKeyword == Form2);
        }

        template <typename FilteredFormType, typename iterator>
        void _forceinline LeaveIfFound(iterator& it, bool& bFound, std::vector<FilteredFormType>& vForms)
        {
             if (bFound) {
                it++;
             }
             else {
                it = vForms.erase(it);
             }
        }

        template <typename FilteredFormType, typename iterator>
        void _forceinline RemoveIfFound(iterator& it, bool& bFound, std::vector<FilteredFormType>& vForms)
        {
             if (bFound) {
                it = vForms.erase(it);
             }
             else {
                it++;
             }
        }




        template <class FilteredFormType, class TargetFormType, typename FunctionToFilter, typename FunctionToProcess>
        void FilterUniversalFindAll(std::vector<FilteredFormType>& vForms, std::vector<TargetFormType>& vFilters, FunctionToFilter func, FunctionToProcess FuncToProcess)
        {
             for (auto it = vForms.begin(); it != vForms.end();) {
                bool bFound = true;

                for (auto it2 = vFilters.begin(); it2 != vFilters.end(); it2++) {

                    if (!func(Iter, Iter2)) {
                        bFound = false;
                        break;
                    }

                }
                FuncToProcess(it, bFound, vForms);
             }
        }



        template <class FilteredFormType, class TargetFormType, typename FunctionToFilter, typename FunctionToProcess>
        void FilterUniversalFindAny(std::vector<FilteredFormType>& vForms, std::vector<TargetFormType>& vFilters, FunctionToFilter func, FunctionToProcess FuncToProcess)
        {
            for (auto it = vForms.begin(); it != vForms.end();) {
                bool bFound = false;

                for (auto it2 = vFilters.begin(); it2 != vFilters.end(); it2++) {
                    if (func(Iter, Iter2)) {
                        bFound = true;
                        break;
                    }
                }
                FuncToProcess(it, bFound, vForms);
            }
        }




        template <bool bFindAll,typename FormType, typename TypeOfFlags, typename CompareFunc, typename FunctionToProcess, typename FunctionToGetFlags>
        void ProcessFiltersByFlags(std::vector<FormType>& vForms, std::string_view Filters, CompareFunc func, FunctionToProcess Func_To_Process, FunctionToGetFlags funcToGetFlags)
        {
            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;

            std::vector<TypeOfFlags> vFilters;

            while (NewModifierPos != NONPOS) {
                NewModifierPos = Filters.find(sArrDelimeter, CurrentPos);

                _DMESSAGE("new flag to process>>{}", Filters.substr(CurrentPos, NewModifierPos - CurrentPos));
                auto FlagResult = funcToGetFlags(hash_djb2a(Filters.substr(CurrentPos, NewModifierPos - CurrentPos)));

                if (FlagResult != iFlagResultBadFlag) {
                    vFilters.push_back(FlagResult);
                }
                CurrentPos = NewModifierPos + 1;
            }

            if (!vFilters.size()) {
                _DMESSAGE("Filters are empty");
                return;
            }

            _DMESSAGE("Filter flags count>>{}", vFilters.size());


            
            if constexpr (bFindAll)
            {
                FilterUniversalFindAll(vForms, vFilters, func, Func_To_Process);
            }
            else {
                FilterUniversalFindAny(vForms, vFilters, func, Func_To_Process);
            }

        }




        template <bool bRemoveIfNoFilters, typename FormType, typename FormTypeSecond, typename Func, class FormTypeID, typename FunctionToProcess>
        void ProcessFiltersByFormsAlt(std::vector<FormType>& vForms, std::string_view Filters, Func func, FormTypeID _FormType, FunctionToProcess Func_To_Process)
        {
            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;

            std::vector<FormTypeSecond> vFilters;

            if (Filters.at(0) == sSearchForFilters) {
                auto CustomFilter = Input::CustomFilters::GetFilterByNameAndCheckForSection(Filters.substr(1, Filters.length() - 1), _FormType);

                if (!CustomFilter) {
                    _DRTFPError("Cannot find a filter with name>>{}", Filters.substr(1, Filters.length() - 1));
                    return;
                }

                vFilters.reserve(CustomFilter->forms.size());

                for (auto it = CustomFilter->forms.begin(); it != CustomFilter->forms.end(); it++) {
                    vFilters.push_back((FormTypeSecond)Iter);
                }
            }
            else {
                vFilters.reserve(4);

                while (NewModifierPos != NONPOS) {
                    NewModifierPos = Filters.find(sArrDelimeter, CurrentPos);

                    auto CurrentForm = GetFormFromStringAndCheckForCategory<false>(Filters.substr(CurrentPos, NewModifierPos - CurrentPos), _FormType);
                    CurrentPos       = NewModifierPos + 1;

                    if (!CurrentForm.bValid) {
                        continue;
                    }

                    vFilters.push_back((FormTypeSecond)CurrentForm.data);
                }
            }

            if (!vFilters.size()) {
                _DMESSAGE("Filters are empty");

                if constexpr (bRemoveIfNoFilters == true) {
                    _DMESSAGE("Removing forms");
                    vForms.clear();
                }

                return;
            }

            FilterUniversalFindAny(vForms, vFilters, func, Func_To_Process);
        }
    






        template <bool bRemoveIfNoFilters,typename FormType, typename FormTypeSecond, typename Func, class FormTypeID>
        void ProcessFiltersByForms(std::vector<FormType>& vForms, std::string_view Filters, Func func, FormTypeID _FormType)
        {
            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;

            std::vector<FormTypeSecond> vFilters;

            if (Filters.at(0) == sSearchForFilters) {
                auto CustomFilter = Input::CustomFilters::GetFilterByNameAndCheckForSection(Filters.substr(1, Filters.length() - 1), _FormType);

                if (!CustomFilter) {
                    _DRTFPError("Cannot find a filter with name>>{}", Filters.substr(1, Filters.length() - 1));
                    return;
                }

                vFilters.reserve(CustomFilter->forms.size());

                for (auto it = CustomFilter->forms.begin(); it != CustomFilter->forms.end(); it++) {
                    vFilters.push_back((FormTypeSecond)Iter);
                }
            }
            else {
                vFilters.reserve(4);

                while (NewModifierPos != NONPOS) {
                    NewModifierPos = Filters.find(sArrDelimeter, CurrentPos);

                    auto CurrentForm = GetFormFromStringAndCheckForCategory<false>(Filters.substr(CurrentPos, NewModifierPos - CurrentPos), _FormType);
                    CurrentPos       = NewModifierPos + 1;

                    if (!CurrentForm.bValid) {
                        continue;
                    }

                    vFilters.push_back((FormTypeSecond)CurrentForm.data);
                }
            }

            if (!vFilters.size()) {
                _DMESSAGE("Filters are empty");

                if constexpr (bRemoveIfNoFilters == true)
                {
                    _DMESSAGE("Removing forms");
                    vForms.clear();
                }

                return;
            }

            func(vForms, vFilters);
        }


        void FilterProjectiles(std::vector<RE::TESForm*>& vForms, std::vector<TempModifier>& Filters)
        {
            std::vector<RE::BGSProjectile*>* vFormsCasted = (std::vector<RE::BGSProjectile*>*)&vForms;

            for (auto it = Filters.begin(); it != Filters.end(); it++) {
                switch (Iter.CurrentModifierName) {
                case sFiltersProjectileInAmmo:
                    ProcessFiltersByFormsAlt<true,RE::BGSProjectile*, RE::TESAmmo*>((*vFormsCasted), Iter.CurrentModifierValue, ProjectileInAmmo, (std::uint8_t)RE::FormType::kAMMO,LeaveIfFound<RE::BGSProjectile*, std::vector<RE::BGSProjectile*>::iterator>);
                    break;
                case sFiltersProjectileNotInAmmo:
                    ProcessFiltersByFormsAlt<false,RE::BGSProjectile*, RE::TESAmmo*>((*vFormsCasted), Iter.CurrentModifierValue, ProjectileInAmmo, (std::uint8_t)RE::FormType::kAMMO,
                                                                               RemoveIfFound<RE::BGSProjectile*, std::vector<RE::BGSProjectile*>::iterator>);
                    break;
                }
            }
        }


        void FilterSpells(std::vector<RE::TESForm*>& vForms, std::vector<TempModifier>& Filters)
        {
            std::vector<RE::SpellItem*>* vFormsCasted = (std::vector<RE::SpellItem*>*)&vForms;

            for (auto it = Filters.begin(); it != Filters.end(); it++) {
                switch (Iter.CurrentModifierName) {
                case 11:
                    //ProcessFiltersByFormsAlt<RE::BGSProjectile*, RE::TESAmmo*>((*vFormsCasted), Iter.CurrentModifierValue, FilterByProjInAmmo, (std::uint8_t)RE::FormType::kAMMO);
                    break;
                }
            }
        }


        void FilterByAmmoInWeap(std::vector<RE::TESAmmo*>& vForms, std::vector<RE::TESObjectWEAP*>& vFilters)
        {
            for (auto it = vForms.begin(); it != vForms.end();) {
                bool bFound = false;

                for (auto it2 = vFilters.begin(); it2 != vFilters.end(); it2++) {

                    if (Iter2->weaponData.get()->WeaponAmmoData->ammo == Iter)
                    {
                        bFound = true;
                        break;
                    }
                }

                if (bFound) {
                    it++;
                }
                else {
                    it = vForms.erase(it);
                }
            }
        }


        void FilterAmmo(std::vector<RE::TESForm*>& vForms, std::vector<TempModifier>& Filters)
        {
            std::vector<RE::TESAmmo*>* vFormsCasted = (std::vector<RE::TESAmmo*>*)&vForms;

            for (auto it = Filters.begin(); it != Filters.end(); it++) {
                switch (Iter.CurrentModifierName) {
                case sFiltersAmmoByWeapon:
                    ProcessFiltersByForms<true,RE::TESAmmo*, RE::TESObjectWEAP*>((*vFormsCasted), Iter.CurrentModifierValue, FilterByAmmoInWeap, (std::uint8_t)RE::FormType::kWEAP);
                    break;
                }
            }
        }


        void FilterByWeapWithAmmo(std::vector<RE::TESObjectWEAP*>& vForms, std::vector<RE::TESAmmo*>& vFilters)
        {
            for (auto it = vForms.begin(); it != vForms.end();) {
                bool bFound = false;

                for (auto it2 = vFilters.begin(); it2 != vFilters.end(); it2++) {
                    if (Iter->weaponData.get()->WeaponAmmoData->ammo == Iter2) {
                        bFound = true;
                        break;
                    }
                }

                if (bFound) {
                    it++;
                }
                else {
                    it = vForms.erase(it);
                }
            }
        }

        void FilterWeapon(std::vector<RE::TESForm*>& vForms, std::vector<TempModifier>& Filters)
        {
            std::vector<RE::TESObjectWEAP*>* vFormsCasted = (std::vector<RE::TESObjectWEAP*>*)&vForms;

            for (auto it = Filters.begin(); it != Filters.end(); it++) {
                switch (Iter.CurrentModifierName) {
                case sFiltersWeaponByAmmo:
                    ProcessFiltersByForms<true,RE::TESObjectWEAP*, RE::TESAmmo*>((*vFormsCasted), Iter.CurrentModifierValue, FilterByWeapWithAmmo,
                                                                            const_GetTypeFromFormType<RE::TESAmmo*>());
                    break;
                }
            }
        }


        void FilterMessage(std::vector<RE::TESForm*>& vForms, std::vector<TempModifier>& Filters)
        {

            std::vector<RE::BGSMessage*>* vFormsCasted = (std::vector<RE::BGSMessage*>*)&vForms;

            for (auto it = Filters.begin(); it != Filters.end(); it++) {
                switch (Iter.CurrentModifierName) {


                case sFilterByFlagSet:
                    ProcessFiltersByFlags<true, RE::BGSMessage*, std::uint32_t>((*vFormsCasted), Iter.CurrentModifierValue, Message::IsFormFlagSet<std::uint32_t>,
                                                                                LeaveIfFound<RE::BGSMessage*, std::vector<RE::BGSMessage*>::iterator>, Message::GetFlagFromFlagName);
                    break;
                case sFilterByFlagNotSet:
                    ProcessFiltersByFlags<true, RE::BGSMessage*, std::uint32_t>((*vFormsCasted), Iter.CurrentModifierValue, Message::IsFormFlagSet<std::uint32_t>,
                                                                                RemoveIfFound<RE::BGSMessage*, std::vector<RE::BGSMessage*>::iterator>,
                                                                                Message::GetFlagFromFlagName);
                    break;
                case sFilterByFlagSetAny:
                    ProcessFiltersByFlags<false, RE::BGSMessage*, std::uint32_t>((*vFormsCasted), Iter.CurrentModifierValue, Message::IsFormFlagSet<std::uint32_t>,
                                                                                 LeaveIfFound<RE::BGSMessage*, std::vector<RE::BGSMessage*>::iterator>,
                                                                                 Message::GetFlagFromFlagName);
                    break;
                case sFilterByFlagNotSetAny:
                    ProcessFiltersByFlags<false, RE::BGSMessage*, std::uint32_t>((*vFormsCasted), Iter.CurrentModifierValue, Message::IsFormFlagSet<std::uint32_t>,
                                                                                  RemoveIfFound<RE::BGSMessage*, std::vector<RE::BGSMessage*>::iterator>,
                                                                                  Message::GetFlagFromFlagName);
                    break;
                }
            }
        }

        void FilterCell(std::vector<RE::TESForm*>& vForms, std::vector<TempModifier>& Filters)
        {
            std::vector<RE::TESObjectCELL*>* vFormsCasted = (std::vector<RE::TESObjectCELL*>*)&vForms;

            for (auto it = Filters.begin(); it != Filters.end(); it++) {
                switch (Iter.CurrentModifierName) {
                case sFilterByFlagSet:
                    ProcessFiltersByFlags<true, RE::TESObjectCELL*, std::uint32_t>((*vFormsCasted), Iter.CurrentModifierValue, Cell::IsFormFlagSet<std::uint32_t>,
                                                                                   LeaveIfFound<RE::TESObjectCELL*, std::vector<RE::TESObjectCELL*>::iterator>,
                                                                                   Cell::GetFlagFromFlagName);
                    break;
                case sFilterByFlagNotSet:
                    ProcessFiltersByFlags<true, RE::TESObjectCELL*, std::uint32_t>((*vFormsCasted), Iter.CurrentModifierValue, Cell::IsFormFlagSet<std::uint32_t>,
                                                                                   RemoveIfFound<RE::TESObjectCELL*, std::vector<RE::TESObjectCELL*>::iterator>,
                                                                                   Cell::GetFlagFromFlagName);
                    break;
                case sFilterByFlagSetAny:
                    ProcessFiltersByFlags<false, RE::TESObjectCELL*, std::uint32_t>((*vFormsCasted), Iter.CurrentModifierValue, Cell::IsFormFlagSet<std::uint32_t>,
                                                                                    LeaveIfFound<RE::TESObjectCELL*, std::vector<RE::TESObjectCELL*>::iterator>,
                                                                                    Cell::GetFlagFromFlagName);
                    break;
                case sFilterByFlagNotSetAny:
                    ProcessFiltersByFlags<false, RE::TESObjectCELL*, std::uint32_t>((*vFormsCasted), Iter.CurrentModifierValue, Cell::IsFormFlagSet<std::uint32_t>,
                                                                                    RemoveIfFound<RE::TESObjectCELL*, std::vector<RE::TESObjectCELL*>::iterator>,
                                                                                    Cell::GetFlagFromFlagName);
                    break;
                }
            }
        }


        void FilterConstructible(std::vector<RE::TESForm*>& vForms, std::vector<TempModifier>& Filters)
        {
            std::vector<RE::BGSConstructibleObject*>* vFormsCasted = (std::vector<RE::BGSConstructibleObject*>*)&vForms;

            for (auto it = Filters.begin(); it != Filters.end(); it++) {
                switch (Iter.CurrentModifierName) {
                case sFiltersConstructibleHasWorkBenchKeyword:
                    ProcessFiltersByFormsAlt<true,RE::BGSConstructibleObject*, RE::BGSKeyword*>(
                        (*vFormsCasted), Iter.CurrentModifierValue, COBJHasKeyword, const_GetTypeFromFormType<RE::BGSKeyword*>(),
                                                                        LeaveIfFound<RE::BGSConstructibleObject*, std::vector<RE::BGSConstructibleObject*>::iterator>);
                    break;
                case sFiltersConstructibleHasNotWorkBenchKeyword:
                    ProcessFiltersByFormsAlt<false,RE::BGSConstructibleObject*, RE::BGSKeyword*>(
                        (*vFormsCasted), Iter.CurrentModifierValue, COBJHasKeyword, const_GetTypeFromFormType<RE::BGSKeyword*>(),
                                                                        RemoveIfFound<RE::BGSConstructibleObject*, std::vector<RE::BGSConstructibleObject*>::iterator>);
                    break;
                    
                }

            }
        }


        void FilterMagicEffect(std::vector<RE::TESForm*>& vForms, std::vector<TempModifier>& Filters)
        {
            std::vector<RE::EffectSetting*>* vFormsCasted = (std::vector<RE::EffectSetting*>*)&vForms;

            for (auto it = Filters.begin(); it != Filters.end(); it++) {
                switch (Iter.CurrentModifierName) {
                case sFilterByFlagSet:
                    ProcessFiltersByFlags<true, RE::EffectSetting*, std::uint32_t>((*vFormsCasted), Iter.CurrentModifierValue, MagicEffect::IsFormFlagSet<std::uint32_t>,
                                                                                   LeaveIfFound<RE::EffectSetting*, std::vector<RE::EffectSetting*>::iterator>,
                                                                                   MagicEffect::GetFlagFromFlagName);
                    break;
                case sFilterByFlagNotSet:
                    ProcessFiltersByFlags<true, RE::EffectSetting*, std::uint32_t>((*vFormsCasted), Iter.CurrentModifierValue, MagicEffect::IsFormFlagSet<std::uint32_t>,
                                                                                   RemoveIfFound<RE::EffectSetting*, std::vector<RE::EffectSetting*>::iterator>,
                                                                                   MagicEffect::GetFlagFromFlagName);
                    break;
                case sFilterByFlagSetAny:
                    ProcessFiltersByFlags<false, RE::EffectSetting*, std::uint32_t>((*vFormsCasted), Iter.CurrentModifierValue, MagicEffect::IsFormFlagSet<std::uint32_t>,
                                                                                    LeaveIfFound<RE::EffectSetting*, std::vector<RE::EffectSetting*>::iterator>,
                                                                                    MagicEffect::GetFlagFromFlagName);
                    break;
                case sFilterByFlagNotSetAny:
                    ProcessFiltersByFlags<false, RE::EffectSetting*, std::uint32_t>((*vFormsCasted), Iter.CurrentModifierValue, MagicEffect::IsFormFlagSet<std::uint32_t>,
                                                                                    RemoveIfFound<RE::EffectSetting*, std::vector<RE::EffectSetting*>::iterator>,
                                                                                    MagicEffect::GetFlagFromFlagName);
                    break;
                }
            }
        }



        void FilterIngestible(std::vector<RE::TESForm*>& vForms, std::vector<TempModifier>& Filters)
        {
            std::vector<RE::AlchemyItem*>* vFormsCasted = (std::vector<RE::AlchemyItem*>*)&vForms;

            for (auto it = Filters.begin(); it != Filters.end(); it++) {
                switch (Iter.CurrentModifierName) {
                case sFilterByFlagSet:
                    ProcessFiltersByFlags<true, RE::AlchemyItem*, std::uint8_t>((*vFormsCasted), Iter.CurrentModifierValue, Ingestibles::IsFormFlagSet<std::uint8_t>,
                                                                                 LeaveIfFound<RE::AlchemyItem*, std::vector<RE::AlchemyItem*>::iterator>,
                                                                                 Ingestibles::GetFlagFromFlagName);
                    break;
                case sFilterByFlagNotSet:
                    ProcessFiltersByFlags<true, RE::AlchemyItem*, std::uint8_t>((*vFormsCasted), Iter.CurrentModifierValue, Ingestibles::IsFormFlagSet<std::uint8_t>,
                                                                                 RemoveIfFound<RE::AlchemyItem*, std::vector<RE::AlchemyItem*>::iterator>,
                                                                                 Ingestibles::GetFlagFromFlagName);
                    break;
                case sFilterByFlagSetAny:
                    ProcessFiltersByFlags<false, RE::AlchemyItem*, std::uint8_t>((*vFormsCasted), Iter.CurrentModifierValue, Ingestibles::IsFormFlagSet<std::uint8_t>,
                                                                                  LeaveIfFound<RE::AlchemyItem*, std::vector<RE::AlchemyItem*>::iterator>,
                                                                                  Ingestibles::GetFlagFromFlagName);
                    break;
                case sFilterByFlagNotSetAny:
                    ProcessFiltersByFlags<false, RE::AlchemyItem*, std::uint8_t>((*vFormsCasted), Iter.CurrentModifierValue, Ingestibles::IsFormFlagSet<std::uint8_t>,
                                                                                  RemoveIfFound<RE::AlchemyItem*, std::vector<RE::AlchemyItem*>::iterator>,
                                                                                  Ingestibles::GetFlagFromFlagName);
                    break;
                }
            }
        }




        void FilterNPC(std::vector<RE::TESForm*>& vForms, std::vector<TempModifier>& Filters)
        {
            std::vector<RE::TESNPC*>* vFormsCasted = (std::vector<RE::TESNPC*>*)&vForms;

            for (auto it = Filters.begin(); it != Filters.end(); it++) {
                switch (Iter.CurrentModifierName) {
                case sFiltersNPCHasRace:
                    ProcessFiltersByFormsAlt<true,RE::TESNPC*, RE::TESRace*>((*vFormsCasted), Iter.CurrentModifierValue, NPCHasRace, const_GetTypeFromFormType<RE::TESRace*>(),LeaveIfFound<RE::TESNPC*, std::vector<RE::TESNPC*>::iterator>);
                    break;
                case sFiltersNPCHasNotRace:
                    ProcessFiltersByFormsAlt<false,RE::TESNPC*, RE::TESRace*>((*vFormsCasted), Iter.CurrentModifierValue, NPCHasRace, const_GetTypeFromFormType<RE::TESRace*>(),RemoveIfFound<RE::TESNPC*, std::vector<RE::TESNPC*>::iterator>);
                    break;

                case sFiltersNPCHasActorBaseFlagSet:
                    ProcessFiltersByFlags<true,RE::TESNPC*, std::uint32_t>((*vFormsCasted), Iter.CurrentModifierValue, NPC::IsActorBaseFlagSet<std::uint32_t>,
                                                                      LeaveIfFound<RE::TESNPC*, std::vector<RE::TESNPC*>::iterator>, NPC::GetFlagFromFlagName);
                    break;
                case sFiltersNPCHasNotActorBaseFlagSet:
                    ProcessFiltersByFlags<true,RE::TESNPC*, std::uint32_t>((*vFormsCasted), Iter.CurrentModifierValue, NPC::IsActorBaseFlagSet<std::uint32_t>,
                                                                      RemoveIfFound<RE::TESNPC*, std::vector<RE::TESNPC*>::iterator>, NPC::GetFlagFromFlagName);
                    break;
                case sFiltersNPCHasActorBaseFlagSetAny:
                    ProcessFiltersByFlags<false, RE::TESNPC*, std::uint32_t>((*vFormsCasted), Iter.CurrentModifierValue, NPC::IsActorBaseFlagSet<std::uint32_t>,
                                                                            LeaveIfFound<RE::TESNPC*, std::vector<RE::TESNPC*>::iterator>, NPC::GetFlagFromFlagName);
                    break;
                case sFiltersNPCHasNotActorBaseFlagSetAny:
                    ProcessFiltersByFlags<false, RE::TESNPC*, std::uint32_t>((*vFormsCasted), Iter.CurrentModifierValue, NPC::IsActorBaseFlagSet<std::uint32_t>,
                                                                             RemoveIfFound<RE::TESNPC*, std::vector<RE::TESNPC*>::iterator>, NPC::GetFlagFromFlagName);
                    break;
                }
            }
        }



        void FilterByExcludeFormID(std::vector<RE::TESForm*>& vForms, std::vector<uint32_t>& vFilters) // Any must be included,otherwise remove
        {
            for (auto it = vForms.begin(); it != vForms.end();) {

               bool bFound = false;

               for (auto it2 = vFilters.begin(); it2 != vFilters.end(); it2++) {
                    if (Iter->formID == Iter2) {
                        bFound = true;
                        break;
                    }
               }

               if (bFound) {
                    it = vForms.erase(it);
               }
               else {
                    it++;
               }
            }
        }





        void FilterArrayByFormIDs(std::vector<RE::TESForm*>& vForms, std::vector<TempModifier>& Filters)
        {

            for (auto it = Filters.begin(); it != Filters.end(); it++) {
               _DMESSAGE("NEW FORM FILTER NAME>>>{} VALUE>>{}", Iter.CurrentModifierName, Iter.CurrentModifierValue);

                switch (Iter.CurrentModifierName) {
                case sFiltersFormPluginInclude:
                    ProcessFiltersByPlugins(vForms, Iter.CurrentModifierValue, FilterByIncludePlugins);
                    break;
                case sFiltersFormPluginExclude:
                    ProcessFiltersByPlugins(vForms, Iter.CurrentModifierValue, FilterByExcludePlugins);
                    break;

                case sFiltersFormIDExclude:
                    ProcessFiltersByFormIDs<false,RE::TESForm*>(vForms, Iter.CurrentModifierValue, FilterByExcludeFormID);
                    break;

                case sFiltersFormlistInclude:
                    ProcessFiltersByForms<true,RE::TESForm*, RE::BGSListForm*>(vForms, Iter.CurrentModifierValue, FilterByIncludeInFormList,
                                                                          const_GetTypeFromFormType<RE::BGSListForm*>());
                    break;

                case sFiltersFormlistExclude:
                    ProcessFiltersByForms<false,RE::TESForm*, RE::BGSListForm*>(vForms, Iter.CurrentModifierValue, FilterByExcludeInFormList,
                                                                          const_GetTypeFromFormType<RE::BGSListForm*>());
                    break;

                }
            }
        }


        std::vector<TempModifier> GetAllFiltersFromLine(std::string_view Filters)
        {
            size_t CurrentPos     = 0;
            size_t NewModifierPos = 0;

            std::vector<TempModifier> result;

            while (NewModifierPos != NONPOS) {
                NewModifierPos                 = Filters.find(sFilterDelimeter, CurrentPos);
                std::string_view CurrentFilter = Filters.substr(CurrentPos, NewModifierPos - CurrentPos);

                auto BracketLeftPos = CurrentFilter.find(sValueDelimeterLeft);

                if (BracketLeftPos != NONPOS) {
                    std::string_view CurrentFilterName = CurrentFilter.substr(0, BracketLeftPos);

                    auto BracketRightPos = CurrentFilter.find_last_of(sValueDelimeterRight);

                    if (BracketRightPos != NONPOS) {
                        TempModifier NewModifier;
                        NewModifier.CurrentModifierName  = hash_djb2a(CurrentFilterName);
                        NewModifier.CurrentModifierValue = CurrentFilter.substr(BracketLeftPos + 1, BracketRightPos - BracketLeftPos - 1);
                        _DMESSAGE("New filter Name>>{}, Value>>{}", CurrentFilterName, NewModifier.CurrentModifierValue);
                        result.push_back(std::move(NewModifier));
                    }
                }
                CurrentPos = NewModifierPos + 1;
            }
            return result;
        }



    }

    
    namespace FormArray
    {
        // Starfield 1.16.244 stores the per-type form containers as
        // {uint32 count; uint32 capacity; TESForm** data; uint64 pad} (0x18 bytes each).
        // CommonLibSF still maps the 1.8.x {BSReadWriteLock, BSTArray} layout, so the
        // real base offset is resolved once at runtime instead of trusted from the SDK.
        struct Raw
        {
            std::uint32_t count;
            std::uint32_t capacity;
            RE::TESForm** data;
            std::uint64_t pad;
        };
        static_assert(sizeof(Raw) == 0x18);

        inline constexpr std::uintptr_t kBaseCandidates[] = { 0x80, 0x78, 0x70, 0x88, 0x60, 0x68, 0x90 };
        inline constexpr int            kProbeTypes[]     = { 4 /*KYWD*/, 0x22 /*ARMO*/, 0x30 /*WEAP*/, 0x11 /*RACE*/ };
        inline std::uintptr_t           g_base            = 0;

        bool IsReadable(const void* a_ptr, std::size_t a_bytes)
        {
            if (!a_ptr || !a_bytes) {
                return false;
            }
            MEMORY_BASIC_INFORMATION mbi{};
            auto                     cur = reinterpret_cast<std::uintptr_t>(a_ptr);
            const auto               end = cur + a_bytes;
            while (cur < end) {
                if (!VirtualQuery(reinterpret_cast<LPCVOID>(cur), &mbi, sizeof(mbi))) {
                    return false;
                }
                if (mbi.State != MEM_COMMIT || (mbi.Protect & PAGE_NOACCESS) || (mbi.Protect & PAGE_GUARD)) {
                    return false;
                }
                cur = reinterpret_cast<std::uintptr_t>(mbi.BaseAddress) + mbi.RegionSize;
            }
            return true;
        }

        const Raw* At(std::uintptr_t a_base, int a_type)
        {
            return reinterpret_cast<const Raw*>(a_base + static_cast<std::uintptr_t>(a_type) * sizeof(Raw));
        }

        bool HoldsType(const Raw* a_arr, int a_type)
        {
            if (!a_arr->count || a_arr->count > a_arr->capacity || a_arr->capacity > (1u << 21)) {
                return false;
            }
            if (!a_arr->data || !IsReadable(a_arr->data, sizeof(RE::TESForm*) * a_arr->count)) {
                return false;
            }
            const auto probe = std::min<std::uint32_t>(a_arr->count, 32u);
            int        matches = 0;
            int        checked = 0;
            for (std::uint32_t i = 0; i < probe; ++i) {
                auto* form = a_arr->data[i];
                if (!form) {
                    continue;
                }
                if (!IsReadable(form, 0x38)) {
                    return false;
                }
                ++checked;
                if (static_cast<int>(form->GetFormType()) == a_type) {
                    ++matches;
                }
            }
            return checked > 0 && matches * 4 >= checked * 3;
        }

        std::uintptr_t Resolve()
        {
            if (g_base) {
                return g_base;
            }
            auto* dh = RE::TESDataHandler::GetSingleton();
            if (!dh) {
                return 0;
            }
            const auto dhBase = reinterpret_cast<std::uintptr_t>(dh);
            for (auto base : kBaseCandidates) {
                int validated = 0;
                for (auto type : kProbeTypes) {
                    if (HoldsType(At(dhBase + base, type), type)) {
                        ++validated;
                    }
                }
                if (validated >= 2) {
                    g_base = dhBase + base;
                    _DMESSAGE("Resolved form array base>>DH+{:04X}", base);
                    return g_base;
                }
            }
            _DMESSAGE("Cannot resolve form array base");
            return 0;
        }
    }

    std::vector<RE::TESForm*> GetAllLoadedTypeFormsFromLineAndProcessFilters(int& iCurrentSection, std::string_view FormIDValue)
    {

        std::vector<RE::TESForm*> vForms{};

        if (iCurrentSection == Sections::k_Reference)
        {
            _DMESSAGE("Cannot search for all references - returning NULL array.");
            return vForms;
        }



        _DMESSAGE("Looking for all forms, category>>{}", iCurrentSection);

        const auto base = FormArray::Resolve();
        if (base) {
            const auto* arr = FormArray::At(base, iCurrentSection);
            _DMESSAGE("Form array>>{} count>>{} capacity>>{}", iCurrentSection, arr->count, arr->capacity);

            if (arr->count && FormArray::IsReadable(arr->data, sizeof(RE::TESForm*) * arr->count)) {
                // Refuse to touch the array unless its contents really are forms of this type.
                int sampled = 0;
                int matching = 0;
                for (std::uint32_t i = 0; i < arr->count && sampled < 8; ++i) {
                    auto* form = arr->data[i];
                    if (!form || !FormArray::IsReadable(form, 0x38)) {
                        continue;
                    }
                    ++sampled;
                    if (static_cast<int>(form->GetFormType()) == iCurrentSection) {
                        ++matching;
                    }
                }

                if (!sampled || matching != sampled) {
                    _DMESSAGE("Form array>>{} type mismatch ({} of {} sampled forms match) - skipped", iCurrentSection, matching, sampled);
                    return vForms;
                }

                vForms.reserve(arr->count);
                for (std::uint32_t i = 0; i < arr->count; ++i) {
                    if (auto* form = arr->data[i]) {
                        vForms.push_back(form);
                    }
                }
            }
            else {
                _DMESSAGE("Form array data unreadable (count>>{}, data>>{:016X})", arr->count, (uintptr_t)arr->data);
            }
        }

        _DMESSAGE("Found forms>>{}", vForms.size());

        if (!vForms.size()) {
            _DMESSAGE("No forms found.");
            return vForms;
        }

        auto AllFilters = Filters::GetAllFiltersFromLine(FormIDValue.substr(1, FormIDValue.length() - 1));

        if (AllFilters.size()) {
            Filters::FilterArrayByFormIDs(vForms, AllFilters);

            int SectionFlags = Section::GetFlags(iCurrentSection);

            if (IsFlagSet(SectionFlags, Section::Flags::k_SupportsKeywords)) {
                _DMESSAGE("Processing keywords filter");

                if (iCurrentSection == Input::Sections::k_Armors)
                {
                    Filters::FilterArrayByKeywords<RE::TESObjectARMO*>(vForms, AllFilters);
                }
                else if (iCurrentSection == Input::Sections::k_NPC)
                {
                    Filters::FilterArrayByKeywords<RE::TESNPC*>(vForms, AllFilters);
                }
                else if (iCurrentSection == Input::Sections::k_Ammo) {
                    Filters::FilterArrayByKeywords<RE::TESAmmo*>(vForms, AllFilters);
                }
                else if (iCurrentSection == Input::Sections::k_Misc) {
                    Filters::FilterArrayByKeywords<RE::TESObjectMISC*>(vForms, AllFilters);
                }
                else if (iCurrentSection == Input::Sections::k_Spell) {
                    Filters::FilterArrayByKeywords<RE::SpellItem*>(vForms, AllFilters);
                }
                else if (iCurrentSection == Input::Sections::k_Activator) {
                    Filters::FilterArrayByKeywords<RE::TESObjectACTI*>(vForms, AllFilters);
                }
                else if (iCurrentSection == Input::Sections::k_Book) {
                    Filters::FilterArrayByKeywords<RE::TESObjectBOOK*>(vForms, AllFilters);
                }
                else if (iCurrentSection == Input::Sections::k_Weapons) {
                    Filters::FilterArrayByKeywords<RE::TESObjectWEAP*>(vForms, AllFilters);
                }
                else if (iCurrentSection == Input::Sections::k_Ingestible) {
                    Filters::FilterArrayByKeywords<RE::AlchemyItem*>(vForms, AllFilters);
                }
                else if (iCurrentSection == Input::Sections::k_Container) {
                    Filters::FilterArrayByKeywords<RE::TESObjectCONT*>(vForms, AllFilters);
                }
                else if (iCurrentSection == Input::Sections::k_Race) {
                    Filters::FilterArrayByKeywords<RE::TESRace*>(vForms, AllFilters);
                }
                else if (iCurrentSection == Input::Sections::k_Terminal) {
                    Filters::FilterArrayByKeywords<RE::BGSTerminal*>(vForms, AllFilters);
                }
                else if (iCurrentSection == Input::Sections::k_MagicEffect) {
                    Filters::FilterArrayByKeywords<RE::EffectSetting*>(vForms, AllFilters);
                }
                else if (iCurrentSection == Input::Sections::k_Location) {
                    Filters::FilterArrayByKeywords<RE::BGSLocation*>(vForms, AllFilters);
                } 
                else {
                    _DRTFPError("--------------!!!!!!!!!!!!!!!!!Unsupported section for keyword filters {} - please report to TommInfinite", iCurrentSection);
                }
            }


            if (iCurrentSection == Input::Sections::k_Projectile)
            {
                Filters::FilterProjectiles(vForms, AllFilters);
            }
            else if (iCurrentSection == Input::Sections::k_Ammo) {
                Filters::FilterAmmo(vForms, AllFilters);
            }
            else if (iCurrentSection == Input::Sections::k_Weapons) {
                Filters::FilterWeapon(vForms, AllFilters);
            }
            else if (iCurrentSection == Input::Sections::k_NPC) {
                Filters::FilterNPC(vForms, AllFilters);
            }
           else if (iCurrentSection == Input::Sections::k_Message) {
                Filters::FilterMessage(vForms, AllFilters);
           }
           else if (iCurrentSection == Input::Sections::k_CELL) {
                Filters::FilterCell(vForms, AllFilters);
           }
           else if (iCurrentSection == Input::Sections::k_Ingestible) {
                Filters::FilterIngestible(vForms, AllFilters);
           }
           else if (iCurrentSection == Input::Sections::k_Constructible) {
                Filters::FilterConstructible(vForms, AllFilters);
           }
           else if (iCurrentSection == Input::Sections::k_MagicEffect) {
                Filters::FilterMagicEffect(vForms, AllFilters);
           }

            if (vForms.size())
            {
                if (IsFlagSet(SectionFlags, Section::Flags::k_SupportsWeight)) {

                    if (iCurrentSection == Sections::k_Misc) {
                        Filters::FilterFormsByValue<RE::TESObjectMISC*, sFilterByWeight>(vForms, AllFilters, Filters::GetWeightFromForm<RE::TESObjectMISC*>);
                    }
                    else if (iCurrentSection == Sections::k_Ammo) {
                        Filters::FilterFormsByValue<RE::TESAmmo*, sFilterByWeight>(vForms, AllFilters, Filters::GetWeightFromForm<RE::TESAmmo*>);
                    }
                    else if (iCurrentSection == Sections::k_Armors) {
                        Filters::FilterFormsByValue<RE::TESObjectARMO*, sFilterByWeight>(vForms, AllFilters, Filters::GetWeightFromForm<RE::TESObjectARMO*>);
                    }
                    else if (iCurrentSection == Sections::k_Weapons) {
                        Filters::FilterFormsByValue<RE::TESObjectWEAP*, sFilterByWeight>(vForms, AllFilters, Filters::GetWeightFromForm<RE::TESObjectWEAP*>);

                    }
                    else if (iCurrentSection == Sections::k_Ingestible) {
                        Filters::FilterFormsByValue<RE::AlchemyItem*, sFilterByWeight>(vForms, AllFilters, Filters::GetWeightFromForm<RE::AlchemyItem*>);
                    }
                    else if (iCurrentSection == Sections::k_Book) {
                        Filters::FilterFormsByValue<RE::TESObjectBOOK*, sFilterByWeight>(vForms, AllFilters, Filters::GetWeightFromForm<RE::TESObjectBOOK*>);
                    }
                }

               if (IsFlagSet(SectionFlags, Section::Flags::k_SupportsValue)) {
                    if (iCurrentSection == Sections::k_Misc) {
                        Filters::FilterFormsByValue<RE::TESObjectMISC*, sFilterByValue>(vForms, AllFilters, Filters::GetMemberValueFromForm<RE::TESObjectMISC*>);
                    }
                    else if (iCurrentSection == Sections::k_Ammo) {
                        Filters::FilterFormsByValue<RE::TESAmmo*, sFilterByValue>(vForms, AllFilters, Filters::GetMemberValueFromForm<RE::TESAmmo*>);
                    }
                    else if (iCurrentSection == Sections::k_Armors) {
                        Filters::FilterFormsByValue<RE::TESObjectARMO*, sFilterByValue>(vForms, AllFilters, Filters::GetMemberValueFromForm<RE::TESObjectARMO*>);
                    }
                    else if (iCurrentSection == Sections::k_Weapons) {
                        Filters::FilterFormsByValue<RE::TESObjectWEAP*, sFilterByValue>(vForms, AllFilters, Filters::GetMemberValueFromForm<RE::TESObjectWEAP*>);
                    }
                    else if (iCurrentSection == Sections::k_Book) {
                        Filters::FilterFormsByValue<RE::TESObjectBOOK*, sFilterByValue>(vForms, AllFilters, Filters::GetMemberValueFromForm<RE::TESObjectBOOK*>);
                    }
               }

            }

        }

        _DMESSAGE("Forms left after filters>>>{}", vForms.size());

        if (bDebugMode) {
            for (auto it = vForms.begin(); it != vForms.end(); it++) {
                _DMESSAGE("Forms>>>{:08X}", Iter->formID);
            }
        }

        return vForms;
    }
        




    void AddFormsFromLineSplittedByComma(std::vector<RE::TESForm*>& vForms, std::string_view FormIDValue, std::uint8_t iCategory)
    {
        size_t CurrentPos     = 0;
        size_t NewModifierPos = 0;

        while (NewModifierPos != NONPOS) {
            NewModifierPos = FormIDValue.find(sArrDelimeter, CurrentPos);

            auto CurrentForm = GetFormFromStringAndCheckForCategory<false>(FormIDValue.substr(CurrentPos, NewModifierPos - CurrentPos), iCategory);
            CurrentPos       = NewModifierPos + 1;

            if (!CurrentForm.bValid) {
                continue;
            }

            vForms.push_back(CurrentForm.data);
        }

    }


    std::vector<RE::TESForm*> GetMultipleFormsFromLine(int& iCurrentSection, std::string_view FormIDValue)
    {
        std::vector<RE::TESForm*> vForms;
        AddFormsFromLineSplittedByComma(vForms, FormIDValue.substr(1, FormIDValue.length() - 1), iCurrentSection);
        return vForms;
    }




    namespace Debug
    {

        // static bool GetSmartPointer(const std::uint32_t& a_handle, RE::NiPointer<RE::TESForm>& a_smartPointerOut)
        //{
        //    using func_t = decltype(&GetSmartPointer);
        //    REL::Relocation<func_t> func{ REL::ID(72986) };
        //    return func(a_handle, a_smartPointerOut);
        // }

        // static std::uint32_t CreateHandle(RE::NiPointer<RE::TESForm*> a_ptr)
        //{
        //    using func_t = decltype(&CreateHandle);
        //    REL::Relocation<func_t> func{ REL::ID(72547) };
        //    return func(a_ptr);
        // }

        void OutputForm(TommPlanetContentManagerBranchNode* formIn)
        {
            _DMESSAGE("PCBN,address>>{:08X}", (uintptr_t)formIn);

            for (auto& it : formIn->nodes) {
                _DMESSAGE("New node,type>>{},formID>>{:08X}", RE::FormTypeToString(it->GetFormType()),it->formID);
            }

        }


        void OutputReBGSModTemplateItems(RE::BGSMod::Template::Items& items, RE::TESObjectWEAP* formIn)
        {
            _DMESSAGE("For weap {:08X}, template count>>{}", formIn->formID, items.items.size());
            for (auto& combination : items.items) {
                if (!combination) {
                    continue;
                }
                _DMESSAGE("new item address>>{:08X}, name>>{}", (uintptr_t)combination, combination->GetFullName());
            }
        }



        void OutputForm(RE::TESObjectWEAP* formIn)
        {
            _DMESSAGE("WeapFound,address>>{:08X}", (uintptr_t)formIn);


            _DMESSAGE("Template count>>{}", formIn->templateItems.items.size());
            _DMESSAGE("Template name>>{}", formIn->templateItems.unk18.c_str());

            OutputReBGSModTemplateItems(formIn->templateItems, formIn);


            //for (auto& ObjTemplate : formIn->templateItems.items) {

            //    _DMESSAGE("new item address>>{:08X}, name>>{},incl count>>{}", (uintptr_t)ObjTemplate,ObjTemplate->name.c_str(),ObjTemplate->includes.size());
            //}





            auto WeaponData = formIn->weaponData.get();
            _DMESSAGE("WeaponData,address>>{:08X}", (uintptr_t)WeaponData);
            _DMESSAGE("WeaponData AMMO DATA adress>>{:08X}", (uintptr_t)WeaponData->WeaponAmmoData);

            _DMESSAGE("WeaponData AUDIO Data adress>>{:08X}", (uintptr_t)WeaponData->WeaponDataAudio); // SoundLevel
            _DMESSAGE("WeaponData DAMAGE DATA adress>>{:08X}", (uintptr_t)WeaponData->WeaponDamage);
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->weaponData.get()->WeaponDamage->attackDamage));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->weaponData.get()->WeaponDamage->rangeMin));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->weaponData.get()->WeaponDamage->rangeMax));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->weaponData.get()->WeaponDamage->critDamageMult));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->weaponData.get()->WeaponDamage->critChanceIncMult));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->weaponData.get()->WeaponDamage->outOfRangeDamageMult));

            CheckFormForForMemberFormAndPrintOut(MEMBER(formIn->weaponData.get()->WeaponAmmoData->ammo));
            CheckFormForForMemberFormAndPrintOut(MEMBER(RTFP::Extra(formIn->weaponData.get()->WeaponAmmoData)->ammoList));

            if (formIn->weaponData.get()->WeaponDamage->damageTypes)
            {
                _DMESSAGE("Damage types array exists");
                _DMESSAGE("Size>>{}", formIn->weaponData.get()->WeaponDamage->damageTypes->size());

                for (auto& tuple : *formIn->weaponData.get()->WeaponDamage->damageTypes)
                {
                    _DMESSAGE("Form>>{:08X},value>>{}", tuple.first->formID, tuple.third.i);
                }

            }
            else {
                _DMESSAGE("Damage types array doesn't exists");
            }



            _DMESSAGE("WeaponData DATA GENERAL adress>>{:08X}", (uintptr_t)WeaponData->WeapDataGeneral);

            int iCount = 0;
            for (auto keyword : RTFP::AttachKeywords(formIn->attachParents)) {
                _DMESSAGE("keyword formID>>{:08X}", keyword->formID);
                iCount++;
            }


            _DMESSAGE("WeaponData FIRING DATA adress>>{:08X}", (uintptr_t)WeaponData->WeaponFiringData);
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->weaponData.get()->WeaponFiringData->attackSeconds));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->weaponData.get()->WeaponFiringData->fireSeconds));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->weaponData.get()->WeaponFiringData->attackDelaySec));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->weaponData.get()->WeaponFiringData->boltChargeSec));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->weaponData.get()->WeaponFiringData->shotsPerSecond));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->weaponData.get()->WeaponFiringData->unknown));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->weaponData.get()->WeaponFiringData->triggerThresholdPrimary));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->weaponData.get()->WeaponFiringData->triggerThresholdSecondary));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->weaponData.get()->WeaponFiringData->burstDelaySeconds));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->weaponData.get()->WeaponFiringData->overrideRateOfFire));

            _DMESSAGE("WeaponData FLAG adress>>{:08X}", (uintptr_t)WeaponData->WeaponFlags);
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->weaponData.get()->WeaponFlags->NonPlayable));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->weaponData.get()->WeaponFlags->PlayerOnly));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->weaponData.get()->WeaponFlags->flag3));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->weaponData.get()->WeaponFlags->flag4));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->weaponData.get()->WeaponFlags->CantDrop));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->weaponData.get()->WeaponFlags->MinorCrime));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->weaponData.get()->WeaponFlags->NonHostile));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->weaponData.get()->WeaponFlags->flag8));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->weaponData.get()->WeaponFlags->flag9));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->weaponData.get()->WeaponFlags->flag10));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->weaponData.get()->WeaponFlags->flag11));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->weaponData.get()->WeaponFlags->flag12));

             _DMESSAGE("WeaponData AIM Data adress>>{:08X}", (uintptr_t)WeaponData->WeaponDataAim);
        }

        void OutputOMODValue(RE::BGSMod::Attachment::Mod::Data::Property& propIn)
        {
            _DMESSAGE("Type>>{},Address>>{:08X},PropertyID>>{}", propIn.type, (uintptr_t)&propIn, propIn.propertyID);
            if (propIn.type == 1)
            {
                _DMESSAGE("Value BOOL>>{}-BOOL>>{}", propIn.type1Val.value1, propIn.type1Val.value2);
            }
            else if (propIn.type == 2)
            {
                _DMESSAGE("Value Float>>{}-Float>>{}", propIn.type2Val.value1, propIn.type2Val.value2);
            }
            else if (propIn.type == 3) {
                _DMESSAGE("Value INT>>{}-INT>>{}", propIn.type3Val.value1, propIn.type3Val.value2);
            }
            else if (propIn.type == 4) {
                if (propIn.type4Val.value1)
                {
                    _DMESSAGE("Value Form type>>{} formID>>{:08X}, - Float>>{}", RE::FormTypeToString(propIn.type4Val.value1->GetFormType()), propIn.type4Val.value1->formID,
                              propIn.type4Val.value2);
                }
                else {
                    _DMESSAGE("Value Form is NULL, - Float>>{}",propIn.type4Val.value2);
                }
                
            }
            else {
                _DMESSAGE("OMOD PROPERTY TYPE NOT SUPPORTED!");
            }

            //std::uint32_t test = 'SPAV';
        }

        void OutputForm(RE::BGSMod::Attachment::Mod* formIn)
        {
          _DMESSAGE("OMOD exists, address>>{:08X}, incl count>>{},Props Count>>{},formID>>{:08X}", (uintptr_t)formIn, formIn->data.includes.size(),formIn->data.properties.size(),formIn->formID);

            for (auto it = formIn->data.includes.begin(); it != formIn->data.includes.end(); it++) {
                _DMESSAGE("New include Address>>{:08X}", (uintptr_t)&Iter);

                _DMESSAGE("Mod>>{:08X},level>>{},optional>{},DontUseAll>{}", Iter.mod->formID, Iter.level,
                          Iter.flags.any(RE::BGSMod::Attachment::Mod::Data::IncludesFlag::kOptional), Iter.flags.any(RE::BGSMod::Attachment::Mod::Data::IncludesFlag::kDontUseAll));
            }

            for (auto it = formIn->data.properties.begin(); it != formIn->data.properties.end(); it++) {

                OutputOMODValue(Iter);
            }

        }


        void OutputForm(RE::BGSMessage* formIn)
        {
            _DMESSAGE("Messageexists, address>>{:08X}, button count>>{}", (uintptr_t)formIn, formIn->menuButtons.size());

            for (auto it2 = formIn->menuButtons.begin(); it2 != formIn->menuButtons.end(); it2++) {
                if (Iter2->reference) {
                    _DMESSAGE("new button text>>{},ref>>{:08X}", Iter2->text.c_str(), Iter2->reference->formID);
                }
                else {
                    _DMESSAGE("new button text>>{},ref>>NULL", Iter2->text.c_str());
                }
            }
        }

        void OutputForm(RE::TESObjectCONT* formIn)
        {
            _DMESSAGE("Container exists, address>>{:08X}, item count>>{}", (uintptr_t)formIn, formIn->containerObjects.size());

            for (auto it2 = formIn->containerObjects.begin(); it2 != formIn->containerObjects.end(); it2++) {
                _DMESSAGE("new container object>>{:08X},count>>{},Item extra>>{:08X}", Iter2.obj->formID, Iter2.count, (long long int)Iter2.itemExtra);
            }
        }

        void OutputProperties(RE::BSTArray<PROPERTY>* Properties)
        {
            if (Properties) {
                _DMESSAGE("Properties size>>{}", Properties->size());
                for (auto it = Properties->begin(); it != Properties->end(); it++) {
                    if (Iter.first && Iter.second) {
                        _DMESSAGE("Property,form1>>{:08X},form2>>{:08X}, value>>{}", Iter.first->formID, Iter.second->formID, Iter.third.f);
                    }
                    else if (Iter.first && !Iter.second) {
                        _DMESSAGE("Property,form1>>{:08X},form2>>NULL, value>>{}", Iter.first->formID, Iter.third.f);
                    }
                    else if (!Iter.first && Iter.second) {
                        _DMESSAGE("Property,form1>>NULL,form2>>{:08X}, value>>{}", Iter.second->formID, Iter.third.f);
                    }
                    else if (!Iter.first && !Iter.second) {
                        _DMESSAGE("Property,form1>>NULL,form2>>NULL, value>>{}", Iter.third.f);
                    }
                }
            }
            else {
                _DMESSAGE("No properties for this form.");
            }
        }

        std::vector<RE::TESForm*> vFormsToOutput;




        void OutputForm(RE::BGSConditionForm* formIn)
        {
            _DMESSAGE("Condition form exists, address>>{:08X}, unk>>{:08X}", (uintptr_t)formIn, formIn->conditions.unk0);

            //CheckFormForForMemberFormAndPrintOut(MEMBER(formIn->quest));
            CheckFormForForMemberFormAndPrintOut(MEMBER(formIn->package));

            Condition::OutputTESConditionItem(RTFP::AsRTFP(formIn->conditions.head));
        }

        void OutputForm(RE::TESNPC* formIn)
        {
            _DMESSAGE("--------Outputting NPC");

            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->actorData.level));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->actorData.baseDisposition));
            CheckFormForForMemberFormAndPrintOut(MEMBER(formIn->legendChance));
            CheckFormForForMemberFormAndPrintOut(MEMBER(formIn->deathItem));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->height));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->heightMax));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->morphWeight.thin));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->morphWeight.muscular));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->morphWeight.fat));
            CheckFormForForMemberFormAndPrintOut(MEMBER(formIn->defaultOutfit));
            CheckFormForForMemberFormAndPrintOut(MEMBER(formIn->sleepOutfit));
            CheckFormForForMemberFormAndPrintOut(MEMBER(formIn->crimeFaction));

            _DMESSAGE("short name>>{}", formIn->shortName.c_str());
            _DMESSAGE("longname>>{}", formIn->fullName.c_str());

            _DMESSAGE("NPC keyword count>>{}", formIn->keywords.size());



            _DMESSAGE("perks count>>{}", formIn->perks.size());
            for (auto it = formIn->perks.begin(); it != formIn->perks.end(); it++) {
                _DMESSAGE("Perk>>{:08X}, rank>>{}", Iter.perk->formID, Iter.currentRank);
            }

            {
                auto headPartsGuard = formIn->headParts.Lock();
                const auto& headParts = *headPartsGuard;

                _DMESSAGE("headpart count>>{}", headParts.size());
                for (auto it = headParts.begin(); it != headParts.end(); it++) {
                    _DMESSAGE("New headpart>>{:08X}", Iter->formID);
                }
            }

            _DMESSAGE("factions count>>{}", formIn->factions.size());
            for (auto it = formIn->factions.begin(); it != formIn->factions.end(); it++) {
                _DMESSAGE("New faction>>{:08X},rank>>{}", Iter.faction->formID, Iter.rank);
            }

            _DMESSAGE("Keywords>>{}", formIn->keywords.size());
            for (auto it = formIn->keywords.begin(); it != formIn->keywords.end(); it++)
            {
                _DMESSAGE("new keyword>>{:08X}", Iter->formID);
            }

            _DMESSAGE("Keywords folders>>{}",formIn->formFolderKeywordLists.size());

            for (auto it = formIn->formFolderKeywordLists.begin(); it != formIn->formFolderKeywordLists.end(); it++) {
                
                _DMESSAGE("keyword folder count>>{:08X}", Iter->keywords.size());
            }

            


            OutputProperties(formIn->properties);

            _DMESSAGE("--------Outputting form list entries - END.");
        }

        void OutputForm(RE::BGSListForm* formIn)
        {
            _DMESSAGE("--------Outputting form list entries, size>>{}.", formIn->arrayOfForms.size());

            std::uint32_t count = 0;
            for (auto it = formIn->arrayOfForms.begin(); it != formIn->arrayOfForms.end(); it++) {
                if (Iter) {
                    _DMESSAGE("pos>>{},New form>>{:08X},type>>{}", count, Iter->formID, RE::FormTypeToString(Iter->GetFormType()));
                }
                else {
                    _DMESSAGE("pos>>{},New form>>NULL", count);
                }

                count++;
            }

            _DMESSAGE("--------Outputting form list entries - END.");
        }

        void OutputForm(RE::TESLeveledList* formIn)
        {
            _DMESSAGE("--------Outputting LVL list entries, size>>{}.", formIn->baseListCount);


            Condition::OutputTESConditionItem(RTFP::AsRTFP(formIn->conditions.head));



            for (auto i = 0; i < formIn->baseListCount; i++) {
                _DMESSAGE("Entry {}, Level>>>{},Form>>{:08X}, Address>>{:08X}, ChanceNone>>{},unk1D>>{},ItemExtra>>{:08X},TESCondition>>{:08X}", i, formIn->leveledLists[i].level,
                          formIn->leveledLists[i].form->formID, (uintptr_t)&formIn->leveledLists[i], formIn->leveledLists[i].chanceNone, formIn->leveledLists[i].unk1D,
                          (uintptr_t)formIn->leveledLists[i].itemExtra, (uintptr_t)formIn->leveledLists[i].conditions);


                if (formIn->leveledLists[i].conditions) {
                    _DMESSAGE("Outputting condition start");
                    Condition::OutputTESConditionItem(RTFP::AsRTFP(formIn->conditions.head));
                    _DMESSAGE("Outputting condition end");
                }
                else {
                    _DMESSAGE("No conditions for this lvl list entry");
                }



            }


            _DMESSAGE("--------Outputting END.");
        }

        void OutputForm(BGSAVMDataAlt* formIn)
        {
            _DMESSAGE("--------Outputting form AVMData entries,EditorID>>{} size>>{},pad>>{}.", formIn->formEditorID.c_str(), formIn->Entries.size(),formIn->pad);
            std::uint32_t count = 0;

            BGSAVMData* formInAlt = (BGSAVMData*)formIn;

            _DMESSAGE("Address>>{:08X},First entry>>{:08X},LastEntry>>{:08X},LastEntry2>>{:08X}", (uintptr_t)formIn, (uintptr_t)formInAlt->firstEntry,(uintptr_t)formInAlt->lastEntry,(uintptr_t)formInAlt->lastEntry2);

            for (auto entr = formIn->Entries.begin(); entr != formIn->Entries.end(); entr++) {
                //AVMData::OutputAVMEntry((*entr));
                _DMESSAGE("pos>>{},name>>{}, path>>{},intensity>>{}, color R>>{},G>>{},B>>{},alpha>>{}, address>>{:08X}", count, (*entr).name.c_str(), (*entr).texturePath.c_str(),
                          (*entr).intensity, (*entr).color.red, (*entr).color.green, (*entr).color.blue, (*entr).color.alpha, (uintptr_t)&(*entr));
                count++;
            }

            _DMESSAGE("--------Outputting END.");
        }

        void OutputForm(RE::TESObjectACTI* formIn)
        {
            _DMESSAGE("--------Outputting form Activator");

            OutputProperties(formIn->properties);
            _DMESSAGE("--------Outputting END.");
        }

        void OutputForm(RE::TESRace* formIn)
        {
            _DMESSAGE("--------Outputting form Race");


            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->data.height[RE::SEXES::kMale]));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->data.height[RE::SEXES::kFemale]));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->data.weight[RE::SEXES::kMale].thin));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->data.weight[RE::SEXES::kMale].muscular));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->data.weight[RE::SEXES::kMale].fat));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->data.weight[RE::SEXES::kFemale].thin));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->data.weight[RE::SEXES::kFemale].muscular));
            CheckFormForForMemberValueAndPrintOut(MEMBER(formIn->data.weight[RE::SEXES::kFemale].fat));

            _DMESSAGE("--------Outputting END.");
        }


        void ProcessForm(RE::TESForm* formIn)
        {
            _DMESSAGE("Form is valid, type>>{},formID>>{:08X},form address>>{:08X}", RE::FormTypeToString(formIn->GetFormType()), formIn->formID, (uintptr_t)formIn);

            std::uint8_t Type = formIn->formType.underlying();

            if (Type == Sections::k_FormList) {
                OutputForm((RE::BGSListForm*)formIn);
            }
            else if (Type == Sections::k_LeveledList_BaseForm || Type == Sections::k_LeveledList_NPC || Type == Sections::k_LeveledList_Item
                     || Type == Sections::k_LeveledList_PackIn)
            {
                OutputForm((RE::TESLevCharacter*)formIn);
            }
            else if (Type == Sections::k_AVMData) {
                OutputForm((BGSAVMDataAlt*)formIn);
            }
            else if (Type == Sections::k_NPC) {
                OutputForm((RE::TESNPC*)formIn);
            }
            else if (Type == Sections::k_ConditionForm) {
                OutputForm((RE::BGSConditionForm*)formIn);
            }
            else if (Type == Sections::k_Activator) {
                OutputForm((RE::TESObjectACTI*)formIn);
            }
            else if (Type == Sections::k_Container) {
                OutputForm((RE::TESObjectCONT*)formIn);
            }
            else if (Type == Sections::k_Message) {
                OutputForm((RE::BGSMessage*)formIn);
            }
            else if (Type == Sections::k_ObjectModification) {
                OutputForm((RE::BGSMod::Attachment::Mod*)formIn);
            }
            else if (Type == Sections::k_Weapons) {
                OutputForm((RE::TESObjectWEAP*)formIn);
            }
            else if (Type == Sections::k_Race) {
                OutputForm((RE::TESRace*)formIn);
            }
            else if (Type == const_GetTypeFromFormType < TommPlanetContentManagerBranchNode*>()) {
                OutputForm((TommPlanetContentManagerBranchNode*)formIn);
            }
            else {
                _DRTFPError("This type of form is not supported for Debug at the moment.")
            }
        }

        void ProcessFormFromLine(RE::TESForm* formIn)
        {
            vFormsToOutput.push_back(formIn);
            ProcessForm(formIn);
        }

        void ProcessFormsInArrayAfterChanges()
        {
            if (vFormsToOutput.size()) {
                _DMESSAGE("Outputting all forms after changes, count>>{}", vFormsToOutput.size());

                for (auto& it : vFormsToOutput) {
                    ProcessForm(it);
                }

                _DMESSAGE("Outputting all forms after changes - END.");
                vFormsToOutput.clear();
            }
            else {
                _DMESSAGE("No debug forms to output.");
            }
        }

    }





   namespace ProcessModifiers
   {


       
        template <class T>
        void ProcessModifier(unsigned long CurrentModifierName, T& CurrentModifierValue, RE::BGSLocation* CurrentForm)
        {
            switch (CurrentModifierName) {
                SwitchAddKeywordsCases SwitchAddFullnameSet
            default:
                _DRTFPError("Modifier is not valid for {}, formID>>{:08X}", RE::FormTypeToString(CurrentForm->GetFormType()), CurrentForm->formID);
            }
        }






        template <class T>
        void ProcessModifier(unsigned long CurrentModifierName, T& CurrentModifierValue, RE::EffectSetting* CurrentForm)
        {
            switch (CurrentModifierName) {
            SwitchAddKeywordsCases  SwitchAddFullnameSet

            case sValueFlagSet:
                ProcessFlagModifierAlt<true>((std::uint32_t&)CurrentForm->data.flags, CurrentModifierValue, MagicEffect::ProcessFlags<true>);
                break;
            case sValueFlagUnset:
                ProcessFlagModifierAlt<false>((std::uint32_t&)CurrentForm->data.flags, CurrentModifierValue, MagicEffect::ProcessFlags<false>);
                break;

            default:
                _DRTFPError("Modifier is not valid for {}, formID>>{:08X}", RE::FormTypeToString(CurrentForm->GetFormType()), CurrentForm->formID);
            }


        }




        template <class T>
        void ProcessModifier(unsigned long CurrentModifierName, T& CurrentModifierValue, RE::TESLoadScreen* CurrentForm)
        {
            switch (CurrentModifierName) {
            case sLoadScreenTexture:
                SetSFString(CurrentForm->loadscreen.textureName);
            case sLoadScreenDescription:
                SetSFString(CurrentForm->loadingText);
            default:
                _DRTFPError("Modifier is not valid for {}, formID>>{:08X}", RE::FormTypeToString(CurrentForm->GetFormType()), CurrentForm->formID);
            }
        }


        template <class T>
        void ProcessModifier(unsigned long CurrentModifierName, T& CurrentModifierValue, RE::BGSTerminal* CurrentForm)
        {
            switch (CurrentModifierName) {
                 SwitchAddKeywordsCases SwitchAddModelCase SwitchAddProperties SwitchAddFullnameSet

            case sTerminalValueTerminalMenu:
                _SetFormFromModifier(CurrentForm->menu);
                break;


            default:
                _DRTFPError("Modifier is not valid for {}, formID>>{:08X}", RE::FormTypeToString(CurrentForm->GetFormType()), CurrentForm->formID);
            }
        }

        template <class T>
        void ProcessModifier(unsigned long CurrentModifierName, T& CurrentModifierValue, RE::BGSMod::Attachment::Mod* CurrentForm)
        {
            switch (CurrentModifierName) {
             case sIncludeAdd:
                ArrayNonForm::_AddRemoveInsert(CurrentForm->data.includes, CurrentModifierValue,
                                               ArrayNonForm::Add<RE::BSTArray<RE::BGSMod::Attachment::Mod::Data::Include>, ObjectModification::EntryFromString::Data>,
                                               ObjectModification::GetFromString<false>);
                break;
             case sIncludeRemove:
                ArrayNonForm::_AddRemoveInsert(CurrentForm->data.includes, CurrentModifierValue,
                                               ArrayNonForm::Remove<RE::BSTArray<RE::BGSMod::Attachment::Mod::Data::Include>, ObjectModification::EntryFromString::Data>,
                                               ObjectModification::GetFromString<false>);
                break;
             case sIncludeReplace:
                ArrayNonForm::_ReplaceInArray(CurrentForm->data.includes, CurrentModifierValue,
                                              ArrayNonForm::Replace<RE::BSTArray<RE::BGSMod::Attachment::Mod::Data::Include>, ObjectModification::EntryFromString::Data>,
                                              ObjectModification::GetFromString<false>);
                break;
             case sIncludeClear:
                ArrayNonForm::_Clear(CurrentForm->data.includes);
                break;

            SwitchAddModelCase SwitchAddFullnameSet

            default:
                _DRTFPError("Modifier is not valid for {}, formID>>{:08X}", RE::FormTypeToString(CurrentForm->GetFormType()), CurrentForm->formID);
            }
        }



       
        template <class T>
        void ProcessModifier(unsigned long CurrentModifierName, T& CurrentModifierValue, RE::TESObjectREFR* CurrentForm)
        {
            switch (CurrentModifierName) {

            case sRefPosX:
                _ApplyMemberNumberMofidier(CurrentForm->data.location.x);
            case sRefPosY:
                _ApplyMemberNumberMofidier(CurrentForm->data.location.y);
            case sRefPosZ:
                _ApplyMemberNumberMofidier(CurrentForm->data.location.z);
            case sRefRotX:
                _ApplyMemberNumberMofidier(CurrentForm->data.angle.x);
            case sRefRotY:
                _ApplyMemberNumberMofidier(CurrentForm->data.angle.y);
            case sRefRotZ:
                _ApplyMemberNumberMofidier(CurrentForm->data.angle.z);
            case sRefScale:
                _ApplyMemberNumberMofidier(CurrentForm->scale);

                default:
                _DRTFPError("Modifier is not valid for {}, formID>>{:08X}", RE::FormTypeToString(CurrentForm->GetFormType()), CurrentForm->formID);
            }
        }


        template <class T>
        void ProcessModifier(unsigned long CurrentModifierName, T& CurrentModifierValue, RE::TESRace* CurrentForm)
        {
            switch (CurrentModifierName) {
            SwitchAddKeywordsCases SwitchAddProperties SwitchAddFullnameSet

             case sRaceMaleHeight:
                _ApplyMemberNumberMofidier(CurrentForm->data.height[RE::SEXES::kMale]);
            case sRaceFeMaleHeight:
                _ApplyMemberNumberMofidier(CurrentForm->data.height[RE::SEXES::kFemale]);
            case sRaceMaleWeightThin:
                _ApplyMemberNumberMofidier(CurrentForm->data.weight[RE::SEXES::kMale].thin);
            case sRaceMaleWeightMuscular:
                _ApplyMemberNumberMofidier(CurrentForm->data.weight[RE::SEXES::kMale].muscular);
            case sRaceMaleWeightFat:
                _ApplyMemberNumberMofidier(CurrentForm->data.weight[RE::SEXES::kMale].fat);
            case sRaceFeMaleWeightThin:
                _ApplyMemberNumberMofidier(CurrentForm->data.weight[RE::SEXES::kFemale].thin);
            case sRaceFeMaleWeightMuscular:
                _ApplyMemberNumberMofidier(CurrentForm->data.weight[RE::SEXES::kFemale].muscular);
            case sRaceFeMaleWeightFat:
                _ApplyMemberNumberMofidier(CurrentForm->data.weight[RE::SEXES::kFemale].fat);

            default: _DRTFPError("Modifier is not valid for {}, formID>>{:08X}", RE::FormTypeToString(CurrentForm->GetFormType()), CurrentForm->formID);
            }
        }


        template <class T>
        void ProcessModifier(unsigned long CurrentModifierName, T& CurrentModifierValue, TommPlanetContentManagerBranchNode* CurrentForm)
        {
            switch (CurrentModifierName) {

            case sPCBNNodeAdd:
            Array::AddRemoveInArray<TommPlanetContentManagerContentNode*>(CurrentForm->nodes, CurrentModifierValue, Array::AddToArray<TommPlanetContentManagerContentNode*>,const_GetTypeFromFormType<TommPlanetContentManagerContentNode*>(),const_GetTypeFromFormType<TommPlanetContentManagerBranchNode*>());
                break;
            case sPCBNNodeRemove:
                Array::AddRemoveInArray<TommPlanetContentManagerContentNode*>(
                    CurrentForm->nodes, CurrentModifierValue, Array::RemoveFromArray<TommPlanetContentManagerContentNode*>,
                    const_GetTypeFromFormType<TommPlanetContentManagerContentNode*>(), const_GetTypeFromFormType<TommPlanetContentManagerBranchNode*>());
                break;
            case sPCBNNodeReplace:
                Array::ReplaceFormInArray<TommPlanetContentManagerContentNode*>(CurrentForm->nodes, CurrentModifierValue,
                                                                                const_GetTypeFromFormType<TommPlanetContentManagerContentNode*>(),
                                                                                const_GetTypeFromFormType<TommPlanetContentManagerBranchNode*>());
                break;
            case sPCBNNodeClear:
                CurrentForm->nodes.clear();
                break;


            default:
                _DRTFPError("Modifier is not valid for {}, formID>>{:08X}", RE::FormTypeToString(CurrentForm->GetFormType()), CurrentForm->formID);
            }
        }




        template <class T>
        void ProcessModifier(unsigned long CurrentModifierName, T& CurrentModifierValue, RE::TESObjectCONT* CurrentForm)
        {
            switch (CurrentModifierName) {
            SwitchAddKeywordsCases
            SwitchAddModelCase
            SwitchAddProperties SwitchAddFullnameSet

            case sContainerItemAdd:
                ArrayNonForm::_AddRemoveInsert(CurrentForm->containerObjects, CurrentModifierValue,
                                               ArrayNonForm::Add<RE::BSTArray<RE::ContainerObject>, ContainerItem::EntryFromString::Data>,
                                               ContainerItem::GetFromString<false>);
                break;
            case sContainerItemRemove:
                ArrayNonForm::_AddRemoveInsert(CurrentForm->containerObjects, CurrentModifierValue,
                                               ArrayNonForm::Remove<RE::BSTArray<RE::ContainerObject>, ContainerItem::EntryFromString::Data>,
                                               ContainerItem::GetFromString<false>);
                break;
            case sContainerItemReplace:
                ArrayNonForm::_ReplaceInArray(CurrentForm->containerObjects, CurrentModifierValue,
                                              ArrayNonForm::Replace<RE::BSTArray<RE::ContainerObject>, ContainerItem::EntryFromString::Data>,
                                              ContainerItem::GetFromString<false>);
                break;
            case sContainerItemClear:
                ArrayNonForm::_Clear(CurrentForm->containerObjects);
                break;

            case sContainerValueDisplayFilter:
                _SetFormFromModifier(CurrentForm->containsOnlyList);
                break;

            default:
                _DRTFPError("Modifier is not valid for {}, formID>>{:08X}", RE::FormTypeToString(CurrentForm->GetFormType()), CurrentForm->formID);
            }
        }




        template <class T>
        void ProcessModifier(unsigned long CurrentModifierName, T& CurrentModifierValue, RE::BGSOutfit* CurrentForm)
        {
            switch (CurrentModifierName) {
            case sFormListAdd:
                FormListArray::AddRemoveFormListInArray(CurrentForm->outfitItems, CurrentModifierValue, FormListArray::AddFormListToArray);
                break;
            case sFormListRemove:
                FormListArray::AddRemoveFormListInArray(CurrentForm->outfitItems, CurrentModifierValue, FormListArray::RemoveFormListFromArray);
                break;
            case sFormListReplace:
                FormListArray::ReplaceFormListInArray(CurrentForm->outfitItems, CurrentModifierValue);
                break;
            case sFormListClear:
                CurrentForm->outfitItems.clear();
                break;

            default:
                _DRTFPError("Modifier is not valid for {}, formID>>{:08X}", RE::FormTypeToString(CurrentForm->GetFormType()), CurrentForm->formID);
            }
        }






        template <class T>
        void ProcessModifier(unsigned long CurrentModifierName, T& CurrentModifierValue, RE::AlchemyItem* CurrentForm)
        {
            switch (CurrentModifierName) {
            SwitchAddKeywordsCases
            SwitchAddWeightCase
            SwitchAddModelCase
            SwitchAddFullnameSet

            case sIngestibleAddictionItem:
                _SetFormFromModifier(CurrentForm->data.addictionItem);
                break;

            case sIngestibleAddictionChance:
                _ApplyMemberNumberMofidier(CurrentForm->data.addictionChance);
                break;

            case sValueSpellEffectAdd:
                ArrayNonForm::_AddRemoveInsert(CurrentForm->listOfEffects, CurrentModifierValue, EffectItem::AddToArray, EffectItem::GetFromString);
                break;
            case sValueSpellEffectRemove:
                ArrayNonForm::_AddRemoveInsert(CurrentForm->listOfEffects, CurrentModifierValue, EffectItem::RemoveFromArray, EffectItem::GetFromString);
                break;
            case sValueSpellEffectReplace:
                ArrayNonForm::_ReplaceInArray(CurrentForm->listOfEffects, CurrentModifierValue, EffectItem::ReplaceInArray, EffectItem::GetFromString);
                break;
            case sValueSpellEffectClear:
                EffectItem::ClearArray(CurrentForm->listOfEffects);
                break;


            case sValueFlagSet:
                //_DMESSAGE("SETTING FLAG");
                ProcessFlagModifierAlt<true>(CurrentForm->data.flags, CurrentModifierValue, Ingestibles::ProcessFlags<true>);
                break;
            case sValueFlagUnset:
                //_DMESSAGE("UNSETTING FLAG");
                ProcessFlagModifierAlt<false>(CurrentForm->data.flags, CurrentModifierValue, Ingestibles::ProcessFlags<false>);
                break;


            default:
                _DRTFPError("Modifier is not valid for {}, formID>>{:08X}", RE::FormTypeToString(CurrentForm->GetFormType()), CurrentForm->formID);
            }
        }







       template <class T>
        void ProcessModifier(unsigned long CurrentModifierName, T& CurrentModifierValue, RE::BGSMessage* CurrentForm)
        {
            switch (CurrentModifierName) {
            case sValueFlagSet:
                ProcessFlagModifierAlt<true>((std::uint32_t&)CurrentForm->flags, CurrentModifierValue, Message::ProcessFlags<true>);
                break;
            case sValueFlagUnset:
                ProcessFlagModifierAlt<false>((std::uint32_t&)CurrentForm->flags, CurrentModifierValue, Message::ProcessFlags<false>);
                break;
            case sMessageOwnerQuest:
                _SetFormFromModifier(CurrentForm->ownerQuest);
                break;
            case sMessageDisplayTime:
                _ApplyMemberNumberMofidier(CurrentForm->displayTime);
                break;
            case sMessageAddButton:
                ArrayNonForm::_AddRemoveInsert(CurrentForm->menuButtons, CurrentModifierValue, Message::AddToArray, Message::GetFromString);
                break;
            default:
                _DRTFPError("Modifier is not valid for {}, formID>>{:08X}", RE::FormTypeToString(CurrentForm->GetFormType()), CurrentForm->formID);
            }
        }






         template <class T>
        void ProcessModifier(unsigned long CurrentModifierName, T& CurrentModifierValue, BGSStoryManagerQuestNode* CurrentForm)
        {
            switch (CurrentModifierName) {
            case sStoryManagerQuestNodePreviousSibling:
                _SetFormFromModifier(CurrentForm->prevSibl);
            case sStoryManagerQuestNodeMaxConcurringQuests:
                _ApplyMemberNumberMofidier(CurrentForm->maxConcurringQuests);
            case sStoryManagerQuestNodeHoursUntillReset:
                _ApplyMemberNumberMofidier(CurrentForm->hoursUntillreset);
            case sStoryManagerQuestNodeNumQuestsToRun:
                _ApplyMemberNumberMofidier(CurrentForm->numQuestsToRun);
            case sStoryManagerQuestNodeEntryAdd:
                ArrayNonForm::_AddRemoveInsert(CurrentForm->Quests, CurrentModifierValue,
                                               ArrayNonForm::Add<RE::BSTArray<BGSStoryManagerQuestNode::QuestEntry>, StoryManagerQuestNode::EntryFromString::Data>,
                                               StoryManagerQuestNode::GetFromString<false>);
                break;
            case sStoryManagerQuestNodeEntryRemove:
                ArrayNonForm::_AddRemoveInsert(CurrentForm->Quests, CurrentModifierValue,
                                               ArrayNonForm::Remove<RE::BSTArray<BGSStoryManagerQuestNode::QuestEntry>, StoryManagerQuestNode::EntryFromString::Data>,
                                               StoryManagerQuestNode::GetFromString<false>);
                break;
            case sStoryManagerQuestNodeEntryReplace:
                ArrayNonForm::_ReplaceInArray(CurrentForm->Quests, CurrentModifierValue,
                                              ArrayNonForm::Replace<RE::BSTArray<BGSStoryManagerQuestNode::QuestEntry>, StoryManagerQuestNode::EntryFromString::Data>,
                                              StoryManagerQuestNode::GetFromString<false>);
                break;
            case sStoryManagerQuestNodeEntryInsert:
                ArrayNonForm::_AddRemoveInsert(CurrentForm->Quests, CurrentModifierValue,
                                               ArrayNonForm::Insert<RE::BSTArray<BGSStoryManagerQuestNode::QuestEntry>, StoryManagerQuestNode::EntryFromString::Data>,
                                              StoryManagerQuestNode::GetFromString<true>);
                break;
            case sStoryManagerQuestNodeEntryClear:
                ArrayNonForm::_Clear(CurrentForm->Quests);
                break;
            default:
                _DRTFPError("Modifier is not valid for {}, formID>>{:08X}", RE::FormTypeToString(CurrentForm->GetFormType()), CurrentForm->formID);
            }
        }



        template <class T>
        void ProcessModifier(unsigned long CurrentModifierName, T& CurrentModifierValue, RE::BGSVoiceType* CurrentForm)
        {
            switch (CurrentModifierName) {
            case sVoiceTypeAnimFaceArchetype:
                _SetFormFromModifier(CurrentForm->animationFaceArchetype);
            default:
                _DRTFPError("Modifier is not valid for {}, formID>>{:08X}", RE::FormTypeToString(CurrentForm->GetFormType()), CurrentForm->formID);
            }
        }

        template <class T>
        void ProcessModifier(unsigned long CurrentModifierName, T& CurrentModifierValue, RE::BGSConditionForm* CurrentForm)
        {
            switch (CurrentModifierName) {
            case sConditionFormAddEntryFrom:
                ArrayNonForm::_AddRemoveInsert(CurrentForm, CurrentModifierValue, ConditionForm::AddEntryFromCondForm, ConditionForm::GetFromString);
                break;

            case sCondidtionAddToForm:
                Condition::AddRemove(CurrentForm->conditions, CurrentModifierValue, Condition::AddConditionToConditionArray);
                break;

            default:
                _DRTFPError("Modifier is not valid for {}, formID>>{:08X}", RE::FormTypeToString(CurrentForm->GetFormType()), CurrentForm->formID);
            }
        }

        template <class T>
        void ProcessModifier(unsigned long CurrentModifierName, T& CurrentModifierValue, RE::TESGlobal* CurrentForm)
        {
            switch (CurrentModifierName) {
            case sValueValue:
                //_MESSAGE("Applying to GLOBAL FORM>>{}", CurrentForm->formID);
                _ApplyMemberNumberMofidier(CurrentForm->value);

            default:
                _DRTFPError("Modifier is not valid for {}, formID>>{:08X}", RE::FormTypeToString(CurrentForm->GetFormType()), CurrentForm->formID);
            }
        }


        template<class T>
        void ProcessModifier(unsigned long CurrentModifierName, T& CurrentModifierValue, RE::SpellItem* CurrentForm)
        {
            switch (CurrentModifierName) {
            SwitchAddKeywordsCases
            case sValueSpellCastingPerk:
                _SetFormFromModifier(CurrentForm->data.castingPerk);
            case sValueSpellType:
                _ApplyMemberNumberMofidier((std::uint8_t&)CurrentForm->data.spellType);
                break;
            case sValueSpellChargeTime:
                _ApplyMemberNumberMofidier(CurrentForm->data.chargeTime);
                break;
            case sValueSpellCastingType:
                _ApplyMemberNumberMofidier((std::uint8_t&)CurrentForm->data.castingType);
                break;
            case sValueSpellTargetType:
                _ApplyMemberNumberMofidier((std::uint8_t&)CurrentForm->data.delivery);
                break;
            case sValueSpellCastDuration:
                _ApplyMemberNumberMofidier(CurrentForm->data.castDuration);
                break;
            case sValueSpellRange:
                _ApplyMemberNumberMofidier(CurrentForm->data.range);
                break;
            case sValueSpellEffectAdd:
                ArrayNonForm::_AddRemoveInsert(CurrentForm->listOfEffects, CurrentModifierValue, EffectItem::AddToArray, EffectItem::GetFromString);
                break;
            case sValueSpellEffectRemove:
                ArrayNonForm::_AddRemoveInsert(CurrentForm->listOfEffects, CurrentModifierValue, EffectItem::RemoveFromArray, EffectItem::GetFromString);
                break;
            case sValueSpellEffectReplace:
                ArrayNonForm::_ReplaceInArray(CurrentForm->listOfEffects, CurrentModifierValue, EffectItem::ReplaceInArray, EffectItem::GetFromString);
                break;
            case sValueSpellEffectClear:
                EffectItem::ClearArray(CurrentForm->listOfEffects);
                break;
                
            default:
                _DRTFPError("Modifier is not valid for {}, formID>>{:08X}", RE::FormTypeToString(CurrentForm->GetFormType()), CurrentForm->formID);
            }
        }


        template <class T>
        void ProcessModifier(unsigned long CurrentModifierName, T& CurrentModifierValue, RE::TESObjectCELL* CurrentForm)
        {
            switch (CurrentModifierName) {
            case sValueFlagSet:
                ProcessFlagModifierAlt<true>((std::uint32_t&)CurrentForm->cellFlags, CurrentModifierValue, Cell::ProcessFlags<true>);
                break;
            case sValueFlagUnset:
                ProcessFlagModifierAlt<false>((std::uint32_t&)CurrentForm->cellFlags, CurrentModifierValue, Cell::ProcessFlags<false>);
                break;
            default:
                _DRTFPError("Modifier is not valid for {}, formID>>{:08X}", RE::FormTypeToString(CurrentForm->GetFormType()), CurrentForm->formID);
            }
        }


        template <class T>
        void ProcessModifier(unsigned long CurrentModifierName, T& CurrentModifierValue, RE::TESAmmo* CurrentForm)
        {
            switch (CurrentModifierName) {
            SwitchAddKeywordsCases SwitchAddValueCase SwitchAddWeightCase SwitchAddModelCase SwitchAddFullnameSet
            case sValueAmmoProjectile:
                _SetFormFromModifier(CurrentForm->data.projectile);
            default: _DRTFPError("Modifier is not valid for {}, formID>>{:08X}", RE::FormTypeToString(CurrentForm->GetFormType()), CurrentForm->formID);
            }
        }

        template <class T>
        void ProcessModifier(unsigned long CurrentModifierName, T& CurrentModifierValue, RE::TESObjectWEAP* CurrentForm)
        {
            switch (CurrentModifierName) {
            SwitchAddKeywordsCases SwitchAddModelCase SwitchAddFullnameSet
            case sValueWeapAmmo:
                _SetFormFromModifier(CurrentForm->weaponData.get()->WeaponAmmoData->ammo);
            case sValueWeapAmmoList:
                _SetFormFromModifierDontCheckForCategory(RTFP::Extra(CurrentForm->weaponData.get()->WeaponAmmoData)->ammoList);
            case sValueWeaponDamage:
                _ApplyMemberNumberMofidier(CurrentForm->weaponData.get()->WeaponDamage->attackDamage);
                break;
            case sValueWeaponCapacity:
                _ApplyMemberNumberMofidier(CurrentForm->weaponData.get()->WeaponAmmoData->ammoCapacity);
                break;
            case sValueWeaponCritDamageMult:
                _ApplyMemberNumberMofidier(CurrentForm->weaponData.get()->WeaponDamage->critDamageMult);
                break;
            case sValueWeaponCritChanceIncMult:
                _ApplyMemberNumberMofidier(CurrentForm->weaponData.get()->WeaponDamage->critChanceIncMult);
                break;
            case sValueWeaponFiringAttackSeconds:
                _ApplyMemberNumberMofidier(CurrentForm->weaponData.get()->WeaponFiringData->attackSeconds);
                break;
            case sValueWeaponFiringAttackDelaySeconds:
                _ApplyMemberNumberMofidier(CurrentForm->weaponData.get()->WeaponFiringData->attackDelaySec);
                break;
            case sValueWeaponAttackOxygenCost:
                _ApplyMemberNumberMofidier(CurrentForm->weaponData.get()->WeapDataGeneral->attackOxygenCost);
                break;
            case sValueWeaponAttackBaseWeight:
                _ApplyMemberNumberMofidier(CurrentForm->weaponData.get()->WeapDataGeneral->baseWeight);
                break;
            case sValueWeaponAttackBaseValue:
                _ApplyMemberNumberMofidier(CurrentForm->weaponData.get()->WeapDataGeneral->baseValue);
                break;
            case sValueWeaponAttackBaseSpeed:
                _ApplyMemberNumberMofidier(CurrentForm->weaponData.get()->WeapDataGeneral->baseSpeed);
                break;
            case sValueWeaponAttackReloadSpeed:
                _ApplyMemberNumberMofidier(CurrentForm->weaponData.get()->WeapDataReload->Reloadspeed);
                break;
            case sValueWeaponAttackBashDamage:
                _ApplyMemberNumberMofidier(CurrentForm->weaponData.get()->WeapDataMelee->bashDamage);
                break;

            case sValueWeaponFiringShotsPerSecond:
                _ApplyMemberNumberMofidier(CurrentForm->weaponData.get()->WeaponFiringData->shotsPerSecond);
                break;
            case sValueWeaponFiringOverrideRateOfFire:
                _ApplyMemberNumberMofidier(CurrentForm->weaponData.get()->WeaponFiringData->overrideRateOfFire);
                break;
            case sValueFlagSet:
                Weapons::ProcessFlagModifier(true, CurrentForm, CurrentModifierValue);
                break;
            case sValueFlagUnset:
                Weapons::ProcessFlagModifier(false, CurrentForm, CurrentModifierValue);
                break;
            case sValueWeaponDamageRangeMin:
                _ApplyMemberNumberMofidier(CurrentForm->weaponData.get()->WeaponDamage->rangeMin);
                break;
            case sValueWeaponDamageRangeMax:
                _ApplyMemberNumberMofidier(CurrentForm->weaponData.get()->WeaponDamage->rangeMax);
                break;
            case sValueWeaponDamageOutOfRangeDamageMult:
                _ApplyMemberNumberMofidier(CurrentForm->weaponData.get()->WeaponDamage->outOfRangeDamageMult);
                break;

             case sAttachParentsArrayAdd:
                AttachParentsArray::AddRemoveForm(CurrentForm, CurrentModifierValue, AttachParentsArray::v_WeaponBGSEntries,
                                                  AttachParentsArray::AddToArray<AttachParentsArray::StoredData<RE::TESObjectWEAP*>>);
                break;
             case sAttachParentsArrayRemove:
                AttachParentsArray::AddRemoveForm(CurrentForm, CurrentModifierValue, AttachParentsArray::v_WeaponBGSEntries,
                                                  AttachParentsArray::RemoveFromArray<AttachParentsArray::StoredData<RE::TESObjectWEAP*>>);
                break;
             case sAttachParentsArrayReplace:
                AttachParentsArray::ProcessReplacing(CurrentForm, CurrentModifierValue, AttachParentsArray::v_WeaponBGSEntries);
                break;

             case sAttachParentsArrayClear:
                AttachParentsArray::ClearArray(CurrentForm, AttachParentsArray::v_WeaponBGSEntries);
                break;

             case sValueWeaponDamageTypeAdd:
                ArrayNonForm::_AddRemoveInsert(CurrentForm->weaponData.get()->WeaponDamage->damageTypes, CurrentModifierValue, ArrayNonForm::Add<RE::BSTArray<TUPLE3>*, TUPLE::TupleData::Data>,
                                               TUPLE::GetFromString<false>);
                break;
             case sValueWeaponDamageTypeRemove:
                if (CurrentForm->weaponData.get()->WeaponDamage->damageTypes) {
                    ArrayNonForm::_AddRemoveInsert(CurrentForm->weaponData.get()->WeaponDamage->damageTypes, CurrentModifierValue,
                                                   ArrayNonForm::Remove<RE::BSTArray<TUPLE3>*, TUPLE::TupleData::Data>,
                                                   TUPLE::GetFromString<false>);
                }
                else {
                    _DMESSAGE("DamageType array in {:08X} doesn't exist for item to be removed.", CurrentForm->formID);
                }

                break;
             case sValueWeaponDamageTypeReplace:
                if (CurrentForm->weaponData.get()->WeaponDamage->damageTypes) {
                    ArrayNonForm::_ReplaceInArray(CurrentForm->weaponData.get()->WeaponDamage->damageTypes, CurrentModifierValue,
                                                  ArrayNonForm::Replace<RE::BSTArray<TUPLE3>*, TUPLE::TupleData::Data>,
                                                  TUPLE::GetFromString<false>);
                }
                {
                    _DMESSAGE("Damage type array in {:08X} doesn't exist for item to be replaced", CurrentForm->formID);
                }

                break;
             case sValueWeaponDamageTypeClear:
                if (CurrentForm->weaponData.get()->WeaponDamage->damageTypes) {
                    ArrayNonForm::_Clear(CurrentForm->weaponData.get()->WeaponDamage->damageTypes);
                }
                else {
                    _DMESSAGE("Damage type array in {:08X} doesn't exist to be cleared.", CurrentForm->formID);
                }

                break;

            default:
                _DRTFPError("Modifier is not valid for {}, formID>>{:08X}", RE::FormTypeToString(CurrentForm->GetFormType()), CurrentForm->formID);
            }
        }

        template <class T>
        void ProcessModifier(unsigned long CurrentModifierName, T& CurrentModifierValue, RE::BGSProjectile* CurrentForm)
        {
            switch (CurrentModifierName) {
            SwitchAddModelCase 
            case sValueProjGravity:
            _ApplyMemberNumberMofidier(CurrentForm->data.gravity)
            case sValueProjSpeed:
            _ApplyMemberNumberMofidier(CurrentForm->data.speed)
            case sValueProjRange:
            _ApplyMemberNumberMofidier(CurrentForm->data.range)
            case sValueProjExplosionProximity:
            _ApplyMemberNumberMofidier(CurrentForm->data.explosionProximity)
            case sValueProjExplosionTimer:
            _ApplyMemberNumberMofidier(CurrentForm->data.explosionTimer)
            case sValueProjMuzzleFlashDuration:
            _ApplyMemberNumberMofidier(CurrentForm->data.muzzleFlashDuration)
            case sValueProjFadeDuration:
            _ApplyMemberNumberMofidier(CurrentForm->data.fadeOutTime)
            case sValueProjImpactForce:
            _ApplyMemberNumberMofidier(CurrentForm->data.force)
            case sValueProjConeSpread:
            _ApplyMemberNumberMofidier(CurrentForm->data.coneSpread)
            case sValueProjCollisionRadius:
            _ApplyMemberNumberMofidier(CurrentForm->data.collisionRadius)
            case sValueProjLifetime:
            _ApplyMemberNumberMofidier(CurrentForm->data.lifetime)
            case sValueProjRelaunchInterval:
                _ApplyMemberNumberMofidier(CurrentForm->data.relaunchInterval)

             default:
                _DRTFPError("Modifier is not valid for {}, formID>>{:08X}", RE::FormTypeToString(CurrentForm->GetFormType()), CurrentForm->formID);
            }
        }


        template<class T>
        void ProcessModifier(unsigned long CurrentModifierName, T& CurrentModifierValue, RE::TESObjectSTAT* CurrentForm)
        {
            switch (CurrentModifierName) {
                SwitchAddModelCase

            default :
                _DRTFPError("Modifier is not valid for {}, formID>>{:08X}", RE::FormTypeToString(CurrentForm->GetFormType()), CurrentForm->formID);
            }
        }

        void ProcessModifier(unsigned long CurrentModifierName, std::string_view CurrentModifierValue, RE::BGSPerk* CurrentForm)
        {
            switch (CurrentModifierName) {
            SwitchAddFullnameSet
            case sValuePerkTrainingPerk:
                _SetFormFromModifier(CurrentForm->trainingPerk);
            case sValuePerkIcon:
                SetSFString(CurrentForm->perkIcon);
            case sValuePerkRestriction:
                _SetFormFromModifier(CurrentForm->restriction);
            default:
                _DRTFPError("Modifier is not valid for {}, formID>>{:08X}", RE::FormTypeToString(CurrentForm->GetFormType()), CurrentForm->formID);
            }
        }

        void ProcessModifier(unsigned long CurrentModifierName, std::string_view CurrentModifierValue, RE::TESObjectARMO* CurrentForm)
        {
            switch (CurrentModifierName) {
            SwitchAddKeywordsCases SwitchAddFullnameSet


            case sValueValue:
                _ApplyMemberNumberMofidier(CurrentForm->instanceData.value().value);
            case sValueWeight:
            {
                // Guard against writing into a record whose instance data is not where
                // CommonLibSF expects it (layout moved between game versions).
                static bool warned = false;
                auto&       inst   = CurrentForm->instanceData;
                if (!inst.has_value()) {
                    if (!warned) {
                        warned = true;
                        _DRTFPError("ARMO {:08X} has no instance data - weight write skipped", CurrentForm->formID);
                    }
                    break;
                }
                float& w = inst.value().weight;
                if (!(w >= 0.0f && w < 5000.0f)) {
                    if (!warned) {
                        warned = true;
                        _DRTFPError("ARMO {:08X} weight is not a sane value - write skipped", CurrentForm->formID);
                    }
                    break;
                }
                ApplyMemberNumberMofidier(CurrentModifierValue, w);
                break;
            }
            case sAttachParentsArrayAdd:
                AttachParentsArray::AddRemoveForm(CurrentForm, CurrentModifierValue, AttachParentsArray::v_ArmorBGSEntries,
                                                  AttachParentsArray::AddToArray<AttachParentsArray::StoredData<RE::TESObjectARMO*>>);
                break;
            case sAttachParentsArrayRemove:
                AttachParentsArray::AddRemoveForm(CurrentForm, CurrentModifierValue, AttachParentsArray::v_ArmorBGSEntries,
                                                  AttachParentsArray::RemoveFromArray<AttachParentsArray::StoredData<RE::TESObjectARMO*>>);
                break;
            case sAttachParentsArrayReplace:
                AttachParentsArray::ProcessReplacing(CurrentForm, CurrentModifierValue, AttachParentsArray::v_ArmorBGSEntries);
                break;

            case sAttachParentsArrayClear:
                AttachParentsArray::ClearArray(CurrentForm, AttachParentsArray::v_ArmorBGSEntries);
                break; 

             default:
                _DRTFPError("Modifier is not valid for {}, formID>>{:08X}", RE::FormTypeToString(CurrentForm->GetFormType()), CurrentForm->formID);
            }
        }


        template <class T>
        void ProcessModifier(unsigned long CurrentModifierName, T& CurrentModifierValue, RE::TESObjectBOOK* CurrentForm)
        {
            switch (CurrentModifierName) {
                SwitchAddKeywordsCases SwitchAddFullnameSet
                    SwitchAddValueCase
                    SwitchAddWeightCase
                    SwitchAddModelCase
                    default:
                        _DRTFPError("Modifier is not valid for {}, formID>>{:08X}", RE::FormTypeToString(CurrentForm->GetFormType()), CurrentForm->formID);
            }
        }




        template <class T>
        void ProcessModifier(unsigned long CurrentModifierName, T& CurrentModifierValue, RE::TESObjectMISC* CurrentForm)
        {
            switch (CurrentModifierName) {
                SwitchAddKeywordsCases
                SwitchAddValueCase
                SwitchAddWeightCase
                SwitchAddModelCase
                SwitchAddFullnameSet

                 default:
                 _DRTFPError("Modifier is not valid for {}, formID>>{:08X}", RE::FormTypeToString(CurrentForm->GetFormType()), CurrentForm->formID);
            }
        }

        void ProcessModifier(unsigned long CurrentModifierName, std::string_view CurrentModifierValue, RE::BGSListForm* CurrentForm)
        {
            switch (CurrentModifierName) {
            case sFormListAdd:
                FormListArray::AddRemoveFormListInArray(CurrentForm->arrayOfForms, CurrentModifierValue, FormListArray::AddFormListToArray);
                break;
            case sFormListRemove:
                FormListArray::AddRemoveFormListInArray(CurrentForm->arrayOfForms, CurrentModifierValue, FormListArray::RemoveFormListFromArray);
                break;
            case sFormListReplace:
                FormListArray::ReplaceFormListInArray(CurrentForm->arrayOfForms, CurrentModifierValue);
                break;
            case sFormListClear:
                CurrentForm->arrayOfForms.clear();
                break;

            default:
                _DRTFPError("Modifier is not valid for {}, formID>>{:08X}", RE::FormTypeToString(CurrentForm->GetFormType()), CurrentForm->formID);
            }
        }

        void ProcessModifier(unsigned long CurrentModifierName, std::string_view CurrentModifierValue, RE::TESNPC* CurrentForm)
        {
            switch (CurrentModifierName) {
            SwitchAddKeywordsCases SwitchAddFullnameSet
             case sValueNPCDeathItem:
                _SetFormFromModifier(CurrentForm->deathItem);
                break;
            case sValueNPCLegendChance:
                _SetFormFromModifier(CurrentForm->legendChance);
                break;
            case sValueNPCDefaultOutfit:
                _SetFormFromModifier(CurrentForm->defaultOutfit);
                break;
            case sValueNPCSleepOutfit:
                _SetFormFromModifier(CurrentForm->sleepOutfit);
                break;
            case sValueNPCCrimeFaction:
                _SetFormFromModifier(CurrentForm->crimeFaction);
                break;
            case sValueNPCXPValueOffset:
                _ApplyMemberNumberMofidier(CurrentForm->actorData.xpValueOffset);
                break;
            case sValueNPCXPLevel:
                _ApplyMemberNumberMofidier(CurrentForm->actorData.level);
                break;
            case sValueNPCCalcMinLevel:
                _ApplyMemberNumberMofidier(CurrentForm->actorData.calcLevelMin);
                break;
            case sValueNPCCalcMaxLevel:
                _ApplyMemberNumberMofidier(CurrentForm->actorData.calcLevelMax);
                break;
            case sValueNPCDispositionBase:
                _ApplyMemberNumberMofidier(CurrentForm->actorData.baseDisposition);
                break;
            case sValueNPCHeightMin:
                _ApplyMemberNumberMofidier(CurrentForm->height);
                break;
            case sValueNPCHeightMax:
                _ApplyMemberNumberMofidier(CurrentForm->heightMax);
                break;
            case sValueNPCWeightThin:
                _ApplyMemberNumberMofidier(CurrentForm->morphWeight.thin);
                break;
            case sValueNPCWeightMuscular:
                _ApplyMemberNumberMofidier(CurrentForm->morphWeight.muscular);
                break;
            case sValueNPCWeightFat:
                _ApplyMemberNumberMofidier(CurrentForm->morphWeight.fat);
                break;
            case sValueNPCShortName:
                SetSFString(CurrentForm->shortName);
            case sValueNPCFlagActorBaseSet:
                //_DMESSAGE("SETTING FLAG");
                ProcessFlagModifierAlt<true>((std::uint32_t&)CurrentForm->actorData.actorBaseFlags, CurrentModifierValue, NPC::ProcessFlagsForActorBaseData<true>);
                break;
            case sValueNPCFlagActporBaseUnset:
                //_DMESSAGE("UNSETTING FLAG");
                ProcessFlagModifierAlt<false>((std::uint32_t&)CurrentForm->actorData.actorBaseFlags, CurrentModifierValue, NPC::ProcessFlagsForActorBaseData<false>);
                break;

            case sActorPerkAdd:
                ArrayNonForm::_AddRemoveInsert(CurrentForm->perks, CurrentModifierValue, ArrayNonForm::Add<RE::BSTArray<RE::PerkRankData>,PerkRankData::PerkRankDataTomm::Data>, PerkRankData::GetFromString<false>);
                break;
            case sActorPerkRemove:
                ArrayNonForm::_AddRemoveInsert(CurrentForm->perks, CurrentModifierValue, ArrayNonForm::Remove<RE::BSTArray<RE::PerkRankData>, PerkRankData::PerkRankDataTomm::Data>,
                                               PerkRankData::GetFromString<false>);
                break;
            case sActorPerkReplace:
                ArrayNonForm::_ReplaceInArray(CurrentForm->perks, CurrentModifierValue, ArrayNonForm::Replace<RE::BSTArray<RE::PerkRankData>, PerkRankData::PerkRankDataTomm::Data>,
                                              PerkRankData::GetFromString<false>);
                break;
            case sActorPerkClearPerkArray:
                ArrayNonForm::_Clear(CurrentForm->perks);
                break;

            case sValueHeadPartsAdd:
            {
                auto headPartsGuard = CurrentForm->headParts.Lock();
                Array::AddRemoveInArray<RE::BGSHeadPart*>(*headPartsGuard, CurrentModifierValue,
                                                          Array::AddToArray<RE::BGSHeadPart*>, const_GetTypeFromFormType<RE::BGSHeadPart*>());
                break;
            }
            case sValueHeadPartsRemove:
            {
                auto headPartsGuard = CurrentForm->headParts.Lock();
                Array::AddRemoveInArray<RE::BGSHeadPart*>(*headPartsGuard, CurrentModifierValue, Array::RemoveFromArray<RE::BGSHeadPart*>,
                                                          const_GetTypeFromFormType<RE::BGSHeadPart*>());
                break;
            }
            case sValueHeadPartsReplace:
            {
                auto headPartsGuard = CurrentForm->headParts.Lock();
                Array::ReplaceFormInArray<RE::BGSHeadPart*>(*headPartsGuard, CurrentModifierValue, const_GetTypeFromFormType<RE::BGSHeadPart*>());
                break;
            }
            case sValueHeadPartsClear:
                (*CurrentForm->headParts.Lock()).clear();
                break;

            case sValueFactionsAdd:
                ArrayNonForm::_AddRemoveInsert(CurrentForm->factions, CurrentModifierValue, ArrayNonForm::Add<RE::BSTArray<RE::FACTION_RANK>,Factions::EntryFromString::Data>,
                                              Factions::GetFromString<false>);
                break;
            case sValueFactionsRemove:
                ArrayNonForm::_AddRemoveInsert(CurrentForm->factions, CurrentModifierValue,
                                              ArrayNonForm::Remove<RE::BSTArray<RE::FACTION_RANK>, Factions::EntryFromString::Data>,
                                              Factions::GetFromString<false>);
                break;
            case sValueFactionsReplace:
                ArrayNonForm::_ReplaceInArray(CurrentForm->factions, CurrentModifierValue, ArrayNonForm::Replace<RE::BSTArray<RE::FACTION_RANK>, Factions::EntryFromString::Data>,
                                      Factions::GetFromString<false>);
                break;
            case sValueFactionsClear:
                ArrayNonForm::_Clear(CurrentForm->factions);
                break;

             SwitchAddProperties


            case sContainerItemAdd:
                ArrayNonForm::_AddRemoveInsert(CurrentForm->containerObjects, CurrentModifierValue,
                                               ArrayNonForm::Add<RE::BSTArray<RE::ContainerObject>, ContainerItem::EntryFromString::Data>, ContainerItem::GetFromString<false>);
                break;
            case sContainerItemRemove:
                ArrayNonForm::_AddRemoveInsert(CurrentForm->containerObjects, CurrentModifierValue,
                                               ArrayNonForm::Remove<RE::BSTArray<RE::ContainerObject>, ContainerItem::EntryFromString::Data>, ContainerItem::GetFromString<false>);
                break;
            case sContainerItemReplace:
                ArrayNonForm::_ReplaceInArray(CurrentForm->containerObjects, CurrentModifierValue,
                                              ArrayNonForm::Replace<RE::BSTArray<RE::ContainerObject>, ContainerItem::EntryFromString::Data>, ContainerItem::GetFromString<false>);
                break;
            case sContainerItemClear:
                ArrayNonForm::_Clear(CurrentForm->containerObjects);
                break;



            default:
                _DRTFPError("Modifier is not valid for {}, formID>>{:08X}", RE::FormTypeToString(CurrentForm->GetFormType()), CurrentForm->formID);
            }
        }

        template <class T>
        void ProcessModifier(unsigned long CurrentModifierName, T& CurrentModifierValue, RE::TESObjectACTI* CurrentForm)
        {
            switch (CurrentModifierName) {
            SwitchAddKeywordsCases SwitchAddModelCase SwitchAddFullnameSet

            case sValueActivatorWaterForm:
                _SetFormFromModifier(CurrentForm->waterForm);
             SwitchAddProperties
            default: _DRTFPError("Modifier is not valid for {}, formID>>{:08X}", RE::FormTypeToString(CurrentForm->GetFormType()), CurrentForm->formID);
            }
        }

        void ProcessModifier(unsigned long CurrentModifierName, std::string_view CurrentModifierValue, RE::BGSConstructibleObject* CurrentForm)
        {
            switch (CurrentModifierName) {
            SwitchAddValueCase SwitchAddFullnameSet
            case sValueConstructibleWorkbenchKeyword:
                _SetFormFromModifier(CurrentForm->benchKeyword);
            case sValueConstructibleCreatedObject:
                SetFormFromModifierDontCheckForCategory(CurrentForm->createdObject, CurrentModifierValue);
                break;
            case sValueConstructibleBuildLimit:
                _SetFormFromModifier(CurrentForm->maxBuildCount);
            case sValueConstructibleCategory:
                ConstructibleObjects::SetCategory(CurrentForm, CurrentModifierValue); 
                break;
            case sValueConstructibleMenuSortOder:
                _ApplyMemberNumberMofidier(CurrentForm->menuSortOrder);
                break;

                //

            case sValueConstructibleComponentAdd:
                ArrayNonForm::_AddRemoveInsert(CurrentForm->components, CurrentModifierValue,
                                               ArrayNonForm::Add <RE::BSTArray<TUPLE3>*, TUPLE::TupleData::Data>,
                                                   TUPLE::GetFromString<false>);
                break;

            case sValueConstructibleComponentRemove:
                if (CurrentForm->components) {
                    ArrayNonForm::_AddRemoveInsert(CurrentForm->components, CurrentModifierValue, ArrayNonForm::Remove<RE::BSTArray<TUPLE3>*, TUPLE::TupleData::Data>,
                                                   TUPLE::GetFromString<false>);
                }
                else {
                    _DMESSAGE("Components array in {:08X} doesn't exist for item to be removed.", CurrentForm->formID);
                }

                break;

            case sValueConstructibleComponentReplace:
                if (CurrentForm->components) {
                    ArrayNonForm::_ReplaceInArray(CurrentForm->components, CurrentModifierValue, ArrayNonForm::Replace<RE::BSTArray<TUPLE3>*, TUPLE::TupleData::Data>,
                                                  TUPLE::GetFromString<false>);
                }
                {
                    _DMESSAGE("Components array in {:08X} doesn't exist for item to be replaced", CurrentForm->formID);
                }

                break;

            case sValueConstructibleComponentClear:
                if (CurrentForm->components)
                {
                    ArrayNonForm::_Clear(CurrentForm->components);
                }
                else {
                    _DMESSAGE("Components array in {:08X} doesn't exist to be cleared.", CurrentForm->formID);
                }

                break;


            default:
                _DRTFPError("Modifier is not valid for {}, formID>>{:08X}", RE::FormTypeToString(CurrentForm->GetFormType()), CurrentForm->formID);
            }
        }

        void ProcessModifier(unsigned long CurrentModifierName, std::string_view CurrentModifierValue, BGSAVMData* CurrentForm)
        {
            switch (CurrentModifierName) {
            case sAVMDataValueType:
                _ApplyMemberNumberMofidier(CurrentForm->type);
                break;
            case sAVMDataEntryAdd:
                AVMData::AddRemoveForm(CurrentForm, CurrentModifierValue, AVMData::AddToArray);
                break;
            case sAVMDataEntryRemove:
                AVMData::AddRemoveForm(CurrentForm, CurrentModifierValue, AVMData::RemoveFromArray);
                break;
            case sAVMDataEntryReplace:
                AVMData::ProcessReplacing(CurrentForm, CurrentModifierValue);
                break;
            case sAVMDataEntryClear:
                AVMData::ClearArray(CurrentForm);
                break;
            default:
                _DRTFPError("Modifier is not valid for {}, formID>>{:08X}", RE::FormTypeToString(CurrentForm->GetFormType()), CurrentForm->formID);
            }
        }


    }





   template <class T>
   void ProcessModifiersForVectorAlt(std::vector<T>& vec, std::string_view& ModifierSection)
   {
        size_t                    CurrentPos     = 0;
        size_t                    NewModifierPos = 0;
        std::vector<TempModifierAlt> vModifiers;

        while (NewModifierPos != NONPOS) {
            NewModifierPos = ModifierSection.find(sSectionDelimeter, CurrentPos);
            _DMESSAGE("Modifier pos>>{}, CurrentPos>>{}", NewModifierPos, CurrentPos);

            std::string_view CurrentModifier = ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos);
            //_DMESSAGE("Modifier>>>{}", CurrentModifier);

            auto BracketLeftPos = CurrentModifier.find(sValueDelimeterLeft);

            if (BracketLeftPos != NONPOS) {
                std::string_view CurrentModifierName = CurrentModifier.substr(0, BracketLeftPos);

                auto BracketRightPos = CurrentModifier.find_last_of(sValueDelimeterRight);

                if (BracketRightPos != NONPOS) {
                    TempModifierAlt NewModifier;
                    NewModifier.CurrentModifierName  = hash_djb2a(CurrentModifierName);
                    NewModifier.value.CurrentModifierValue = CurrentModifier.substr(BracketLeftPos + 1, BracketRightPos - BracketLeftPos - 1);
                    _DMESSAGE("Adding Modifier to ARRAY, NAME>>{},Value>>{}, Name hash>>{}", CurrentModifierName, NewModifier.value.CurrentModifierValue,
                              NewModifier.CurrentModifierName);
                    vModifiers.push_back(std::move(NewModifier));
                }
            }

            CurrentPos = NewModifierPos + 1;
        }

        if (!vModifiers.size()) {
            _DMESSAGE("No modifiers found in {}", ModifierSection);
            return;
        }

        for (auto it2 = vModifiers.begin(); it2 != vModifiers.end();) {
            _MESSAGE(" Testing Modifiers HASH>>{},Value>>{},form>>{:08X}", Iter2.CurrentModifierName, Iter2.value.CurrentModifierValue, vec.at(0)->formID);
            ProcessModifiers::ProcessModifier(Iter2.CurrentModifierName, Iter2.value, vec.at(0));

            if (IsFlagSet(Iter2.value.flags, TempModifierAlt::Flags::kNeedsToBeValid) && !IsFlagSet(Iter2.value.flags, TempModifierAlt::Flags::kValid)) {
                _DMESSAGE("{} is NOT valid - erasing from modifiers.", Iter2.value.CurrentModifierValue);
                it2 = vModifiers.erase(it2);
            }
            else {
                _DMESSAGE("{} is valid - continuing.", Iter2.value.CurrentModifierValue);
                it2++;
            }
        }

        if (!vModifiers.size()) {
            _DMESSAGE("No modifiers left after checking first form for them>>{}", ModifierSection);
            return;
        }


        if (bDebugMode) {

            for (auto it = vec.begin() + 1; it != vec.end(); it++) {
                for (auto it2 = vModifiers.begin(); it2 != vModifiers.end(); it2++) {
                    _MESSAGE("ProcessModifier HASH>>{},Value>>{},form>>{:08X}", Iter2.CurrentModifierName, Iter2.value.CurrentModifierValue, Iter->formID);
                    ProcessModifiers::ProcessModifier(Iter2.CurrentModifierName, Iter2.value, Iter);
                }
            }
        }
        else {
            for (auto it = vec.begin() + 1; it != vec.end(); it++) {
                for (auto it2 = vModifiers.begin(); it2 != vModifiers.end(); it2++) {
                    ProcessModifiers::ProcessModifier(Iter2.CurrentModifierName, Iter2.value, Iter);
                }
            }
        }
   }




    template <class T>
    void ProcessModifiersForVector(std::vector<T>& vec, std::string_view& ModifierSection)
    {
        size_t                    CurrentPos     = 0;
        size_t                    NewModifierPos = 0;
        std::vector<TempModifier> vModifiers;

        while (NewModifierPos != NONPOS) {
            NewModifierPos = ModifierSection.find(sSectionDelimeter, CurrentPos);
            _DMESSAGE("Modifier pos>>{}, CurrentPos>>{}", NewModifierPos, CurrentPos);

            std::string_view CurrentModifier = ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos);
            //_DMESSAGE("Modifier>>>{}", CurrentModifier);

            auto BracketLeftPos = CurrentModifier.find(sValueDelimeterLeft);

            if (BracketLeftPos != NONPOS) {
                std::string_view CurrentModifierName = CurrentModifier.substr(0, BracketLeftPos);

                auto BracketRightPos = CurrentModifier.find_last_of(sValueDelimeterRight);

                if (BracketRightPos != NONPOS) {
                    TempModifier NewModifier;
                    NewModifier.CurrentModifierName  = hash_djb2a(CurrentModifierName);
                    NewModifier.CurrentModifierValue = CurrentModifier.substr(BracketLeftPos + 1, BracketRightPos - BracketLeftPos - 1);
                    _DMESSAGE("Adding Modifier to ARRAY, NAME>>{},Value>>{}, Name hash>>{}", CurrentModifierName, NewModifier.CurrentModifierValue,
                              NewModifier.CurrentModifierName);
                    vModifiers.push_back(std::move(NewModifier));
                }
            }

            CurrentPos = NewModifierPos + 1;
        }

        if (!vModifiers.size()) {
            _DMESSAGE("No modifiers found in {}", ModifierSection);
            return;
        }

        if (bDebugMode) {
            for (auto it = vec.begin(); it != vec.end(); it++) {
                for (auto it2 = vModifiers.begin(); it2 != vModifiers.end(); it2++) {
                    _MESSAGE("ProcessModifier HASH>>{},Value>>{},form>>{:08X}", Iter2.CurrentModifierName, Iter2.CurrentModifierValue, Iter->formID);
                    ProcessModifiers::ProcessModifier(Iter2.CurrentModifierName, Iter2.CurrentModifierValue, Iter);
                }
            }
        }
        else {
            for (auto it = vec.begin(); it != vec.end(); it++) {
                for (auto it2 = vModifiers.begin(); it2 != vModifiers.end(); it2++) {
                    ProcessModifiers::ProcessModifier(Iter2.CurrentModifierName, Iter2.CurrentModifierValue, Iter);
                }
            }
        }
    }


    template <typename>
    struct is_std_vector : std::false_type
    {
    };

    template <typename T, typename A>
    struct is_std_vector<std::vector<T, A>> : std::true_type
    {
    };

    template<class T>
    void ProcessFormUniversal(int& iCurrentSection, T& CurrentForm, std::string_view& ModifierSection)
    {

        switch (iCurrentSection) {
        case Sections::k_FormList:

            if constexpr (is_std_vector<T>::value)
            {

            }
            else {

            }
        default:
            _DMESSAGE("Current section is undefined>>{}", iCurrentSection);
            break;
        }

    }

    template <class T>
    void ProcessModifiersForForm(T* CurrentForm, std::string_view& ModifierSection)
    {
        size_t CurrentPos     = 0;
        size_t NewModifierPos = 0;
        while (NewModifierPos != NONPOS) {
            NewModifierPos = ModifierSection.find(sSectionDelimeter, CurrentPos);
            _DMESSAGE("Modifier pos>>{}, CurrentPos>>{}", NewModifierPos, CurrentPos);

            std::string_view CurrentModifier = ModifierSection.substr(CurrentPos, NewModifierPos - CurrentPos);
            _DMESSAGE("Modifier>>><{}>", CurrentModifier);

            auto BracketLeftPos = CurrentModifier.find(sValueDelimeterLeft);

            if (BracketLeftPos != NONPOS) {
                std::string_view CurrentModifierName = CurrentModifier.substr(0, BracketLeftPos);

                auto BracketRightPos = CurrentModifier.find_last_of(sValueDelimeterRight);

                if (BracketRightPos != NONPOS) {
                    std::string_view CurrentModifierValue = CurrentModifier.substr(BracketLeftPos + 1, BracketRightPos - BracketLeftPos - 1);

                    _DMESSAGE("ProcessModifiersForForm Modifier>>{}, Modifier value>>{}", CurrentModifierName, CurrentModifierValue);
                    ProcessModifiers::ProcessModifier(hash_djb2a(CurrentModifierName), CurrentModifierValue, CurrentForm);
                }
                else {
                    _DRTFPError("No right bracket for {}", CurrentModifier);
                }
            }
            else {
                _DRTFPError("No left bracket for {}", CurrentModifier);
            }

            CurrentPos = NewModifierPos + 1;
        }
    }


    void _ProcessModifiersForFormHelper(int& iCurrentSection, TESFormResult& CurrentForm, std::string_view& ModifierSection) {

        switch (iCurrentSection) {
        case Sections::k_FormList:
            ProcessModifiersForForm((RE::BGSListForm*)CurrentForm.data, ModifierSection);
            break;
        case Sections::k_Global:
            ProcessModifiersForForm((RE::TESGlobal*)CurrentForm.data, ModifierSection);
            break;
        case Sections::k_AVMData:
            ProcessModifiersForForm((BGSAVMData*)CurrentForm.data, ModifierSection);
            break;
        case Sections::k_LeveledList_BaseForm:
        case Sections::k_LeveledList_NPC:
        case Sections::k_LeveledList_Item:
        case Sections::k_LeveledList_PackIn:
            ProcessModifiersForLeveledList((RE::TESLevCharacter*)CurrentForm.data, ModifierSection);
            break;
        case Sections::k_NPC:
            ProcessModifiersForForm((RE::TESNPC*)CurrentForm.data, ModifierSection);
            break;
        case Sections::k_Misc:
            ProcessModifiersForForm((RE::TESObjectMISC*)CurrentForm.data, ModifierSection);
            break;
        case Sections::k_Ammo:
            ProcessModifiersForForm((RE::TESAmmo*)CurrentForm.data, ModifierSection);
            break;
        case Sections::k_Projectile:
            ProcessModifiersForForm((RE::BGSProjectile*)CurrentForm.data, ModifierSection);
            break;
        case Sections::k_Weapons:
            ProcessModifiersForForm((RE::TESObjectWEAP*)CurrentForm.data, ModifierSection);
            break;
        case Sections::k_Armors:
            ProcessModifiersForForm((RE::TESObjectARMO*)CurrentForm.data, ModifierSection);
            break;
        case Sections::k_Perk:
            ProcessModifiersForForm((RE::BGSPerk*)CurrentForm.data, ModifierSection);
            break;
        case Sections::k_Activator:
            ProcessModifiersForForm((RE::TESObjectACTI*)CurrentForm.data, ModifierSection);
            break;
        case Sections::k_Constructible:
            ProcessModifiersForForm((RE::BGSConstructibleObject*)CurrentForm.data, ModifierSection);
            break;
        case Sections::k_Spell:
            ProcessModifiersForForm((RE::SpellItem*)CurrentForm.data, ModifierSection);
            break;
        case Sections::k_Static:
            ProcessModifiersForForm((RE::TESObjectSTAT*)CurrentForm.data, ModifierSection);
            break;
        case Sections::k_CELL:
            ProcessModifiersForForm((RE::TESObjectCELL*)CurrentForm.data, ModifierSection);
            break;
        case Sections::k_Book:
            ProcessModifiersForForm((RE::TESObjectBOOK*)CurrentForm.data, ModifierSection);
            break;
        case Sections::k_ConditionForm:
            ProcessModifiersForForm((RE::BGSConditionForm*)CurrentForm.data, ModifierSection);
            break;
        case Sections::k_VoiceType:
            ProcessModifiersForForm((RE::BGSVoiceType*)CurrentForm.data, ModifierSection);
            break;
        case Sections::k_StoryManagerQuestNode:
            ProcessModifiersForForm((BGSStoryManagerQuestNode*)CurrentForm.data, ModifierSection);
            break;
        case Sections::k_Message:
            ProcessModifiersForForm((RE::BGSMessage*)CurrentForm.data, ModifierSection);
            break;
        case Sections::k_Ingestible:
            ProcessModifiersForForm((RE::AlchemyItem*)CurrentForm.data, ModifierSection);
            break;
        case Sections::k_Outfit:
            ProcessModifiersForForm((RE::BGSOutfit*)CurrentForm.data, ModifierSection);
            break;
        case Sections::k_Container:
            ProcessModifiersForForm((RE::TESObjectCONT*)CurrentForm.data, ModifierSection);
            break;
        case Sections::k_MagicEffect:
            ProcessModifiersForForm((RE::EffectSetting*)CurrentForm.data, ModifierSection);
            break;
        case Sections::k_PlanetContentManagerBranchNode:
            ProcessModifiersForForm((TommPlanetContentManagerBranchNode*)CurrentForm.data, ModifierSection);
            break;
        case Sections::k_Race:
            ProcessModifiersForForm((RE::TESRace*)CurrentForm.data, ModifierSection);
            break;
        case Sections::k_ObjectModification:
            ProcessModifiersForForm((RE::BGSMod::Attachment::Mod*)CurrentForm.data, ModifierSection);
            break;
        case Sections::k_Terminal:
            ProcessModifiersForForm((RE::BGSTerminal*)CurrentForm.data, ModifierSection);
            break;
        case Sections::kLoadScreen:
            ProcessModifiersForForm((RE::TESLoadScreen*)CurrentForm.data, ModifierSection);
            break;
        case Sections::k_Location:
            ProcessModifiersForForm((RE::BGSLocation*)CurrentForm.data, ModifierSection);
            break;

        case Sections::k_Debug:
            if (bDebugMode) {
                Debug::ProcessFormFromLine(CurrentForm.data);
            }
            break;

        default:
            _DRTFPError("Current section is undefined>>{}", iCurrentSection);
            break;
        }

    }


    void _ProcessModifiersForVectorHelper(int& iCurrentSection, std::vector<RE::TESForm*>& vec, std::string_view& ModifierSection)
    {

        switch (iCurrentSection) {
        case Sections::k_FormList:
            ProcessModifiersForVectorAlt((std::vector<RE::BGSListForm*>&)vec, ModifierSection);
            break;
        case Sections::k_Global:
            ProcessModifiersForVectorAlt((std::vector<RE::TESGlobal*>&)vec, ModifierSection);
            break;
        case Sections::k_Ammo:
            ProcessModifiersForVectorAlt((std::vector<RE::TESAmmo*>&)vec, ModifierSection);
            break;
        case Sections::k_Projectile:
            ProcessModifiersForVectorAlt((std::vector<RE::BGSProjectile*>&)vec, ModifierSection);
            break;
        case Sections::k_Weapons:
            ProcessModifiersForVectorAlt((std::vector<RE::TESObjectWEAP*>&)vec, ModifierSection);
            break;
        case Sections::k_Armors:
            ProcessModifiersForVectorAlt((std::vector<RE::TESObjectARMO*>&)vec, ModifierSection);
            break;
        case Sections::k_Misc:
            ProcessModifiersForVectorAlt((std::vector<RE::TESObjectMISC*>&)vec, ModifierSection);
            break;
        case Sections::k_Perk:
            ProcessModifiersForVector((std::vector<RE::BGSPerk*>&)vec, ModifierSection);
            break;
        case Sections::k_NPC:
            ProcessModifiersForVectorAlt((std::vector<RE::TESNPC*>&)vec, ModifierSection);
            break;
        case Sections::k_Activator:
            ProcessModifiersForVectorAlt((std::vector<RE::TESObjectACTI*>&)vec, ModifierSection);
            break;
        case Sections::k_Constructible:
            ProcessModifiersForVectorAlt((std::vector<RE::BGSConstructibleObject*>&)vec, ModifierSection);
            break;
        case Sections::k_Spell:
            ProcessModifiersForVectorAlt((std::vector<RE::SpellItem*>&)vec, ModifierSection);
            break;
        case Sections::k_Static:
            ProcessModifiersForVectorAlt((std::vector<RE::TESObjectSTAT*>&)vec, ModifierSection);
            break;
        case Sections::k_AVMData:
            ProcessModifiersForVectorAlt((std::vector<BGSAVMData*>&)vec, ModifierSection);
            break;
        case Sections::k_CELL:
            ProcessModifiersForVectorAlt((std::vector<RE::TESObjectCELL*>&)vec, ModifierSection);
            break;
        case Sections::k_Book:
            ProcessModifiersForVectorAlt((std::vector<RE::TESObjectBOOK*>&)vec, ModifierSection);
            break;
        case Sections::k_ConditionForm:
            ProcessModifiersForVectorAlt((std::vector<RE::BGSConditionForm*>&)vec, ModifierSection);
            break;
        case Sections::k_VoiceType:
            ProcessModifiersForVectorAlt((std::vector<RE::BGSVoiceType*>&)vec, ModifierSection);
            break;
        case Sections::k_StoryManagerQuestNode:
            ProcessModifiersForVectorAlt((std::vector<BGSStoryManagerQuestNode*>&)vec, ModifierSection);
            break;
        case Sections::k_Message:
            ProcessModifiersForVectorAlt((std::vector<RE::BGSMessage*>&)vec, ModifierSection);
            break;
        case Sections::k_Ingestible:
            ProcessModifiersForVectorAlt((std::vector<RE::AlchemyItem*>&)vec, ModifierSection);
            break;
        case Sections::k_Outfit:
            ProcessModifiersForVectorAlt((std::vector<RE::BGSOutfit*>&)vec, ModifierSection);
            break;
        case Sections::k_Container:
            ProcessModifiersForVectorAlt((std::vector<RE::TESObjectCONT*>&)vec, ModifierSection);
            break;
        case Sections::k_PlanetContentManagerBranchNode:
            ProcessModifiersForVectorAlt((std::vector<TommPlanetContentManagerBranchNode*>&)vec, ModifierSection);
            break;
        case Sections::k_MagicEffect:
            ProcessModifiersForVectorAlt((std::vector<RE::EffectSetting*>&)vec, ModifierSection);
            break;
        case Sections::k_Race:
            ProcessModifiersForVectorAlt((std::vector<RE::TESRace*>&)vec, ModifierSection);
            break;
        case Sections::k_ObjectModification:
            ProcessModifiersForVectorAlt((std::vector<RE::BGSMod::Attachment::Mod*>&)vec, ModifierSection);
            break;
        case Sections::k_Terminal:
            ProcessModifiersForVectorAlt((std::vector<RE::BGSTerminal*>&)vec, ModifierSection);
            break;
        case Sections::kLoadScreen:
            ProcessModifiersForVectorAlt((std::vector<RE::TESLoadScreen*>&)vec, ModifierSection);
            break;
        case Sections::k_Location:
            ProcessModifiersForVectorAlt((std::vector<RE::BGSLocation*>&)vec, ModifierSection);
            break;

        case Sections::k_Reference:
            _DRTFPError("Multiple references processing is not supported in this verson!");
            break;

        case Sections::k_LeveledList_BaseForm:
        case Sections::k_LeveledList_NPC:
        case Sections::k_LeveledList_Item:
        case Sections::k_LeveledList_PackIn:

            for (auto it = vec.begin(); it != vec.end(); it++) {
                ProcessModifiersForLeveledList((RE::TESLevCharacter*)Iter, ModifierSection);
            }
            break;

        default:
            _DRTFPError("Current section is undefined>>{}", iCurrentSection);
            break;
        }
    }




    

    void GetAndProcessReferenceFromString(std::string_view FormIDValue, std::string_view ModifierSection)
    {
        auto DelimeterPos = FormIDValue.find(sParametersDelimeter);

        TESFormResult CurrentForm{};

        if (DelimeterPos == NONPOS) {
            CurrentForm = GetFormFromStringAndDontCheckForCategory<false>(FormIDValue);

            if (!CurrentForm.bValid) {
                return;
            }

            if (CurrentForm.data->formType == RE::FormType::kREFR || CurrentForm.data->formType == RE::FormType::kACHR) {
            }
            else {
                _DRTFPError("This forms has type of >>{} - not actor or ref", CurrentForm.data->formType.underlying());
                return;
            }

            ProcessModifiersForForm((RE::TESObjectREFR*)CurrentForm.data, ModifierSection);



        }
        else {
            _DMESSAGE("Form is temporary.");
            auto Cell = GetFormFromStringAndCheckForCategory<false>(FormIDValue.substr(DelimeterPos + 1, FormIDValue.length() - DelimeterPos + 1),
                                                                    const_GetTypeFromFormType<RE::TESObjectCELL*>());

            if (!Cell.bValid) {
                return;
            }

            auto FormID = GetFormIDFromStringEx(FormIDValue.substr(0, DelimeterPos));

            if (!FormID)
            {
                _DMESSAGE("Cannot build ref formID from string>>{}", FormIDValue.substr(0, DelimeterPos));
                return;
            }

            RE::TESObjectCELL* CellUse = (RE::TESObjectCELL*)Cell.data;

            for (auto it = CellUse->references.begin(); it != CellUse->references.end(); it++)
            {
                auto CurrentRef = Iter.get();

                if (CurrentRef)
                {
                    _DMESSAGE("new ref in cell>>{:08X}", CurrentRef->formID);

                    if (CurrentRef->formID == FormID) {
                        _DMESSAGE("form in cell found>>{:08X}", CurrentForm.data->formID);
                        ProcessModifiersForForm(CurrentRef, ModifierSection);
                        return;
                    }
                }

            }

        }


    }

    void ProcessLine(std::string_view v, int& iCurrentSection)
    {
        if (!v.size()) {
            //_DMESSAGE("new line is empty");
            return;
        }

        if (v.at(0) == sSkipLineSymbol) {
            _DMESSAGE("SKIPPING LINE");
            return;
        }

        _DMESSAGE("-------------------------------new line>>{}", v);


        if (v.at(0) == '[') {
            auto Pos = v.find(']');

            if (Pos == NONPOS) {
                _DRTFPError("could not find closing bracket for {}", v);
                iCurrentSection = k_None;
                return;
            }

            if (Pos < 2) {
                _DRTFPError("Section name is not specified", v);
                iCurrentSection = k_None;
                return;
            }

            std::string_view sSection = v.substr(1, Pos - 1);
            //_DMESSAGE("new section>>{}", sSection);


            auto CurrentSection = Input::GetSectionByName(sSection);

            if (!CurrentSection)
            {
                iCurrentSection = k_None;
                _DRTFPError("[{}] category is not supported.", sSection);
                return;
            }

            iCurrentSection = CurrentSection->SectionID;
            _DMESSAGE("New section>>{}", sSection);
            return;

        }

        if (iCurrentSection == Sections::k_None) {
            _DMESSAGE("No section or incorrect section - skip line.");
            return;
        }


        TESFormResult CurrentForm;

        auto PipePose = v.find(sSectionDelimeter);

        if (PipePose == NONPOS) {
            _DRTFPError("Cannot find first Pipe in {} - that means you haven't set any modifiers for the form.", v);
            return;
        }
        else if (PipePose == 0) {
            _DRTFPError("No form specified in ", v);
            return;
        }

        std::string_view FormIDValue = v.substr(0, PipePose);

        if (!FormIDValue.length())
        {
            _DRTFPError("Lenght of FormID is 0.");
            return;
        }


        std::string_view ModifierSection = v.substr(PipePose + 1, v.length() - PipePose - 1);



        if (iCurrentSection == Sections::k_Gamesettings) {
            Input::GameSettingsProcessing::ProcessGameSettingsLine(FormIDValue, ModifierSection);
            return;
        }
        if (iCurrentSection == Sections::k_Condition) {
            Input::Condition::ProcessConditionLine(FormIDValue, ModifierSection);
            return;
        }
        if (iCurrentSection == Sections::k_Filters)
        {

            Input::CustomFilters::CreateFilterFromLine(FormIDValue, ModifierSection);
            return;
        }
        else if (iCurrentSection == Sections::k_Reference) {
            GetAndProcessReferenceFromString(FormIDValue, ModifierSection);
            return;
        }
        else if (FormIDValue.at(0) == sSearchForAllFormsSymbol)
        {
            std::vector<RE::TESForm*> vForms = GetAllLoadedTypeFormsFromLineAndProcessFilters(iCurrentSection, FormIDValue);

            if (!vForms.size()) {
                _DMESSAGE("No forms left after filters.");
                return;
            }

            _ProcessModifiersForVectorHelper(iCurrentSection, vForms, ModifierSection);

            return;
        }
        else if (FormIDValue.at(0) == sSearchForMultipleForms)
        {
            std::vector<RE::TESForm*> vForms = GetMultipleFormsFromLine(iCurrentSection, FormIDValue);

            if (!vForms.size()) {
                _DMESSAGE("No forms left after filters.");
                return;
            }

            _ProcessModifiersForVectorHelper(iCurrentSection, vForms, ModifierSection);

            return;
        }
        else if (FormIDValue.at(0) == sSearchForFilters) {

            auto CustomFilter = Input::CustomFilters::GetFilterByName(FormIDValue.substr(1, FormIDValue.length() - 1));

            if (!CustomFilter)
            {
                _DRTFPError("Cannot find a filter with name>>{}", FormIDValue.substr(1, FormIDValue.length() - 1));
                return;
            }

            if (CustomFilter->iSection != iCurrentSection)
            {
                _DRTFPError("Cannot accept filter forms for current section {}. Section in filters>>{}", iCurrentSection, CustomFilter->iSection);
                return;
            }

            _DMESSAGE("Found filter,forms>>{}", CustomFilter->forms.size());

            _ProcessModifiersForVectorHelper(iCurrentSection, CustomFilter->forms, ModifierSection);
            return;
        }
        else {
                CurrentForm = GetFormFromStringAndCheckForCategory<false>(FormIDValue, iCurrentSection);

                if (!CurrentForm.bValid) {

                    return;
                    //if (iCurrentSection == Input::Sections::k_Debug && CurrentForm.data)
                    //{
                    //    _DMESSAGE("But it's debug so let's continue");
                    //}
                    //else {
                    //    return;
                    //}
                }
        }

        //auto SecondPipePose = v.find(sSectionDelimeter, PipePose + 1);

        //if (SecondPipePose == NONPOS) {
        //    _DMESSAGE("Cannot find second Pipe in {}", v);
        //    return;
        //}
        //else if (SecondPipePose - PipePose == 1) {
        //    _DMESSAGE("Nothing specified in form setters ", v);
        //    return;
        //}

        _DMESSAGE("Modifier section from the line>>{}", ModifierSection);

        _ProcessModifiersForFormHelper(iCurrentSection, CurrentForm, ModifierSection);
    }



    bool ProcessFileModifier(std::string_view ModifierSection, File& file, int& iModifiersFound) // if returned false - file will not be processed( minver check)
    {
        size_t EqualPos = ModifierSection.find("=", 0);


        if (EqualPos == NONPOS)
        {
            return true;
        }

        std::string_view sModifier = ModifierSection.substr(0, EqualPos);
        std::string_view sValue    = ModifierSection.substr(EqualPos + 1, ModifierSection.length() - EqualPos + 1);

        _DMESSAGE("Modifier>>>{},Value>>{}", sModifier, sValue);

        if (sModifier == "minver")
        {
            iModifiersFound++;
            auto IntResult = GetNumberFromString<std::int32_t>(sValue);

            if (!IntResult.bSuccess) {
                    _DMESSAGE("-------------------------!!!Cannot convert specified minver to integer.");
            }
            else {
                    if (IntResult.data > iVersion) {
                        _MESSAGE("SKIPPING FILE {} - minimum version required is {}, plugin Version>{}", file.name, IntResult.data, iVersion);

                        float       fTempVersion = IntResult.data;
                        fTempVersion /= 100;

                        sFileErrors += "File " + file.name + " requires RTFP - V." + std::format("{:.2f}", fTempVersion) + "\n";
                        return false;
                    }
            }

            
        }
        else if (sModifier == "priority")
        {
            iModifiersFound++;
            auto IntResult = GetNumberFromString<std::int32_t>(sValue);
            file.Priority  = IntResult.data;
            _DMESSAGE("Setting priority to {}", file.Priority);
            return true;
        }
        else if (sModifier == "onlyifpluginloaded")
        {

            auto BracketLeftPos = sValue.find(sValueDelimeterLeft);

            if (BracketLeftPos != NONPOS) {
                    std::string_view PluginName = sValue.substr(0, BracketLeftPos);

                    auto BracketRightPos = sValue.find_last_of(sValueDelimeterRight);

                    if (BracketRightPos != NONPOS) {
                        std::string_view CurrentModifierValue = sValue.substr(BracketLeftPos + 1, BracketRightPos - BracketLeftPos - 1);

                        _DMESSAGE("ProcessModifiersFor <onlyifpluginloaded>  Plugin>>{}, Modifier value>>{}", PluginName, CurrentModifierValue);
                        iModifiersFound++;
                        file.RequiresPluginLoaded = PluginName;

                        if (CurrentModifierValue.find("notify") != NONPOS) {
                            file.RequiresPluginLoadedWarning = true;
                            _DMESSAGE("Notify user if file is not loaded");
                        }
                        _DMESSAGE("File requires <{}> plugin to be loaded.", file.RequiresPluginLoaded);
                        return true;

                    }
            }

        }
        else {
            _DMESSAGE("Modifier {} is not recognized", sModifier);
            return true;
        }


        return true;
        
    }




     bool ProcessFileModifiers(File& file,std::string& content) {

        if (content.at(0) == '#') {
            _DMESSAGE("# found - skipping first line.");
            return true;
        }
 
        std::string_view sTemp              = content;
        auto             FirstLineSeparator = sTemp.find("\n");


        if (FirstLineSeparator == NONPOS) {
            _DMESSAGE("No new line separator.");
            return true;
        }
        std::string_view sFirstLine = sTemp.substr(0, FirstLineSeparator);

        size_t CurrentPos     = 0;
        size_t NewModifierPos = 0;

        int iModifiersFound = 0;

        while (NewModifierPos != NONPOS) {
            NewModifierPos = sFirstLine.find(sSectionDelimeter, CurrentPos);


            if (!ProcessFileModifier(sFirstLine.substr(CurrentPos, NewModifierPos - CurrentPos), file, iModifiersFound))
            {
                return false;
            }
            
            CurrentPos = NewModifierPos + 1;
        }

        if (iModifiersFound)
        {
            content.erase(0, FirstLineSeparator + 1);
            file.firstLineRemoved = true;
        }

         return true;
     }




     void CheckAndRemoveBOM(std::ifstream& is)
     {
         /* Read the first byte. */
         const char c0 = is.get();
         if (c0 != '\xEF') {
            is.putback(c0);
            return;
         }

         /* Read the second byte. */
         const char c1 = is.get();
         if (c1 != '\xBB') {
            is.putback(c1);
            is.putback(c0);
            return;
         }

         /* Peek the third byte. */
         const char c2 = is.peek();
         if (c2 != '\xBF') {
            is.putback(c1);
            is.putback(c0);
            return;
         }

         _DMESSAGE("file has UTF-8-BOM encoding - accounting.");
         is.ignore(1);
         return; // This file contains a BOM for UTF-8.
     }


     bool _forceinline ProcessMofidiersAndAddNewFileToVector(File& file, std::string& str)
     {
         _DMESSAGE("first char>>{}", str.at(0));

         if (!ProcessFileModifiers(file, str)) {
            return false;
         }
         file.content = std::move(str);

         file.ID = iFileIDCount;
         iFileIDCount++;
         files.push_back(std::move(file));
         return true;
     }



    bool StoreFile(std::filesystem::directory_entry DirEntry)
    {
        std::string sFileName = DirEntry.path().string();

        _DMESSAGE("Storing file {}", sFileName);
        std::ifstream t(sFileName);
        CheckAndRemoveBOM(t);


        std::string str(std::istreambuf_iterator<char>{ t }, {});

        if (!str.size())
        {
            _DMESSAGE("File is empty!");
            return false;
        }


        File NewFile;
        NewFile.name = DirEntry.path().filename().string();
        return ProcessMofidiersAndAddNewFileToVector(NewFile, str);
    }

    void ClearStoredEntries()
    {
        if (StoredEntries::v_Stored.size()) {
            _DMESSAGE("Dropping {} stored restore entries (game data was reset).", StoredEntries::v_Stored.size());
        }
        StoredEntries::v_Stored.clear();
    }

    void RestoreOldEnries()
    {
        _DMESSAGE("Restoring old entries before reset,count>>{}", StoredEntries::v_Stored.size());

        for (auto it = StoredEntries::v_Stored.begin(); it != StoredEntries::v_Stored.end(); it++)
        {
            _DMESSAGE("Form>>{:08X}", Iter.formIn->formID);
            std::uint8_t FormType = Iter.formIn->formType.underlying();

            if (FormType == (std::uint8_t)RE::FormType::kAVMD)
            {
                _DMESSAGE("Restoring AVM Data");
                auto formIn         = (BGSAVMData*)Iter.formIn;
                formIn->firstEntry = (RE::AVMData::Entry*)Iter.firstEntry;
                formIn->lastEntry = (RE::AVMData::Entry*)Iter.lastEntry;
                formIn->lastEntry2  = (RE::AVMData::Entry*)Iter.lastEntry2;
                _DMESSAGE("Deleting  AVM RTFP entries.");
                delete[] (RE::AVMData::Entry*)Iter.NewFirstEntryAddress;
                _DMESSAGE("Deleting AVM RTFP entries done.");
            }
            else if (FormType == (std::uint8_t)RE::FormType::kLVLB || FormType == (std::uint8_t)RE::FormType::kLVLN || FormType == (std::uint8_t)RE::FormType::kLVLI
                || FormType == (std::uint8_t)RE::FormType::kLVLP)
            {
                _DMESSAGE("Restoring LVLed lists");
                auto  formIn = (RE::TESLevCharacter*)Iter.formIn;
                formIn->leveledLists        = (RE::LEVELED_OBJECT*)Iter.firstEntry;
                formIn->baseListCount       = Iter.lastEntry;

                _DMESSAGE("Deleting LVLed list RTFP entries.");
                delete[] (RE::LEVELED_OBJECT*)Iter.NewFirstEntryAddress;
                _DMESSAGE("Deleting LVLed list RTFP entries done.");
            }
            else if (FormType == (std::uint8_t)RE::FormType::kWEAP) {
                _DMESSAGE("Restoring WEAP");
                auto  formIn   = (RE::TESObjectWEAP*)Iter.formIn;
                auto& triplet  = RTFP::Triplet(RTFP::AttachKeywords(formIn->attachParents));
                triplet.begin       = (void*)Iter.firstEntry;
                triplet.end         = (void*)Iter.lastEntry;
                triplet.capacityEnd = (void*)Iter.lastEntry2;

                //_DMESSAGE("Deleting ATTP Weapon RTFP entries.");
                //delete[] (RE::BGSKeyword**)Iter.NewFirstEntryAddress;
                //_DMESSAGE("Deleting ATTP Weapon RTFP entries done.");
            }
            else if (FormType == (std::uint8_t)RE::FormType::kARMO) {
                _DMESSAGE("Restoring ARMO");
                auto  formIn   = (RE::TESObjectARMO*)Iter.formIn;
                auto& triplet  = RTFP::Triplet(RTFP::AttachKeywords(formIn->attachParents));
                triplet.begin       = (void*)Iter.firstEntry;
                triplet.end         = (void*)Iter.lastEntry;
                triplet.capacityEnd = (void*)Iter.lastEntry2;

                //_DMESSAGE("Deleting ATTP Armor RTFP entries.");
                //delete[] (RE::BGSKeyword**)Iter.NewFirstEntryAddress;
                //_DMESSAGE("Deleting ATTP Armor RTFP entries done.");
            }
            else {
                _DMESSAGE("--------------------UNKNOWN TYPE TO RESTORE>>{}", FormType);
            }



        }

        _DMESSAGE("Clearing stored entries.");
        StoredEntries::v_Stored.clear();

    }

    template <class T>
    void ProcessAndClearArray(T& Arr, const char* Name)
    {
        if (Arr.size()) {
            _DMESSAGE("Applying changes for {} array.", Name);
            for (auto it = Arr.begin(); it != Arr.end(); it++) {
                if (Iter.bAffected) {
                        Iter.ApplyChanges();
                        _DMESSAGE("Applied changes for>>{:08X}", Iter.formIn->formID);
                }
            }
            Arr.clear();
        }
    }

    void CleanUpAfterFileProcessing()
    {
        Input::Condition::tesConditionsFromString.clear();
        Input::CustomFilters::v_filters.clear();
        ProcessAndClearArray(AVMData::vStored, GET_VARIABLE_NAME(AVMData::vStored));
        ProcessAndClearArray(AttachParentsArray::v_WeaponBGSEntries, GET_VARIABLE_NAME(AttachParentsArray::v_WeaponBGSEntries));
        ProcessAndClearArray(AttachParentsArray::v_ArmorBGSEntries, GET_VARIABLE_NAME(AttachParentsArray::v_ArmorBGSEntries));
        ProcessAndClearArray(LeveledLists::vStored, GET_VARIABLE_NAME(LeveledLists::vStored));
    }

    template<bool SingleProcessing>
    void ProcessFile(Input::File& file)
    {
        _DMESSAGE("---------------------------------------------------------------------Processing file>>{}", file.name);
        currentFile = &file;
        if (file.RequiresPluginLoaded.length())
        {
            auto ModInfo = LoadedPlugins::GetModInfo(file.RequiresPluginLoaded);

            if (ModInfo == NULL) {
                _DMESSAGE("Plugin <{}> is not loaded - don't process file", file.RequiresPluginLoaded);

                if (file.RequiresPluginLoadedWarning)
                {
                    sFileErrors += "File " + file.name + " requires " + file.RequiresPluginLoaded + " to be loaded." + "\n";
                }

                return;
            }
        }

        iFilesProcessed++;
        file.TimesProcessed++;
        
        std::string_view sTemp = file.content;

        Input::CustomFilters::v_filters.clear();

        size_t CurrentPos = 0;
        size_t NewLinePos = 0;

        if (file.firstLineRemoved)
        {
            currentLine = 1;
        }
        else {
            currentLine = 0;
        }


        int iCurrentSection = Sections::k_None;
        while (NewLinePos != NONPOS) {
            currentLine++;
            NewLinePos = sTemp.find("\n", CurrentPos);
            ProcessLine(sTemp.substr(CurrentPos, NewLinePos - CurrentPos), iCurrentSection);
            CurrentPos = NewLinePos + 1;
        }

        if constexpr (SingleProcessing == true)
        {
            Input::CleanUpAfterFileProcessing();
        }

    }

    
    std::string to_lower(std::string s)
    {
        for (char& c : s)
            c = tolower(c);
        return s;
    }


    Input::File* GetFileByName(std::string_view FileName)
    {
        auto sFileNameLower = to_lower((std::string)FileName);
        for (auto it = Input::files.begin(); it != Input::files.end(); it++) {
            if (to_lower(Iter.name) == sFileNameLower) {
                return &Iter;
            }
        }
        return NULL;
    }


    Input::File* GetFileByID(std::uint32_t ID)
    {

        for (auto it = Input::files.begin(); it != Input::files.end(); it++) {
            if (Iter.ID == ID) {
                return &Iter;
            }
        }
        return NULL;
    }


    int IsFileLoaded(std::string_view FileName)
    {
        auto pFile = GetFileByName(FileName);

        if (pFile)
        {
            return pFile->TimesProcessed;
        }
        return Ext::RTFPErrors::kFileNotLoaded;
    }


    int ProcessFileByID(std::uint32_t ID)
    {
        auto pFile = GetFileByID(ID);

        if (pFile) {
            ProcessFile<true>(*pFile);
            return pFile->TimesProcessed;
        }
        return Ext::RTFPErrors::kFileNotLoaded;
    }



    int ProcessFileByName(std::string FileName)
    {
        auto pFile = GetFileByName(FileName);

        if (pFile) {
            ProcessFile<true>(*pFile);
            return pFile->TimesProcessed;
        }
        return Ext::RTFPErrors::kFileNotLoaded;
    }




    void ProcessAllFiles()
    {
        iFilesProcessed = 0;
        std::sort(files.begin(), files.end(), [](File& a, File& b) -> bool { return a.Priority > b.Priority; });

        for (auto it = files.begin(); it != files.end(); it++) {
            
            ProcessFile<false>(Iter);
        }
        CleanUpAfterFileProcessing();
    }




    void Load()
    {

        #ifdef TestingPlugin
            plf::nanotimer timer;
            timer.start();
        #endif //  TestingPlugin


        if (!f_Does_FolderExist(s_InputFolder)) {
            _MESSAGE("Creating RTFP folder.")
            f_Create_Folders_For_Path(s_InputFolder);
        }

        if (!f_Does_FolderExist(s_InputFolder)) {
            _MESSAGE("RTFP folder doesn't exist - cannot create.");
            return;
        }


        for (const auto& dir_entry : std::filesystem::directory_iterator{ s_InputFolder }) {
            if (!dir_entry.is_directory())
            {
                if (dir_entry.path().extension().string() == ".txt")
                {
                    StoreFile(dir_entry);
                }
                else {
                    auto FileName = dir_entry.path().filename().string();
                    _MESSAGE("File format is not txt>>{}", FileName);
                }
            }
        }

        _MESSAGE("Stored files>>{}", files.size());

        #ifdef TestingPlugin
            _DMESSAGE("File loaded - seconds elapsed>>{}", float(timer.get_elapsed_ms() / 1000));
        #endif //  TestingPlugin

    }

} // namespace Input


namespace Ext
{

    struct PluginData
    {
       std::uint8_t  InterfaceVer = InterfaceVer;
       std::uint32_t Version      = iVersion;
       std::uint32_t VersionBeta  = iVersionBeta;
    };

    PluginData* pPluginDataInst = NULL;

    extern "C" __declspec(dllexport) const PluginData* fn_ext_GetPluginVersionData()
    {
        if (!pPluginDataInst)
        {
            pPluginDataInst = new PluginData;
            _DMESSAGE("Creating plugin data");
        }
       return pPluginDataInst;
    }


    extern "C" __declspec(dllexport) double fn_ext_ProcessFileByID(std::uint32_t ID)
    {
       if (!CritSectionMain.IsInit()) {
            _MESSAGE("Crit section is not initialized!");
            return RTFPErrors::kRTFPNotInitalized;
       }
       else if (bGameReset) {
            return RTFPErrors::kCurrentlyUnavaiable;
       }

       int                        iResult = 0;
       RTFPCriticalSectionVisitor CritSectionVisitor{};
       iResult = Input::ProcessFileByID(ID);
       return iResult;
    }

    extern "C" __declspec(dllexport) double fn_ext_ProcessFileByName(const char* FileName)
    {
       if (!CritSectionMain.IsInit()) {
            _MESSAGE("Crit section is not initialized!");
            return RTFPErrors::kRTFPNotInitalized;
       }
       else if (bGameReset) {
            return RTFPErrors::kCurrentlyUnavaiable;
       }

       int iResult = 0;
       RTFPCriticalSectionVisitor CritSectionVisitor{};
       iResult = Input::ProcessFileByName(FileName);
       return iResult;
    }

    extern "C" __declspec(dllexport) double fn_ext_IsFileLoaded(const char* FileName)
    {
       if (!CritSectionMain.IsInit()) {
            _MESSAGE("Crit section is not initialized!");
            return RTFPErrors::kRTFPNotInitalized;
       }
       else if (bGameReset)
       {
            return RTFPErrors::kCurrentlyUnavaiable;
       }

       int iResult = false;
       RTFPCriticalSectionVisitor CritSectionVisitor{};
       iResult = Input::IsFileLoaded(FileName);
       return iResult;
    }

    extern "C" __declspec(dllexport) double fn_ext_ExecuteLines(const char* contentIn, std::uint32_t Flags)
    {
       _DMESSAGE("Creating file from EXT,flags>>{}", Flags);
       if (!CritSectionMain.IsInit()) {
            _MESSAGE("Crit section is not initialized!");
            return RTFPErrors::kRTFPNotInitalized;
       }
       else if (bGameReset) {
            return RTFPErrors::kCurrentlyUnavaiable;
       }

       std::string sContentTemp = contentIn;

       if (!sContentTemp.length()) {
            _MESSAGE("Length of file is zero.");
            return RTFPErrors::kStringLengthZero;
       }

       RTFPCriticalSectionVisitor CritSectionVisitor{};


       Input::File NewFile;
       NewFile.name    = "TempFile>>" + std::to_string(Input::files.size());

       if (IsFlagSet(Flags, RTFPFlags::kExecuteImmediately)) {
            NewFile.content = std::move(sContentTemp);
            Input::ProcessFile<true>(NewFile);
            return RTFPErrors::kSuccess;
       }
       else {
           if (Input::ProcessMofidiersAndAddNewFileToVector(NewFile, sContentTemp))
           {
                return iFileIDCount - 1; //LastID
           }
           else {
                return RTFPErrors::kFileNotValid;
           }
            
       }

    }

}

