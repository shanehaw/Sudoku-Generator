#include "lib.h"
#include <Windows.h>
//=====================================================================
//	Helpers
//=====================================================================
void FillTree(TNode * node, int * numList, int numListLen, int * thusFar, int thusFarLen, int num)
{
	if(numListLen == 0)
	{
		node->numOrder = new int[num];
		for(int i = 0; i < num; i++)
		{
			node->numOrder[i] = thusFar[i];
		}
		node->isEnd = true;
	}
	else
	{
		node->isEnd = false;
		node->numOrder = NULL;
		node->branchArrSize = numListLen;
		node->branches = new TNode*[numListLen];
		for(int i = 0; i < numListLen; i++)
		{
			int * sendThusFar = new int[thusFarLen + 1];
			for(int j = 0; j < thusFarLen; j++)
			{
				sendThusFar[j] = thusFar[j];
			}
			sendThusFar[thusFarLen] = numList[i];

			int * sendNumList = new int[numListLen - 1];
			int iCount = 0;
			for(int j = 0; j < numListLen; j++)
			{
				if(i==j)
					continue;
				
				sendNumList[iCount++] = numList[j];
			}

			node->branches[i] = new TNode();

			FillTree(node->branches[i], sendNumList, numListLen -1, sendThusFar, thusFarLen + 1, num);

			delete [] sendThusFar;
			delete [] sendNumList;
		}
	}
}

int iCount = 0;
void FillList(TNode * node, int ** list, int num)
{
	if(node->isEnd)
	{
		list[iCount] = new int[num];
		for(int i = 0; i < num; i++)
		{
			list[iCount][i] = node->numOrder[i];
		}
		iCount++;
	}
	else
	{
		for(int i = 0; i < node->branchArrSize; i++)
		{
			FillList(node->branches[i], list, num);
		}
	}
}

void DeleteTree(TNode * node)
{
	for(int i = 0; i < node->branchArrSize; i++)
	{
		DeleteTree(node->branches[i]);
	}

	delete [] node->branches;

	if(node->isEnd)
		delete [] node->numOrder;

	delete node;
}

int fact(int num)
{
	int k;
	if(num == 0)
		return 1;
	else
	{
		k = num * fact(num - 1);
		return k;
	}
}

int ** GetInts(int minRange, int maxRange)
{
	//For returning
	int numRange = (maxRange - minRange) + 1;
	int num = fact(numRange);

	int ** isRet = new int *[num];

	//Create the Permutation Tree
	TNode * baseNode = new TNode();
	int * thusFar = NULL;
	int * numList = new int[numRange];
	int iCounter = 0;
	for(int i = minRange; i <= maxRange; i++)
		numList[iCounter++] = i;

	FillTree(baseNode, numList, iCounter, thusFar, 0, numRange);

	iCounter = 0;
	iCount = 0;
	FillList(baseNode, isRet, numRange); 
	DeleteTree(baseNode);

	delete [] thusFar;
	delete [] numList;

	return isRet;
}

int * GetTLR()
{
	int iCellCount = 0;
	int * cells = new int[9];
	bool used[9];
	for(int i = 0; i < 9; i++) 
		used[i] = false;
	bool bFull = false;
	while(!bFull)
	{
		int temp = rand() % 9 + 1;
		if(!used[temp-1])
		{
			cells[iCellCount++] = temp;
			used[temp-1] = true;
		}

		bFull = true;
		for(int i = 0; i < 9; i++)
		{
			if(used[i] == false)
			{
				bFull = false;
				break;
			}
		}
	}
	return cells;
}

bool isTMValid(int * TL, int * TM)
{
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 3; j++)
			if(TM[i] == TL[(j % 3) + ((i / 3)*3)])
				return false;

	return true;
}

bool isTRValid(int * TL, int * TM, int * TR)
{
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 3; j++)
			if(	(TR[i] == TM[(j % 3) + ((i / 3)*3)]) || 
				(TR[i] == TL[(j % 3) + ((i / 3)*3)]))
				return false;

	return true;
}

bool isMLValid(int * TL, int * ML)
{
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 3; j++)
			if(ML[i] == TL[(i % 3) + ((j % 3)*3)])
				return false;

	return true;
}

bool isMMValid(int * ML, int * TM, int * MM)
{
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 3; j++)
			if( (MM[i] == ML[(j % 3) + ((i / 3)*3)]) || 
				(MM[i] == TM[(i % 3) + ((j % 3)*3)]))
				return false;

	return true;
}

bool isMRValid(int * ML, int * MM, int * TR, int * MR)
{
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 3; j++)
			if(	(MR[i] == ML[(j % 3) + ((i / 3)*3)]) ||
				(MR[i] == MM[(j % 3) + ((i / 3)*3)]) ||
				(MR[i] == TR[(i % 3) + ((j % 3)*3)]))
				return false;

	return true;
}

bool isBLValid(int * TL, int * ML, int * BL)
{
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 3; j++)
			if(	(BL[i] == TL[(i % 3) + ((j % 3)*3)]) ||
				(BL[i] == ML[(i % 3) + ((j % 3)*3)]))
				return false;

	return true;
}

