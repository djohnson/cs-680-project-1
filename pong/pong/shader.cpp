#include "shader.h"

GLuint
	VertexShaderId,
	FragmentShaderId,
	ProgramId,
	VaoId,
	VboId;

static GLuint make_buffer( GLenum target, Vertex buffer_data, GLsizei buffer_size) {
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(target, buffer);
    glBufferData(target, buffer_size, &buffer_data, GL_STATIC_DRAW);
    return buffer;
}

static GLuint make_texture(const char *filename)
{
    int width, height;
    void *pixels = read_tga(filename, &width, &height);
    GLuint texture;

    if (!pixels)
        return 0;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_EDGE);
    glTexImage2D(
        GL_TEXTURE_2D, 0,           /* target, level */
        GL_RGB8,                    /* internal format */
        width, height, 0,           /* width, height, border */
        GL_BGR, GL_UNSIGNED_BYTE,   /* external format, type */
        pixels                      /* pixels */
    );
    free(pixels);
    return texture;
}

void CreateVBO(void)
{
	Vertex temp_vertex;

	GLenum ErrorCheckValue = glGetError();
	const size_t BufferSize = main_scene.elements[0].verticies.size()*sizeof(float);
	const size_t VertexSize = sizeof(temp_vertex);
	const size_t RgbOffset = sizeof(temp_vertex.XYZW);
	
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	make_buffer( GL_ARRAY_BUFFER, main_scene.elements[0].verticies[0], BufferSize);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		std::cout<< "Error creating VBO: " << gluErrorString(ErrorCheckValue);
		exit(-1);
	}
}

void DestroyVBO(void)
{
	GLenum ErrorCheckValue = glGetError();

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		std::cout<< "Error destroying the VBO: "<< gluErrorString(ErrorCheckValue);
		exit(-1);
	}
}

static GLuint make_shader(GLenum type, const char *filename)
{
    GLuint shader;
    GLint compile_status;

	std::string shader_source = file_contents_d(filename);
	const GLchar * shader_source_string = shader_source.c_str();

    shader = glCreateShader(type);
	
	glShaderSource(shader, 1, &shader_source_string, NULL);

    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
	GLenum ErrorCheckValue = glGetError();
    
	if  (!compile_status) {
        std::cout<< "Error creating the shader: " << gluErrorString(ErrorCheckValue);
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

static GLuint make_program(GLuint vertex_shader, GLuint fragment_shader)
{
    GLint compile_status;
    GLuint program = glCreateProgram();

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &compile_status);
	GLenum ErrorCheckValue = glGetError();

    if  (!compile_status) {
        std::cout<< "Error creating the program: " << gluErrorString(ErrorCheckValue);
        glDeleteProgram(program);
        return 0;
    }
    return program;
}



void CreateShaders(void)
{
	GLenum ErrorCheckValue;
	VertexShaderId = make_shader(GL_VERTEX_SHADER, "vertex.glsl");
	FragmentShaderId = make_shader(GL_FRAGMENT_SHADER, "fragment.glsl");

	ProgramId = make_program( VertexShaderId, FragmentShaderId);
	glUseProgram(ProgramId);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		std::cout<< "Error creating the shader: " << gluErrorString(ErrorCheckValue);
		exit(-1);
	}
}

void DestroyShaders(void)
{
	GLenum ErrorCheckValue = glGetError();

	glUseProgram(0);

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);

	glDeleteProgram(ProgramId);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		std::cout<<"Error destorying shaders";
		std::cout<< gluErrorString(ErrorCheckValue);

		exit(-1);
	}
}

void Cleanup(void)
{
	DestroyShaders();
	DestroyVBO();
}