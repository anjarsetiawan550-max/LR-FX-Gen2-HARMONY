cmake_minimum_required(VERSION 3.22)

project(ReverbFX VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.13" CACHE STRING "Minimum macOS version")

include(FetchContent)
FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG        8.0.6
    GIT_SHALLOW    ON
)
FetchContent_MakeAvailable(JUCE)

# ---- Aset GUI (PNG) disematkan ke dalam plugin sebagai BinaryData ----
juce_add_binary_data(ReverbFXAssets
    SOURCES
        Assets/background_panel.png
        Assets/lcd_bezel.png
        Assets/lcd_screen_bg.png
        Assets/lcd_glass_overlay.png
        Assets/beat_red_on.png
        Assets/beat_red_off.png
        Assets/beat_green_on.png
        Assets/beat_green_off.png
        Assets/knob_large_strip_64f.png
        Assets/knob_small_strip_64f.png
        Assets/btn_down_up.png
        Assets/btn_down_down.png
        Assets/btn_up_up.png
        Assets/btn_up_down.png
        Assets/btn_utility_up.png
        Assets/btn_utility_down.png
        Assets/btn_menu_up.png
        Assets/btn_menu_down.png
        Assets/btn_exit_up.png
        Assets/btn_exit_down.png
        Assets/btn_store_up.png
        Assets/btn_store_down.png
        Assets/btn_tap_up.png
        Assets/btn_tap_down.png
        Assets/btn_tap_led_glow.png
)

# ---- Plugin: Standalone + VST3 ----
juce_add_plugin(ReverbFX
    COMPANY_NAME            "ReverbFX"
    PLUGIN_MANUFACTURER_CODE Rvfx
    PLUGIN_CODE             Rvb1
    FORMATS                 Standalone VST3
    PLUGIN_NAME             "LR FX Gen 2"
    PRODUCT_NAME            "LR FX Gen 2"
    IS_SYNTH                FALSE
    NEEDS_MIDI_INPUT        FALSE
    NEEDS_MIDI_OUTPUT       FALSE
    IS_MIDI_EFFECT          FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE
    COPY_PLUGIN_AFTER_BUILD FALSE
    VST3_CATEGORIES         Fx Reverb
)

# Windows Standalone .exe icon (same LR logo as LR PRO FX)
if (WIN32)
    target_sources(ReverbFX_Standalone PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Assets/Logo/r_plugin_icon.rc")
endif()

target_sources(ReverbFX PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginEditor.cpp
)

target_compile_definitions(ReverbFX PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_STRICT_REFCOUNTEDPOINTER=1
)

target_link_libraries(ReverbFX
    PRIVATE
        ReverbFXAssets
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
)
