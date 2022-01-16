#pragma once
#include <Windows.h>

#include <cstdint>
#include <cstddef>

#define REFLOW_MEMORY_CONST(type) static constexpr type

#define REFLOW_MEMORY_PAGE_SIZE 4096
#define REFLOW_MEMORY_FIT(size)   (size + (4096 - (size % REFLOW_MEMORY_PAGE_SIZE)))

#define REFLOW_MEMORY_VMEM_RESERVE(ptr, size) ::VirtualAlloc(ptr, size, MEM_RESERVE, PAGE_READWRITE)
#define REFLOW_MEMORY_VMEM_COMMIT(ptr, size)  ::VirtualAlloc(ptr, size, MEM_COMMIT , PAGE_READWRITE)

#define REFLOW_MEMORY_FAIL_IF(cond, ret)  if(cond) return ret;
#define REFLOW_MEMORY_THROW_IF(cond, thr) if(cond) throw  thr; 