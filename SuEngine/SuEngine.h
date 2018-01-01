#pragma once

#ifdef SU_ENGINE_EXPORTS
#define SU_API __declspec(dllexport)
#else
#define SU_API __declspec(dllimport)
#endif