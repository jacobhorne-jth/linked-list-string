#include <gtest/gtest.h>

#include "list.hpp"

using namespace std;
using list::Node;

TEST(ListTests, FromStringBasic) {
    Node* const foo_list_head = list::from_string("foo");
    Node* foo_list = foo_list_head;

    EXPECT_EQ(foo_list->data, 'f');
    // ASSERT instead of EXPECT means: end the test here if this fails, do not try to continue
    // running. This is useful to prevent early crashes.
    ASSERT_NE(foo_list->next, nullptr);

    foo_list = foo_list->next;
    EXPECT_EQ(foo_list->data, 'o');
    ASSERT_NE(foo_list->next, nullptr);

    foo_list = foo_list->next;
    EXPECT_EQ(foo_list->data, 'o');
    ASSERT_EQ(foo_list->next, nullptr);

    list::free(foo_list_head);
}

TEST(ListTests, Length) {
    Node* const head = list::from_string("foo");
    EXPECT_EQ(list::length(head), 3);
    list::free(head);
}

// Add remaining tests below. All tests should follow
// the format of `TEST(ListTests, <TestName>){}`.


TEST(ListTests, Print)
{
    Node* head = list::from_string("jacob");
    ostringstream out;

    list::print(out, head);

    EXPECT_EQ(out.str(), "jacob");

    list::free(head);
}


TEST(ListTests, Copy)
{
    Node* original1 = list::from_string("foo");
    Node* copied1 = list::copy(original1);

    EXPECT_EQ(list::compare(original1, copied1), 0);

    list::free(original1);
    list::free(copied1);

    Node* original2 = list::from_string("j");
    Node* copied2 = list::copy(original2);

    EXPECT_EQ(list::compare(original2, copied2), 0);

    list::free(original2);
    list::free(copied2);

    Node* original3 = list::from_string("");
    Node* copied3 = list::copy(original3);

    EXPECT_EQ(list::compare(original3, copied3), 0);

    list::free(original3);
    list::free(copied3);

}

TEST(ListTests, Compare)
{
    Node* first = list::from_string("foo");
    Node* second = list::from_string("foo");
    Node* third = list::from_string("foooooo");

    EXPECT_EQ(list::compare(first, second), 0);
    EXPECT_LT(list::compare(first, third), 0);
    EXPECT_GT(list::compare(third, second), 0);

    list::free(first);
    list::free(second);
    list::free(third);

    Node* empty = list::from_string("");
    Node* nonempty = list::from_string("a");

    EXPECT_LT(list::compare(empty, nonempty), 0);
    EXPECT_GT(list::compare(nonempty, empty), 0);
    EXPECT_EQ(list::compare(empty, list::from_string("")), 0);

    list::free(empty);
    list::free(nonempty);

    Node* upper = list::from_string("XYZ");
    Node* lower = list::from_string("xyz");

    EXPECT_LT(list::compare(upper, lower), 0);
    EXPECT_GT(list::compare(lower, upper), 0);

    list::free(upper);
    list::free(lower);

    Node* a = list::from_string("awesome");
    Node* z = list::from_string("zooanimals");

    EXPECT_LT(list::compare(a, z), 0);
    EXPECT_GT(list::compare(z, a), 0);

    list::free(a);
    list::free(z);
}

TEST(ListTests, CompareWithN)
{
    Node* first = list::from_string("foofoo");
    Node* second = list::from_string("foozzz");
    Node* third = list::from_string("fooaaa");


    EXPECT_EQ(list::compare(first, second, 3), 0);
    EXPECT_LT(list::compare(first, second, 5), 0);
    EXPECT_GT(list::compare(first, third, 4), 0);


    list::free(first);
    list::free(second);
    list::free(third);

    Node* empty = list::from_string("");
    Node* nonempty = list::from_string("a");

    EXPECT_LT(list::compare(empty, nonempty, 1), 0);
    EXPECT_GT(list::compare(nonempty, empty, 1), 0);
    EXPECT_EQ(list::compare(empty, list::from_string(""), 1), 0);

    list::free(empty);
    list::free(nonempty);

    Node* upper = list::from_string("XYZ");
    Node* lower = list::from_string("xyz");

    EXPECT_LT(list::compare(upper, lower, 3), 0);
    EXPECT_GT(list::compare(lower, upper, 3), 0);

    list::free(upper);
    list::free(lower);

    Node* a = list::from_string("awesome");
    Node* z = list::from_string("zooanimals");

    EXPECT_LT(list::compare(a, z, 7), 0);
    EXPECT_GT(list::compare(z, a, 7), 0);

    list::free(a);
    list::free(z);
}

