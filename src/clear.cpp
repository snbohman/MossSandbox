#include <moss/extensions/vulkan.hpp>
#include <moss/moss.hpp>
using namespace moss;

class RenderContext : public Context {
public:
    void init(Mirror& mirror) override {
        mirror
            .connect<vk::Core, vk::FrameBegin, vk::ClearAttachment, vk::FrameEnd>()
            .create()
                .attach<vk::WindowSettings>("moss", 400, 200, 60, false)
                .attach<vk::RendererSettings>(true);
    }
};

int main() { App app; app.init().mount<RenderContext>().build().run().exit(); }