bool isBMValid(int * BL, int * TM, int * MM, int * BM)
{
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 3; j++)
			if(	(BM[i] == BL[(j % 3) + ((i / 3)*3)]) ||
				(BM[i] == TM[(i % 3) + ((j % 3)*3)]) ||
				(BM[i] == MM[(i % 3) + ((j % 3)*3)]))
				return false;

	return true;
}

bool isBRValid(int * BL, int * BM, int * TR, int * MR, int * BR)
{
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 3; j++)
			if( (BR[i] == BL[(j % 3) + ((i / 3)*3)]) ||
				(BR[i] == BM[(j % 3) + ((i / 3)*3)]) ||
				(BR[i] == TR[(i % 3) + ((j % 3)*3)]) ||
				(BR[i] == MR[(i % 3) + ((j % 3)*3)]))
				return false;

	return true;
}

bool BuildPuzzle(int ** perms, int permsLen, int ** current, int numDone)
{
	if(numDone == 9)
		return true;
	else
	{
		bool bRet = false;

		if(numDone != 0)
			current[numDone] = new int[9];

		std::list<int> poss;

		switch(numDone)
		{
		case 0:
			{
				current[numDone] = GetTLR();
				bRet = BuildPuzzle(perms, permsLen, current, numDone + 1);
				break;
			}
		case 1:
			{
				for(int i = 0; i < permsLen; i++)
					if(isTMValid(current[0], perms[i]))
						poss.push_back(i);
				break;
			}
		case 2:
			{
				for(int i = 0; i < permsLen; i++)
					if(isTRValid(current[0],current[1], perms[i]))
						poss.push_back(i);
				break;
			}
		case 3:
			{
				for(int i = 0; i < permsLen; i++)
					if(isMLValid(current[0],perms[i]))
						poss.push_back(i);
				break;
			}
		case 4:
			{
				for(int i = 0; i < permsLen; i++)
					if(isMMValid(current[3],current[1],perms[i]))
						poss.push_back(i);
				break;
			}
		case 5:
			{
				for(int i = 0; i < permsLen; i++)
					if(isMRValid(current[3],current[4],current[2], perms[i]))
						poss.push_back(i);
				break;
			}
		case 6:
			{
				for(int i = 0; i < permsLen; i++)
					if(isBLValid(current[0], current[3], perms[i]))
						poss.push_back(i);
				break;
			}
		case 7:
			{
				for(int i = 0; i < permsLen; i++)
					if(isBMValid(current[6],current[1],current[4],perms[i]))
						poss.push_back(i);
				break;
			}
		case 8:
			{
				for(int i = 0; i < permsLen; i++)
					if(isBRValid(current[6],current[7],current[2],current[5],perms[i]))
						poss.push_back(i);
				break;
			}
		}

		while(poss.size() != 0 && !bRet)
		{
			int rndIndex = rand() % poss.size() + 1;
			for(int i = 0; i < rndIndex; i++)
			{
				int temp = poss.front();
				poss.pop_front();
				poss.push_back(temp);
			}
			int temp = poss.front();
			poss.pop_front();

			for(int i = 0; i < 9; i++)
			{
				current[numDone][i] = perms[temp][i];
			}

			bRet = BuildPuzzle(perms, permsLen, current, numDone + 1);
			if(!bRet)
				delete [] current[numDone + 1];
		}

		return bRet;
	}
}

int ** GetPrintableForm(int ** puzzle)
{
	int ** sortedNums = new int*[9];
	for(int i = 0; i < 9; i++)
		sortedNums[i] = new int[9];

	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++)
			sortedNums[i][j] = puzzle[((i / 3)*3) + (j / 3)][((i % 3) * 3) + (j % 3)];

	return sortedNums;
}

int ** GetHLine(int ** puzzle, int index)
{
	int ** line = new int *[9];

	line[0] = &puzzle[((index / 3) * 3)][((index % 3) * 3)];
	line[1] = &puzzle[((index / 3) * 3)][((index % 3) * 3) + 1];
	line[2] = &puzzle[((index / 3) * 3)][((index % 3) * 3) + 2];

	line[3] = &puzzle[((index / 3) * 3) + 1][((index % 3) * 3)];
	line[4] = &puzzle[((index / 3) * 3) + 1][((index % 3) * 3) + 1];
	line[5] = &puzzle[((index / 3) * 3) + 1][((index % 3) * 3) + 2];

	line[6] = &puzzle[((index / 3) * 3) + 2][((index % 3) * 3)];
	line[7] = &puzzle[((index / 3) * 3) + 2][((index % 3) * 3) + 1];
	line[8] = &puzzle[((index / 3) * 3) + 2][((index % 3) * 3) + 2];
	
	return line;
}

