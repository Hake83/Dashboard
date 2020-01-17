#pragma once

#include <unordered_map>

#include "helper.h"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	// Set uniforms
	void SetUniform1f(const std::string& name, GLfloat value);
	void SetUniform2f(const std::string& name, GLfloat v0, GLfloat v1);
	void SetUniform3f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2);
	void SetUniform4f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

	void SetUniform1i(const std::string& name, GLint value);
	void SetUniform2i(const std::string& name, GLint v0, GLint v1);
	void SetUniform3i(const std::string& name, GLint v0, GLint v1, GLint v2);
	void SetUniform4i(const std::string& name, GLint v0, GLint v1, GLint v2, GLint v3);

	void SetUniform1ui(const std::string& name, GLuint value);
	void SetUniform2ui(const std::string& name, GLuint v0, GLuint v1);
	void SetUniform3ui(const std::string& name, GLuint v0, GLuint v1, GLuint v2);
	void SetUniform4ui(const std::string& name, GLuint v0, GLuint v1, GLuint v2, GLuint v3);

	void SetUniform1fv(const std::string& name, const GLfloat* value);
	void SetUniform2fv(const std::string& name, const GLfloat* v0, const GLfloat* v1);
	void SetUniform2fv(const std::string& name, const GLfloat* v0, const GLfloat* v1, const GLfloat* v2);
	void SetUniform2fv(const std::string& name, const GLfloat* v0, const GLfloat* v1, const GLfloat* v2, const GLfloat* v3);

	void SetUniform1iv(const std::string& name, const GLint* value);
	void SetUniform2iv(const std::string& name, const GLint* v0, const GLint* v1);
	void SetUniform2iv(const std::string& name, const GLint* v0, const GLint* v1, const GLint* v2);
	void SetUniform2iv(const std::string& name, const GLint* v0, const GLint* v1, const GLint* v2, const GLint* v3);

	void SetUniform1uiv(const std::string& name, const GLuint* value);
	void SetUniform2uiv(const std::string& name, const GLuint* v0, const GLuint* v1);
	void SetUniform2uiv(const std::string& name, const GLuint* v0, const GLuint* v1, const GLuint* v2);
	void SetUniform2uiv(const std::string& name, const GLuint* v0, const GLuint* v1, const GLuint* v2, const GLuint* v3);

	void SetUniformMat3f(const std::string& name, const mat3 matrix);
	void SetUniformMat4f(const std::string& name, const mat4 matrix);



private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;

	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	int GetUniformLocation(const std::string& name);
};