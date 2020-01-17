#include "log.h"

#define GL_LOG_FILE "GL.log"

bool init_log()
{
	std::ofstream log_file(GL_LOG_FILE, std::ios_base::out);
	if (!log_file.is_open())
	{
		std::cout << "Error opening the log file" << std::endl;
		return false;
	}

	log_file.close();
	return true;
}

bool gl_log(const std::string& text, int v[2])
{
	std::ofstream log_file(GL_LOG_FILE, std::ios_base::out);
	if (!log_file.is_open())
	{
		std::cout << "Error opening the log file" << std::endl;
		return false;
	}

	log_file << text;
	log_file << " " << v[0] << " " << v[1] << std::endl;
	log_file.close();

	return true;

}

bool gl_log(const std::string& text, int v)
{
	std::ofstream log_file(GL_LOG_FILE, std::ios_base::out);
	if (!log_file.is_open())
	{
		std::cout << "Error opening the log file" << std::endl;
		return false;
	}

	log_file << text;
	log_file << " " << v << std::endl;
	log_file.close();

	return true;
}

bool gl_log(const std::string& text, const GLubyte* message)
{
	std::ofstream log_file(GL_LOG_FILE, std::ios_base::out);
	if (!log_file.is_open())
	{
		std::cout << "Error opening the log file" << std::endl;
		return false;
	}

	log_file << text << " ";
	log_file << message << std::endl;
	log_file.close();

	return true;
}

bool gl_log(const GLubyte* message)
{
	std::ofstream log_file(GL_LOG_FILE, std::ios_base::out);
	if (!log_file.is_open())
	{
		std::cout << "Error opening the log file" << std::endl;
		return false;
	}

	log_file << message << std::endl;
	log_file.close();

	return true;
}

bool gl_log(const std::string& text)
{
	std::ofstream log_file(GL_LOG_FILE, std::ios_base::out);
	if (!log_file.is_open())
	{
		std::cout << "Error opening the log file" << std::endl;
		return false;
	}

	log_file << text << std::endl;
	log_file.close();

	return true;
}

bool print_all(GLuint id)
{
	int params = -1;

	std::ofstream log_file(GL_LOG_FILE, std::ios::out | std::ios_base::app);
	if (!log_file.is_open())
	{
		std::cout << "Error opening the log file in print_all function" << std::endl;
		return false;
	}

	//print link status
	glGetProgramiv(id, GL_LINK_STATUS, &params);
	log_file << "-------------------\nshader program " << id << " info:\nGL_LINK_STATUS = "
		<< params << "\n\n";

	//print shaders
	glGetProgramiv(id, GL_ATTACHED_SHADERS, &params);
	log_file << "GL_ATTACHED_SHADERS = " << params << "\n\n";

	//print active attributes
	glGetProgramiv(id, GL_ACTIVE_ATTRIBUTES, &params);
	log_file << "GL_ACTIVE_ATTRIBUTES = " << params << std::endl << std::endl;

	log_file.close();
	return true;
}