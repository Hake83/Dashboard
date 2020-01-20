#include "Shader.h"

Shader::Shader(const std::string& filepath)
	: m_FilePath(filepath), m_RendererID(0)
{
	ShaderProgramSource source = ParseShader(m_FilePath);
	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
	enum  class ShaderType//enum to define writing state for the parser
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::ifstream stream(filepath);
	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			if (type != ShaderType::NONE)
				ss[(int)type] << line << '\n';
		}
	}
	stream.close();
	return { ss[0].str(), ss[1].str() };
}

GLuint Shader::CompileShader(unsigned int type, const std::string& source)
{
	GLuint id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	//Logic to output an error message if the shader is messed up
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::string error_header = "Failed to compile ";
		error_header.append(type == GL_VERTEX_SHADER ? "vertex " : "fragment ");
		error_header.append("shader");
		gl_log(error_header);
		gl_log(message);
		glDeleteShader(id);
		return 0;
	}

	return id;
}

GLuint Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	GLuint program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	int location = glGetUniformLocation(m_RendererID, name.c_str());
	if (location == -1)
	{
		std::string error_message = "Warning: uniform '";
		error_message.append(name);
		error_message.append("' doesn't exist!");
	}

	m_UniformLocationCache[name] = location;
	return location;
}

void Shader::Bind() const
{
	glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetUniform1f(const std::string& name, GLfloat value)
{
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform2f(const std::string& name, GLfloat v0, GLfloat v1)
{
	glUniform2f(GetUniformLocation(name), v0, v1);
}

void Shader::SetUniform3f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2)
{
	glUniform3f(GetUniformLocation(name), v0, v1, v2);
}

void Shader::SetUniform4f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniform1i(const std::string& name, GLint value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform2i(const std::string& name, GLint v0, GLint v1)
{
	glUniform2i(GetUniformLocation(name), v0, v1);
}

void Shader::SetUniform3i(const std::string& name, GLint v0, GLint v1, GLint v2)
{
	glUniform3i(GetUniformLocation(name), v0, v1, v2);
}

void Shader::SetUniform4i(const std::string& name, GLint v0, GLint v1, GLint v2, GLint v3)
{
	glUniform4i(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniform1ui(const std::string& name, GLuint value)
{
	glUniform1ui(GetUniformLocation(name), value);
}

void Shader::SetUniform2ui(const std::string& name, GLuint v0, GLuint v1)
{
	glUniform2ui(GetUniformLocation(name), v0, v1);
}

void Shader::SetUniform3ui(const std::string& name, GLuint v0, GLuint v1, GLuint v2)
{
	glUniform3ui(GetUniformLocation(name), v0, v1, v2);
}

void Shader::SetUniform4ui(const std::string& name, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
	glUniform4ui(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniform1fv(const std::string& name, const GLsizei count, const GLfloat* value)
{
	glUniform1fv(GetUniformLocation(name), count, value);
}

void Shader::SetUniform2fv(const std::string& name, const GLsizei count, const GLfloat* value)
{
	glUniform2fv(GetUniformLocation(name), count, value);
}

void Shader::SetUniform3fv(const std::string& name, const GLsizei count, const GLfloat* value)
{
	glUniform3fv(GetUniformLocation(name), count, value);
}

void Shader::SetUniform4fv(const std::string& name, const GLsizei count, const GLfloat* value)
{
	glUniform4fv(GetUniformLocation(name), count, value);
}

void Shader::SetUniform1iv(const std::string& name, const GLsizei count, const GLint* value)
{
	glUniform1iv(GetUniformLocation(name), count, value);
}

void Shader::SetUniform2iv(const std::string& name, const GLsizei count, const GLint* value)
{
	glUniform2iv(GetUniformLocation(name), count, value);
}

void Shader::SetUniform3iv(const std::string& name, const GLsizei count, const GLint* value)
{
	glUniform3iv(GetUniformLocation(name), count, value);
}

void Shader::SetUniform4iv(const std::string& name, const GLsizei count, const GLint* value)
{
	glUniform4iv(GetUniformLocation(name), count, value);
}

void Shader::SetUniform1uiv(const std::string& name, const GLsizei count, const GLuint* value)
{
	glUniform1uiv(GetUniformLocation(name), count, value);
}

void Shader::SetUniform2uiv(const std::string& name, const GLsizei count, const GLuint* value)
{
	glUniform2uiv(GetUniformLocation(name), count, value);
}

void Shader::SetUniform3uiv(const std::string& name, const GLsizei count, const GLuint* value)
{
	glUniform3uiv(GetUniformLocation(name), count, value);
}

void Shader::SetUniform4uiv(const std::string& name, const GLsizei count, const GLuint* value)
{
	glUniform4uiv(GetUniformLocation(name), count, value);
}

void Shader::SetUniformMat3f(const std::string& name, GLsizei count, const mat3 matrix)
{
	glUniformMatrix3fv(GetUniformLocation(name), count, GL_FALSE, matrix.m);
}

void Shader::SetUniformMat4f(const std::string& name, GLsizei count, const mat4 matrix)
{
	glUniformMatrix4fv(GetUniformLocation(name), count, GL_FALSE, matrix.m);
}
