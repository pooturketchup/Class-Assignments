#include "PathSearch.h"
#include <iostream>

namespace fullsail_ai { namespace algorithms {

	PathSearch::PathSearch()
	{
		tileMap = nullptr;
	}

	PathSearch::~PathSearch()
	{
		//shutdown();
	}

	double PathSearch::distance(double x, double x2, double y, double y2) {
		double deltaX = x2 - x;
		double deltaY = y2 - y;
		deltaX = deltaX * deltaX;
		deltaY = deltaY * deltaY;
		double result = (double)sqrtf((deltaX + deltaY));
		return result;
	}

	//unsigned int BreakIntoBits(unsigned int hexValue1, unsigned int hexValue2, float R) {
	//	unsigned int red1 = ((hexValue1 >> 16) & 0xFF);
	//	unsigned int green1 = ((hexValue1 >> 8) & 0xFF);
	//	unsigned int blue1 = ((hexValue1) & 0xFF);
	//	unsigned int red2 = ((hexValue2 >> 16) & 0xFF);
	//	unsigned int green2 = ((hexValue2 >> 8) & 0xFF);
	//	unsigned int blue2 = ((hexValue2) & 0xFF);
	//	unsigned int interpolate = (unsigned int)(red2 - red1) * (unsigned int)R + red1 << 16 |
	//		(unsigned int)(green2 - green1) * (unsigned int)R + green1 << 8 | (unsigned int)(blue2 - blue1) * (unsigned int)R + blue1;
	//	return interpolate;
	//}


	void PathSearch::initialize(TileMap* _tileMap)
	{
		tileMap = _tileMap;
		copyMap = tileMap;
		//Done = false;
		col = tileMap->getColumnCount();
		row = tileMap->getRowCount();
		Tile* tile;
		SearchNode* node;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				//create all nodes in tile Map then assign neighbors
				
				//nodes are not passed in correctly that is why A* does not work
				
				tile = tileMap->getTile(i, j);
				//if (tile->getWeight() != 0)
				//{
					nodes[tile] = new SearchNode();
					nodes[tile]->tile = tile;
				//}
				
			}
		}
		
