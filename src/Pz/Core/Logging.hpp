#pragma once

#include <spdlog/spdlog.h>
#include <string_view>

namespace Pz::Core
{

class Logger
{
  public:
    static void init(std::string_view name = "Pz");

    static std::shared_ptr<spdlog::logger> &getCoreLogger()
    {
        return coreLogger;
    }

    static std::shared_ptr<spdlog::logger> &getClientLogger()
    {
        return clientLogger;
    }

  private:
    static std::shared_ptr<spdlog::logger> coreLogger;
    static std::shared_ptr<spdlog::logger> clientLogger;
};

#define PZ_CORE_TRACE(...) ::Pz::Core::Logger::getCoreLogger()->trace(__VA_ARGS__)
#define PZ_CORE_DEBUG(...) ::Pz::Core::Logger::getCoreLogger()->debug(__VA_ARGS__)
#define PZ_CORE_INFO(...) ::Pz::Core::Logger::getCoreLogger()->info(__VA_ARGS__)
#define PZ_CORE_WARN(...) ::Pz::Core::Logger::getCoreLogger()->warn(__VA_ARGS__)
#define PZ_CORE_ERROR(...) ::Pz::Core::Logger::getCoreLogger()->error(__VA_ARGS__)
#define PZ_CORE_CRITICAL(...) ::Pz::Core::Logger::getCoreLogger()->critical(__VA_ARGS__)

#define PZ_TRACE(...) ::Pz::Core::Logger::getClientLogger()->trace(__VA_ARGS__)
#define PZ_DEBUG(...) ::Pz::Core::Logger::getClientLogger()->debug(__VA_ARGS__)
#define PZ_INFO(...) ::Pz::Core::Logger::getClientLogger()->info(__VA_ARGS__)
#define PZ_WARN(...) ::Pz::Core::Logger::getClientLogger()->warn(__VA_ARGS__)
#define PZ_ERROR(...) ::Pz::Core::Logger::getClientLogger()->error(__VA_ARGS__)
#define PZ_CRITICAL(...) ::Pz::Core::Logger::getClientLogger()->critical(__VA_ARGS__)

} // namespace Pz::Core
