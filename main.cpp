#include "algo_hw2.hpp"

#include <vector>
#include <vector>
#include <vector>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iostream>
#include <vector>
#include <array>
#include <tuple>

#include <cstddef>
#include <cstdlib>

const std::array<int, 3> Empty{ -1, -1, -1 };
const std::array<int, 3> NIL{ 0, 0, 0 };

const int full_complete_size = 63;
std::vector<int> insert_tree(full_complete_size * 3 + 1, -1);
std::vector<int> delete_tree(full_complete_size * 3 + 1, -1);
std::vector<int> delete_check(full_complete_size * 3 + 1, -1);

#define USE_GOOGLE_TEST
#if defined(USE_GOOGLE_TEST)
#include <gtest/gtest.h>

TEST(AlgoHW2,Insert) {
	Insert(insert_tree.data(), 3);
	Insert(insert_tree.data(), 4);
	Insert(insert_tree.data(), 3);
	Insert(insert_tree.data(), 5);
	Insert(insert_tree.data(), 2);
	Insert(insert_tree.data(), 3);

	
	bool res = true;
	for (int i = 1; i < full_complete_size + 1; ++i) {
		res &= (delete_tree[3 * i - 2] == insert_tree[3 * i - 2]);
		res &= (delete_tree[3 * i - 1] == insert_tree[3 * i - 1]);
	}
	EXPECT_TRUE(res);

}


TEST(AlgoHW2,Delete) {

	Delete(delete_tree.data(), 3);
	Delete(delete_tree.data(), 4);
	Delete(delete_tree.data(), 3);
	Delete(delete_tree.data(), 5);
	Delete(delete_tree.data(), 2);
	Delete(delete_tree.data(), 3);

	bool res = true;
	for (int i = 1; i < full_complete_size + 1; ++i) {
		res &= (delete_tree[3 * i - 2] == delete_check[3 * i - 2]);
		res &= (delete_tree[3 * i - 1] == delete_check[3 * i - 1]);
	}
	EXPECT_TRUE(res);
}

TEST(AlgoHW2,Insert_Advance) {
	EXPECT_TRUE(std::equal(delete_tree.begin(), delete_tree.end(), insert_tree.begin()));
}

TEST(AlgoHW2,Delete_Advance) {
	EXPECT_TRUE(std::equal(delete_tree.begin(), delete_tree.end(), delete_check.begin()));

}


TEST(AlgoHW2,Rank) {
	EXPECT_EQ(18.0, Rank(insert_tree.data(), 3));
	EXPECT_EQ(18.0, Rank(delete_tree.data(), 3));
}
TEST(AlgoHW2,Select) {
	EXPECT_EQ(18.0, Rank(insert_tree.data(), 3));
	EXPECT_EQ(18.0, Select(delete_tree.data(),3));
}


#endif

int main(int argc, char **argv) {

	std::cout << student_id << "'s homework \n";

	using test_node = std::array<int, 3>;
	std::vector<test_node> input_nodes(full_complete_size + 1, Empty);
	std::vector<int> input_NIL_index{
		//
		// set the NIL nodes
		//
		8,9,10,11,24,25,26,30,31,54,55,56,57,58,59
	};
	for (auto index : input_NIL_index) {
		input_nodes[index] = NIL;
	}
	using mark_node = std::tuple<int, test_node>;
	std::vector<mark_node> input_tree_nodes{
		//
		// set red black tree nodes
		//
		// {place, data of the node}
		//
		mark_node( 1 ,{ 0, 5,14 } ),
		mark_node( 2 ,{ 0, 2, 3 } ),
		mark_node( 3, { 0, 30, 10 } ),
		mark_node( 4, { 0, 1, 1 } ),
		mark_node( 5, { 0, 3, 1 } ),
		mark_node( 6, { 1, 26, 4 } ),
		mark_node( 7, { 1, 41, 5 } ),
		mark_node( 12, { 0, 24, 1 } ),
		mark_node( 13, { 0, 28, 2 } ),
		mark_node( 14, { 0, 38, 3 } ),
		mark_node( 15, { 0, 47, 1 } ),
		mark_node( 27, { 1, 29, 1 } ),
		mark_node( 28, { 1, 35, 1 } ),
		mark_node( 29, { 1, 39, 1 } ),
	};

	for (auto tree_node : input_tree_nodes) {
		input_nodes[std::get<0>(tree_node)] = std::get<1>(tree_node);
	}

	delete_tree[0] = static_cast<int>(delete_tree.size());
	for (std::size_t i = 1; i < input_nodes.size(); ++i) {
		for (int j = 0;j < 3;++j) {
			delete_tree[3 * i + j - 2] = input_nodes[i][j];
		}
	}






#if defined(USE_GOOGLE_TEST)
	::testing::InitGoogleTest(&argc, argv);
	auto res = RUN_ALL_TESTS();
#endif

	std::cout << "\nstudent_id is " << student_id << "\n";
	system("pause");

}


