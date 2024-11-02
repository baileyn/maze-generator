#include "Logging.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Pz::Core
{

std::shared_ptr<spdlog::logger> Logger::coreLogger = nullptr;
std::shared_ptr<spdlog::logger> Logger::clientLogger = nullptr;

void Logger::init(std::string_view name)
{
    spdlog::set_pattern("%^[%T] %n: %v%$");

    coreLogger = spdlog::stdout_color_mt("PzEngine");
    clientLogger = spdlog::stdout_color_mt(name.data());
}

} // namespace Pz::Core
