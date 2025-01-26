#include "ArgParse.h"
#include <iostream>

namespace tvl {
ArgParse::ArgParse(const std::string& program_name) : _program_name(program_name) {}

ArgParse::~ArgParse() {
    _arguments.clear();
    _short_to_long.clear();
    _help_messages.clear();
    _positional_args.clear();
}

void ArgParse::Add(const std::string& longName, const std::string& shortName, const std::string& helpMessage) {
    _arguments[longName] = "";
    _help_messages[longName] = helpMessage;
    if (!shortName.empty()) {
        _short_to_long[shortName] = longName;
    }
}
std::string ArgParse::Get(const std::string& name) const {
    if (_arguments.find(name) == _arguments.end()) {
        throw std::invalid_argument("Argument not found: " + name);
    }
    return _arguments.at(name);
}

bool ArgParse::Has(const std::string& name) const { return _arguments.find(name) != _arguments.end(); }

bool ArgParse::PositionHas(const std::string& name) const {
    return std::ranges::find(_positional_args.begin(), _positional_args.end(), name) != _positional_args.end();
}

void ArgParse::Parse(int argc, char* argv[]) {
    if (argc <= 1) {
        throw std::invalid_argument("No arguments provided");
    }

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg.substr(0, 2) == "--") {
            std::string key = arg.substr(2);
            if (_arguments.find(key) == _arguments.end()) {
                throw std::invalid_argument("Unknown argument: --" + key);
            }
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                _arguments[key] = argv[++i];
            } else {
                _arguments[key] = "true";
            }
        } else if (arg.substr(0, 1) == "-") {
            std::string short_key = arg.substr(1);
            if (_short_to_long.find(short_key) == _short_to_long.end()) {
                throw std::invalid_argument("Unknown argument: -" + short_key);
            }
            std::string long_key = _short_to_long[short_key];
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                _arguments[long_key] = argv[++i];
            } else {
                _arguments[long_key] = "true";
            }
        } else {
            _positional_args.push_back(arg);
        }
    }
}

void ArgParse::PrintHelp() const {
    std::cout << "Usage: " << _program_name << " [OPTIONS] [ARGS]\n" << "Available options:\n";
    for (const auto& [long_name, help] : _help_messages) {
        std::cout << "  --" << long_name;

        for (const auto& [short_name, long_key] : _short_to_long) {
            if (long_key == long_name) {
                std::cout << ", -" << short_name;
                break;
            }
        }
        std::cout << "\t\t" << help << "\n";
    }
}

const std::vector<std::string>& ArgParse::GetPositionalArgs() const { return _positional_args; }
}  // namespace tvl