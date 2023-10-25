/*
    T
*/

#pragma once

#include <cstddef>
#include "serialization_utils.h"

namespace Duck {
	class Serializable {
	public:
		virtual ~Serializable() = default;

		/**
		 * Gets the serialized size of the object.
		 * @return The serialized size, in bytes, of the object.
		 */
		virtual size_t serialized_size() const = 0;

		/**
		 * Serializes the object.
		 * @param buf The buffer to serialize into.
		 */
		virtual void serialize(uint8_t*& buf) const = 0;

		/**
		 * Deserializes the object.
		 * @param buf The buffer to deserialize from.
		 */
		virtual void deserialize(const uint8_t*& buf) = 0;
	};
}