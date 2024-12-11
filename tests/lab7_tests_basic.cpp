#include <gtest/gtest.h>
#include "game_basic.h"
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>

class GameTest : public ::testing::Test {
protected:
    void SetUp() override {
        game = std::make_unique<GameBasic>("test_log.txt");
    }

    void TearDown() override {
        if (game->IsRunning()) {
            game->StopGame();
        }
        std::remove("test_log.txt");
        std::remove("test_game_state.txt");
    }

    std::unique_ptr<GameBasic> game;
};

TEST_F(GameTest, AddNPC) {
    game->AddNPC("Bear", "TestBear", 100, 100);
    game->AddNPC("Elf", "TestElf", 20, 20);
    game->AddNPC("Robber", "TestRobber", 30, 30);

    std::stringstream output;
    auto old_buf = std::cout.rdbuf(output.rdbuf());
    
    game->PrintNPCs();
    
    std::cout.rdbuf(old_buf);

    EXPECT_TRUE(output.str().find("Bear TestBear at (100, 100)") != std::string::npos);
    EXPECT_TRUE(output.str().find("Elf TestElf at (20, 20)") != std::string::npos);
    EXPECT_TRUE(output.str().find("Robber TestRobber at (30, 30)") != std::string::npos);
}

TEST_F(GameTest, SaveAndLoadFromFile) {
    game->AddNPC("Bear", "TestBear", 100, 100);
    game->AddNPC("Elf", "TestElf", 20, 20);

    game->SaveToFile("test_game_state.txt");

    GameBasic loaded_game("test_log.txt");
    loaded_game.LoadFromFile("test_game_state.txt");

    std::stringstream output;
    auto old_buf = std::cout.rdbuf(output.rdbuf());
    
    loaded_game.PrintNPCs();
    
    std::cout.rdbuf(old_buf);

    EXPECT_TRUE(output.str().find("Bear TestBear at (100, 100)") != std::string::npos);
    EXPECT_TRUE(output.str().find("Elf TestElf at (20, 20)") != std::string::npos);
}

TEST_F(GameTest, ShortGameRun) {
    game->AddNPC("Bear", "TestBear", 10, 10);
    game->AddNPC("Elf", "TestElf", 15, 15);

    game->AddObserver(std::make_shared<ConsoleObserver>());
    game->AddObserver(std::make_shared<FileObserver>("test_log.txt"));

    std::thread gameThread([&]() {
        game->StartGame();
    });

    std::this_thread::sleep_for(std::chrono::seconds(2));
    game->StopGame();
    
    if (gameThread.joinable()) {
        gameThread.join();
    }

    std::ifstream log_file("test_log.txt");
    std::string log_content((std::istreambuf_iterator<char>(log_file)),
                          std::istreambuf_iterator<char>());

    EXPECT_TRUE(log_content.find("has been killed") != std::string::npos);
}

TEST_F(GameTest, InvalidNPCCoordinates) {
    EXPECT_THROW(game->AddNPC("Bear", "InvalidBear", -1, 100), std::invalid_argument);
    EXPECT_THROW(game->AddNPC("Elf", "InvalidElf", 100, NPC::MAP_SIZE + 1), std::invalid_argument);
}

TEST_F(GameTest, NPCMovementBounds) {
    game->AddNPC("Bear", "TestBear", NPC::MAP_SIZE - 5, NPC::MAP_SIZE - 5);
    
    std::thread gameThread([&]() {
        game->StartGame();
    });

    std::this_thread::sleep_for(std::chrono::seconds(1));
    game->StopGame();
    
    if (gameThread.joinable()) {
        gameThread.join();
    }

    std::stringstream output;
    auto old_buf = std::cout.rdbuf(output.rdbuf());
    game->PrintNPCs();
    std::cout.rdbuf(old_buf);


    std::string outputStr = output.str();
    EXPECT_TRUE(outputStr.find("TestBear") != std::string::npos);
    EXPECT_TRUE(outputStr.find("(100, 100)") == std::string::npos);
}