//---------------------------------------------------------------------------------
// AStar.h
//---------------------------------------------------------------------------------
#include "..\stdafx.h"
#include <vector>
#include <unordered_map>
#include <limits>

class CAstar {
	struct Node {
		struct Hash;
		Node() = default;
		Node(int row, int col, int moveX, int moveY) : Row(row), Col(col), MoveX(moveX), MoveY(moveY) {}
		int Row;
		int Col;
		int MoveX;
		int MoveY;

		bool operator==(const Node& node) const {
			return node.Row == Row && node.Col == Col && node.MoveX == MoveX && node.MoveY == MoveY;
		}

		struct Hash {
			size_t operator()(const Node& node) const {
				return static_cast<size_t>(node.Col + node.Row + static_cast<float>(node.MoveX + node.MoveY));
			}
		};
	};
	
public:
	static void GetMove(int sourceRow, int sourceCol, int destRow, int destCol, int& moveX, int& moveY);
	static int CalculateHeuristic(int x, int y, int destX, int destY);
	static Node GetStartOfPath(std::unordered_map<Node, Node, Node::Hash> nodeToParentInCheapestPath, Node node);
	static std::vector<Node> GetSuccessors(Node node);
};