		int w,hc, c;
		int cost;
		Tile* top, *bottom, *left, *right, *tl, *tr, *bl, *br;//adj;
		SearchNode* next, *test;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				tile = tileMap->getTile(i, j);
				c = tile->getWeight();
				next = nodes[tile];
				if (c != 0)
				{
					
				
				//find 6 neighbors for odd and even rows
				if (i % 2 == 0) {//check if a tile is 0 weight don't push
					//if you want to fix the nodes just check nodes[tileMap index] != nullptr

					if (tileMap->getTile(i - 1, j - 1) != nullptr && tileMap->getTile(i - 1, j - 1)->getWeight() > 0)
					{
						bl = tileMap->getTile(i - 1, j - 1);
						//next = nodes[bl];
						//nodes[tile]->neighbors.push_back(next);
						next->neighbors.push_back(nodes[bl]);
					}


					if (tileMap->getTile(i + 1, j - 1) != nullptr && tileMap->getTile(i + 1, j - 1)->getWeight() > 0)// && tileMap->getTile(i + 1, j - 1)->getWeight() != 0)
					{
						tl = tileMap->getTile(i + 1, j - 1);
						//next = nodes[tl];
						//nodes[tile]->neighbors.push_back(next);
						next->neighbors.push_back(nodes[tl]);
					}
				}													   
				else {	

					if (tileMap->getTile(i + 1, j + 1) != nullptr && tileMap->getTile(i + 1, j + 1)->getWeight() > 0)// && tileMap->getTile(i + 1, j + 1)->getWeight() != 0)
					{
						tr = tileMap->getTile(i + 1, j + 1);
						//next = nodes[tr];
						//nodes[tile]->neighbors.push_back(next);
						next->neighbors.push_back(nodes[tr]);
					}


					if (tileMap->getTile(i - 1, j + 1) != nullptr && tileMap->getTile(i - 1, j + 1)->getWeight() > 0)// && tileMap->getTile(i - 1, j + 1)->getWeight() != 0)
					{
						br = tileMap->getTile(i - 1, j + 1);
						//next = nodes[br];
						//nodes[tile]->neighbors.push_back(next);
						next->neighbors.push_back(nodes[br]);
					}
				}

				if (tileMap->getTile(i + 1, j) != nullptr && tileMap->getTile(i + 1, j)->getWeight() > 0)
				{
					top = tileMap->getTile(i + 1, j);
					//next = nodes[top];
					//nodes[tile]->neighbors.push_back(next);
					next->neighbors.push_back(nodes[top]);
				}

				if (tileMap->getTile(i, j + 1) != nullptr && tileMap->getTile(i, j + 1)->getWeight() > 0)
				{
					right = tileMap->getTile(i, j + 1);
					//next = nodes[right];
					//nodes[tile]->neighbors.push_back(next);
					next->neighbors.push_back(nodes[right]);
				}

				if (tileMap->getTile(i - 1, j) != nullptr && tileMap->getTile(i - 1, j)->getWeight() > 0)
				{
					bottom = tileMap->getTile(i - 1, j);
					//next = nodes[bottom];
					//nodes[tile]->neighbors.push_back(next);
					next->neighbors.push_back(nodes[bottom]);
				}

				if (tileMap->getTile(i, j - 1) != nullptr && tileMap->getTile(i, j - 1)->getWeight() > 0)
				{
					left = tileMap->getTile(i, j - 1);
					//next = nodes[left];
					//nodes[tile]->neighbors.push_back(next);
					next->neighbors.push_back(nodes[left]);
				}
				
				//calculate cost
				for (int n = 0; n < nodes[tile]->neighbors.size(); n++)
				{
					int t = nodes[tile]->neighbors.size();
					SearchNode* check = nodes[tile];// ->neighbors[n];
					w = nodes[tile]->neighbors[n]->tile->getWeight(); 
					cost = w * distance(nodes[tile]->tile->getXCoordinate(), nodes[tile]->neighbors[n]->tile->getXCoordinate(),
						nodes[tile]->tile->getYCoordinate(), nodes[tile]->neighbors[n]->tile->getYCoordinate());
					nodes[tile]->travelCost = cost;
					//heuristic cost
					//hc = distance(nodes[tile]->tile->getXCoordinate())
				}

				}


