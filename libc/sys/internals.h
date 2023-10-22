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

#ifndef DUCKOS_LIBC_INTERNALS_H
#define DUCKOS_LIBC_INTERNALS_H

extern void _init();
extern void _fini();

int __cxa_atexit(void (*exit_function)(void*), void* parameter, void* dso_handle);
void __cxa_finalize(void* dso_handle);
__attribute__((noreturn)) void __cxa_pure_virtual() __attribute__((weak));
__attribute__((noreturn)) void __stack_chk_fail();

#endif //DUCKOS_LIBC_INTERNALS_H
