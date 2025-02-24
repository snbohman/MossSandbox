#include <core/state.hpp>


State& State::getInstance() {
    static State instance;
    return instance;
}

State::StateData const& State::getState() const {
    return *currentState.load();
}

template<typename Func>
void State::updateState(Func&& func) {
    std::lock_guard<std::mutex> lock(mtx);
    auto currentStatePtr = currentState.load();
    auto newState = std::make_unique<StateData>(*currentStatePtr);
    func(*newState);
    currentState.store(newState.release());
}
