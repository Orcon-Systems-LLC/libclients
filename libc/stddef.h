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
    
    Copyright (c) Byteduck 2016-2020. All rights reserved.
*/

#ifndef DUCKOS_LIBC_STDDEF_H
#define DUCKOS_LIBC_STDDEF_H

#include <sys/cdefs.h>
#include <kernel/api/stddef.h>

__DECL_BEGIN

#ifdef __cplusplus
#define NULL nullptr
#else
#define NULL ((void*)0)
typedef int wchar_t;
#endif

__DECL_END

#endif //DUCKOS_LIBC_STDDEF_H