int ** GetVLine(int ** puzzle, int index)
{
	int ** line = new int * [9];

	line[0] = &(puzzle[(index / 3)][(index % 3)]);
	line[1] = &(puzzle[(index / 3)][(index % 3) + 3]);
	line[2] = &(puzzle[(index / 3)][(index % 3) + 6]);

	line[3] = &(puzzle[(index / 3) + 3][(index % 3)]);
	line[4] = &(puzzle[(index / 3) + 3][(index % 3) + 3]);
	line[5] = &(puzzle[(index / 3) + 3][(index % 3) + 6]);

	line[6] = &(puzzle[(index / 3) + 6][(index % 3)]);
	line[7] = &(puzzle[(index / 3) + 6][(index % 3) + 3]);
	line[8] = &(puzzle[(index / 3) + 6][(index % 3) + 6]);

	return line;
}

void RemovePossibilitiesLine(int ** line, int * possibilities, int * cell)
{
	if(*cell == 0)
	{
		bool found[9] = {false};

		for(int i = 0; i < 9; i++)
			if(*line[i] != 0)
				found[*line[i] - 1] = true;
	
		for(int i = 0; i < 9; i++)
			if(found[i])
				possibilities[i] = 0;
	}
	else
		for(int i = 0; i < 9; i++)
			possibilities[i] = 0;
}

void RemovePossibilitiesSeg(int * seg, int * poss, int * cell)
{
	if(*cell == 0)
	{
		bool found[9] = {false};
		for(int i = 0; i < 9; i++)
			if(seg[i] != 0)
				found[seg[i] - 1] = true;
		
		for(int i = 0; i < 9; i++)
			if(found[i])
				poss[i] = 0;
	}
	else
		for(int i = 0; i < 9; i++)
			poss[i] = 0;
}

bool IsPuzzleValid(int ** puzzle)
{
	return	isTMValid(puzzle[TLi],puzzle[TMi]) &&
			isTRValid(puzzle[TLi],puzzle[TMi],puzzle[TRi]) &&
			isMLValid(puzzle[TLi],puzzle[MLi]) &&
			isMMValid(puzzle[MLi],puzzle[TMi],puzzle[MMi]) &&
			isMRValid(puzzle[MLi],puzzle[MMi],puzzle[TRi],puzzle[MRi]) &&
			isBLValid(puzzle[TLi],puzzle[MLi],puzzle[BLi]) &&
			isBMValid(puzzle[BLi],puzzle[TMi],puzzle[MMi],puzzle[BMi]) &&
			isBRValid(puzzle[BLi],puzzle[BMi],puzzle[TRi],puzzle[MRi],puzzle[BRi]);
}

void CleanupPossibilities(int *** p)
{
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++)
			delete [] p[i][j];

	for(int i = 0; i < 9; i++)
		delete [] p[i];

	delete [] p;
}
//===============================================================
// Solving Functions
//===============================================================
bool SearchForSingles(int ** puzzle, int *** poss, std::tuple<int,int> temp)
{
	bool found = false;

	int a = std::get<0>(temp);
	int b = std::get<1>(temp);

	int numCount = 0;
	for(int i = 0; i < 9; i++)
		if(poss[a][b][i] != 0)
			numCount++;

	if(numCount == 1)
	{	//Is a single

		int num = -1;
		for(int i = 0; i < 9; i++)
			if(poss[a][b][i] != 0)
			{
				num = poss[a][b][i];
				break;
			}

		if(num != -1)
		{
			puzzle[a][b] = num;
			found = true;
		}
	}
	return found;
}

