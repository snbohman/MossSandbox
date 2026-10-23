#include <moss/extensions/vulkan.hpp>
#include <moss/meta/logs.hpp>
#include <moss/moss.hpp>

using namespace moss;

// Same layout as the push_constant block in every validate shader (16 bytes)
struct Params {
    f32 time;
    f32 width;
    f32 height;
    f32 frame;
};

// Writes component data PassSystem reads, so it connects BEFORE PassSystem
class ParamsSystem : public System {
public:
    void tick(const Key<key::READ>& key) override {
        vk::RenderCore& core = cmd::Resource<vk::RenderCore>::init(key).get();

        auto rows = cmd::Query<
            With<vk::PushConstants>,
            cmd::View<Include<vk::PushConstants>>
        >::init(key).atlas();

        for (auto [pc] : rows) {
            Params& params = pc.as<Params>();
            params.time = static_cast<f32>(glfwGetTime());
            params.width = static_cast<f32>(core.drawImage.imageExtent.width);
            params.height = static_cast<f32>(core.drawImage.imageExtent.height);
            // At tick time frameNumber is the index of the frame being recorded
            params.frame = static_cast<f32>(core.frame.frameNumber);
        }
    }
};

class ValidateContext : public Context {
public:
    void init(Mirror& mirror) override {
        const Params initial{ 0.0f, 1280.0f, 720.0f, 0.0f };

        mirror
            .connect<
                vk::Core, vk::FrameBegin, vk::ImageSystem, ParamsSystem, vk::PassSystem, vk::FrameEnd
            >()
            .create()
                .attach<vk::WindowSettings>("moss validate", 1280, 720, 60, true)   // resizable
                .attach<vk::RendererSettings>(true)
                .attach<vk::HotReload>(500u)   // check 8: poll the SPIR-V files every 500 ms
            // Resources
            .create().attach<vk::SimImage>("fieldA").attach<vk::ImageExtent>(256u, 256u).attach<vk::DoubleBuffered>()
            .create().attach<vk::SimImage>("fieldB").attach<vk::ImageExtent>(256u, 256u).attach<vk::DoubleBuffered>()
            .create().attach<vk::SimBuffer>("counter", u64(256)).attach<vk::DoubleBuffered>()
            // Pass 0: Once seed, writes both double-buffered images
            .create()
                .attach<vk::ComputeShader>("shaders/validate/seed.comp.spv")
                .attach<vk::Bind>(vk::write(0, "fieldA"), vk::write(1, "fieldB"))
                .attach<vk::Dispatch>("fieldA")
                .attach<vk::Once>()
            // Pass 1: compute writes the draw image (follows the window)
            .create()
                .attach<vk::ComputeShader>("shaders/validate/background.comp.spv")
                .attach<vk::Bind>(vk::write(0, "draw"))
                .attach<vk::Dispatch>("draw")
                .attach<vk::PushConstants>(initial)
            // Pass 2: even Repeat
            .create()
                .attach<vk::ComputeShader>("shaders/validate/diffuse.comp.spv")
                .attach<vk::Bind>(vk::read(0, "fieldA"), vk::write(1, "fieldA"))
                .attach<vk::Dispatch>("fieldA")
                .attach<vk::Repeat>(4u)
                .attach<vk::PushConstants>(initial)
            // Pass 3: odd Repeat (the read side flips every frame)
            .create()
                .attach<vk::ComputeShader>("shaders/validate/diffuse.comp.spv")
                .attach<vk::Bind>(vk::read(0, "fieldB"), vk::write(1, "fieldB"))
                .attach<vk::Dispatch>("fieldB")
                .attach<vk::Repeat>(5u)
                .attach<vk::PushConstants>(initial)
            // Pass 4: buffer ping-pong, odd Repeat
            .create()
                .attach<vk::ComputeShader>("shaders/validate/count.comp.spv")
                .attach<vk::Bind>(vk::storage(0, "counter"), vk::storageWrite(1, "counter"))
                .attach<vk::Dispatch>(1u)
                .attach<vk::Repeat>(3u)
            // Pass 5: graphics, no Bind
            .create()
                .attach<vk::VertexShader>("shaders/gradient/fullscreen.vert.spv")
                .attach<vk::FragmentShader>("shaders/validate/strip.frag.spv")
                .attach<vk::PipelineState>(
                    VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, VkCullModeFlags(VK_CULL_MODE_NONE),
                    VK_FRONT_FACE_COUNTER_CLOCKWISE, true
                )
                .attach<vk::PushConstants>(initial)
            // Pass 6: display, binds both fields and the buffer (3 double-buffered resources, 8 sets)
            .create()
                .attach<vk::VertexShader>("shaders/gradient/fullscreen.vert.spv")
                .attach<vk::FragmentShader>("shaders/validate/display.frag.spv")
                .attach<vk::Bind>(
                    vk::sample(0, "fieldA"), vk::sample(1, "fieldB"), vk::storage(2, "counter")
                )
                .attach<vk::PipelineState>(
                    VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, VkCullModeFlags(VK_CULL_MODE_NONE),
                    VK_FRONT_FACE_COUNTER_CLOCKWISE, true
                )
                .attach<vk::PushConstants>(initial)
            // Pass 7: hot reload target. Graphics, no Bind, drawn last (on top): a
            // 96 px pulsing swatch in the top-right corner. Edit reload.frag while
            // the program runs; push constants keep working after a reload
            .create()
                .attach<vk::VertexShader>("shaders/gradient/fullscreen.vert.spv")
                .attach<vk::FragmentShader>("shaders/validate/reload.frag.spv")
                .attach<vk::PipelineState>(
                    VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, VkCullModeFlags(VK_CULL_MODE_NONE),
                    VK_FRONT_FACE_COUNTER_CLOCKWISE, true
                )
                .attach<vk::PushConstants>(initial);
    }
};

int main() {
    App app;
    app.init()
        .mount<ValidateContext>()
        .build()
        .run()
        .exit();
}
