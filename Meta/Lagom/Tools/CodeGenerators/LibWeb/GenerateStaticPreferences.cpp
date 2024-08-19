/*
 * Copyright (c) 2024, Jamie Mansfield <jmansfield@cadixdev.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "GeneratorUtil.h"
#include <AK/SourceGenerator.h>
#include <AK/StringBuilder.h>
#include <LibCore/ArgsParser.h>
#include <LibMain/Main.h>

ErrorOr<void> generate_header_file(JsonObject& preferences_data, Core::File& file);
ErrorOr<void> generate_implementation_file(JsonObject& preferences_data, Core::File& file);
String preference_key_to_cpp_name(String const&);

ErrorOr<int> serenity_main(Main::Arguments arguments)
{
    StringView generated_header_path;
    StringView generated_implementation_path;
    StringView json_path;

    Core::ArgsParser args_parser;
    args_parser.add_option(generated_header_path, "Path to the StaticPreferences header file to generate", "generated-header-path", 'h', "generated-header-path");
    args_parser.add_option(generated_implementation_path, "Path to the StaticPreferences implementation file to generate", "generated-implementation-path", 'c', "generated-implementation-path");
    args_parser.add_option(json_path, "Path to the JSON file to read from", "json-path", 'j', "json-path");
    args_parser.parse(arguments);

    auto json = TRY(read_entire_file_as_json(json_path));
    VERIFY(json.is_object());
    auto preferences_data = json.as_object();

    auto generated_header_file = TRY(Core::File::open(generated_header_path, Core::File::OpenMode::Write));
    auto generated_implementation_file = TRY(Core::File::open(generated_implementation_path, Core::File::OpenMode::Write));

    TRY(generate_header_file(preferences_data, *generated_header_file));
    TRY(generate_implementation_file(preferences_data, *generated_implementation_file));

    return 0;
}

ErrorOr<void> generate_header_file(JsonObject& prefs_data, Core::File& file)
{
    StringBuilder builder;
    SourceGenerator generator { builder };

    generator.append(R"~~~(
#pragma once

#include <AK/String.h>

namespace Web::Preferences {

)~~~");

    prefs_data.for_each_member([&](auto& name, auto& value) {
        VERIFY(value.is_object());
        auto value_obj = value.as_object();

        auto value_type = MUST(String::from_byte_string(value_obj.get_byte_string("type"sv).value()));

        auto pref_generator = generator.fork();
        pref_generator.set("key:cpp", preference_key_to_cpp_name(MUST(String::from_byte_string(name))));

        if (value_type == "string") {
            pref_generator.append(R"~~~(
String @key:cpp@();
void set_@key:cpp@(String const&);
)~~~");
        } else if (value_type == "boolean") {
            pref_generator.append(R"~~~(
bool @key:cpp@();
void set_@key:cpp@(bool);
)~~~");
        } else {
            VERIFY_NOT_REACHED();
        }
    });

    generator.appendln(R"~~~(
}
)~~~");

    TRY(file.write_until_depleted(generator.as_string_view().bytes()));
    return {};
}

ErrorOr<void> generate_implementation_file(JsonObject& prefs_data, Core::File& file)
{
    StringBuilder builder;
    SourceGenerator generator { builder };

    generator.append(R"~~~(
#include <LibWeb/Preferences/Preferences.h>
#include <LibWeb/Preferences/StaticPreferences.h>

namespace Web::Preferences {
)~~~");

    prefs_data.for_each_member([&](auto& name, auto& value) {
        VERIFY(value.is_object());
        auto value_obj = value.as_object();

        auto value_type = MUST(String::from_byte_string(value_obj.get_byte_string("type"sv).value()));
        auto value_initial_value = MUST(String::from_byte_string(value_obj.get_byte_string("initial_value"sv).value()));

        auto pref_generator = generator.fork();
        pref_generator.set("key", MUST(String::from_byte_string(name)));
        pref_generator.set("key:cpp", preference_key_to_cpp_name(MUST(String::from_byte_string(name))));
        pref_generator.set("initial_value", value_initial_value);

        if (value_type == "string") {
            pref_generator.append(R"~~~(
String @key:cpp@()
{
    return Preferences::the().get("@key@"_string).value_or("@initial_value@"_string);
}

void set_@key:cpp@(String const& value)
{
    Preferences::the().set("@key@"_string, value);
}
)~~~");
        } else if (value_type == "boolean") {
            pref_generator.append(R"~~~(
bool @key:cpp@()
{
    return Preferences::the().get("@key@"_string).value_or("@initial_value@"_string) == "true";
}

void set_@key:cpp@(bool value)
{
    Preferences::the().set("@key@"_string, value ? "true"_string : "false"_string);
}
)~~~");
        } else {
            VERIFY_NOT_REACHED();
        }

    });

    generator.appendln("}");

    TRY(file.write_until_depleted(generator.as_string_view().bytes()));
    return {};
}

String preference_key_to_cpp_name(String const& key)
{
    return MUST(key.replace("."sv, "_"sv, ReplaceMode::All));
}
