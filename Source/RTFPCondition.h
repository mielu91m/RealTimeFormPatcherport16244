#pragma once

// Current CommonLibSF only ships a stub for TESConditionItem (next pointer + "..."),
// while RTFP needs the full record to build conditions from text.
// Starfield's record follows the same layout as Fallout 4's CONDITION_ITEM_DATA:
//   next            00
//   global/value    08
//   run-on handle   10 (handle + pad)
//   function id     18 (uint16 index into Script::GetScriptCommands)
//   params[2]       20
//   flag bits       30
//   run-on object   31
// The struct here mirrors that layout for 1.16.244 and is validated by the
// static_assert at the bottom.

namespace RTFP
{
    // Values match Starfield's condition "run on" object enum.
    enum CONDITIONITEMOBJECT : std::uint8_t
    {
        kSelf = 0,
        kTarget,
        kRef,
        kCombatTarget,
        kLinkedRef,
        kQuestAlias,
        kPackData,
        kEventData,
        kCommandTarget,
        kEventCameraRef,
        kMyKiller,
        kPlayerShip
    };

    enum CompareOperators : std::uint8_t
    {
        k_EqualTo = 0,
        k_NotEqualTo,
        k_GreaterThan,
        k_GreaterThanEqual,
        kLessThan,
        kLessThanEqual
    };

    union CONDITION_PARAM
    {
        RE::TESForm*         vForm;
        RE::BSFixedString*   vString;
        std::uint32_t        vInt;
        float                vFloat;
    };

    struct TESConditionItem
    {
        TESConditionItem* next;                 // 00
        union
        {
            RE::TESGlobal* global;              // 08
            float          value;
        };
        std::uint32_t     ObjectRefHandle;      // 10
        std::uint32_t     ObjectRefHandlePAD;   // 14
        std::uint16_t     functionID;           // 18
        std::uint8_t      pad1A[6];             // 1A
        CONDITION_PARAM   params[2];            // 20
        std::uint8_t      compareOr : 1;        // 30:0
        std::uint8_t      aliasParams : 1;      // 30:1
        std::uint8_t      valueIsGlobal : 1;    // 30:2
        std::uint8_t      packDataParams : 1;   // 30:3
        std::uint8_t      swapsSubjectAndTarget : 1; // 30:4
        std::uint8_t      compareOperators : 3; // 30:5
        CONDITIONITEMOBJECT object;             // 31
        std::uint8_t      unk0;                 // 32
        std::uint8_t      pad33[5];             // 33
    };
    static_assert(sizeof(TESConditionItem) == 0x38);

    // The SDK type only models `next`; game records use the full layout above.
    inline TESConditionItem* AsRTFP(RE::TESConditionItem* a_item)
    {
        return reinterpret_cast<TESConditionItem*>(a_item);
    }

    inline const TESConditionItem* AsRTFP(const RE::TESConditionItem* a_item)
    {
        return reinterpret_cast<const TESConditionItem*>(a_item);
    }
}
