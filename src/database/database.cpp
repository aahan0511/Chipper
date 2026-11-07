// This file was AI-generated

#include "database.hpp"

#include "../../settings.hpp"

#include "../cli/cli.hpp"

#include <nlohmann/json.hpp>

#include <array>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <set>
#include <string>
#include <vector>


using json = nlohmann::json;


// SHA-1

uint32_t rotl(uint32_t value, int bits) {
    return (value << bits) | (value >> (32 - bits));
}

std::string sha1(const std::vector<uint8_t> &data) {
    uint32_t h[5] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0};

    std::vector<uint8_t> message(data);
    uint64_t bit_length = (uint64_t)data.size() * 8;
    message.push_back(0x80);
    while (message.size() % 64 != 56)
        message.push_back(0x00);
    for (int i = 7; i >= 0; i--)
        message.push_back((bit_length >> (i * 8)) & 0xFF);

    for (size_t chunk = 0; chunk < message.size(); chunk += 64) {
        uint32_t w[80];
        for (int i = 0; i < 16; i++)
            w[i] = (message[chunk + 4 * i] << 24) | (message[chunk + 4 * i + 1] << 16)
                 | (message[chunk + 4 * i + 2] << 8) | message[chunk + 4 * i + 3];
        for (int i = 16; i < 80; i++)
            w[i] = rotl(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);

        uint32_t a = h[0], b = h[1], c = h[2], d = h[3], e = h[4];
        for (int i = 0; i < 80; i++) {
            uint32_t f, k;
            if (i < 20)      { f = (b & c) | (~b & d);          k = 0x5A827999; }
            else if (i < 40) { f = b ^ c ^ d;                   k = 0x6ED9EBA1; }
            else if (i < 60) { f = (b & c) | (b & d) | (c & d); k = 0x8F1BBCDC; }
            else             { f = b ^ c ^ d;                   k = 0xCA62C1D6; }

            uint32_t temp = rotl(a, 5) + f + e + k + w[i];
            e = d;
            d = c;
            c = rotl(b, 30);
            b = a;
            a = temp;
        }

        h[0] += a; h[1] += b; h[2] += c; h[3] += d; h[4] += e;
    }

    char hex[41];
    std::snprintf(hex, sizeof(hex), "%08x%08x%08x%08x%08x", h[0], h[1], h[2], h[3], h[4]);
    return hex;
}


// DOWNLOADING

bool downloadFile(const std::string &name) {
    std::filesystem::path target = DATABASE_DIR / name;
    std::filesystem::path temp = DATABASE_DIR / (name + ".part");

    std::string command = "curl -sfL --max-time " + std::to_string(DATABASE_DOWNLOAD_TIMEOUT)
                        + " -o \"" + temp.string() + "\" \"" + DATABASE_URL + name + "\"";

    if (std::system(command.c_str()) != 0) {
        std::error_code ec;
        std::filesystem::remove(temp, ec);
        return false;
    }

    std::error_code ec;
    std::filesystem::rename(temp, target, ec);
    return !ec;
}

bool loadJSON(const std::string &name, json &out) {
    std::ifstream file(DATABASE_DIR / name);
    if (!file)
        return false;

    out = json::parse(file, nullptr, false);
    return !out.is_discarded();
}


// QUIRKS

const std::set<std::string> COSMIC_PLATFORMS = {"originalChip8", "modernChip8"};
const std::set<std::string> SUPERCHIP_PLATFORMS = {"superchip", "superchip1", "chip48"};

void applyQuirks(const json &quirks) {
    QUIRK_SHIFT                     = quirks.value("shift", QUIRK_SHIFT);
    QUIRK_MEMORY_INCREMENT_BY_X     = quirks.value("memoryIncrementByX", QUIRK_MEMORY_INCREMENT_BY_X);
    QUIRK_MEMORY_LEAVE_I_UNCHANGED  = quirks.value("memoryLeaveIUnchanged", QUIRK_MEMORY_LEAVE_I_UNCHANGED);
    QUIRK_WRAP                      = quirks.value("wrap", QUIRK_WRAP);
    QUIRK_JUMP                      = quirks.value("jump", QUIRK_JUMP);
    QUIRK_VBLANK                    = quirks.value("vblank", QUIRK_VBLANK);
    QUIRK_LOGIC                     = quirks.value("logic", QUIRK_LOGIC);
}

