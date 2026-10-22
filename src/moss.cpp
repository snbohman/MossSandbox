#include <moss/moss.hpp>


int main() {
    moss::App app;
    app
        .init()
        .build()
        .run()
        .exit();
}