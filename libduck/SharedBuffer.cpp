/*
	.
*/

#include "SharedBuffer.h"
#include "Log.h"
using namespace Duck;

ResultRet<Duck::Ptr<SharedBuffer>> SharedBuffer::alloc(size_t size, std::string name) {
	shm shm_info;
	if(shmcreate_named(nullptr, size, &shm_info, name.c_str()))
		return Result(errno);
	return Ptr<SharedBuffer>(new SharedBuffer(shm_info));
}

ResultRet<Duck::Ptr<SharedBuffer>> SharedBuffer::adopt(int id) {
	shm shm_info;
	if(shmattach(id, nullptr, &shm_info))
		return Result(errno);
	return Ptr<SharedBuffer>(new SharedBuffer(shm_info));
}

SharedBuffer::SharedBuffer(shm shm_info): m_shm(shm_info) {

}

SharedBuffer::~SharedBuffer() noexcept {
	if(shmdetach(m_shm.id) < 0)
		Duck::Log::warnf("Duck::SharedBuffer: Failed to detach shm: {}", strerror(errno));
}

ResultRet<Duck::Ptr<SharedBuffer>> SharedBuffer::copy(std::string name) const {
	auto cpy_res = alloc(m_shm.size, std::move(name));
	if(cpy_res.is_error())
		return cpy_res.result();
	memcpy(cpy_res.value()->ptr(), ptr(), m_shm.size);
	return std::move(cpy_res.value());
}

int SharedBuffer::allow(int pid, bool read, bool write) {
	return shmallow(m_shm.id, pid, (read ? SHM_READ : 0) | (write ? SHM_WRITE : 0));
}
