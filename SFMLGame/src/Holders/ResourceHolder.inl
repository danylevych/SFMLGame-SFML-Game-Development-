//#include "ResourceHolder.h" // <- if you want to make some changes.

#include <stdexcept> // <- For std::runtime_error
#include <cassert>

template<typename ID, typename Resource>
inline void ResourceHolder<ID, Resource>::Load(const ID id, const std::string& path)
{
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(path))
	{
		throw std::runtime_error("TextureHolder::Load - Failed to load: " + path);
	}

	auto inserted = resourceMap.emplace(id, std::move(resource));
	assert(inserted.second);
}

template<typename ID, typename Resource>
template<typename Parameter>
inline void ResourceHolder<ID, Resource>::Load(const ID id, const std::string& path, const Parameter& secondPar)
{
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(path, secondPar))
	{
		throw std::runtime_error("TextureHolder::Load - Failed to load: " + path);
	}

	auto inserted = resourceMap.emplace(id, std::move(resource));
	assert(inserted.second);
}


template<typename ID, typename Resource>
inline Resource& ResourceHolder<ID, Resource>::Get(const ID id)
{
	auto found = resourceMap.find(id);
	assert(found != resourceMap.end());

	return *found->second;
}

template<typename ID, typename Resource>
inline const Resource& ResourceHolder<ID, Resource>::Get(const ID id) const
{
	auto found = resourceMap.find(id);
	assert(found != resourceMap.end());

	return *found->second;
}