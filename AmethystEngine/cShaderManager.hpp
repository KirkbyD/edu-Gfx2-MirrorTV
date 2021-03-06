#pragma once

#include <string>
#include <vector>
#include <map>

class cShaderManager {
public:
	class cShader {
	public:
		cShader();
		~cShader();
		enum eShaderType { VERTEX_SHADER, FRAGMENT_SHADER, GEOMETRY_SHADER, UNKNOWN };
		eShaderType shaderType;
		std::string getShaderTypeString(void);

		unsigned int ID;	// or "name" from OpenGL
		std::vector<std::string> vecSource;
		bool bSourceIsMultiLine;
		std::string fileName;
	};

	class cShaderProgram {
	public:
		cShaderProgram() : ID(0) { };
		~cShaderProgram() { };
		unsigned int ID;	// ID from OpenGL (calls it a "name")
		std::string friendlyName;	// We give it this name

		// TODO: For the students to do, because it's FUN, FUN, FUN
		std::map< std::string /*name of uniform variable*/, int /* uniform location ID */ > mapUniformName_to_UniformLocation;
		// Returns -1 (just like OpenGL) if NOT found
		int getUniformID_From_Name(std::string name);
		// Look up the uniform location and save it.
		bool LoadUniformLocation(std::string variableName);


		// ** Call this once, when compiled and linked
		// When called, this will load the map of uniforms. 
		void LoadActiveUniforms(void);
		std::map<std::string /*uniform name*/,
			int /*uniform location*/> map_UniformNameToLocID;
		// This looks up the map, instead of calling glGetUniformLocation() over and over
		int getUniformLocID(std::string uniformname);

		//		void glUniform( std::string name, glm::vec4 value );
		//
		//		void glUniform1f( std::string name, float value );
		//		void glUniform2f( std::string name, glm::vec2 value );
		//		void glUniform3f( std::string name, glm::vec3 value );

		std::string getNameStringFromType(int glVariableType);
	};

	cShaderManager() { };
	~cShaderManager() { };

	bool useShaderProgram(unsigned int ID);
	bool useShaderProgram(std::string friendlyName);

	// This will recreate the shader by default
	bool createProgramFromFile(std::string friendlyName, cShader& vertexShad, cShader& fragShader, bool replaceExisting = true);
	bool createProgramFromFile(std::string friendlyName, cShader& vertexShad, cShader& fragShader, cShader& geomShader, bool replaceExisting = true);

	void setBasePath(std::string basepath);
	unsigned int getIDFromFriendlyName(std::string friendlyName);

	// Used to load the uniforms. Returns NULL if not found.
	cShaderProgram* pGetShaderProgramFromFriendlyName(std::string friendlyName);

	// Clears last error
	std::string getLastError(void);

	void DeconstructShaderPrograms();

private:
	// Returns an empty string if it didn't work
	bool m_loadSourceFromFile(cShader& shader);
	std::string m_basepath;

	bool m_compileShaderFromSource(cShader& shader, std::string& error);
	// returns false if no error
	bool m_wasThereACompileError(unsigned int shaderID, std::string& errorText);
	bool m_wasThereALinkError(unsigned int progID, std::string& errorText);

	std::string m_lastError;

	std::map< unsigned int /*ID*/, cShaderProgram > m_ID_to_Shader;			// SHADER PROGRAM
	std::map< std::string /*name*/, unsigned int /*ID*/ > m_name_to_ID;		// SHADERS
};
