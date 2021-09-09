#pragma once
#include <map>
#include <memory>
#include <string>
#include <stdexcept>
#include <cassert>

// 
template <class Resource, class Identifier>
class ResourceHolder {
private:
	// 
	std::map<Identifier, std::unique_ptr<Resource>> resources;

public:
	ResourceHolder() {}

	// 
	void load(Identifier id, const std::string& filename);
	// 
	Resource& get(Identifier id);
};

template <class Resource, class Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
	// 
	std::unique_ptr<Resource> resource(new Resource());

	// 
	if (!resource->loadFromFile(filename))
		throw std::exception("ResourceHolder::load - Failed to load a texture.");

	// 
	// 
	auto inserted = resources.insert(std::make_pair(id, std::move(resource)));

	// 
	assert(inserted.second);
}

template <class Resource, class Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
	// 
	auto found = resources.find(id);
	// 
	assert(found != resources.end());

	// 
	return *found->second;
}