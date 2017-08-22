#ifndef _LIB_H_
#define _LIB_H_

#include <stdlib.h>
#include <list>
#include <time.h>
#include <tuple>

#define SHANELIBAPI extern "C" __declspec(dllexport)
//=====================================================================
//	Defines
//=====================================================================
#define TLi 0
#define TMi 1
#define TRi 2
#define MLi 3
#define MMi 4
#define MRi 5
#define BLi 6
#define BMi 7
#define BRi 8
//=====================================================================
//	Structures
//=====================================================================
struct TNode
{
	bool isEnd;
	int * numOrder;
	TNode ** branches;
	int branchArrSize;
};
//=====================================================================
//	API Functions
//=====================================================================
SHANELIBAPI int Factorial(int num);

SHANELIBAPI void Cleanup(int ** is, int length);

SHANELIBAPI int ** CreatePuzzle(bool sorted, bool intemediate);

//SHANELIBAPI int ** CreatePuzzleMinMissing(bool sorted, int min);

SHANELIBAPI void SolveThisPuzzle(int ** puzzle);

SHANELIBAPI int ** PrintOrder(int ** puzzle);

SHANELIBAPI int *** CreatePuzzles(bool sorted, int num, bool intemediate);

SHANELIBAPI void CleanupPuzzles(int num, int *** puzzles);
//=====================================================================
//	Helper Functions
//=====================================================================
void FillTree(TNode * node, int * numList, int numListLen, int * thusFar, int thusFarLen, int num);

void DeleteTree(TNode * node);

int fact(int num);

int ** GetInts(int minRange, int maxRange);

int * GetTLR();

bool isTMValid(int * TL, int * TM);

bool isTRValid(int * TL, int * TM, int * TR);

bool isMLValid(int * TL, int * ML);

bool isMMValid(int * ML, int * TM, int * MM);

bool isMRValid(int * ML, int * MM, int * TR, int * MR);

bool isBLValid(int * TL, int * ML, int * BL);

bool isBMValid(int * BL, int * TM, int * MM, int * BM);

bool isBRValid(int * BL, int * BM, int * TR, int * MR, int * BR);

bool BuildPuzzle(int ** perms, int permsLen, int ** current, int numDone);

int ** GetPrintableForm(int ** puzzle);

int * GetTLR();

int ** GetHLine(int ** puzzle, int index);

int ** GetVLine(int ** puzzle, int index);

void RemovePossibilitiesLine(int ** line, int * possibilities, int * cell);

void RemovePossibilitiesSeg(int * seg, int * poss, int * cell);

int ** FindVLinePoss(int *** possibilities, int index);

int ** FindHLinePoss(int *** possibilities, int index);

bool NotSegRow(int l, int i, int j);

bool NotSegCol(int l, int i, int j);

bool LC2CheckCol(int i, int j, int l);

bool LC2CheckRow(int i, int j, int l);

void CheckLockedCandidates1(int *** possibilities);

void CheckLockedCandidates2(int *** possibilities);

void CheckNakedPair(int *** possibilities);

int *** FindAllPossibilities(int ** puzzle, bool intemediate);

void CleanupPossibilities(int *** p);

bool SearchForSingles(int ** puzzle, int *** poss, std::tuple<int,int> temp);

bool SearchForHiddenSingles(int ** puzzle, int *** poss, int index);

bool doSinglesSearch(int ** puzzle, bool intemediate);

bool SolvePuzzle(int ** puzzle, bool intemediate);

void MakePuzzle(int ** puzzle, bool intemediate);

#endif