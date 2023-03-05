//---------------------------------------------------------------------------------
// AStar.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "AStar.h"
#include "GameLevel.h"
#include <set>

void CAstar::GetMove(int sourceRow, int sourceCol, int destRow, int destCol, int& moveX, int& moveY)
{
	Node startNode = Node(sourceRow, sourceCol, 0, 0);

	std::unordered_map<Node, int, Node::Hash> nodeToCheapestPathCost;
	std::unordered_map<Node, Node, Node::Hash> nodeToParentInCheapestPath;
	std::unordered_map<Node, int, Node::Hash> nodeToBestGuessCost;

	nodeToCheapestPathCost[startNode] = 0;
	nodeToBestGuessCost[startNode] = CalculateHeuristic(sourceRow, sourceCol, destRow, destCol);

	auto cmp = [&](Node node1, Node node2) {
		if (nodeToBestGuessCost.count(node1) == 0) {
			return false;
		}
		else if (nodeToBestGuessCost.count(node2) == 0) {
			return true;
		}
		else {
			return nodeToBestGuessCost[node1] < nodeToBestGuessCost[node2];
		}
	};

	std::set<Node, decltype(cmp)> frontier(cmp);
	frontier.emplace(startNode);

	while (!frontier.empty()) {
		Node node = *(frontier.begin());

		bool isGoal = node.Row == destRow && node.Col == destCol;
		if (isGoal) {
			Node moveNode = GetStartOfPath(nodeToParentInCheapestPath, node);
			moveX = moveNode.MoveX;
			moveY = moveNode.MoveY;
			return;
		}

		frontier.erase(node);

		for (auto& successor : GetSuccessors(node)) {
			int dist = nodeToCheapestPathCost[node] + 1;
			if (nodeToCheapestPathCost.count(successor) == 0 || dist < nodeToCheapestPathCost[successor]) {
				nodeToParentInCheapestPath[successor] = node;
				nodeToCheapestPathCost[successor] = dist;
				nodeToBestGuessCost[successor] = dist + CalculateHeuristic(successor.Row, successor.Col, destRow, destCol);
				frontier.emplace(successor);
			}
		}
	}

	moveX = 0;
	moveY = 0;
}

int CAstar::CalculateHeuristic(int row, int col, int destRow, int destCol)
{
	int manhattanDistance = abs(row - destRow) + abs(col - destCol);
	return manhattanDistance;
}

CAstar::Node CAstar::GetStartOfPath(std::unordered_map<Node, Node, Node::Hash> nodeToParentInCheapestPath, Node node)
{
	Node startNode = node;
	while (node.MoveX != 0 && node.MoveY != 0) {
		startNode = node;
		node = nodeToParentInCheapestPath[node];
	}
	return startNode;
}

std::vector<CAstar::Node> CAstar::GetSuccessors(Node node)
{
	std::vector<Node> successors;

	// Check left
	int newRow, newCol;
	newRow = node.Row;
	newCol = node.Col - 1;
	CLevelCell* cell = CGameLevel::GetInstance().GetLevelCell(newRow, newCol);
	if (cell != nullptr && !cell->Blocked()) {
		int moveX, moveY;
		moveX = -1;
		moveY = 0;
		auto successor = Node(newRow, newCol, moveX, moveY);
		successors.push_back(successor);
	}

	// Check right
	newRow = node.Row;
	newCol = node.Col + 1;
	cell = CGameLevel::GetInstance().GetLevelCell(newRow, newCol);
	if (cell != nullptr && !cell->Blocked()) {
		int moveX, moveY;
		moveX = 1;
		moveY = 0;
		auto successor = Node(newRow, newCol, moveX, moveY);
		successors.push_back(successor);
	}

	// Check up
	newRow = node.Row + 1;
	newCol = node.Col;
	cell = CGameLevel::GetInstance().GetLevelCell(newRow, newCol);
	if (cell != nullptr && !cell->Blocked()) {
		int moveX, moveY;
		moveX = 0;
		moveY = 1;
		auto successor = Node(newRow, newCol, moveX, moveY);
		successors.push_back(successor);
	}

	// Check down
	newRow = node.Row - 1;
	newCol = node.Col;
	cell = CGameLevel::GetInstance().GetLevelCell(newRow, newCol);
	if (cell != nullptr && !cell->Blocked()) {
		int moveX, moveY;
		moveX = 0;
		moveY = -1;
		auto successor = Node(newRow, newCol, moveX, moveY);
		successors.push_back(successor);
	}

	return successors;
}