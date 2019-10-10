#pragma once

#include "ShaderFlat.h"

class CScene;

class CShaderPhong : public CShaderFlat
{
public:
	/**
	 * @brief Constructor
	 * @param scene Reference to the scene
	 * @param color The color of the object
	 * @param ka The ambient coefficient
	 * @param kd The diffuse reflection coefficients
	 * @param ks The specular refelection coefficients
	 * @param ke The shininess exponent
	 */
	CShaderPhong(CScene& scene, Vec3f color, float ka, float kd, float ks, float ke)
		: CShaderFlat(color)
		, m_scene(scene)
		, m_ka(ka)
		, m_kd(kd)
		, m_ks(ks)
		, m_ke(ke)
	{}
	virtual ~CShaderPhong(void) = default;

/*
	virtual Vec3f Shade(const Ray& ray) const override
	{
		// --- PUT YOUR CODE HERE ---
		return RGB(0, 0, 0);
	}
*/
	
	virtual Vec3f Shade(const Ray& ray) const override
	{

		// Problem 2.4.2
		
        Ray temp_ray;
        temp_ray.org = ray.org + ray.t * ray.dir; // now the new origin is the old end-point
        temp_ray.t = std::numeric_limits<float>::infinity(); // max hit distance
        Vec3f Sum_2 = 0;
        Vec3f Sum_3 = 0;

        for (auto i : m_scene.m_vpLights) {
            auto R = i->Illuminate(temp_ray);
            if (!m_scene.Occluded(temp_ray) && R) {

            	// Relevant for Term_2
            	auto temp_2 = temp_ray.dir.dot(ray.hit->GetNormal(ray));
                Sum_2 += *R * max(0.f, temp_2);

            	// Relevant for Term_3
                auto ReflL = temp_ray.dir - 2 * (temp_ray.dir.dot(ray.hit->GetNormal(ray))) * ray.hit->GetNormal(ray);
                auto temp_3 = ray.dir.dot(ReflL);
                Sum_3 += *R * pow(max(0.f, temp_3), m_ke);
            }

        }

        Vec3f Term_1 = m_ka * CShaderFlat::Shade(ray); // m_ka * c_a <- assuming c_a is white
        Vec3f Term_2 = m_kd * CShaderFlat::Shade(ray).mul(Sum_2);
        Vec3f Term_3 = m_ks * RGB(1, 1, 1) * (Sum_3);
        return Term_1 + Term_2 + Term_3;

	}


	
private:
	CScene& m_scene;
	float 	m_ka;    ///< ambient coefficient
	float 	m_kd;    ///< diffuse reflection coefficients
	float 	m_ks;    ///< specular refelection coefficients
	float 	m_ke;    ///< shininess exponent
};
