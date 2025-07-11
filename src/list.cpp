#include "list.hpp"
#include <iostream>
using namespace std;


namespace list 
{

Node* from_string(const char *s) 
{
    if(s == nullptr || s[0] == '\0')
    {
        return nullptr;
    }

    Node* head = new Node{s[0], nullptr};
    Node* curr = head;

    for (int i = 1; s[i] != '\0'; ++i)
    {
        curr->next = new Node{s[i], nullptr};
        curr = curr->next;
    }

    return head;
}

void free(Node* head)
{
    for (Node* curr = head; curr != nullptr;)
    {
        Node* next = curr->next;
        delete curr;
        curr = next;
    }
}

void print(ostream& out, Node* head)
{
    for(Node* curr = head; curr != nullptr; curr = curr->next) 
    {
        out << curr->data;
    }
}

Node* copy(Node* head)
{
    if (head == nullptr)
    {
        return nullptr;
    }

    Node* new_head = new Node{head->data, nullptr};
    Node* curr_new = new_head;

    for (Node* curr_old = head->next; curr_old != nullptr; curr_old = curr_old->next)
    {
        curr_new->next = new Node{curr_old->data, nullptr};
        curr_new = curr_new->next;
    }

    return new_head;
}

int compare(Node* lhs, Node* rhs)
{
    for (; lhs != nullptr && rhs != nullptr; lhs = lhs->next, rhs = rhs->next)
    {
        if (lhs->data != rhs->data)
        {
            return lhs->data - rhs->data;
        }
    }
    if (lhs == nullptr && rhs == nullptr)
    {
        //if they both reached null at same
        return 0;
    }

    //checks if one ended before the other because cant compare data
    if (lhs == nullptr)
    {
        return -1;
    } 
    else
    {
        return 1;
    }
}

int compare(Node* lhs,  Node* rhs, int n)
{
    for (int i = 0; i < n; ++i) 
    {
        if (lhs == nullptr && rhs == nullptr)
        {
            return 0;
        }

        if (lhs == nullptr)
        {
            return -1;
        }

        if (rhs == nullptr)
        {
            return 1;
        }

        if (lhs->data != rhs->data)
        {
            return lhs->data - rhs->data;
        }

        lhs = lhs->next;
        rhs = rhs->next;
    }
    return 0;
}

int length(Node* head)
{
    int count = 0;
    for (Node* curr = head; curr != nullptr; curr = curr->next)
    {
        count += 1;
    }
    return count;
}

Node* reverse(Node* head)
{
    Node* reversed = nullptr;

    for(Node* curr = head; curr != nullptr; curr = curr->next)
    {
        Node* node = new Node{curr->data, reversed};
        reversed = node;
    }
    return reversed;
}

Node* append(Node* lhs, Node* rhs)
{
    if (lhs == nullptr)
    {
        return copy(rhs);
    }

    if (rhs == nullptr)
    {
        return copy(lhs);
    }

    Node* result = new Node{lhs->data, nullptr};
    Node* curr_result = result;

    for (Node* curr = lhs->next; curr != nullptr; curr = curr->next)
    {
        curr_result->next = new Node{curr->data, nullptr};
        curr_result = curr_result->next;
    }

    for(Node* curr = rhs; curr != nullptr; curr = curr->next)
    {
        curr_result->next = new Node{curr->data, nullptr};
        curr_result = curr_result->next;
    }

    return result;
}

int index(Node* head, Node* node)
{
    int index = 0;
    for (Node* curr = head; curr != nullptr; curr = curr->next)
    {
        if (curr == node)
        {
            return index;
        }
        ++index;
    }

    return -1;
}

Node* find_char(Node* head, char c)
{
    for (Node* curr = head; curr != nullptr; curr = curr->next)
    {
        if (curr->data == c) {
            return curr;
        }
    }
    return nullptr;
}

Node* find_list(Node* haystack, Node* needle)
{
    if (needle == nullptr) 
    {
        return haystack;
    }

    int haystack_len = length(haystack);
    int needle_len = length(needle);

    if (needle_len == 0 || needle_len > haystack_len)
    {
        return nullptr;
    }

    for (Node* curr = haystack; curr != nullptr; curr = curr->next)
    {
        if (compare(curr, needle, needle_len) == 0)
        {
            return curr;
        }
    }
    return nullptr;

}

Node* nth(Node* head, int n)
{
    int index = 0;
    for(Node* curr = head; curr != nullptr; curr = curr->next)
    {
        if (index == n)
        {
            return curr;
        }
        ++index;
    }
    return nullptr;
}

Node* last(Node* head)
{
    if (head == nullptr)
    {
        return nullptr;
    }

    Node* curr = head;
    for (; curr->next != nullptr; curr = curr->next)
    {
    }
    return curr;
}
}