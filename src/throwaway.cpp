#include <moss/moss.hpp>
using namespace moss;


struct Counter { int value = 0; };

class Producer : public System {
public:
    void build(const Key<key::WRITE>& key) override {
        cmd::Resource<Counter>::init(key).emplace().value = 41;
    }
};

class Consumer : public System {
public:
    void build(const Key<key::WRITE>& key) override {
        M_INFO("counter = {}", cmd::Resource<Counter>::init(key).get().value); // expect 41
    }
    void tick(const Key<key::READ>& key) override {
        auto& c = cmd::Resource<Counter>::init(key).get();
        M_INFO("tick {}", c.value);
        if (++c.value > 43) cmd::Quit::init(key).quit();
    }
};

class TestContext : public Context {
public:
    void init(Mirror& mirror) override {
        mirror.connect<Producer, Consumer>();
    }
};

int main() {
    App app;
    app.init().mount<TestContext>().build().run().exit();
}
