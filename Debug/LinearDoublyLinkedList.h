#pragma once

#include <assert.h>

namespace labworks
{
    class LinearDoublyLinkedList;
    class LinearDoublyLinkedListNode
    {
        friend LinearDoublyLinkedList;

        bool host_list_owner;
        bool user_data_owner;
        LinearDoublyLinkedList *host_list;

    public:
        void *user_data;

    public:
        LinearDoublyLinkedListNode *prev_node;
        LinearDoublyLinkedListNode *next_node;

    public:
        LinearDoublyLinkedListNode();
        ~LinearDoublyLinkedListNode();

        void attach_data(void *data);
        void attach_back(LinearDoublyLinkedList *attachee_list);
        void attach_front(LinearDoublyLinkedList *attachee_list);
        void attach_after(LinearDoublyLinkedListNode *attachee_node);
        void attach_before(LinearDoublyLinkedListNode *attachee_node);

    public:
        static LinearDoublyLinkedListNode *create_new(void *user_data);

    };

    class LinearDoublyLinkedList
    {
    public:
        LinearDoublyLinkedListNode *first_node;

    public:
        LinearDoublyLinkedList();
        ~LinearDoublyLinkedList();
        LinearDoublyLinkedListNode *get_last_node();

    public:
        // _TyCallback signature: 'bool (LinearDoublyLinkedListNode *node)'
        template <typename _TyCallback> void for_each_node(_TyCallback callback)
        {
            auto last_node = first_node;
            auto next_node = last_node;
            while (last_node != nullptr)
            {
                next_node = last_node->next_node;
                if (callback(last_node)) break;
                else last_node = next_node;
            }
        }

        template <typename _TyNodeContext> LinearDoublyLinkedListNode *new_add_back(_TyNodeContext *context)
        {
            if (auto new_node = LinearDoublyLinkedListNode::create_new(reinterpret_cast<void*>(context)))
            {
                new_node->host_list = this;
                new_node->host_list_owner = true;

                new_node->attach_back(this);
                return new_node;
            }

            return nullptr;
        }

    };


}

