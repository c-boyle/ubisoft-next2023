//---------------------------------------------------------------------------------
// AStar.h
//---------------------------------------------------------------------------------
#include "..\stdafx.h"
#include <vector>

class CAstar {
	struct Node {
		struct Hash;
		Node(int row, int col, float moveX, float moveY) : Row(row), Col(col), MoveX(moveX), MoveY(moveY) {}
		int Row;
		int Col;
		float MoveX;
		float MoveY;

		bool operator==(const Node& node) {
			return node.Row == Row && node.Col == Col && node.MoveX == MoveX && node.MoveY == MoveY;
		}

		struct Hash {
			size_t operator()(const Node& node) const {
				return static_cast<size_t>(node.Col + node.Row + static_cast<float>(node.MoveX + node.MoveY));
			}
		};
	};

	static void GetMove(int sourceX, int sourceY, int destX, int destY, int& moveX, int& moveY);

	static int CalculateHeuristic(int x, int y, int destX, int destY);

	static Node GetStartOfPath(std::unordered_map<Node, Node, Node::Hash> nodeToParentInCheapestPath, Node node);

	static std::vector<Node> GetSuccessors(Node node, int destRow, int destCol);
};