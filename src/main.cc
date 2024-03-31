#include <vksetup/application.hh>

#include <memory>
#include <iostream>

int main(int, char**) {
    using namespace vksetup;

    auto ptr{ std::make_unique<application>() };


    try {
        if (ptr->init()) {
            ptr->run();
        }
    } catch (const std::exception& e) {
        std::cerr << "Excep. what: " << e.what() << std::endl;
    }


    return 0;
}