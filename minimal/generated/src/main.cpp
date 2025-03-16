#include <moss/moss.hpp>
#include <minimal/ecs/ecs.hpp>

int main() {
    spdlog::set_level(spdlog::level::debug);
    moss::App app;

    moss::types::AttachmentRegistry attachmentRegistry;
    app.buildAttachmentRegistry(attachmentRegistry);

    REGISTER_TAG(minimal::cmp::PlayerTag);

    app.setAttachmentRegistry(attachmentRegistry);

    /* Custom Input */
    app.init({.dataDirectory = "mossSandbox/minimal/data"});

    app.addScene("scene1", true);
    app.run();
}
