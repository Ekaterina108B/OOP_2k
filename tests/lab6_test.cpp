#include <gtest/gtest.h>
#include "game.h"
#include <fstream>
#include <sstream>

class GameTest : public ::testing::Test {
protected:
    void SetUp() override {
        game = std::make_unique<Game>("test_log.txt");
    }

    void TearDown() override {
        std::remove("test_log.txt");
        std::remove("test_game_state.txt");
    }

    std::unique_ptr<Game> game;
};

TEST_F(GameTest, AddNPC) {
    game->AddNPC("Bear", "TestBear", 100, 100);
    game->AddNPC("Elf", "TestElf", 200, 200);
    game->AddNPC("Robber", "TestRobber", 300, 300);

    std::stringstream output;
    auto old_buf = std::cout.rdbuf(output.rdbuf());
    game->printNPCs();
    std::cout.rdbuf(old_buf);

    EXPECT_TRUE(output.str().find("Bear TestBear at (100, 100)") != std::string::npos);
    EXPECT_TRUE(output.str().find("Elf TestElf at (200, 200)") != std::string::npos);
    EXPECT_TRUE(output.str().find("Robber TestRobber at (300, 300)") != std::string::npos);
}

TEST_F(GameTest, SaveAndLoadFromFile) {
    Game loaded_game("test_log.txt");
    
    game->AddNPC("Bear", "TestBear", 100, 100);
    game->AddNPC("Elf", "TestElf", 200, 200);
    game->SaveToFile("test_game_state.txt");
    loaded_game.LoadFromFile("test_game_state.txt");

    std::stringstream output;
    auto old_buf = std::cout.rdbuf(output.rdbuf());
    loaded_game.PrintNPC();
    std::cout.rdbuf(old_buf);

    EXPECT_TRUE(output.str().find("Bear TestBear at (100, 100)") != std::string::npos);
    EXPECT_TRUE(output.str().find("Elf TestElf at (200, 200)") != std::string::npos);
}

TEST_F(GameTest, RunBattle) {
    game->AddNPC("Bear", "TestBear", 100, 100);
    game->AddNPC("Elf", "TestElf", 200, 200);
    game->AddNPC("Robber", "TestRobber", 300, 300);
    game->AddObserver(std::make_shared<ConsoleObserver>());
    game->AddObserver(std::make_shared<FileObserver>("test_log.txt"));

    game->RunBattle(150);

    std::ifstream log_file("test_log.txt");
    std::string log_content((std::istreambuf_iterator<char>(log_file)),
                            std::istreambuf_iterator<char>());

    EXPECT_TRUE(log_content.find("has been killed") != std::string::npos);
}

TEST_F(GameTest, InvalidNPCCoordinates) {
    EXPECT_THROW(game->AddNPC("Bear", "InvalidBear", -1, 100), std::invalid_argument);
    EXPECT_THROW(game->AddNPC("Elf", "InvalidElf", 100, 501), std::invalid_argument);
}