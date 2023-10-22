/*
    This file is part of duckOS.
    
    duckOS is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    
    duckOS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with duckOS.  If not, see <https://www.gnu.org/licenses/>.
    
    Copyright (c) Byteduck 2016-2022. All rights reserved.
*/
#pragma once

#include <memory>
#include "Buffer.h"

namespace Duck {
	class ByteBuffer: public Buffer {
	public:
		DUCK_OBJECT_DEF(ByteBuffer);

		~ByteBuffer() noexcept;

		/**
		 * Creates a new ByteBuffer that points to existing memory.
		 * @param ptr The pointer to memory.
		 * @param size The size, in bytes, of the buffer.
		 * @return The new ByteBuffer.
		 */
		static Ptr<ByteBuffer> adopt(void* ptr, size_t size);

		/**
		 * Creates a new ByteBuffer from a copy of existing memory.
		 * @param ptr The pointer to memory.
		 * @param size The size, in bytes, of the buffer.
		 * @return The new ByteBuffer.
		 */
		static Ptr<ByteBuffer> copy(const void* ptr, size_t size);

		/**
		 * Creates a new ByteBuffer from existing memory, which will not be freed on destruction.
		 * @param ptr The pointer to memory.
		 * @param size The size, in bytes, of the buffer.
		 * @return The new ByteBuffer.
		 */
		static Ptr<ByteBuffer> shadow(void* ptr, size_t size);

		/**
		 * Creates a clone of the ByteBuffer.
		 * @return A new, cloned ByteBuffer.
		 */
		[[nodiscard]] Ptr<ByteBuffer> clone() const;

		/**
		 * Gets a pointer to the memory in the buffer.
		 * @tparam T The type of the pointer.
		 * @return The pointer.
		 */
		template<typename T>
		[[nodiscard]] T* data() const {
			return (T*) data();
		}

		/**
		 * Gets the size, in terms of a type, of the buffer.
		 * @tparam T The type to get the size in terms of.
		 * @return The size, in Ts, of the buffer.
		 */
		template<typename T>
		[[nodiscard]] size_t size() const {
			return size() / sizeof(T);
		}

		/**
		 * Gets a pointer to the memory in the buffer.
		 * @return The pointer.
		 */
		[[nodiscard]] void* data() const override;

		/**
		 * Gets the size of the buffer.
		 * @return The size, in bytes, of the buffer.
		 */
		[[nodiscard]] size_t size() const override;

	private:
		explicit ByteBuffer(void* ptr, size_t size);

		/**
		 * Allocates a new ByteBuffer. Copies will point to the same memory - use clone() to create a copy.
		 * @param size The size, in bytes, of the buffer.
		 */
		explicit ByteBuffer(size_t size);

		void* m_ptr;
		size_t m_size;
		bool m_free_on_destroy;
	};
}


