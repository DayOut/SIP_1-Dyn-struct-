//#include "stdafx.h"

#ifndef BLIST_INCLUDE
#define BLIST_INCLUDE

//-------------DEFINES---------------------------------

#ifndef SUCCESS_INCLUDE
#define SUCCESS_INCLUDE

#define	SUCCESS_OPER		0x0
#define	NOT_SUCCESS_OPER	0x1

#endif

//------------END OF DEFINES----------------------------

// Шаблонный класс для работы с двунаправленным списком
template <typename INF> class TBList
{
// тип данных, который описывает элемент списка
	template <typename ElemType> struct TElem
	{
		ElemType Inf;
		TElem *Next, *Prev;
	};
// Информационная часть (полезная нагрузка) + указатель на следующий элемент (когда он равен NULL, то это последний элемент)
// + указатель на предыдущий элемент (когда он равен NULL, то это первый элемент)

	protected:
// Описываем указатели на первый, последний и текущий элементы списка, которые недоступны пользователю
		TElem<INF> *Head, *Tail, *CurPos;

// Флаг, определяющий действия при выполнении оператора присваивания: true - копирование списка; 
// - получение указателей на первый, последний и текущий элементы

		bool SafeFlag;
		
//-----------------------------------------------------------------------

// Недоступный пользователю метод, который возвращает указатель на найденный элемент
// NULL - если элемент не найден

		TElem<INF> *SearchElem(INF &Inf)
		{
			CurPos = Head;

			while ((CurPos != NULL) && !(CurPos->Inf == (INF&)Inf))
				CurPos = CurPos->Next;
	
			return CurPos;
		}

//-----------------------------------------------------------------------

// Недоступный пользователю метод, который вставляет новый элемент после указанного
// Элементы задаются через указатели на элемент списка

		void InsAfter(TElem<INF> *After, INF &Inf)
		{
			TElem<INF> *Cur;

			if (After != NULL)
			{
				Cur = new TElem<INF>;
				Cur->Inf = (INF&)Inf;
				Cur->Next = After->Next;
				Cur->Prev = After;
				if (After != Tail)
					After->Next->Prev = Cur;
				else
					Tail = Cur;
				After->Next = Cur;
			}
			else
				AddAfterTail(Inf);
		}

//-----------------------------------------------------------------------

// Недоступный пользователю метод, который производит удаление элемента, заданного через указатель

		void DelElemFromList(TElem<INF> *Elem)
		{
			if (Elem != Head)
				Elem->Prev->Next = Elem->Next;
			else
				Head = Head->Next;
	
			if (Elem != Tail) 
				Elem->Next->Prev = Elem->Prev;
			else
				Tail = Tail->Prev;

			delete Elem;
		}

//-----------------------------------------------------------------------

// Недоступный пользователю метод, который производит сортировку части списка

		void Sort(TElem<INF> *Left, TElem<INF> *Right)
		{
			register TElem<INF> *Cur;
			TElem<INF> *HeadL, *TailL;
			TElem<INF> *CurRight = Left, *CurLeft = Left;

			while (CurRight != Right)
			{
				Cur = CurRight->Next;
				do
				{
					if (CurRight->Inf >= Cur->Inf) 
					{			
						HeadL = Cur;
						if (CurLeft == Left) 
							CurLeft = HeadL;

						while ((Cur != Right) && (CurRight->Inf >= Cur->Inf))
							Cur = Cur->Next;

						if (CurRight->Inf < Cur->Inf) 
							TailL = Cur->Prev;
						else 
						{
							Right = HeadL->Prev;
							TailL = Cur;
							Cur = NULL;
						}

						if (TailL != Tail) 
							TailL->Next->Prev = HeadL->Prev;
						else 
							Tail = HeadL->Prev;

						HeadL->Prev->Next = TailL->Next;

						if (CurRight != Head) 
							CurRight->Prev->Next = HeadL;
						else 
							Head = HeadL;

						HeadL->Prev = CurRight->Prev;
						CurRight->Prev = TailL;
						TailL->Next = CurRight;
					
						if (Cur != NULL) 
							continue;
						break;
					}
					Cur = Cur->Next;

				}while (Cur != Right->Next);

				if ((CurLeft != Left) && (CurLeft != CurRight->Prev)) 
				{
					Sort(CurLeft, CurRight->Prev);
					CurLeft = Left;
				}

				if (CurRight != Right) 
					CurRight = CurRight->Next;
				else
					break;
			}
		}


		void SortFull(TElem<INF> *Left, register TElem<INF> *Right)
		{  
			register TElem<INF> *Cur, *tmpLeft, *tmpRight;
			TElem<INF> *HeadL, *HeadR, *LocalTail, *NewLeft;
			int FirstLoop = 1;

			do
			{
				if (Left->Inf > Right->Inf)
				{
					if (Left != Head)
						Left->Prev->Next = Right;
					else
						Head = Right;
					if (Right != Tail)
						Right->Next->Prev = Left;
					else
						Tail = Left;
					if (Left->Next != Right) 
					{
						Left->Next->Prev = Right;
						Right->Prev->Next = Left;
						tmpRight = Left->Prev;
						Left->Prev = Right->Prev;
						Right->Prev = tmpRight;
						tmpRight = Left->Next;
						Left->Next = Right->Next;
						Right->Next = tmpRight;
					} 
					else
					{
						Right->Prev = Left->Prev;
						Left->Next = Right->Next;
						Left->Prev = Right;
						Right->Next = Left;
					}


					tmpRight = Left;
					Left = Right;
					Right = tmpRight;
				}

				tmpLeft = Left;
				tmpRight = Right;
				do
				{
					if (tmpLeft->Inf > tmpLeft->Next->Inf)
						goto NextCmp; // для таких отдельный котел в аду
					tmpLeft = tmpLeft->Next;
				}while (tmpLeft != tmpRight);
				return;

NextCmp:	
				HeadL = tmpLeft != Left ? tmpLeft->Prev : tmpLeft;


				if (FirstLoop)
				{
					while  (tmpLeft != tmpRight)
					{
						if (tmpRight->Inf < tmpRight->Prev->Inf)
							break;
						tmpRight = tmpRight->Prev;
					}

					if (tmpLeft == Left)
						tmpLeft = tmpLeft->Next;

					if (tmpLeft != tmpRight)
					{
						HeadR = tmpRight != Right ? tmpRight->Next : tmpRight; 

						if (tmpRight == Right)
							tmpRight = tmpRight->Prev;
						if (tmpLeft->Next != tmpRight)
						{
							while (tmpLeft->Next != tmpRight->Prev)
							{
								if (tmpLeft->Inf > tmpRight->Inf)
								{
									tmpLeft->Prev->Next = tmpRight;
									tmpRight->Next->Prev = tmpLeft;
									tmpLeft->Next->Prev = tmpRight;
									tmpRight->Prev->Next = tmpLeft;
									
									Cur = tmpLeft->Prev;
									tmpLeft->Prev = tmpRight->Prev;
									tmpRight->Prev = Cur;

									Cur = tmpLeft->Next;
									tmpLeft->Next = tmpRight->Next;
									tmpRight->Next = Cur;
									
									Cur = tmpLeft;
									tmpLeft = tmpRight;
									tmpRight = Cur;

									tmpLeft = tmpLeft->Next;
									if (tmpLeft->Next != tmpRight->Prev)
										tmpRight = tmpRight->Prev;
									continue;
								}
								break;
							}
							if (tmpLeft->Next == tmpRight && tmpLeft->Inf > tmpRight->Inf)
							{
								tmpLeft->Prev->Next = tmpRight;
								tmpRight->Next->Prev = tmpLeft;
								tmpRight->Prev = tmpLeft->Prev;
								tmpLeft->Prev = tmpRight;
								tmpLeft->Next = tmpRight->Next;
								tmpRight->Next = tmpLeft;
							}
						}

						tmpRight = HeadR != Right->Prev && HeadR->Inf < HeadR->Prev->Inf ? HeadR : HeadR->Prev;

						if (tmpRight != Right && tmpRight->Next != Right && tmpRight->Inf > Left->Inf && Right->Inf > tmpRight->Inf)
						{
							Right->Prev->Next = tmpRight;
							tmpRight->Prev->Next = Right;
							if (Right != Tail)
								Right->Next->Prev = tmpRight;
							else
								Tail = tmpRight;
												
							tmpRight->Next->Prev = Right;

							Cur = Right->Prev;
							Right->Prev = tmpRight->Prev;
							tmpRight->Prev = Cur;

							Cur = Right->Next;
							Right->Next = tmpRight->Next;
							tmpRight->Next = Cur;

							Right = tmpRight;
						}
					}
				}

				
				tmpLeft = HeadL->Next;
				while (tmpLeft != Right->Prev && tmpLeft->Prev != Left)
				{
					if (tmpLeft->Inf < Right->Inf && Left->Inf < tmpLeft->Inf)
					{
						if (Left != Head)
							Left->Prev->Next = tmpLeft;
						else
							Head = tmpLeft;
						tmpLeft->Prev->Next = Left;
						Left->Next->Prev = tmpLeft;
						tmpLeft->Next->Prev = Left;

						Cur = Left->Prev;
						Left->Prev = tmpLeft->Prev;
						tmpLeft->Prev = Cur;

						Cur = Left->Next;
						Left->Next = tmpLeft->Next;
						tmpLeft->Next = Cur;

						Left = tmpLeft;
						break;
					}
					tmpLeft = tmpLeft->Next;
				}

				FirstLoop = 0;

				tmpLeft = LocalTail = Left;
				Cur = tmpLeft->Next;
				tmpRight = Right;
				HeadR = NewLeft = HeadL = NULL;

				while (Cur != Right)
				{
					if (Cur->Inf <= tmpLeft->Inf)
					{
						HeadL = Cur;
						do
						{
							Cur = Cur->Next;
						}while (Cur->Inf < tmpLeft->Inf);
						LocalTail = Cur->Prev;
						HeadL->Prev->Next = Cur;
						Cur->Prev = HeadL->Prev;
						LocalTail->Next = tmpLeft;
						if (tmpLeft->Prev != NULL) 
							tmpLeft->Prev->Next = HeadL; 
						else 
							Head = HeadL;
						HeadL->Prev = tmpLeft->Prev;
						tmpLeft->Prev = LocalTail;
						if (Left == tmpLeft) 
							Left = HeadL;
						if (Cur == Right) 
							goto IsCall;
					}

					if (Cur->Inf >= Right->Inf)
					{
						HeadR = Cur;
						do
						{
							Cur = Cur->Next;
						}while (Cur != Right && Cur->Inf >= Right->Inf);
						LocalTail = Cur->Prev;
						HeadR->Prev->Next = Cur;
						Cur->Prev = HeadR->Prev;
						HeadR->Prev = Right;
						if (Right->Next != NULL) 
							Right->Next->Prev = LocalTail; 
						else 
							Tail = LocalTail;
						LocalTail->Next = Right->Next;
						Right->Next = HeadR;
						if (Right == tmpRight)
							tmpRight = LocalTail;

						if (Cur == Right) 
							goto IsCall; 
						continue;
					}

					if ((HeadL == NULL) && ((Cur->Inf < LocalTail->Inf) && ((NewLeft == NULL) || (NewLeft->Inf > Cur->Inf)))) 
						NewLeft = Cur;


					LocalTail = Cur;
					Cur = Cur->Next;
				}
				if (NewLeft == HeadL) 
					return;


IsCall:			if (HeadR != NULL && Right->Next != tmpRight)
				{
					SortFull(Right->Next, tmpRight);
				}
				if (HeadL != NULL)
				{
					if (Left != tmpLeft->Prev)
						SortFull(Left, tmpLeft->Prev);				
					tmpLeft = tmpLeft->Next;
				}
				else 
					if (NewLeft != NULL)
					{
						if (NewLeft->Inf >= Right->Inf)
							return;						

						do
						{
							tmpLeft = tmpLeft->Next;
						}while (tmpLeft->Inf <= NewLeft->Inf);

					}

				Left = tmpLeft;

				if ((Right->Prev != Left) && (Left != Right)) 
					Right = Right->Prev;
			}while(tmpLeft != Right);
		}


//-----------------------------------------------------------------------

//-----------------------------------------------------------------------

	public:
		TBList()
		{
			Head = Tail = CurPos = NULL;
			SafeFlag = true;
		}

		~TBList()
		{
			DelAllElem();
		}


		TBList(TBList &List)
		{
			Head = Tail = CurPos = NULL;
			SafeFlag = true;
			*this = List;
		}

//-----------------------------------------------------------------------

// Получение / изменение флага, определяющего дествия при выполнении перегруженного оператора присваивания

		void SetSafeFlag(bool Val)
		{
			SafeFlag = Val;
		}

		bool GetSaveFlag()
		{
			return SafeFlag;
		}

		__declspec(property(get = GetSafeFlag, put = SetSafeFlag)) bool safeFlag;

//-----------------------------------------------------------------------

// Обнуляет указатели на первый, последний и текущий элементы списка.
// Применяется перед вызовом деструктора экземпляра класса, в случае использования
// "небезопасного" оператора присваивания

		void UnBindList()
		{
			Head = Tail = CurPos = NULL;
		}

//-----------------------------------------------------------------------

// Вставка нового элемента после последнего. Элемент задается своей информационной частью

		void AddAfterTail(INF &Inf)
		{
			TElem<INF> *Cur = new TElem<INF>;

			Cur->Inf = (INF&)Inf;
			Cur->Next = NULL;
			Cur->Prev = Tail;
			if (Head != NULL) 
				Tail->Next = Cur;
			else
				CurPos = Head = Cur;
			Tail = Cur;
		}
		
//-----------------------------------------------------------------------

// Вставка нового элемента после указанного. Элементы задаются своими информационной частью

		void AddToListAfterElem(INF &Inf, INF &InfAfter)
		{
			InsAfter(SearchElem(InfAfter), (INF&)Inf);
		}

//-----------------------------------------------------------------------

// Вставка нового элемента перед первым. Элемент задается своей информационной частью

		void AddBeforeHead(INF &Inf)
		{
			TElem<INF> *Cur = new TElem<INF>;

			Cur->Inf = (INF&)Inf;
			Cur->Next = Head;
			Cur->Prev = NULL;
			if (Head != NULL)
				Head->Prev = Cur;
			else
				CurPos = Tail = Cur;
			Head = Cur;
		}

//-----------------------------------------------------------------------

// Вставка нового элемента по порядку в отсортированный список. Элемент задается своей информационной частью

		void InsertByOrder(INF &Inf)
		{
			TElem<INF> *Cur = Tail;

			while ((Cur != NULL) && (Cur->Inf > Inf))
				Cur = Cur->Prev;

			if (Cur != NULL)
				InsAfter(Cur, Inf);
			else
				AddBeforeHead(Inf);
		}

//-----------------------------------------------------------------------

// Удаление элемента. Элемент задается своей информационной частью

		int DelFromList(INF &Inf)
		{
			TElem<INF> *Found = CurPos, *CurPosOld = CurPos;

			if (!((CurPos != NULL) && (CurPos->Inf == (INF&)Inf)))
				Found = SearchElem((INF&)Inf);

			CurPos = CurPosOld;

			if (Found == NULL) 
				return NOT_SUCCESS_OPER;

			if (CurPos == Found)
				CurPos = CurPos != Tail ? CurPos->Next : CurPos->Prev;

			DelElemFromList(Found);

			return SUCCESS_OPER;
		}

//-----------------------------------------------------------------------

// Удаление текущего элемента

		int DelCurElem()
		{
			TElem<INF> *Found = CurPos;

			if (Found == NULL)
				return NOT_SUCCESS_OPER;

			CurPos = CurPos->Next ? CurPos->Next : CurPos->Prev;
			DelElemFromList(Found);

			return SUCCESS_OPER;
		}

//-----------------------------------------------------------------------
// Восстановление упорядочивания для текущего элемента

		int SortCurElem()
		{
			if (CurPos != NULL)
			{
				TElem<INF> *CurPrevNext = CurPos->Prev;

				while ((CurPrevNext != NULL) && (CurPrevNext->Inf > CurPos->Inf))
					CurPrevNext = CurPrevNext->Prev;

				if (CurPrevNext != CurPos->Prev)
				{
					CurPos->Prev->Next = CurPos->Next;
					if (CurPos != Tail)
						CurPos->Next->Prev = CurPos->Prev;
					else
					{
						Tail = CurPos->Prev;
						Tail->Next = NULL;
					}
					CurPos->Prev = CurPrevNext;

					if (CurPrevNext != NULL)
					{
						CurPrevNext->Next->Prev = CurPos;
						CurPos->Next = CurPrevNext->Next;					
						CurPrevNext->Next = CurPos;
					}
					else
					{
						CurPos->Next = Head;
						Head = Head->Prev = CurPos;
					}
					return SUCCESS_OPER;
				}

				CurPrevNext = CurPos->Next;
				while ((CurPrevNext != NULL) && (CurPrevNext->Inf < CurPos->Inf))
					CurPrevNext = CurPrevNext->Next;


				if (CurPrevNext != CurPos->Next)
				{
					CurPos->Next->Prev = CurPos->Prev;
					if (CurPos != Head)
						CurPos->Prev->Next = CurPos->Next;
					else
					{
						Head = CurPos->Next;
						Head->Prev = NULL;
					}
					CurPos->Next = CurPrevNext;

					if (CurPrevNext != NULL)
					{
						CurPrevNext->Prev->Next = CurPos;
						CurPos->Prev = CurPrevNext->Prev;
						CurPrevNext->Prev = CurPos;
					}
					else
					{
						CurPos->Prev = Tail;
						Tail = Tail->Next = CurPos;
					}
						
				}
				return SUCCESS_OPER;
			}
			return NOT_SUCCESS_OPER;
		}

//-----------------------------------------------------------------------

// Поиск элемента. Элемент задается своей информационной частью

		int SearchElement(INF &Inf)
		{
			int res = (SearchElem(Inf) == NULL) ? NOT_SUCCESS_OPER : SUCCESS_OPER;

			if  (CurPos != NULL) 
				Inf = CurPos->Inf;

			return res;

		}

//-----------------------------------------------------------------------

// Сортировка списка

		void SortList()
		{
			Sort(Head, Tail);
		}

		void SortListBiDir()
		{
			if (Head != Tail)
				SortFull(Head, Tail);
		}

//-----------------------------------------------------------------------

// Удаление всех элементов из списка

		void DelAllElem()
		{
			TElem<INF> *Cur = Head;

			while (Head != NULL)
			{
				Cur = Head;
				Head = Head->Next;
				delete Cur;
			}

			CurPos = Tail = NULL;
		}

//-------------------------------------------------------------

// Получение указателя на информационную часть 1-го или последнего элементов

		int GetHeadTailInf(INF *&Inf, bool head = true)
		{
			if (!(*this))
			{
				Inf = head ? &Head->Inf : & Tail->Inf;
				return SUCCESS_OPER;
			}
			return NOT_SUCCESS_OPER;
		}

//-------------------------------------------------------------

// Получение указателя на информационную часть текущего элемента

		int GetCurInf(INF *&Inf)
		{
			if (CurPos != NULL)
			{
				Inf = &CurPos->Inf;
				return SUCCESS_OPER;
			}
			return NOT_SUCCESS_OPER;
		}

//-------------------------------------------------------------

// Получение копии информационной части текущего элемента

		int GetCurInf(INF &Inf)
		{
			if (CurPos != NULL)
			{
				Inf = CurPos->Inf;
				return SUCCESS_OPER;
			}
			return NOT_SUCCESS_OPER;
		}

//-------------------------------------------------------------

// Изменение информационной части текущего элемента

		int ModifyCurInf(INF &Inf)
		{
			if (CurPos != NULL)
			{
				CurPos->Inf = (INF&)Inf;
				return SUCCESS_OPER;
			}
			return NOT_SUCCESS_OPER;
		}


//-----------------------------------------------------------------------

// Проверка существования элементов в списке

		bool operator!()
		{
			return (Head != NULL);
		}

//--------------------------------------------------------------

// Переход к следующему элементу

		TBList& operator++()
		{
			if (CurPos != NULL)
				CurPos = CurPos->Next;

			return *this;
		}

//--------------------------------------------------------------

// Переход к предыдущему элементу

		TBList& operator--()
		{
			if (CurPos != NULL)
				CurPos = CurPos->Prev;

			return *this;
		}

//--------------------------------------------------------------

// Инициализация начала отсчета (указателя на текущий элемент)

		void SetStart(bool head = true)
		{
			CurPos = head ? Head : Tail;
		}

//--------------------------------------------------------------

// Перегруженный оператор присваивания для класса TBList

		TBList<INF>& operator=(TBList<INF> &Val)
		{
			if (this != &Val)
			{
				if (SafeFlag)
				{
					TElem<INF> *CurVal = Val.Head, *Cur = Head, *Prev;

					while ((CurVal != NULL) && (Cur!= NULL))
					{
						Cur->Inf = CurVal->Inf;
						CurVal = CurVal->Next;
						Cur = Cur->Next;
					}

					while (CurVal != NULL)
					{
						AddAfterTail(CurVal->Inf);
						CurVal = CurVal->Next;
					}

					if (Cur != NULL)
					{
						Tail = Cur->Prev;
						if (Tail != NULL)
							Tail->Next = NULL;
						else
							Head = NULL;
			
						while (Cur != NULL)
						{
							Prev = Cur;
							Cur = Cur->Next;
							delete Prev;
						}
					}
					CurPos = Head;
				}
				else
				{
					CurPos = Val.CurPos;
					Head = Val.Head;
					Tail = Val.Tail;
				}
				SafeFlag = Val.SafeFlag;

			}
			return *this;

		}

};


#endif