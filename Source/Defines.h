#pragma once

#define iBadPluginindex 255
#define iMaxCharCountForValues 255
#define iMaxLVLListCount 255
#define iFlagResultBadFlag 0

#define sSkipLineSymbol          '#'
#define sSearchForMultipleForms  '+'
#define sSearchForFilters        '^'
#define sSearchForAllFormsSymbol '*'
#define sNULLForm             "~"
#define sSectionDelimeter     '|'
#define sValueDelimeterLeft      '('
#define sValueDelimeterRight     ')'
#define sFilterDelimeter      '+'
#define sFormIDDelimeter      '~'
#define sPropertiesDelimeter     ':'
#define sArrDelimeter         ','
#define sParametersDelimeter  '_'
#define sQuotes     '"'

#define NONPOS                std::string_view::npos

#define sValueDamage   "dmg"_sh
#define sValueCapacity "cap"_sh
#define sValueName     "name"_sh
#define sValueModel "model"_sh

#define sValueValue     "val"_sh
#define sValueWeight    "weight"_sh
#define sValueFlagSet   "set_flag"_sh
#define sValueFlagUnset "uns_flag"_sh

#define sAttachParentsArrayAdd "add_APPR"_sh
#define sAttachParentsArrayRemove "rmv_APPR"_sh
#define sAttachParentsArrayReplace "rpl_APPR"_sh
#define sAttachParentsArrayClear "clr_APPR"_sh

//AMMO
#define sValueAmmoProjectile "proj"_sh
#define sFiltersAmmoByWeapon "ammo_in_weap"_sh


//WEAPON
#define sValueWeapAmmo "ammo"_sh
#define sValueWeapAmmoList "ammo_list"_sh
#define sFiltersWeaponByAmmo "weap_by_ammo"_sh

#define sValueWeaponDamage   "dam"_sh
#define sValueWeaponDamageRangeMin "rng_min"_sh
#define sValueWeaponDamageRangeMax "rng_max"_sh
#define sValueWeaponDamageOutOfRangeDamageMult "out_of_rng_dmg_mult"_sh


#define sValueWeaponCapacity "cap"_sh
#define sValueWeaponCritDamageMult "crit_dam_mult"_sh
#define sValueWeaponCritChanceIncMult "crit_ch_inc_mult"_sh

#define sValueWeaponFiringAttackSeconds "atk_sec"_sh
#define sValueWeaponFiringAttackDelaySeconds "atk_del_sec"_sh
#define sValueWeaponFiringShotsPerSecond "shot_per_sec"_sh
#define sValueWeaponFiringOverrideRateOfFire    "over_rate_fire"_sh

#define sValueWeaponAttackOxygenCost "atk_ox_cost"_sh
#define sValueWeaponAttackBaseWeight   "weight"_sh
#define sValueWeaponAttackBaseValue   "val"_sh
#define sValueWeaponAttackBaseSpeed   "base_speed"_sh
#define sValueWeaponAttackReloadSpeed    "reload_speed"_sh
#define sValueWeaponAttackBashDamage   "bash_dam"_sh


#define sValueWeaponDamageTypeAdd     "add_dmgt"_sh
#define sValueWeaponDamageTypeRemove  "rmv_dmgt"_sh
#define sValueWeaponDamageTypeReplace "rpl_dmgt"_sh
#define sValueWeaponDamageTypeClear   "clr_dmgt"_sh


#define sWeaponFlagNonPlayable "non_play"_sh
#define sWeaponFlagPlayerOnly "pc_only"_sh
#define sWeaponFlagCantDrop  "cnt_drp"_sh
#define sWeaponFlagMinorCrime "mnr_cri"_sh
#define sWeaponFlagNonHostile  "non_hst"_sh

