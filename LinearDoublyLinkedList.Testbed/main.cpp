
#include <iostream>

#include <LinearDoublyLinkedList.h>
using namespace labworks;

struct NodeContext
{
    int id;
};

int main(int argc, char *argv[])
{
    LinearDoublyLinkedList list;

    for (auto i = 0; i < 100; i++)
        list.new_add_back<NodeContext>(new NodeContext { i } );

    list.for_each_node([&](LinearDoublyLinkedListNode *node)
    {
        auto context = reinterpret_cast<NodeContext*>(node->user_data);
        std::cout << "element id: " << context->id << std::endl;
        return false;
    });

    return 0;
}



