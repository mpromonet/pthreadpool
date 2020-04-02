#pragma once

#ifndef PTHREADPOOL_USE_CPUINFO
	#define PTHREADPOOL_USE_CPUINFO 0
#endif

#ifndef PTHREADPOOL_USE_FUTEX
	#if defined(__linux__)
		#define PTHREADPOOL_USE_FUTEX 1
	#elif defined(__EMSCRIPTEN__)
		#define PTHREADPOOL_USE_FUTEX 1
	#else
		#define PTHREADPOOL_USE_FUTEX 0
	#endif
#endif

/* Number of iterations in spin-wait loop before going into futex/condvar wait */
#define PTHREADPOOL_SPIN_WAIT_ITERATIONS 1000000

#define PTHREADPOOL_CACHELINE_SIZE 64
#define PTHREADPOOL_CACHELINE_ALIGNED __attribute__((__aligned__(PTHREADPOOL_CACHELINE_SIZE)))

#if defined(__clang__)
	#if __has_extension(c_static_assert) || __has_feature(c_static_assert)
		#define PTHREADPOOL_STATIC_ASSERT(predicate, message) _Static_assert((predicate), message)
	#else
		#define PTHREADPOOL_STATIC_ASSERT(predicate, message)
	#endif
#elif defined(__GNUC__) && ((__GNUC__ > 4) || (__GNUC__ == 4) && (__GNUC_MINOR__ >= 6))
	/* Static assert is supported by gcc >= 4.6 */
	#define PTHREADPOOL_STATIC_ASSERT(predicate, message) _Static_assert((predicate), message)
#else
	#define PTHREADPOOL_STATIC_ASSERT(predicate, message)
#endif

#ifndef PTHREADPOOL_INTERNAL
	#if defined(__ELF__)
		#define PTHREADPOOL_INTERNAL __attribute__((__visibility__("internal")))
	#elif defined(__MACH__)
		#define PTHREADPOOL_INTERNAL __attribute__((__visibility__("hidden")))
	#else
		#define PTHREADPOOL_INTERNAL
	#endif
#endif