//PROJECTILE
#define sValueProjGravity             "grav"_sh
#define sValueProjSpeed               "speed"_sh
#define sValueProjRange               "range"_sh
#define sValueProjExplosionProximity  "expl_prox"_sh
#define sValueProjExplosionTimer      "expl_timer"_sh
#define sValueProjMuzzleFlashDuration "muzz_fldur"_sh
#define sValueProjFadeDuration         "fdout_dur"_sh
#define sValueProjImpactForce         "imp_force"_sh
#define sValueProjConeSpread          "cone_spr"_sh
#define sValueProjCollisionRadius     "coll_rad"_sh // Seems to be reset by 0 by the game or SFEdit glitches.
#define sValueProjLifetime            "lifetime"_sh
#define sValueProjRelaunchInterval    "rel_int"_sh
#define sFiltersProjectileInAmmo      "proj_in_ammo"_sh
#define sFiltersProjectileNotInAmmo       "proj_not_in_ammo"_sh

//NPC
#define sFiltersNPCHasRace "of_race"_sh
#define sFiltersNPCHasNotRace "not_of_race"_sh

#define sFiltersNPCHasActorBaseFlagSet "is_flag_ab_set"_sh
#define sFiltersNPCHasNotActorBaseFlagSet  "is_flag_ab_uns"_sh

#define sFiltersNPCHasActorBaseFlagSetAny    "is_flag_ab_set_any"_sh
#define sFiltersNPCHasNotActorBaseFlagSetAny "is_flag_ab_uns_any"_sh


#define sValueNPCDeathItem "death_item"_sh
#define sValueNPCLegendChance "legn_chance"_sh

#define sValueNPCXPValueOffset "xp_val_offs"_sh
#define sValueNPCXPLevel "lvl"_sh
#define sValueNPCCalcMinLevel "calc_min_lvl"_sh
#define sValueNPCCalcMaxLevel     "calc_max_lvl"_sh
#define sValueNPCDispositionBase     "disp_base"_sh
#define sValueNPCDefaultOutfit  "def_outfit"_sh
#define sValueNPCSleepOutfit       "spc_outfit"_sh
#define sValueNPCCrimeFaction        "crm_fact"_sh
#define sValueNPCHeightMin       "hgt_min"_sh
#define sValueNPCHeightMax          "hgt_max"_sh

#define sValueNPCWeightThin "wgt_thn"_sh
#define sValueNPCWeightMuscular "wgt_msc"_sh
#define sValueNPCWeightFat "wgt_fat"_sh
#define sValueNPCShortName      "short_name"_sh


#define sValueHeadPartsAdd "add_hdpt"_sh
#define sValueHeadPartsRemove "rmv_hdpt"_sh
#define sValueHeadPartsReplace "rpl_hdpt"_sh
#define sValueHeadPartsClear "clr_hdpt"_sh

#define sValueFactionsAdd     "add_fact"_sh
#define sValueFactionsRemove   "rmv_fact"_sh
#define sValueFactionsReplace "rpl_fact"_sh
#define sValueFactionsClear    "clr_fact"_sh


#define sValueNPCFlagActorBaseSet          "set_flag_ab"_sh
#define sValueNPCFlagActporBaseUnset        "uns_flag_ab"_sh
#define sActorFlagFemale        "female"_sh
#define sActorFlagEssential "essential"_sh
#define sActorFlagIsChargenFacePreset "is_chrg_face_preset"_sh
#define sActorFlagRespawn "respawn"_sh
#define sActorFlagAutoCalcStats "autoCalcStats"_sh
#define sActorFlagUnique "unique"_sh
#define sActorFlagDoesntAffectStealthMeter "doesn_aff_stlt_mtr"_sh
#define sActorFlagPCLevelMult             "pc_level_mult"_sh
#define sActorFlagProtected "protected"_sh
#define sActorFlagSummonable               "summonable"_sh
#define sActorFlagDoesntBleed "doesn_bleed"_sh
#define sActorFlagBleedoutOverride         "bleed_over"_sh
#define sActorFlagOppositeGenderAnims "oppos_gnd_ani"_sh
#define sActorFlagSimpleActor      "simpl_act"_sh
#define sActorFlagIsGhost      "is_ghst"_sh
#define sActorFlagInvulnerable             "invuln"_sh

