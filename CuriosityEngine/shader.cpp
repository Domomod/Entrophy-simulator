#include <iostream>
#include <fstream>
#include <string>

#include "shader.h"
#include "material.h"

void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string LoadShader(const std::string& fileName);
GLuint CreateShader(const std::string& text, GLenum shaderType);

Shader::Shader(const std::string& fileName)
{
    m_program = glCreateProgram();
    m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
    m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);
    m_shaders[2] = CreateShader(LoadShader("./res/ambient.fs"), GL_FRAGMENT_SHADER);
    m_shaders[3] = CreateShader(LoadShader("./res/diffuse.fs"), GL_FRAGMENT_SHADER);
    m_shaders[4] = CreateShader(LoadShader("./res/specular.fs"), GL_FRAGMENT_SHADER);

    for(unsigned int i = 0; i < NUM_SHADERS; i++)
        glAttachShader(m_program, m_shaders[i]);

    glBindAttribLocation(m_program, 0, "position");
    glBindAttribLocation(m_program, 1, "texCoord");
    glBindAttribLocation(m_program, 2, "normal");
    glBindAttribLocation(m_program, 3, "tangent");

    glLinkProgram(m_program);
    CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Program linking failed: ");

    glValidateProgram(m_program);
    CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program in invalid: ");

    m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
    m_uniforms[MODEL_U] = glGetUniformLocation(m_program, "model");
    m_uniforms[CAMERA_POS_U] = glGetUniformLocation(m_program, "cameraPos");
    m_uniforms[VIEW_MATRIX_U] = glGetUniformLocation(m_program, "viewMatrix");

	m_LightSourceUniforms[TYPE_U] = glGetUniformLocation(m_program, "lightSources[0].Type");
	m_LightSourceUniforms[POSITION_U] = glGetUniformLocation(m_program, "lightSources[0].Position");
	m_LightSourceUniforms[ATTENUATION_U] = glGetUniformLocation(m_program, "lightSources[0].Attenuation");
	m_LightSourceUniforms[DIRECTION_U] = glGetUniformLocation(m_program, "lightSources[0].Direction");
	m_LightSourceUniforms[COLOR_U] = glGetUniformLocation(m_program, "lightSources[0].Color");
	m_LightSourceUniforms[AMBIENT_U] = glGetUniformLocation(m_program, "lightSources[0].AmbientCoefficient");
	
	m_NumLights = glGetUniformLocation(m_program, "NUM_LIGHTS");

	m_MaterialUniforms[MAT_EMMISION_U] = glGetUniformLocation(m_program, "material.Emmision");
	m_MaterialUniforms[MAT_AMBIENT_U] = glGetUniformLocation(m_program, "material.Ambient");
	m_MaterialUniforms[MAT_DIFFUSE_U] = glGetUniformLocation(m_program, "material.Diffuse");
	m_MaterialUniforms[MAT_SPECULAR_U] = glGetUniformLocation(m_program, "material.Specular");
	m_MaterialUniforms[MAT_SHININESS_U] = glGetUniformLocation(m_program, "material.Shininess");
	m_MaterialUniforms[MAT_DISP_SCALE_U] = glGetUniformLocation(m_program, "material.DispMapScale");
	m_MaterialUniforms[MAT_DISP_BIAS_U] = glGetUniformLocation(m_program, "material.DispMapBias");
}

Shader::~Shader()
{
    for(unsigned int i = 0; i < NUM_SHADERS; i++)
    {
        glDetachShader(m_program, m_shaders[i]);
        glDeleteShader(m_shaders[i]);
    }

    glDeleteProgram(m_program);
}

void Shader::Bind()
{
    glUseProgram(m_program);

    GLuint t1Location = glGetUniformLocation(m_program, "diffuse");
    GLuint t2Location = glGetUniformLocation(m_program, "normalMap");
    GLuint t3Location = glGetUniformLocation(m_program, "dispMap");

    glUniform1i(t1Location, 0);
    glUniform1i(t2Location, 1);
    glUniform1i(t3Location, 2);
}


void Shader::Detach()
{
    glUseProgram(0);
}