bool SearchForHiddenSingles(int ** puzzle, int *** poss, int index)
{
	bool found = false;

	//Search for hidden single in segment
	//-----------------------------------

	int ** segPoss = new int *[9];
	for(int i = 0; i < 9; i++)
		segPoss[i] = new int[9];

	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++)
			segPoss[i][j] = poss[index][i][j];
	
	//	- Find a possiblity which is not zero
	//	- Loop through all other cells in the segment and 
	//	  if they are not 0, 0 them
	//	- if any non-zeros are found zero the orignal as well
	//	- this removes all duplicate possibilities

	//Remove all possibilities
	for(int i = 0; i < 9; i++)
	{	//Run through each cell
		for(int j = 0; j < 9; j++)
		{	//Run through each possibility
			bool dups = false;
			if(segPoss[i][j] != 0)
			{	//Found a non-zero
				for(int k = 0; k < 9; k++)
				{	//Run through the list again
					if(segPoss[k][j] != 0 && k != i)
					{	//if a non-zero is found, then it is a duplicate.
						//set to 0 and dups to true so that the original
						//is zeroed as well
						segPoss[k][j] = 0;
						dups = true;
					}
				}
			}
			if(dups)
				segPoss[i][j] = 0;
		}
	}

	for(int i = 0; i < 9; i++)
	{
		int iVal = -1;
		bool bHS = false;
		for(int j = 0; j < 9; j++)
		{
			if(bHS)
			{
				bHS = false;
				break;
			}
			else
			{
				if(segPoss[i][j] != 0)
				{
					bHS = true;
					iVal = segPoss[i][j];
					break;
				}
			}
		}

		if(bHS)
		{
			found = true;
			puzzle[index][i] = iVal;
		}
	}

	for(int i = 0; i < 9; i++)
		delete [] segPoss[i];
	delete [] segPoss;

	//Search for hidden Single in a horizontal Line
	//---------------------------------------------

	int ** hLine = new int *[9];
	int ** hProbLine = new int *[9];
	for(int i = 0; i < 9; i++)
		hProbLine[i] = new int[9];

	for(int i = 0 ; i < 9; i++)
	{
		hLine[i] = &puzzle[((index / 3) * 3) + (i / 3)][((index % 3) * 3) + (i % 3)];
		for(int j = 0; j < 9; j++)
			hProbLine[i][j] = poss[((index / 3) * 3) + (i / 3)][((index % 3) * 3) + (i % 3)][j];
	}

	for(int i = 0; i < 9; i++)
	{	//Run through each cell
		for(int j = 0; j < 9; j++)
		{	//Run through each possibility
			bool dups = false;
			if(hProbLine[i][j] != 0)
			{	//Found a non-zero
				for(int k = 0; k < 9; k++)
				{	//Run through the list again
					if(hProbLine[k][j] != 0 && k != i)
					{	//if a non-zero is found, then it is a duplicate.
						//set to 0 and dups to true so that the original
						//is zeroed as well
						hProbLine[k][j] = 0;
						dups = true;
					}
				}
			}
			if(dups)
				hProbLine[i][j] = 0;
		}
	}

	for(int i = 0; i < 9; i++)
	{
		int iVal = -1;
		bool bHS = false;
		for(int j = 0; j < 9; j++)
		{
			if(bHS)
			{
				bHS = false;
				break;
			}
			else
			{
				if(hProbLine[i][j] != 0)
				{
					bHS = true;
					iVal = hProbLine[i][j];
					break;
				}
			}
		}

		if(bHS)
		{
			found = true;
			*(hLine[i]) = iVal;
		}
	}

	for(int i = 0; i < 9; i++)
		delete []  hProbLine[i];
	delete [] hProbLine;

	delete [] hLine;

	//Search for hidden Single in vertical line
	//-----------------------------------------
	
	int ** vLine = new int *[9];
	int ** vProbLine = new int *[9];
	for(int i = 0; i < 9; i++)
		vProbLine[i] = new int[9];

	for(int i = 0 ; i < 9; i++)
	{
		vLine[i] = &puzzle[(index / 3) + ((i / 3) * 3)][(index % 3) + ((i % 3) * 3)];
		for(int j = 0; j < 9; j++)
			vProbLine[i][j] = poss[(index / 3) + ((i / 3) * 3)][(index % 3) + ((i % 3) * 3)][j];
	}

	for(int i = 0; i < 9; i++)
	{	//Run through each cell
		for(int j = 0; j < 9; j++)
		{	//Run through each possibility
			bool dups = false;
			if(vProbLine[i][j] != 0)
			{	//Found a non-zero
				for(int k = 0; k < 9; k++)
				{	//Run through the list again
					if(vProbLine[k][j] != 0 && k != i)
					{	//if a non-zero is found, then it is a duplicate.
						//set to 0 and dups to true so that the original
						//is zeroed as well
						vProbLine[k][j] = 0;
						dups = true;
					}
				}
			}
			if(dups)
				vProbLine[i][j] = 0;
		}
	}

	for(int i = 0; i < 9; i++)
	{
		int iVal = -1;
		bool bHS = false;
		for(int j = 0; j < 9; j++)
		{
			if(bHS)
			{
				bHS = false;
				break;
			}
			else
			{
				if(vProbLine[i][j] != 0)
				{
					bHS = true;
					iVal = vProbLine[i][j];
					break;
				}
			}
		}

		if(bHS)
		{
			found = true;
			*(vLine[i]) = iVal;
		}
	}

	for(int i = 0; i < 9; i++)
		delete []  vProbLine[i];
	delete [] vProbLine;

	delete [] vLine;

	return found;
}

bool doSinglesSearch(int ** puzzle, bool intemediate)
{
	bool bReturn = false;

	int *** poss = FindAllPossibilities(puzzle, intemediate);

	std::list<std::tuple<int,int>> unknowns; 

	//Try and solve
	//Find all unsolved
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++)
			for(int k = 0; j < 9; k++)
				if(poss[i][j][k] == 0)
				{
					std::tuple<int,int> index(i,j);
					unknowns.push_back(index);
					break;
				}

	//Run Through all unknowns
	for(int i = 0; i < unknowns.size(); i++)
	{
		std::tuple<int,int> temp = unknowns.front();

		if(SearchForSingles(puzzle, poss, temp))
			bReturn = true;
			
		unknowns.pop_front();
		unknowns.push_back(temp);
	}

	CleanupPossibilities(poss);
	return bReturn;
}

