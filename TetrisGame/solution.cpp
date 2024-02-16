#include "solution.h"




std::mutex fitness_mutex;

void Solution::fit(int num_of_simulations) {
    int num_simulations = num_of_simulations;
    const int num_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads(num_threads);

    auto simulateGame = [this]() {
        for (int i = 0; i < num_simulations; ++i) {
            int ticks_survived = 0;
            AITetrisGame game(0, 0, false, false);
            game.setAIWeights(max_height_penality, holes_penality, bumpiness_penality);
            while (!game.isGameOver()) {
                game.play(0);
                ticks_survived++;
            }
            {
                std::lock_guard<std::mutex> lock(fitness_mutex);
                fitness_score += static_cast<double>(ticks_survived) / 1000000;
            }
        }
        };

    // Start threads to run game simulations
    for (int i = 0; i < num_threads; ++i) {
        threads[i] = std::thread(simulateGame);
    }

    // Join threads to wait for them to finish
    for (int i = 0; i < num_threads; ++i) {
        threads[i].join();
    }
}



//void Solution::fit() {
//    const int num_simulations = 10;
//    const int num_threads = std::thread::hardware_concurrency();
//    std::vector<std::thread> threads(num_threads);
//
//    auto simulateGame = [&](int threadId) {
//        for (int i = threadId; i < num_simulations; i += num_threads) {
//            int ticks_survived = 0;
//            AITetrisGame game(0, 0, false, false);
//            game.setAIWeights(height_penalty, max_height_penality, holes_penality, bumpiness_penality);
//            while (!game.isGameOver()) {
//                game.play(0);
//                ticks_survived++;
//            }
//            fitness_score += static_cast<double>(ticks_survived) / 1000000;
//        }
//        };
//
//    // Start threads to run game simulations
//    for (int i = 0; i < num_threads; ++i) {
//        threads[i] = std::thread(simulateGame, i);
//    }
//
//    // Join threads to wait for them to finish
//    for (int i = 0; i < num_threads; ++i) {
//        threads[i].join();
//    }
//}