#define sActorPerkAdd "add_perk"_sh
#define sActorPerkRemove "rmv_perk"_sh
#define sActorPerkReplace "rpl_perk"_sh
#define sActorPerkClearPerkArray "clr_perk"_sh

//Constructible
#define sValueConstructibleWorkbenchKeyword "wrkbench_kwd"_sh
#define sValueConstructibleCreatedObject "created_obj"_sh
#define sValueConstructibleBuildLimit   "build_lmt"_sh
#define sValueConstructibleCategory       "cat"_sh
#define sValueConstructibleMenuSortOder            "menu_srt_ord"_sh
#define sValueConstructibleComponentAdd        "add_comp"_sh
#define sValueConstructibleComponentRemove     "rmv_comp"_sh
#define sValueConstructibleComponentReplace        "rpl_comp"_sh
#define sValueConstructibleComponentClear   "clr_comp"_sh


#define sFiltersConstructibleHasWorkBenchKeyword "has_wrkbench_kwd"_sh
#define sFiltersConstructibleHasNotWorkBenchKeyword "has_not_wrkbench_kwd"_sh


//Activator
#define sValueActivatorWaterForm "water"_sh

//Perk
#define sValuePerkTrainingPerk "train_perk"_sh
#define sValuePerkIcon "icon"_sh
#define sValuePerkRestriction         "restriction"_sh

//Spell
#define sValueSpellType "type"_sh
#define sValueSpellChargeTime        "chrg_time"_sh
#define sValueSpellCastingType "cast_type"_sh
#define sValueSpellTargetType       "trg_type"_sh
#define sValueSpellCastDuration        "cast_dur"_sh
#define sValueSpellRange      "range"_sh
#define sValueSpellCastingPerk       "cast_perk"_sh
#define sValueSpellEffectAdd "add_effect"_sh
#define sValueSpellEffectRemove "rmv_effect"_sh
#define sValueSpellEffectReplace "rpl_effect"_sh
#define sValueSpellEffectClear "clr_effect"_sh

//AVMData
#define sAVMDataValueType "type"_sh
#define sAVMDataEntryAdd  "add_entr"_sh
#define sAVMDataEntryRemove  "rmv_entr"_sh
#define sAVMDataEntryReplace  "rpl_entr"_sh
#define sAVMDataEntryClear  "clr_entr"_sh


//Race
#define sRaceMaleHeight "m_hgt"_sh
#define sRaceFeMaleHeight "f_hgt"_sh
#define sRaceMaleWeightThin   "m_wgt_thn"_sh
#define sRaceMaleWeightMuscular   "m_wgt_msc"_sh
#define sRaceMaleWeightFat   "m_wgt_fat"_sh
#define sRaceFeMaleWeightThin   "f_wgt_thn"_sh
#define sRaceFeMaleWeightMuscular   "f_wgt_msc"_sh
#define sRaceFeMaleWeightFat   "f_wgt_fat"_sh


//Static


//Cell
#define sCellFlagCanFastTravel "can_fst_trvl"_sh
#define sCellFlagPublic  "public"_sh
//#define sLCellUsePlanetGravity "use_plnt_grav"_sh


//ConditionForm
#define sConditionFormAddEntryFrom "add_entry_from"_sh


// Voice type
#define sVoiceTypeAnimFaceArchetype "anim_face_archetype"_sh


//StoryManagerQuestNode 
#define sStoryManagerQuestNodeMaxConcurringQuests "max_concur_qsts"_sh
#define sStoryManagerQuestNodeHoursUntillReset "hrs_untl_rst"_sh
#define sStoryManagerQuestNodeNumQuestsToRun    "num_qsts_to_run"_sh
#define sStoryManagerQuestNodePreviousSibling      "prev_siblng"_sh

