#include <Arduino.h>
#include <unity.h>

void printMultiline(const String &message, String lines[], int &lineCount);

void test_single_line_message()
{
    String message = "Hello World";
    String lines[10];
    int lineCount;

    printMultiline(message, lines, lineCount);

    TEST_ASSERT_EQUAL(1, lineCount);
    TEST_ASSERT_EQUAL_STRING("Hello World", lines[0].c_str());
}

void test_multiline_message()
{
    String message = "Hello\nWorld\nTesting";
    String lines[10];
    int lineCount;

    printMultiline(message, lines, lineCount);

    TEST_ASSERT_EQUAL(3, lineCount);
    TEST_ASSERT_EQUAL_STRING("Hello", lines[0].c_str());
    TEST_ASSERT_EQUAL_STRING("World", lines[1].c_str());
    TEST_ASSERT_EQUAL_STRING("Testing", lines[2].c_str());
}
