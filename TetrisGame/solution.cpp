#include "solution.h"


void Solution::fit() {
    const int num_simulations = 10;
    const int num_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads(num_threads);

    auto simulateGame = [&](int threadId) {
        for (int i = threadId; i < num_simulations; i += num_threads) {
            int ticks_survived = 0;
            AITetrisGame game(0, 0, false, false);
            game.setAIWeights(height_penalty, max_height_penality, holes_penality, bumpiness_penality);
            while (!game.isGameOver()) {
                game.play(0);
                ticks_survived++;
            }
            fitness_score += static_cast<double>(ticks_survived) / 1000000;
        }
        };

    // Start threads to run game simulations
    for (int i = 0; i < num_threads; ++i) {
        threads[i] = std::thread(simulateGame, i);
    }

    // Join threads to wait for them to finish
    for (int i = 0; i < num_threads; ++i) {
        threads[i].join();
    }
}



//void Solution::fit() {
//
//	for (int i = 0; i < 10; i++){
//		int ticks_survived = 0;
//		AITetrisGame game(0, 0, false, false);
//		game.setAIWeights(height_penalty, max_height_penality, holes_penality, bumpiness_penality);
//		while (!game.isGameOver())
//		{
//			game.play(0);
//			ticks_survived++;
//		}
//		fitness_score += ((double)ticks_survived) /1000000;
//		// fitness_score =  0 - std::abs(10000 - ticks_survived)/100;
//		// fitness_score =  0 - std::abs(100 - ticks_survived)/100;
//	}
//};