#include "node.h"

#include <iostream>
#include <sstream>

void test(Scene::Node::ptr_node_type const & __parent) {
    for(std::size_t i = 0 ; i < 100 ; i++) {
        std::ostringstream oss;
        oss << i;
        Scene::Node n(oss.str(), __parent);
    }
}

int main() {
    Scene::Node n;
    std::cout << n.id() << " | " << n.name() << " : "
        << n.child().size() << std::endl;
    return 0;
}
