#pragma once

#ifdef OPTICSENSORLIBEXPORTING
#	define OPTICSENSOR_API __declspec(dllexport)
#else
#	define OPTICSENSOR_API __declspec(dllimport)
#endif