void Shader::UpdateMaterial(Material* material)
{
	glUniform3fv(m_MaterialUniforms[MAT_EMMISION_U], 1, (float*)&material->m_emmision);
	glUniform3fv(m_MaterialUniforms[MAT_AMBIENT_U], 1, (float*)&material->m_ambient);
	glUniform3fv(m_MaterialUniforms[MAT_DIFFUSE_U], 1, (float*)&material->m_diffuse);
	glUniform3fv(m_MaterialUniforms[MAT_SPECULAR_U], 1, (float*)&material->m_specular);
	glUniform1fv(m_MaterialUniforms[MAT_SHININESS_U], 1, (float*)&material->m_shininess);
	glUniform1fv(m_MaterialUniforms[MAT_DISP_SCALE_U], 1, (float*)&material->m_dispMapScale);
	glUniform1fv(m_MaterialUniforms[MAT_DISP_BIAS_U], 1, (float*)&material->m_dispMapBias);

}

void Shader::LoadLights(std::vector<Light> lights)
{
	int number = lights.size();
	if (number > MAX_LIGHTS)
		number = MAX_LIGHTS;

	for (int i = 0; i < number; i++)
    {
		glUniform1iv(m_LightSourceUniforms[TYPE_U] + i, 1, (int*)&lights[i].m_type);
		glUniform3fv(m_LightSourceUniforms[POSITION_U] + i, 1, (float*)&lights[i].m_position);
		glUniform3fv(m_LightSourceUniforms[ATTENUATION_U] + i, 1, (float*)&lights[i].m_attunation);
		glUniform3fv(m_LightSourceUniforms[DIRECTION_U] + i, 1, (float*)&lights[i].m_direction);
		glUniform3fv(m_LightSourceUniforms[COLOR_U] + i, 1, (float*)&lights[i].m_color);
		glUniform1fv(m_LightSourceUniforms[AMBIENT_U] + i, 1, (float*)&lights[i].m_ambientCoefficient);
    }

	glUniform1iv(m_NumLights, 1, (int*)&number);
}

void Shader::Update(const Transform& transform, const Camera& camera)
{
    glm::mat4 model = camera.GetViewProjection() * transform.GetModel();
    glm::mat4 modelMatrix = transform.GetModel();
    glm::mat4 viewprojection= camera.GetViewProjection();

    glm::vec3 positionCamera = camera.getPos();

    glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(m_uniforms[MODEL_U], 1, GL_FALSE, &modelMatrix[0][0]);
    glUniform3fv(m_uniforms[CAMERA_POS_U], 1, (float*)&positionCamera);
    glUniformMatrix4fv(m_uniforms[VIEW_MATRIX_U], 1, GL_FALSE, &viewprojection[0][0]);
    //glUniform1fv(m_uniforms[MAT_SHININESS_U], 1, (float*)&glLight[1].quadraticAtt);
}

GLuint CreateShader(const std::string& text, GLenum shaderType)
{
    GLuint shader = glCreateShader(shaderType);

    if(shader == 0)
        std::cerr<< "Error: Shader creation failed!" << std::endl;

    const GLchar* shaderSourceStrings[1];
    GLint shaderSourceStringLengths[1];

    shaderSourceStrings[0] = text.c_str();
    shaderSourceStringLengths[0] = text.length();

    glShaderSource(shader , 1, shaderSourceStrings, shaderSourceStringLengths);
    glCompileShader(shader);

    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");

    return shader;
}

static std::string LoadShader(const std::string& fileName)
{
    std::ifstream file;
    file.open((fileName).c_str());

    std::string output;
    std::string line;

    if(file.is_open())
    {
        while(file.good())
        {
            getline(file, line);
			output.append(line + "\n");
        }
    }
    else
    {
		std::cerr << "Unable to load shader: " << fileName << std::endl;
    }

    return output;
}

void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if(isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if(success == GL_FALSE)
    {
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}

Shader::Shader(const Shader& other)
{
    this->m_program = other.m_program;
    for(int i; i < NUM_SHADERS; i++)
        this->m_shaders[i] = other.m_shaders[i];
    for(int i; i < NUM_UNIFORMS; i++)
        this->m_uniforms[i] = other.m_uniforms[i];
    for(int i; i < NUM_PARAMS_LIGHT; i++)
        this->m_LightSourceUniforms[i] = other.m_LightSourceUniforms[i];
	for (int i; i < NUM_PARAMS_MAT; i++)
		this->m_MaterialUniforms[i] = other.m_MaterialUniforms[i];
}
