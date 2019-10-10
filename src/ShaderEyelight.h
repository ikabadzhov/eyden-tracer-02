#pragma once

#include "ShaderFlat.h"

/**
 * @brief Eye-light shader class
 */
class CShaderEyelight : public CShaderFlat
{
public:
	/**
	 * @brief Constructor
	 * @details This is a texture-free and light-source-free shader
	 * @param scene Reference to the scene
	 * @param color The color of the objects
	 */
	CShaderEyelight(Vec3f color = RGB(0.5f, 0.5f, 0.5f))
		: CShaderFlat(color)
	{}
	virtual ~CShaderEyelight(void) = default;

	virtual Vec3f Shade(const Ray& ray) const override
	{
		// TASK 2.3.2
		// a(vec) dot b(vec) == |a|*|b|*cos(Theta)
		// => cos Theta = (a(vec) dot b(vec)) / (|a|*|b|)
		float theta = ray.hit->GetNormal(ray).dot(-ray.dir);
		return (fabs(theta)) * CShaderFlat::Shade(ray) / (norm(ray.hit->GetNormal(ray))*norm(-ray.dir));
	}
};

