#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include <nlohmann/json.hpp>

using json = nlohmann::json;


std::string read_file(const std::string& path) {
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

json read_json_file(const std::string& path) {
    return json::parse(read_file(path));
}
