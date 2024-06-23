#pragma once

using uint24_t = __uint24;

// Generated with ardugotools on 2024-06-23T15:06:22-04:00

constexpr uint24_t race_stats_table = 0x000000;
constexpr uint24_t role_stats_table = 0x00007E;
constexpr uint24_t weapons_stats_table = 0x000096;
constexpr uint24_t armors_stats_table = 0x0000C6;
constexpr uint24_t helments_stats_table = 0x0000E2;
// Image info for "torch"
constexpr uint24_t torch       = 0x0000F7;
constexpr uint8_t  torchFrames = 2;
constexpr uint16_t torchWidth  = 16;
constexpr uint16_t torchHeight = 16;
// Image info for "tilesheet"
// Raycast frame bytes: 172, mipmap widths: 32,16,8,4
constexpr uint24_t tilesheet       = 0x00017B;
constexpr uint8_t  tilesheetFrames = 9;
constexpr uint24_t test_dungeon = 0x000787;
constexpr uint24_t test_dungeon_offsets = 0x0055AF;
constexpr uint24_t test_dungeon_raycast = 0x0055B3;
constexpr uint24_t test_dungeon_raycast_offsets = 0x00A3DB;

// FX addresses (only really used for initialization)
constexpr uint16_t FX_DATA_PAGE = 0xFF5C;
constexpr uint24_t FX_DATA_BYTES = 41951;

// Helper macro to initialize fx, call in setup()
#define FX_INIT() FX::begin(FX_DATA_PAGE)
