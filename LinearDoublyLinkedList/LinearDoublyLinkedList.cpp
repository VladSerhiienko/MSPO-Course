
#include "LinearDoublyLinkedList.h"

labworks::LinearDoublyLinkedListNode::LinearDoublyLinkedListNode()
    : host_list_owner(false)
    , user_data_owner(true)
    , host_list(nullptr)
{

}

labworks::LinearDoublyLinkedListNode::~LinearDoublyLinkedListNode()
{
    if (user_data_owner)
        delete user_data,
        user_data = nullptr;
}

void labworks::LinearDoublyLinkedListNode::attach_data(void * data)
{
    user_data = data;
}

void labworks::LinearDoublyLinkedListNode::attach_back(LinearDoublyLinkedList * list)
{
    assert(list != nullptr);
    if (list->get_last_node() == nullptr) 
        list->first_node = this;
    else
    {
        auto last_node = list->get_last_node();
        last_node->next_node = this;
        this->prev_node = last_node;
    }
}

void labworks::LinearDoublyLinkedListNode::attach_front(LinearDoublyLinkedList * list)
{
    assert(list != nullptr);
    auto first = list->first_node;

    list->first_node = this;
    this->next_node = first;
    first->prev_node = this;
}

void labworks::LinearDoublyLinkedListNode::attach_after(LinearDoublyLinkedListNode * attachee_node)
{
    assert(attachee_node != nullptr);

    auto next = attachee_node->next_node;
    attachee_node->next_node = this;
    next->prev_node = this;
    this->next_node = next;
    this->prev_node = attachee_node;
}

void labworks::LinearDoublyLinkedListNode::attach_before(LinearDoublyLinkedListNode * attachee_node)
{
    assert(attachee_node != nullptr);

    auto prev = attachee_node->prev_node;
    attachee_node->prev_node = this;
    prev->next_node = this;
    this->prev_node = prev;
    this->next_node = attachee_node;
}

labworks::LinearDoublyLinkedListNode *labworks::LinearDoublyLinkedListNode::create_new(void * user_data)
{
    auto node = new LinearDoublyLinkedListNode();
    node->attach_data(user_data);
    return node;
}

labworks::LinearDoublyLinkedList::LinearDoublyLinkedList()
    : first_node (nullptr)
{
}

labworks::LinearDoublyLinkedList::~LinearDoublyLinkedList()
{
    for_each_node([this](LinearDoublyLinkedListNode *&node)
    {
        if (node->host_list_owner)
            delete node,
            node = nullptr;
        return false;
    });
}

labworks::LinearDoublyLinkedListNode * labworks::LinearDoublyLinkedList::get_last_node()
{
    if (first_node == nullptr)
        return nullptr;

    auto last_node = first_node;
    while (last_node->next_node != nullptr)
        last_node = last_node->next_node;
    return last_node;
}
