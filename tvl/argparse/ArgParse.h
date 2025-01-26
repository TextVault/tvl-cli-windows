#pragma once
#include <map>
#include <string>
#include <vector>

namespace tvl {
class ArgParse final {
public:
    ArgParse(const std::string& program_name);
    ~ArgParse();

    void Add(const std::string& longName, const std::string& shortName = "\0", const std::string& helpMessage = "\0");

    std::string Get(const std::string& name) const;
    bool Has(const std::string& name) const;

    bool PositionHas(const std::string& name) const;

    void Parse(int argc, char* argv[]);
    void PrintHelp() const;
    const std::vector<std::string>& GetPositionalArgs() const;

private:
    std::string _program_name;
    std::map<std::string, std::string> _arguments;
    std::map<std::string, std::string> _short_to_long;
    std::map<std::string, std::string> _help_messages;
    std::vector<std::string> _positional_args;
};
}  // namespace tvl