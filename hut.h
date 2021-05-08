
/**
 * Header only Unit Tests for C
 *
 * @file        hut.h
 * @author	ustaslive
 * @created	2020/11/19
 */

#ifndef __HUT_H
#define __HUT_H

#include <stdio.h>
#include <string.h>


#define CHK_LONG_EQ(expected, actual) do {\
		TEST_STAT.checks_done++;\
		long _expected = expected;\
		long _actual = actual;\
		if (_expected!=_actual){\
			TEST_STAT.checks_fail++;\
			printf("Failed in test %s (%s:%d)\n"\
				"\tExpected (%s): %ld\n"\
				"\tActual (%s): %ld\n" \
				,__func__, __FILE__, __LINE__,\
				#expected, _expected, #actual, _actual);\
			goto out;\
		}\
		else {TEST_STAT.checks_ok++;}\
	} while(0)
#define CHK_INT_EQ(expected, actual) do {\
		TEST_STAT.checks_done++;\
		int _expected = expected;\
		int _actual = actual;\
		if (_expected!=_actual){\
			TEST_STAT.checks_fail++;\
			printf("Failed in test %s (%s:%d)\n"\
				"\tExpected (%s): %d\n"\
				"\tActual (%s): %d\n" \
				,__func__, __FILE__, __LINE__,\
				#expected, _expected, #actual, _actual);\
			goto out;\
		}\
		else {TEST_STAT.checks_ok++;}\
	} while(0)

#define CHK_PTR_EQ(expected, actual) do {\
		TEST_STAT.checks_done++;\
		void *_expected = expected;\
		void *_actual = actual;\
		if (_expected!=_actual){\
			TEST_STAT.checks_fail++;\
			printf("Failed in test %s (%s:%d)\n"\
				"\tExpected (%s): %p\n"\
				"\tActual (%s): %p\n" \
				,__func__, __FILE__, __LINE__,\
				#expected, _expected, #actual, _actual);\
			goto out;\
		}\
		else {TEST_STAT.checks_ok++;}\
	} while(0)

#define CHK_PTR_NE(not_expected, actual) do {\
		TEST_STAT.checks_done++;\
		void *_not_expected = expected;\
		void *_actual = actual;\
		if (_not_expected==_actual){\
			TEST_STAT.checks_fail++;\
			printf("Failed in test %s (%s:%d)\n"\
				"\tNot expected (%s): %p\n"\
				"\tActual (%s): %p\n" \
				,__func__, __FILE__, __LINE__,\
				#not_expected, _not_expected,\
				#actual, _actual);\
			goto out;\
		}\
		else {TEST_STAT.checks_ok++;}\
	} while(0)

#define CHK_STR_EQ(expected, actual) do {\
		TEST_STAT.checks_done++;\
		char _expected[50000] = {'\0'};\
		char _actual[50000] = {'\0'};\
		strncpy(_expected, expected, sizeof(_expected));\
		_expected[sizeof(_expected)-1] = '\0';\
		strncpy(_actual, actual, sizeof(_actual));\
		_actual[sizeof(_actual)-1] = '\0';\
		if (0 != strcmp(_expected,_actual)){\
		TEST_STAT.checks_fail++;\
		printf("Failed in test %s (%s:%d)\n"\
				"\tExpected (%s): '%s'\n"\
				"\tActual (%s): '%s'\n" \
				,__func__, __FILE__, __LINE__,\
				#expected, _expected, #actual, _actual);\
			goto out;\
		}\
		else {TEST_STAT.checks_ok++;}\
	} while(0)

#define CHK_DBL_EQ(expected, actual) do {\
	} while(0)

#define HUT_INIT()	_hut_init()
#define HUT_RESULTS()	_hut_results()
#define HUT_TEST_BEGIN(testname)	_hut_test_begin(testname)
#define HUT_TEST_END(testname)	_hut_test_end(testname)

#define HUT_RUN(groupname, testname) _hut_run_test(testname,\
			_hut_test_group_setup_##groupname,\
			_hut_test_group_teardown_##groupname,\
			#testname)

#define HUT_GROUP_SETUP(groupname) void _hut_test_group_setup_##groupname(void)
#define HUT_GROUP_TEARDOWN(groupname) void _hut_test_group_teardown_##groupname(void)


typedef struct test_stat_t
{
	int	checks_done;
	int	checks_ok;
	int	checks_fail;
	int	tests_done;
	int	tests_ok;
	int	tests_fail;

	int	saved_checks_fail;
} test_stat_t;

static test_stat_t TEST_STAT;

static void _hut_init(void)
{
	memset(&TEST_STAT, 0, sizeof(TEST_STAT));
}

static void _hut_results(void)
{
	printf("Tests(%d=%d+%d), Checks(%d=%d+%d)\n",
		TEST_STAT.tests_done,
		TEST_STAT.tests_ok,
		TEST_STAT.tests_fail,
		TEST_STAT.checks_done,
		TEST_STAT.checks_ok,
		TEST_STAT.checks_fail
		);
	if ( TEST_STAT.checks_fail || TEST_STAT.tests_fail )
	{
		printf("FAILURE\n");
	}
	else
	{
		printf("SUCCESS\n");
	}
}

static void _hut_test_begin(const char *test_name)
{
	printf("Executing test '%s'\n", test_name);
	TEST_STAT.saved_checks_fail = TEST_STAT.checks_fail;
}

static void _hut_test_end(const char *test_name)
{
	printf("Test '%s' completed\n", test_name);
	TEST_STAT.tests_done++;
	if ( TEST_STAT.saved_checks_fail < TEST_STAT.checks_fail )
	{
		TEST_STAT.tests_fail++;
	}
	else
	{
		TEST_STAT.tests_ok++;
	}
}

static void _hut_run_test(void (*test_to_execute)(void),
			void (*group_setup)(void),
			void (*group_teardown)(void),
			const char *testname)
{
	HUT_TEST_BEGIN(testname);
	group_setup();
	test_to_execute();
	group_teardown();
	HUT_TEST_END(testname);

}

#endif /* __HUT_H */
