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

#ifndef DUCKOS_LIBC_SYSCALL_H
#define DUCKOS_LIBC_SYSCALL_H

#include <kernel/syscall/syscall_numbers.h>
#include "cdefs.h"

__DECL_BEGIN

int syscall(int call);
int syscall_noerr(int call);
int syscall2(int call, int b);
int syscall2_noerr(int call, int b);
int syscall3(int call, int b, int c);
int syscall3_noerr(int call, int b, int c);
int syscall4(int call, int b, int c, int d);
int syscall4_noerr(int call, int b, int c, int d);

__DECL_END

#endif //DUCKOS_LIBC_SYSCALL_H
