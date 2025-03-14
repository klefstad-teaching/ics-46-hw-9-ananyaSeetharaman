#include <gtest/gtest.h>

#include "../src/dijkstras.h"
#include "../src/ladder.h"

TEST(DijkstraTests, SimpleGraphTest) {
  Graph G;
  G.numVertices = 5;
  G.resize(5);
  G[0].push_back(Edge(0, 1, 2));
  G[0].push_back(Edge(0, 2, 4));
  G[1].push_back(Edge(1, 2, 1));
  G[1].push_back(Edge(1, 3, 7));
  G[2].push_back(Edge(2, 4, 3));
  G[3].push_back(Edge(3, 4, 1));
  
  vector<int> previous;
  vector<int> distances = dijkstra_shortest_path(G, 0, previous);
  
  EXPECT_EQ(distances[4], 6);
  
  vector<int> path = extract_shortest_path(distances, previous, 4);
  vector<int> expectedPath = {0, 1, 2, 4};
  EXPECT_EQ(path, expectedPath);
}

TEST(DijkstraTests, NoPathTest) {
  Graph G;
  G.numVertices = 3;
  G.resize(3);
  G[0].push_back(Edge(0, 1, 5));
  
  vector<int> previous;
  vector<int> distances = dijkstra_shortest_path(G, 0, previous);

  EXPECT_EQ(distances[2], INF);
  
  vector<int> path = extract_shortest_path(distances, previous, 2);
  EXPECT_TRUE(path.empty());
}


// Ladder tests
TEST(LadderTests, IsAdjacentTest) {
  EXPECT_TRUE(is_adjacent("apple", "appl"));
  EXPECT_TRUE(is_adjacent("appl", "apple"));
  EXPECT_TRUE(is_adjacent("apple", "bapple"));
  EXPECT_TRUE(is_adjacent("zoom", "zoo"));
  EXPECT_TRUE(is_adjacent("apple", "apple"));
}

TEST(LadderTests, GenerateWordLadderFoundTest) {
  std::set<std::string> dict = {"cat", "bat", "bet", "bed", "at", "ad", "ed"};
  
  vector<string> ladder = generate_word_ladder("cat", "bed", dict);

  ASSERT_FALSE(ladder.empty());
  EXPECT_EQ(ladder.front(), "cat");
  EXPECT_EQ(ladder.back(), "bed");
}

TEST(LadderTests, GenerateWordLadderNotFoundTest) {
  std::set<std::string> dict = {"hello", "help", "hell"};
  
  vector<string> ladder = generate_word_ladder("hello", "world", dict);
  EXPECT_TRUE(ladder.empty());
}

TEST(LadderTests, PrintWordLadderOutputTest) {
  std::vector<std::string> ladder = {"awake", "aware", "ware", "were", "wee", "see", "seep", "sleep"};
  
  std::stringstream ss;
  std::streambuf* orig_buf = std::cout.rdbuf();
  std::cout.rdbuf(ss.rdbuf());
  
  print_word_ladder(ladder);
  
  std::cout.rdbuf(orig_buf);
  
  std::string output = ss.str();
  std::string expected = "Word ladder found: awake aware ware were wee see seep sleep \n";
  EXPECT_EQ(output, expected);
}

TEST(LadderTests, PrintWordLadderNoLadderTest) {
  std::vector<std::string> ladder;
  
  std::stringstream ss;
  std::streambuf* orig_buf = std::cout.rdbuf();
  std::cout.rdbuf(ss.rdbuf());
  
  print_word_ladder(ladder);
  
  std::cout.rdbuf(orig_buf);
  
  std::string output = ss.str();
  std::string expected = "No word ladder found.\n";
  EXPECT_EQ(output, expected);
}