bool doHiddenSingleSearch(int ** puzzle, bool intemediate)
{
	bool bReturn = false;

	int *** poss = FindAllPossibilities(puzzle, intemediate);

	//Run through all segments
	for(int i = 0; i < 9; i++)
		if(SearchForHiddenSingles(puzzle, poss, i))
			bReturn = true;	

	CleanupPossibilities(poss);
	return bReturn;
}

bool SolvePuzzle(int ** puzzle, bool intemediate)
{
	bool solved = false;

	int iCount = 0;
	while(!solved && iCount < 20)
	{
		//Check for Singles
		bool bFoundSingle = false;
		if(doSinglesSearch(puzzle, intemediate));
			bFoundSingle = true;	

		//Check for hidden Singles
		bool bFoundHiddenSingle = false;
		if(doHiddenSingleSearch(puzzle, intemediate))
			bFoundHiddenSingle = true;

		solved = true;
		for(int i = 0; i < 9; i++)
			for(int j = 0; j < 9; j++)
				if(puzzle[i][j] == 0)
					solved = false;

		iCount++;
	}

	return solved;
}

int ** FindVLinePoss(int *** possibilities, int index)
{
	int ** pLine = new int * [9];

	pLine[0] = possibilities[(index / 3)][(index % 3)];
	pLine[1] = possibilities[(index / 3)][(index % 3) + 3];
	pLine[2] = possibilities[(index / 3)][(index % 3) + 6];

	pLine[3] = possibilities[(index / 3) + 3][(index % 3)];
	pLine[4] = possibilities[(index / 3) + 3][(index % 3) + 3];
	pLine[5] = possibilities[(index / 3) + 3][(index % 3) + 6];

	pLine[6] = possibilities[(index / 3) + 6][(index % 3)];
	pLine[7] = possibilities[(index / 3) + 6][(index % 3) + 3];
	pLine[8] = possibilities[(index / 3) + 6][(index % 3) + 6];

	return pLine;
}

int ** FindHLinePoss(int *** possibilities, int index)
{
	int ** pLine = new int *[9];

	pLine[0] = possibilities[((index / 3) * 3)][((index % 3) * 3)];
	pLine[1] = possibilities[((index / 3) * 3)][((index % 3) * 3) + 1];
	pLine[2] = possibilities[((index / 3) * 3)][((index % 3) * 3) + 2];

	pLine[3] = possibilities[((index / 3) * 3) + 1][((index % 3) * 3)];
	pLine[4] = possibilities[((index / 3) * 3) + 1][((index % 3) * 3) + 1];
	pLine[5] = possibilities[((index / 3) * 3) + 1][((index % 3) * 3) + 2];

	pLine[6] = possibilities[((index / 3) * 3) + 2][((index % 3) * 3)];
	pLine[7] = possibilities[((index / 3) * 3) + 2][((index % 3) * 3) + 1];
	pLine[8] = possibilities[((index / 3) * 3) + 2][((index % 3) * 3) + 2];

	return pLine;
}

bool NotSegRow(int l, int i, int j)
{
	bool nValid = false;

	int j2, j3;
	if(j % 3 == 2)
	{
		j2 = j - 2;
		j3 = j - 1;
	}

	if(j % 3 == 1)
	{
		j2 = j - 1;
		j3 = j + 1;
	}

	if(j % 3 == 0)
	{
		j2 = j + 1;
		j3 = j + 2;
	}

	if (l != (((i % 3) * 3) + (j % 3))  &&
		l != (((i % 3) * 3) + (j2 % 3)) &&
		l != (((i % 3) * 3) + (j3 % 3)))
			nValid = true;
	
	return nValid;
}

bool NotSegCol(int l, int i, int j)
{
	bool nValid = false;

	int j2, j3;
	if(j / 3 == 2)
	{
		j2 = j - 3;
		j3 = j - 6;
	}

	if(j / 3 == 1)
	{
		j2 = j - 3;
		j3 = j + 3;
	}

	if(j / 3 == 0)
	{
		j2 = j + 3;
		j3 = j + 6;
	}

	if (l != (((i / 3) * 3) +  (j / 3))  &&
		l != (((i / 3) * 3) +  (j2 / 3)) &&
		l != (((i / 3) * 3) +  (j3 / 3)))
			nValid = true;
	
	return nValid;
}

bool LC2CheckCol(int i, int j, int l)
{
	return l != (((i % 3) * 3) +  (j % 3));
}

bool LC2CheckRow(int i, int j, int l)
{
	return l != (((i / 3) * 3) + (j / 3));
}

