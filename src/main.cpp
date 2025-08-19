#include <moss/extensions/raylib/meta.hpp>
#include <moss/moss.hpp>


class CubeContext : public moss::Context {
public:
    virtual void init(moss::Mirror& mirror) {
        mirror.create().attach<moss::extensions::raylib::RectRenderable>(
            moss::extensions::raylib::Transform(
                200, 200
            ),
            moss::extensions::raylib::RectShape(
                100, 100
            ),
            moss::extensions::raylib::Albedo(
                0.5, 0.5, 0.5
            )
        );
    };
};


int main() {
    moss::App app;
    app.init()
        .mount<moss::extensions::raylib::Renderer>()
        .mount<CubeContext>()
        .build()
        .run()
        .exit();
}
