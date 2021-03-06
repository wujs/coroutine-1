#ifndef _ORDINATOR_H__
#define _ORDINATOR_H__

#include "Common.h"
#include "Routine.h"

COROUTINE_NAMESPACE_START

class Schedule
{
public:
	Schedule(size_t stackSize = STACK_DEFAULT)
		:_current(-1)
		, _stackSize(stackSize)
#ifdef _MSC_VER
		, _main(ConvertThreadToFiber(nullptr))
#endif
	{

	}

	~Schedule()
	{
		for (auto &r : _routines)
			delete r;
		_routines.clear();
	}

	std::vector<coroutine::Routine*> _routines;
	std::queue<size_t> _indexes;
	size_t _current;
	size_t _stackSize;
#ifdef _MSC_VER
	LPVOID _main;
#else
	ucontext_t _main;
#endif
};

COROUTINE_NAMESPACE_END



#endif