void CheckLockedCandidates1(int *** possibilities)
{
	for(int i = 0; i < 9; i++)
	{	//Run through each segment looking for Locked Candidates
		for(int j = 0; j < 9; j++)
		{	//Run through each cell within each segment
			int * m_poss = possibilities[i][j];
			bool bAnswer = true;
			for(int k = 0; k < 9; k++)
				if(m_poss[k] != 0)
					bAnswer = false;

			if(!bAnswer)
			{	//Is not an answer check if Locked Candidate
				for(int k = 0; k < 9; k++)
				{	//For each possibility on this cell
					if(possibilities[i][j][k] != 0)
					{
						//The individual possibility that we are dealing with
						int iPoss = possibilities[i][j][k];

						bool bLockedRow = true;
						bool bLockedCol = true;

						for(int l = 0; l < 9; l++)
						{	//Have a second cursor through the cell to check if locked
							for(int m = 0; m < 9; m++)
							{	//If another possibility in the segment is the same and not in the same row then not a
								//locked candidate
								if(possibilities[i][l][m] == iPoss && (j / 3 != l / 3))
									bLockedRow = false;

								//Similar to the above but the column version
								if(possibilities[i][l][m] == iPoss && (j % 3 != l % 3))
									bLockedCol = false;
							}
						}

						if(bLockedRow)
						{
							//Run through the row and remove all possibilities of iPoss from them
							int ** p_hLine = FindHLinePoss(possibilities, (((i / 3) * 3) + (j / 3)));
							for(int l = 0; l < 9; l++)
								for(int m = 0; m < 9; m++)
									if(NotSegRow(l, i, j) && p_hLine[l][m] == iPoss)
										p_hLine[l][m] = 0;
							
							delete [] p_hLine;
						}

						if(bLockedCol)
						{
							int ** p_vLine = FindVLinePoss(possibilities,(((i % 3) * 3) +  (j % 3)));
							for(int l = 0; l < 9; l++)
								for(int m = 0; m < 9; m++)
									if(NotSegCol(l, i, j) && p_vLine[l][m] == iPoss)
										p_vLine[l][m] = 0;

							delete [] p_vLine;
						}
					}
				}
			}
		}
	}
}

void CheckLockedCandidates2(int *** possibilities)
{
	for(int i = 0; i < 9; i++)
	{
		//Get the line
		int ** p_tHPossLine = FindHLinePoss(possibilities, i);
		int ** p_tVPossLine = FindVLinePoss(possibilities, i);

		//Move through each cell and determine if any of the possibilities are localized
		//to its segment
		for(int j = 0; j < 9; j++)
		{
			for(int k = 0; k < 9; k++)
			{	//Run through each possibility
				bool bHLocal = true, bVLocal = true;

				int iHVal = p_tHPossLine[j][k];
				int iVVal = p_tVPossLine[j][k];

				if(iHVal != 0 || iVVal != 0)
				{
					//Run a second cursor through the lines to determine whether this
					//possibility is indeed a locked candidate
					for(int l = 0; l < 9; l++)
					{
						for(int m = 0; m < 9; m++)
						{
							if(iHVal != 0 && iHVal == p_tHPossLine[l][m] && l / 3 != j / 3)
							{
								bHLocal = false;
							}

							if(iVVal != 0 && iVVal == p_tVPossLine[l][m] && l / 3 != j / 3)
							{
								bVLocal = false;
							}
						}
					}

					if(bHLocal)
						for(int l = 0; l < 9; l++)
							for(int m = 0; m < 9; m++)
								if(possibilities[((i / 3) * 3) + (j / 3)][l][m] == iHVal &&
									LC2CheckRow(((i / 3) * 3) + (j / 3), l, i))
										possibilities[((i / 3) * 3) + (j / 3)][l][m] = 0;

					if(bVLocal)
						for(int l = 0; l < 9; l++)
							for(int m = 0; m < 9; m++)
								if(possibilities[(i / 3) + ((j / 3) * 3)][l][m] == iVVal &&
									LC2CheckCol((i / 3) + ((j / 3) * 3), l, i))
										possibilities[(i / 3) + ((j / 3) * 3)][l][m] = 0;

				}
			}
		}

		//Cleanup
		delete [] p_tHPossLine;
		delete [] p_tVPossLine;
	}
}

