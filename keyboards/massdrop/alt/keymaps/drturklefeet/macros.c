enum alt_keycodes {
    U_T_AUTO = SAFE_RANGE, //USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,              //USB Toggle Automatic GCR control
    DBG_TOG,               //DEBUG Toggle On / Off
    DBG_MTRX,              //DEBUG Toggle Matrix Prints
    DBG_KBD,               //DEBUG Toggle Keyboard Prints
    DBG_MOU,               //DEBUG Toggle Mouse Prints
    MD_BOOT,               //Restart into bootloader after hold timeout
    ACEIDM,
    BENZO,
    BETAB,
    COA,
    GLIM,
    HFACEI,
    LOPID,
    STATIN,
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
};

#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL  (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_ALT  (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {

        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;

        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;

        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;

        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;

        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;

        case RGB_TOG:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL: {
                        rgb_matrix_set_flags(LED_FLAG_KEYLIGHT);
                        rgb_matrix_set_color_all(0, 0, 0);
                    }
                    break;
                case LED_FLAG_KEYLIGHT: {
                    rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                    rgb_matrix_set_color_all(0, 0, 0);
                    }
                    break;
                case LED_FLAG_UNDERGLOW: {
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_disable_noeeprom();
                    }
                    break;
                default: {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable_noeeprom();
                    }
                    break;
                }
            }
            return false;

        case ACEIDM:
            if (record->event.pressed) {
                // when keycode ACEIDM is pressed
                SEND_STRING("Your patient has a diagnosis of diabetes and hypertension and is not taking an ACEI, ARB, or renin inhibitor. Please evaluate whether the following medications would be appropriate for this patient: benazepril 5mg, enalapril 2.5mg, lisinopril 5mg, or losartan 25mg (if contraindication to an ACEi)");
            } else {
                // when keycode ACEIDM is released
            }
            break;

        case BENZO:
            if (record->event.pressed) {
                // when keycode BENZO is pressed
                SEND_STRING("During a comprehensive medication review, your patient listed __________ as a current medication. Older adults experience an increased sensitivity to benzodiazepines, as well as decreased metabolism of long acting agents. The American Geriatric Society recommends avoiding benzodiazepines in adults 65 years and older due to an increased risk of cognitive impairment, delirium, falls, fractures, and motor vehicle crashes in older adults. Please evaluate current therapy and consider discontinuation of __________. Thank you. [Ref: AGS Beers Criteria. J Am Geriatr Soc 67:674–694, 2019.]");
            } else {
                // when keycode BENZO is released
            }
            break;

        case BETAB:
            if (record->event.pressed) {
                // when keycode BETAB is pressed
                SEND_STRING("The use of 1 of the 3 beta blockers proven to reduce mortality (bisoprolol, carvedilol, and sustained-released metoprolol succinate) is recommended for all patients with current or prior symptoms of Heart Failure, unless contraindicated, to reduce morbidity and mortality. Ref: 2013 ACCF/AHA Guideline for the Management of Heart Failure. (Available at https://circ.ahajournals.org/content/128/16/e240.full.pdf+html) Consider adding the appropriate beta blocker therapy for this patient. The use of one of the three beta blockers proven to reduce mortality (bisoprolol, carvedilol, and sustained-released metoprolol succinate) is recommended for all patients with HFrEF and current or prior symptoms of Heart Failure, unless contraindicated, to reduce morbidity and mortality. (Level Reference A, Ref: 2017 ACC/AHA/HFSA Focused Update of the 2013 ACCF/AHA Guidelines)");
            } else {
                // when keycode BETAB is released
            }
            break;

        case COA:
            if (record->event.pressed) {
                // when keycode COA is pressed
                SEND_STRING("On a scale of 1-10, 10 being the most pain, patient reports: ____.\n");
                SEND_STRING("Patient may need additional functional screening if _______.\n");
                SEND_STRING("Patient reports having the following items in their Advanced Care Plan:\n");
                SEND_STRING("___ Advanced Directive\n");
                SEND_STRING("___ Actionable Medical Orders\n");
                SEND_STRING("___ Living Will\n");
                SEND_STRING("___ Surrogate Decision Maker\n");
                SEND_STRING("Please discuss advanced care plans with your patient. Some examples include: Advanced Directive, Actionable Medical Orders, Living Will, and Surrogate Decision Maker.");
            } else {
                // when keycode COA is released
            }
            break;

        case GLIM:
            if (record->event.pressed) {
                // when keycode GLIM is pressed
                SEND_STRING("Patient has reported outling blood glucose data that may forgo current goal criteria. Last known Blood sugar was _____ with an average of about ____ most weeks. Please consider additonal therapy review and education regarding goals at this time if this is relevant for this patient. During a comprehensive medication review, your patient listed _____ as a current medication for diabetes. Glyburide and Glimepiride are on the Beer's list and are considered potentially dangerous for use in patients over the age of 65 due to an increased risk of severe prolonged hypoglycemia. Please evaluate current sulfonylurea therapy and consider discontinuation or switching to glipizide if appropriate. Thank you.");
            } else {
                // when keycode GLIM is released
            }
            break;

        case HFACEI:
            if (record->event.pressed) {
                // when keycode HFACEI is pressed
                SEND_STRING("Heart Failure - Starting an ACEI or ARB to prevent worsening symptoms. Angiotensin-converting enzyme inhibitors are recommended for all patients with current or prior symptoms of HF and reduced LVEF, unless contraindicated. Angiotensin II receptor blockers  are recommended who are ACE inhibitor-intolerant.  (Ref: 2013 ACCF/AHA Guideline for the Management of Heart Failure. Available at https://circ.ahajournals.org/content/128/16/e240.full.pdf+html.) Consider adding the appropriate ACEI or ARB therapy for this patient. Use of an ACEI or ARB is recommended for all patients with HFrEF and current or prior symptoms, unless contraindicated, to reduce morbidity and mortality. (Level Evidence A, Ref: 2017 ACC/AHA/HFSA Focused Update of the 2013 ACCF/AHA Guidelines");
            } else {
                // when keycode HFACEI is released
            }
            break;

        case LOPID:
            if (record->event.pressed) {
                // when keycode LOPID is pressed
                SEND_STRING("During a comprehensive medication review, your patient noted gemfibrozil and _______ as current medications. Gemfibrozil can increase the serum concentrations of statins by the inhibition of OATP1B1; coadministration is recommended to be avoided. Using gemfibrozil and statins in combination can increase the risk of myopathy and rhabdomyolysis. Please review therapy and use caution if these medication must be used together. Thank you. [Ref: Rhabdomyolysis with HMG CoA reductase inhibitors and gemfibrozil combination therapy. DOI: 10.1002/pds.977]");
            } else {
                // when keycode LOPID is released
            }
            break;

        case STATIN:
            if (record->event.pressed) {
                // when keycode STATIN is pressed
                SEND_STRING("Statin therapy should be added to lifestyle therapy, regardless of baseline lipid levels, for diabetic patients who are over the age of 40 years. (Ref: Diabetes Care. 2014. ADA. Volume 37, Supplement 1, January 2014. Available at: http://care.diabetesjournals.org/content/37/Supplement_1/S14.full.pdf+html) Consider adding appropriate statin therapy for this patient. [Statin therapy is recommended for diabetic patients age 40 and older, regardless of baseline lipid levels. Ref. 2018 ACC/AHA Cholesterol Clinical Practice Guidelines]. Medical claims have identified this patient as having hyperlipidemia. Consider adding the appropriate cholesterol-lowering therapy for this patient. [Ref: 2013 ACC/AHA Blood Cholesterol Guidelines]");
            } else {
                // when keycode STATIN is released
            }
            break;
    }
    return true;
};
