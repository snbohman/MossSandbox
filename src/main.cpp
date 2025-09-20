#include <moss/extensions/raylib/meta.hpp>
#include <moss/moss.hpp>


struct BlueTag : public moss::Component{ };
struct GreenTag : public moss::Component { };

class RenderableMovement : public moss::System {
public:
    void tick(const moss::Key<moss::key::READ>& key, const moss::DynamicView& view) override {
        if (IsKeyDown(KEY_Q)) {
            moss::cmd::Quit::init(key).quit();
        }

        i8 velx = 0;
        i8 vely = 0;
        if (IsKeyDown(KEY_LEFT)) velx -= 5;
        else if (IsKeyDown(KEY_RIGHT)) velx += 5;
        else if (IsKeyDown(KEY_UP)) vely -= 5;
        else if (IsKeyDown(KEY_DOWN)) vely += 5;

        if (velx != 0 || vely != 0) {
            auto blueAtlas = moss::cmd::Query<
                moss::With< moss::extensions::raylib::RectRenderable >,
                moss::cmd::View<
                    moss::Include<GreenTag>
                >
            >::init(key).atlas();

            auto greenAtlas = moss::cmd::Query<
                moss::With< moss::extensions::raylib::RectRenderable >,
                moss::cmd::View<
                    moss::Include<BlueTag>
                >
            >::init(key).atlas();

            f32 multiplier = 0;
            for (const auto& [rect] : blueAtlas) {
                rect.transform.x += velx * multiplier;
                rect.transform.y += vely * multiplier;

                multiplier += 0.3;
            }

            multiplier = 0;
            for (const auto& [rect] : greenAtlas) {
                rect.transform.x += velx * multiplier;
                rect.transform.y += vely * multiplier;

                multiplier += 0.3;
            }
        }
    }
};

class CubeContext : public moss::Context {
public:
    virtual void init(moss::Mirror& mirror) {
        mirror
            .create(10)
                .attach<moss::extensions::raylib::RectRenderable>(
                    moss::extensions::raylib::Transform( 200, 200 ),
                    moss::extensions::raylib::RectShape( 300, 200 ),
                    moss::extensions::raylib::Albedo( 0.5, 0.2, 0.5, 0.2 )
                )
                .attach<BlueTag>()
            .create(10)
                .attach<moss::extensions::raylib::RectRenderable>(
                    moss::extensions::raylib::Transform( 200, 500 ),
                    moss::extensions::raylib::RectShape( 300, 200 ),
                    moss::extensions::raylib::Albedo( 0.2, 0.5, 0.5, 0.2 )
                )
                .attach<GreenTag>()
            .connect<RenderableMovement>();
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
