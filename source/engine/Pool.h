#pragma once

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace engine
{

template <typename T>
class Pool
{
public:
	Pool(unsigned size) :
		objects(size),
		markedAsUsed(size),
		unused(size)
	{
		std::cout << "Creating pool of " << size << " objects of type "
			<< typeid(T).name() << " (" << size * sizeof(T) / 1024 << "kb)" << std::endl;
	}

	T & newObject()
	{
		unsigned i = findNextFreeObject();
		assert(unused != 0);
		--unused;

		markedAsUsed[i] = true;
		return objects[i];
	}

	void removeObject(T & object)
	{
		assert(unused != objects.size());

		for (unsigned i = 0; i < objects.size(); ++i) {
			if (&objects[i] == &object) {
				objects = T();

				++unused;
				markedAsUsed[i] = false;
				return;
			}
		}

		throw std::runtime_error(
			std::string("Trying to free object that does not belong to pool: ")
			+ typeid(T).name());
	}
private:
	unsigned findNextFreeObject() const
	{
		for (unsigned i = 0; i < objects.size(); ++i) {
			if (markedAsUsed[i]) {
				continue;
			}

			return i;
		}

		throw std::runtime_error(
			std::string("No free objects in pool: ") + typeid(T).name());
	}

	std::vector<T> objects;
	std::vector<bool> markedAsUsed;
	unsigned unused;
};

} // namespace engine
