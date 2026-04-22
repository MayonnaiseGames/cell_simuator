#include "shader_class.hpp"

// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* filename){
	std::ifstream in(filename, std::ios::binary);
	if (in){
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char *vertex_file, const char *fragment_file){
    std::string vertex_code = get_file_contents(vertex_file);
    std::string fragment_code = get_file_contents(fragment_file);

    const char* vertex_source = vertex_code.c_str();
    const char* fragment_source = fragment_code.c_str();

    //compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_source, NULL);
    glCompileShader(vertexShader);

    //compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_source, NULL);
    glCompileShader(fragmentShader);

    //put both compiled shaders in a program to use
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    //free memory of shaders after program is created
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::activate(){
    glUseProgram(ID);
}

void Shader::destroy(){
    glDeleteProgram(ID);
}
