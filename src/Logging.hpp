#pragma once

#include <spdlog/spdlog.h>

#define LOG_ERROR(message, ...) spdlog::error("[ERROR] " message, __VA_ARGS__)
#define LOG_WARNING(message, ...) spdlog::warn("[WARNING] " message, __VA_ARGS__)
#define LOG_INFO(message, ...) spdlog::info("[INFO] " message, __VA_ARGS__)
#define LOG_DEBUG(message, ...) spdlog::debug("[DEBUG] " message, __VA_ARGS__)
#define LOG_TRACE(message, ...) spdlog::trace("[TRACE] " message, __VA_ARGS__)