#define sStoryManagerQuestNodeEntryAdd            "add_entr"_sh
#define sStoryManagerQuestNodeEntryRemove         "rmv_entr"_sh
#define sStoryManagerQuestNodeEntryReplace        "rpl_entr"_sh
#define sStoryManagerQuestNodeEntryInsert        "ins_entr"_sh
#define sStoryManagerQuestNodeEntryClear          "clr_entr"_sh


//Message
#define sMessageOwnerQuest              "own_qst"_sh
#define sMessageDisplayTime             "dspl_time"_sh

#define sMessageAddButton "add_but"_sh

#define sMessageFlagMessageBox          "msg_box"_sh
#define sMessageFlagDelayInitialDisplay "delay_init_dspl"_sh

//Ingestible
#define sIngestibleAddictionItem "addict_spell"_sh
#define sIngestibleAddictionChance "addict_chance"_sh

#define sIngestibleFlagNoAutoCalc "no_auto_calc"_sh
#define sIngestibleFlagFoodItem    "food_item"_sh
#define sIngestibleFlagMedicine    "medicine"_sh
#define sIngestibleFlagPoison    "poison"_sh

// Container
#define sContainerItemAdd     "item_add"_sh
#define sContainerItemRemove "item_rmv"_sh
#define sContainerItemReplace "item_rpl"_sh
#define sContainerItemClear    "item_clr"_sh
#define sContainerValueDisplayFilter   "dspl_flt"_sh



//PlanetContentManagerBranchNode
#define sPCBNNodeAdd     "node_add"_sh
#define sPCBNNodeRemove       "node_rmv"_sh
#define sPCBNNodeReplace    "node_rpl"_sh
#define sPCBNNodeClear        "node_clr"_sh

// LoadScreen
#define sLoadScreenTexture "load_screen"_sh
#define sLoadScreenDescription "descr"_sh



//Conditions
#define sCondidtionAddToForm "cnd_add"_sh


// Reference
#define sRefPosX "pos_x"_sh
#define sRefPosY "pos_y"_sh
#define sRefPosZ "pos_z"_sh

#define sRefRotX "rot_x"_sh
#define sRefRotY "rot_y"_sh
#define sRefRotZ "rot_z"_sh

#define sRefScale "scale"_sh

#define sRefSetFlag "set_flag"_sh
#define sRefUnSetFlag "uns_flag"_sh


//OMOD
#define sIncludeAdd     "incl_add"_sh
#define sIncludeRemove  "incl_rmv"_sh
#define sIncludeReplace "incl_rpl"_sh
#define sIncludeClear   "incl_clr"_sh

//Terminal
#define sTerminalValueTerminalMenu "tmlm"_sh


//Magic item
#define sMagicItemFlagHostile "hostile"_sh
#define sMagicItemFlagRecover "recover"_sh
#define sMagicItemFlagDetrimental "detrimental"_sh
#define sMagicItemFlagSnapToNavMesh "snap_to_nvmesh"_sh
#define sMagicItemFlagNoHitEvent    "no_hit_evn"_sh
#define sMagicItemDispelWithKeywords "disp_wth_keyw"_sh
#define sMagicItemNoDuration         "no_dur"_sh
#define sMagicItemNoMagnitude        "no_magn"_sh
#define sMagicItemNoArea        "no_area"_sh
#define sMagicItemFXPersist           "fx_persist"_sh
#define sMagicItemGoryVisuals        "gory_vis"_sh
#define sMagicItemHideInUI        "hid_in_ui"_sh
#define sMagicItemNoRecast        "no_recast"_sh
#define sMagicItemPowerAffectsMagnitude "pwr_aff_magn"_sh
#define sMagicItemPowerAffectsDuration "pwr_aff_dur"_sh
#define sMagicItemPainless "painless"_sh
#define sMagicNoHitEffect  "no_hit_eff"_sh
#define sMagicNoDeathDispel "no_dth_disp"_sh


