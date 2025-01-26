#include <iostream>

#include "argparse/ArgParse.h"

int main(int argc, char* argv[]) {
    tvl::ArgParse parser("tvl.exe");

    parser.Add("file", "f", "File to upload to the server.");
    parser.Add("username", "u", "Username for upload by user.");
    parser.Add("password", "p", "Password for private paste.");

    try {
        parser.Parse(argc, argv);

        // NOTE: Install method
        const auto isInstallMethod = parser.PositionHas("install");
        if (isInstallMethod) {
            // TODO: Implement
        }

        // NOTE: Login method
        const auto isLoginMethod = parser.PositionHas("login");
        const auto username = parser.Get("username");
        if (isLoginMethod && !username.empty()) {
            // TODO: Login logic
            std::cout << "trying to login with username: '" << parser.Get("username") << "'" << "\n";
        } else if (username.empty()) {
            std::cerr << "Failed to login, no username provided." << "\n";
            return EXIT_FAILURE;
        }

    } catch (const std::exception& e) {
        parser.PrintHelp();

        return 1;
    }
}