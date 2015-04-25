/*
 * TEST		     -- Execute the sentence right after it when test mode
 *			is on. Otherwise, ignore that sentence.
 *		
 * TEST_BLOCK()	     -- Execute all codes inside parentheses when test mode
 *			is on. Otherwise, ignore those codes.
 *
 * REPORT()	     -- Print information to console when test mode is on.
 *
 * SUPPRESS	     --	On automatic suppression mode, do the opposite of
 *			what TEST does. On manual suppression mode, when
 *			enable suppression option is on, ignore the sentence
 *			right after it. Otherwise, execute that sentence.
 *
 * SUPPRESS_BLOCK()  --	On automatic suppression mode, do the opposite of
 *                      what TEST_BLOCK() does. On manual suppression mode, 
 *                      when enable suppression option is on, ignore all
 *                      codes inside the parentheses. Otherwise, execute
 *			those codes.
 */
#ifndef TESTMODE
	#define TESTMODE 	 1 // Test Mode (1 = ON, 0 = OFF)
#endif
#if !defined(ENABLE_SUPPRESS) && 0 // Suppression Mode (1 = MAN, 0 = AUTO)
	#define ENABLE_SUPPRESS  0 // Enable Suppression (1 = ON, 0 = OFF)
#endif
#ifndef ENABLE_SUPPRESS
	#define DEFAULT_SUPPRESS
#else
	#if ENABLE_SUPPRESS
		#define SUPPRESS if(1);else
		#define SUPPRESS_BLOCK(...)
	#else
		#define SUPPRESS
		#define SUPPRESS_BLOCK(...) __VA_ARGS__
	#endif
#endif
#if TESTMODE
	#define TEST 
	#define TEST_BLOCK(...) __VA_ARGS__
	#define REPORT(...) printf(__VA_ARGS__);
	#ifdef DEFAULT_SUPPRESS
		#define SUPPRESS if(1);else
		#define SUPPRESS_BLOCK(...)
	#endif
#else
	#define TEST if(1);else 
	#define TEST_BLOCK(...)
	#define REPORT(...)
	#ifdef DEFAULT_SUPPRESS
		#define SUPPRESS
		#define SUPPRESS_BLOCK(...) __VA_ARGS__
	#endif
#endif
