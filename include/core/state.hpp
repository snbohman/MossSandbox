#pragma once

#include <atomic>
#include <mutex>


/// Singleton-pattern-esque design ///
class State {
public:
    enum GameState {
        PLAYING,
        MENU
    };

    struct StateData {
        GameState gameState;
        float gameTime;
        
        StateData() : gameState(MENU), gameTime(0.0f) { }
    };

public:
    static State& getInstance();

    StateData const& getState() const;

    template<typename Func>
    void updateState(Func&& func);

private:
    std::atomic<StateData*> currentState;
    mutable std::mutex mtx;
};
