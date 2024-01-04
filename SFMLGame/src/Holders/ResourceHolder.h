#pragma once

#include <map>
#include <memory>
#include <SFML/Graphics/Texture.hpp>


//////////////////////////////////////////////////
// \brief
//	  This class is like lightweight pettern
//	  for the project.
// 
//    And it stores each resource, that the 
//    game will be use.
// 
//////////////////////////////////////////////////
template<typename ID, typename Resource>
class ResourceHolder
{
private:
	std::map<ID, std::unique_ptr<Resource>> resourceMap;

public:
	ResourceHolder() = default;
	~ResourceHolder() = default;

public:
	///////////////////////////////////////////////////////////
	// \brief
	//		This method loads the resource from file 
	//		into resourceMap.
	// 
	///////////////////////////////////////////////////////////
	void Load(const ID id, const std::string& path);

	//////////////////////////////////////////////////////////
	// \brief
	//		This is an overloaded Load method for 
	//		another classes, which do not have the
	//		loadFromFile method that takes one param.
	//		such as sf::Shader.
	// 
	//////////////////////////////////////////////////////////
	template<typename Parameter>
	void Load(const ID id, const std::string& path, const Parameter& secondPar);

	///////////////////////////////////////////////////////////
	// \brief
	//		These both return the requested resource.
	// 
	///////////////////////////////////////////////////////////
	Resource& Get(const ID id);
	const Resource& Get(const ID id) const;
};


///////////////////////////////////////////////////////////
// 
//		We include the .inl file in the end, because
//		the compiler knows about methods of the class
//		after its definition nothing else.
// 
//		Actualy, we need to remove the .inl file from 
//		the files list, which compiler will be use to
//		create a progrem.
// 
///////////////////////////////////////////////////////////
#include "ResourceHolder.inl"