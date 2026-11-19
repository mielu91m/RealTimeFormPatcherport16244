#pragma once

// Bridges between RTFP's original 1.9-era record assumptions and the
// shapes current CommonLibSF exposes for 1.16.244.

namespace RTFP
{
    // ---------------------------------------------------------------- attach parents
    // BGSAttachParentArray is BaseFormComponent (vtable at 0) followed by a
    // BSTHeapSTLVector<BGSKeyword*> (begin / end / capacity-end triplet at 0x08).
    // The pre-1.10 SDK exposed those three pointers directly as
    // firstEntry / lastEntry / lastEntry2, which is what RTFP's save/restore
    // logic expects.
    using AttachKeywordArray = RE::BGSTypedKeywordValueArray<RE::KeywordType::kAttachPoint>;

    struct KeywordTriplet
    {
        void* begin;        // 00
        void* end;          // 08
        void* capacityEnd;  // 10
    };
    static_assert(sizeof(KeywordTriplet) == 0x18);

    inline AttachKeywordArray& AttachKeywords(RE::BGSAttachParentArray& a_array)
    {
        return a_array;
    }

    inline KeywordTriplet& Triplet(AttachKeywordArray& a_array)
    {
        return *reinterpret_cast<KeywordTriplet*>(&a_array);
    }

    // ---------------------------------------------------------------- weapon ammo
    // 1.16 SDK leaves 0x20..0x28 unnamed (pad_0028). Earlier SFSE headers exposed
    // that slot as a second ammo form pointer, which RTFP's "Weapon ammo list"
    // modifier writes to.
    struct WeaponAmmoDataExtra
    {
        std::uint8_t pad00[0x18];  // 00
        RE::TESAmmo* ammo;         // 18
        RE::TESAmmo* ammoList;     // 20
    };
    static_assert(offsetof(WeaponAmmoDataExtra, ammo) == 0x18);
    static_assert(offsetof(WeaponAmmoDataExtra, ammoList) == 0x20);

    inline WeaponAmmoDataExtra* Extra(RE::WeaponAmmoData* a_data)
    {
        return reinterpret_cast<WeaponAmmoDataExtra*>(a_data);
    }
}
