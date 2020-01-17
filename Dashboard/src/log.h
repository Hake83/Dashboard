#pragma once

#include "helper.h"

bool init_log();
bool gl_log(const std::string& text, int v[2]);
bool gl_log(const std::string& text, int v);
bool gl_log(const std::string& text, const GLubyte* message);
bool gl_log(const GLubyte* message);
bool gl_log(const std::string& text);
bool print_all(GLuint id);
bool gl_log();