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

	Copyright (c) Byteduck 2016-2021. All rights reserved.
*/

#pragma once

#include <sys/types.h>
#include <libduck/Stream.h>
#include <libduck/Result.h>
#include <libduck/DataSize.h>

namespace Sys::Mem {
	using Amount = Duck::DataSize;

	class Info {
	public:
		Amount usable;
		Amount used;
		Amount reserved;
		Amount kernel_virt;
		Amount kernel_phys;
		Amount kernel_heap;
		Amount kernel_disk_cache;

		inline double used_frac() const {
			return (double)((long double) used / (long double) usable);
		}

		inline double free_frac() const {
			return 1.0 - used_frac();
		}

		inline Amount free() const {
			return {(size_t) usable - (size_t) used};
		}

		inline Amount available() const {
			return {(size_t) usable - (size_t) used + (size_t) kernel_disk_cache};
		}

		inline double available_frac() const {
			return (double)((long double) available() / (long double) usable);
		}
	};

	Duck::ResultRet<Info> get_info(Duck::InputStream& file);
	Duck::ResultRet<Info> get_info();
}
