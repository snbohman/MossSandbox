#include <moss/extensions/vulkan.hpp>
#include <moss/meta/logs.hpp>
#include <moss/moss.hpp>

using namespace moss;

// Same layout as the push_constant block in gradient.frag
struct GradientParams {
    f32 time;
    f32 mousex;
    f32 mousey;
    f32 width;
    f32 height;
    f32 pad;
};

// Writes component data PassSystem reads, so it connects BEFORE PassSystem
class TimeSystem : public System {
public:
    void tick(const Key<key::READ>& key) override {
        GLFWwindow* window = cmd::Resource<
            vk::RenderCore
        >::init(key).get().foundation.window;
        double x, y;
        glfwGetCursorPos(window, &x, &y);

        auto rows = cmd::Query<
            With<vk::PushConstants>,
            cmd::View<Include<vk::PushConstants>>
        >::init(key).atlas();

        for (auto [pc] : rows) {
            pc.as<GradientParams>().time = static_cast<f32>(glfwGetTime());
            pc.as<GradientParams>().mousex = static_cast<f32>(x);
            pc.as<GradientParams>().mousey = static_cast<f32>(y);
        }
    }

};

class GradientContext : public Context {
public:
    void init(Mirror& mirror) override {
        mirror
            .connect<vk::Core, vk::FrameBegin, TimeSystem, vk::PassSystem, vk::FrameEnd>()
            .create()
                .attach<vk::WindowSettings>("moss", 1280, 720)
                .attach<vk::RendererSettings>(true)
            .create()   // one graphics pass: vertex + fragment, no Bind, no Dispatch
                .attach<vk::VertexShader>("shaders/gradient/fullscreen.vert.spv")
                .attach<vk::FragmentShader>("shaders/gradient/gradient.frag.spv")
                .attach<vk::PushConstants>(GradientParams{ 0.0f, 0, 0, 1280, 720, 0.0f });
    }
};

int main() {
    App app;
    app.init()
        .mount<GradientContext>()
        .build()
        .run()
        .exit();
}
