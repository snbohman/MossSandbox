// Expermimental forward look
class FluidContext : public Context {
public:
    void init(Mirror& mirror) override {
        mirror
            .connect<vk::Core, vk::FrameBegin, vk::ImageSystem, vk::PassSystem, vk::FrameEnd>()
            .create()
                .attach<vk::WindowSettings>("moss", 1280, 720)
                .attach<vk::RendererSettings>(true)
            .create().attach<vk::Image>("velocity").attach<vk::Scale>(0.5f).attach<vk::DoubleBuffered>()
            .create().attach<vk::Image>("pressure").attach<vk::DoubleBuffered>()
            .create().attach<vk::Image>("divergence")
            .create()   // pressure solve
                .attach<vk::Compute>("shaders/jacobi.comp.spv")
                .attach<vk::Bind>(vk::sample("pressure"), vk::sample("divergence"), vk::write("pressure"))
                .attach<vk::Dispatch>(vk::over("pressure"))
                .attach<vk::Repeat>(20)
            .create()   // display
                .attach<vk::Fragment>("shaders/display.frag.spv")
                .attach<vk::Bind>(vk::sample("dye"));
    }
};
