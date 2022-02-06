using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.IO.Pipes;
using FullSailAFI.GamePlaying.CoreAI;

namespace FullSailAFI.GamePlaying
{
    public class StudentAI : Behavior
    {
        TreeVisLib treeVisLib;  // lib functions to communicate with TreeVisualization
        bool visualizationFlag = false;  // turn this on to use tree visualization (which you will have to implement via the TreeVisLib API)
                                         // WARNING: Will hang program if the TreeVisualization project is not loaded!

        public StudentAI()
        {
            if (visualizationFlag == true)
            {
                if (treeVisLib == null)  // should always be null, but just in case
                    treeVisLib = TreeVisLib.getTreeVisLib();  // WARNING: Creation of this object will hang if the TreeVisualization project is not loaded!
            }
        }

        //
        // This function starts the look ahead process to find the best move
        // for this player color.
        //
        double alpha = double.NegativeInfinity, beta = double.PositiveInfinity;
       // int whiteDepth = 0;
       // int blackDepth = 0;
        public ComputerMove Run(int _nextColor, Board _board, int _lookAheadDepth)
        {
            ComputerMove nextMove = GetBestMove(_nextColor, _board, _lookAheadDepth, alpha, beta);
            
            return nextMove;
        }

        private int GetNextPlayer(int player, Board gamestate)
        {
            if (gamestate.HasAnyValidMove(-player))
            {
                return -player;
            }
            else
            {
                return player;
            }
        }

        //
        // This function uses look ahead to evaluate all valid moves for a
        // given player color and returns the best move it can find. This
        // method will only be called if there is at least one valid move
        // for the player of the designated color.
        //

        private ComputerMove GetBestMove(int color, Board board, int depth, double alpha, double beta)
        {
            //TODO: the lab
            // throw new NotImplementedException();
            //Black = -1, Empty = 0, White = 1
            ComputerMove bestMove = null;
            ComputerMove move = null;
            Board newState = new Board();

            List<ComputerMove> availableMoves = new List<ComputerMove>();
            


            if (board.HasAnyValidMove(color) == false)
            {
               bestMove = Run(GetNextPlayer(color, board), board, depth);
              
                return bestMove;
            }

                //generate valid moves
                for (int i = 0; i < Board.Width; i++)
                {
                    for (int j = 0; j < Board.Height; j++)
                    {
                        if (board.IsValidMove(color, i, j))
                        {
                            move = new ComputerMove(i, j);
                            availableMoves.Add(move);
                        }
                    }
                }
             

              foreach(ComputerMove space in availableMoves)
              {
                  newState.Copy(board);
                  newState.MakeMove(color, space.row, space.col); 
                
                if (newState.IsTerminalState() || depth == 0)
                {
                    space.rank = Evaluate(newState);
                }
                else
                {
                    space.rank = GetBestMove(GetNextPlayer(color, newState), newState, depth - 1, alpha, beta).rank;
                }

                if (bestMove == null || ((space.rank > bestMove.rank) && (color == 1)) || ((space.rank < bestMove.rank) && (color == -1)))
                {
                      bestMove = space;

                    //alpha beta
                    if (color == 1 && bestMove.rank > alpha)
                    {
                        alpha = bestMove.rank;
                    }
                    else if (color == -1 && bestMove.rank < beta)
                    {
                        beta = bestMove.rank;
                    }

                    if (alpha >= beta)
                    {
                        break;
                    }
                } 
              }


            return bestMove;

        }

        #region Recommended Helper Functions

        private int Evaluate(Board _board)
        {
            ////TODO: determine score based on position of pieces
             //return ExampleAI.MinimaxAFI.EvaluateTest(_board); // TEST WITH THIS FIRST, THEN IMPLEMENT YOUR OWN EVALUATE
            int points = 0;//look at player point of view not if greater than 0
            int curr = 0;

            for (int r = 0; r < Board.Width; r++)
            {
                for (int c = 0; c < Board.Height; c++)
                {
                    curr = _board.GetSquareContents(r, c);

                    if (curr != 0)
                    {
                        //corners
                        if ((r == 0 && c == 0) || (r == Board.Width - 1 && c == 0) || (r == Board.Width - 1 && c == Board.Height - 1) || (r == 0 && c == Board.Height - 1))
                        {
                            points += curr * 100;
                        }
                        else if ((r == 0 || r == Board.Width - 1) || (c == 0 || c == Board.Height - 1))//sides
                        {
                            points += curr * 10;
                        }
                        else
                        {
                            points += curr * 1;
                        }

                    }
                }
            }


            if (_board.IsTerminalState())
            {
                if (points > 0)
                {
                    points += 10000;
                }
                else
                {
                    points -= 10000;
                }
            }

            return points;
        }

        #endregion

    }
}
