/*
	.
*/

#pragma once

#include <sys/shm.h>
#include <memory>
#include "Result.h"
#include "Object.h"
#include "Serializable.h"

namespace Duck {
	class SharedBuffer: public Duck::Object {
	public:
		DUCK_OBJECT_DEF(SharedBuffer);

		~SharedBuffer() noexcept;

		static ResultRet<Duck::Ptr<SharedBuffer>> alloc(size_t size, std::string name);
		static ResultRet<Duck::Ptr<SharedBuffer>> adopt(int id);

		[[nodiscard]] ResultRet<Duck::Ptr<SharedBuffer>> copy(std::string name) const;
		int allow(int pid, bool read = true, bool write = true);

		[[nodiscard]] void* ptr() const { return m_shm.ptr; }
		[[nodiscard]] size_t size() const { return m_shm.size; }
		[[nodiscard]] int id() const { return m_shm.id; }

		template<typename T>
		[[nodiscard]] T* ptr() const { return (T*) m_shm.ptr; }
		template<typename T>
		[[nodiscard]] size_t size() const { return size() / sizeof(T); }

	private:
		explicit SharedBuffer(struct shm shm_info);

		struct shm m_shm = {nullptr, 0, 0};
	};
}