void CheckNakedPair(int *** possibilities)
{
	//=================
	//	Segment Check
	//=================

	for(int i = 0; i < 9; i++)
	{	//Move through each segment
		for(int j = 0; j < 9; j++)
		{	//Move through each cell in the segment

			int iVal1 = -1, iVal2 = -1;

			int iSegPoss = 0;
			for(int k = 0; k < 9; k++)
				if(possibilities[i][j][k] != 0)
				{
					iSegPoss++;
					if(iVal1 == -1)
						iVal1 = possibilities[i][j][k];
					else if(iVal2 == -1)
						iVal2 = possibilities[i][j][k];
				}

			if(iSegPoss == 2)
			{	//Check if this is a np
				for(int k = 0; k < 9; k++)
				{
					if(k == j)
						continue;

					int iVal2_1 = -1, iVal2_2 = -1;

					int iSegPoss_2 = 0;
					for(int l = 0; l < 9; l++)
						if(possibilities[i][k][l] != 0)
						{
							iSegPoss_2++;

							if(iVal2_1 == -1)
								iVal2_1 = possibilities[i][k][l];
							else if(iVal2_2 == -1)
								iVal2_2 = possibilities[i][k][l];
						}

					if(iSegPoss_2 == 2 && iVal1 == iVal2_1 && iVal2 == iVal2_2)
					{
						for(int m = 0; m < 9; m++)
							if(m != j && m != k)
							{
								possibilities[i][m][iVal1-1] = 0;
								possibilities[i][m][iVal2-1] = 0;
							}
					}
				}
			}
		}
	}

	//========================
	//	Line Checks
	//========================

	for(int i = 0; i < 9; i++)
	{	//Move through each line

		int ** p_hLinePoss = FindHLinePoss(possibilities, i);
		int ** p_vLinePoss = FindVLinePoss(possibilities, i);

		for(int j = 0; j < 9; j++)
		{	//Move through each cell
			
			int iVVal1 = -1, iVVal2 = -1;
			int iVal1 = -1, iVal2 = -1;
			
			int iVLineCount = 0;
			int iHLineCount = 0;
			for(int k = 0; k < 9; k++)
			{
				if(p_hLinePoss[j][k] != 0)
				{
					iHLineCount++;
					if(iVal1 == -1)
						iVal1 = p_hLinePoss[j][k];
					else if(iVal2 == -1)
						iVal2 = p_hLinePoss[j][k];
				}

				if(p_vLinePoss[j][k] != 0)
				{
					iVLineCount++;
					if(iVVal1 == -1)
						iVVal1 = p_vLinePoss[j][k];
					else if(iVVal2 == -1)
						iVVal2 = p_vLinePoss[j][k];
				}
			}

			if(iHLineCount == 2)
			{
				for(int k = 0; k < 9; k++)
				{
					if(k == j)
						continue;

					int iVal1_1 = -1, iVal2_2 = -1;

					int iHLineCount_2 = 0;
					for(int l = 0; l < 9; l++)
						if(p_hLinePoss[k][l] != 0)
						{
							iHLineCount_2++;
							if(iVal1_1 == -1)
								iVal1_1 = p_hLinePoss[k][l];
							else if(iVal2_2 == -1)
								iVal2_2 = p_hLinePoss[k][l];
						}
					
					if(iHLineCount_2 == 2 && iVal1 == iVal1_1 && iVal2 == iVal2_2)
					{
						for(int l = 0; l < 9; l++)
							if(l != j && l != k)
							{
								p_hLinePoss[l][iVal1-1] = 0;
								p_hLinePoss[l][iVal2-1] = 0;
							}
					}
				}
			}

			if(iVLineCount == 2)
			{
				for(int k = 0; k < 9; k++)
				{
					if(k == j)
						continue;

					int iVVal1_1 = -1, iVVal2_2 = -1;

					int iVLineCount_2 = 0;
					for(int l = 0; l < 9; l++)
						if(p_vLinePoss[k][l] != 0)
						{
							iVLineCount_2++;
							if(iVVal1_1 == -1)
								iVVal1_1 = p_vLinePoss[k][l];
							else if(iVVal2_2 == -1)
								iVVal2_2 = p_vLinePoss[k][l];
						}
					
					if(iVLineCount_2 == 2 && iVVal1 == iVVal1_1 && iVVal2 == iVVal2_2)
					{
						for(int l = 0; l < 9; l++)
							if(l != j && l != k)
							{
								p_vLinePoss[l][iVVal1-1] = 0;
								p_vLinePoss[l][iVVal2-1] = 0;
							}
					}
				}
			}
		}

		delete [] p_hLinePoss;
		delete [] p_vLinePoss;
	}
}

int *** FindAllPossibilities(int ** puzzle, bool intemediate)
{
	int *** possibilities = new int ** [9];
	
	for(int i = 0; i < 9; i++)
		possibilities[i] = new int * [9];

	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++)
			possibilities[i][j] = new int[9];
	
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++)
			for(int k = 0; k < 9; k++)
				possibilities[i][j][k] = k + 1;

	//============
	//	Beginner
	//============
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++)
		{
				int ** line = GetHLine(puzzle,(((i / 3) * 3) + (j / 3)));
				RemovePossibilitiesLine(line, possibilities[i][j], &puzzle[i][j]);
				delete [] line;				

				int ** vline = GetVLine(puzzle,(((i % 3) * 3) +  (j % 3)));
				RemovePossibilitiesLine(line, possibilities[i][j], &puzzle[i][j]);
				delete [] vline;

				RemovePossibilitiesSeg(puzzle[i], possibilities[i][j], &puzzle[i][j]);
		}

	//================
	//	Intermediate
	//================
	if(intemediate)
	{
		CheckLockedCandidates1(possibilities);

		CheckLockedCandidates2(possibilities);

		CheckNakedPair(possibilities);
	}

	return possibilities;
}