std::string quirksSummary() {
    auto flag = [](const std::string &name, bool value) { return name + "=" + (value ? "on" : "off"); };
    return flag("shift", QUIRK_SHIFT) + " "
         + flag("memoryIncrementByX", QUIRK_MEMORY_INCREMENT_BY_X) + " "
         + flag("memoryLeaveIUnchanged", QUIRK_MEMORY_LEAVE_I_UNCHANGED) + " "
         + flag("wrap", QUIRK_WRAP) + " "
         + flag("jump", QUIRK_JUMP) + " "
         + flag("vblank", QUIRK_VBLANK) + " "
         + flag("logic", QUIRK_LOGIC);
}


void adjustQuirksFromDatabase(const std::vector<uint8_t> &rom) {
    if (!DATABASE_ADJUST_QUIRKS)
        return;

    std::error_code ec;
    std::filesystem::create_directories(DATABASE_DIR, ec);

    const std::array<std::string, 3> files = {"sha1-hashes.json", "programs.json", "platforms.json"};
    info("downloading the CHIP-8 database.");
    for (const std::string &name : files)
        if (!downloadFile(name))
            warning("could not download \"" + name + "\", using the cached copy if there is one.");

    json hashes, programs, platforms;
    if (!loadJSON("sha1-hashes.json", hashes) || !loadJSON("programs.json", programs) || !loadJSON("platforms.json", platforms)) {
        warning("CHIP-8 database is unavailable, using the platform and quirks from settings.hpp.");
        return;
    }

    std::string hash = sha1(rom);
    info("ROM SHA-1: " + hash + ".");

    if (!hashes.contains(hash) || !hashes[hash].is_number_integer()) {
        info("ROM not found in the CHIP-8 database, using the platform and quirks from settings.hpp.");
        return;
    }

    size_t program_index = hashes[hash].get<size_t>();
    if (!programs.is_array() || program_index >= programs.size()) {
        warning("CHIP-8 database is malformed, using the platform and quirks from settings.hpp.");
        return;
    }

    const json &program = programs[program_index];
    const json &rom_entry = program["roms"][hash];
    std::string title = program.value("title", "unknown");

    std::vector<std::string> rom_platforms = rom_entry.value("platforms", std::vector<std::string>{});
    if (rom_entry.contains("quirkyPlatforms"))
        for (auto &[name, _] : rom_entry["quirkyPlatforms"].items())
            rom_platforms.push_back(name);

    if (rom_platforms.empty()) {
        warning("\"" + title + "\" has no platform in the CHIP-8 database, using the platform and quirks from settings.hpp.");
        return;
    }

    std::string platform;
    for (const std::string &candidate : rom_platforms) {
        if (COSMIC_PLATFORMS.contains(candidate) || SUPERCHIP_PLATFORMS.contains(candidate)) {
            platform = candidate;
            break;
        }
    }

    if (platform.empty()) {
        std::string listed;
        for (const std::string &candidate : rom_platforms)
            listed += (listed.empty() ? "" : ", ") + candidate;
        error("\"" + title + "\" is made for " + listed + ", which is not implemented.");
    }

    PLATFORM_COSMIC = COSMIC_PLATFORMS.contains(platform);

    bool platform_found = false;
    for (const json &entry : platforms) {
        if (entry.value("id", "") == platform && entry.contains("quirks")) {
            applyQuirks(entry["quirks"]);
            EXECUTION_TARGET_STEPS = entry.value("defaultTickrate", EXECUTION_TARGET_STEPS);
            platform_found = true;
            break;
        }
    }

    if (rom_entry.contains("quirkyPlatforms") && rom_entry["quirkyPlatforms"].contains(platform)) {
        applyQuirks(rom_entry["quirkyPlatforms"][platform]);
        platform_found = true;
    }

    if (!platform_found) {
        warning("no quirks for \"" + platform + "\" in the CHIP-8 database, using the platform and quirks from settings.hpp.");
        return;
    }

    info("found \"" + title + "\" in the CHIP-8 database, using the " + platform + " platform and quirks.");
    info("quirks: " + quirksSummary() + ".");
    info("tickrate: " + std::to_string(EXECUTION_TARGET_STEPS) + " opcodes per frame.");
}
