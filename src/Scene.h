#pragma once

#include "ILight.h"
#include "Prim.h"
#include "CameraPerspective.h"

/**
 * @brief Scene class
 */
class CScene
{
public:
	/**
	 * @brief Constructor
	 * @param camera The reference to the camera
	 * @todo Background may be image
	 */
	CScene(Vec3f bgColor = RGB(0,0,0))
		: m_bgColor(bgColor)
		, m_pCamera(std::make_unique<CCameraPerspective>(Vec3f(0,0,8), Vec3f(0,0,-1), Vec3f(0,1,0), 60, Size(800, 600)))
	{}
  	~CScene(void) = default;
  
	/**
	 * @brief Adds a new primitive to the scene
	 * @param prim Pointer to the primitive
	 */
	void Add(const std::shared_ptr<CPrim> pPrim)
	{

		m_vpPrims.push_back(pPrim);
		// from Problem 2.2.4: use the Add method as a settter
	}
	/**
	 * @brief Adds a new light to the scene
	 * @param pLight Pointer to the light
	 */
	void Add(const std::shared_ptr<ILight> pLight)
	{

		// Problem 2.4.1
		m_vpLights.push_back(pLight); // push the vector (add elements)
		//m_vpPrims = pLight;
	}
  
	/**
	 * @brief Checks intersection of ray \b ray with all contained objects
	 * @param ray The ray
	 * @retval true If ray \b ray intersects any object
	 * @retval false otherwise
	 */
	bool Intersect(Ray& ray) const
{

		// Problem 2.3.1.
		int flag = 0;
		for (auto it = m_vpPrims.begin() ; it != m_vpPrims.end(); ++it)
		{ // iterate through the primitives
			if ((*it)->Intersect(ray)){
				ray.hit = (*it).get();
				flag++; // flag that there was an intersection of at least one object
			}
		}
		if (flag > 0){
			return true;
		}
		return false;
	}

	/**
	 * find occluder
	 */
	bool Occluded(Ray& ray)
	{
		// --- PUT YOUR CODE HERE ---
		// 2.5.
		// check if something blocks the light
		for(auto prim : m_vpPrims)
			if(prim->Intersect(ray))
				return true;

		return false;
	}

	/**
	 trace the given ray and shade it and
	 return the color of the shaded ray
	 */
	Vec3f RayTrace(Ray& ray) const
	{
		// Problem 2.3.1
		if (Intersect(ray))
			return ray.hit->getShader()->Shade(ray); // initially was set to white
		else
			return m_bgColor; // initially was set to black
		
		//return Vec3f();
	}


public:
	std::unique_ptr<CCameraPerspective>		m_pCamera;
	std::vector<std::shared_ptr<ILight>>	m_vpLights;						///< lights
	
private:
	Vec3f									m_bgColor	= RGB(0, 0, 0);    	///< background color
	std::vector<std::shared_ptr<CPrim>> 	m_vpPrims;						///< primitives
};
