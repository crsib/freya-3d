#ifndef CORE_H_
#define CORE_H_
//Core
#include "core/EngineCore.h"

#include "core/EngineSubsystem.h"
#include "core/EString.h"
#include "core/EStringList.h"
#include "core/Utils/FromString.hpp"
//Memory
#include "core/memory/MemoryArena.h"
//Filesystem
#include "core/filesystem/Filesystem.h"
//Driver development
#include "core/drivermodel/DriverID.h"
//multithreading
#include "core/multithreading/Thread.h"
#include "core/multithreading/ThreadID.h"
#include "core/multithreading/Mutex.h"
#include "core/multithreading/Condition.h"
#include "core/multithreading/RingBuffer.h"
#include "core/multithreading/ThreadBlocks.h"
#include "core/multithreading/Runnable.h"
//Task managemet
#include "core/taskmanager/Task.h"
#include "core/taskmanager/TaskManager.h"
#include "core/taskmanager/Shutdown.h"
#endif /*CORE_H_*/