				//SearchNode* check = new SearchNode();
				//Tile* test = tileMap->getTile(0, 0);
				//check->tile = test;
				//for (int n = 0; n < nodes[test]->neighbors.size(); n++)
				//{
				//	check = nodes[test]->neighbors[n];//nodes[tile]->neighbors[n];
				//}
			
			}
		}
			

		//Code to test neighbors in Lab B
		for (auto node : nodes)
		{
			if (node.second == nullptr)
				continue;
			for (auto neighbor : node.second->neighbors)
			{
				node.second->tile->addLineTo(neighbor->tile, 0xff0000ff);
			}
		}
	}

	boolean PathSearch::greedyisGreater(PlannerNode* lhs, PlannerNode* rhs)
	{
		return (lhs->searchNode->heuristicCost > rhs->searchNode->heuristicCost);
	}

	boolean PathSearch::unifromisGreater(PlannerNode* lhs, PlannerNode* rhs)
	{
		return (lhs->searchNode->givenCost > rhs->searchNode->givenCost);
	}

	boolean PathSearch::AisGreater(PlannerNode* lhs, PlannerNode* rhs)
	{
		return (lhs->searchNode->finalCost > rhs->searchNode->finalCost);
	}

	void PathSearch::enter(int startRow, int startColumn, int goalRow, int goalColumn)
	{
		Tile* cost;
		SearchNode* update;
		double hc;

		Tile* tile = tileMap->getTile(startRow, startColumn);
		start = nodes[tile];

		Tile* gTile = tileMap->getTile(goalRow, goalColumn);
		goal = nodes[gTile];

		PlannerNode* begin = new PlannerNode();
		begin->searchNode = start;

			//calculate heuristic cost
			/*for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; j++)
				{
					cost = tileMap->getTile(i, j);

					hc = distance(nodes[cost]->tile->getXCoordinate(), goal->tile->getXCoordinate(),
						nodes[cost]->tile->getXCoordinate(), goal->tile->getYCoordinate());
					nodes[cost]->heuristicCost = hc;
				}
			}*/
		
			//push is enqueue and pop is dequeue

		while (!solution.empty())
		{
			solution.pop_back();
		}
		if (searchType == 0)
		{
			q.push(begin);
			visited[start] = q.front();
			visited[start]->searchNode->visited = true;
		}
		else if (searchType == 1)
		{
			gopen.push(begin);
			visited[start] = gopen.front();
			//calculate cost
			visited[start]->searchNode->heuristicCost = distance(visited[start]->searchNode->tile->getXCoordinate(), goal->tile->getXCoordinate(),
				visited[start]->searchNode->tile->getYCoordinate(), goal->tile->getYCoordinate());
			visited[start]->searchNode->visited = true;
		}
		else if (searchType == 2)
		{
			uopen.push(begin);
			visited[start] = uopen.front();
			uopen.front()->searchNode->givenCost = 0;
			visited[start]->searchNode->visited = true;
		}
		else if (searchType == 3)
		{

			//calculate heuristic cost
			/*for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; j++)
				{
					cost = tileMap->getTile(i, j);

					hc = distance(nodes[cost]->tile->getXCoordinate(), goal->tile->getXCoordinate(),
						nodes[cost]->tile->getXCoordinate(), goal->tile->getYCoordinate());
					nodes[cost]->heuristicCost = hc;
				}
			}*/

			aopen.push(begin);
			visited[start] = aopen.front();
			visited[start]->searchNode->givenCost = 0;
			visited[start]->searchNode->heuristicCost = distance(visited[start]->searchNode->tile->getXCoordinate(), goal->tile->getXCoordinate(),
				visited[start]->searchNode->tile->getYCoordinate(), goal->tile->getYCoordinate());
			visited[start]->searchNode->finalCost = aopen.front()->searchNode->givenCost + aopen.front()->searchNode->heuristicCost * 1;
			visited[start]->searchNode->visited = true;

		}



	}
	//this is the while loop
	void PathSearch::update(long timeslice)
	{
		PlannerNode* curr, *target, *prev, *successorNode, *startPoint, *endPoint, *node;
		SearchNode* setNode, *successor;
		Tile* clear;
		bool iter = false;
		int givenCost, heuristicCost, finalCost, nodesCreated, openNodes, solutionPath = 0, nodesConstructed, nodesDestructed;
		unsigned int color;
		float tempGivenCost;
		if (timeslice == 0)//play does one iteration
		{
			iter = true;
		}
		else if (timeslice > 0)//fastforward
		{
			iter = true;
		}

		if (searchType == 0)
		{

			while (!q.empty() && iter)
			{
				curr = q.front();
				q.pop();

				if (curr->searchNode == goal) 
				{
					//build solution list;
					target = visited[start]; 
					prev = curr;
					while (target != prev)
					{
						prev->searchNode->tile->addLineTo(prev->parent->searchNode->tile, 0xffff0000);
						prev->searchNode->visited = true;
						for (int i = 0; i < curr->searchNode->neighbors.size(); i++)
						{
							if (curr->searchNode->neighbors[i]->visited == true)
							{
								curr->searchNode->neighbors[i]->tile->setFill(0xff0000ff);
								curr->searchNode->neighbors[i]->tile->setOutline(0xffff00ff);
							}
							else
							{
								curr->searchNode->neighbors[i]->tile->setFill(0xff00ff00);
								curr->searchNode->neighbors[i]->tile->setOutline(0xffff00ff);
								curr->searchNode->neighbors[i]->tile->clearLines();
							}
							curr->searchNode->neighbors[i]->tile->setOutline(0xffff00ff);
						}
						solution.push_back(prev->searchNode->tile);
						prev = prev->parent;
						solutionPath++;

					}
					solution.push_back(prev->searchNode->tile);
					std::cout << "\n" + solutionPath;
					//std::cout << q.size();
					Done = true;
					exit();
					return;
				}
				else
				{
					Done = false;
				}

				//clear lines
				//Tile* clear;
				//SearchNode* setNode;
				for (int i = 0; i < row; i++)
				{
					for (int j = 0; j < col; j++)
					{
						clear = tileMap->getTile(i, j);
						clear->clearLines();
						setNode = nodes[clear];
						if (setNode->visited == true)
						{
							//setNode->tile->setFill(0xff0000ff);
							//setNode->tile->setMarker(0xff0000ff);
						}
						for (int n = 0; n < curr->searchNode->neighbors.size(); n++)
						{
							if (setNode->visited == false && setNode == curr->searchNode->neighbors[n])
							{
								//setNode->tile->setMarker(0x0000ff00); 
								setNode->tile->setFill(0xff00ff00);
							}

						}
						setNode->tile->setOutline(0xff0000ff);
					}

				}

				//SearchNode* successor;
				//PlannerNode* successorNode;

				/*if (curr == visited[start])
				{
					successorNode = new PlannerNode();
					successorNode->searchNode = curr->searchNode;
					successorNode->parent = nullptr;
					visited[curr->searchNode] = successorNode;
					q.push(successorNode);
				}*/
				
				for (int i = 0; i < curr->searchNode->neighbors.size(); i++) 
				{
					successor = curr->searchNode->neighbors[i];
					
					if(visited[successor] == nullptr)
					{
						successorNode = new PlannerNode();
						successorNode->searchNode = successor;
						successorNode->parent = curr;
						visited[successor] = successorNode;
						q.push(visited[successor]);//successorNode);
						visited[successor]->searchNode->visited = true;
					}
				}
				
					startPoint = visited[start];
					endPoint = visited[successor];// , * temp = endPoint;
					bool check = true;
					//draw new line and update open nodes
				while (startPoint != endPoint)//check == true; 
				{
					endPoint->searchNode->tile->addLineTo(endPoint->parent->searchNode->tile, 0xffff0000);
					
					//endPoint->searchNode->visited = true;
					//if(visited[successor]->parent->searchNode == visited[successor]->searchNode->neighbors[0])//if the visited[successor] is the parent of the first neighbor update its marker
					//endPoint->searchNode->tile->setFill(0xff00ff00);
					if (endPoint->searchNode->visited == true  || visited[start]->searchNode->visited == true)
					{
						endPoint->searchNode->tile->setFill(0xff0000ff);
					}
					for (int i = 0; i < visited[successor]->searchNode->neighbors.size(); i++)
					{



						//if (visited[successor]->searchNode->neighbors[i]->visited == true)
						//{
						//	//visited[successor]->searchNode->neighbors[i]->tile->setFill(0xff0000ff);
						//	//visited[successor]->searchNode->neighbors[i]->tile->setOutline(0xffff00ff);
						//}
						//else
						//{
						//	//visited[successor]->searchNode->neighbors[i]->tile->setOutline(0xffff00ff);
						//	//visited[successor]->searchNode->neighbors[i]->tile->clearLines();
						//}
						if (visited[successor]->searchNode->neighbors[i]->visited != true)
						{
							visited[successor]->searchNode->neighbors[i]->tile->setFill(0xff00ff00);
							//visited[successor]->searchNode->neighbors[i]->tile->setMarker(0x7f00ff00);


								//while (visited[successor]->searchNode->visited != true)
								//{
								//	//interpolate marker color from dark to green
								//	unsigned int color = BreakIntoBits(0x0000ff00, 0xff00ff00, 0.6);

								//	visited[successor]->searchNode->neighbors[i]->tile->setMarker(color);
								//}

						}

						visited[successor]->searchNode->neighbors[i]->tile->setOutline(0xffff00ff);
					}

					if (endPoint == startPoint)
					{
						break;
					}
					endPoint = endPoint->parent;
				}
				
				if (timeslice == 0)
				{
					iter = false;
					return;
				}
			}
		}
		else if (searchType == 1)
		{
			while (!gopen.empty() && iter)
			{
				curr = gopen.front();
				gopen.pop();

				if (curr->searchNode == goal)
				{
					target = visited[start];
					prev = curr;
					while (target != prev)
					{
						prev->searchNode->tile->addLineTo(prev->parent->searchNode->tile, 0xffff0000);
						prev->searchNode->visited = true;
						for (int i = 0; i < curr->searchNode->neighbors.size(); i++)
						{
							if (curr->searchNode->neighbors[i]->visited == true)
							{
								curr->searchNode->neighbors[i]->tile->setFill(0xff0000ff);
								curr->searchNode->neighbors[i]->tile->setOutline(0xffff00ff);
							}
							else
							{
								curr->searchNode->neighbors[i]->tile->setFill(0xff00ff00);
								curr->searchNode->neighbors[i]->tile->setOutline(0xffff00ff);
								curr->searchNode->neighbors[i]->tile->clearLines();
							}
							curr->searchNode->neighbors[i]->tile->setOutline(0xffff00ff);
						}
						solution.push_back(prev->searchNode->tile);
						prev = prev->parent;
					}
					solution.push_back(prev->searchNode->tile);
					Done = true;
					exit();
					return;
				}
				else
				{
					Done = false;
				}

				//clear lines
				for (int i = 0; i < row; i++)
				{
					for (int j = 0; j < col; j++)
					{
						clear = tileMap->getTile(i, j);
						clear->clearLines();
						setNode = nodes[clear];
						if (setNode->visited == true)
						{
							setNode->tile->setFill(0xff0000ff);
							setNode->tile->setMarker(0xff0000ff);
						}
						for (int n = 0; n < curr->searchNode->neighbors.size(); n++)
						{
							if (setNode->visited == false && setNode == curr->searchNode->neighbors[n])
							{
								//setNode->tile->setMarker(0x0000ff00); 
							}

						}
						setNode->tile->setOutline(0xff0000ff);
					}

				}


				for (int i = 0; i < curr->searchNode->neighbors.size(); i++)
				{
					successor = curr->searchNode->neighbors[i];

					if (visited[successor] == nullptr)
					{
						successorNode = new PlannerNode();
						successorNode->searchNode = successor;
						successorNode->parent = curr;
						successorNode->searchNode->heuristicCost = distance(successor->tile->getXCoordinate(), goal->tile->getXCoordinate(),
							successor->tile->getYCoordinate(), goal->tile->getYCoordinate());
						visited[successor] = successorNode;
						gopen.push(successorNode);
					}
				}

				startPoint = visited[start];
				endPoint = visited[successor];
				//draw new line and update open nodes
				while (startPoint != endPoint)
				{
					endPoint->searchNode->tile->addLineTo(endPoint->parent->searchNode->tile, 0xffff0000);
					endPoint->searchNode->visited = true;

					for (int i = 0; i < visited[successor]->searchNode->neighbors.size(); i++)
					{

						if (visited[successor]->searchNode->neighbors[i]->visited != true)
						{
							visited[successor]->searchNode->neighbors[i]->tile->setFill(0xff00ff00);

						}

						visited[successor]->searchNode->neighbors[i]->tile->setOutline(0xffff00ff);
					}
					endPoint = endPoint->parent;
				}
				
				if (timeslice == 0)
				{
					iter = false;
					return;
				}
			}
		}
		else if (searchType == 2)
		{
			while (!uopen.empty() && iter)
			{
				curr = uopen.front();
				uopen.pop();

				if (curr->searchNode == goal)
				{
					target = visited[start];
					prev = curr;
					while (target != prev)
					{
						prev->searchNode->tile->addLineTo(prev->parent->searchNode->tile, 0xffff0000);
						prev->searchNode->visited = true;
						for (int i = 0; i < curr->searchNode->neighbors.size(); i++)
						{
							if (curr->searchNode->neighbors[i]->visited == true)
							{
								curr->searchNode->neighbors[i]->tile->setFill(0xff0000ff);
								curr->searchNode->neighbors[i]->tile->setOutline(0xffff00ff);
							}
							else
							{
								curr->searchNode->neighbors[i]->tile->setFill(0xff00ff00);
								curr->searchNode->neighbors[i]->tile->setOutline(0xffff00ff);
								curr->searchNode->neighbors[i]->tile->clearLines();
							}
							curr->searchNode->neighbors[i]->tile->setOutline(0xffff00ff);
						}
						solution.push_back(prev->searchNode->tile);
						prev = prev->parent;
					}
					solution.push_back(prev->searchNode->tile);
					Done = true;
					//exit();
					return;
				}
				else
				{
					//Done = false;
				}

				//clear lines
				for (int i = 0; i < row; i++)
				{
					for (int j = 0; j < col; j++)
					{
						clear = tileMap->getTile(i, j);
						clear->clearLines();
						setNode = nodes[clear];
						if (setNode->visited == true)
						{
							setNode->tile->setFill(0xff0000ff);
							setNode->tile->setMarker(0xff0000ff);
						}
						for (int n = 0; n < curr->searchNode->neighbors.size(); n++)
						{
							if (setNode->visited == false && setNode == curr->searchNode->neighbors[n])
							{
								//setNode->tile->setMarker(0x0000ff00); 
							}

						}
						setNode->tile->setOutline(0xff0000ff);
					}

				}

				for (int i = 0; i < curr->searchNode->neighbors.size(); i++)
				{
					successor = curr->searchNode->neighbors[i];
					tempGivenCost = curr->searchNode->givenCost + curr->searchNode->neighbors[i]->travelCost;

					if (visited[successor] != nullptr)
					{
						if (tempGivenCost < visited[successor]->searchNode->givenCost)
						{
							successorNode = visited[successor];
							uopen.remove(successorNode);
							successorNode->searchNode->givenCost = tempGivenCost;
							successorNode->parent = curr;
							uopen.push(successorNode);
						}
					}
					else
					{
						successorNode = new PlannerNode();
						successorNode->searchNode = successor;
						successorNode->searchNode->givenCost = tempGivenCost;
						successorNode->parent = curr;
						visited[successor] = successorNode;
						uopen.push(successorNode);
					}

				}

				startPoint = visited[start];
				endPoint = visited[successor];
				//draw new line and update open nodes
				while (startPoint != endPoint)
				{
					endPoint->searchNode->tile->addLineTo(endPoint->parent->searchNode->tile, 0xffff0000);
					endPoint->searchNode->visited = true;

					for (int i = 0; i < visited[successor]->searchNode->neighbors.size(); i++)
					{

						if (visited[successor]->searchNode->neighbors[i]->visited != true)
						{
							visited[successor]->searchNode->neighbors[i]->tile->setFill(0xff00ff00);

						}

						visited[successor]->searchNode->neighbors[i]->tile->setOutline(0xffff00ff);
					}
					endPoint = endPoint->parent;
				}

				if (timeslice == 0)
				{
					iter = false;
					return;
				}
		    }
		}
		else if (searchType == 3)
		{
		while (!aopen.empty() && iter == true)
		{
			curr = aopen.front();
			aopen.pop();


			//clear lines
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; j++)
				{
					clear = tileMap->getTile(i, j);
					clear->clearLines();
					setNode = nodes[clear];
					if (setNode->visited == true)
					{
						setNode->tile->setFill(0xff0000ff);
						setNode->tile->setMarker(0xff0000ff);
					}
					for (int n = 0; n < curr->searchNode->neighbors.size(); n++)
					{
						if (setNode->visited == false && setNode == curr->searchNode->neighbors[n])
						{
							//setNode->tile->setMarker(0x0000ff00); 
						}

					}
					setNode->tile->setOutline(0xff0000ff);
				}

			}


			if (curr->searchNode == goal)
			{
				target = visited[start];
				prev = curr;
				while (target != prev) 
				{
					prev->searchNode->tile->addLineTo(prev->parent->searchNode->tile, 0xffff0000);
					prev->searchNode->visited = true;
					for (int i = 0; i < curr->searchNode->neighbors.size(); i++)
					{
						if (curr->searchNode->neighbors[i]->visited == true)
						{
							curr->searchNode->neighbors[i]->tile->setFill(0xff0000ff);
							curr->searchNode->neighbors[i]->tile->setOutline(0xffff00ff);
						}
						else
						{
							curr->searchNode->neighbors[i]->tile->setFill(0xff00ff00);
							curr->searchNode->neighbors[i]->tile->setOutline(0xffff00ff);
							curr->searchNode->neighbors[i]->tile->clearLines();
						}
						curr->searchNode->neighbors[i]->tile->setOutline(0xffff00ff);
					}
					solution.push_back(prev->searchNode->tile);
					prev = prev->parent;
				}
				solution.push_back(prev->searchNode->tile);
				Done = true;
				//exit();
				return;
			}
			/*else
			{
				Done = false;
			}*/

			

			for (int i = 0; i < curr->searchNode->neighbors.size(); i++)
			{
				successor = curr->searchNode->neighbors[i];
				tempGivenCost = curr->searchNode->givenCost + curr->searchNode->neighbors[i]->travelCost;

				if (visited[successor] != nullptr)
				{
					 node = visited[successor];

					if (tempGivenCost < node->searchNode->givenCost)
					{
						aopen.remove(node);
						node->searchNode->givenCost = tempGivenCost;
						node->searchNode->heuristicCost = distance(node->searchNode->tile->getXCoordinate(), goal->tile->getXCoordinate(),
							node->searchNode->tile->getXCoordinate(), goal->tile->getYCoordinate());
						node->searchNode->finalCost = node->searchNode->givenCost + node->searchNode->heuristicCost * 1;
						node->parent = curr;
						aopen.push(node);
						//visited[successor] = node;
					}
				}
				else
				{
					node = new PlannerNode();
					node->searchNode = successor;
					node->searchNode->givenCost = tempGivenCost;
					node->searchNode->heuristicCost = distance(node->searchNode->tile->getXCoordinate(), goal->tile->getXCoordinate(),
						node->searchNode->tile->getXCoordinate(), goal->tile->getYCoordinate());
					node->searchNode->finalCost = node->searchNode->givenCost + node->searchNode->heuristicCost * 1;
					node->parent = curr;
					aopen.push(node);
					visited[successor] = node;
					node->searchNode->tile->setFill(0xff00ff00);
				}

			}

			//startPoint = visited[start];
			//endPoint = visited[successor];
			////draw new line and update open nodes
			//while (startPoint != endPoint)
			//{
			//	if (endPoint->parent == nullptr)
			//	{
			//		break;
			//	}
			//	endPoint->searchNode->tile->addLineTo(endPoint->parent->searchNode->tile, 0xffff0000);
			//	endPoint->searchNode->visited = true;

			//	for (int i = 0; i < visited[successor]->searchNode->neighbors.size(); i++)
			//	{

			//		if (visited[successor]->searchNode->neighbors[i]->visited != true)
			//		{
			//			visited[successor]->searchNode->neighbors[i]->tile->setFill(0xff00ff00);

			//		}

			//		visited[successor]->searchNode->neighbors[i]->tile->setOutline(0xffff00ff);
			//	}
			//	endPoint = endPoint->parent;
			//}

			//if (timeslice == 0)
			//{
			////	iter = false;
			//	return;
			//}
		}
		}
	}

	void PathSearch::exit()
	{
		//start = nullptr;
		//goal = nullptr;
		visited.clear();
		Done = false;

		tileMap->resetTileDrawing();
		while (!q.empty()) {
			q.pop();
		}
		while (!gopen.empty()) {
			gopen.pop();
		}
		while (!aopen.empty()) {
			aopen.pop();
		}
		while (!uopen.empty()) {
			uopen.pop();
		}
		/*if (tileMap != copyMap)
		{
			shutdown();

		}*/
		initialize(tileMap);
	}

	void PathSearch::shutdown()
	{
	/*	Tile* tile;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				tile = tileMap->getTile(i, j);
				delete nodes[tile];
			}
		}*/

		nodes.clear();
	}

	bool PathSearch::isDone() const
	{
		return Done;//true;
	}

	std::vector<Tile const*> const PathSearch::getSolution() const
	{
		std::vector<Tile const*> temp;
		
		temp = solution;
		//Tile const* b = temp.back();
		return temp;
	}
}}  // namespace fullsail_ai::algorithms