//LeveledLists
#define sLVLListArrayAdd        "add"_sh
#define sLVLListArrayRemove     "rmv"_sh
#define sLVLListArrayInsert     "ins"_sh
#define sLVLListArrayReplace     "rpl"_sh
#define sLVLListArrayDontSort       "dontsort"_sh
#define sLVLListChanceGlobal    "global"_sh

#define sLVLListFlagCalculateFromAllLevels "calc_from_all_levels"_sh
#define sLVLListFlagCalculateForEachItem   "calc_for_each_item"_sh
#define sLVLListFlagCalculateAll           "calc_all"_sh

#define sLVLListCondidtionAddToEntry "cnd_add_to_entr"_sh

#define sKWDArrayAdd     "kwd_add"_sh
#define sKWDArrayRemove  "kwd_rmv"_sh
#define sKWDArrayReplace "kwd_rpl"_sh
#define sKWDArrayClear   "kwd_clr"_sh


#define sPropertyAdd     "prop_add"_sh
#define sPropertyRemove  "prop_rmv"_sh
#define sPropertyReplace "prop_rpl"_sh
#define sPropertyClear   "prop_clr"_sh



#define sFormListAdd     "add"_sh
#define sFormListRemove  "rmv"_sh
#define sFormListReplace "rpl"_sh
#define sFormListClear   "clr"_sh

// #define sFiltersFormIDInclude "formid_incl"_sh
#define sFiltersFormIDExclude     "formid_excl"_sh
#define sFiltersFormPluginInclude "plugin_incl"_sh
#define sFiltersFormPluginExclude "plugin_excl"_sh
#define sFiltersFormlistInclude "frml_incl"_sh
#define sFiltersFormlistExclude "frml_excl"_sh

#define sFiltersKeywordInclude    "keyw_incl"_sh
#define sFiltersKeywordIncludeAny "keyw_incl_any"_sh
#define sFiltersKeywordExclude    "keyw_excl"_sh
#define sFiltersKeywordExcludeAny "keyw_excl_any"_sh

#define sFilterByWeight "flt_weight"_sh
#define sFilterByValue "flt_value"_sh

#define sFilterByFlagSet "is_flag_set"_sh
#define sFilterByFlagNotSet "is_flag_uns"_sh
#define sFilterByFlagSetAny    "is_flag_set_any"_sh
#define sFilterByFlagNotSetAny "is_flag_uns_any"_sh


#define sAdd  '+'
#define sSub  '-'
#define sMult '*'
#define sDiv  '/'


#define sFilterEqual  '='
#define sFilterNotEqual   '!'
#define sFilterLarger '>'
#define sFilterLesser  '<'


#define SwitchAddKeywordsCases                                                                                                                                                     \
    case sKWDArrayAdd:                                                                                                                                                             \
        KeywordsArray::AddRemoveKeywordInArray(CurrentForm->keywords, CurrentModifierValue, KeywordsArray::AddKeywordToArray);                                                     \
        break;                                                                                                                                                                     \
    case sKWDArrayRemove:                                                                                                                                                          \
        KeywordsArray::AddRemoveKeywordInArray(CurrentForm->keywords, CurrentModifierValue, KeywordsArray::RemoveKeywordFromArray);                                                \
        break;                                                                                                                                                                     \
    case sKWDArrayReplace:                                                                                                                                                         \
        KeywordsArray::ReplaceKeywordInArray(CurrentForm->keywords, CurrentModifierValue);                                                                                         \
        break;                                                                                                                                                                     \
    case sKWDArrayClear:                                                                                                                                                           \
        CurrentForm->keywords.clear();                                                                                                                                             \
        break;

#define SwitchAddValueCase                                                                                                                                                         \
    case sValueValue:                                                                                                                                                              \
        ApplyMemberNumberMofidier(CurrentModifierValue, CurrentForm->value);                                                                                                        \
        break;