TEST(ListTests, Reverse)
{
    Node* original1 = list::from_string("foo");
    Node* copied1 = list::copy(original1);
    Node* reversed1 = list::reverse(copied1);

    EXPECT_EQ(reversed1->data, 'o');
    EXPECT_EQ(reversed1->next->data, 'o');
    EXPECT_EQ(reversed1->next->next->data, 'f');
    EXPECT_EQ(reversed1->next->next->next, nullptr);

    list::free(original1); 
    list::free(copied1);
    list::free(reversed1);

    Node* original2 = list::from_string("");
    Node* copied2 = list::copy(original2);
    Node* reversed2 = list::reverse(copied2);

    EXPECT_EQ(reversed2, nullptr);

    list::free(original2); 
    list::free(copied2);
    list::free(reversed2);
}

TEST(ListTests, Append)
{
    Node* first1 = list::from_string("foo");
    Node* second1 = list::from_string("abc");
    Node* combined1 = list::append(first1, second1);
    Node* expected1 = list::from_string("fooabc");
    EXPECT_EQ(list::compare(combined1, expected1), 0);

    list::free(first1);
    list::free(second1);
    list::free(combined1);
    list::free(expected1);

    Node* first2 = list::from_string("");
    Node* second2 = list::from_string("");
    Node* combined2 = list::append(first2, second2);
    Node* expected2 = list::from_string("");
    EXPECT_EQ(list::compare(combined2, expected2), 0);

    list::free(first2);
    list::free(second2);
    list::free(combined2);
    list::free(expected2);

    Node* first3 = list::from_string("");
    Node* second3 = list::from_string("abc");
    Node* combined3 = list::append(first3, second3);
    Node* expected3 = list::from_string("abc");
    EXPECT_EQ(list::compare(combined3, expected3), 0);

    list::free(first3);
    list::free(second3);
    list::free(combined3);
    list::free(expected3);

    Node* first4 = list::from_string("abc");
    Node* second4 = list::from_string("");
    Node* combined4 = list::append(first4, second4);
    Node* expected4 = list::from_string("abc");
    EXPECT_EQ(list::compare(combined4, expected4), 0);

    list::free(first4);
    list::free(second4);
    list::free(combined4);
    list::free(expected4);
}

TEST(ListTests, Index)
{
    Node* head = list::from_string("foo");
    EXPECT_EQ(list::index(head, head->next), 1);
    list::free(head);

    Node* test = list::from_string("foo");
    EXPECT_EQ(list::index(test, test), 0);
    list::free(test);
}

TEST(ListTests, FindChar) 
{
    Node* head = list::from_string("hello");
    Node* found = list::find_char(head, 'e');

    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->data, 'e');

    Node* not_found = list::find_char(head, 'z');
    EXPECT_EQ(not_found, nullptr);

    list::free(head);
}

TEST(ListTests, FindList) 
{
    Node* haystack = list::from_string("mississippi");
    Node* needle = list::from_string("sis");

    Node* matching = list::find_list(haystack, needle);
    ASSERT_NE(matching, nullptr);
    EXPECT_EQ(matching->data, 's');

    Node* missing = list::from_string("foo");
    EXPECT_EQ(list::find_list(haystack, missing), nullptr);

    list::free(haystack);
    list::free(needle);
    list::free(missing);
}

TEST(ListTests, Nth)
{
    Node* head = list::from_string("hellothere");
    Node* n = list::nth(head, 4);

    ASSERT_NE(n, nullptr);
    EXPECT_EQ(n->data, 'o');

    list::free(head);
}

TEST(ListTests, Last)
{
    Node* head = list::from_string("foo");
    Node* last_node = list::last(head);

    ASSERT_NE(last_node, nullptr);
    EXPECT_EQ(last_node->data, 'o');
    EXPECT_EQ(last_node->next, nullptr);

    list::free(head);
}