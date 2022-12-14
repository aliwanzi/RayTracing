#pragma once
#include "./../../Core/Common.h"

namespace SandTable 
{
	class Shader
	{
	public:
		Shader(const std::string& name, const std::string& filepath);
		Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);

		 ~Shader();

		void Bind() const;
		void Unbind() const;

		void SetInt(const std::string& name, int value);
		void SetIntArray(const std::string& name, int* values, uint32_t count);
		void SetFloat(const std::string& name, float value);
		void SetFloat2(const std::string& name, const glm::vec2& value);
		void SetFloat3(const std::string& name, const glm::vec3& value);
		void SetFloat4(const std::string& name, const glm::vec4& value);
		void SetMat4(const std::string& name, const glm::mat4& value);

		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformIntArray(const std::string& name, int* values, uint32_t count);

		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		std::string ReadFile(const std::string& filepath);
		std::map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::map<GLenum, std::string>& shaderSources);
	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};

	class ShaderLibrary
	{
	public:
		void AddShader(const std::string& name, std::shared_ptr<Shader> shader);
		void AddShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		std::shared_ptr<Shader> AddShader(const std::string& name, const std::string& filepath);

		std::shared_ptr<Shader> GetShader(const std::string& name);
	private:
		std::map<std::string, std::shared_ptr<Shader>> m_mapShader;
	};
}