#define SwitchAddWeightCase                                                                                                                                                        \
    case sValueWeight:                                                                                                                                                             \
        ApplyMemberNumberMofidier(CurrentModifierValue, CurrentForm->weight);                                                                                                       \
        break;

#define _ApplyMemberNumberMofidier(...)                                                                                                                                             \
    ApplyMemberNumberMofidier(CurrentModifierValue, __VA_ARGS__);                                                                                                                   \
    break;


#define SwitchAddModelCase                                                                                                                                                         \
    case sValueModel:                                                                                                                                                              \
        SFString::Set(CurrentForm->model, CurrentModifierValue);                                                                                                        \
        break;


#define SetFloatMofidier(CurrentValue, Value)  CurrentValue = Value;
#define AddFloatMofidier(CurrentValue, Value)  CurrentValue = CurrentValue + Value;
#define SubFloatMofidier(CurrentValue, Value)  CurrentValue = CurrentValue - Value;
#define MultFloatMofidier(CurrentValue, Value) CurrentValue = CurrentValue * Value;
#define DivFloatMofidier(CurrentValue, Value)  CurrentValue = CurrentValue / Value;


#define SetSFString(CurrentValue) SFString::Set(CurrentValue, CurrentModifierValue);break;

#define SwitchAddFullnameSet                                                                                                                                                       \
    case sValueName:                                                                                                                                                               \
        SetSFString(CurrentForm->fullName);                                                                                                                                          \

#define _SetFormFromModifier(CurrentValue)                                                                                                                            \
    SetFormFromModifier(CurrentValue, CurrentModifierValue, const_GetTypeFromFormType<decltype(CurrentValue)>());                                                                      \
    break;

#define _SetFormFromModifierDontCheckForCategory(CurrentValue)                                                                                                                                         \
    SetFormFromModifierDontCheckForCategory(CurrentValue, CurrentModifierValue);                                                                  \
    break;



//

#define SwitchAddProperties  \
case sPropertyAdd:\
ArrayNonForm::_AddRemoveInsert(CurrentForm->properties, CurrentModifierValue, ArrayNonForm::Add<RE::BSTArray<PROPERTY>*, Properties::EntryFromString::Data>,\
                               Properties::GetFromString<false, float>);\
break;\
\
case sPropertyRemove:\
if (CurrentForm->properties) {\
    ArrayNonForm::_AddRemoveInsert(CurrentForm->properties, CurrentModifierValue, ArrayNonForm::Remove<RE::BSTArray<PROPERTY>*, Properties::EntryFromString::Data>,\
                                   Properties::GetFromString<false, float>);\
}\
else {\
    _DMESSAGE("Components array in {:08X} doesn't exist for item to be removed.", CurrentForm->formID);\
}\
\
break;\
\
case sPropertyReplace:\
if (CurrentForm->properties) {\
    ArrayNonForm::_ReplaceInArray(CurrentForm->properties, CurrentModifierValue, ArrayNonForm::Replace<RE::BSTArray<PROPERTY>*, Properties::EntryFromString::Data>,\
                                  Properties::GetFromString<false, float>);\
}\
\
break;\
\
case sPropertyClear:\
if (CurrentForm->properties) {\
    ArrayNonForm::_Clear(CurrentForm->properties);\
}\
else {\
    _DMESSAGE("Property array in {:08X} doesn't exist to be cleared.", CurrentForm->formID);\
}\
\
break;\

#define _SetOrRemoveFlag(CurrentFlag,FunctionToGet)                                                                                                                                                       \
    case CurrentFlag:                                                                                                                                                               \
        SetOrRemoveFlagAlt<bSet>(Flags, CONSTEVAL(FunctionToGet(CurrentFlag)));                                                                                                            \
        break;                                                                                                                                                                      \
                                                                                                                                                                                     \
