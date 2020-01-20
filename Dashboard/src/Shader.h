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

	void SetUniform1fv(const std::string& name, const GLsizei count, const GLfloat* value);
	void SetUniform2fv(const std::string& name, const GLsizei count, const GLfloat* value);
	void SetUniform3fv(const std::string& name, const GLsizei count, const GLfloat* value);
	void SetUniform4fv(const std::string& name, const GLsizei count, const GLfloat* value);

	void SetUniform1iv(const std::string& name, const GLsizei count, const GLint* value);
	void SetUniform2iv(const std::string& name, const GLsizei count, const GLint* value);
	void SetUniform3iv(const std::string& name, const GLsizei count, const GLint* value);
	void SetUniform4iv(const std::string& name, const GLsizei count, const GLint* value);

	void SetUniform1uiv(const std::string& name, const GLsizei count, const GLuint* value);
	void SetUniform2uiv(const std::string& name, const GLsizei count, const GLuint* value);
	void SetUniform3uiv(const std::string& name, const GLsizei count, const GLuint* value);
	void SetUniform4uiv(const std::string& name, const GLsizei count, const GLuint* value);

	void SetUniformMat3f(const std::string& name, GLsizei count, const mat3 matrix);
	void SetUniformMat4f(const std::string& name, GLsizei count, const mat4 matrix);



private:
	std::string m_FilePath;
	GLuint m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;

	ShaderProgramSource ParseShader(const std::string& filepath);
	GLuint CompileShader(unsigned int type, const std::string& source);
	GLuint CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	int GetUniformLocation(const std::string& name);
};