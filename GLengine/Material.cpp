#include <memory>
#include <Shadinclude.hpp>
#include "Material.h"
#include "RTexture.h"
#include "Texture.h"
#include "RCubeMap.h"

RMaterial::RMaterial(const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShaderPath)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode = Shadinclude::load(vertexShaderPath);
    std::string fragmentCode = Shadinclude::load(fragmentShaderPath);
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    // 2. compile shaders
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    unsigned int geom;
    // Optional Geometry Shader
    if (geometryShaderPath)
    {
        std::string geometryCode = Shadinclude::load(geometryShaderPath);
        const char* gShaderCode = geometryCode.c_str();
        geom = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geom, 1, &gShaderCode, NULL);
        glCompileShader(geom);
        checkCompileErrors(geom, "GEOMETRY");
        glAttachShader(ID, geom);
    }
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if (geometryShaderPath)
    {
        glDeleteShader(geom);
    }
}

RMaterial::~RMaterial()
{
    glDeleteProgram(ID);
}

void RMaterial::Activate() const
{
    glUseProgram(ID);
}

void RMaterial::Use() const
{
    // Cull
    glCullFace(cullMode);
    // Transparency
    glBlendFunc(blendFuncSrc, blendFuncDest);
    // Depth
    glDepthFunc(depthFunc);
    glDepthMask(depthMask);
    // Stencil
    glStencilFunc(stencilFunc, stencilRef, stencilMask);
    glStencilOp(stencilFail, stencilPassDepthFail, stencilDepthPass);
    // Set textures
    int i = 0;
    for (auto it = textures.begin(); it != textures.end(); ++it)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        if (std::dynamic_pointer_cast<RTexture2D>(it->second))
        {
            glBindTexture(GL_TEXTURE_2D, it->second->GetID());
        }
        else if (std::dynamic_pointer_cast<RCubeMap>(it->second))
        {
            glBindTexture(GL_TEXTURE_CUBE_MAP, it->second->GetID());
        }
        i++;
    }

    // Activate shader
    Activate();
}

void RMaterial::checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

void RMaterial::SetTexture(const std::string& name, std::shared_ptr<RTexture> texture)
{
    if (textures.find(name) != textures.end())
    {
        textures[name] = texture;
    }
    else
    {
        SetInt(name, textures.size());
        textures.insert({ name, texture });
    }
}