void MakePuzzle(int ** puzzle, bool intemediate)
{
	bool bAttempts[9][9] = {false};
	int iAttempts = 0;
	bool shouldStop = false;
	//while (!shouldStop)//while(iAttempts < 81) 
	//{

	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{				
			if(puzzle[i][j] == 0)
			{
				bAttempts[i][j] = true;
			}
			else
			{
				bAttempts[i][j] = false;
			}
		}
	}

	bool tryFindNum = true;
	while(tryFindNum)
	{
		bool somethingToTry = false;

		for(int i = 0; i < 9; i++)
		{
			for(int j = 0; j < 9; j++)
			{
				if(bAttempts[i][j] == false)
				{
					somethingToTry = true;
					break;					
				}
			}

			if(somethingToTry)
			{
				break;
			}
		}

		if(somethingToTry)
		{
			int index1 = -1;
			int index2 = -1;
			bool notDone = false;

			while(!notDone)
			{
				index1 = rand() % 9;
				index2 = rand() % 9;

				if(bAttempts[index1][index2] == false)
				{
					notDone = true;
					bAttempts[index1][index2] = true;
				}
			}

			int tempVal = puzzle[index1][index2];
			puzzle[index1][index2] = 0;

			int ** puzzleCopy = new int * [9];
			for(int j = 0; j < 9; j++)
			{
				puzzleCopy[j] = new int[9];
			}

			for(int j = 0; j < 9; j++)
			{
				for(int k = 0; k < 9; k++)
				{
					puzzleCopy[j][k] = puzzle[j][k];
				}
			}

			if(!SolvePuzzle(puzzleCopy, intemediate))
			{
				puzzle[index1][index2] = tempVal;
				
			}
			else
			{
				for(int i = 0; i < 9; i++)
				{
					for(int j = 0; j < 9; j++)
					{				
						if(puzzle[i][j] == 0)
						{
							bAttempts[i][j] = true;
						}
						else
						{
							bAttempts[i][j] = false;
						}
					}
				}
			}

			for(int i = 0; i < 9; i++)
			{
				delete [] puzzleCopy[i];
			}
			delete puzzleCopy;

			iAttempts++;
		}
		else
		{
			tryFindNum = false;
		}
	}
	//}
}
//=====================================================================
//	API Functions
//=====================================================================
SHANELIBAPI int Factorial(int num)
{
	return fact(num);
}

SHANELIBAPI void Cleanup(int ** is, int length)
{
	for(int i = 0; i < length; i++)
		delete [] is[i];
	delete [] is;
}

SHANELIBAPI int ** CreatePuzzle(bool sorted, bool intemediate)
{
	srand(time(NULL));
	int ** numsRet = new int * [9];
	int ** perms = GetInts(1,9);

	if(BuildPuzzle(perms, fact(9), numsRet, 0))
	{
		Cleanup(perms, fact(9));

		MakePuzzle(numsRet, intemediate);

		if(sorted)
		{
			int ** sortedNums = GetPrintableForm(numsRet);
			Cleanup(numsRet, 9);

			return sortedNums;
		}
		else
			return numsRet;
	}
	else
	{
		Cleanup(numsRet, 9);
		Cleanup(perms, fact(9));
		return NULL;
	}
}

//SHANELIBAPI int ** CreatePuzzleMinMissing(bool sorted, int min)
//{
//	if(min > 60)
//		min = 60;
//
//	srand(time(NULL));
//	int ** puzzle = NULL;
//	int ** perms = GetInts(1,9);
//
//	int iCount = 0;
//	bool found = false;
//	while(!found)
//	{
//		puzzle = new int *[9];
//		BuildPuzzle(perms, fact(9), puzzle, 0);
//		MakePuzzle(puzzle);
//
//		int iCount = 0;
//		for(int i = 0; i < 9; i++)
//			for(int j = 0; j < 9; j++)
//				if(puzzle[i][j] == 0)
//					iCount++;
//
//		if(iCount < min)
//		{
//			for(int i = 0; i < 9; i++)
//				delete [] puzzle[i];
//			delete [] puzzle;
//		}
//		else
//			found = true;
//	}
//
//	Cleanup(perms, fact(9));
//	return puzzle;
//}

SHANELIBAPI void SolveThisPuzzle(int ** puzzle)
{
	SolvePuzzle(puzzle, true);
}

SHANELIBAPI int ** PrintOrder(int ** puzzle)
{
	return GetPrintableForm(puzzle);
}

SHANELIBAPI int *** CreatePuzzles(bool sorted, int num, bool intemediate)
{
	srand(time(NULL));
	int ** perms = GetInts(1,9);
	int *** puzzles = new int **[num];
	int fact9 = fact(9);

	for(int i = 0; i < num; i++)
	{
		puzzles[i] = new int * [9];
		if(BuildPuzzle(perms, fact9, puzzles[i], 0))
		{			
			MakePuzzle(puzzles[i], intemediate);

			if(sorted)
			{
				int ** sortedNums = GetPrintableForm(puzzles[i]);
				Cleanup(puzzles[i], 9);
				puzzles[i] = sortedNums;			
			}
		}
		else
		{
			Cleanup(puzzles[i], 9);
			return NULL;
		}
	}

	Cleanup(perms, fact(9));
	return puzzles;
}

SHANELIBAPI void CleanupPuzzles(int num, int *** puzzles)
{
	for(int i = 0; i < num; i++)
		Cleanup(puzzles[i], 9);

	delete [] puzzles;	
}