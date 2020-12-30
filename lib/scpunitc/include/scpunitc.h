/**
 * @file scpunitc.h
 * @author Nathan Seymour
 * @brief A basic header-file only testing library, designed for
 * cross-platform use.
 */

#ifndef SCPUNITC_H
#define SCPUNITC_H

#include <stdlib.h>
#include <string.h>

// Test results
#define TEST_OK 0
#define TEST_FAILED_ASSERT_EQ 1
#define TEST_FAILED_ASSERT_TRUE 2
#define TEST_FAILED_ASSERT_STR_EQ 3

// Printing
#ifdef SILENT_TESTING
#define PRINT(...) while(0) {}
#else
#include <stdio.h>
#define PRINT(...) printf(__VA_ARGS__)
#endif

static char _has_error = 0;

typedef struct {
    int result;
    int passed_assertions;
} test_results;

typedef void (*scpunitc_test)(test_results*);

typedef struct {
    int tests_allocated_size;
    int tests_count;
    scpunitc_test *tests;
    char **test_names;
} test_suite;

#define TEST_SUITE(suite_name) void scpunitc_suite_##suite_name(test_suite* suite)

#define DEFINE_SUITE(suite_name) extern void scpunitc_suite_##suite_name(test_suite* suite)

#define TEST(test_name) static void scpunitc_test_##test_name(test_results *_test_results)

#define ADD_TEST(test_name) \
    { \
        suite->tests_count++; \
        if(suite->tests_allocated_size > suite->tests_count) \
        { \
            suite->tests_allocated_size += 5; \
            suite->tests = realloc(suite->tests, suite->tests_allocated_size * sizeof(scpunitc_test)); \
            suite->test_names = realloc(suite->test_names, suite->tests_allocated_size * sizeof(char*)); \
        } \
        suite->tests[suite->tests_count - 1] = scpunitc_test_##test_name; \
        suite->test_names[suite->tests_count - 1] = #test_name; \
    }

#define RUN_TEST(test_function, test_name) \
    {                       \
        test_results results;              \
        results.result = 0;                \
        results.passed_assertions = 0;\
        PRINT("\t- Test %s\n", test_name); \
        test_function(&results); \
        if(results.result == 0)             \
        { \
            PRINT("\tTest %s PASSED with %i assertions\n", test_name, results.passed_assertions); \
        }                   \
        else                \
        {                   \
            _has_error = 1; \
            PRINT("\t Test %s FAILED with code %i\n", test_name, results.result);\
        }\
    }

#define RUN_SUITE(suite_name) \
    {                         \
        test_suite suite;     \
        suite.tests = malloc(5 * sizeof(scpunitc_test)); \
        suite.test_names = malloc(5 * sizeof(char*));\
        suite.tests_allocated_size = 5;                  \
        suite.tests_count = 0; \
        PRINT("\nTest Suite %s\n", #suite_name); \
        scpunitc_suite_##suite_name(&suite);   \
        for(int i = 0; i < suite.tests_count; i++) \
        {                     \
            RUN_TEST(suite.tests[i], suite.test_names[i]); \
        }                     \
        free(suite.tests);    \
        free(suite.test_names);\
    }

// ASSERT_EQ
#define ASSERT_EQ_MSG(left, right, assert_statement) \
    PRINT("\t\t- %s", assert_statement); \
    if((left) != (right)) \
    { \
        _test_results->result = TEST_FAILED_ASSERT_EQ; \
        PRINT(" FAILED\n"); \
        PRINT("\t\tREASON: \"%s\" should be equal to \"%s\", but it is not.\n", #left, #right); \
        PRINT("\t\t\tINT value of left: %i\n", (int)(left));                                    \
        PRINT("\n"); \
        return; \
    } \
    else \
    { \
        PRINT(" PASSED\n"); \
        _test_results->passed_assertions++; \
    }
#define ASSERT_EQ(left, right) ASSERT_EQ_MSG(left, right, "Assert values to be equal.")

// ASSERT_STR_EQ
#define ASSERT_STR_EQ_MSG(left, right, assert_statement) \
    PRINT("\t\t- %s", assert_statement); \
    if(strcmp((left), (right)) != 0) \
    { \
        _test_results->result = TEST_FAILED_ASSERT_STR_EQ; \
        PRINT(" FAILED\n"); \
        PRINT("\t\tREASON: \"%s\" should be equal to \"%s\", but it is not.\n", #left, #right); \
        PRINT("\t\t\tSTRING value of left : %s\n", (char*)(left)); \
        PRINT("\t\t\tSTRING value of right: %s\n", (char*)(right)); \
        PRINT("\n"); \
        return; \
    } \
    else \
    { \
        PRINT(" PASSED\n"); \
        _test_results->passed_assertions++; \
    }
#define ASSERT_STR_EQ(left, right) ASSERT_STR_EQ_MSG(left, right, "Assert strings to be equal.")

// ASSERT_TRUE
#define ASSERT_TRUE_MSG(expression, assert_statement) \
    PRINT("\t\t- %s", assert_statement); \
    if(!(expression)) \
    { \
        _test_results->result = TEST_FAILED_ASSERT_TRUE; \
        PRINT(" FAILED\n"); \
        PRINT("\t\tREASON: \"%s\" should be true, but it is not.\n\n", #expression); \
        return; \
    } \
    else \
    {                                               \
        PRINT(" PASSED\n"); \
        _test_results->passed_assertions++; \
    }
#define ASSERT_TRUE(expression) ASSERT_TRUE_MSG(expression, "Assert to be true.")

#endif //SCPUNITC_H
