#pragma once
#include <Windows.h>

#include <cstddef>
#include <cstdint>

#define REFLOW_FORMAT_ALIGNED_STRUCT(bytes, name) struct alignas(bytes) name

#define REFLOW_FORMAT_FILE_CREATE(name) CreateFileA(name, GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_NEW   , 0, NULL)
#define REFLOW_FORMAT_FILE_OPEN(name)   CreateFileA(name, GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL)

#define REFLOW_DEVICE_OPEN(name) REFLOW_FORMAT_FILE_OPEN(name)